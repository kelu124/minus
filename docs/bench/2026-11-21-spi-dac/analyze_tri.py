"""Triangle from the PIC DAC (dac tri 512 3584 16) captured on AD2AN3 (acq 4 0 19). Usage: python3 analyze_tri.py <capture.txt> [png]"""
import sys, re, numpy as np
import matplotlib; matplotlib.use("Agg"); import matplotlib.pyplot as plt
lines = open(sys.argv[1]).read().splitlines()
h = next(i for i, l in enumerate(lines) if l.startswith("# acq "))
n = int(re.search(r"n=(\d+)", lines[h])[1]); fill = float(re.search(r"fill=([\d.]+)us", lines[h])[1])
y = np.array([int(v) for v in lines[h + 1:h + 1 + n]], float); t = np.arange(n) * fill / n
print(lines[h][:200])
print(f"min {y.min():.0f} max {y.max():.0f} (expected codes 512..3584 if ADC and DAC share AVDD; DAC INL/gain error +-35 LSB)")
yc = y - (y.max() + y.min()) / 2                         # rising mid-level crossings, linearly interpolated
i = np.where((yc[:-1] < 0) & (yc[1:] >= 0))[0]; tc = t[i] + (t[i + 1] - t[i]) * (-yc[i]) / (yc[i + 1] - yc[i])
per = np.diff(tc); print(f"period {per.mean():.3f} us +- {per.std():.3f} over {len(per)} periods (nominal 24.58 us = (hi-lo)*16/slp*4 ns*2)")
d = np.diff(y); print(f"slope up {np.median(d[d>0]):.1f} / down {np.median(d[d<0]):.1f} LSB per sample (nominal 3072/12.29us*40ns = {3072/12.29*0.0402:.1f})")
if len(sys.argv) > 2:
    plt.figure(figsize=(9, 3.2)); plt.plot(t, y, lw=0.7); plt.xlabel("time (us)"); plt.ylabel("ADC code")
    plt.title("PIC DAC triangle 512..3584 on DACOUT1, read by ADC2 (AD2AN3) over SPI"); plt.tight_layout(); plt.savefig(sys.argv[2], dpi=110)
