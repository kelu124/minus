// minus — pulse-echo functions built on the ADC extras (pic 1.1.3). See pe_ext.h and
// docs/claude/specs/2026-11-22-adc-extras-design.md. All run one capture through acq_run (RDY rises at the start, so the
// RP's pulser fires on it exactly as for "pe").
#include <xc.h>
#include <string.h>
#include "pe_ext.h"

static unsigned buf_mean(void) {
    uint32_t s = 0;
    for (unsigned i = 0; i < ACQ_N; i++) s += acq_buf[i];
    return (unsigned)((s + ACQ_N / 2u) / ACQ_N);
}

acq_saved_t pe_std_begin(void) {
    acq_saved_t s = { acq_get_div(), acq_get_navg(), acq_get_samc() };
    acq_set_div(4); acq_set_samc(0); acq_set_navg(1);
    return s;
}
void pe_std_end(acq_saved_t s) { acq_set_div(s.div); acq_set_samc(s.samc); acq_set_navg(s.navg); }

// Oversampling: N back-to-back 32 ns conversions + ~40 ns sequence overhead per trigger -> the trigger period must be at
// least N*32 + 48 ns, plus margin: div = (N*32 + 52) / 5 + 1 -> 4: 37 (185 ns, 5.4 Msps, 13-bit); 16: 113 (565 ns,
// 1.77 Msps, 14-bit) — measured 186.0 / 565.4 ns. (pic 1.1.3 used 36 / 112: zero margin at 16, review 2026-11-22.)
acq_status_t pe_os(unsigned os, uint32_t *ticks) {
    if (os != 4u && os != 16u) return ACQ_NOTREADY;
    acq_saved_t s = pe_std_begin();
    acq_set_div((os * 32u + 48u + 4u) / 5u + 1u);
    acq_set_os(os);
    acq_status_t st = acq_run(ticks);
    acq_set_os(0);
    pe_std_end(s);
    return st;
}

acq_status_t pe_tof(unsigned thr, unsigned blank, unsigned ref_in, tof_t *r) {
    unsigned ref = ref_in ? ref_in : 2048u;               // the hardware comparator needs its bounds before the capture
    unsigned lo = ref > thr ? ref - thr : 0u, hi = ref + thr > 4095u ? 4095u : ref + thr;
    r->idx = -1; r->peak_idx = -1; r->peak = 0; r->ref = ref; r->hw = 0; r->ticks = 0;
    acq_saved_t sv = pe_std_begin();                      // 12-bit samples at 40 ns, whatever the last ACQ set
    acq_set_cmp(1u, lo, hi);                              // CMPMOD 001: result out of [lo, hi]
    acq_status_t st = acq_run(&r->ticks);
    r->hw = acq_cmp_flag();
    acq_set_cmp(0u, 0u, 0u);
    pe_std_end(sv);
    if (st != ACQ_OK) return st;
    if (!ref_in) r->ref = ref = buf_mean();
    for (unsigned i = blank; i < ACQ_N; i++) {
        int d = (int)acq_buf[i] - (int)ref; if (d < 0) d = -d;
        if ((unsigned)d > thr) { r->idx = (int)i; break; }
    }
    if (r->idx >= 0) {
        unsigned end = (unsigned)r->idx + TOF_PEAK_WIN; if (end > ACQ_N) end = ACQ_N;
        for (unsigned i = (unsigned)r->idx; i < end; i++) {
            int d = (int)acq_buf[i] - (int)ref; if (d < 0) d = -d;
            if ((unsigned)d > r->peak) { r->peak = (unsigned)d; r->peak_idx = (int)i; }
        }
    }
    return st;
}

static unsigned env_shots, env_dec_cur;
void pe_env_invalidate(void) { env_dec_cur = 0; env_shots = 0; }
acq_status_t pe_env(unsigned dec, unsigned acc, env_t *r) {
    r->n = 0; r->dec = dec; r->shots = env_shots; r->ticks = 0;
    if (dec < ENV_DEC_MIN || dec > ENV_DEC_MAX) return ACQ_NOTREADY;
    acq_saved_t sv = pe_std_begin();
    acq_status_t st = acq_run(&r->ticks);
    pe_std_end(sv);
    r->dec = dec; r->n = ACQ_N / dec; r->shots = env_shots;
    if (st != ACQ_OK) return st;
    unsigned words; uint32_t *sum = acq_scratch32(&words);
    if (r->n > words) return ACQ_NOTREADY;
    if (!acc || dec != env_dec_cur) { memset(sum, 0, r->n * 4u); env_shots = 0; env_dec_cur = dec; }
    unsigned m = buf_mean();
    for (unsigned k = 0; k < r->n; k++) {                  // integrate-and-dump of |x - mean| over dec samples, 1/16 LSB
        uint32_t s = 0; const uint16_t *x = acq_buf + k * dec;
        for (unsigned j = 0; j < dec; j++) { int d = (int)x[j] - (int)m; s += (uint32_t)(d < 0 ? -d : d); }
        sum[k] += (s * 16u + dec / 2u) / dec;
    }
    env_shots++;
    for (unsigned k = 0; k < r->n; k++) {                  // running average back into acq_buf for SPIX / UTX
        uint32_t v = (sum[k] + env_shots / 2u) / env_shots;
        acq_buf[k] = (uint16_t)(v > 65535u ? 65535u : v);
    }
    r->shots = env_shots;
    return st;
}
