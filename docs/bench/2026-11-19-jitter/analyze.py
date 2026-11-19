#!/usr/bin/env python3
"""E3 sample-comb phase / jitter analysis of shots.npz (capture.py).

usage (repo root):  /usr/bin/python3 docs/bench/2026-11-19-jitter/analyze.py
writes report.txt, jitter_distribution.png, jitter_template.png next to this script.

Quantity of interest: phi = when the pulse happens relative to the ADC sample comb, per shot. If the capture
started at a fixed time after the pulse, phi would be constant; E3 says it is not.

Method
1. Main bang (electrical, no acoustic path): the transmit feed-through occupies samples 0..~14. Because phi is
   spread over a sample period, the 400 shots sample this waveform at many different phases. Equivalent-time
   reconstruction: start from the mid-scale crossing estimate of phi, place every shot's samples 0..15 on a common
   time axis t = i*dt - phi, bin to a 1 ns template, then re-fit each shot's phi by least squares against the
   template (0.1 ns grid). Three iterations. This is the primary phi estimator (precision ~ 1 ns, see residual).
2. Echoes (acoustic path, independent check): delay of each echo vs the mean by x32 FFT-upsampled
   cross-correlation. The acoustic path drifts slowly (temperature / target), so the echo delay is high-passed
   (minus a 15-shot running median) before comparing with phi.
3. Distribution of phi: rms, span, percentiles, Kolmogorov-Smirnov distance to a uniform over its span and over
   one sample period, fine histogram, clustering periodogram over candidate clock periods (4 ns ADC 250 MHz,
   5 ns SCCP 200 MHz, 6.67 ns RP PIO 150 MHz, 20 ns trigger comb), shot-to-shot autocorrelation,
   set A (back-to-back) vs set B (random 0-50 ms delay), correlation with rp_fill (RDY window seen by the RP).
"""
import json
from pathlib import Path

import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

D = Path(__file__).resolve().parent
z = np.load(D / "shots.npz")
meta = json.loads((D / "meta.json").read_text())
R = z["samples"].astype(float)              # raw codes
N, L = R.shape
DT = float(np.median(z["fill_us"])) * 1000 / L
sets = z["set"]
rep = []
say = lambda s: (rep.append(s), print(s))
say(f"{N} shots ({(sets == 'A').sum()} back-to-back, {(sets == 'B').sum()} with a random 0-50 ms pause), "
    f"rp {meta['rp']} / pic {meta['pic']}, `{meta['command']}`, {meta['gain']}")
say(f"sample period {DT:.3f} ns; fill_us {sorted(set(z['fill_us'].tolist()))}; re-shots (shots>1): "
    f"{int((z['shots'] > 1).sum())}; all fired: {bool(z['fired'].all())}")


# ------------------------------------------------------------------ 1. main bang, equivalent-time template fit
def crossing(x, start, falling):
    for i in range(start, 30):
        a, b = x[i - 1], x[i]
        if (a >= 2048 > b) if falling else (a < 2048 <= b):
            return i - 1 + (a - 2048) / (a - b)
    return np.nan


f0 = np.array([crossing(x, 3, True) for x in R])
r0 = np.array([crossing(x, int(f) + 2, False) for x, f in zip(R, f0)])
phi = (f0 + r0) / 2 * DT
phi -= np.median(phi)
NS = 16                                         # samples 0..15 carry the main bang
idx = np.arange(NS) * DT
grid = np.arange(-120, NS * DT + 120, 1.0)


def template(phi):
    t = (idx[None, :] - phi[:, None]).ravel()
    v = R[:, :NS].ravel()
    k = np.round(t - grid[0]).astype(int)
    T = np.full(len(grid), np.nan)
    for j in np.unique(k):
        T[j] = np.median(v[k == j])
    good = np.isfinite(T)
    return np.interp(grid, grid[good], T[good])


cand = np.arange(-80, 80.01, 0.1)
for it in range(3):
    T = template(phi)
    sse = np.array([[np.sum((x[:NS] - np.interp(idx - c, grid, T)) ** 2) for c in cand] for x in R])
    phi = cand[np.argmin(sse, axis=1)]
    phi -= np.median(phi)
resid = np.sqrt(np.min(sse, axis=1) / NS)
say(f"MAIN-BANG template fit: residual {np.median(resid):.0f} LSB rms per sample (main bang spans ~4000 LSB); "
    f"phi at the search edge: {int(np.sum(np.abs(phi) > 79))} shots")

# ------------------------------------------------------------------ 2. echoes (independent check)
X = R - np.median(R, axis=1, keepdims=True)
ref = X.mean(0)
B = 25
blk = np.abs(ref[: L // B * B]).reshape(-1, B).max(1)
hot = (blk > 6 * np.median(blk)) & (np.arange(len(blk)) * B * DT / 1000 > 30)
wins, i = [], 0
while i < len(hot):
    if hot[i]:
        j = i
        while j + 1 < len(hot) and hot[j + 1]:
            j += 1
        wins.append(slice(max(0, i * B - B), min(L, (j + 1) * B + B)))
        i = j + 1
    else:
        i += 1
UP = 32


def delay(x, ref, w):
    a, b = x[w] - x[w].mean(), ref[w] - ref[w].mean()
    n = len(a); nf = 2 * n
    cc = np.fft.irfft(np.fft.rfft(a, nf) * np.conj(np.fft.rfft(b, nf)), nf * UP) * UP
    cc = np.concatenate([cc[-(n * UP):], cc[: n * UP]])
    k = int(np.argmax(cc)); y0, y1, y2 = cc[k - 1], cc[k], cc[k + 1]
    return (k + 0.5 * (y0 - y2) / (y0 - 2 * y1 + y2) - n * UP) / UP


w1 = max(wins, key=lambda w: np.abs(ref[w]).max())        # strongest echo
ed = np.array([delay(x, ref, w1) for x in X]) * DT
def runmed(v, k=15):
    return np.array([np.median(v[max(0, i - k // 2): i + k // 2 + 1]) for i in range(len(v))])
drift = runmed(ed)
ehp = ed - drift
t_us = np.arange(L) * DT / 1000
r_e = np.corrcoef(phi, ehp)[0, 1]
slope_e = np.polyfit(phi, ehp, 1)[0]
say(f"ECHO check (strongest echo, {t_us[w1.start]:.1f}-{t_us[w1.stop - 1]:.1f} µs): slow acoustic drift "
    f"{np.ptp(drift):.0f} ns p-p over the run (removed); shot-to-shot part vs main-bang phi: r = {r_e:.2f}, "
    f"slope {slope_e:.2f} (1 = echo moves with the pulse), residual {np.std(ehp - slope_e * phi):.1f} ns rms")

# whole-sample slips: echo delay (drift removed) minus the main-bang phase, in units of one sample. 0 = the echo is
# where the pulse timing says; +-1 = the sample comb gained / lost one full period between the main bang and the
# echo (an RF-cycle mis-pick would be ~7.5 samples at 3.3 MHz, so +-1 is not an estimator artefact on a strong echo).
slip_rows = []
for w in sorted(wins, key=lambda w: w.start):
    if np.abs(ref[w]).max() < 0.1 * np.abs(ref[w1]).max():
        continue
    d = np.array([delay(x, ref, w) for x in X]) * DT
    res = (d - runmed(d)) - phi
    k = np.round(res / DT).astype(int)
    near = np.abs(k) <= 2
    frac = (res - k * DT)[k == 0]
    c = {v: int(np.sum(k == v)) for v in (-2, -1, 0, 1, 2)}
    slip_rows.append((t_us[w.start], t_us[w.stop - 1], c, frac.std(), int((~near).sum())))
    say(f"SLIPS echo {t_us[w.start]:.1f}-{t_us[w.stop - 1]:.1f} µs: shots by offset (samples) -2..+2 {list(c.values())}, "
        f"off by >2 (RF-cycle mis-picks, ignored) {int((~near).sum())}; aligned shots' residual {frac.std():.1f} ns rms")

# ------------------------------------------------------------------ 3. distribution of phi
def ks_uniform(v, lo, hi):
    u = np.sort((v - lo) / (hi - lo)); n = len(u)
    d = np.max(np.maximum(np.arange(1, n + 1) / n - u, u - np.arange(n) / n))
    lam = (np.sqrt(n) + 0.12 + 0.11 / np.sqrt(n)) * d
    p = 2 * sum((-1) ** (j - 1) * np.exp(-2 * j * j * lam * lam) for j in range(1, 100))
    return d, float(min(1, max(0, p)))


lo, hi = phi.min(), phi.max()
d_span, p_span = ks_uniform(phi, lo, hi)
q = np.percentile(phi, [0.5, 2.5, 25, 50, 75, 97.5, 99.5])
core = phi[(phi > q[1]) & (phi < q[5])]
say(f"PHI (pulse vs sample comb): rms {phi.std():.1f} ns, span {hi - lo:.1f} ns p-p, central 95 % "
    f"{q[5] - q[1]:.1f} ns; uniform over one sample would be {DT:.1f} ns p-p / {DT / np.sqrt(12):.1f} ns rms")
say("  percentiles 0.5/2.5/25/50/75/97.5/99.5 %: " + " ".join(f"{v:+.1f}" for v in q) + " ns")
say(f"  KS vs uniform over its span: D = {d_span:.3f}, p = {p_span:.3g}")
gaps = np.diff(np.sort(phi))
g = np.argmax(gaps)
say(f"  largest gap in the sorted phases: {gaps[g]:.1f} ns between {np.sort(phi)[g]:+.1f} and {np.sort(phi)[g + 1]:+.1f} ns; "
    f"shots above it: {int(np.sum(phi > np.sort(phi)[g]))}")
periods = np.linspace(2.5, 25, 2251)
Rp = np.abs(np.exp(2j * np.pi * phi[None, :] / periods[:, None]).mean(1))
pk = periods[np.argmax(Rp)]
at = lambda P: Rp[np.argmin(abs(periods - P))]
say(f"  clustering periodogram |<exp(2πi phi/P)>|: max {Rp.max():.3f} at P = {pk:.2f} ns (3/√N = {3 / np.sqrt(N):.3f}); "
    f"P = 4 ns {at(4):.3f}, 5 ns {at(5):.3f}, 6.67 ns {at(6.667):.3f}, 20 ns {at(20):.3f}")
ac = [np.corrcoef(phi[:-k], phi[k:])[0, 1] for k in range(1, 6)]
say("  shot-to-shot autocorrelation (lag 1..5): " + " ".join(f"{v:+.2f}" for v in ac))
A = sets == "A"
dAB, pAB = None, None
say(f"  set A (back-to-back) rms {phi[A].std():.1f} ns, set B (random pause) rms {phi[~A].std():.1f} ns; "
    f"corr(pause, phi) in B {np.corrcoef(z['delay_s'][~A], phi[~A])[0, 1]:+.2f}")
rpf = z["rp_fill_us"]
say(f"  rp_fill (RDY window timed by the RP, 1 µs resolution): {dict(zip(*np.unique(rpf, return_counts=True)))}; "
    f"mean phi per value " + ", ".join(f"{v}: {phi[rpf == v].mean():+.1f}" for v in np.unique(rpf)) + " ns")
(D / "report.txt").write_text("\n".join(rep) + "\n")

# ------------------------------------------------------------------ figures
fig, ax = plt.subplots(2, 2, figsize=(11, 7.5))
ax[0, 0].hist(phi, bins=np.arange(np.floor(lo) - 1, hi + 2, 2), color="C0")
ax[0, 0].set(xlabel="phi: pulse vs sample comb (ns, 2 ns bins)", ylabel="shots",
             title=f"{N} shots · rms {phi.std():.1f} ns · span {hi - lo:.0f} ns")
for k in (-1, 0, 1):
    ax[0, 0].axvline(k * DT, color="k", lw=.5, ls=":")
ax[0, 1].plot(np.sort(phi), np.arange(1, N + 1) / N, label="measured")
ax[0, 1].plot([lo, hi], [0, 1], "k--", lw=1, label="uniform over the span")
ax[0, 1].set(xlabel="phi (ns)", ylabel="CDF", title=f"KS D = {d_span:.2f}"); ax[0, 1].legend()
ax[1, 0].plot(phi, ".", ms=3)
ax[1, 0].axvline(A.sum() - .5, color="k", lw=.8)
ax[1, 0].set(xlabel="shot (set A | set B)", ylabel="phi (ns)", title="sequence: no memory between shots")
ax[1, 1].plot(periods, Rp); ax[1, 1].axhline(3 / np.sqrt(N), color="k", ls="--", lw=1, label="3/√N")
for P in (4, 5, 6.667, 20):
    ax[1, 1].axvline(P, color="r", lw=.6)
ax[1, 1].set(xlabel="candidate clock period P (ns)", ylabel="|<exp(2πi phi/P)>|",
             title="clustering on a clock grid?"); ax[1, 1].legend()
plt.tight_layout(); fig.savefig(D / "jitter_distribution.png", dpi=130)

fig, ax = plt.subplots(1, 2, figsize=(12, 3.8))
ax[0].plot(grid, T, "k", lw=1, label="1 ns equivalent-time template")
for x, p in list(zip(R, phi))[:40]:
    ax[0].plot(idx - p, x[:NS], ".", ms=2, alpha=.5)
ax[0].set(xlim=(-60, NS * DT), xlabel="ns after the pulse reference", ylabel="ADC code",
          title="main bang: 40 shots placed by their fitted phi")
ax[0].legend()
ax[1].plot(phi, ehp, ".", ms=3)
xx = np.array([lo, hi]); ax[1].plot(xx, slope_e * xx, "r", lw=1)
ax[1].set(xlabel="main-bang phi (ns)", ylabel="echo delay, drift removed (ns)",
          title=f"independent echo timing: r = {r_e:.2f}, slope {slope_e:.2f}")
plt.tight_layout(); fig.savefig(D / "jitter_template.png", dpi=130)
print("figures written")

# ------------------------------------------------------------------ datasheet outputs (macros + compact figure)
DS = D.parents[2] / "datasheet"
s40 = next((r for r in slip_rows if r[0] < 60), None)
s80 = next((r for r in slip_rows if 60 <= r[0] < 100), None)
pct = lambda r: 100 * (r[2][-1] + r[2][1] + r[2][-2] + r[2][2]) / max(1, sum(r[2].values()))
mac = {"Ephirms": f"{phi.std():.1f}", "Ephispan": f"{hi - lo:.0f}", "Ephinine": f"{q[5] - q[1]:.0f}",
       "Eksd": f"{d_span:.2f}", "Eksp": f"{p_span:.3f}", "Eshots": f"{N}", "Eacone": f"{ac[0]:+.2f}",
       "Esliptime": f"{s40[0]:.0f}" if s40 else "?", "Eslipa": f"{pct(s40):.0f}" if s40 else "?",
       "Esliptimeb": f"{s80[0]:.0f}" if s80 else "?", "Eslipb": f"{pct(s80):.0f}" if s80 else "?",
       "Eresid": f"{s40[3]:.1f}" if s40 else "?", "Eclusterp": f"{pk:.1f}", "Eclusterr": f"{Rp.max():.2f}"}
(DS / "jitter_values.tex").write_text("% generated by docs/bench/2026-11-19-jitter/analyze.py -- do not edit\n" +
                                      "".join(f"\\newcommand{{\\v{k}}}{{{v}}}\n" for k, v in mac.items()))
fig, ax = plt.subplots(1, 2, figsize=(7.2, 2.5))
ax[0].hist(phi, bins=np.arange(np.floor(lo) - 1, hi + 2, 2), color="#1f5fa8")
ax[0].set(xlabel="pulse vs sample comb, φ (ns)", ylabel="shots", title=f"{N} shots, {phi.std():.1f} ns rms")
d1 = np.array([delay(x, ref, w1) for x in X]) * DT
ax[1].plot(phi, (d1 - runmed(d1)) - phi, ".", ms=2, color="#1f5fa8")
for k in (-1, 0, 1):
    ax[1].axhline(k * DT, color="k", lw=.4, ls=":")
ax[1].set(xlabel="φ (ns)", ylabel="echo − φ (ns)", title=f"echo at {t_us[w1.start]:.0f} µs: whole-sample slips", ylim=(-70, 70))
for a in ax:
    a.tick_params(labelsize=7); a.title.set_size(8); a.xaxis.label.set_size(8); a.yaxis.label.set_size(8)
plt.tight_layout(); fig.savefig(DS / "figures" / "comb_phase.pdf")
print("datasheet macros + figure written")
