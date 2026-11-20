# 2026-11-19 — datasheet measurement campaign, board 3 (v1.1)

Feeds `datasheet/` (LaTeX). Firmware rp 0.1.33/pic 0.1.24 for `campaign.sh`, rp 0.1.34/pic 0.1.25 for
`time_pe.py`, `t1_*` and `t4b/`. 3.3 MHz piezo connected to TX and RX, USB power, 25 °C.

- `campaign.sh` (repo root): T1 identification + 20 pings, T4 pulse sweeps (`t4_hi*`, `t4_lo*`), T5 main bang at unity
  (`t5_mb_in{0,17,25}`), T7 16 shots at gain 2 0 0 and 0 1 0 (`t7_*`), T9 noise at 9 gains + ADC alone (`t9_*`),
  T10 sample-rate options (`t10_div*`). (Its T3 used rpcli's fixed wait — superseded by `time_pe.py`.)
- `time_pe.py PORT N` — end-to-end `pe` time (command → `# pulse` line): 0.877 s per single shot (`t3_timing.txt`).
- `t4b/sweep.sh` — fine pulse-width sweep requested by the owner: 12 points in 13–147 ns (+153…600 ns), 2 shots each.
- `analyze.py` → `datasheet/figures/*.pdf`, `values.tex` (macros), `noise_rows.tex`, and `report.txt`.

Key results (report.txt): ADC alone 0.81 LSB = 10.5 bits; chain 3.5 → 14.5 LSB (×1 → ×134) full band, 0.44 → 4.0 LSB in
1.5–5 MHz; echo −6 dB band 2.88–3.55 MHz (peak 3.37), −6 dB envelope 764 ns; pulse-width optimum 113 ns (plateau 75–130),
effective pulse ≈ t_hi + 48 ns; dead zone 8.2 µs whatever the clamp; echo amplitude CV 2.9 %; sample-comb phase vs pulse
spread uniformly over one sample (36–43 ns p-p, 11–14 ns rms) → align before averaging (8 shots: −11.6 dB).
