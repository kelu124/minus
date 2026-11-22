"""Would a band-pass (FFT, 2-6 MHz) envelope beat the PIC's rectify-and-average env? Host prototype on the recorded pe shots
(env.npz 'pe_ref', gain x3.2). Envelopes compared: (a) PIC-style |x - mean| integrate-and-dump (dec 8), (b) full-band Hilbert,
(c) FFT band-pass 2-6 MHz + Hilbert. Metric per shot: first-echo peak / rms of the envelope in the echo-free 55-78 us window.
Writes bandpass_env.npz and datasheet/figures/ext_bpenv.pdf. Usage (repo root): /usr/bin/python3 docs/bench/2026-11-22-datasheet-ext/bandpass_env.py"""
import sys
from pathlib import Path
import numpy as np
import matplotlib; matplotlib.use("Agg"); import matplotlib.pyplot as plt
HERE = Path(__file__).resolve().parent; ROOT = HERE.parents[2]
sys.path.insert(0, str(HERE)); sys.path.insert(0, str(ROOT / "python" / "library"))
from minus.live import hilbert_envelope


def bandpass_envelope(y, fs, f1=2e6, f2=6e6, shape="brick", fc=3.3e6, fwhm=2.5e6):
    """FFT band-pass + analytic signal: brick wall f1..f2, raised cosine f1..f2 (1 MHz edges) or Gaussian (fc, FWHM)."""
    n = len(y); Y = np.fft.fft(y - y.mean()); f = np.fft.fftfreq(n, 1 / fs); pos = f > 0
    if shape == "brick":
        H = np.where((f >= f1) & (f <= f2), 1.0, 0.0)
    elif shape == "rc":
        w = 1e6; H = np.zeros(n); H[(f >= f1) & (f <= f2)] = 1
        lo = (f > f1 - w) & (f < f1); H[lo] = 0.5 * (1 - np.cos(np.pi * (f[lo] - (f1 - w)) / w))
        hi = (f > f2) & (f < f2 + w); H[hi] = 0.5 * (1 + np.cos(np.pi * (f[hi] - f2) / w))
    else:
        H = np.exp(-0.5 * ((f - fc) / (fwhm / 2.3548)) ** 2)
    return np.abs(np.fft.ifft(Y * 2 * H * pos))


def pic_env(y, dec=8):
    m = int((int(y.sum()) + len(y) // 2) // len(y)); n = len(y) // dec
    return np.abs(y[:n * dec].astype(np.int64) - m).reshape(n, dec).mean(1)


z = np.load(HERE / "env.npz"); pe = z["pe_ref"].astype(float); dt = float(z["pe_dt_ns"]) * 1e-9; fs = 1 / dt
t = np.arange(pe.shape[1]) * dt * 1e6
q = (t > 55) & (t < 78); e1 = (t > 38) & (t < 52)
res = {}
for name, f in (("pic_env8", lambda y: np.pad(np.repeat(pic_env(y), 8), (0, 7), mode="edge")[:len(y)] * np.pi / 2),   # x pi/2: amplitude units like the others
                ("hilbert_full", hilbert_envelope), ("bandpass_2_6MHz", lambda y: bandpass_envelope(y, fs)),
                ("rc_2_6MHz", lambda y: bandpass_envelope(y, fs, shape="rc")),
                ("gauss_3p3_2p5MHz", lambda y: bandpass_envelope(y, fs, shape="gauss"))):
    E = np.array([f(y) for y in pe]); pk = E[:, e1].max(1); fl = np.sqrt((E[:, q] ** 2).mean(1))
    res[name] = dict(peak=pk.mean(), floor=fl.mean(), snr_db=float(np.mean(20 * np.log10(pk / fl))))
    res[name + "_env0"] = E[0]
    print(f"{name:16s} echo peak {pk.mean():7.1f}  floor rms {fl.mean():6.2f}  peak/floor {np.mean(20*np.log10(pk/fl)):5.1f} dB")
S = np.mean([np.abs(np.fft.rfft((y - y.mean()) * np.hanning(len(y)))) for y in pe], axis=0); fr = np.fft.rfftfreq(len(t), dt) / 1e6
fig, ax = plt.subplots(1, 2, figsize=(7.2, 2.3))
ax[0].semilogy(fr, S, lw=0.5); ax[0].axvspan(2, 6, color="0.85"); ax[0].set_xlabel("MHz"); ax[0].set_title("mean spectrum, 16 pe shots (grey: 2–6 MHz)")
for name, lab in (("pic_env8", "|x−mean| over 8 (×π/2)"), ("hilbert_full", "Hilbert, full band"), ("bandpass_2_6MHz", "brick wall 2–6 MHz"),
                  ("rc_2_6MHz", "raised cosine 2–6 MHz"), ("gauss_3p3_2p5MHz", "Gaussian 3.3 / 2.5 MHz")):
    ax[1].semilogy(t, np.maximum(res[name + "_env0"], 0.3), lw=0.6, label=f"{lab}: {res[name]['snr_db']:.1f} dB")
ax[1].set_xlim(30, 100); ax[1].set_xlabel("time after the pulse (µs)"); ax[1].set_ylabel("envelope (LSB)"); ax[1].legend(fontsize=6)
ax[1].set_title("one shot; legend = first-echo peak / floor (55–78 µs)")
fig.tight_layout(); fig.savefig(ROOT / "datasheet" / "figures" / "ext_bpenv.pdf"); plt.close(fig)
np.savez_compressed(HERE / "bandpass_env.npz", **{k: (np.array([v["peak"], v["floor"], v["snr_db"]]) if isinstance(v, dict) else v)
                                                  for k, v in res.items()}, columns=np.array(["peak", "floor_rms", "peak_over_floor_db"]))
