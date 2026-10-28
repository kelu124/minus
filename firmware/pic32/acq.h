// minus devkit — PIC32AK "acq": one 4095-sample capture of an ADC1 input (default AN9 = the common
// ADC node, net PIC32_ADC, pin 5 / RA9; or AN0 = OA1OUT, AN1 = OA1IN+) at up to 20 Msps (DMA
// ceiling, 50 ns per transfer; the ADC itself converts at 40 Msps), into RAM, via DMA. acq_il_run =
// two channels interleaved, 20 M 2-sums/s (memory 0011).
// Design: docs/claude/specs/2026-10-27-acq-design.md
#ifndef ACQ_H
#define ACQ_H
#include <stdint.h>

#define ACQ_N        4095u
#define ACQ_IL_HALF  2047u           // acq_il_run: samples per channel (two channels interleaved -> ACQ_IL_N values)
#define ACQ_IL_N     (2u * ACQ_IL_HALF)
#define ACQ_INPUT_NODE 9u            // ADC1 PINSEL of the common ADC node (AD1AN9 / RA9); 0 = OA1OUT (AD1AN0), 1 = OA1IN+ (AD1AN1)
#define ACQ_TRIG_DIV 8u              // SCCP1 time base on CLKGEN12 160 MHz / 8 = 20 MHz trigger = the DMA ceiling (4 = 40 MHz: half the triggers are lost by the DMA; use acqcpu for 40 Msps)
#define ACQ_TICK_NS  100u            // Timer1 tick: FPB 80 MHz / prescaler 8 = 100 ns (6.5 ms range)
#define ACQ_DEADLINE_TICKS 50000u    // 5 ms DMA deadline, in Timer1 ticks (expected fill ~ 1024 ticks)
#define ACQ_POLL_NOPS      1024      // NOPs between two DMA0STAT polls: each CPU SFR access stalls the DMA (~one lost trigger)
#define ACQ_DEADLINE_SPINS 800u      // deadline in wait-loop iterations (~13 us each) ~ 10 ms

typedef enum { ACQ_OK = 0, ACQ_TIMEOUT, ACQ_DMAERR, ACQ_OVERRUN, ACQ_NOTREADY } acq_status_t;
#define ACQ_ADRDY_SPINS 2000000u     // bounded wait for the ADC calibration (~5000 ADC clocks = 16 us; this is >> that)

void         acq_init(void);               // ADC1 on + ready, CH0 config, SCCP1/Timer1/DMA set up; once, after clocks_init()
acq_status_t acq_run(uint32_t *ticks);     // one capture into acq_buf; *ticks = Timer1 count at DMA DONE (or deadline)
void         acq_set_div(unsigned div);    // trigger period in CLKGEN12 clocks (4 = 40 Msps, 6 = 26.7, 8 = 20, 16 = 10); clamps 4..255
unsigned     acq_get_div(void);
void         acq_set_samc(int samc);       // -1 = auto (fit the trigger period), 0..7 = fixed SAMC (0.5 + 2n TAD)
int          acq_get_samc(void);
void         acq_set_input(unsigned pinsel); // ADC1 positive input (PINSEL 0..15): 9 node, 0 OA1OUT, 1 OA1IN+
unsigned     acq_get_input(void);
void         acq_set_navg(unsigned n);     // 1 = one conversion per trigger; 2..16 = sum of n back-to-back conversions per trigger (ADC at 40 Msps)
unsigned     acq_get_navg(void);
acq_status_t acq_cpu_run(unsigned trg, unsigned rptcnt, unsigned gap, unsigned phase, uint32_t *ticks);   // CPU-loop reader: trg 2 back-to-back (rate by SAMC), 3 repeat timer (r+1)*12.5 ns
acq_status_t acq_il_run(unsigned off, unsigned navg, uint32_t *ticks);   // two-channel interleave: CH0 on SCCP1, CH1 on SCCP2 offset by off counts (0 = div/2+1), navg-sums each; result in acq_buf[ACQ_IL_N]
uint32_t     acq_adc_bb(unsigned n, unsigned ovs, uint32_t *data);   // DMA-free ADC throughput test: Timer1 ticks for n back-to-back conversions
extern uint16_t acq_buf[ACQ_N];            // unsigned 12-bit right-aligned samples

#endif
