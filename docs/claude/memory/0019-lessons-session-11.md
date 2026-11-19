# 0019 — Lessons learnt, session 11 (board 3 bring-up → pulse-echo → gain → noise → datasheet), 2026-11-19

**Status:** durable · type: lessons / how-to
## Hardware / bench
- **Check the netlist before flashing a new board**: pin map vs `minus_devkit.h` (U8 pins, R22/R23/R27 to PGC1/PGD1/MCLR) —
  `kicad-cli sch export netlist --format kicadxml` + `.claude/skills/kicad-netlist-reading/nets.py <xml> pins U8`.
- **Net names lie**: "PWM_H" (GPIO8) drives the low-side N-FET to GND, "PWM_L" (GPIO9) the high-side P-FET (active low).
  RP2350 pads default to pull-down → Q1 on at boot → set pulser idle as the very first thing in `main()`.
- A board revision can silently remove peripherals the firmware assumes (board 3: no WS2812 on GPIO10, an LP5562 on I²C
  instead; ADC node moved from AD1AN9 to AD2AN9; OA2 now in the chain → AMP2 on at boot).
- The PIC ADC has internal inputs (AD1AN15/AD2AN15 band gap 0.8 V, AN14 15/16 VDD) = the cleanest ADC-only noise reference
  and an AVDD meter; they need SAMC ≥ 3 (8 ns reads 16 % low).
- An "LNA tap" read by a sample-and-hold ADC can show huge flat noise (aliased GHz bandwidth) that never reaches the
  band-limited chain: don't trust a direct ADC read of a wideband node.
## ADC / acquisition
- **div 4 (20 ns triggers) + 32 ns conversion = phase luck**: usually every 2nd trigger (40 ns), sometimes 40/60/60 ns
  (echoes at 0.75× the index, fill 226 µs, DMA status clean). How often depends on the build (code alignment). Detect it from
  the fill time **on the PIC** (`slow`, no payload) — a retry that waits for the 0.7 s payload is 1000× more expensive.
- The sample comb's phase vs the pulse is random over one full sample period (uniform, 40 ns p-p): **align shots by
  cross-correlation (sub-sample FFT shift) before averaging**; measure averaging noise with the half-difference of two
  disjoint N-means in the gaps between echoes (otherwise repeatable reverberation or echo CV masquerades as noise).
- **Period-4 fixed pattern** on every external ADC input (one sample in 4 ≈ 23 LSB low): estimate per capture (per-phase mean
  minus mean) and subtract — always look at per-phase means (i mod 2, mod 4) of a noise record before quoting noise/ENOB.
- Quote noise both full band and in the transducer band (1.5–5 MHz): the ADC is 10.5 bits, the chain 6.3–8.3 bits full band
  but 8.2–11.4 bits in band. Noise-only ENOB = 12 − log2(σ√12) is an upper bound (no distortion).
- Pulse width: echo ∝ |sin(π f (t_hi + δ))| with δ ≈ 48 ns on board 3 (dead time keeps +5 V, driver delays); optimum
  113 ns for the 3.3 MHz probe, not the 200 ns default.
## Tooling / workflow
- **Flashing the RP**: after `reboot dfu` wait for `/media/kelu/RP2350/INFO_UF2.TXT` (not just the dir) before `cp`, else cp
  fails and a following `pic flash` re-flashes the *old* embedded PIC image. `reboot dfu` sometimes returns to the app
  (`2e8a:0009`): ask the owner to hold SW2 (BOOTSEL) while plugging in. The CDC port may come back as `/dev/ttyACM1`.
  A unplugged board looks exactly like a failed reboot — ask before debugging.
- `rpcli.py --wait=S` always waits ≥ S: never use it to time anything (`bench/2026-11-19-datasheet/time_pe.py` does).
- Long bench loops: run in the background (`run_in_background`), write each capture to its own file, keep the script in
  the bench folder so the data is reproducible; `LC_NUMERIC=C` in shell scripts (this machine's locale uses a decimal comma).
- matplotlib lives in `/usr/bin/python3` only (not the pyenv python).
- LaTeX here: pdflatex + tikz/booktabs/longtable/tcolorbox, **no siunitx/latexmk**; declare Unicode symbols
  (`\DeclareUnicodeCharacter`) or pdflatex stops; never `\input` inside a tabular (end-of-file breaks `\bottomrule`) — wrap
  rows in a macro; three pdflatex runs for `lastpage`; generate every measured number as a macro from the analysis script.
- Keep `.claude/skills/minus-commit-log/COMMITS.md` updated on every commit (was forgotten during session 11, caught up).
Related: [[0016-pulser-pulse-echo]], [[0017-noise-enob]], [[0018-datasheet]], [[0011-adc-dma-throughput]].
