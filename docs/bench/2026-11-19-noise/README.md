# 2026-11-19 — ADC and RX-chain noise / ENOB, board 3 (minUS_08112026)

fw rp 0.1.32 / pic 0.1.23. No pulse; transducer connected (same setup as `../2026-11-19-gain/`). 12-bit, full scale =
AVDD; AVDD from the 0.8 V band gap = **3.32 V / 3.31 V** (ADC1 / ADC2) → 1 LSB ≈ 0.81 mV (the scripts use 3.3 V).

- Capture: `bash docs/bench/2026-11-19-noise/capture.sh` (repo root): ADC-only internal inputs (codes 15/14 = AD1AN15 band gap /
  AD1AN14 15/16 AVDD, 31/30 = ADC2 same, SAMC 0 and 3), ADC node (25) at the 9 gain settings × 3 records, OA1OUT (0) and
  LNA tap (1) at g011/g000/g300 × 2. Slow-lock (18.08 Msps) records are retried.
- Analysis: `/usr/bin/python3 docs/bench/2026-11-19-noise/analyze_noise.py` → `noise_summary.txt` (as captured) and
  `noise_summary_clean.txt` (period-4 pattern removed), `noise_vs_gain*.png`, `noise_psd*.png`, `adc_hist*.png`.
  In-band numbers: `band_1p5-5MHz.txt` (FFT brick-wall 1.5–5 MHz, pattern removed, 2.72 MHz line notched).
- Definitions: noise-limited ENOB = (SNR_FS − 1.76)/6.02, SNR_FS = 20 log10(1448 LSB rms full-scale sine / σ). It excludes
  distortion (no sine test yet) → an upper bound on the datasheet-style ENOB (DS70005592 AD34: 10.5 bits typ, 1 kHz sine).

## 1. ADC alone (internal references, 4031 samples × 3)
| input | SAMC | mean | σ (LSB) | ENOB_n (full Nyquist) |
|---|---|---|---|---|
| AD1AN15 band gap | 3 | 986.9 | 0.83 | 10.48 |
| AD2AN15 band gap | 3 | 989.2 | 0.82 | 10.49 |
| AD1AN14 15/16 AVDD | 3 | 3481.6 | 1.00 | 10.21 |
| AD2AN14 15/16 AVDD | 3 | 3479.4 | 0.89 | 10.37 |
| AD2AN15 band gap | 0 | 828.9 | 0.88 | 10.39 |

→ **ADC: σ ≈ 0.82–1.0 LSB, 10.2–10.5 noise-limited bits over the full 12.4 MHz Nyquist band (matches the datasheet 10.5),
11.5 bits in the 1.5–5 MHz band.** No pattern, no spurs. Notes: at SAMC 0 (8 ns) the band gap reads 16 % low (828 vs 987: the
internal source does not settle in 8 ns; external nodes with 56 pF are fine). 15/16 AVDD reads 3480 instead of 3840 even at
SAMC 3 — unexplained (spec ±15 LSB), not needed here.

## 2. Fixed pattern on every external input
Every external ADC input (ADC node, OA1OUT, both cores) carries a **period-4 pattern locked to the sample clock: one sample in
four ≈ 23 LSB low, ≈ 10.5 LSB rms, the same at every gain** (so it is not from the amplifiers), phase random per capture.
It is the fs/4 (6.21 MHz) and fs/2 (12.43 MHz) lines in `noise_psd.png`. Internal inputs do not show it → it enters at the
pin (digital activity coupling into the AVDD/pin/ground at the 160 ns pattern of trigger/ADC/DMA). Removed in software per
record (per-phase mean); a residual remains at 6.21/12.43 MHz.

## 3. Chain at the ADC node (σ in LSB)
| setting | G (meas.) | as captured | pattern removed | ENOB_n full band | in band 1.5–5 MHz* | SNR_FS in band | ENOB_n in band | input-ref. @LNA in** |
|---|---|---|---|---|---|---|---|---|
| g011 | 1.0 | 9.27 | 3.69 | 8.33 | 0.45 | 70.2 dB | 11.4 | 12.2 nV/√Hz |
| g010 | 3.7 | 10.53 | 4.08 | 8.18 | 0.52 | 68.9 | 11.1 | 3.9 |
| g110 | 6.9 | 11.96 | 4.68 | 7.98 | 0.61 | 67.5 | 10.9 | 2.4 |
| g210 | 9.8 | 12.55 | 4.94 | 7.90 | 0.66 | 66.8 | 10.8 | 1.8 |
| g310 | 13.1 | 12.24 | 5.43 | 7.77 | 0.83 | 64.8 | 10.5 | 1.7 |
| g000 | 13.2 | 12.06 | 6.07 | 7.61 | 1.03 | 62.9 | 10.2 | 2.1 |
| g100 | 40.0 | 12.47 | 6.86 | 7.43 | 2.02 | 57.1 | 9.2 | 1.4 |
| g200 | 77.4 | 14.21 | 9.43 | 6.97 | 2.88 | 54.0 | 8.7 | 1.0 |
| g300 | 133.6 | 18.57 | 15.09 | 6.29 | 4.17 | 50.8 | 8.2 | 0.85 |

\* pattern removed and the 2.72 MHz interference line notched (with it: 0.48 … 8.02 LSB). \*\* /24 dB assumed BGA2817 gain
(not measured on the board), 3.5 MHz band. 50 Ω thermal noise = 0.91 nV/√Hz.

Model (pattern removed): σ² = s0² + (G2·n2)² + (G1G2·n1)² → s0 = 4.6 LSB (gain-independent: ADC 0.8 + residual fs/4, fs/2
lines + near-Nyquist noise; in band the floor is the ADC itself), n2 = 146 µV at the OA2 input, **n1 = 85 µV rms at the OA1
input (LNA output), full band**; the front end is 44 / 73 / 88 % of the output noise at 32 / 38 / 43 dB.

## 4. What it means
- **ADC: fine (10.2–10.5 bits full band, 11.5 in band).** The chain's full-band ENOB (6.3–8.3 bits) is set by things
  around the ADC, not by the converter: the period-4 pattern (−1.3 bit as captured), the fs/4, fs/2 residuals and wideband
  noise near Nyquist. Band-limiting to the transducer band recovers 10–11.4 bits up to ~20 dB of gain.
- **At maximum gain (42.5 dB) the system is front-end-noise limited**: 13 nV/√Hz at the OA1 input, ≈ 0.85 nV/√Hz at the LNA
  input if the LNA gives 24 dB — that is the 50 Ω thermal floor, so either the LNA gain is higher than 24 dB or the transducer
  source impedance is below 50 Ω; either way more analog gain would mostly amplify front-end noise. In-band dynamic range
  at that gain: 50.8 dB (FS 1.56 mV pp at the LNA input, noise ≈ 1.6 µV rms).
- **Interference lines that scale like signal** (enter at the front end): **2.72 MHz (in the transducer band, ≈ half the in-band
  noise power at 32–43 dB)** and 0.49 MHz. Source unknown (a regulator, USB, the RP?) — to find with the scope / by powering
  things off.
- **LNA tap (AD1AN1) reads 32.6 LSB = 26 mV rms of flat, aliased noise**, but almost none reaches OA1OUT (n1 = 85 µV): the ADC's
  wide sample-and-hold bandwidth aliases GHz-wide LNA noise (or an oscillation) — this tap is not a usable measurement point.
  Worth a look with a fast scope / spectrum analyser at the LNA output.
- **Echo SNR** (sine-equivalent, pattern removed, full band): first echo 33 dB at 0 dB gain (48 dB at 15 dB before
  clipping); echo 3 (121 µs) 39 dB at 37.8 dB; echo 4 (161 µs) 28 dB at 37.8–42.5 dB. In band the noise is 3–4× lower
  (+9 to +12 dB).
