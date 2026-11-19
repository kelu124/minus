#!/usr/bin/env python3
"""Plot the board-3 gain sweep (pe captures at 9 gain settings).

usage: /usr/bin/python3 bench/2026-11-19-gain/plot_gain.py [dir]
Inputs: pe_g<leg><u1><u2>_in25.txt (ADC node) and pe_g<leg><u1><u2>_in0.txt (OA1OUT), saved from rpcli.py.
Outputs: gain_full.png (A-lines, in 25), gain_echo1.png (first echo zoom), gain_amplitude.png (echo pp vs gain),
         and prints the echo table + measured stage gains.
"""
import re
import sys
from math import log10
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np

RF = [2200, 4700, 6800, 10000]
ORDER = ["011", "010", "110", "210", "310", "000", "100", "200", "300"]
ECHOES_US = [40.7, 80.5, 120.7, 161.0]
CLIP_LO, CLIP_HI = 60, 3960


def stage(leg, unity):
    return 1.0 if unity else 1.0 + RF[leg] / 1000.0


def nominal(tag):
    leg, u1, u2 = int(tag[0]), int(tag[1]), int(tag[2])
    return stage(leg, u1), stage(leg, u2)


def load(path):
    text = path.read_text()
    fs = float(re.search(r"fs=([0-9.]+)Msps", text).group(1)) * 1e6
    v = np.array([int(l) for l in text.splitlines() if l.strip().isdigit()], float)
    return fs, v


def echo_pp(fs, v, t_us, half_us=5.0):
    i0, i1 = int((t_us - half_us) * 1e-6 * fs), int((t_us + half_us) * 1e-6 * fs)
    seg = v[max(0, i0):min(len(v), i1)]
    clipped = bool((seg <= CLIP_LO).any() or (seg >= CLIP_HI).any())
    return seg.max() - seg.min(), clipped


def label(tag):
    g1, g2 = nominal(tag)
    leg = int(tag[0])
    rf = "" if tag[1:] == "11" else f"Rf {RF[leg] / 1000:.1f}k "
    return f"{rf}OA1 ×{g1:.1f} · OA2 ×{g2:.1f} = {20 * log10(g1 * g2):.1f} dB"


def main(d):
    d = Path(d)
    runs = {t: {inp: load(d / f"pe_g{t}_in{inp}.txt") for inp in (25, 0)} for t in ORDER
            if (d / f"pe_g{t}_in25.txt").exists()}
    tags = [t for t in ORDER if t in runs]

    # 1) A-lines at the ADC node
    fig, axes = plt.subplots(len(tags), 1, figsize=(11, 1.55 * len(tags)), sharex=True)
    for ax, t in zip(axes, tags):
        fs, v = runs[t][25]
        ax.plot(np.arange(len(v)) / fs * 1e6, v, lw=0.5, color="#2f6db5")
        ax.set_ylim(-100, 4195); ax.set_yticks([0, 2048, 4095]); ax.grid(alpha=0.25)
        ax.set_title(label(t), fontsize=8.5, loc="left", pad=2)
    axes[-1].set_xlabel("time from pulse / ADC start (µs)")
    top = axes[0].secondary_xaxis("top", functions=(lambda us: us * 0.077, lambda cm: cm / 0.077))
    top.set_xlabel("depth at 1540 m/s (cm)")
    fig.suptitle("minus board 3 · pulse-echo at 9 gain settings · ADC node AD2AN9 (in 25) · + LNA", fontsize=11)
    fig.tight_layout(); fig.savefig(d / "gain_full.png", dpi=110); plt.close(fig)

    # 2) first echo, zoomed, one panel per gain
    fig, axes = plt.subplots(3, 3, figsize=(12, 7.5), sharex=True, sharey=True)
    for ax, t in zip(axes.flat, tags):
        fs, v = runs[t][25]
        tt = np.arange(len(v)) / fs * 1e6
        m = (tt > 38.5) & (tt < 45.5)
        ax.plot(tt[m], v[m], lw=0.9, marker=".", ms=2.5, color="#2f6db5")
        ax.axhspan(-100, CLIP_LO, color="#d9534f", alpha=0.12); ax.axhspan(CLIP_HI, 4195, color="#d9534f", alpha=0.12)
        ax.set_ylim(-100, 4195); ax.grid(alpha=0.25)
        ax.set_title(label(t), fontsize=8)
    for ax in axes[-1]: ax.set_xlabel("µs")
    fig.suptitle("first echo (40.7 µs ≈ 31 mm) at each gain · ADC node · red bands = ADC rails", fontsize=11)
    fig.tight_layout(); fig.savefig(d / "gain_echo1.png", dpi=110); plt.close(fig)

    # 3) echo amplitude vs nominal chain gain
    fig, ax = plt.subplots(1, 1, figsize=(8.5, 5))
    colors = ["#2f6db5", "#e08a2e", "#3a9a5b", "#8e5bb5"]
    print("tag   nominal_dB  " + "  ".join(f"pp@{e:.0f}us" for e in ECHOES_US) + "   OA1OUT pp@41us  noise_sd")
    for k, e in enumerate(ECHOES_US):
        xs, ys, cl = [], [], []
        for t in tags:
            g1, g2 = nominal(t)
            pp, c = echo_pp(*runs[t][25], e)
            xs.append(20 * log10(g1 * g2)); ys.append(pp); cl.append(c)
        xs, ys, cl = map(np.array, (xs, ys, cl))
        ax.semilogy(xs[~cl], ys[~cl], "o", color=colors[k], label=f"echo {k + 1} ({e:.0f} µs)")
        ax.semilogy(xs[cl], ys[cl], "x", color=colors[k], ms=8)
    ax.set_xlabel("nominal OA1 × OA2 gain (dB, from Rf/Rg)"); ax.set_ylabel("peak-to-peak at the ADC node (LSB)")
    ax.axhline(4095, color="#d9534f", lw=0.8, ls="--"); ax.text(0.5, 4300, "full scale", color="#d9534f", fontsize=8)
    ax.grid(alpha=0.3, which="both"); ax.legend(fontsize=8, title="o = clean   x = clipped", title_fontsize=8)
    ax.set_title("echo amplitude vs gain · board 3 · in 25", fontsize=10)
    fig.tight_layout(); fig.savefig(d / "gain_amplitude.png", dpi=110); plt.close(fig)

    for t in tags:
        g1, g2 = nominal(t)
        fs, v = runs[t][25]
        pps = [echo_pp(fs, v, e) for e in ECHOES_US]
        oa1 = echo_pp(*runs[t][0], ECHOES_US[0])
        noise = (v[-75:] - np.median(v)).std()
        print(f"g{t}  {20 * log10(g1 * g2):5.1f}      " + "  ".join(f"{p:6.0f}{'*' if c else ' '}" for p, c in pps)
              + f"     {oa1[0]:6.0f}{'*' if oa1[1] else ' '}        {noise:5.1f}")
    print("(* = clipped)")
    for f in ("gain_full.png", "gain_echo1.png", "gain_amplitude.png"):
        print("wrote", d / f)


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else Path(__file__).parent)
