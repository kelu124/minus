# 2026-11-19 — gain sweep, pulse-echo on board 3 (minUS_08112026)

Firmware rp 0.1.32 / pic 0.1.23 (proto 8). Pulse +5 V 200 ns / off 27 ns / GND 500 ns; `pe` (4095 samples, 24.86 Msps,
auto-retry when the ADC locks to the slow 53 ns pattern). Same target as `docs/bench/2026-11-19-pe/` (echo train every 40.2 µs).

Commands: `gain <leg> <u1> <u2>` then `pe 200 500 25` (ADC node) and `pe 200 500 0` (OA1OUT). Files `pe_g<leg><u1><u2>_in<in>.txt`.
Settings: g011 (both ×1, 0 dB), g010/g110/g210/g310 (OA1 ×1, OA2 leg 0–3: 10.1/15.1/17.8/20.8 dB),
g000/g100/g200/g300 (both stages leg 0–3: 20.2/30.2/35.7/41.7 dB). Nominal gain per stage 1 + Rf/1k, Rf = 2.2k/4.7k/6.8k/10k.

Plots: `/usr/bin/python3 docs/bench/2026-11-19-gain/plot_gain.py docs/bench/2026-11-19-gain` → `gain_full.png` (A-lines),
`gain_echo1.png` (first echo zoom), `gain_amplitude.png` (echo pp vs gain; x = clipped, ADC node saturates < 60 / > 3960).

Echo pp (LSB, in 25; * = clipped) at 41 / 80 / 121 / 161 µs, and noise sd:
| setting | dB | e1 | e2 | e3 | e4 | noise |
|---|---|---|---|---|---|---|
| g011 | 0.0 | 474 | 141 | 55 | 31 | 9.5 |
| g010 | 10.1 | 1702 | 533 | 138 | 63 | 10.7 |
| g110 | 15.1 | 3331 | 950 | 265 | 98 | 12.9 |
| g210 | 17.8 | 3941* | 1376 | 365 | 118 | 13.7 |
| g310 | 20.8 | 3993* | 1844 | 507 | 148 | 15.0 |
| g000 | 20.2 | 4028* | 1956 | 452 | 151 | 14.2 |
| g100 | 30.2 | 4030* | 3996* | 1380 | 437 | 28.7 |
| g200 | 35.7 | 3994* | 4021* | 2493 | 711 | 46.6 |
| g300 | 41.7 | 4013* | 3998* | 3597 | 1003 | 70.4 |

Measured stage gains (unclipped echoes vs the ×1 setting): OA1 leg 0–3 ≈ ×3.5–3.7 / ×5.2–6.4 / ×7.9 / ×10.2 (nominal 3.2/5.7/7.8/11);
OA2 ≈ ×3.6–3.8 / ×6.7–7.0 / ×9.8 / ×13.1 (10–20 % above nominal: mux Ron + C44 path, to check). Noise grows from 9.5 to 70 LSB
(×7.4 for ×121): at low gain the ADC/front noise floor dominates, at 42 dB the LNA/OA1 noise does. Gain switching via UGE works.
