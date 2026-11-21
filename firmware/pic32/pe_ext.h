// minus — pulse-echo functions built on the ADC extras (pic 1.1.3). Design: docs/claude/specs/2026-11-22-adc-extras-design.md
#ifndef PE_EXT_H
#define PE_EXT_H
#include <stdint.h>
#include "acq.h"

#define TOF_PEAK_WIN 64u               // samples searched for the peak after the first crossing
#define ENV_DEC_MIN  4u                // 4095/4 = 1023 values = the u32 scratch size
#define ENV_DEC_MAX  64u

typedef struct { int idx, peak_idx; unsigned peak, ref, hw; uint32_t ticks; } tof_t;
typedef struct { unsigned n, dec, shots; uint32_t ticks; } env_t;

// standard capture settings (div 4 = 25 Msps, samc 0, navg 1) around a capture, the user's restored after (review 2026-11-22)
typedef struct { unsigned div, navg; int samc; } acq_saved_t;
acq_saved_t  pe_std_begin(void);
void         pe_std_end(acq_saved_t s);
void         pe_env_invalidate(void);  // the ENV running sum lives in the ACQIL buffer: call after ACQIL overwrites it
acq_status_t pe_os(unsigned os, uint32_t *ticks);                       // one capture with oversampling 4 / 16 (div raised to fit)
acq_status_t pe_tof(unsigned thr, unsigned blank, unsigned ref, tof_t *r);   // ref 0 = capture mean (comparator uses 2048)
acq_status_t pe_env(unsigned dec, unsigned acc, env_t *r);              // envelope into acq_buf[0..n) (1/16 LSB), running average
#endif
