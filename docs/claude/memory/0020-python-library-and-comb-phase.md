# 0020 — Python library, fw-sync rule, E3 comb phase (2026-11-19, session 12)

**Python library** `python/library/minus` (written for rp 1.1.2 / pic 1.1.0, proto 10; now rp 1.1.9 / pic 1.1.6, proto 15 — see 0021 for fmt b64, live viewer):
- Framing: each CLI line is followed by a sentinel `#end<k>`; the firmware answers `unknown '#end<k>' — try help`, which marks the
  end of the reply (works for 4097-line `pe` captures). One `Minus` method per command, parsers in `protocol.py`.
- `commands.py` = registry (dispatch token, exact `help` usage, method, `FIRMWARE`). `fwsync.py` checks it against
  `firmware/rp2354/main.c` (dispatch in `main`, usages in `help()`, `cmd_pic` subcommands), `firmware/pic32/main.c` (link
  dispatch), both `version.h`, and a SHA-256 fingerprint of all firmware sources (`firmware_sync.json`).
- Enforced by `.claude/hooks/fwsync-check.sh` (PostToolUse Edit|Write|MultiEdit, exit 2) and `.githooks/pre-commit`
  (`git config core.hooksPath .githooks`; also runs the offline tests). After a firmware change: update library, re-record
  `tests/fixtures` (`tests/record_fixture.py`, board needed), re-run notebooks, `python3 -m minus.fwsync --update`.
- Use `/usr/bin/python3` (has pyserial, numpy, matplotlib, nbformat/nbclient); the pyenv python lacks matplotlib.
- `acqil` changes the PIC div (24): run `acq 4 0 25 1` after it. `pic id/verify` reset the PIC (UGE/pc go back to boot values). The first link line after an RP reboot can go unanswered: `pic_ident()` retries once.

**Naming / versions (owner, 2026-11-19):** the board is "minus v1.1" (= board 3); firmware 1.1.x
(`minus-rp2354`, `minus-pic32`). The datasheet keeps the measurement firmware (rp 0.1.34 / pic 0.1.25) in `values.tex`.

**LP5562 U5** (board 3): I²C 0x30, EN tied high, OSC1 32 kHz on CLK; firmware uses ENABLE 0x40 → 500 µs → CONFIG 0x01 (internal
clock) → LED_MAP 0x00 → PWM B 0x02 / G 0x03 / R 0x04. Colour order R/G/B confirmed by the owner (2026-11-19). rp 1.1.2: `rgb R G B [pct]`, pct = brightness % (default 25), scales the PWM.

**E3 comb phase** (`docs/bench/2026-11-19-jitter/`, 400 `pe` shots): φ (pulse vs sample comb) from an equivalent-time fit of the
main bang: 39 ns span (one sample), 11.3 ns rms, near-uniform (KS p 0.003, clustering near 4 ns ≈ 250 MHz ADC clock),
independent shots (lag-1 −0.03). **Whole-sample slips**: echo vs φ off by exactly ±1 sample in 14 % of shots at 37 µs, 31 % at
76 µs, clustered at φ ≈ −10 / +12 ns → marginal trigger/conversion lock (cousin of the E2 slow lock). Echo delays also drift
~160 ns over minutes (acoustic path), so use the main bang for φ, and remove the drift before comparing echoes.
