// minus v1.1 (board 3) — PIC32AK1216GC41048 "capture engine" firmware.
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
// Bus ownership: the RP2354 is the only I2C master; the PIC's I2C pins (RD7/RD8) stay Hi-Z. Since proto 11 (pic 1.1.1)
// SPI1 is a client of the RP's SPI0 (RD0 SS1, RD1 SCK1, RD2 SDI1 unused, RC2 SDO1): capture payloads go out as framed
// SPI transfers ("SPIX"), the UART keeps the commands and the fallback payload path ("UTX"). The ACQ commands no longer
// push their payload: the RP pulls it (docs/claude/specs/2026-11-21-dac-spi-link-design.md).
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "version.h"
#include "acq.h"
#include "dac.h"
#include "xfer.h"
#include "pe_ext.h"

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

#define RDY_LAT    LATAbits.LATA7

// ---------------------------------------------------------------- slow-lock self-heal (pic 1.1.2)
// Bench 2026-11-22 (docs/bench/2026-11-22-slowlock/): the "slow" ADC lock (40/60/60 ns sample pattern, datasheet E2) is a
// per-boot state — after a PLL1 lock either ~all captures are ok or 85-100 % are slow, 6 of 12 boots each; re-sourcing
// CLKGEN12 does not change it. So the phase between PLL1's dividers (CPU/SCCP = VCO/5, ADC = VCO/4) decides it, and a
// fresh lock re-rolls it. At boot (and on RELOCK) the PIC test-captures and re-locks PLL1 until the captures are uniform.
#define LOCK_TEST_N   8u        // test captures per lock; 0 slow required (a mixed state runs ~35 % slow: 0.65^8 = 3 % escape)
#define LOCK_MAX      12u       // locks tried (p(not good) ~ 0.6 each -> 0.2 % to end not good)
static unsigned lock_tries, lock_slow;
static void uart1_init(void);
static void clocks_relock(void) {
    AD1CONbits.ON = 0; AD2CONbits.ON = 0;
    uint32_t g;
    CLK1CONbits.NOSC = 1;  CLK1CONbits.OSWEN = 1;  g = 2000000; while (CLK1CONbits.OSWEN && --g) ;   // CPU on FRC
    CLK6CONbits.NOSC = 1;  CLK6CONbits.OSWEN = 1;  g = 2000000; while (CLK6CONbits.OSWEN && --g) ;
    CLK12CONbits.NOSC = 1; CLK12CONbits.OSWEN = 1; g = 2000000; while (CLK12CONbits.OSWEN && --g) ;
    PLL1CONbits.ON = 0; OSCCTRLbits.PLL1EN = 0;
    g = 2000000; while (OSCCTRLbits.PLL1RDY && --g) ;
    clocks_init();
    uart1_init();
    acq_init();
}
static unsigned lock_check(void) {           // slow captures out of LOCK_TEST_N, at the standard settings (div 4, samc 0, navg 1)
    unsigned slow = 0; uint32_t t;
    acq_saved_t sv = pe_std_begin();          // a user's navg / samc would disable the slow check (review 2026-11-22)
    for (unsigned i = 0; i < LOCK_TEST_N; i++) if (acq_run(&t) == ACQ_SLOW) slow++;
    pe_std_end(sv);
    RDY_LAT = 0;
    return slow;
}
// RDY may have been left high by PING (it toggles RDY per reply): make the low phase before a capture / SPI frame long enough
// for the RP's polling to see it (review 2026-11-22; the plain RDY_LAT = 0 lasted well under 1 us).
static void rdy_low_settle(void) {
    if (RDY_LAT) { RDY_LAT = 0; for (volatile unsigned i = 0; i < 400; i++) ; }   // ~8 us at 200 MHz
    RDY_LAT = 0;
}
static void lock_until_uniform(void) {
    for (lock_tries = 1; ; lock_tries++) {
        lock_slow = lock_check();
        if (lock_slow == 0 || lock_tries >= LOCK_MAX) break;
        clocks_relock();
    }
}

// ---------------------------------------------------------------- pins
#define LED2_LAT   LATCbits.LATC5
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
    RPINR10bits.SCK1R = 50;         // SCK1 <- RP50 (RD1, pin 38, net SPI_CLK  <- RP GPIO2)
    RPINR10bits.SDI1R = 51;         // SDI1 <- RP51 (RD2, pin 39, net SPI_MOSI <- RP GPIO3; DISSDI, unused)
    RPINR10bits.SS1R  = 49;         // SS1  <- RP49 (RD0, pin 37, net SPI_CS   <- RP GPIO5)
    RPOR8bits.RP35R   = 13;         // RP35 (RC2, pin 31, net SPI_MISO -> RP GPIO4) <- SDO1 (output function 13)
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
    xfer_spi_init();
    lock_until_uniform();

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
                    // navg goes back to 1 unless given (pic 1.1.4): it used to persist and silently change the next capture
                    unsigned navg = 1;
                    if (line[3] == ' ') {
                        char *e; acq_set_div((unsigned)strtoul(line + 4, &e, 10));
                        if (*e == ' ') { acq_set_samc((int)strtol(e + 1, &e, 10));
                            if (*e == ' ') { acq_set_input((unsigned)strtoul(e + 1, &e, 10));
                                if (*e == ' ') navg = (unsigned)strtoul(e + 1, NULL, 10); } }
                    }
                    acq_set_navg(navg);
                    rdy_low_settle();                   // PONG may have left RDY high; the RP times the RDY pulse of this capture
                    uint32_t t = 0; acq_status_t st = acq_run(&t);
                    const char *sname = st == ACQ_OK ? "ok" : st == ACQ_TIMEOUT ? "timeout" : st == ACQ_DMAERR ? "dmaerr" : st == ACQ_OVERRUN ? "overrun" : st == ACQ_SLOW ? "slow" : "notready";
                    char out[48]; snprintf(out, sizeof out, "ACQ %u %lu %u %s\n", (unsigned)ACQ_N, (unsigned long)t, (unsigned)ACQ_TICK_NS, sname);
                    xfer_set_n(st == ACQ_OK ? ACQ_N : 0);   // payload pulled by SPIX / UTX (proto 11)
                    uart1_puts(out);
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
                } else if (!strncmp(line, "PC", 2) && (line[2] == ' ' || line[2] == '?')) {
                    // PC 0|1: period-4 fixed-pattern correction off/on (on at boot); PC? = state + last offsets (LSB/16)
                    if (line[2] == ' ') acq_set_pc(line[3] == '1');
                    const int32_t *o; unsigned on = acq_get_pc(&o);
                    char out[64]; snprintf(out, sizeof out, "PC %u %ld %ld %ld %ld\n", on, (long)o[0], (long)o[1], (long)o[2], (long)o[3]);
                    uart1_puts(out);
                } else if (!strncmp(line, "UGE ", 4)) {
                    // UGE <a1> <a2>: op amp unity-gain enable (AMPxCON1.UGE, DS70005592 §32.4.2.1 = internal OUT -> IN- short,
                    // gain 1 whatever the external Rf/Rg). Board 3: the RP picks Rf via the 4052 (GPIO25/23); UGE = 1 bypasses
                    // that stage. The amp is disabled around the change.
                    char *e; unsigned a1 = (unsigned)strtoul(line + 4, &e, 10) & 1u, a2 = *e == ' ' ? (unsigned)strtoul(e + 1, NULL, 10) & 1u : 0u;
                    unsigned en1 = AMP1CON1bits.AMPEN, en2 = AMP2CON1bits.AMPEN;
                    AMP1CON1bits.AMPEN = 0; AMP1CON1bits.UGE = a1; AMP1CON1bits.AMPEN = en1;
                    AMP2CON1bits.AMPEN = 0; AMP2CON1bits.UGE = a2; AMP2CON1bits.AMPEN = en2;
                    char out[32]; snprintf(out, sizeof out, "UGE %u %u\n", (unsigned)AMP1CON1bits.UGE, (unsigned)AMP2CON1bits.UGE);
                    uart1_puts(out);
                } else if (!strncmp(line, "ACQCPU ", 7)) {
                    // ACQCPU <trg> [rptcnt [gap [phase]]]: CPU-loop capture (no DMA), same reply format as ACQ
                    char *e; unsigned trg = (unsigned)strtoul(line + 7, &e, 10); unsigned r = 1, gap = 0, phase = 0;
                    if (*e == ' ') { r = (unsigned)strtoul(e + 1, &e, 10); if (*e == ' ') { gap = (unsigned)strtoul(e + 1, &e, 10); if (*e == ' ') phase = (unsigned)strtoul(e + 1, NULL, 10); } }
                    rdy_low_settle();
                    uint32_t t = 0; acq_status_t st = acq_cpu_run(trg, r, gap, phase, &t);
                    char out[48]; snprintf(out, sizeof out, "ACQ %u %lu %u %s\n", (unsigned)ACQ_N, (unsigned long)t, (unsigned)ACQ_TICK_NS, st == ACQ_OK ? "ok" : "notready");
                    xfer_set_n(st == ACQ_OK ? ACQ_N : 0);
                    uart1_puts(out);
                } else if (!strncmp(line, "ACQIL", 5) && (line[5] == 0 || line[5] == ' ')) {
                    // ACQIL [div [off [navg]]]: two-channel interleaved integration capture (CH0 SCCP1, CH1 SCCP2
                    // offset by off counts, navg-sums each); same reply format as ACQ with n = ACQ_IL_N
                    unsigned off = 0, navg = 2;
                    if (line[5] == ' ') { char *e; acq_set_div((unsigned)strtoul(line + 6, &e, 10));
                        if (*e == ' ') { off = (unsigned)strtoul(e + 1, &e, 10); if (*e == ' ') navg = (unsigned)strtoul(e + 1, NULL, 10); } }
                    rdy_low_settle();
                    uint32_t t = 0; acq_status_t st = acq_il_run(off, navg, &t);
                    pe_env_invalidate();                // its DMA1 just overwrote the ENV running sum
                    const char *sname = st == ACQ_OK ? "ok" : st == ACQ_TIMEOUT ? "timeout" : st == ACQ_DMAERR ? "dmaerr" : st == ACQ_OVERRUN ? "overrun" : st == ACQ_SLOW ? "slow" : "notready";
                    char out[48]; snprintf(out, sizeof out, "ACQ %u %lu %u %s\n", (unsigned)ACQ_IL_N, (unsigned long)t, (unsigned)ACQ_TICK_NS, sname);
                    xfer_set_n(st == ACQ_OK ? ACQ_IL_N : 0);
                    uart1_puts(out);
                } else if (!strncmp(line, "ACQOS ", 6)) {
                    // ACQOS <4|16> [in]: one capture with hardware oversampling (MODE 11): 13 / 14-bit, 185 / 565 ns per sample
                    // (div raised to fit, restored after); reply = an ACQ header, payload pulled by SPIX / UTX
                    char *e; unsigned os = (unsigned)strtoul(line + 6, &e, 10);
                    if (*e == ' ') acq_set_input((unsigned)strtoul(e + 1, NULL, 10));
                    rdy_low_settle();
                    uint32_t t = 0; acq_status_t st = pe_os(os, &t);
                    const char *sname = st == ACQ_OK ? "ok" : st == ACQ_TIMEOUT ? "timeout" : st == ACQ_DMAERR ? "dmaerr" : st == ACQ_OVERRUN ? "overrun" : st == ACQ_SLOW ? "slow" : "notready";
                    char out[48]; snprintf(out, sizeof out, "ACQ %u %lu %u %s\n", (unsigned)ACQ_N, (unsigned long)t, (unsigned)ACQ_TICK_NS, sname);
                    xfer_set_n(st == ACQ_OK ? ACQ_N : 0);
                    uart1_puts(out);
                } else if (!strncmp(line, "TOF ", 4)) {
                    // TOF <thr> [blank [in [ref]]]: capture + first |x - ref| > thr at or after sample blank (comparator armed on
                    // [ref-thr, ref+thr], ref 0 = capture mean). Reply: TOF <idx|-1> <peak_idx> <peak> <ref> <hw> <ticks> <tick_ns> <status>
                    char *e; unsigned thr = (unsigned)strtoul(line + 4, &e, 10), blank = 0, ref = 0;
                    if (*e == ' ') { blank = (unsigned)strtoul(e + 1, &e, 10);
                        if (*e == ' ') { acq_set_input((unsigned)strtoul(e + 1, &e, 10)); if (*e == ' ') ref = (unsigned)strtoul(e + 1, NULL, 10); } }
                    rdy_low_settle();
                    tof_t r; acq_status_t st = pe_tof(thr, blank, ref, &r);
                    const char *sname = st == ACQ_OK ? "ok" : st == ACQ_SLOW ? "slow" : st == ACQ_TIMEOUT ? "timeout" : "err";
                    xfer_set_n(st == ACQ_OK ? ACQ_N : 0);   // the A-line stays pullable (SPIX / UTX) for checks
                    char out[96]; snprintf(out, sizeof out, "TOF %d %d %u %u %u %lu %u %s\n", r.idx, r.peak_idx, r.peak, r.ref, r.hw,
                                           (unsigned long)r.ticks, (unsigned)ACQ_TICK_NS, sname);
                    uart1_puts(out);
                } else if (!strncmp(line, "ENV ", 4)) {
                    // ENV <dec> [in [acc]]: capture + envelope (|x - mean| integrated over dec samples, 1/16 LSB), acc 1 = add to the
                    // running average of the previous shots. Reply: ENV <n> <dec> <shots> <ticks> <tick_ns> <status>; the average
                    // (n values) is pulled by SPIX / UTX
                    char *e; unsigned dec = (unsigned)strtoul(line + 4, &e, 10), acc = 0;
                    if (*e == ' ') { acq_set_input((unsigned)strtoul(e + 1, &e, 10)); if (*e == ' ') acc = (unsigned)strtoul(e + 1, NULL, 10); }
                    rdy_low_settle();
                    env_t r; acq_status_t st = pe_env(dec, acc, &r);
                    const char *sname = st == ACQ_OK ? "ok" : st == ACQ_SLOW ? "slow" : st == ACQ_TIMEOUT ? "timeout" : "err";
                    xfer_set_n(st == ACQ_OK ? r.n : 0);
                    char out[64]; snprintf(out, sizeof out, "ENV %u %u %u %lu %u %s\n", r.n, r.dec, r.shots, (unsigned long)r.ticks, (unsigned)ACQ_TICK_NS, sname);
                    uart1_puts(out);
                } else if (!strcmp(line, "SPIX")) {
                    // SPIX (proto 12): send the last capture (or XTEST pattern) as one SPI frame, announced on RDY (high = clock
                    // now, low = done); no UART reply except "SPIX 0" when nothing is pending. The RP falls back to UTX on failure.
                    rdy_low_settle();
                    (void)xfer_spix(uart1_puts, NULL);
                } else if (!strcmp(line, "UTX")) {
                    // UTX: the same payload over the UART (fallback / reference): "UTX <n>" then 2n bytes, u16 little-endian
                    unsigned n = xfer_get_n();
                    char out[24]; snprintf(out, sizeof out, "UTX %u\n", n);
                    uart1_puts(out);
                    for (unsigned i = 0; i < n; i++) { uart1_putc((char)(acq_buf[i] & 0xFF)); uart1_putc((char)(acq_buf[i] >> 8)); }
                } else if (!strncmp(line, "XTEST", 5) && (line[5] == 0 || line[5] == ' ')) {
                    // XTEST [seed]: fill acq_buf with the 16-bit Galois LFSR (0xB400) from seed (default 1) — link self-test
                    unsigned seed = line[5] == ' ' ? (unsigned)strtoul(line + 6, NULL, 0) & 0xFFFFu : 1u;
                    if (!seed) seed = 1;
                    xfer_xtest(seed);
                    char out[32]; snprintf(out, sizeof out, "XTEST %u %u\n", (unsigned)ACQ_N, seed);
                    uart1_puts(out);
                } else if (!strncmp(line, "DAC", 3) && (line[3] == 0 || line[3] == ' ' || line[3] == '?')) {
                    // DAC 0 | DAC 1 <code> | DAC 2 <lo> <hi> <slp> | DAC 3 <hz> [amp [mid]] | DAC?  (DACOUT1 = RA1 pin 3 = AD2AN3)
                    // reply: the state line (dac_describe) or "DAC ERR <why>"
                    int r = 0;
                    if (line[3] == ' ') {
                        char *e; unsigned m = (unsigned)strtoul(line + 4, &e, 10);
                        if (m == 0) r = dac_off();
                        else if (m == 1) r = *e == ' ' ? dac_dc((unsigned)strtoul(e + 1, NULL, 0)) : -1;
                        else if (m == 2) {
                            unsigned lo = 0, hi = 0, slp = 0;
                            if (*e == ' ') { lo = (unsigned)strtoul(e + 1, &e, 0); if (*e == ' ') { hi = (unsigned)strtoul(e + 1, &e, 0); if (*e == ' ') slp = (unsigned)strtoul(e + 1, NULL, 0); } }
                            r = dac_tri(lo, hi, slp);
                        } else if (m == 3) {
                            float hz = 0; unsigned amp = 1500, mid = 2048;
                            if (*e == ' ') { hz = strtof(e + 1, &e); if (*e == ' ') { amp = (unsigned)strtoul(e + 1, &e, 0); if (*e == ' ') mid = (unsigned)strtoul(e + 1, NULL, 0); } }
                            r = dac_sine(hz, amp, mid, NULL, NULL, NULL);
                        } else r = -1;
                    }
                    char out[64];
                    if (r == -1) uart1_puts("DAC ERR args\n");
                    else if (r == -2) uart1_puts("DAC ERR noclk\n");
                    else { dac_describe(out, sizeof out); uart1_puts(out); }
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
                } else if (!strcmp(line, "LOCK?") || !strcmp(line, "RELOCK")) {
                    // LOCK? = how the boot-time lock went; RELOCK = redo it now (re-runs acq_init: op amps / UGE back to boot state)
                    // reply "LOCK <locks tried> <slow captures of 8 in the last test>"
                    if (line[0] == 'R') lock_until_uniform();
                    char out[32]; snprintf(out, sizeof out, "LOCK %u %u\n", lock_tries, lock_slow);
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
