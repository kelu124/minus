# Morning report — 2026-11-22 (night work, unattended)

Board 3 now runs **rp 1.1.8 / pic 1.1.5, link protocol 14**. Everything below was tested on the board without a piezo (the
PIC DAC on input 19 served as the signal), reviewed by an independent agent, fixed, soaked, committed and pushed to `main`.
Your hardware files (`hardware/minUS.kicad_pcb`, `hardware/production/*`) were not touched and are still uncommitted.

## What you asked for

| Item | Result |
|---|---|
| `acqos` warning | In the RP help/usage (+ a line printed with `pe 1`), the library docstring, the firmware README, the design note and notebook 02: one pulse, averaging inside each sample; **not for the 3.3 MHz RF echo** (5.4 / 1.77 Msps alias it, 128 / 512 ns average it out) — use `pe`, `env`, `tof` |
| 1. Compact host output | `fmt b64` (base64 u16): **11.4 KB / 30 ms instead of 24.8 KB / 110 ms per capture**. The library switches to it on connect. A full `pe` from Python is now **31 ms** end to end (it was 185 ms at the start of yesterday evening) |
| 5. Older open items | `ACQ` now resets `navg` (pic 1.1.4). **TGC** = `tgc <t_us> <leg> …` (gain-leg steps during each capture) — works, but each 4052 switch costs ~2 µs of saturation + ~15 µs of settling (break-before-make): `Capture.tgc_valid()` masks it; a hardware fix is noted. Averaging over shots = `env … shots`. `reboot dfu` returning to the app: **not reproduced** in ~15 reflashes, parked. PLL2 / 40 Msps and the +425 LSB CPU-loop offset: **parked to Someday** with the reason (the DMA caps any RAM capture at 25 Msps; re-clocking the ADC risks the slow-lock fix) |
| PC viewer | `python3 -m minus.live` — A-line, envelope (dB) and scrolling M-mode; modes pe / acq / env / tof; **22 frames/s** (pe), 43 (env). Tested in a real Tk window on your desktop and headless. **Jupyter live object**: `LiveView(dev)` — run / mode / input / gain controls over an image updating in place from a background thread (~5 frames/s, PNG rendering). Example: `python/notebooks/04_live_viewer.ipynb` |

## Self-check
- **Independent review** (read-only agent over the whole night's diff) found 9 issues — 3 likely bugs (e.g. `tof`/`env`
  inheriting a previous `navg`, a zero-margin `acqos` divider, a timed-out reply that could be parsed as the next capture),
  5 risks (RDY left high by PING, error paths), 1 thread bug in the viewer. **All fixed and re-checked on the board**
  (rp 1.1.8 / pic 1.1.5); details in `docs/bench/2026-11-22-pc-robust/README.md`.
- **Soaks** (library end to end, mixed commands, PIC resets, re-locks, link tests): **2700/2700** on rp 1.1.7 / pic 1.1.4 and
  **2000/2000** on rp 1.1.8 / pic 1.1.5 (with PINGs leaving RDY high) — 0 SPI frame errors, 0 fallbacks.
- **Tests:** 23 library tests (incl. new ones for base64, 1-byte-read framing, stale replies, the viewer), RP host tests
  (base64 vectors), fwsync in sync; fixture re-recorded (64 replies); notebooks 01–04 executed on the board with 0 errors.
- Bugs my own new tests caught tonight: a library **framing bug** (a USB read boundary inside the end-marker line leaked
  "ry help" into the next reply — pre-existing, now fixed with a regression test) and a fixture sequence that left op amp 2
  off. One hypothesis that did **not** hold (tgc transient biasing the pattern correction) was tested A/B and dropped.

## For you
- With a piezo: try `python3 -m minus.live` (input 25, pick the gain), `tof <thr> <blank_ns>` and `env 8 16`, and judge
  `tgc` on a deep target (17 µs lost per step).
- PCB: Update PCB from Schematic (F8), route DACOUT1 → GPIO26, then re-export production; In1 slots + one QR code before ordering.
- Next firmware candidates are at the top of `docs/claude/TODO.md`.

Commits tonight (newest first): `1552ba1` review fixes · `5e7d73f` live viewer · `299a809` proto 14 (b64, tgc, navg) ·
`6ae0bf3` ADC extras · `3114543` proto 12 + slow-lock self-heal (+ changelog commits after each).
