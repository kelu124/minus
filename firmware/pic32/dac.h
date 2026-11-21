// minus — PIC32AK DAC1 test signal on DACOUT1 (U9 pin 3 = RA1, also AD2AN3 = acq input code 19, AD1AN7 = code 7;
// board 3: H6.16; v1.2: also RP GPIO26/ADC0). Design: docs/claude/specs/2026-11-21-dac-spi-link-design.md
#ifndef DAC_H
#define DAC_H
#include <stdint.h>

#define DAC_CODE_MIN 0x0CDu      // 5 % AVDD (DS70005592 Eq. 19-1: usable range 0x0CD..0xF32)
#define DAC_CODE_MAX 0xF32u      // 95 % AVDD
#define DAC_SINE_MAX 128u        // sine table points (RAM: 16 KB total, ~12 KB are the capture buffers)
#define DAC_SINE_MIN_UPD 200u    // minimum update period in 5 ns SCCP3 counts = 1 us (DAC settles in 0.75-2 us, DA07)

typedef enum { DAC_OFF = 0, DAC_DC = 1, DAC_TRI = 2, DAC_SINE = 3 } dac_mode_t;

// All return 0 on success, <0 on error (-1 bad args, -2 no DAC clock: PLL2/CLKGEN7 did not lock).
int  dac_off(void);
int  dac_dc(unsigned code);
int  dac_tri(unsigned lo, unsigned hi, unsigned slp);                 // hardware triangle; slp = SLPDAT (12.4 counts per 4 ns step)
int  dac_sine(float hz, unsigned amp, unsigned mid, float *hz_out, unsigned *npts, unsigned *upd_counts);
// state for the reply line: "DAC <mode> ..." written into buf
void dac_describe(char *buf, unsigned len);

#endif
