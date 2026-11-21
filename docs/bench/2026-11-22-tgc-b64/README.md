# 2026-11-22 — compact sample output (fmt b64) and time-gain steps (tgc), board 3, no piezo

Firmware **rp 1.1.7 / pic 1.1.4, proto 14**. Scripts from the repo root with `/usr/bin/python3`.

## fmt b64 (raw serial timing, `acq 4 0 19 1` on a DAC DC level)
| fmt | bytes over USB | time | decoded |
|---|---|---|---|
| text | 24 777 | 110 ms | 4095 samples |
| b64 | 11 427 | **30 ms** | 8190 B → 4095 samples, same values (mean 2014–2015, min 2011, max 2018–2020) |
The library switches to b64 on connect (`Minus(fmt="b64")`); text still parses.

## tgc (`tgc_noise.py 5` → `tgc_noise.json`, `tgc_step.png`)
RX-chain noise on input 25 (no signal) with the 4052 leg: leg 0 4.8 LSB rms, leg 3 13.8; `gain 0 0 0` + `tgc 60 3` → the
step lands at 60 µs in every capture. **Each switch costs ~2 µs of saturation (up to ~4000 codes) + ~15 µs of settling**
(undershoot to ~1920, back by ~77 µs): the 4052 is break-before-make, the op-amp feedback opens for a moment. The library's
`Capture.tgc_valid()` masks 17 µs after each step. (The first tgc_noise run's "before" rms of 6.7 and a fixture capture with
a drifting baseline both came from op amp 2 left **off** by an earlier `raw AMP2 0` in the sequence — fixture fixed.)
Hardware idea for later: make-before-break switching or a parallel Rf switched in, so the loop never opens.

## Gain settling (no change needed)
After `gain 3 0 0` / `gain 0 0 0` the baseline is at its final value (±5 LSB) in the first capture, 31 ms later.
