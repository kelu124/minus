// minus devkit — PIC32AK "acq": one 4095-sample capture of an ADC1 input (default AN9 = the common
// ADC node, net PIC32_ADC, pin 5 / RA9; or AN0 = OA1OUT, AN1 = OA1IN+) at up to 25 Msps (DMA
// ceiling at CPU 200 MHz: 4 standard-bus clocks = 40 ns per transfer; the ADC core converts every 32 ns
// with its 250 MHz clock), into RAM, via DMA. acq_il_run = two channels interleaved (memory 0011).
// Until fw 0.1.19 (CPU 160 / ADC 320 MHz): 20 Msps DMA ceiling, 25 ns conversions, 6.25 ns SCCP ticks.
// Design: docs/claude/specs/2026-10-27-acq-design.md
#ifndef ACQ_H
#define ACQ_H
#include <stdint.h>

#define ACQ_N        4095u
#define ACQ_IL_HALF  2047u           // acq_il_run: samples per channel (two channels interleaved -> ACQ_IL_N values)
#define ACQ_IL_N     (2u * ACQ_IL_HALF)
#define ACQ_INPUT_NODE 9u            // ADC1 PINSEL of the common ADC node (AD1AN9 / RA9); 0 = OA1OUT (AD1AN0), 1 = OA1IN+ (AD1AN1)
#define ACQ_TRIG_DIV 4u              // SCCP1 time base on CLKGEN12 200 MHz / 4 = 20 ns triggers: the ADC (32 ns) takes every other one -> a uniform 40 ns = 25 Msps comb that the DMA (40 ns per transfer) just sustains. Bench 2026-11-02: div 8 (40 ns triggers) sits on the DMA edge and drops ~1 in 4 (fill 226 us), div 5/6 jitter, div 10 = clean 20 Msps
#define ACQ_TICK_NS  80u             // Timer1 tick: FPB 100 MHz / prescaler 8 = 80 ns (5.2 ms range); sent to the RP in every ACQ header
#define ACQ_DEADLINE_TICKS 50000u    // 4 ms DMA deadline, in Timer1 ticks (expected fill ~ 2048 ticks at div 8)
#define ACQ_POLL_NOPS      1024      // NOPs between two DMA0STAT polls: each CPU SFR access stalls the DMA (~one lost trigger)
#define ACQ_DEADLINE_SPINS 800u      // deadline in wait-loop iterations (~13 us each) ~ 10 ms

typedef enum { ACQ_OK = 0, ACQ_TIMEOUT, ACQ_DMAERR, ACQ_OVERRUN, ACQ_NOTREADY } acq_status_t;
#define ACQ_ADRDY_SPINS 2000000u     // bounded wait for the ADC calibration (~5000 ADC clocks = 16 us; this is >> that)

void         acq_init(void);               // ADC1 on + ready, CH0 config, SCCP1/Timer1/DMA set up; once, after clocks_init()
acq_status_t acq_run(uint32_t *ticks);     // one capture into acq_buf; *ticks = Timer1 count at DMA DONE (or deadline)
void         acq_set_div(unsigned div);    // trigger period in CLKGEN12 clocks of 5 ns (4 = 25 Msps default, 10 = 20, 20 = 10; 5..9 irregular); clamps 4..255
unsigned     acq_get_div(void);
void         acq_set_samc(int samc);       // -1 = auto (fit the trigger period), 0..7 = fixed SAMC (0.5 + 2n TAD)
int          acq_get_samc(void);
void         acq_set_input(unsigned pinsel); // ADC1 positive input (PINSEL 0..15): 9 node, 0 OA1OUT, 1 OA1IN+
unsigned     acq_get_input(void);
void         acq_set_navg(unsigned n);     // 1 = one conversion per trigger; 2..16 = sum of n back-to-back conversions per trigger (ADC core at 31.25 Msps, 32 ns each)
unsigned     acq_get_navg(void);
acq_status_t acq_cpu_run(unsigned trg, unsigned rptcnt, unsigned gap, unsigned phase, uint32_t *ticks);   // CPU-loop reader: trg 2 back-to-back (rate by SAMC), 3 repeat timer (r+1)*12.5 ns
acq_status_t acq_il_run(unsigned off, unsigned navg, uint32_t *ticks);   // two-channel interleave: CH0 on SCCP1, CH1 on SCCP2 offset by off counts (0 = div/2+1), navg-sums each; result in acq_buf[ACQ_IL_N]
uint32_t     acq_adc_bb(unsigned n, unsigned ovs, uint32_t *data);   // DMA-free ADC throughput test: Timer1 ticks for n back-to-back conversions
extern uint16_t acq_buf[ACQ_N];            // unsigned 12-bit right-aligned samples

#endif
