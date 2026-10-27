// minus devkit — PIC32AK1216GC41048 "capture engine" firmware, step 1: inter-MCU link bring-up.
//
// Answers "PING n\n" received on UART1 (U1RX = RP39/RC6, pin 25, net UART_TX <- RP2354 GPIO16)
// with "PONG n\n" on U1TX = RP40/RC7 (pin 26, net UART_RX -> RP2354 GPIO17). Net names are from
// the RP's point of view (fw 0.1.1 had them swapped: both chips drove UART_TX, RP saw nothing). Toggles RDY (RA7 -> RP2354 GPIO7) on every reply, mirrors
// TRIG (RA0 <- RP2354 GPIO6) edges into a counter, blinks LED2 (RC5) as a heartbeat.
//
// Clocking (fw 0.1.1): PLL1 from the 8 MHz FRC -> VCO 640 MHz -> Fout 160 MHz = CLKGEN1 (CPU +
// peripherals, FCY) and VCO/2 = 320 MHz = CLKGEN6 (ADC) / CLKGEN12 = 160 MHz (SCCP). Same recipe
// as datasheet DS70005592 Example 18-3. The "standard speed peripheral clock" (UART CLKSEL = 0,
// Timer1, SCCP CLKSEL = 0) is the system clock / 2 = FPB (Table 21-2, Table 26-2).
// FRC is +/-1.5 %, fine for 115200 baud.
//
// Register/bitfield names and #pragma config names are checked against the PIC32AK-GC_DFP
// 1.1.53 device header p32AK1216GC41048.h; the source compiles with XC-DSC 3.31.01.
//
// Bus ownership (decision 2026-10-26): the RP2354 is the only master of the digipots
// (MCP4131 x2 on SPI, MCP4531 x2 + MCP4728 on I2C). The PIC's SPI pins (RD0/RD1/RD2/RC2) and
// I2C pins (RD7/RD8) stay Hi-Z (inputs, reset default) in this step — do not enable SPI1/I2C2.
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "version.h"
#include "acq.h"

// ---------------------------------------------------------------- configuration bits
// JTAG must be OFF: TCK/TDO/TDI/TMS sit on RD1 (SPI_CLK), RD2 (SPI_MOSI), RD3, RB1 (digipot).
#pragma config JTAGEN = OFF        // FICD: JTAG off (else TCK/TDO/TMS steal the SPI pins)
#pragma config WDTEN  = SW         // FWDT: watchdog under software control (stays off)
#pragma config WINDIS = ON         // FWDT: non-window mode
// (this family has no ICS / debug-pair config setting: any PGCx/PGDx pair works for ICSP)

// ---------------------------------------------------------------- clocks
#define FCY 160000000UL          // CLKGEN1 = PLL1 Fout
#define FPB (FCY / 2)            // standard speed peripheral clock = system clock / 2

static void clocks_init(void) {
    // DS70005592 Example 18-3 ("OscillatorInitialization"): FRC 8 MHz, PLLPRE 1, FBDIV 80 -> VCO
    // 640 MHz (OS51: 500-1600 MHz); POSTDIV1 4, POSTDIV2 1 -> Fout 160 MHz; VCO1DIV INTDIV 1 ->
    // VCO/(2*1) = 320 MHz for the ADC (CLKGEN6 max input 320 MHz, TAD = 80 MHz -> 40 Msps).
    PLL1CONbits.ON = 1;
    OSCCTRLbits.PLL1EN = 1;
    while (OSCCTRLbits.PLL1RDY == 0) ;
    PLL1CONbits.FSCMEN = 0;                 // no fail-safe clock monitor during bring-up
    VCO1DIVbits.INTDIV = 1;                 // VCO div output = 640 / (2*1) = 320 MHz
    PLL1DIVbits.PLLFBDIV = 80;              // 8 MHz * 80 = 640 MHz
    PLL1DIVbits.PLLPRE = 1;
    PLL1DIVbits.POSTDIV1 = 4;               // 640 / 4 = 160 MHz
    PLL1DIVbits.POSTDIV2 = 1;
    PLL1CONbits.DIVSWEN = 1;  while (PLL1CONbits.DIVSWEN) ;    // latch VCO divider
    PLL1CONbits.NOSC = 1;                   // PLL input = FRC
    PLL1CONbits.OSWEN = 1;    while (PLL1CONbits.OSWEN) ;
    PLL1CONbits.FOUTSWEN = 1; while (PLL1CONbits.FOUTSWEN) ;   // latch output dividers
    PLL1CONbits.PLLSWEN = 1;  while (PLL1CONbits.PLLSWEN) ;    // latch input/feedback dividers
    while (PLL1CONbits.CLKRDY == 0) ;
    // CLKGEN1 (CPU + peripherals) <- PLL1 Fout (NOSC 5) = 160 MHz
    CLK1CONbits.NOSC = 5;  CLK1CONbits.OSWEN = 1;  while (CLK1CONbits.OSWEN) ;  while (CLK1CONbits.CLKRDY == 0) ;
    // CLKGEN6 (ADC) <- PLL1 VCO divider (NOSC 7) = 320 MHz
    CLK6CONbits.ON = 1;  CLK6CONbits.NOSC = 7;  CLK6CONbits.OSWEN = 1;  while (CLK6CONbits.OSWEN) ;  while (CLK6CONbits.CLKRDY == 0) ;
    // CLKGEN12 (SCCP / REFO1) <- PLL1 Fout (NOSC 5) = 160 MHz
    CLK12CONbits.ON = 1; CLK12CONbits.NOSC = 5; CLK12CONbits.OSWEN = 1; while (CLK12CONbits.OSWEN) ; while (CLK12CONbits.CLKRDY == 0) ;
}

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
    TRISCbits.TRISC6 = 1;           // RC6 = RP39 = U1RX  (net UART_TX, driven by the RP)
    TRISCbits.TRISC7 = 0;           // RC7 = RP40 = U1TX  (net UART_RX, read by the RP)
}

static void pps_init(void) {
    // Unlock: PACCON2.RPCONWR enables writes to RPCON, then clear RPCON.IOLOCK.
    PACCON2bits.RPCONWR = 1;
    RPCONbits.IOLOCK = 0;
    RPINR9bits.U1RXR = 39;          // U1RX <- RP39 (RC6, pin 25, net UART_TX)
    RPOR9bits.RP40R  = 9;           // RP40 (RC7, pin 26, net UART_RX) -> U1TX (output function 9, Table 14-13)
    RPCONbits.IOLOCK = 1;
}

static void uart1_init(void) {
    U1CON = 0;
    // CLKSEL[1:0]=0: FUART = standard speed peripheral clock = FPB (system clock / 2, Table 21-2);
    // CLKMOD=1 (fractional): baud = FUART / BRG.  (0.1.0 wrongly assumed FUART = 8 MHz.)
    U1BRG = FPB / 115200UL;         // 694 -> 115 274 baud (+0.06 %)
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
    clocks_init();
    pins_init();
    pps_init();
    uart1_init();
    acq_init();

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
                } else if (!strncmp(line, "ACQ", 3) && (line[3] == 0 || line[3] == ' ')) {
                    // ACQ [div]: one capture; reply = header line, then ACQ_N little-endian u16 only on "ok"
                    if (line[3] == ' ') acq_set_div((unsigned)strtoul(line + 4, NULL, 10));
                    uint32_t t = 0; acq_status_t st = acq_run(&t);
                    const char *sname = st == ACQ_OK ? "ok" : st == ACQ_TIMEOUT ? "timeout" : st == ACQ_DMAERR ? "dmaerr" : st == ACQ_OVERRUN ? "overrun" : "notready";
                    char out[48]; snprintf(out, sizeof out, "ACQ %u %lu %u %s\n", (unsigned)ACQ_N, (unsigned long)t, (unsigned)ACQ_TICK_NS, sname);
                    uart1_puts(out);
                    if (st == ACQ_OK)
                        for (unsigned i = 0; i < ACQ_N; i++) { uart1_putc((char)(acq_buf[i] & 0xFF)); uart1_putc((char)(acq_buf[i] >> 8)); }
                } else if (!strcmp(line, "ID?")) {
                    uart1_puts("PIC32AK1216GC41048 " FW_NAME " " FW_VERSION " proto " FW_STR(PROTO_VERSION) "\n");
                } else if (len == 0 && line[0]) {
                    uart1_puts("ERR\n");
                }
            } else if (len < (int)sizeof line - 1) line[len++] = (char)c;
        }
        if (++beat == 4000000UL) { beat = 0; LED2_LAT ^= 1; }   // ~heartbeat at 160 MHz
    }
}
