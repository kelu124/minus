// minus — PIC32AK DAC1 test signal on DACOUT1. See dac.h and docs/claude/specs/2026-11-21-dac-spi-link-design.md.
//
// DAC1 is a pulse-density DAC + RC filter (DS70005592 §19.4.2): 12-bit, usable codes 0x0CD..0xF32 (5-95 % AVDD),
// settling 0.75 us typ / 2 us max (DA07). Its clock CLKGEN7 comes from PLL2 (8 MHz FRC x 125 = 1000 MHz VCO,
// VCO-div output /2 = 500 MHz, as in the datasheet examples), so PLL1 (CPU 200 MHz / ADC 250 MHz) is untouched.
// Started lazily on the first DAC command, so a clock problem never blocks boot.
//   dc   : DAC1DAT.DACDAT = code.
//   tri  : hardware Triangle Wave mode (DAC1SLPCON.TWME + SLOPEN) between DACLOW and DACDAT, slope SLPDAT (12.4 format,
//          per T_DAC = 2/F_DAC = 4 ns): no bus traffic, safe during any capture. Half period = (hi-lo)*16/slp * 4 ns.
//   sine : DMA2 copies a <= 128-point table (32-bit words, DACDAT in bits 27:16) into DAC1DAT on every SCCP3 secondary
//          16-bit timer match (CCP3IF = DMA trigger 0x1A; dual 16-bit timer mode, §SCCP: "secondary time base ...
//          generates CCPxIF"), update period >= 1 us. One extra DMA transfer per update shares the bus with the capture
//          DMA (memory 0011): measure before trusting a 25 Msps capture with the sine running.
#include <xc.h>
#include <math.h>
#include <stdio.h>
#include "dac.h"

#define FPDMDAC_ADDR 0x7F20B0u   // factory DAC calibration word (§19.4.4 / Table 19-7)
#define PLL_SPINS    2000000u

static int clk_state = 0;        // 0 = not tried, 1 = ok, -1 = failed
static dac_mode_t mode = DAC_OFF;
static unsigned cur_lo, cur_hi, cur_slp, cur_npts, cur_upd, cur_amp, cur_mid;
static float cur_hz;
static uint32_t sine_tab[DAC_SINE_MAX] __attribute__((aligned(4)));

static int wait_clear(volatile uint32_t *reg, uint32_t mask) { uint32_t g = PLL_SPINS; while ((*reg & mask) && --g) ; return g != 0; }

static int dac_clock_init(void) {
    if (clk_state) return clk_state;
    uint32_t g;
    PLL2CONbits.ON = 1;
    OSCCTRLbits.PLL2EN = 1;
    g = PLL_SPINS; while (OSCCTRLbits.PLL2RDY == 0 && --g) ;
    if (!g) return clk_state = -1;
    PLL2CONbits.FSCMEN = 0;
    VCO2DIVbits.INTDIV = 1;                 // VCO-div output = 1000 / (2*1) = 500 MHz -> CLKGEN7
    PLL2DIVbits.PLLFBDIV = 125;             // 8 MHz * 125 = 1000 MHz (OS51: 500-1600 MHz)
    PLL2DIVbits.PLLPRE = 1;
    PLL2DIVbits.POSTDIV1 = 5;               // Fout 200 MHz (unused)
    PLL2DIVbits.POSTDIV2 = 1;
    PLL2CONbits.DIVSWEN = 1;  if (!wait_clear(&PLL2CON, _PLL2CON_DIVSWEN_MASK)) return clk_state = -1;
    PLL2CONbits.NOSC = 1;                   // PLL2 input = FRC
    PLL2CONbits.OSWEN = 1;    if (!wait_clear(&PLL2CON, _PLL2CON_OSWEN_MASK)) return clk_state = -1;
    PLL2CONbits.FOUTSWEN = 1; if (!wait_clear(&PLL2CON, _PLL2CON_FOUTSWEN_MASK)) return clk_state = -1;
    PLL2CONbits.PLLSWEN = 1;  if (!wait_clear(&PLL2CON, _PLL2CON_PLLSWEN_MASK)) return clk_state = -1;
    g = PLL_SPINS; while (PLL2CONbits.CLKRDY == 0 && --g) ;
    if (!g) return clk_state = -1;
    // CLKGEN7 (PDM DAC) <- PLL2 VCO-div output (NOSC 8, Table 15-3) = 500 MHz
    CLK7CONbits.ON = 1; CLK7CONbits.NOSC = 8; CLK7CONbits.OSWEN = 1;
    if (!wait_clear(&CLK7CON, _CLK7CON_OSWEN_MASK)) return clk_state = -1;
    g = PLL_SPINS; while (CLK7CONbits.CLKRDY == 0 && --g) ;
    if (!g) return clk_state = -1;

    // DAC module: factory INL/DNL trims, transition / steady-state timers at their 500 MHz defaults (340 / 552 ns)
    uint32_t cal = *(volatile uint32_t *)FPDMDAC_ADDR;
    DACCTRL1 = 0;
    if (cal != 0xFFFFFFFFu) {
        DACCTRL1bits.POSINLADJ = (cal >> 16) & 0x3Fu;
        DACCTRL1bits.NEGINLADJ = (cal >> 8) & 0x7Fu;
        DACCTRL1bits.DNLADJ    = cal & 0x1Fu;
    }
    DACCTRL2bits.TMODTIME = 0x55;
    DACCTRL2bits.SSTIME   = 0x8A;
    ANSELAbits.ANSELA1 = 1; TRISAbits.TRISA1 = 1;   // RA1 = DACOUT1 (analog; the DAC output buffer drives it)
    DAC1CON = 0;
    DACCTRL1bits.ON = 1;
    return clk_state = 1;
}

static void sine_stop(void) {
    DMA2CHbits.CHEN = 0;
    CCP3CON1bits.ON = 0;
}
static void slope_stop(void) { DAC1SLPCON = 0; DAC1SLPDAT = 0; }

int dac_off(void) {
    sine_stop();
    if (clk_state == 1) { slope_stop(); DAC1CONbits.DACOEN = 0; DAC1CONbits.DACEN = 0; }
    mode = DAC_OFF;
    return 0;
}

static void dac_enable_out(void) { DAC1CONbits.DACOEN = 1; DAC1CONbits.DACEN = 1; }

int dac_dc(unsigned code) {
    if (code < DAC_CODE_MIN || code > DAC_CODE_MAX) return -1;
    if (dac_clock_init() < 0) return -2;
    sine_stop(); slope_stop();
    DAC1CONbits.UPDTMDIS = 0;
    DAC1DATbits.DACLOW = 0; DAC1DATbits.DACDAT = code;
    dac_enable_out();
    mode = DAC_DC; cur_hi = code;
    return 0;
}

int dac_tri(unsigned lo, unsigned hi, unsigned slp) {
    // DS70005592 Example 19-3 note: DACDAT <= 0xF32 - SLPDAT and DACLOW >= 0x0CD + SLPDAT
    if (slp == 0 || slp > 0xFFFFu || lo >= hi || hi + slp > DAC_CODE_MAX || lo < DAC_CODE_MIN + slp) return -1;
    if (dac_clock_init() < 0) return -2;
    sine_stop(); slope_stop();
    DAC1CONbits.UPDTMDIS = 0;
    DAC1DATbits.DACLOW = lo; DAC1DATbits.DACDAT = hi;
    DAC1SLPDATbits.SLPDAT = slp;
    DAC1SLPCONbits.TWME = 1;
    DAC1SLPCONbits.SLOPEN = 1;
    dac_enable_out();
    mode = DAC_TRI; cur_lo = lo; cur_hi = hi; cur_slp = slp;
    return 0;
}

int dac_sine(float hz, unsigned amp, unsigned mid, float *hz_out, unsigned *npts, unsigned *upd_counts) {
    if (!(hz > 0.0f) || mid < DAC_CODE_MIN + amp || mid + amp > DAC_CODE_MAX) return -1;
    // points per period: as many as fit in the table at >= 1 us per update
    float per_counts = 200e6f / hz;                         // SCCP3 counts (5 ns) per sine period
    unsigned n = (unsigned)(per_counts / DAC_SINE_MIN_UPD);
    if (n > DAC_SINE_MAX) n = DAC_SINE_MAX;
    if (n < 8) return -1;                                   // > 125 kHz: fewer than 8 points per period
    float upd = per_counts / (float)n;
    if (upd > 65535.0f) return -1;                          // < 23.8 Hz: 16-bit secondary timer period exceeded
    unsigned u = (unsigned)(upd + 0.5f);
    if (dac_clock_init() < 0) return -2;
    sine_stop(); slope_stop();
    for (unsigned k = 0; k < n; k++) {
        float v = (float)mid + (float)amp * sinf(6.2831853f * (float)k / (float)n);
        int c = (int)(v + 0.5f);
        if (c < (int)DAC_CODE_MIN) c = DAC_CODE_MIN;
        if (c > (int)DAC_CODE_MAX) c = DAC_CODE_MAX;
        sine_tab[k] = (uint32_t)c << 16;                    // DAC1DAT: DACDAT = bits 27:16, DACLOW = 0
    }
    DAC1CONbits.UPDTMDIS = 1;                               // small steps: no transition-mode ripple
    DAC1DAT = sine_tab[0];
    dac_enable_out();
    // SCCP3: dual 16-bit timer, primary disabled (PRL = 0), secondary period u counts -> CCP3IF every update
    CCP3CON1 = 0;
    CCP3CON1bits.T32 = 0; CCP3CON1bits.MOD = 0; CCP3CON1bits.CLKSEL = 1; CCP3CON1bits.TMRPS = 0; CCP3CON1bits.SYNC = 0;
    CCP3TMR = 0;
    CCP3PR = (uint32_t)(u - 2u) << 16;                     // the secondary timer period is PRH + 2 counts (bench 2026-11-21:
                                                            // PRH = u-1 gave 19.884 kHz for 20 kHz = 201 counts per 200)
    // DMA2: repeated one-shot, 32-bit, table -> DAC1DAT, reload source + count after each pass
    DMACONbits.ON = 1;
    DMA2CH = 0; DMA2STAT = 0;
    DMA2SELbits.CHSEL = 0x1A;                               // Table 16-2: CCP3 IC/OC (CCP3IF)
    DMA2SRC = (uint32_t)sine_tab;
    DMA2DST = (uint32_t)&DAC1DAT;
    DMA2CNT = n;
    DMA2CHbits.SIZE = 2; DMA2CHbits.SAMODE = 1; DMA2CHbits.DAMODE = 0; DMA2CHbits.TRMODE = 1;
    DMA2CHbits.RELOADS = 1; DMA2CHbits.RELOADC = 1;
    DMA2CHbits.CHEN = 1;
    CCP3CON1bits.ON = 1;
    mode = DAC_SINE; cur_npts = n; cur_upd = u; cur_amp = amp; cur_mid = mid;
    cur_hz = 200e6f / ((float)u * (float)n);
    if (hz_out) *hz_out = cur_hz;
    if (npts) *npts = n;
    if (upd_counts) *upd_counts = u;
    return 0;
}

void dac_describe(char *buf, unsigned len) {
    const char *ck = clk_state == 1 ? "" : clk_state < 0 ? " noclk" : "";
    switch (mode) {
    case DAC_DC:   snprintf(buf, len, "DAC 1 %u%s\n", cur_hi, ck); break;
    case DAC_TRI:  snprintf(buf, len, "DAC 2 %u %u %u%s\n", cur_lo, cur_hi, cur_slp, ck); break;
    case DAC_SINE: snprintf(buf, len, "DAC 3 %.1f %u %u %u %u%s\n", (double)cur_hz, cur_npts, cur_upd, cur_amp, cur_mid, ck); break;
    default:       snprintf(buf, len, "DAC 0%s\n", ck); break;
    }
}
