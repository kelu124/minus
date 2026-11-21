# 2026-11-22 — PIC ADC extras for pulse-echo, reachable from the RP (design)

Owner request (session 13): "write extra functions on the PIC32 side that make the most of the ADC extras (in line with
pulse echo for us) and make them accessible by the rp". No hardware change; board 3 has no piezo connected, so every
function is checked with the PIC DAC on AD2AN3 (input 19).

## ADC extras available (DS70005592 §18.3, ADnCHxCON)
- MODE 11 **oversampling**: ACCNUM 4/16/64/256 conversions per trigger → 13/14/15/16-bit result (TRG2SRC re-triggers).
- MODE 10 integration (already used: `navg` 2..16), MODE 01 window-gated accumulation, ACCRO + secondary accumulator.
- **Digital comparator per channel**: CMPMOD (> lo, ≤ lo, in [lo, hi], out of [lo, hi]) on ADnCHxCMPLO/HI, flag in
  ADnCMPSTAT.CHxCMP (set by hardware, cleared by writing 0).
- DIFF / NINSEL (differential) and LEFT (fractional) — no use on board 3 (no ANN pins wired to the front end).

## Functions (proto 13, pic 1.1.3 / rp 1.1.6)
1. **`ACQOS <4|16> [in]`** — one capture with hardware oversampling (MODE 11, ACCBRST): each sample = 4 or 16
   back-to-back 32 ns conversions, 13/14-bit, trigger period raised automatically to fit (div 35 = 175 ns / 5.7 Msps,
   div 113 = 565 ns / 1.77 Msps). Lower noise and a 4× / 14× longer window (0.76 / 2.32 ms = 0.55 / 1.8 m of water).
   64/256 left out: their fill (8.6 / 34 ms) exceeds Timer1's 5.2 ms range. RP: `acqos <4|16> [in [pe]]` (pe 1 = fire the
   pulser on RDY as `pe`), printed like `acq`. **Caveat (owner question, 2026-11-22):** one pulse, averaging inside each
   sample; at 5.4 / 1.77 Msps a 3.3 MHz echo aliases (Nyquist 2.7 / 0.88 MHz) and the 128 / 512 ns average cancels most of
   it — not an RF mode; for echoes use `pe`, `env` or `tof`.
2. **`TOF <thr> [blank] [in] [ref]`** — pulse-echo time of flight without sending the A-line: one uniform 25 Msps capture
   with the channel comparator armed out of [ref−thr, ref+thr] (hardware flag = "something crossed"), then the PIC finds
   the first sample at or after `blank` with |x−ref| > thr and the largest |x−ref| in the next 64 samples. ref 0 = the
   capture mean. Reply `TOF <idx|-1> <peak_idx> <peak_dev> <ref> <hw flag> <ticks> <tick_ns> <status>` (one line, no
   payload). RP: `tof <thr> [blank_ns [in [ref]]]` fires the pulser like `pe` and prints index, time (ns) and depth (mm).
3. **`ENV <dec> [in [acc]]`** — on-PIC envelope: capture (pulse on RDY), x − mean, |·|, integrate-and-dump over `dec`
   samples (4..64) → n = 4095/dec values; `acc 1` adds into a running sum (u32, the second capture buffer) for
   multi-shot averaging — envelopes average well although the sample comb phase is random per shot (E3, ±20 ns vs a µs
   envelope). The current average (1/16 LSB, u16) is left in acq_buf for SPIX/UTX. Reply
   `ENV <n> <dec> <shots> <ticks> <tick_ns> <status>`. RP: `env <dec> [shots [in]]` fires one pulse per shot, then pulls the
   averaged envelope once and prints `# env n=… dec=… shots=… dt=…ns …` + one value per line (LSB × 16).
- Slow captures: TOF/ENV/ACQOS report `slow` like ACQ; the RP re-shoots (≤ 8, RELOCK after 3) like `pe`.
- Library: `acqos()`, `tof()` → `Tof`, `env()` → `Envelope` (values in LSB, time axis); fixture + notebook 02 section.

## Checks without a piezo (DAC on AD2AN3 = input 19)
- ACQOS: `dac dc 2048` → noise rms of `acq` vs `acqos 4` vs `acqos 16` (expect ~1/2 and ~1/4 until the DAC/pin noise
  floor); triangle → slope and period consistent with the longer sample period.
- TOF: triangle 512..3584 (24.58 µs), ref 2048, thr 1000 → first crossing where the triangle leaves [1048, 3048]:
  predictable from the triangle phase in the same capture (host check on an `acq`).
- ENV: triangle → envelope = |tri − mean| averaged over `dec` samples: compare with the host computation on an `acq`.
