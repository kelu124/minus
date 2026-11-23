# 0023 — envbp host simulation vs firmware; repo hygiene rules (2026-11-23, session 14)

**Status:** current · type: project/reference · extends [[0021-spi-link-and-dac]] (envbp) and [[0018-datasheet]] (rev 0.3a)

## envbp (PIC Gaussian band-pass envelope) simulated offline
- `pe_envbp` (`firmware/pic32/pe_ext.c`) is ported line by line to Python as `pic_envbp()` — identical in
  `python/notebooks/05_envbp_filter.ipynb` (offline, no board) and `docs/bench/2026-11-22-datasheet-ext/analyze.py`
  (→ `datasheet/figures/ext_envbp_sim.pdf`, macros `xBpSim*`, `xBpTaps`, `xBpRange` in `datasheet/ext_values.tex`).
- Input: `envbp.npz` `pe_ref` (16 raw pe shots, gain ×3.2, dt 40.20 ns, rp 1.1.9 / pic 1.1.6, 2026-11-22 15:54). The PIC never
  returns the RF it filtered, so sim vs firmware is compared statistically (different pulses, same session).
- 3.3 / 2.5 MHz, dec 8: **23 taps** (half = round(3·149.9 ns / 40.2 ns) = 11; the datasheet had said 21 — fixed in rev 0.3a).
- First echo (38–52 µs) / floor rms (55–78 µs): raw |x−mean| 44.7 dB, env 43.8 dB, **envbp sim 56.5 dB vs PIC 56.0 dB**;
  16 shots 57.3 / 56.8 dB. Envelope pulse-peak / floor ≈ **66 dB** (the owner's "60 dB" = 56 echo/floor … 66 full range).
  Other filters sim/PIC: 3.3/1.5 57.9/56.8, 3.3/4.0 52.8/54.5, 4.0/4.0 49.9/48.3 dB.
- 16-shot averaging adds only ~1 dB → the inter-echo floor after envbp is mostly in-band, repeatable (ring-down/reverb).
- An out-of-band burst at ~135–145 µs in the raw RF (~25 dB above the raw floor, not an echo) is removed by the filter.

## Repo rules added
- `node_modules/`, root `/package.json`, `/package-lock.json` (local xpm install) are in `.gitignore`; `.githooks/pre-commit`
  refuses any staged `node_modules/` path (catches `git add -f`); rule listed in `CLAUDE.md`.
- Running `analyze.py` regenerates every `ext_*.pdf` byte-different with unchanged content → revert the untouched ones
  (`git checkout -- datasheet/figures/ext_*.pdf`) and commit only the figures that really changed.
