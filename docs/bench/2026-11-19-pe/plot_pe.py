#!/usr/bin/env python3
"""Plot pulse-echo captures from the RP CLI (`pe` / `acq` output saved by rpcli.py).

usage: /usr/bin/python3 docs/bench/2026-11-19-pe/plot_pe.py <dir>
Reads pe_in*.txt (and acq_in25_nopulse.txt if present) and writes pe_full.png, pe_zoom.png.
Time axis from the capture's measured fs (header 'fs=...Msps'); depth axis at c = 1540 m/s.
"""
import re
import sys
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

C = 1540.0  # m/s
LABELS = {
    "pe_in1.txt": "in 1 · AD1AN1 · LNA out (OA1IN+)",
    "pe_in0.txt": "in 0 · AD1AN0 · OA1OUT",
    "pe_in17.txt": "in 17 · AD2AN1 · OA2OUT",
    "pe_in25.txt": "in 25 · AD2AN9 · PIC32_ADC (filtered)",
    "acq_in25_nopulse.txt": "in 25 · no pulse (noise floor)",
}


def load(path):
    fs, vals = None, []
    for line in path.read_text().splitlines():
        m = re.search(r"fs=([0-9.]+)Msps", line)
        if m:
            fs = float(m.group(1)) * 1e6
        elif line.strip().isdigit():
            vals.append(int(line))
    return fs, vals


def main(d):
    d = Path(d)
    runs = [(n, *load(d / n)) for n in LABELS if (d / n).exists()]
    for name, zoom_us, out in (("full", None, "pe_full.png"), ("zoom", 12.0, "pe_zoom.png")):
        fig, axes = plt.subplots(len(runs), 1, figsize=(11, 2.1 * len(runs)), sharex=True)
        for ax, (n, fs, v) in zip(axes, runs):
            t = [i / fs * 1e6 for i in range(len(v))]
            if zoom_us:
                k = sum(1 for x in t if x <= zoom_us)
                t, v = t[:k], v[:k]
                ax.plot(t, v, lw=0.9, marker=".", ms=3, color="#2f6db5")
            else:
                ax.plot(t, v, lw=0.5, color="#2f6db5")
            ax.set_ylim(-100, 4195)
            ax.axhline(2048, color="0.7", lw=0.5, ls="--")
            ax.set_ylabel("ADC (12 bit)")
            ax.set_title(f"{LABELS[n]}   fs {fs / 1e6:.2f} Msps", fontsize=9, loc="left")
            ax.grid(alpha=0.25)
        axes[-1].set_xlabel("time from RDY rise = ADC start = pulser trigger (µs)")
        top = axes[0].secondary_xaxis("top", functions=(lambda us: us * 1e-6 * C / 2 * 100,
                                                         lambda cm: cm / 100 * 2 / C * 1e6))
        top.set_xlabel("depth at 1540 m/s (cm)")
        fig.suptitle(f"minus board 3 · pulse-echo · +5 V 200 ns / off 27 ns / GND 500 ns · {name}", fontsize=11)
        fig.tight_layout()
        fig.savefig(d / out, dpi=110)
        print("wrote", d / out)


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else Path(__file__).parent)
