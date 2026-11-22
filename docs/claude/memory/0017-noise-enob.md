# 0017 — ADC and RX-chain noise / ENOB, board 3 (2026-11-19, session 11)

**Status:** measured · type: project · data `docs/bench/2026-11-19-noise/` (README = full tables)
- ADC alone (internal band gap AD1AN15/AD2AN15 = codes 15/31): σ 0.82–1.0 LSB → 10.2–10.5 noise-limited bits full band
  (datasheet ENOB 10.5), 11.5 in 1.5–5 MHz. AVDD = 3.32 V from the 0.8 V band gap. Internal refs need SAMC ≥ 3 (8 ns reads 16 % low).
- External inputs carry a **period-4 fixed pattern** (one sample in 4 ≈ 23 LSB low, ≈ 10.5 LSB rms, gain-independent, random
  phase per capture): remove by per-phase mean before any noise figure. It halves the as-captured ENOB of the chain.
- Chain, pattern removed: 3.7 → 15.1 LSB (×1 → ×134) = 8.3 → 6.3 bits full band; in band 11.4 → 8.2 bits. Front end n1 =
  85 µV rms at OA1 in; at max gain ≈ 0.85 nV/√Hz at the LNA input (if 24 dB) ≈ 50 Ω thermal → front-end limited above ~32 dB.
- Interference: 2.72 MHz (in band) and 0.49 MHz enter at the front end. AD1AN1 (LNA tap) reads 26 mV rms aliased wideband noise.
Related: [[0016-pulser-pulse-echo]], [[0011-adc-dma-throughput]].
