#!/usr/bin/env python3
"""Noise / ENOB analysis of the board-3 ADC and RX chain.

usage: /usr/bin/python3 docs/bench/2026-11-19-noise/analyze_noise.py
Reads docs/bench/2026-11-19-noise/*_r<k>.txt (capture.sh) and docs/bench/2026-11-19-gain/pe_g*_in25.txt (echo SNR).
Writes noise_vs_gain.png, noise_psd.png, adc_hist.png and noise_summary.txt in docs/bench/2026-11-19-noise/.

Definitions (12-bit, full scale = AVDD = 3.3 V -> 1 LSB = 0.806 mV):
  noise-limited ENOB = 12 - log2(sigma * sqrt(12))  ==  (SNR_FS - 1.76) / 6.02 with SNR_FS = 20 log10(1448 / sigma),
  1448 LSB = rms of a full-scale sine. It ignores distortion (needs a sine test) so it is an upper bound on true ENOB.
Chain model: sigma_out^2 = s_adc^2 + (G2 * n2)^2 + (G1 * G2 * n1)^2, n1 = noise at OA1 input (LNA output side),
  n2 = noise added at OA2 input (OA1 at x1 + OA2 itself), G1/G2 = measured stage gains (docs/bench/2026-11-19-gain).
"""
import re
from math import log10, log2, sqrt
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np

D = Path(__file__).resolve().parent
GAIN_DIR = D.parent / "2026-11-19-gain"
LSB_V = 3.3 / 4096
LNA_DB = 24.0          # BGA2817 nominal small-signal gain (memory 0013/0014) - assumption, not measured on this board
# measured stage gains per mux leg (docs/bench/2026-11-19-gain README, mean of the clean echoes)
G1_MEAS = [3.58, 5.8, 7.9, 10.2]
G2_MEAS = [3.68, 6.9, 9.8, 13.1]
NOMINAL_RF = [2.2, 4.7, 6.8, 10.0]
TAGS = ["011", "010", "110", "210", "310", "000", "100", "200", "300"]


def load(p):
    t = p.read_text()
    m = re.search(r"fs=([0-9.]+)Msps", t)
    v = np.array([int(l) for l in t.splitlines() if l.strip().isdigit()], float)
    return (float(m.group(1)) * 1e6 if m else None), v


def records(prefix):
    out = []
    for p in sorted(D.glob(f"{prefix}_r*.txt")):
        fs, v = load(p)
        if len(v) == 4095:
            out.append((fs, v))
    return out


DEPATTERN = False      # set by main(): remove the period-4 fixed pattern (fs/4, fs/2 tones) per record


def depattern(x, per=4):
    """subtract the per-phase mean (period `per` samples): the fixed pattern locked to the sample clock that every
    external ADC input shows (one sample in four ~23 LSB low, phase random per capture, same at every gain)."""
    n = len(x) // per * per
    ph = x[:n].reshape(-1, per).mean(0)
    return x[:n] - np.tile(ph, n // per)


def prep(v, skip=64):
    x = v[skip:] - v[skip:].mean()
    return depattern(x) if DEPATTERN else x


def sigma(recs, skip=64):
    """pooled rms after removing each record's mean (and the period-4 pattern if DEPATTERN); first samples skipped."""
    x = np.concatenate([prep(v, skip) for _, v in recs])
    return float(x.std()), x


def enob(s):
    return 12 - log2(max(s, 1e-9) * sqrt(12))


def snr_fs(s):
    return 20 * log10(1448.2 / s)


def stage_gains(tag):
    leg, u1, u2 = int(tag[0]), int(tag[1]), int(tag[2])
    return (1.0 if u1 else G1_MEAS[leg]), (1.0 if u2 else G2_MEAS[leg])


def welch(recs, nseg=512, skip=64):
    fs = recs[0][0]
    win = np.hanning(nseg); scale = 1.0 / (fs * (win ** 2).sum())
    acc, n = 0, 0
    for _, v in recs:
        x = prep(v, skip)
        for i in range(0, len(x) - nseg + 1, nseg // 2):
            seg = x[i:i + nseg] - x[i:i + nseg].mean()
            acc = acc + np.abs(np.fft.rfft(seg * win)) ** 2 * scale * 2; n += 1
    return np.fft.rfftfreq(nseg, 1 / fs), acc / n          # LSB^2/Hz, one-sided


def spurs(f, p, k=3):
    base = np.median(p)
    idx = np.argsort(p)[::-1]
    out = []
    for i in idx:
        if f[i] < 0.2e6 or any(abs(f[i] - g) < 0.2e6 for g, _ in out):
            continue
        out.append((f[i], 10 * log10(p[i] / base)))
        if len(out) == k:
            break
    return out


def main():
    global DEPATTERN
    for dp in (False, True):
        DEPATTERN = dp
        run("_clean" if dp else "")


def run(suffix):
    L = []
    say = lambda s="": (print(s), L.append(s))

    # ---------------------------------------------------------------- 1) ADC alone
    say("== ADC alone (internal references, no front end) ==")
    say(f"{'input':<26}{'SAMC':>5}{'mean':>9}{'sigma LSB':>11}{'p-p':>6}{'ENOB_n':>8}{'SNR_FS dB':>11}")
    adc_rows = {}
    names = {15: "AD1AN15 band gap 0.8 V", 14: "AD1AN14 15/16 AVDD", 31: "AD2AN15 band gap", 30: "AD2AN14 15/16 AVDD"}
    for samc in (0, 3):
        for code in (15, 14, 31, 30):
            r = records(f"adc_in{code}_samc{samc}")
            if not r:
                continue
            s, x = sigma(r)
            mean = np.mean([v[64:].mean() for _, v in r])
            adc_rows[(code, samc)] = (mean, s, x)
            say(f"{names[code]:<26}{samc:>5}{mean:>9.1f}{s:>11.2f}{int(x.max() - x.min()):>6}{enob(s):>8.2f}{snr_fs(s):>11.1f}")
    for code in (15, 31):
        if (code, 3) in adc_rows:
            say(f"  -> AVDD from the 0.8 V band gap ({names[code][:7]}, SAMC 3): {0.8 * 4096 / adc_rows[(code, 3)][0]:.3f} V "
                "(band gap spec 0.784-0.816 V, so +/-2 %)")
    s_adc = None
    if (31, 3) in adc_rows:
        s_adc = adc_rows[(31, 3)][1]
    say()

    # ---------------------------------------------------------------- 2) chain at the ADC node
    say("== Chain noise at the ADC node (in 25, no pulse, transducer connected) ==")
    say(f"{'setting':<9}{'G1':>6}{'G2':>6}{'G dB':>7}{'sigma LSB':>11}{'mV rms':>8}{'ENOB_n':>8}{'in-ref @OA1 in uV':>19}{'@LNA in uV':>12}")
    rows = []
    for t in TAGS:
        r = records(f"node_g{t}")
        if not r:
            continue
        s, _ = sigma(r)
        g1, g2 = stage_gains(t)
        G = g1 * g2
        rows.append((t, g1, g2, s, r))
        say(f"g{t:<8}{g1:>6.2f}{g2:>6.2f}{20 * log10(G):>7.1f}{s:>11.2f}{s * LSB_V * 1e3:>8.2f}{enob(s):>8.2f}"
            f"{s * LSB_V / G * 1e6:>19.1f}{s * LSB_V / G / 10 ** (LNA_DB / 20) * 1e6:>12.2f}")

    # least-squares fit of the model (variances are linear in a^2, b^2, c^2)
    A = np.array([[1.0, g2 ** 2, (g1 * g2) ** 2] for _, g1, g2, _, _ in rows])
    y = np.array([s ** 2 for *_, s, _ in rows])
    coef, *_ = np.linalg.lstsq(A, y, rcond=None)
    coef = np.clip(coef, 0, None)
    a, b, c = np.sqrt(coef)
    say()
    say("Model fit sigma^2 = s0^2 + (G2 n2)^2 + (G1 G2 n1)^2 (LSB):")
    say(f"  s0 (ADC + after-OA2 noise) = {a:.2f} LSB = {a * LSB_V * 1e3:.2f} mV rms"
        + (f"   (ADC alone measured {s_adc:.2f} LSB)" if s_adc else ""))
    say(f"  n2 (added at OA2 input)    = {b:.2f} LSB = {b * LSB_V * 1e6:.0f} uV rms")
    say(f"  n1 (at OA1 input = LNA out)= {c:.2f} LSB = {c * LSB_V * 1e6:.0f} uV rms"
        f"  -> at LNA input (/{LNA_DB:.0f} dB) {c * LSB_V / 10 ** (LNA_DB / 20) * 1e6:.1f} uV rms")
    for t, g1, g2, s, _ in rows:
        pred = sqrt(a * a + (g2 * b) ** 2 + (g1 * g2 * c) ** 2)
        share = (g1 * g2 * c) ** 2 / pred ** 2 * 100
        L.append(f"  g{t}: measured {s:.2f}, model {pred:.2f} LSB, front-end (n1) share {share:.0f} %")
    print("\n".join(L[-len(rows):]))
    say()

    # ---------------------------------------------------------------- 3) taps
    say("== Taps (no pulse) ==")
    for name, what in (("lna", "AD1AN1 LNA out (OA1IN+)"), ("oa1", "AD1AN0 OA1OUT")):
        for t in ("011", "000", "300"):
            r = records(f"{name}_g{t}")
            if r:
                s, _ = sigma(r)
                say(f"  {what:<25} g{t}: sigma {s:.2f} LSB = {s * LSB_V * 1e6:.0f} uV rms, mean {np.mean([v.mean() for _, v in r]):.0f}")
    say()

    # ---------------------------------------------------------------- 4) spectra (input-referred at the OA1 input)
    say("== Noise spectra, input-referred to the OA1 input (= LNA output) ==")
    fig, ax = plt.subplots(figsize=(9.5, 5.2))
    band = None
    for t, g1, g2, s, r in rows:
        if t not in ("011", "010", "000", "100", "300"):
            continue
        f, p = welch(r)
        G = g1 * g2
        dens = np.sqrt(p) * LSB_V / G * 1e9          # nV/rtHz at OA1 input
        ax.semilogy(f / 1e6, dens, lw=1, label=f"g{t} ({20 * log10(G):.0f} dB)")
        m = (f > 2e6) & (f < 5e6)
        band = np.median(dens[m])
        sp = ", ".join(f"{fx / 1e6:.2f} MHz +{db:.0f} dB" for fx, db in spurs(f, p))
        say(f"  g{t}: median 2-5 MHz {band:.0f} nV/rtHz at OA1 in = {band / 10 ** (LNA_DB / 20):.1f} nV/rtHz at LNA in; top spurs: {sp}")
    rl = records("lna_g011")
    if rl:
        f, p = welch(rl)
        ax.semilogy(f / 1e6, np.sqrt(p) * LSB_V * 1e9, color="#d9534f", lw=0.8, label="LNA tap AD1AN1 as read (not /G)")
        say(f"  LNA tap AD1AN1 (as read by the ADC): median 2-5 MHz {np.median(np.sqrt(p)[(f > 2e6) & (f < 5e6)]) * LSB_V * 1e9:.0f} nV/rtHz, flat to Nyquist = wideband (aliased) noise")
    if s_adc is not None:
        f, p = welch(records("adc_in31_samc3"))
        ax.semilogy(f / 1e6, np.sqrt(p) * LSB_V * 1e9, "k--", lw=0.8, label="ADC alone (AD2AN15, not divided by G)")
    ax.axvspan(2, 5, color="0.85", alpha=0.5, zorder=0); ax.text(2.1, ax.get_ylim()[0] * 1.3, "transducer band", fontsize=8)
    ax.set_xlabel("frequency (MHz)"); ax.set_ylabel("noise density at OA1 input (nV/√Hz)")
    ax.set_title("board 3 RX noise, input-referred to OA1 in (= LNA out), Welch 512 pt" + (" · period-4 pattern removed" if suffix else " · as captured"), fontsize=10)
    ax.grid(alpha=0.3, which="both"); ax.legend(fontsize=8)
    fig.tight_layout(); fig.savefig(D / f"noise_psd{suffix}.png", dpi=110); plt.close(fig)
    say()

    # ---------------------------------------------------------------- 5) noise vs gain plot
    fig, ax = plt.subplots(figsize=(8.5, 5))
    Gs = np.array([g1 * g2 for _, g1, g2, _, _ in rows]); S = np.array([s for *_, s, _ in rows])
    ax.loglog(Gs, S, "o", color="#2f6db5", label="measured (ADC node)")
    gg = np.logspace(0, np.log10(150), 100)
    ax.loglog(gg, np.sqrt(a * a + (gg * c) ** 2), "-", color="#e08a2e", lw=1, label="model, both stages (G2·n2 folded)")
    if s_adc:
        ax.axhline(s_adc, color="k", ls="--", lw=0.8, label=f"ADC alone {s_adc:.2f} LSB")
    for t, g1, g2, s, _ in rows:
        ax.annotate(f"g{t}", (g1 * g2, s), textcoords="offset points", xytext=(4, -10), fontsize=7)
    sec = ax.secondary_yaxis("right", functions=(lambda s: 12 - np.log2(np.maximum(s, 1e-3) * sqrt(12)),
                                                 lambda e: 2 ** (12 - e) / sqrt(12)))
    sec.set_ylabel("noise-limited ENOB (bits)")
    ax.set_xlabel("OA1 × OA2 gain (measured, linear)"); ax.set_ylabel("output noise σ (LSB)")
    ax.set_title("output noise and noise-limited ENOB vs gain · board 3" + (" · period-4 pattern removed" if suffix else " · as captured"), fontsize=10)
    ax.grid(alpha=0.3, which="both"); ax.legend(fontsize=8)
    fig.tight_layout(); fig.savefig(D / f"noise_vs_gain{suffix}.png", dpi=110); plt.close(fig)

    # ---------------------------------------------------------------- 6) ADC histograms
    if adc_rows:
        fig, axes = plt.subplots(1, len([k for k in adc_rows if k[1] == 3]), figsize=(12, 3.2))
        for ax, key in zip(np.atleast_1d(axes), [k for k in adc_rows if k[1] == 3]):
            mean, s, x = adc_rows[key]
            vals = np.round(x + mean).astype(int)
            lo, hi = vals.min(), vals.max()
            ax.hist(vals, bins=np.arange(lo - 0.5, hi + 1.5), color="#2f6db5")
            ax.set_title(f"{names[key[0]]}\nσ {s:.2f} LSB · ENOB_n {enob(s):.2f}", fontsize=8)
            ax.set_xlabel("code")
        fig.suptitle("ADC alone, SAMC 3, 3 × 4031 samples each", fontsize=10)
        fig.tight_layout(); fig.savefig(D / f"adc_hist{suffix}.png", dpi=110); plt.close(fig)

    # ---------------------------------------------------------------- 7) echo SNR from the gain sweep
    say("== Echo SNR (gain sweep captures, echo pp vs the chain noise at that gain) ==")
    noise = {t: s for t, _, _, s, _ in rows}
    for t in TAGS:
        p = GAIN_DIR / f"pe_g{t}_in25.txt"
        if not p.exists() or t not in noise:
            continue
        fs, v = load(p)
        cells = []
        for e in (40.7, 80.5, 120.7, 161.0):
            i0, i1 = int((e - 5) * 1e-6 * fs), int((e + 5) * 1e-6 * fs)
            seg = v[i0:i1]
            clip = seg.min() < 60 or seg.max() > 3960
            snr = 20 * log10((seg.max() - seg.min()) / (2 * sqrt(2)) / noise[t])
            cells.append(f"{snr:5.1f}{'*' if clip else ' '}")
        say(f"  g{t}: echo SNR (sine-equivalent, dB) at 41/80/121/161 us: " + "  ".join(cells) + "   (* clipped)")

    hdr = ("### pattern-removed (period-4 fixed pattern subtracted per record = random noise only)" if suffix
           else "### as captured (includes the period-4 fixed pattern at fs/4, fs/2)")
    (D / f"noise_summary{suffix}.txt").write_text(hdr + "\n" + "\n".join(L) + "\n")
    print(f"wrote noise_summary{suffix}.txt, noise_vs_gain{suffix}.png, noise_psd{suffix}.png, adc_hist{suffix}.png")


if __name__ == "__main__":
    main()
