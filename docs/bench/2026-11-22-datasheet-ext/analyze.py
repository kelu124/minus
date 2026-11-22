"""Analysis for datasheet rev 0.3: reads the .npz files of campaign.py, writes datasheet/figures/ext_*.pdf and
datasheet/ext_values.tex (LaTeX macros, letters only). Run from the repo root:
    /usr/bin/python3 docs/bench/2026-11-22-datasheet-ext/analyze.py
"""
import json, sys
from pathlib import Path
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
FIG = ROOT / "datasheet" / "figures"
sys.path.insert(0, str(ROOT / "python" / "library"))
from minus.live import hilbert_envelope  # noqa: E402

V = {}                                  # macro name -> text
plt.rcParams.update({"font.size": 8, "axes.titlesize": 8, "axes.labelsize": 8, "legend.fontsize": 7,
                     "xtick.labelsize": 7, "ytick.labelsize": 7, "lines.linewidth": 0.8})


def load(name):
    p = HERE / f"{name}.npz"
    return np.load(p, allow_pickle=False) if p.exists() else None


def v(name, val, fmt="{:.1f}"):
    V[name] = fmt.format(val) if not isinstance(val, str) else val


def pic_env(y, dec):
    """The PIC's ENV algorithm (firmware/pic32/pe_ext.c pe_env), one shot, in LSB: mean over all 4095 samples (rounded),
    |x - mean|, integrate-and-dump over dec samples, rounded to 1/16 LSB."""
    m = int((int(y.sum()) + len(y) // 2) // len(y))
    n = len(y) // dec
    s = np.abs(y[:n * dec].astype(np.int64) - m).reshape(n, dec).sum(1)
    return np.floor((s * 16 + dec // 2) / dec) / 16.0


meta = None
# ------------------------------------------------------------------------------------------------ pe reference
z = load("pe_ref")
if z is not None:
    meta = json.loads(str(z["meta"]))
    y = z["g010"].astype(float); dt = float(z["g010_dt_ns"].mean()); t = np.arange(4095) * dt / 1000
    e = np.mean([hilbert_envelope(s) for s in y], axis=0)
    m1 = (t > 38) & (t < 52); i1 = np.argmax(np.where(m1, e, 0))
    m2 = (t > 80) & (t < 102); i2 = np.argmax(np.where(m2, e, 0))
    v("xEchoAt", t[i1]); v("xEchoAmp", e[i1], "{:.0f}"); v("xEchoBt", t[i2]); v("xEchoBamp", e[i2], "{:.0f}")
    v("xEchoAmm", t[i1] * 0.77, "{:.1f}"); v("xNoiseQuiet", np.mean([s[(t > 55) & (t < 78)].std() for s in y]), "{:.1f}")
    v("xRefGain", float(z["g010_total"]), "{:.1f}")

# ------------------------------------------------------------------------------------------------ link
z = load("link")
if z is not None:
    tab = z["table"]
    rows = []
    for r in tab:
        mhz, cnt, ok, fe, pe_, mean, mn, mx, rdy, wire, uart = r
        rows.append(f"{mhz:g} & {int(ok)}/{int(cnt)} & {int(fe)} & {mean / 1000:.2f} & {rdy:.0f} & {wire / 1000:.2f} & "
                    f"{'yes' if uart else 'no'}\\\\")
    V["xLinkRows"] = "\n".join(rows)
    v("xLinkMeanA", tab[0, 5] / 1000, "{:.1f}")
z = load("fmt")
if z is not None:
    v("xFmtText", np.median(z["text_s"]) * 1000, "{:.0f}"); v("xFmtBsix", np.median(z["b64_s"]) * 1000, "{:.0f}")
    v("xFmtTextKB", int(z["text_chars"]) / 1000, "{:.1f}"); v("xFmtBsixKB", int(z["b64_chars"]) / 1000, "{:.1f}")

# ------------------------------------------------------------------------------------------------ lock
z = load("lock")
if z is not None:
    tab = z["table"]
    v("xLockBoots", len(tab), "{:d}"); v("xLockOk", int((tab[:, 3] == 20).sum()), "{:d}")
    v("xLockMax", int(tab[:, 1].max()), "{:d}"); v("xLockMean", tab[:, 1].mean(), "{:.1f}")
    v("xLockFirst", int((tab[:, 1] == 1).sum()), "{:d}")

# ------------------------------------------------------------------------------------------------ DAC
z = load("dac")
if z is not None and "dc_codes" in z.files:
    codes = z["dc_codes"].astype(float); adc = z["dc_adc"]
    pfit = np.polyfit(codes, adc, 1); inl = adc - np.polyval(pfit, codes)
    v("xDacGain", pfit[0], "{:.4f}"); v("xDacOff", pfit[1], "{:.0f}"); v("xDacInl", np.abs(inl).max(), "{:.0f}")
    tri = z["tri_spi"].astype(float); dt = float(z["tri_dt_ns"]); t = np.arange(4095) * dt / 1000
    pers = []
    for s_ in tri:
        c = s_ - (s_.max() + s_.min()) / 2; i = np.where((c[:-1] < 0) & (c[1:] >= 0))[0]
        tc = t[i] + (t[i + 1] - t[i]) * (-c[i]) / (c[i + 1] - c[i]); pers += list(np.diff(tc))
    v("xTriPer", np.mean(pers), "{:.2f}"); v("xTriLo", tri.min(1).mean(), "{:.0f}"); v("xTriHi", tri.max(1).mean(), "{:.0f}")
    v("xSineSlow", int(z["sine_slow"]), "{:d}"); v("xSineN", int(z["sine_n"]), "{:d}")
    fig, ax = plt.subplots(2, 2, figsize=(7.2, 4.4))
    ax[0, 0].plot(codes, adc, "o", ms=3); ax[0, 0].plot(codes, np.polyval(pfit, codes), lw=0.6)
    a2 = ax[0, 0].twinx(); a2.plot(codes, inl, "r.-", lw=0.5, ms=3); a2.set_ylabel("deviation from the line (LSB)", color="r")
    ax[0, 0].set_xlabel("DAC code"); ax[0, 0].set_ylabel("ADC code (mean)"); ax[0, 0].set_title("dac dc sweep, read by ADC2 (AD2AN3)")
    ax[0, 1].plot(t, tri[0], lw=0.6, label="SPI link"); ax[0, 1].plot(t, z["tri_uart"][0], lw=0.6, ls="--", label="UART")
    ax[0, 1].set_xlabel("time (µs)"); ax[0, 1].set_title(f"dac tri 512 3584 16: period {np.mean(pers):.2f} µs"); ax[0, 1].legend(fontsize=6)
    key = "sine800_div20" if "sine800_div20" in z.files else None
    if key:
        sd = float(z["sine_dt_ns"]); y = z[key][0].astype(float); ts = np.arange(4095) * sd * 1e-9
        best = None
        for f0 in np.linspace(19000, 21000, 801):
            A = np.column_stack([np.sin(2 * np.pi * f0 * ts), np.cos(2 * np.pi * f0 * ts), np.ones(4095)])
            cc, r, *_ = np.linalg.lstsq(A, y, rcond=None)
            if best is None or r[0] < best[0]: best = (r[0], f0, cc)
        _, f0, cc = best; A = np.column_stack([np.sin(2 * np.pi * f0 * ts), np.cos(2 * np.pi * f0 * ts), np.ones(4095)])
        fit = A @ cc; res = y - fit; amp = np.hypot(cc[0], cc[1]); sinad = 20 * np.log10(amp / np.sqrt(2) / res.std())
        v("xSineF", f0 / 1000, "{:.2f}"); v("xSineAmp", amp, "{:.0f}"); v("xSineRes", res.std(), "{:.1f}"); v("xSineSinad", sinad, "{:.1f}")
        v("xSineDt", sd, "{:.1f}")
        ax[1, 0].plot(ts * 1e6, y, lw=0.6, label="capture"); ax[1, 0].plot(ts * 1e6, res + y.min() - 60, lw=0.5, label="residual (offset)")
        ax[1, 0].set_xlabel("time (µs)"); ax[1, 0].set_title(f"dac sine 20000 800, acq 20 (10 Msps): {f0/1000:.2f} kHz, {sinad:.1f} dB SINAD")
        ax[1, 0].legend(fontsize=6)
        S = np.abs(np.fft.rfft((y - y.mean()) * np.hanning(4095))); fr = np.fft.rfftfreq(4095, sd * 1e-9) / 1e3
        ax[1, 1].semilogy(fr, S / S.max(), lw=0.5); ax[1, 1].set_xlim(0, 400); ax[1, 1].set_xlabel("kHz")
        ax[1, 1].set_title("its spectrum (staircase images at multiples of 1 MHz / 50 points)")
    fig.tight_layout(); fig.savefig(FIG / "ext_dac.pdf"); plt.close(fig)

# ------------------------------------------------------------------------------------------------ envbp
z = load("envbp")
if z is not None:
    dt = float(z["dt_ns"]); n = z["env_s1"].shape[1]; te = np.arange(n) * dt / 1000
    q = (te > 55) & (te < 78); e1 = (te > 38) & (te < 52)
    def db(a):                                          # mean over runs of peak / floor rms
        return np.mean([20 * np.log10(r[e1].max() / np.sqrt((r[q] ** 2).mean())) for r in a])
    rows = []
    for lab, k1, k16 in [("env (|x−mean|)", "env_s1", "env_s16")] + \
            [(f"envbp {fc} / {bw}", f"bp_f{fc}_b{bw}_s1", f"bp_f{fc}_b{bw}_s16") for fc, bw in ((3300, 1500), (3300, 2500), (3300, 4000), (4000, 4000))]:
        a1, a16 = z[k1], z[k16]
        rows.append(f"{lab} & {a1[:, e1].max(1).mean():.0f} & {np.sqrt((a1[:, q] ** 2).mean(1)).mean():.2f} & {db(a1):.1f} & "
                    f"{np.sqrt((a16[:, q] ** 2).mean(1)).mean():.2f} & {db(a16):.1f}\\\\")
    V["xBpRows"] = "\n".join(rows)
    v("xBpGain", db(z["bp_f3300_b2500_s1"]) - db(z["env_s1"]), "{:.1f}")
    v("xBpTime", np.median(z["time_s1"]) * 1000, "{:.0f}")
    fig, ax = plt.subplots(1, 1, figsize=(7.0, 2.3))
    ax.semilogy(te, np.maximum(z["env_s1"][0] * np.pi / 2, 0.1), lw=0.6, label="env 8 (×π/2), 1 shot")
    ax.semilogy(te, np.maximum(z["bp_f3300_b2500_s1"][0], 0.1), lw=0.6, label="envbp 8 (3.3 / 2.5 MHz), 1 shot")
    ax.semilogy(te, np.maximum(z["bp_f3300_b2500_s16"].mean(0), 0.1), lw=0.8, label="envbp 8, 16 shots")
    ax.set_xlabel("time after the pulse (µs)"); ax.set_ylabel("envelope (LSB)"); ax.legend(fontsize=6, loc="upper right")
    ax.set_title("on-PIC envelopes on the echoes, gain ×3.2: band-pass removes the out-of-band floor")
    fig.tight_layout(); fig.savefig(FIG / "ext_envbp.pdf"); plt.close(fig)

# ------------------------------------------------------------------------------------------------ acqos
z = load("acqos")
if z is not None:
    k = {"acq": 1, "os4": 2, "os16": 4}
    for name, mac in (("acq", "xOsNoiseA"), ("os4", "xOsNoiseB"), ("os16", "xOsNoiseC")):
        v(mac, np.mean([(s.astype(float) / k[name])[64:].std() for s in z[f"dc_{name}"]]), "{:.2f}")
    v("xOsDtB", float(z["dc_os4_dt_ns"]), "{:.0f}"); v("xOsDtC", float(z["dc_os16_dt_ns"]), "{:.0f}")
    fig, ax = plt.subplots(1, 2, figsize=(7.0, 2.1))
    names = ["acq\n40 ns", "acqos 4\n186 ns", "acqos 16\n565 ns"]
    ax[0].bar(names, [float(V["xOsNoiseA"]), float(V["xOsNoiseB"]), float(V["xOsNoiseC"])], color="0.4")
    ax[0].set_ylabel("noise (LSB rms, 12-bit units)"); ax[0].set_title("DAC DC level on AD2AN3")
    for name, lab in (("pe", "pe (25 Msps)"), ("os4", "acqos 4 25 1"), ("os16", "acqos 16 25 1")):
        dtn = float(z[f"echo_{name}_dt_ns"]); s = z[f"echo_{name}"][0].astype(float) / k["acq" if name == "pe" else name]
        tt = np.arange(4095) * dtn / 1000; m = (tt > 36) & (tt < 56)
        ax[1].plot(tt[m], s[m] - np.median(s), label=lab, lw=0.6 if name == "pe" else 1.0)
    ax[1].set_xlabel("time after the pulse (µs)"); ax[1].set_ylabel("12-bit LSB, minus median")
    ax[1].set_title("first echo: oversampling kills the 3.3 MHz RF"); ax[1].legend(loc="lower right", fontsize=6)
    fig.tight_layout(); fig.savefig(FIG / "ext_acqos.pdf"); plt.close(fig)
    def echo_pk(name, k):                                 # peak |x - median| inside the first-echo window only (38-52 us)
        dtn = float(z[f"echo_{name}_dt_ns"]); tt = np.arange(4095) * dtn / 1000; m = (tt > 38) & (tt < 52)
        a = z[f"echo_{name}"].astype(float) / k
        return np.mean([np.abs(r[m] - np.median(r)).max() for r in a])
    pe_pk = echo_pk("pe", 1)
    v("xOsEchoRatioB", echo_pk("os4", 2) / pe_pk * 100, "{:.0f}"); v("xOsEchoRatioC", echo_pk("os16", 4) / pe_pk * 100, "{:.0f}")

# ------------------------------------------------------------------------------------------------ tof
z = load("tof")
if z is not None:
    tab = z["table"]; dt = float(z["pe_dt_ns"]); ref = z["pe_ref"].astype(float)
    blank = 25000 // 40
    fig, ax = plt.subplots(1, 1, figsize=(6.5, 2.0))
    rows = []
    for j, thr in enumerate(np.unique(tab[:, 0])):
        r = tab[tab[:, 0] == thr]; found = r[:, 1] >= 0; tt = r[found, 1] * r[found, 6] / 1000
        host = []
        for s in ref:                                     # the same search on host-side pe captures
            m = s.mean(); i = np.where(np.abs(s[blank:] - m) > thr)[0]
            if len(i): host.append((blank + i[0]) * dt / 1000)
        host = np.array(host)
        rows.append(f"{thr:.0f} & {found.mean() * 100:.0f} & {tt.mean():.2f} & {tt.std() * 1000:.0f} & "
                    f"{(r[found, 3]).mean():.0f} & {host.mean() if len(host) else float('nan'):.2f} & "
                    f"{host.std() * 1000 if len(host) else float('nan'):.0f} & {r[:, 5].mean() * 100:.0f}\\\\")
        ax.hist(tt, bins=np.arange(41.0, 44.0, 0.04), alpha=0.6, label=f"thr {thr:.0f} (PIC)")
        ax.plot(host, np.full(len(host), -1 - j), "|", ms=6)
    ax.set_xlabel("first crossing after the 25 µs blank (µs)"); ax.set_ylabel("shots (bars); host check (ticks below)")
    ax.set_title("tof on the first echo, 50 shots per threshold, gain ×3.2"); ax.legend(ncol=4, loc="upper left")
    fig.tight_layout(); fig.savefig(FIG / "ext_tof.pdf"); plt.close(fig)
    V["xTofRows"] = "\n".join(rows)
    v("xTofTime", np.median(z["tof_time_s"]) * 1000, "{:.1f}")

# ------------------------------------------------------------------------------------------------ env (step by step)
z = load("env")
if z is not None:
    pe = z["pe_ref"].astype(np.int64); dt = float(z["pe_dt_ns"]); t = np.arange(4095) * dt / 1000
    dec = 8; y = pe[0]; m = int((int(y.sum()) + 2047) // 4095)
    em = pic_env(y, dec); te = np.arange(len(em)) * dt * dec / 1000
    pic1 = z["env_d8_s1"][0]; pic16 = z["env_d8_s16"].mean(0)
    host16 = np.mean([pic_env(s, dec) for s in pe], axis=0)
    hil = np.mean([hilbert_envelope(s.astype(float)) for s in pe], axis=0)
    fig, ax = plt.subplots(4, 1, figsize=(7.0, 6.0), sharex=True)
    w = (t > 38) & (t < 56); we = (te > 38) & (te < 56)
    ax[0].plot(t[w], y[w], lw=0.6); ax[0].axhline(m, color="r", lw=0.6)
    ax[0].set_ylabel("1. capture\n(ADC code)"); ax[0].set_title(f"on-PIC envelope (env {dec}), first echo; red = capture mean {m}")
    ax[1].plot(t[w], np.abs(y[w] - m), lw=0.6); ax[1].set_ylabel("2. |x − mean|\n(LSB)")
    ax[2].step(te[we], em[we], where="post", label="host emulation of this shot"); ax[2].step(te[we], pic1[we], where="post",
                                                                                         label="PIC env (another shot)")
    ax[2].set_ylabel(f"3. mean over\n{dec} samples (LSB)"); ax[2].legend(loc="upper right")
    ax[3].plot(te[we], pic16[we], label="PIC env, 16 shots (mean of 5 runs)")
    ax[3].plot(te[we], host16[we], label="host emulation, 16 pe shots", ls="--")
    ax[3].plot(t[w], hil[w] * 2 / np.pi, label="host Hilbert |analytic| × 2/π, 16 shots", lw=0.6)
    ax[3].set_ylabel("4. average over\nshots (LSB)"); ax[3].set_xlabel("time after the pulse (µs)"); ax[3].legend(loc="upper right")
    fig.tight_layout(); fig.savefig(FIG / "ext_env_steps.pdf"); plt.close(fig)
    # agreement PIC vs host emulation (16-shot means), and noise floor vs shots
    c = np.corrcoef(pic16, host16)[0, 1]; v("xEnvCorr", c, "{:.3f}")
    k = (te > 38) & (te < 52); v("xEnvRatio", pic16[k].sum() / host16[k].sum() * 100, "{:.0f}")
    rows = []
    fig, ax = plt.subplots(1, 1, figsize=(4.2, 2.1))
    for dd in (4, 8, 16, 32):
        dte = float(z[f"env_d{dd}_dt_ns"]); tt = np.arange(4095 // dd) * dte / 1000; q = (tt > 55) & (tt < 78)
        pk = (tt > 38) & (tt < 52)
        cells, nf = [], []
        for sh in (1, 4, 16):                             # random part: spread across the 5 runs, per point, in the quiet region
            a = z[f"env_d{dd}_s{sh}"]
            fl = float(a[:, q].std(0).mean()); nf.append(fl)
            cells.append(f"{a[:, q].mean():.1f} / {fl:.2f}")
        peak = z[f"env_d{dd}_s16"][:, pk].max(1).mean()
        rows.append(f"{dd} & {dte:.0f} & {4095 // dd} & " + " & ".join(cells) + f" & {peak:.0f}\\\\")
        ax.plot([1, 4, 16], nf, "o-", label=f"dec {dd}")
    ax.set_xscale("log", base=2); ax.set_yscale("log"); ax.set_xticks([1, 4, 16]); ax.set_xticklabels(["1", "4", "16"])
    ax.plot([1, 16], [nf[0] * 1.0 / 1, nf[0] / 4], "k:", lw=0.6, label="1/√N")
    ax.set_xlabel("shots averaged"); ax.set_ylabel("run-to-run spread (LSB rms)"); ax.legend(fontsize=6)
    ax.set_title("env noise floor, 55–78 µs (no echo)")
    fig.tight_layout(); fig.savefig(FIG / "ext_env_shots.pdf"); plt.close(fig)
    V["xEnvRows"] = "\n".join(rows)
    v("xEnvTimeA", np.median(z["time_s1"]) * 1000, "{:.0f}"); v("xEnvTimeB", np.median(z["time_s16"]) * 1000, "{:.0f}")

# ------------------------------------------------------------------------------------------------ tgc
z = load("tgc")
if z is not None:
    dt = float(z["dt_ns"]); t = np.arange(4095) * dt / 1000
    ts = float(z["step_us"]) if "step_us" in z.files else 30.0
    key = "step_leg2" if "step_leg2" in z.files else "step30_leg2"
    env = {k: np.mean([hilbert_envelope(s.astype(float)) for s in z[kk]], axis=0)
           for k, kk in (("off", "off"), ("step", key), ("const", "leg2_const"))}
    fig, ax = plt.subplots(1, 1, figsize=(7.0, 2.2))
    for k, lab in (("off", "gain 0 0 0 (×10)"), ("step", f"×10, tgc {ts:.0f} 2 (→ ×61 at {ts:.0f} µs)"), ("const", "gain 2 0 0 (×61)")):
        ax.semilogy(t, np.maximum(env[k], 0.5), label=lab)
    ax.axvspan(ts, ts + 17, color="0.85"); ax.set_xlabel("time after the pulse (µs)"); ax.set_ylabel("mean envelope (LSB)")
    ax.set_title(f"time-gain step at {ts:.0f} µs on the echoes (16 shots each; grey = switch transient)"); ax.legend(loc="upper right")
    fig.tight_layout(); fig.savefig(FIG / "ext_tgc.pdf"); plt.close(fig)
    v("xTgcAt", ts, "{:.0f}"); v("xTgcEnd", ts + 17, "{:.0f}")
    def ratio(a, b, k):
        w = (t > a) & (t < b); return env[k][w].max() / env["off"][w].max()
    v("xTgcBefore", ratio(38, 52, "step"), "{:.2f}")                        # first echo: before the step, unchanged
    v("xTgcInB", ratio(80, 92, "step"), "{:.1f}"); v("xTgcInBc", ratio(80, 92, "const"), "{:.1f}")   # second echo (in the transient?)
    v("xTgcRatio", ratio(118, 140, "step"), "{:.1f}"); v("xTgcConst", ratio(118, 140, "const"), "{:.1f}")   # third echo, after it

# ------------------------------------------------------------------------------------------------ period-4 pattern
z = load("pc")
if z is not None:
    def phase_dev(a):                                     # per capture: phase means minus overall mean, samples 64..
        out = []
        for s in a.astype(float):
            q = s[64:]; ph = np.arange(64, 4095) & 3
            pm = np.array([q[ph == k].mean() for k in range(4)]); out.append(pm - q.mean())
        return np.array(out)
    raw, cor = phase_dev(z["raw"]), phase_dev(z["corrected"])
    rr = np.sqrt((raw ** 2).mean(1)); rc = np.sqrt((cor ** 2).mean(1))
    v("xPcRaw", np.median(rr), "{:.1f}"); v("xPcCor", np.median(rc), "{:.2f}")
    v("xPcLow", np.median(raw.min(1)), "{:.0f}"); v("xPcBad", (rc > 2).mean() * 100, "{:.0f}")
    v("xPcN", len(rc), "{:d}")
    rot = np.array([np.roll(r, -int(np.argmin(r))) for r in raw])         # align on the low phase
    fig, ax = plt.subplots(1, 3, figsize=(7.2, 2.0))
    ax[0].plot(range(4), rot.T, color="0.6", lw=0.5); ax[0].plot(range(4), np.median(rot, 0), "k-o", ms=3)
    ax[0].set_xticks(range(4)); ax[0].set_xlabel("phase (rotated: low phase first)"); ax[0].set_ylabel("phase mean − mean (LSB)")
    ax[0].set_title(f"raw pattern, {len(rr)} captures")
    ax[1].hist(rr, bins=20, alpha=0.7, label="raw (pc 0)"); ax[1].hist(rc, bins=20, alpha=0.7, label="corrected (pc 1)")
    ax[1].set_xlabel("pattern rms (LSB)"); ax[1].legend(); ax[1].set_title("per capture")
    f = np.fft.rfftfreq(4095, 40.2e-9) / 1e6
    for a, lab in ((z["raw"], "pc 0"), (z["corrected"], "pc 1")):
        S = np.mean([np.abs(np.fft.rfft((s.astype(float) - s.mean()) * np.hanning(4095))) for s in a], axis=0)
        ax[2].semilogy(f, S, lw=0.5, label=lab)
    ax[2].set_xlabel("MHz"); ax[2].set_title("spectrum: fs/4 = 6.2, fs/2 = 12.4 MHz"); ax[2].legend()
    fig.tight_layout(); fig.savefig(FIG / "ext_pc.pdf"); plt.close(fig)

z = load("live")
if z is not None:
    v("xLiveFpsPe", float(z["pe_fps"]), "{:.0f}"); v("xLiveFpsBp", float(z["envbp_fps"]), "{:.0f}")

# ------------------------------------------------------------------------------------------------ period-4: the signal itself
z = load("pc")
if z is not None:
    def pc_host(y):
        """The PIC's correction (acq.c acq_pc_apply) on the host: phase means over samples 64.. minus the overall mean, in
        1/16 LSB, subtracted from every sample, rounded, clamped."""
        q = y[64:].astype(np.int64); ph = np.arange(64, len(y)) & 3; n = len(q); tot = int(q.sum())
        off = np.zeros(4, dtype=np.int64)
        for k in range(4):
            sk, ck = int(q[ph == k].sum()), int((ph == k).sum())
            a_ = sk * 16 * n - tot * 16 * ck; d_ = ck * n
            off[k] = (a_ + d_ // 2) // d_ if a_ >= 0 else -((-a_ + d_ // 2) // d_)
        v_ = y.astype(np.int64) * 16 - off[np.arange(len(y)) & 3]
        v_ = np.where(v_ >= 0, (v_ + 8) // 16, -((-v_ + 8) // 16))
        return np.clip(v_, 0, 4095), off / 16.0
    raw = z["raw"]; cor_pic = z["corrected"].astype(float)
    hc = [pc_host(r) for r in raw]; cor_host = np.array([h[0] for h in hc], dtype=float); offs_host = np.array([h[1] for h in hc])
    def half_low(y):                                       # low phase in the first and in the second half of a capture
        out = []
        for lo, hi in ((64, 2048), (2048, 4095)):
            q = y[lo:hi].astype(float); ph = np.arange(lo, hi) & 3
            out.append(int(np.argmin([q[ph == k].mean() for k in range(4)])))
        return out
    halves = np.array([half_low(r) for r in raw]); slipped = halves[:, 0] != halves[:, 1]
    v("xPcSlip", slipped.mean() * 100, "{:.0f}"); v("xPcSlipN", int(slipped.sum()), "{:d}")
    resid = np.array([np.sqrt(((np.array([c[64:][(np.arange(64, 4095) & 3) == k].mean() for k in range(4)]) - c[64:].mean()) ** 2).mean())
                      for c in cor_host])
    clean = [i for i in np.argsort(resid) if not slipped[i]]
    ic = clean[0] if clean else 0
    isl = int(np.where(slipped)[0][0]) if slipped.any() else None
    y0, c0, o0 = raw[ic].astype(float), cor_host[ic], offs_host[ic]
    lowk = int(np.argmin(o0))
    v("xPcHostRaw", np.mean([r[64:].std() for r in raw.astype(float)]), "{:.2f}")
    v("xPcHostCor", np.mean([r[64:].std() for r in cor_host]), "{:.2f}")
    v("xPcPicCor", np.mean([r[64:].std() for r in cor_pic]), "{:.2f}")
    v("xPcOffA", o0[0], "{:+.2f}"); v("xPcOffB", o0[1], "{:+.2f}"); v("xPcOffC", o0[2], "{:+.2f}"); v("xPcOffD", o0[3], "{:+.2f}")
    fig, ax = plt.subplots(3, 2, figsize=(7.2, 6.4))
    ax = np.vstack([ax[0], ax[1], ax[2]])
    i0 = 1000; idx = np.arange(i0, i0 + 40)
    ax[0, 0].plot(idx, y0[idx], "o-", ms=2.5, lw=0.5, label="raw (pc 0)")
    ax[0, 0].plot(idx[(idx & 3) == lowk], y0[idx][(idx & 3) == lowk], "rs", ms=3.5, mfc="none", label=f"phase {lowk} (low)")
    ax[0, 0].plot(idx, c0[idx], "o-", ms=2.5, lw=0.5, label="corrected on the host")
    ax[0, 0].set_xlabel("sample index"); ax[0, 0].set_ylabel("ADC code"); ax[0, 0].set_title("one capture, 40 samples (no pulse, ×10)")
    ax[0, 0].legend(fontsize=6)
    for k in range(4):
        ax[0, 1].hist(y0[64:][(np.arange(64, 4095) & 3) == k] - y0[64:].mean(), bins=np.arange(-50, 30, 2), histtype="step", label=f"phase {k}")
    ax[0, 1].set_xlabel("raw sample − capture mean (LSB)"); ax[0, 1].set_title(f"raw, per phase: offsets {np.round(o0, 1)} LSB"); ax[0, 1].legend(fontsize=6)
    for k in range(4):
        ax[1, 0].hist(c0[64:][(np.arange(64, 4095) & 3) == k] - c0[64:].mean(), bins=np.arange(-50, 30, 2), histtype="step", label=f"phase {k}")
    ax[1, 0].set_xlabel("corrected sample − mean (LSB)"); ax[1, 0].set_title("after the correction: the four phases coincide"); ax[1, 0].legend(fontsize=6)
    f = np.fft.rfftfreq(4095, 40.2e-9) / 1e6
    for a_, lab in ((raw.astype(float), "raw"), (cor_host, "host-corrected (same captures)"), (cor_pic, "PIC-corrected (other captures)")):
        S = np.mean([np.abs(np.fft.rfft((r - r.mean()) * np.hanning(4095))) for r in a_], axis=0)
        ax[1, 1].semilogy(f, S, lw=0.5, label=lab)
    ax[1, 1].set_xlabel("MHz"); ax[1, 1].set_title("mean spectra, 40 captures each"); ax[1, 1].legend(fontsize=6)
    if isl is not None:                                    # a slipped capture: the low phase changes inside the record
        ys, cs_ = raw[isl].astype(float), cor_host[isl]
        w = 32; seg = np.arange(64, 4095 - w, w)
        for k in range(4):
            ax[2, 0].plot(seg * 40.2e-3, [ys[i:i + w][(np.arange(i, i + w) & 3) == k].mean() - ys[i:i + w].mean() for i in seg], lw=0.7, label=f"phase {k}")
        ax[2, 0].set_xlabel("time (µs)"); ax[2, 0].set_ylabel("phase mean − local mean"); ax[2, 0].legend(fontsize=6)
        ax[2, 0].set_title(f"a slipped capture (raw): the low phase moves at {halves[isl][0]}→{halves[isl][1]}")
        for k in range(4):
            ax[2, 1].hist(cs_[64:][(np.arange(64, 4095) & 3) == k] - cs_[64:].mean(), bins=np.arange(-50, 30, 2), histtype="step", label=f"phase {k}")
        ax[2, 1].set_xlabel("corrected sample − mean (LSB)"); ax[2, 1].set_title("…after the correction: still two populations"); ax[2, 1].legend(fontsize=6)
    else:
        ax[2, 0].axis("off"); ax[2, 1].axis("off")
    fig.tight_layout(); fig.savefig(FIG / "ext_pc_signal.pdf"); plt.close(fig)
    np.savez_compressed(HERE / "pc_host.npz", raw=raw, corrected_host=cor_host.astype(np.uint16), offsets_host_lsb=offs_host,
                        note=np.array("pc.npz raw captures corrected on the host with the PIC's algorithm (analyze.py pc_host)"))

# ------------------------------------------------------------------------------------------------ write
if meta:
    V["xCampFw"] = f"rp {meta['rp']} / pic {meta['pic']}, proto {meta['proto']}"; V["xCampDate"] = meta["date"]
lines = ["% generated by docs/bench/2026-11-22-datasheet-ext/analyze.py — do not edit"]
for k, val in sorted(V.items()):
    lines.append(f"\\newcommand{{\\{k}}}{{{val}}}")
(ROOT / "datasheet" / "ext_values.tex").write_text("\n".join(lines) + "\n")
print("\n".join(f"{k} = {V[k][:80]}" for k in sorted(V)))
