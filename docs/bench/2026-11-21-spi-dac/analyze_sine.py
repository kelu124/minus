"""Sine from the PIC DAC (dac sine <hz> ...) captured on AD2AN3. Fits a sine, reports f, amplitude, residual, SINAD/ENOB.
Usage: python3 analyze_sine.py <capture.txt> [png]"""
import sys, re, numpy as np
import matplotlib; matplotlib.use("Agg"); import matplotlib.pyplot as plt
lines = open(sys.argv[1]).read().splitlines()
h = next(i for i, l in enumerate(lines) if l.startswith("# acq "))
n = int(re.search(r"n=(\d+)", lines[h])[1]); fill = float(re.search(r"fill=([\d.]+)us", lines[h])[1])
y = np.array([int(v) for v in lines[h + 1:h + 1 + n]], float); t = np.arange(n) * fill / n * 1e-6
print(lines[h][:170])
best = None
for f in np.linspace(19000, 21000, 2001):                     # coarse search, then least squares at the best f
    A = np.column_stack([np.sin(2*np.pi*f*t), np.cos(2*np.pi*f*t), np.ones(n)])
    c, r, *_ = np.linalg.lstsq(A, y, rcond=None); r = float(r[0]) if len(r) else np.inf
    if best is None or r < best[0]: best = (r, f, c)
r, f, c = best; A = np.column_stack([np.sin(2*np.pi*f*t), np.cos(2*np.pi*f*t), np.ones(n)]); fit = A @ c
amp = np.hypot(c[0], c[1]); res = y - fit; rms = res.std()
sinad = 20*np.log10(amp/np.sqrt(2)/rms); enob = (sinad - 1.76)/6.02
print(f"f = {f:.1f} Hz, amplitude {amp:.1f} LSB (asked 1500 DAC codes), offset {c[2]:.1f}")
print(f"residual {rms:.2f} LSB rms, max |res| {np.abs(res).max():.1f} -> SINAD {sinad:.1f} dB = {enob:.2f} ENOB (DAC staircase + ADC together)")
if len(sys.argv) > 2:
    fig, ax = plt.subplots(2, 1, figsize=(9, 4.6), sharex=True)
    ax[0].plot(t*1e6, y, lw=0.6, label="capture"); ax[0].plot(t*1e6, fit, lw=0.6, label=f"fit {f/1e3:.3f} kHz"); ax[0].legend(loc="upper right"); ax[0].set_ylabel("ADC code")
    ax[1].plot(t*1e6, res, lw=0.5); ax[1].set_ylabel("residual (LSB)"); ax[1].set_xlabel("time (us)")
    ax[0].set_title("PIC DAC sine (50 points, 1 us updates) on AD2AN3, acq 10 (20 Msps) over SPI"); plt.tight_layout(); plt.savefig(sys.argv[2], dpi=110)
