#!/usr/bin/env python3
"""Datasheet analysis: bench data -> figures (PDF) + LaTeX value macros.

usage: /usr/bin/python3 bench/2026-11-19-datasheet/analyze.py
Inputs : bench/2026-11-19-datasheet/ (campaign.sh), bench/2026-11-19-gain/, bench/2026-11-19-noise/
Outputs: datasheet/minUS_08112026/figures/*.pdf, datasheet/minUS_08112026/values.tex, and a text report on stdout.
"""
import glob
import re
from math import log10, log2, sqrt
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np

ROOT = Path(__file__).resolve().parents[2]
B = ROOT / "bench/2026-11-19-datasheet"
GAIN = ROOT / "bench/2026-11-19-gain"
NOISE = ROOT / "bench/2026-11-19-noise"
OUT = ROOT / "datasheet/minUS_08112026"
FIG = OUT / "figures"
FIG.mkdir(parents=True, exist_ok=True)
LSB_MV = 3.32 / 4096 * 1e3        # AVDD 3.32 V measured from the band gap
C = 1540.0
BLUE, ORANGE, GREEN, PURPLE, RED, GREY = "#2f6db5", "#e08a2e", "#3a9a5b", "#8e5bb5", "#c0392b", "#7f7f7f"
plt.rcParams.update({"font.size": 8.5, "axes.titlesize": 9, "axes.labelsize": 8.5, "legend.fontsize": 7.5,
                     "figure.dpi": 150, "savefig.bbox": "tight", "axes.grid": True, "grid.alpha": 0.25,
                     "font.family": "sans-serif"})
V = {}          # LaTeX macros
REPORT = []


def say(s=""):
    print(s); REPORT.append(s)


def macro(name, val, fmt="{}"):
    V[name] = fmt.format(val)


def load(p):
    t = Path(p).read_text()
    m = re.search(r"fs=([0-9.]+)Msps", t)
    v = np.array([int(l) for l in t.splitlines() if l.strip().isdigit()], float)
    return (float(m.group(1)) * 1e6 if m else None), v, t


def tus(fs, n):
    return np.arange(n) / fs * 1e6


def win(fs, v, t0, t1):
    i0, i1 = int(t0 * 1e-6 * fs), int(t1 * 1e-6 * fs)
    return v[max(0, i0):min(len(v), i1)]


def pp(fs, v, t, half=5.0):
    s = win(fs, v, t - half, t + half)
    return s.max() - s.min(), bool(s.min() < 60 or s.max() > 3960)


ECHO = [40.7, 80.5, 120.7, 161.0]


def save(fig, name):
    fig.savefig(FIG / f"{name}.pdf"); plt.close(fig)


# ------------------------------------------------------------------ T1 identification / link
def t1():
    t = (B / "t1_ident.txt").read_text()
    m = re.search(r"minus-devkit-rp2354 (\S+) proto (\d+)", t); macro("rpfw", m.group(1)); macro("proto", m.group(2))
    m = re.search(r"minus-devkit-pic32 (\S+)", t); macro("picfw", m.group(1))
    m = re.search(r"unique id: (\S+)", t); macro("uid", m.group(1))
    i2c = re.findall(r"0x([0-9A-F]{2})", t.split("> i2c")[1]) if "> i2c" in t else []
    macro("itwoc", ", ".join("0x" + a for a in i2c) if i2c else "none")
    us = [int(x) for x in re.findall(r"ok, (\d+) us", (B / "t1_ping.txt").read_text())]
    macro("pingus", np.mean(us), "{:.0f}"); macro("pingn", len(us))
    say(f"T1 rp {V['rpfw']} pic {V['picfw']} proto {V['proto']} uid {V['uid']} i2c {V['itwoc']} ping {V['pingus']} us (n={len(us)})")


# ------------------------------------------------------------------ T3 timing
def t3():
    rows = [l.split() for l in (B / "t3_timing.txt").read_text().splitlines() if l.strip()]
    secs = np.array([float(r[0]) for r in rows])
    one = secs[[int(r[2]) == 1 for r in rows]]
    macro("petime", np.median(one), "{:.2f}"); macro("prf", 1 / np.median(one), "{:.2f}")
    xfer = 4095 * 2 * 10 / 115200
    macro("xfer", xfer, "{:.2f}")
    say(f"T3 pe end-to-end (time_pe.py) median {np.median(one):.3f} s over {len(one)} single-shot captures; payload transfer {xfer:.2f} s")


# ------------------------------------------------------------------ T4 pulse sweeps
def t4():
    # fine sweep (bench/2026-11-19-datasheet/t4b/, owner request): t_hi requested in ns -> programmed = round(ns * 0.15) PIO cycles
    files = sorted(glob.glob(str(B / "t4b/hi*_r*.txt")))
    req = sorted({int(re.search(r"hi(\d+)_r", f).group(1)) for f in files})
    res = []
    for hi in req:
        a, b = [], []
        for f in sorted(glob.glob(str(B / f"t4b/hi{hi}_r*.txt"))):
            fs, v, _ = load(f)
            if len(v) != 4095: continue
            a.append(pp(fs, v, ECHO[0])[0]); b.append(pp(fs, v, ECHO[1])[0])
        cyc = max(2, int(hi * 0.15 + 0.5))
        if a: res.append((cyc / 0.15, np.mean(a), np.mean(b), np.ptp(a) / 2, np.ptp(b) / 2))
    res = np.array(res)
    best = res[np.argmax(res[:, 1])]
    macro("hibest", best[0], "{:.0f}")
    macro("hinpts", int((res[:, 0] <= 151).sum()))
    say("T4 fine hi sweep (programmed ns: echo1 / echo2 pp): " + "; ".join(f"{h:.1f}: {a:.0f}/{b:.0f}" for h, a, b, _, _ in res))
    fig, ax = plt.subplots(figsize=(7.0, 2.6))
    ax.errorbar(res[:, 0], res[:, 1], yerr=res[:, 3], fmt="o-", color=BLUE, ms=3.5, lw=1, capsize=2, label="echo 1 (41 µs)")
    ax.errorbar(res[:, 0], res[:, 2], yerr=res[:, 4], fmt="s-", color=ORANGE, ms=3.5, lw=1, capsize=2, label="echo 2 (80 µs)")
    fc = float(V.get("fcen", "3.22")) * 1e6
    tt = np.linspace(0, res[:, 0].max(), 400)
    model = np.abs(np.sin(np.pi * fc * tt * 1e-9))
    ax.plot(tt, model * best[1], ":", color=GREY, lw=0.8, label=f"ideal |sin(π f t)|, f = {fc / 1e6:.2f} MHz")
    # effective pulse = t_hi + delta (dead time: the node stays at +5 V until Q2 turns on; driver delays): fit delta, scale
    m = res[:, 0] >= 20
    best_fit = None
    for d in np.arange(0, 120, 0.5):
        g = np.abs(np.sin(np.pi * fc * (res[m, 0] + d) * 1e-9)); k = (g @ res[m, 1]) / (g @ g)
        err = np.sum((res[m, 1] - k * g) ** 2)
        if best_fit is None or err < best_fit[0]: best_fit = (err, d, k)
    _, dlt, kk = best_fit
    r2 = 1 - best_fit[0] / np.sum((res[m, 1] - res[m, 1].mean()) ** 2)
    macro("deltaeff", dlt, "{:.0f}"); macro("deltarsq", r2, "{:.2f}")
    say(f"T4 fit: effective +5 V pulse = t_hi + {dlt:.1f} ns (R^2 {r2:.2f}, f {fc / 1e6:.2f} MHz)")
    ax.plot(tt, np.abs(np.sin(np.pi * fc * (tt + dlt) * 1e-9)) * kk, "--", color=GREY, lw=0.9,
            label=f"fit |sin(π f (t + {dlt:.0f} ns))|")
    ax.axvspan(0, 150, color=GREEN, alpha=0.06)
    ax.set_xlabel("programmed +5 V phase $t_{hi}$ (ns, 6.67 ns PIO steps)"); ax.set_ylabel("echo amplitude (LSB p-p)")
    ax.set_xlim(0, res[:, 0].max() + 10); ax.set_ylim(0, res[:, 1].max() * 1.32); ax.legend(ncol=4, loc="upper center", fontsize=6.8)
    save(fig, "pulse_width")
    # clamp sweep: ring-down after the main bang
    los = [1, 100, 250, 500, 1000, 2000]
    rr = []
    fig, ax = plt.subplots(figsize=(3.4, 2.4))
    cols = [BLUE, ORANGE, GREEN, PURPLE, RED, GREY]
    for lo, col in zip(los, cols):
        fs, v, _ = load(sorted(glob.glob(str(B / f"t4_lo{lo}_r*.txt")))[0])
        base = np.median(v[-1500:]); x = np.abs(v - base)
        env = np.convolve(x, np.ones(9) / 9, "same")
        noise = np.std(v[-1500:] - base)
        thr = max(6 * noise, 60)
        above = np.where(env[:900] > thr)[0]
        dz = (above[-1] + 1) / fs * 1e6 if len(above) else 0
        e1 = pp(fs, v, ECHO[0])[0]
        rr.append((lo, dz, e1))
        t = tus(fs, len(v)); m = t < 14
        ax.plot(t[m], env[m], lw=0.8, color=col, label=f"$t_{{lo}}$ = {lo} ns")
    ax.axhline(thr, color="k", lw=0.6, ls="--")
    ax.set_yscale("log"); ax.set_xlabel("time after trigger (µs)"); ax.set_ylabel("|signal − baseline| (LSB, 9-pt mean)")
    ax.legend(ncol=2)
    save(fig, "clamp_ringdown")
    macro("deadzone", [d for l, d, _ in rr if l == 500][0], "{:.1f}")
    macro("deadzonemm", [d for l, d, _ in rr if l == 500][0] * C / 2 * 1e-3, "{:.1f}")
    say("T4 lo sweep (dead zone us, echo1 pp): " + "; ".join(f"{l} ns {d:.1f} us {e:.0f}" for l, d, e in rr))
    return res, rr


# ------------------------------------------------------------------ T5 main bang / latency
def t5():
    out = {}
    fig, ax = plt.subplots(figsize=(7.0, 2.3))
    for inp, col, name in ((0, BLUE, "OA1OUT (in 0)"), (17, ORANGE, "OA2OUT (in 17)"), (25, GREEN, "ADC node (in 25)")):
        fs, v, _ = load(B / f"t5_mb_in{inp}.txt")
        base = np.median(v[1000:]); noise = np.std(v[1000:2000] - base)
        onset = int(np.argmax(np.abs(v - base) > max(8 * noise, 80)))
        out[inp] = onset / fs * 1e9
        t = tus(fs, len(v)); m = t < 3.0
        ax.plot(t[m], v[m], ".-", lw=0.8, ms=2.5, color=col, label=f"{name}: onset sample {onset}")
    ax.axvspan(0, 0.2, color=RED, alpha=0.10); ax.text(0.01, 3900, "+5 V", fontsize=7, color=RED)
    ax.axvspan(0.227, 0.727, color=BLUE, alpha=0.08); ax.text(0.30, 3900, "GND clamp", fontsize=7, color=BLUE)
    ax.set_xlabel("time from RDY rising edge = ADC start (µs)"); ax.set_ylabel("ADC code"); ax.set_ylim(-80, 4180)
    ax.legend(loc="lower right")
    save(fig, "main_bang")
    macro("onsetns", "\\textless\\,40" if max(out.values()) < 40 else f"{max(out.values()):.0f}")
    say("T5 main-bang onset (ns after ADC start): " + ", ".join(f"in{k} {v:.0f}" for k, v in out.items()))


# ------------------------------------------------------------------ T6 echo spectrum, pulse length
def t6(tag="010"):
    files = sorted(glob.glob(str(B / f"t7_g{tag}_r*.txt")))
    fs, v0, _ = load(files[0])
    stack = np.array([load(f)[1] for f in files])
    avg = stack.mean(0)
    seg = win(fs, avg, 37.5, 47.5); seg = seg - seg.mean()
    nfft = 8192
    sp = np.abs(np.fft.rfft(seg * np.hanning(len(seg)), nfft)); f = np.fft.rfftfreq(nfft, 1 / fs) / 1e6
    sp_db = 20 * np.log10(sp / sp.max())
    k = np.argmax(sp); fc = f[k]
    lo = f[:k][sp_db[:k] < -6][-1] if (sp_db[:k] < -6).any() else f[0]
    hi = f[k:][sp_db[k:] < -6][0] if (sp_db[k:] < -6).any() else f[-1]
    fcen = (lo + hi) / 2
    # envelope (analytic signal) of echo 1
    n = len(seg); X = np.fft.fft(seg); h = np.zeros(n); h[0] = 1; h[1:(n + 1) // 2] = 2
    if n % 2 == 0: h[n // 2] = 1
    env = np.abs(np.fft.ifft(X * h)); te = np.arange(n) / fs * 1e6 + 37.5
    above = np.where(env > env.max() / 2)[0]
    w6 = (above[-1] - above[0] + 1) / fs * 1e9
    macro("fpeak", fc, "{:.2f}"); macro("fcen", fcen, "{:.2f}"); macro("bwlo", lo, "{:.2f}"); macro("bwhi", hi, "{:.2f}")
    macro("fbw", (hi - lo) / fcen * 100, "{:.0f}"); macro("pulselen", w6, "{:.0f}"); macro("axres", w6 * 1e-9 * C / 2 * 1e3, "{:.2f}")
    # echo spacing -> path
    # echo spacing: cross-correlate echo 1 with echo 2 and echo 2 with echo 3 (parabolic peak)
    spacing = []
    for a_, b_ in ((ECHO[0], ECHO[1]), (ECHO[1], ECHO[2])):
        x = win(fs, avg, a_ - 4, a_ + 4); x = x - x.mean()
        y = win(fs, avg, b_ - 4 - 2, b_ + 4 + 2); y = y - y.mean()
        cc = np.correlate(y, x, "valid"); i = int(np.argmax(cc))
        d = 0.5 * (cc[i - 1] - cc[i + 1]) / (cc[i - 1] - 2 * cc[i] + cc[i + 1]) if 0 < i < len(cc) - 1 else 0
        spacing.append((b_ - 4 - 2 - (a_ - 4)) + (i + d) / fs * 1e6)
    spacing = np.array(spacing)
    macro("echospacing", np.mean(spacing), "{:.1f}"); macro("pathmm", np.mean(spacing) * 1e-6 * C / 2 * 1e3, "{:.1f}")
    say(f"T6 echo 1 spectrum: peak {fc:.2f} MHz, -6 dB {lo:.2f}-{hi:.2f} MHz (centre {fcen:.2f}, {100 * (hi - lo) / fcen:.0f} % FBW); "
        f"-6 dB pulse length {w6:.0f} ns; echo spacing {np.mean(spacing):.2f} us")
    fig, axes = plt.subplots(1, 2, figsize=(7.0, 2.4))
    ax = axes[0]
    ax.plot(te, seg, lw=0.8, color=BLUE); ax.plot(te, env, lw=1, color=ORANGE); ax.plot(te, -env, lw=1, color=ORANGE)
    ax.set_xlabel("time (µs)"); ax.set_ylabel("LSB (16-shot mean)"); ax.set_title(f"echo 1 · −6 dB envelope width {w6:.0f} ns")
    ax = axes[1]
    ax.plot(f, sp_db, color=BLUE, lw=1); ax.axhline(-6, color="k", lw=0.6, ls="--")
    ax.axvspan(lo, hi, color=ORANGE, alpha=0.15)
    ax.set_xlim(0, 10); ax.set_ylim(-40, 2); ax.set_xlabel("frequency (MHz)"); ax.set_ylabel("dB")
    ax.set_title(f"spectrum · peak {fc:.2f} MHz · −6 dB {lo:.2f}–{hi:.2f} MHz")
    save(fig, "echo_spectrum")


# ------------------------------------------------------------------ T7 repeatability + averaging + A-line figure
def t7():
    for tag, label in (("200", "both stages leg 2 (≈38 dB)"), ("010", "OA2 leg 0 (≈11 dB)")):
        files = sorted(glob.glob(str(B / f"t7_g{tag}_r*.txt")))
        recs = [load(f) for f in files]
        fs = recs[0][0]
        stack = np.array([r[1] for r in recs])
        shots = [int(m.group(1)) for r in recs for m in [re.search(r"(\d+) shot", r[2])] if m]
        # amplitude repeatability on the first unclipped echo
        k = 2 if tag == "200" else 1
        amps = np.array([pp(fs, s, ECHO[k])[0] for s in stack])
        # arrival-time jitter: cross-correlate echo k against the mean, parabolic interpolation
        ref = win(fs, stack.mean(0), ECHO[k] - 4, ECHO[k] + 4); ref = ref - ref.mean()
        lags = []
        for s in stack:
            x = win(fs, s, ECHO[k] - 4, ECHO[k] + 4); x = x - x.mean()
            cc = np.correlate(x, ref, "full"); i = np.argmax(cc)
            if 0 < i < len(cc) - 1:
                d = 0.5 * (cc[i - 1] - cc[i + 1]) / (cc[i - 1] - 2 * cc[i] + cc[i + 1]); lags.append(i + d - (len(ref) - 1))
        jit = np.std(lags) / fs * 1e9
        span = (max(lags) - min(lags)) / fs * 1e9
        # align every shot on the mean (Fourier sub-sample shift), then noise of an N-average by the half-difference
        # of two disjoint N-averages: sigma_N = std(mean(A) - mean(B)) / sqrt(2) (removes everything repeatable)
        n = stack.shape[1]; fr = np.fft.rfftfreq(n)
        al = np.array([np.fft.irfft(np.fft.rfft(s - s.mean()) * np.exp(2j * np.pi * fr * l), n) for s, l in zip(stack, lags)])
        # averaging: noise in a quiet window (24-36 us) vs N
        Ns = [1, 2, 4, 8]; nz = []
        for N in Ns:
            vals = []
            for i in range(0, 16 - 2 * N + 1, 2 * N):
                dlt = al[i:i + N].mean(0) - al[i + N:i + 2 * N].mean(0)
                q = np.concatenate([win(fs, dlt, a_, b_) for a_, b_ in ((14, 36), (47, 75), (88, 115), (128, 155))])
                vals.append(np.std(q) / sqrt(2))    # gaps between the echoes only (echo amplitude CV ~3 % would dominate)
            nz.append(np.mean(vals))
        Ns.append(16); nz.append(nz[-1] / sqrt(2))      # 16 shots: extrapolated from 8 (only one disjoint pair of 8 exists)
        say(f"T7 g{tag}: shots/capture {shots}; echo{k + 1} amp mean {amps.mean():.0f} CV {100 * amps.std() / amps.mean():.2f} %; "
            f"arrival jitter {jit:.2f} ns rms (span {span:.0f} ns); noise of an N-average (aligned, half-difference) {dict(zip(Ns, np.round(nz, 2)))}")
        if tag == "200":
            macro("ampcv", 100 * amps.std() / amps.mean(), "{:.1f}"); macro("jitter", jit, "{:.1f}")
            macro("noiseone", nz[0], "{:.1f}"); macro("noisesixteen", nz[-1], "{:.1f}")
            macro("avggain", 20 * log10(nz[0] / nz[3]), "{:.1f}"); macro("jitspan", span, "{:.0f}")
            macro("retryrate", 100 * np.mean(np.array(shots) > 1), "{:.0f}")
            fig, ax = plt.subplots(figsize=(3.4, 2.4))
            ax.loglog(Ns[:4], nz[:4], "o-", color=BLUE, ms=3.5, label="measured (aligned, half-difference)")
            ax.loglog(Ns, nz[0] / np.sqrt(Ns), "--", color=GREY, lw=0.8, label=r"$1/\sqrt{N}$")
            ax.set_xlabel("shots averaged N"); ax.set_ylabel("noise σ (LSB)"); ax.legend()
            ax.set_xticks(Ns); ax.set_xticklabels(Ns)
            save(fig, "averaging")
            # A-line figure: single shot vs 16-shot mean, full and log-envelope
            t = tus(fs, stack.shape[1])
            fig, axes = plt.subplots(2, 1, figsize=(7.0, 3.6), sharex=True)
            axes[0].plot(t, stack[0], lw=0.4, color=BLUE)
            axes[0].set_ylabel("ADC code"); axes[0].set_ylim(-80, 4180); axes[0].set_title(f"single shot · gain {label} · 25 Msps · 4095 samples")
            avg = al.mean(0) + np.median(stack); b = np.median(avg)
            n = len(avg); X = np.fft.fft(avg - b); h = np.zeros(n); h[0] = 1; h[1:(n + 1) // 2] = 2
            env = np.abs(np.fft.ifft(X * h))
            axes[1].plot(t, 20 * np.log10(np.maximum(env, 0.3) / 2048), lw=0.6, color=ORANGE)
            axes[1].set_ylabel("envelope (dBFS)"); axes[1].set_xlabel("time (µs)"); axes[1].set_ylim(-75, 3)
            axes[1].set_title("16-shot mean, envelope")
            top = axes[0].secondary_xaxis("top", functions=(lambda us: us * 1e-6 * C / 2 * 1e2, lambda cm: cm / 1e2 * 2 / C * 1e6))
            top.set_xlabel("depth at 1540 m/s (cm)")
            save(fig, "aline")


# ------------------------------------------------------------------ gain (reuse the gain sweep)
RF = [2.2, 4.7, 6.8, 10.0]
G1M = [3.58, 5.8, 7.9, 10.2]; G2M = [3.68, 6.9, 9.8, 13.1]
TAGS = ["011", "010", "110", "210", "310", "000", "100", "200", "300"]


def gains(tag, measured=True):
    leg, u1, u2 = int(tag[0]), int(tag[1]), int(tag[2])
    if measured:
        return (1.0 if u1 else G1M[leg]), (1.0 if u2 else G2M[leg])
    return (1.0 if u1 else 1 + RF[leg]), (1.0 if u2 else 1 + RF[leg])


def t8():
    fig, ax = plt.subplots(figsize=(3.4, 2.5))
    cols = [BLUE, ORANGE, GREEN, PURPLE]
    for k, e in enumerate(ECHO):
        xs, ys, cl = [], [], []
        for t in TAGS:
            fs, v, _ = load(GAIN / f"pe_g{t}_in25.txt")
            g1, g2 = gains(t, False); a, c = pp(fs, v, e)
            xs.append(20 * log10(g1 * g2)); ys.append(a); cl.append(c)
        xs, ys, cl = map(np.array, (xs, ys, cl))
        ax.semilogy(xs[~cl], ys[~cl], "o", ms=3.5, color=cols[k], label=f"echo {k + 1}")
        ax.semilogy(xs[cl], ys[cl], "x", ms=5, color=cols[k])
    ax.axhline(4095, color=RED, lw=0.6, ls="--")
    ax.set_xlabel("programmed OA1·OA2 gain (dB)"); ax.set_ylabel("echo amplitude (LSB p-p)"); ax.legend(ncol=2, title="o clean · x clipped", title_fontsize=7)
    save(fig, "gain_echoes")


# ------------------------------------------------------------------ noise (T9 with firmware correction + earlier ADC-alone data)
def band_sigma(x, fs, f1=1.5e6, f2=5e6, notch=2.72e6):
    X = np.fft.rfft(x); f = np.fft.rfftfreq(len(x), 1 / fs)
    m = (f >= f1) & (f <= f2) & ~((f > notch - 0.15e6) & (f < notch + 0.15e6))
    return np.fft.irfft(X * m, len(x)).std()


def t9():
    rows = []
    for t in TAGS:
        fl = sorted(glob.glob(str(B / f"t9_g{t}_r*.txt")))
        if not fl:
            continue
        xs = [load(f) for f in fl]
        fs = xs[0][0]
        s_full = np.sqrt(np.mean([(v[64:] - v[64:].mean()).var() for _, v, _ in xs]))
        s_band = np.sqrt(np.mean([band_sigma(v[64:] - v[64:].mean(), fs) ** 2 for _, v, _ in xs]))
        g1, g2 = gains(t); G = g1 * g2
        rows.append((t, G, s_full, s_band))
    fa = sorted(glob.glob(str(B / "t9_adc_r*.txt")))
    adc = np.sqrt(np.mean([(v[64:] - v[64:].mean()).var() for _, v, _ in (load(f) for f in fa)])) if fa else None
    enob = lambda s: 12 - log2(s * sqrt(12))
    say("T9 noise with firmware pattern correction (full band / 1.5-5 MHz, LSB; ENOB_n):")
    for t, G, sf, sb in rows:
        say(f"   g{t} G {G:6.1f}: {sf:5.2f} ({enob(sf):.2f} b) / {sb:5.2f} ({enob(sb):.2f} b); in-band input-ref at OA1 in "
            f"{sb * LSB_MV * 1e3 / G / sqrt(3.5e6) * 1e3:.1f} nV/rtHz")
    if adc:
        say(f"   ADC alone (AD2AN15, SAMC 3): {adc:.2f} LSB = {enob(adc):.2f} bits")
        macro("adcsigma", adc, "{:.2f}"); macro("adcenob", enob(adc), "{:.1f}")
    d = {t: (G, sf, sb) for t, G, sf, sb in rows}
    macro("nzunity", d["011"][1], "{:.1f}"); macro("enobunity", enob(d["011"][1]), "{:.1f}")
    macro("nzmax", d["300"][1], "{:.1f}"); macro("enobmax", enob(d["300"][1]), "{:.1f}")
    macro("nzbandunity", d["011"][2], "{:.2f}"); macro("enobbandunity", enob(d["011"][2]), "{:.1f}")
    macro("nzbandmax", d["300"][2], "{:.1f}"); macro("enobbandmax", enob(d["300"][2]), "{:.1f}")
    macro("eninmax", d["300"][2] * LSB_MV * 1e-3 / d["300"][0] / sqrt(3.5e6) * 1e9, "{:.0f}")
    macro("drmax", 20 * log10(1448.2 / d["300"][2]), "{:.0f}")
    # table rows for LaTeX
    lines = []
    for t, G, sf, sb in rows:
        g1n, g2n = gains(t, False)
        lines.append(f"\\texttt{{gain {t[0]} {t[1]} {t[2]}}} & {20 * log10(g1n * g2n):.1f} & {20 * log10(G):.1f} & {sf:.2f} & {enob(sf):.1f} & {sb:.2f} & {enob(sb):.1f} & "
                     f"{sb * LSB_MV * 1e-3 / G / sqrt(3.5e6) * 1e9:.0f} \\\\")
    (OUT / "noise_rows.tex").write_text("\\newcommand{\\noiserows}{%\n" + "\n".join(lines) + "}\n")
    fig, ax = plt.subplots(figsize=(3.4, 2.5))
    Gs = np.array([r[1] for r in rows])
    ax.loglog(Gs, [r[2] for r in rows], "o", color=BLUE, ms=3.5, label="full band (0–12.4 MHz)")
    ax.loglog(Gs, [r[3] for r in rows], "s", color=ORANGE, ms=3.5, label="1.5–5 MHz")
    if adc: ax.axhline(adc, color="k", lw=0.6, ls="--", label=f"ADC alone ({adc:.2f} LSB)")
    ax.set_xlabel("measured OA1·OA2 gain (×)"); ax.set_ylabel("output noise σ (LSB)")
    sec = ax.secondary_yaxis("right", functions=(lambda s: 12 - np.log2(np.maximum(s, 1e-3) * sqrt(12)), lambda e: 2 ** (12 - e) / sqrt(12)))
    sec.set_ylabel("noise-limited ENOB (bit)")
    ax.legend(fontsize=6.5)
    save(fig, "noise_gain")
    # PSD figure from the noise campaign (pattern removed), input-referred
    fig, ax = plt.subplots(figsize=(7.0, 2.5))
    for t, col in (("011", BLUE), ("000", GREEN), ("100", ORANGE), ("300", PURPLE)):
        fl = sorted(glob.glob(str(B / f"t9_g{t}_r*.txt")))
        G = gains(t)[0] * gains(t)[1]; acc = 0; n = 0; nseg = 512; w = np.hanning(nseg)
        for f in fl:
            fs, v, _ = load(f); x = v[64:] - v[64:].mean()
            for i in range(0, len(x) - nseg + 1, nseg // 2):
                s = x[i:i + nseg] - x[i:i + nseg].mean(); acc = acc + np.abs(np.fft.rfft(s * w)) ** 2 / (fs * (w ** 2).sum()) * 2; n += 1
        fr = np.fft.rfftfreq(nseg, 1 / fs) / 1e6
        ax.semilogy(fr, np.sqrt(acc / n) * LSB_MV * 1e6 / G, lw=0.9, color=col, label=f"gain {t[0]} {t[1]} {t[2]} (×{G:.0f})")
    ax.axvspan(1.5, 5, color=GREY, alpha=0.12)
    ax.set_xlabel("frequency (MHz)"); ax.set_ylabel("nV/√Hz at OA1 input"); ax.legend(ncol=4)
    save(fig, "noise_psd")


# ------------------------------------------------------------------ T10 sample rates
def t10():
    out = []
    for div in (4, 10, 20, 40):
        p = B / f"t10_div{div}.txt"
        if p.exists():
            m = re.search(r"fill=([0-9.]+)us fs=([0-9.]+)Msps", p.read_text())
            if m: out.append((div, float(m.group(1)), float(m.group(2))))
    say("T10 sample rate options: " + "; ".join(f"div {d}: fill {f} us, {r} Msps" for d, f, r in out))
    for d, f, r in out:
        macro(f"fsdiv{ {4: 'four', 10: 'ten', 20: 'twenty', 40: 'forty'}[d] }", r, "{:.2f}")
        macro(f"filldiv{ {4: 'four', 10: 'ten', 20: 'twenty', 40: 'forty'}[d] }", f, "{:.1f}")


def main():
    t1(); t3(); t6(); t4(); t5(); t7(); t8(); t9(); t10()
    lines = [f"\\newcommand{{\\v{k}}}{{{v}}}" for k, v in sorted(V.items())]
    (OUT / "values.tex").write_text("% generated by bench/2026-11-19-datasheet/analyze.py -- do not edit\n" + "\n".join(lines) + "\n")
    (B / "report.txt").write_text("\n".join(REPORT) + "\n")
    print(f"wrote {len(V)} macros, figures in {FIG}")


if __name__ == "__main__":
    main()
