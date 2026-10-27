// minus devkit — PIC32AK "acq" capture engine, step 1 of the data path.
//
// Chain: SCCP1 16-bit time base (CLKGEN12 = 160 MHz, period ACQ_TRIG_DIV) --"SCCP1 Trigger out"
// (TRG1SRC 12)--> ADC1 channel 0 (PINSEL 9 = AD1AN9/RA9, single sample, 0.5 TAD sampling) --channel
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
    // Analog input: RA9 = AD1AN9 (reset default is analog+input; make it explicit)
    ANSELAbits.ANSELA9 = 1;
    TRISAbits.TRISA9 = 1;

    // ADC1 core on (CLKGEN6 = 320 MHz must be running); startup calibration ~5000 ADC clocks.
    // Bounded wait: if the ADC never comes up the link must still work and ACQ reports "notready".
    AD1CONbits.ON = 1;
    for (uint32_t i = 0; i < ACQ_ADRDY_SPINS && AD1CONbits.ADRDY == 0; i++) ;

    // Channel 0: AN9, single-ended, unsigned right-aligned, one conversion per trigger,
    // sampling 0.5 TAD (6.25 ns) — the node is driven through 100 R / 56 pF, see pcb-brief.
    AD1CH0CON = 0;
    AD1CH0CONbits.PINSEL  = 9;
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

    while (DMA0STATbits.DONE == 0 && TMR1 < ACQ_DEADLINE_TICKS) ;

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
