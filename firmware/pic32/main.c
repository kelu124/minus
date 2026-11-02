// minus devkit — PIC32AK1216GC41048 "capture engine" firmware, step 1: inter-MCU link bring-up.
//
// Answers "PING n\n" received on UART1 (U1RX = RP39/RC6, pin 25, net UART_TX <- RP2354 GPIO16)
// with "PONG n\n" on U1TX = RP40/RC7 (pin 26, net UART_RX -> RP2354 GPIO17). Net names are from
// the RP's point of view (fw 0.1.1 had them swapped: both chips drove UART_TX, RP saw nothing). Toggles RDY (RA7 -> RP2354 GPIO7) on every reply, mirrors
// TRIG (RA0 <- RP2354 GPIO6) edges into a counter, blinks LED2 (RC5) as a heartbeat.
//
// Clocking (fw 0.1.20, 2026-11-02): PLL1 from the 8 MHz FRC -> VCO 1000 MHz -> Fout 200 MHz = CLKGEN1
// (CPU + peripherals, FCY; 200 MHz is the rated maximum, OS25 TCY >= 5 ns) and VCO/4 = 250 MHz = CLKGEN6
// (ADC: TAD = 250/4 = 62.5 MHz -> 32 ns conversions) / CLKGEN12 = 200 MHz (SCCP, 5 ns ticks). Same
// recipe as the datasheet PTG/ADC example ("clocks_initialize", CPU 200 MHz + 250 MHz ADC clock).
// fw 0.1.1-0.1.19 ran VCO 640 -> 160 MHz CPU / 320 MHz ADC (Example 18-3); the DMA then moved one word
// per 50 ns (20 Msps); at 200 MHz it is 40 ns (25 Msps). 320 MHz for the ADC now needs PLL2 (todo). The "standard speed peripheral clock" (UART CLKSEL = 0,
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
#define FCY 200000000UL          // CLKGEN1 = PLL1 Fout (rated max; was 160 MHz until fw 0.1.19)
#define FPB (FCY / 2)            // standard speed peripheral clock = system clock / 2

static void clocks_init(void) {
    // FRC 8 MHz, PLLPRE 1, FBDIV 125 -> VCO 1000 MHz (OS51: 500-1600 MHz); POSTDIV1 5, POSTDIV2 1 ->
    // Fout 200 MHz; VCO1DIV INTDIV 2 -> VCO/(2*2) = 250 MHz for the ADC (CLKGEN6 max input 320 MHz;
    // TAD = input/4 = 62.5 MHz -> 1.5 TAD conversion + 0.5 TAD sampling = 32 ns = 31.25 Msps core).
    // One PLL cannot give 200 MHz Fout and 320 MHz VCO-div at once (VCO/(2n) of 1000 = 500/250/...).
    PLL1CONbits.ON = 1;
    OSCCTRLbits.PLL1EN = 1;
    while (OSCCTRLbits.PLL1RDY == 0) ;
    PLL1CONbits.FSCMEN = 0;                 // no fail-safe clock monitor during bring-up
    VCO1DIVbits.INTDIV = 2;                 // VCO div output = 1000 / (2*2) = 250 MHz
    PLL1DIVbits.PLLFBDIV = 125;             // 8 MHz * 125 = 1000 MHz
    PLL1DIVbits.PLLPRE = 1;
    PLL1DIVbits.POSTDIV1 = 5;               // 1000 / 5 = 200 MHz
    PLL1DIVbits.POSTDIV2 = 1;
    PLL1CONbits.DIVSWEN = 1;  while (PLL1CONbits.DIVSWEN) ;    // latch VCO divider
    PLL1CONbits.NOSC = 1;                   // PLL input = FRC
    PLL1CONbits.OSWEN = 1;    while (PLL1CONbits.OSWEN) ;
    PLL1CONbits.FOUTSWEN = 1; while (PLL1CONbits.FOUTSWEN) ;   // latch output dividers
    PLL1CONbits.PLLSWEN = 1;  while (PLL1CONbits.PLLSWEN) ;    // latch input/feedback dividers
    while (PLL1CONbits.CLKRDY == 0) ;
    // CLKGEN1 (CPU + peripherals) <- PLL1 Fout (NOSC 5) = 200 MHz
    CLK1CONbits.NOSC = 5;  CLK1CONbits.OSWEN = 1;  while (CLK1CONbits.OSWEN) ;  while (CLK1CONbits.CLKRDY == 0) ;
    // CLKGEN6 (ADC) <- PLL1 VCO divider (NOSC 7) = 250 MHz
    CLK6CONbits.ON = 1;  CLK6CONbits.NOSC = 7;  CLK6CONbits.OSWEN = 1;  while (CLK6CONbits.OSWEN) ;  while (CLK6CONbits.CLKRDY == 0) ;
    // CLKGEN12 (SCCP / REFO1) <- PLL1 Fout (NOSC 5) = 200 MHz (5 ns per SCCP count)
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
                    // ACQ [div [samc [in [navg]]]]: one capture; reply = header line, then ACQ_N little-endian u16 only on "ok"
                    if (line[3] == ' ') {
                        char *e; acq_set_div((unsigned)strtoul(line + 4, &e, 10));
                        if (*e == ' ') { acq_set_samc((int)strtol(e + 1, &e, 10));
                            if (*e == ' ') { acq_set_input((unsigned)strtoul(e + 1, &e, 10));
                                if (*e == ' ') acq_set_navg((unsigned)strtoul(e + 1, NULL, 10)); } }
                    }
                    RDY_LAT = 0;                        // PONG may have left RDY high; the RP times the RDY pulse of this capture
                    uint32_t t = 0; acq_status_t st = acq_run(&t);
                    const char *sname = st == ACQ_OK ? "ok" : st == ACQ_TIMEOUT ? "timeout" : st == ACQ_DMAERR ? "dmaerr" : st == ACQ_OVERRUN ? "overrun" : "notready";
                    char out[48]; snprintf(out, sizeof out, "ACQ %u %lu %u %s\n", (unsigned)ACQ_N, (unsigned long)t, (unsigned)ACQ_TICK_NS, sname);
                    uart1_puts(out);
                    if (st == ACQ_OK)
                        for (unsigned i = 0; i < ACQ_N; i++) { uart1_putc((char)(acq_buf[i] & 0xFF)); uart1_putc((char)(acq_buf[i] >> 8)); }
                } else if (!strncmp(line, "AMP1 ", 5)) {
                    // AMP1 0|1: op amp 1 off/on (high-power mode, external gain). On at boot (acq_init).
                    AMP1CON1bits.AMPEN = line[5] == '1';
                    char out[24]; snprintf(out, sizeof out, "AMP1 %u\n", (unsigned)AMP1CON1bits.AMPEN);
                    uart1_puts(out);
                } else if (!strncmp(line, "AMP2 ", 5)) {
                    // AMP2 0|1: op amp 2 (OA2IN+ = OA1OUT pin 18/RB2, OA2IN- = RB1 pin 17 = U11 wiper + R49 1k to GND,
                    // OA2OUT = RB0 pin 16 = FE_A_OUT / AD2AN1). Gain = 1 + R_AW(U11) / 1k, set over I2C by the RP ("pot 0 n").
                    // Off at boot. High-power mode, external gain, like AMP1. RB0..RB2 are analog by reset default.
                    AMP2CON1bits.UGE   = 0;
                    AMP2CON1bits.HPEN  = 1;
                    AMP2CON1bits.AMPEN = line[5] == '1';
                    char out[24]; snprintf(out, sizeof out, "AMP2 %u\n", (unsigned)AMP2CON1bits.AMPEN);
                    uart1_puts(out);
                } else if (!strncmp(line, "ACQCPU ", 7)) {
                    // ACQCPU <trg> [rptcnt [gap [phase]]]: CPU-loop capture (no DMA), same reply format as ACQ
                    char *e; unsigned trg = (unsigned)strtoul(line + 7, &e, 10); unsigned r = 1, gap = 0, phase = 0;
                    if (*e == ' ') { r = (unsigned)strtoul(e + 1, &e, 10); if (*e == ' ') { gap = (unsigned)strtoul(e + 1, &e, 10); if (*e == ' ') phase = (unsigned)strtoul(e + 1, NULL, 10); } }
                    RDY_LAT = 0;
                    uint32_t t = 0; acq_status_t st = acq_cpu_run(trg, r, gap, phase, &t);
                    char out[48]; snprintf(out, sizeof out, "ACQ %u %lu %u %s\n", (unsigned)ACQ_N, (unsigned long)t, (unsigned)ACQ_TICK_NS, st == ACQ_OK ? "ok" : "notready");
                    uart1_puts(out);
                    if (st == ACQ_OK)
                        for (unsigned i = 0; i < ACQ_N; i++) { uart1_putc((char)(acq_buf[i] & 0xFF)); uart1_putc((char)(acq_buf[i] >> 8)); }
                } else if (!strncmp(line, "ACQIL", 5) && (line[5] == 0 || line[5] == ' ')) {
                    // ACQIL [div [off [navg]]]: two-channel interleaved integration capture (CH0 SCCP1, CH1 SCCP2
                    // offset by off counts, navg-sums each); same reply format as ACQ with n = ACQ_IL_N
                    unsigned off = 0, navg = 2;
                    if (line[5] == ' ') { char *e; acq_set_div((unsigned)strtoul(line + 6, &e, 10));
                        if (*e == ' ') { off = (unsigned)strtoul(e + 1, &e, 10); if (*e == ' ') navg = (unsigned)strtoul(e + 1, NULL, 10); } }
                    RDY_LAT = 0;
                    uint32_t t = 0; acq_status_t st = acq_il_run(off, navg, &t);
                    const char *sname = st == ACQ_OK ? "ok" : st == ACQ_TIMEOUT ? "timeout" : st == ACQ_DMAERR ? "dmaerr" : st == ACQ_OVERRUN ? "overrun" : "notready";
                    char out[48]; snprintf(out, sizeof out, "ACQ %u %lu %u %s\n", (unsigned)ACQ_IL_N, (unsigned long)t, (unsigned)ACQ_TICK_NS, sname);
                    uart1_puts(out);
                    if (st == ACQ_OK)
                        for (unsigned i = 0; i < ACQ_IL_N; i++) { uart1_putc((char)(acq_buf[i] & 0xFF)); uart1_putc((char)(acq_buf[i] >> 8)); }
                } else if (!strncmp(line, "ADCBB ", 6)) {
                    // ADCBB <n> [ovs]: time n back-to-back conversions (no DMA); reply "ADCBB n ovs ticks tick_ns data"
                    char *e; unsigned n = (unsigned)strtoul(line + 6, &e, 10); unsigned ovs = *e == ' ' ? (unsigned)strtoul(e + 1, NULL, 10) : 0;
                    uint32_t data = 0, t = acq_adc_bb(n, ovs, &data);
                    char out[64]; snprintf(out, sizeof out, "ADCBB %u %u %lu %u %lu\n", n, ovs, (unsigned long)t, (unsigned)ACQ_TICK_NS, (unsigned long)data);
                    uart1_puts(out);
                } else if (!strncmp(line, "CLK12 ", 6)) {
                    // diagnostic: re-source CLKGEN12 (SCCP1 trigger clock). 1 = FRC 8 MHz, 5 = PLL1 Fout (200 MHz), 7 = PLL1 VCO/4 (250 MHz)
                    unsigned n = (unsigned)strtoul(line + 6, NULL, 10) & 0xF;
                    CLK12CONbits.NOSC = n; CLK12CONbits.OSWEN = 1;
                    uint32_t guard = 2000000; while (CLK12CONbits.OSWEN && --guard) ;
                    guard = 2000000; while (CLK12CONbits.CLKRDY == 0 && --guard) ;
                    char out[40]; snprintf(out, sizeof out, "CLK12 cosc=%u rdy=%u\n", (unsigned)CLK12CONbits.COSC, (unsigned)CLK12CONbits.CLKRDY);
                    uart1_puts(out);
                } else if (!strcmp(line, "ID?")) {
                    uart1_puts("PIC32AK1216GC41048 " FW_NAME " " FW_VERSION " proto " FW_STR(PROTO_VERSION) "\n");
                } else if (len == 0 && line[0]) {
                    uart1_puts("ERR\n");
                }
            } else if (len < (int)sizeof line - 1) line[len++] = (char)c;
        }
        if (++beat == 5000000UL) { beat = 0; LED2_LAT ^= 1; }   // ~heartbeat at 200 MHz (loop count)
    }
}
