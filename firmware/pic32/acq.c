// minus devkit — PIC32AK "acq" capture engine, step 1 of the data path.
//
// Chain: SCCP1 16-bit time base (CLKGEN12 = 160 MHz, period ACQ_TRIG_DIV) --"SCCP1 Trigger out"
// (TRG1SRC 12)--> ADC1 channel 0 (PINSEL 9 = AD1AN9/RA9 by default, 0 = OA1OUT, 1 = OA1IN+; single sample) --channel
// 0 ready (DMA trigger 0x2B "ADC1 - AN0", channel-numbered)--> DMA0 copies AD1CH0DATA (16-bit) into
// acq_buf[ACQ_N], one-shot. Timer1 (FPB/8 = 100 ns) measures start -> DMA DONE so the RP can print
// the effective sample rate and detect dropped triggers (DMA throughput at 40 M/s is unspecified).
// Status: ok | timeout (DONE not reached in 5 ms) | dmaerr (address/bus fault) | overrun (dropped
// trigger = dropped samples, the anti-goal) | notready (ADC calibration never finished).
// All register/bitfield names from p32AK1216GC41048.h (DFP 1.1.53); sequences from DS70005592
// §18.5 (ADC examples), Example 16-1 (DMA one-shot), §27.4 (SCCP time base).
#include <xc.h>
#include "acq.h"

uint16_t acq_buf[ACQ_N] __attribute__((aligned(4)));
static unsigned acq_div = ACQ_TRIG_DIV;
static unsigned acq_input = ACQ_INPUT_NODE;   // ADC1 PINSEL: 9 = PIC32_ADC node (RA9), 0 = OA1OUT (RA2), 1 = OA1IN+ (RA4, RX node)
void     acq_set_input(unsigned pinsel) { acq_input = pinsel & 0xF; }
unsigned acq_get_input(void) { return acq_input; }
static unsigned acq_navg = 1;                 // 1 = single conversion per trigger; N>1 = integration mode, N back-to-back conversions summed
void     acq_set_navg(unsigned n) { if (n < 1) n = 1; if (n > 16) n = 16; acq_navg = n; }
unsigned acq_get_navg(void) { return acq_navg; }

// Sampling time (SAMC, 0.5 + n*2 TAD at 80 MHz TAD) chosen to fit the trigger period: conversion
// takes 1.5 TAD = 18.75 ns, so sample time <= period - 18.75 ns - margin. Longer sampling helps the
// bare ADC node (10k||10k bias, no FE buffer) charge the hold capacitor.
static unsigned samc_for_div(unsigned div) {
    unsigned period_ns = div * 25u / 4u;                  // div x 6.25 ns
    unsigned budget_ns = period_ns > 25u ? period_ns - 25u : 0;   // 18.75 ns conversion + ~6 ns margin
    unsigned samc = 0;
    while (samc < 7 && (625u + 2500u * (samc + 1)) / 100u <= budget_ns) samc++;   // 6.25 + 25*samc ns
    return samc;
}
void acq_set_div(unsigned div) { if (div < 4) div = 4; if (div > 255) div = 255; acq_div = div; }
static int acq_samc = 0;                  // default fixed 0 (6.25 ns) — deterministic; auto (-1) was found to skip triggers irregularly
void acq_set_samc(int samc) { acq_samc = samc < 0 ? -1 : (samc > 7 ? 7 : samc); }
int  acq_get_samc(void) { return acq_samc; }
unsigned acq_get_div(void) { return acq_div; }

void acq_init(void) {
    // Analog inputs (reset default is analog+input; make it explicit): RA9 = AD1AN9 (net PIC32_ADC),
    // RA2 = AD1AN0 = OA1OUT (pin 8), RA4 = AD1AN1 = OA1IN+ (pin 10, the RX node), RA3 = OA1IN- (pin 9).
    ANSELAbits.ANSELA9 = 1;  TRISAbits.TRISA9 = 1;
    ANSELAbits.ANSELA2 = 1;  TRISAbits.TRISA2 = 1;
    ANSELAbits.ANSELA4 = 1;  TRISAbits.TRISA4 = 1;
    ANSELAbits.ANSELA3 = 1;  TRISAbits.TRISA3 = 1;

    // Op amp 1 (DS70005592 ch. 32): the board wires it as a non-inverting x11 stage on the RX node
    // (OA1IN+ = RX node, R47 1k OA1IN- to GND, R48 10k OA1OUT to OA1IN-), DC-coupled to GND so only the
    // positive half of an echo comes out (TODO_HARDWARE). High-power mode = 100 MHz GBW; external
    // gain (UGE 0); OMONEN 0 — OA1OUT is a real pin here and is read as AD1AN0 directly. "AMP1 0|1"
    // on the link toggles it.
    AMP1CON1 = 0;
    AMP1CON1bits.UGE   = 0;
    AMP1CON1bits.HPEN  = 1;
    AMP1CON1bits.AMPEN = 1;

    // ADC1 core on (CLKGEN6 = 320 MHz must be running); startup calibration ~5000 ADC clocks.
    // Bounded wait: if the ADC never comes up the link must still work and ACQ reports "notready".
    AD1CONbits.RPTCNT = 1;              // repeat timer: 2 ADC clocks = 25 ns (set before ON; used by the ACQCPU trg 3 experiment)
    AD1CONbits.ON = 1;
    for (uint32_t i = 0; i < ACQ_ADRDY_SPINS && AD1CONbits.ADRDY == 0; i++) ;

    // Channel 0: AN9, single-ended, unsigned right-aligned, one conversion per trigger,
    // sampling 0.5 TAD (6.25 ns) — the node is driven through 100 R / 56 pF, see pcb-brief.
    AD1CH0CON = 0;
    AD1CH0CONbits.PINSEL  = ACQ_INPUT_NODE;
    AD1CH0CONbits.MODE    = 0;          // single sample initiated by TRG1SRC
    AD1CH0CONbits.SAMC    = 0;          // 0.5 TAD
    AD1CH0CONbits.DIFF    = 0;
    AD1CH0CONbits.TRG1SRC = 12;         // 01100 = SCCP1 Trigger out (Table 18-3)

    // SCCP1 in 32-bit Timer mode (DS70005592 §27.4.2.2, same as the ADC Example 18-10): a
    // CCP1TMR == CCP1PR match raises the Special Event Trigger (= "SCCP1 Trigger out", ADC
    // TRG1SRC 12) and the Sync output, and resets the timer. (Dual 16-bit mode would need CCP1RB
    // for the trigger instead.) Clock = CLKGEN12 160 MHz. Left OFF until a capture.
    CCP1CON1 = 0;
    CCP1CON1bits.CCSEL  = 0;            // time base / output compare block
    CCP1CON1bits.T32    = 1;            // single 32-bit timer
    CCP1CON1bits.MOD    = 0;            // timer mode, no output functions
    CCP1CON1bits.CLKSEL = 1;            // 001 = CLKGEN12 (Table 27-2)
    CCP1CON1bits.TMRPS  = 0;            // 1:1
    CCP1CON1bits.SYNC   = 0;            // self-synchronised: period set by CCP1PR
    CCP1PR  = ACQ_TRIG_DIV - 1u;        // match at PR, reset -> period = PR + 1 counts (if the bench shows
                                        // 32 MHz instead of 40, the period is PR + 2: use ACQ_TRIG_DIV - 2)
    CCP1TMR = 0;

    // Timer1: FPB / 8 = 10 MHz -> 100 ns per tick, free-running to 0xFFFF (6.55 ms)
    T1CON = 0;
    T1CONbits.TCS   = 0;                // standard speed peripheral clock
    T1CONbits.TCKPS = 1;                // 01 = 1:8 (T1CON[5:4])
    PR1  = 0xFFFF;
    TMR1 = 0;

    // DMA module: on, RAM window 0x4000-0x7FFF (16 KB), channel 0 triggered by ADC1 channel 0
    DMACONbits.ON = 1;
    DMALOW  = 0x4000;
    DMAHIGH = 0x7FFF;
    DMA0SELbits.CHSEL = 0x2B;           // Table 16-2: 0x2B "ADC1 - AN0" (channel 0); try 0x34 if silent
}

acq_status_t acq_run(uint32_t *ticks) {
    if (AD1CONbits.ADRDY == 0) { if (ticks) *ticks = 0; return ACQ_NOTREADY; }
    CCP1PR = acq_div - 1u;                                // trigger period (see acq_set_div)
    AD1CH0CONbits.PINSEL = acq_input;                     // input (see acq_set_input)
    // navg > 1: integration mode (DS70005592 §18.4.5 / Example 18-6): the SCCP trigger starts the first
    // conversion, TRG2SRC 2 (back-to-back) re-triggers immediately for the rest, the sum of navg results
    // lands in AD1CH0DATA (12 + log2(navg) bits) and raises the channel-ready DMA request once. Each
    // conversion is 1.5 TAD + sampling (0.5 TAD at SAMC 0) = 25 ns, i.e. the ADC core runs at 40 Msps
    // while the DMA only has to move one word per trigger (20 Msps max at div 8).
    if (acq_navg > 1) { AD1CH0CONbits.MODE = 2; AD1CH0CONbits.TRG2SRC = 2; AD1CH0CNT = acq_navg; AD1CH0CONbits.ACCRO = 0; }
    else              { AD1CH0CONbits.MODE = 0; AD1CH0CONbits.TRG2SRC = 0; }
    AD1CH0CONbits.SAMC = acq_samc < 0 ? samc_for_div(acq_div) : (unsigned)acq_samc;

    // DMA0: one-shot, 16-bit, fixed source (AD1CH0DATA), incrementing destination (acq_buf).
    // Clear every status flag (DONE, HALF, OVERRUN, ADRERR, BRERR, BWERR are write-0-to-clear) so a
    // previous fault cannot stick to this run.
    IFS2bits.DMA0IF = 0;
    DMA0CH = 0;
    DMA0STAT = 0;
    DMA0SRC = (uint32_t)&AD1CH0DATA;
    DMA0DST = (uint32_t)acq_buf;
    DMA0CNT = ACQ_N;
    DMA0CHbits.SIZE   = 1;              // 16-bit transfers
    DMA0CHbits.SAMODE = 0;              // source fixed
    DMA0CHbits.DAMODE = 1;              // destination increments
    DMA0CHbits.TRMODE = 0;              // one-shot: CHEN clears when CNT reaches 0
    DMA0CHbits.CHEN   = 1;

    (void)AD1CH0DATA;                   // clear any stale channel-ready flag before arming the trigger
    CCP1TMR = 0;
    TMR1 = 0;
    LATAbits.LATA7 = 1;                 // RDY high = capture window (RP times it with its own clock)
    T1CONbits.ON = 1;
    CCP1CON1bits.ON = 1;                // triggers start: one conversion every acq_div CLKGEN12 clocks

    // Bus-quiet wait: the CPU has priority over the DMA on the SFR bus (DS70005592 §16.2), so a tight
    // poll of DMA0STAT/TMR1 stalls the transfers (measured: 23-27 Msps floor at a 40 MHz trigger).
    // Poll DMA0STAT only every ~64 cycles and count iterations instead of reading Timer1.
    for (uint32_t spins = 0; DMA0STATbits.DONE == 0 && spins < ACQ_DEADLINE_SPINS; spins++)
        for (int k = 0; k < ACQ_POLL_NOPS; k++) __builtin_nop();

    uint32_t t = TMR1;
    LATAbits.LATA7 = 0;                 // RDY low = capture done (or deadline)
    CCP1CON1bits.ON = 0;                // stop triggers
    T1CONbits.ON = 0;
    acq_status_t st = ACQ_OK;
    if (DMA0STATbits.ADRERR != 0 || DMA0STATbits.BRERR || DMA0STATbits.BWERR) st = ACQ_DMAERR;   // faults stop the channel before DONE
    else if (DMA0STATbits.DONE == 0) st = ACQ_TIMEOUT;
    else if (DMA0STATbits.OVERRUN) st = ACQ_OVERRUN;   // a trigger arrived while the previous transfer was still running: samples dropped
    DMA0CHbits.CHEN = 0;
    if (ticks) *ticks = t;
    return st;
}

// ADC-core throughput test without DMA (link command "ADCBB n [ovs]"): one software trigger starts n
// back-to-back conversions on channel 0 (integration mode; ovs = oversampling burst mode, n rounded to
// 4/16/64/256) and Timer1 (100 ns ticks) times trigger -> channel ready. Answers "how fast is one
// channel really" independently of the DMA. Restores the SCCP-triggered single-sample setup afterwards.
uint32_t acq_adc_bb(unsigned n, unsigned ovs, uint32_t *data) {
    AD1CH0CONbits.PINSEL = acq_input;
    AD1CH0CONbits.SAMC   = acq_samc < 0 ? 0 : (unsigned)acq_samc;
    if (ovs) { AD1CH0CONbits.MODE = 3; AD1CH0CONbits.ACCNUM = n >= 256 ? 3 : n >= 64 ? 2 : n >= 16 ? 1 : 0; AD1CH0CONbits.ACCBRST = 1; }
    else     { AD1CH0CONbits.MODE = 2; AD1CH0CNT = n; }
    AD1CH0CONbits.TRG2SRC = 2;          // back-to-back re-trigger
    AD1CH0CONbits.TRG1SRC = 1;          // software start
    (void)AD1CH0DATA;                   // clear a stale ready flag
    TMR1 = 0; T1CONbits.ON = 1;
    AD1SWTRGbits.CH0TRG = 1;
    for (uint32_t spins = 0; AD1STATbits.CH0RDY == 0 && spins < 100000u; spins++)
        for (int k = 0; k < 16; k++) __builtin_nop();     // ~0.2 us poll granularity
    uint32_t t = TMR1; T1CONbits.ON = 0;
    if (data) *data = AD1CH0DATA;
    AD1CH0CONbits.MODE = 0; AD1CH0CONbits.ACCBRST = 0; AD1CH0CONbits.TRG2SRC = 0; AD1CH0CONbits.TRG1SRC = 12;
    return t;
}

// CPU-loop reader (link command "ACQCPU r"): no DMA. Channel 0 in single-sample mode, triggered by the
// ADC's own repeat timer (TRG1SRC 3, period = (r+1) ADC clocks of 12.5 ns: r=1 -> 25 ns = 40 Msps,
// r=3 -> 50 ns = 20 Msps). The CPU copies AD1CH0DATA into acq_buf in a tight loop without checking the
// ready flag: CPU (160 MHz) and ADC clock (320 MHz) come from the same PLL, so a 4-cycle loop is
// phase-locked to a 25 ns conversion period. Timer1 times the loop so the RP can print cycles/sample.
// trg 2 = back-to-back (conversion period = 1.5 TAD + sampling = 25 ns at SAMC 0, 50 ns at SAMC 1, +25 ns
// per SAMC step), trg 3 = repeat timer (bench 2026-10-28: produced no conversions, DATA stayed stale).
acq_status_t acq_cpu_run(unsigned trg, unsigned rptcnt, unsigned gap, unsigned phase, uint32_t *ticks) {
    if (AD1CONbits.ADRDY == 0) { if (ticks) *ticks = 0; return ACQ_NOTREADY; }
    AD1CH0CONbits.PINSEL  = acq_input;
    AD1CH0CONbits.SAMC    = acq_samc < 0 ? 0 : (unsigned)acq_samc;
    AD1CH0CONbits.MODE    = 0;
    AD1CH0CONbits.TRG2SRC = 0;
    if (rptcnt != 1) AD1CONbits.RPTCNT = rptcnt & 0x3F;   // may be ignored while ON = 1 (datasheet note 3); 1 is set at init
    // Back-to-back (trg 2) chains from a finished conversion: kick the core with one software-triggered
    // conversion on channel 1 (same input) right after arming channel 0.
    AD1CH1CON = 0; AD1CH1CONbits.PINSEL = acq_input; AD1CH1CONbits.TRG1SRC = 1;
    volatile uint32_t *src = &AD1CH0DATA;
    uint16_t *dst = acq_buf;
    LATAbits.LATA7 = 1;
    TMR1 = 0; T1CONbits.ON = 1;
    AD1CH0CONbits.TRG1SRC = trg & 0x1F; // conversions start now (2 = back-to-back, 3 = repeat timer, 12 = SCCP1)
    if (trg == 12) { CCP1PR = acq_div - 1u; CCP1TMR = 0; CCP1CON1bits.ON = 1; }
    if (trg == 2) AD1SWTRGbits.CH1TRG = 1;
    // phase = NOPs between the trigger start and the first read: moves the 4-cycle read instant relative to
    // the ADC's result write. CPU reads win the bus (DS70005592 §16.2) and a colliding ADC write is lost, so
    // the wrong phase returns every result twice (bench 2026-10-28: the same code gave pairs or clean
    // 25 ns samples depending on build alignment).
    for (unsigned k = 0; k < phase; k++) __builtin_nop();
    // gap = extra NOPs per read (0 = 4 cycles/read = 25 ns; 4 -> 8 cycles = 50 ns; 12 -> 16 cycles = 100 ns)
    switch (gap) {
    case 0:  for (unsigned i = 0; i < ACQ_N; i++) dst[i] = (uint16_t)*src; break;
    case 4:  for (unsigned i = 0; i < ACQ_N; i++) { dst[i] = (uint16_t)*src; __builtin_nop(); __builtin_nop(); __builtin_nop(); __builtin_nop(); } break;
    default: for (unsigned i = 0; i < ACQ_N; i++) { dst[i] = (uint16_t)*src; for (unsigned k = 0; k < gap; k++) __builtin_nop(); } break;
    }
    uint32_t t = TMR1; T1CONbits.ON = 0;
    CCP1CON1bits.ON = 0;
    AD1CH0CONbits.TRG1SRC = 12;         // back to the SCCP1 trigger
    AD1CH1CONbits.TRG1SRC = 0;
    LATAbits.LATA7 = 0;
    (void)AD1CH0DATA; (void)AD1CH1DATA;
    if (ticks) *ticks = t;
    return ACQ_OK;
}
