# 2026-11-22 — datasheet rev 0.3 campaign (board 3 with the Annex A transducer)

Re-tests every feature added since datasheet rev 0.2, with echoes (first echo 43.1 µs ≈ 33 mm, second 85.6 µs).
Firmware **rp 1.1.9 / pic 1.1.6, proto 15** (final run 2026-11-22 15:54; a first run on rp 1.1.8 / pic 1.1.5 was replaced). One compressed NumPy file per test (arrays + `meta` JSON with firmware, date,
board); no raw text dumps.

```bash
/usr/bin/python3 docs/bench/2026-11-22-datasheet-ext/campaign.py [test ...]   # records the .npz files (board needed)
/usr/bin/python3 docs/bench/2026-11-22-datasheet-ext/analyze.py              # -> datasheet/figures/ext_*.pdf + datasheet/ext_values.tex
make -C datasheet                                                             # PDF
```

| File | Content |
|---|---|
| `pe_ref.npz` | `pe` at gains ×1 / ×3.2 / ×10 / ×32.5 / ×60.8, 16 shots each (`g<leg><u1><u2>`, `_total`, `_dt_ns`) |
| `link.npz` | `linktest 200` at 12.5 / 18.75 / 25 MHz: ok, errors, ms per frame, SPIX→RDY, clocking, UART copy identical |
| `fmt.npz` | end-to-end `acq()` times with text vs base64 output (20 each) and reply sizes |
| `lock.npz` | 10 PIC resets: locks needed, slow of 8, ok/slow of 20 captures |
| `acqos.npz` | DAC DC level: acq / acqos 4 / acqos 16 (5 each); first echo: pe vs acqos 4/16 with pulse (8 each) |
| `tof.npz` | `tof thr 25000 25`, thr 30/60/100/150 × 50 shots (index, peak, ref, flag, dt) + 30 pe captures + timing |
| `env.npz` | `env dec shots 25`, dec 4/8/16/32 × shots 1/4/16 × 5 runs + 16 pe captures + timing |
| `tgc.npz` | ×10, ×10 with `tgc 30 2`, ×61 constant: 16 pe each |
| `pc.npz` | 40 captures with `pc 0`, 40 with `pc 1` + the PIC's offsets per capture |
| `dac.npz` | DC sweep (9 codes), triangle over SPI and UART, sine 20 kHz at 10 Msps (amp 800 and 1500), slow count at 25 Msps |
| `envbp.npz` | `envbp 8 shots 25 fc bw` for 3300/1500, 3300/2500, 3300/4000, 4000/4000 × 1 and 16 shots × 5 runs; env alongside; 16 pe shots; timing |
| `live.npz` | live viewer, 60 frames in pe and envbp modes: last frame's depth axis, RF, envelope, M-mode image; frames/s |
| `bandpass_env.npz` | host prototype (`bandpass_env.py`): peak / floor / dB for env, Hilbert, brick-wall, raised-cosine and Gaussian band-pass |
| `pc_host.npz` | the `pc.npz` raw captures corrected on the host with the PIC's algorithm (+ offsets) |

Results are in datasheet rev 0.3 §4.7 (pattern correction) and §5 (link, envelope detection step by step, time of flight,
oversampling, tgc, DAC, lock check), with the numbers in `datasheet/ext_values.tex`.

**History — DAC test failure → firmware fix (now done):** with the DMA-fed `dac sine` running, the captures were `slow` (bus contention, documented)
and the RP sent `RELOCK`; the PIC's lock check then also saw slow captures and re-locked 12 times (`LOCK 12 8`). Fix written
(pic 1.1.6: pause the sine DMA during the lock check) flashed after the board came back (it had dropped off USB at a `reboot dfu`, E8); the whole campaign
was re-run on rp 1.1.9 / pic 1.1.6, all 12 tests ok.
