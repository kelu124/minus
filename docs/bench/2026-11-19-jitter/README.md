# 2026-11-19 — E3 sample-comb phase / jitter study (board 3 = minus v1.1)

Datasheet erratum E3: the sample comb's phase vs the pulse changes from shot to shot. This campaign measures its
distribution, checks whether shots are independent, and looks for clock-domain structure.

- Firmware rp 1.1.1 / pic 1.1.0 (proto 10), board unique ID 7D4466C63B374C98, 3.3 MHz piezo on TX/RX, USB power.
- `capture.py` (repo root, uses `python/library`): `acq 4 0 25 1` (known PIC state), `gain 2 0 0`, `pc 1`, then
  **400 × `pe 200 500 25 27`**: set A = 300 back-to-back shots, set B = 100 shots each after a random 0–50 ms pause.
  → `shots.npz` (samples + per-shot `shots`, `fill_us`, `rp_fill_us`, `fired`, `delay_s`, `t_unix`), `meta.json`.
- `analyze.py` → `report.txt`, `jitter_distribution.png`, `jitter_template.png`, and for the datasheet
  `datasheet/jitter_values.tex` + `datasheet/figures/comb_phase.pdf`.

## Method

1. **φ from the main bang** (purely electrical). The 400 shots sample the transmit feed-through at different
   phases → 1 ns equivalent-time template; each shot's φ = least-squares fit (0.1 ns grid, 3 iterations). A fit one
   sample away is ~10⁴× worse, so φ has no wrap ambiguity. Fit residual 11 LSB rms on a 4000 LSB waveform.
2. **Echoes as an independent check**: echo delay by ×32 upsampled cross-correlation; the acoustic path drifts
   slowly (161 ns p-p over the run, temperature/target) so a 15-shot running median is removed first.

## Results (report.txt)

- **φ spans 39 ns = one sample (40.2 ns), 11.3 ns rms** (uniform would be 11.6). Close to uniform but not exactly:
  KS D = 0.09 (p = 0.003); the periodogram of φ peaks at P ≈ 4.2 ns (0.27 vs 3/√N = 0.15), i.e. some clustering
  near the 250 MHz ADC-clock period.
- **Shots are independent**: lag-1 autocorrelation −0.03; a random 0–50 ms pause changes nothing (set B rms 10.5 ns
  vs 11.6 ns, corr(pause, φ) −0.07). No re-shots (`slow` lock, E2) in 400 captures.
- **New: whole-sample comb slips.** The strong echo at 37 µs is where φ says in 343/400 shots (residual 8.1 ns rms),
  but exactly **one sample (40.2 ns) off in 14 %** (51 late, 6 early); at 76 µs **31 %** (48/58 ±1, 5 ±2). The
  comb gains or loses a whole period during the capture, more often the longer it runs. The PIC fill time
  (80 ns Timer1 resolution) does not see it. The slipped shots cluster at φ ≈ −10 ns and +8…+16 ns, so it depends
  on the start phase: probably a marginal trigger/conversion lock, a milder form of the 40/60/60 ns slow lock.
- Consequences: average after aligning on the echo of interest (not on the main bang), and reject shots whose late
  echoes disagree by a whole sample. Root-cause fix (firmware): start SCCP1 from the ADC clock domain, or time-stamp
  conversions.
