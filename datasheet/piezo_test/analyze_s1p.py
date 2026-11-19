#!/usr/bin/env python3
"""Characterise the test transducer from its one-port VNA measurement (BiViPiezo.s1p, owner, NanoVNA).

usage (repo root):  /usr/bin/python3 datasheet/piezo_test/analyze_s1p.py
writes datasheet/piezo_values.tex (macros) and datasheet/figures/piezo_impedance.pdf, and prints a report.

- Z = Z0 (1 + S11) / (1 - S11), Z0 from the Touchstone option line.
- Return loss RL = -20 log10 |S11|; the -10 dB band is where RL >= 10 dB (|S11| <= 0.316).
- Series resonance fs = maximum of the conductance G = Re(1/Z); parallel resonance fp = maximum of R = Re(Z);
  phase-zero crossings reported too.
- Matched-probe check: a bare ceramic is capacitive away from resonance; an inductive band-edge susceptance and
  |Z| ~ 50 ohm across the band mean the probe carries a matching network (no Butterworth-Van Dyke fit then).
The measurement is at the VNA port, so it includes whatever cable / adapter was between the VNA and the element.
"""
from pathlib import Path

import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

HERE = Path(__file__).resolve().parent
DS = HERE.parent
src = HERE / "BiViPiezo.s1p"

f, S = [], []
z0, fmt, unit = 50.0, "RI", 1.0
for ln in src.read_text().splitlines():
    ln = ln.split("!")[0].strip()
    if not ln:
        continue
    if ln.startswith("#"):
        tok = ln[1:].upper().split()
        unit = {"HZ": 1, "KHZ": 1e3, "MHZ": 1e6, "GHZ": 1e9}[tok[0]]
        fmt = tok[2]
        z0 = float(tok[tok.index("R") + 1])
        continue
    a, b, c = (float(x) for x in ln.split()[:3])
    f.append(a * unit)
    S.append(complex(b, c) if fmt == "RI" else (b * np.exp(1j * np.radians(c)) if fmt == "MA"
                                                else 10 ** (b / 20) * np.exp(1j * np.radians(c))))
f, S = np.array(f), np.array(S)
Z = z0 * (1 + S) / (1 - S)
Y = 1 / Z
RL = -20 * np.log10(np.abs(S))
ph = np.degrees(np.angle(Z))
fm = f / 1e6
rep = []
say = lambda s: (rep.append(s), print(s))
say(f"{src.name}: {len(f)} points, {fm[0]:.2f}-{fm[-1]:.2f} MHz, Z0 {z0:.0f} ohm")

# return-loss dips
dips = [i for i in range(1, len(f) - 1) if RL[i] >= RL[i - 1] and RL[i] >= RL[i + 1] and RL[i] > 6]
dips = sorted(sorted(dips, key=lambda i: -RL[i])[:2])
for i in dips:
    say(f"RL dip {fm[i]:.3f} MHz: {RL[i]:.1f} dB, Z = {Z[i].real:.1f} {Z[i].imag:+.1f}j ohm")
band = RL >= 10
edges = np.where(band)[0]
f10lo, f10hi = (fm[edges[0]], fm[edges[-1]]) if len(edges) else (np.nan, np.nan)
say(f"-10 dB return-loss band {f10lo:.2f}-{f10hi:.2f} MHz (contiguous: {bool(band[edges[0]:edges[-1] + 1].all()) if len(edges) else False})")

# resonances
iG = int(np.argmax(Y.real)); iR = int(np.argmax(Z.real))
fs, fp = f[iG], f[iR]
zc = [i for i in range(len(f) - 1) if np.sign(ph[i]) != np.sign(ph[i + 1])]
zc_f = [fm[i] - ph[i] * (fm[i + 1] - fm[i]) / (ph[i + 1] - ph[i]) for i in zc]
say(f"series resonance (max G) fs = {fs / 1e6:.3f} MHz, G = {Y.real[iG] * 1e3:.2f} mS; parallel resonance (max R) "
    f"fp = {fp / 1e6:.3f} MHz, R = {Z.real[iR]:.1f} ohm; phase zero at " + ", ".join(f"{x:.3f}" for x in zc_f) + " MHz")

# matched-probe check: a bare piezo ceramic is capacitive away from resonance (B = w C0 > 0); here the band-edge
# susceptance is inductive and |Z| stays near 50 ohm, i.e. the probe carries a matching network, so no BVD fit.
edge = np.r_[0:10, len(f) - 10:len(f)]
b_edge = np.median(Y.imag[edge])
inner = slice(dips[0], dips[-1] + 1)
mid = dips[0] + int(np.argmin(RL[inner]))
subs, i = [], 0
while i < len(f):
    if band[i]:
        j = i
        while j + 1 < len(f) and band[j + 1]:
            j += 1
        subs.append((fm[i], fm[j])); i = j + 1
    else:
        i += 1
say(f"-10 dB sub-bands: " + ", ".join(f"{a:.2f}-{b:.2f}" for a, b in subs) + f" MHz; between the dips RL falls to "
    f"{RL[mid]:.1f} dB at {fm[mid]:.2f} MHz")
band_z = (fm >= 3.0) & (fm <= 4.4)
say(f"|Z| over 3.0-4.4 MHz: {abs(Z[band_z]).min():.0f}-{abs(Z[band_z]).max():.0f} ohm; band-edge susceptance "
    f"{b_edge * 1e3:+.1f} mS ({'inductive' if b_edge < 0 else 'capacitive'}) -> "
    f"{'matched probe (integrated network), BVD fit of the ceramic not applicable' if b_edge < 0 else 'bare ceramic'}")
i33 = int(np.argmin(abs(f - 3.3e6)))
say(f"at 3.30 MHz: |Z| = {abs(Z[i33]):.1f} ohm, phase {ph[i33]:+.1f} deg, RL {RL[i33]:.1f} dB")

mac = {"Pfmin": f"{fm[0]:.1f}", "Pfmax": f"{fm[-1]:.1f}", "Pnpts": f"{len(f)}",
       "Pdipa": f"{fm[dips[0]]:.2f}", "Prla": f"{RL[dips[0]]:.1f}", "Pdipb": f"{fm[dips[-1]]:.2f}", "Prlb": f"{RL[dips[-1]]:.1f}",
       "Pza": f"{Z[dips[0]].real:.0f}\\,{'+' if Z[dips[0]].imag >= 0 else '−'}\\,j{abs(Z[dips[0]].imag):.0f}",
       "Pzb": f"{Z[dips[-1]].real:.0f}\\,{'+' if Z[dips[-1]].imag >= 0 else '−'}\\,j{abs(Z[dips[-1]].imag):.0f}",
       "Ptenlo": f"{f10lo:.2f}", "Ptenhi": f"{f10hi:.2f}", "Pfs": f"{fs / 1e6:.2f}", "Pfp": f"{fp / 1e6:.2f}", "Pzc": ", ".join(f"{x:.2f}" for x in zc_f),
       "Pmidf": f"{fm[mid]:.2f}", "Pmidrl": f"{RL[mid]:.1f}", "Pzlo": f"{abs(Z[band_z]).min():.0f}",
       "Pzhi": f"{abs(Z[band_z]).max():.0f}", "Psubs": ", ".join(f"{a:.2f}–{b:.2f}" for a, b in subs), "Pzmag": f"{abs(Z[i33]):.0f}", "Pzph": f"{ph[i33]:+.0f}".replace("-", "−")}
(DS / "piezo_values.tex").write_text("% generated by datasheet/piezo_test/analyze_s1p.py -- do not edit\n" +
                                     "".join(f"\\newcommand{{\\v{k}}}{{{v}}}\n" for k, v in mac.items()))

fig, ax = plt.subplots(1, 3, figsize=(7.4, 2.4))
ax[0].plot(fm, RL, color="#1f5fa8", lw=1)
ax[0].invert_yaxis(); ax[0].set(xlabel="MHz", ylabel="return loss (dB)", title="S11 (50 Ω)")
ax[0].axhline(10, color="k", lw=.5, ls=":")
ax[1].plot(fm, abs(Z), color="#1f5fa8", lw=1, label="|Z|")
ax[1].plot(fm, Z.real, color="#c0392b", lw=.8, label="R")
ax[1].plot(fm, Z.imag, color="#27ae60", lw=.8, label="X")
ax[1].axhline(0, color="k", lw=.4)
ax[1].set(xlabel="MHz", ylabel="Ω", title="impedance"); ax[1].legend(fontsize=6, loc="upper right")
ax[2].plot(fm, Y.real * 1e3, color="#1f5fa8", lw=1, label="G")
ax[2].plot(fm, Y.imag * 1e3, color="#7f8c8d", lw=.8, label="B")
ax[2].axvline(fs / 1e6, color="#c0392b", lw=.6, ls="--")
ax[2].set(xlabel="MHz", ylabel="mS", title="admittance"); ax[2].legend(fontsize=6)
for a in ax:
    a.tick_params(labelsize=7); a.title.set_size(8); a.xaxis.label.set_size(8); a.yaxis.label.set_size(8)
plt.tight_layout(); fig.savefig(DS / "figures" / "piezo_impedance.pdf")
(HERE / "report.txt").write_text("\n".join(rep) + "\n")
print("wrote piezo_values.tex, figures/piezo_impedance.pdf, piezo_test/report.txt")
