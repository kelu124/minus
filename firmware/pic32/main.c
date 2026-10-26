// minus devkit — PIC32AK1216GC41048 "capture engine" firmware, step 1: inter-MCU link bring-up.
//
// Answers "PING n\n" received on UART1 (RP40/RC7 <- RP2354 GPIO16) with "PONG n\n" on
// RP39/RC6 (-> RP2354 GPIO17). Toggles RDY (RA7 -> RP2354 GPIO7) on every reply, mirrors
// TRIG (RA0 <- RP2354 GPIO6) edges into a counter, blinks LED2 (RC5) as a heartbeat.
//
// Clocking: left at the reset default (CLKGEN1 = FRC 8 MHz, no PLL). FRC is +/-1.5 %, fine
// for 115200 baud. UART clock = "standard speed peripheral clock" (CLKSEL = 0) = 8 MHz.
//
// *** NOT YET COMPILED: XC-DSC is not installed on this machine (see firmware/README.md).
// *** Register/bitfield names and #pragma config names were checked (2026-10-26) against the
// *** PIC32AK-GC_DFP 1.1.53 device header p32AK1216GC41048.h and its config_docs.
//
// Bus ownership (decision 2026-10-26): the RP2354 is the only master of the digipots
// (MCP4131 x2 on SPI, MCP4531 x2 + MCP4728 on I2C). The PIC's SPI pins (RD0/RD1/RD2/RC2) and
// I2C pins (RD7/RD8) stay Hi-Z (inputs, reset default) in this step — do not enable SPI1/I2C2.
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "version.h"

// ---------------------------------------------------------------- configuration bits
// JTAG must be OFF: TCK/TDO/TDI/TMS sit on RD1 (SPI_CLK), RD2 (SPI_MOSI), RD3, RB1 (digipot).
#pragma config JTAGEN = OFF        // FICD: JTAG off (else TCK/TDO/TMS steal the SPI pins)
#pragma config WDTEN  = SW         // FWDT: watchdog under software control (stays off)
#pragma config WINDIS = ON         // FWDT: non-window mode
// (this family has no ICS / debug-pair config setting: any PGCx/PGDx pair works for ICSP)

// ---------------------------------------------------------------- pins
#define LED2_LAT   LATCbits.LATC5
#define RDY_LAT    LATAbits.LATA7
#define TRIG_PORT  PORTAbits.RA0

static volatile uint32_t trig_edges;

static void pins_init(void) {
    // RA0 (TRIG in) and RA7 (RDY out) are analog-capable (AD2AN6 / AD1AN6): make them digital.
    ANSELAbits.ANSELA0 = 0;
    ANSELAbits.ANSELA7 = 0;
    TRISAbits.TRISA0 = 1;           // TRIG input
    RDY_LAT = 0; TRISAbits.TRISA7 = 0;   // RDY output
    LED2_LAT = 0; TRISCbits.TRISC5 = 0;  // LED2 output
    TRISCbits.TRISC6 = 0;           // RC6 = U1TX (RP39)
    TRISCbits.TRISC7 = 1;           // RC7 = U1RX (RP40)
}

static void pps_init(void) {
    // Unlock: PACCON2.RPCONWR enables writes to RPCON, then clear RPCON.IOLOCK.
    PACCON2bits.RPCONWR = 1;
    RPCONbits.IOLOCK = 0;
    RPINR9bits.U1RXR = 40;          // U1RX <- RP40 (RC7)
    RPOR9bits.RP39R  = 9;           // RP39 (RC6) -> U1TX (output function code 9, Table 14-13)
    RPCONbits.IOLOCK = 1;
}

static void uart1_init(void) {
    U1CON = 0;
    // CLKSEL[1:0]=0 (peripheral clock, 8 MHz), CLKMOD=1 (fractional): baud = FUART / BRG
    U1BRG = 8000000UL / 115200UL;   // 69 -> 115 942 baud (+0.6 %)
    U1CONbits.CLKMOD = 1;
    U1CONbits.MODE   = 0;           // 8N1, asynchronous
    U1CONbits.TXEN   = 1;
    U1CONbits.RXEN   = 1;
    U1CONbits.ON     = 1;
}
static void uart1_putc(char c) { while (U1STATbits.TXBF) ; U1TXB = c; }
static void uart1_puts(const char *s) { while (*s) uart1_putc(*s++); }
static int  uart1_getc_nb(void) { return U1STATbits.RXBE ? -1 : (int)(uint8_t)U1RXB; }

int main(void) {
    pins_init();
    pps_init();
    uart1_init();

    char line[64]; int len = 0;
    uint32_t beat = 0; int last_trig = TRIG_PORT;
    uart1_puts("PIC32 up\n");
    for (;;) {
        // TRIG edge counter (polled; good enough for bring-up)
        int t = TRIG_PORT; if (t && !last_trig) trig_edges++; last_trig = t;

        int c = uart1_getc_nb();
        if (c >= 0) {
            if (c == '\r') continue;
            if (c == '\n') {
                line[len] = 0; len = 0;
                if (!strncmp(line, "PING ", 5)) {
                    char out[32]; snprintf(out, sizeof out, "PONG %s\n", line + 5);
                    uart1_puts(out);
                    RDY_LAT ^= 1;                       // toggles once per reply
                } else if (!strcmp(line, "TRIG?")) {
                    char out[32]; snprintf(out, sizeof out, "TRIG %lu\n", (unsigned long)trig_edges);
                    uart1_puts(out);
                } else if (!strcmp(line, "ID?")) {
                    uart1_puts("PIC32AK1216GC41048 " FW_NAME " " FW_VERSION " proto " FW_STR(PROTO_VERSION) "\n");
                } else if (len == 0 && line[0]) {
                    uart1_puts("ERR\n");
                }
            } else if (len < (int)sizeof line - 1) line[len++] = (char)c;
        }
        if (++beat == 200000UL) { beat = 0; LED2_LAT ^= 1; }   // ~heartbeat at 8 MHz
    }
}
