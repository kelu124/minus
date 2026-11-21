# 2026-11-22 — independent review of the night's code, fixes, and two soaks (rp 1.1.8 / pic 1.1.5)

## Review (subagent, read-only, `git diff 1b02fb3 HEAD`): 9 findings, all fixed in rp 1.1.8 / pic 1.1.5
1. `tof`/`env` inherited div/samc/navg from the last ACQ (e.g. after `acq … 4`: 4× sums vs a 12-bit threshold; blank_ns/40
   wrong at other divs) → `pe_std_begin()/pe_std_end()` force div 4 / samc 0 / navg 1 around their capture.
   Checked: after `raw ACQ 4 0 25 4`, `tof` sees a 12-bit peak (1105 LSB) at 40.2 ns/sample.
2. `acqos` divider was 36 / 112 (doc said 35 / 113; 112 = zero margin) → `(N*32 + 52)/5 + 1` = 37 / 113: measured
   186.0 / 565.4 ns; and oversampled captures now get their own `slow` check (fill > N × period + 5 %).
3. Python: a timed-out exchange left its late reply in front of the next one (an old capture could be parsed as new) → the
   partial reply is kept and everything up to the last stale end marker is dropped (regression test).
4. `SPIX 0` left RDY as it was → RDY dropped first.
5. RDY left high by PING (it toggles per reply): the low phase before a capture/frame was < 1 µs, the RP could miss it (no
   tgc, rp_fill -1, a TOF reply overflowing the UART FIFO) → `rdy_low_settle()` holds RDY low ~8 µs when it was high.
   Checked: 5 `pe` with RDY stale-high all saw the window (rp_fill 162–164 µs) with tgc applied; soak with PINGs clean.
6. `ENV` with dec out of range printed an uninitialised struct → zeroed (`ENV 0 2 0 0 80 err`).
7. The ENV running sum lives in the ACQIL buffer → invalidated after ACQIL.
8. `RELOCK` after `acq … navg>1` tested nothing (slow check disabled) → lock_check uses the standard settings.
   Checked: `LOCK 1 0` from a real test, next plain ACQ 2058 ticks.
9. Viewer: `stop()` on the worker thread joined itself → no self-join.

## Pattern-correction estimator A/B (`pc_ab.py 20` → `pc_ab.json`) — no change kept
Suspecting the tgc switch transient biased the period-4 correction, a block-wise robust estimator was tried. On the same raw
captures (pc 0) the residual pattern rms is identical without tgc (1.81 / 1.19 LSB, 3–55 / 80–164 µs) and within 0.15 LSB
with `tgc 60 3` (old 2.56 / 1.39, new 2.41 / 1.50; raw ~11). Reverted (the datasheet numbers refer to the original). The bad
fixture capture that triggered it was a comb slip mid-capture (E3) — the tgc test now uses a lag-4 difference (3.7 → 15.2).

## Soaks (`docs/bench/2026-11-22-soak/soak.py`, library end to end, no piezo)
| Firmware | rounds × ops | result | medians |
|---|---|---|---|
| rp 1.1.7 / pic 1.1.4 | 300 × 9 (+3 PIC resets, 300 RELOCK) | **2700 / 2700 ok**, 3609 SPI frames, 0 errors / fallbacks | pe 31 ms, tof 9.4, env×4 32, linktest(5) 763 |
| rp 1.1.8 / pic 1.1.5 | 200 × 10 (+ single PINGs: RDY often stale-high) | **2000 / 2000 ok**, 2200 frames, 0 errors | pe 32 ms, tof 9.5, ping 4.2 |
