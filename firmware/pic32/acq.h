// minus devkit — PIC32AK "acq": one 4095-sample capture of ADC1 input AN9 (the common ADC node,
// schematic net PIC32_ADC, pin 5 / RA9) at a nominal 40 Msps, into RAM, via DMA.
// Design: docs/claude/specs/2026-10-27-acq-design.md
#ifndef ACQ_H
#define ACQ_H
#include <stdint.h>

#define ACQ_N        4095u
#define ACQ_TRIG_DIV 4u              // SCCP1 time base on CLKGEN12 160 MHz / 4 = 40 MHz trigger; 8 -> 20 Msps
#define ACQ_TICK_NS  100u            // Timer1 tick: FPB 80 MHz / prescaler 8 = 100 ns (6.5 ms range)
#define ACQ_DEADLINE_TICKS 50000u    // 5 ms DMA deadline, in Timer1 ticks (expected fill ~ 1024 ticks)

typedef enum { ACQ_OK = 0, ACQ_TIMEOUT, ACQ_DMAERR, ACQ_OVERRUN, ACQ_NOTREADY } acq_status_t;
#define ACQ_ADRDY_SPINS 2000000u     // bounded wait for the ADC calibration (~5000 ADC clocks = 16 us; this is >> that)

void         acq_init(void);               // ADC1 on + ready, CH0 config, SCCP1/Timer1/DMA set up; once, after clocks_init()
acq_status_t acq_run(uint32_t *ticks);     // one capture into acq_buf; *ticks = Timer1 count at DMA DONE (or deadline)
extern uint16_t acq_buf[ACQ_N];            // unsigned 12-bit right-aligned samples

#endif
