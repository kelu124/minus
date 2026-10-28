# 0011 — PIC32AK ADC / DMA / CPU throughput facts (bench, board 2, 2026-10-28)

**Status:** current · type: project/reference · source: session 06 log, DS70005592 §7.3, §15, §16, §18

## The numbers
| Path | Measured | Why |
| --- | --- | --- |
| ADC core, one channel, back-to-back | **25.05 ns / conversion (40 Msps)** — `ADCBB 4095` = 1026 Timer1 ticks | 1.5 TAD conversion + 0.5 TAD sampling at TAD 80 MHz |
| DMA, 16-bit SFR → RAM, CPU quiet | **50 ns / transfer → 20 Msps** (div 8 = 1 transfer per trigger; div 4–6 = 1 per 2 triggers; div 7 = jitter) | DMA sits on the standard-speed bus (= CPU/2, Table 16-1): 4 bus clocks per transfer. `BMXINITPR.DMAPR` has no effect |
| DMA with the CPU polling `DMA0STAT`/`TMR1` back-to-back | fake 37.5 ns/sample with **~30 % duplicated samples** | CPU has priority on the SFR bus (§16.2); stalled DMA re-serves the request. Session-05 "26.6 Msps" and its non-linear div table were this artefact |
| CPU loop `dst[i] = AD1CH0DATA` | exactly **4 cycles = 25 ns per read**, phase-locked to the ADC (same PLL) | at 50 ns triggers every sample is seen once (gap 4) / twice (gap 0) — perfect; at 25 ns triggers marginal: phases 0/1/5 ≈ 10 % duplicated pairs, other phases every other result lost (CPU read beats the ADC result write) |
| Integration mode (`navg` N, back-to-back re-trigger) | sum arrives after ≈ 25·N + 40 ns per trigger | per-sequence overhead ≈ 40 ns; `navg 2` at div 8 → 88 ns → use div ≥ 15 |
| SCCP1 trigger period | **div × 6.25 ns** (div 8 → 50.3, 16 → 100.5, 32 → 195 ns, RP crystal) | FRC ≈ +0.5 % slow; the old "0.6–0.75 × div" numbers were the duplicate artefact |
| ADC trigger sources 2 (immediate re-trigger) and 3 (repeat timer) as TRG1SRC | **never fire** (DATA stays stale) | **Datasheet Table 18-3: TRG1SRC 00010/00011 are Reserved** — both sources exist only as TRG2SRC (Table 18-4), i.e. inside a multi-sample sequence. No free-running single-sample mode exists |
| 20 M sums/s ("20 Msps integrated over 2") on one channel | **not possible as measured**: CNT=2 sequence = 88 ns → 11.4 M sums/s max (div 15) | oversampling mode starts at ACCNUM=4, so CNT=2 integration is the only hardware 2-sum; the ≈ 40 ns per-trigger overhead cannot be skipped (no self-retrigger for TRG1SRC). Untested route: CH0 + CH1 on the same input, each CNT=2 at 100 ns, triggered 50 ns apart (SCCP1 trigger-out vs SCCP1 OCMP-out), two DMA channels = 20 M transfers/s total = exactly the DMA ceiling |

## What it means for minus
- **Default capture = `acq` at div 8 = 20 Msps via DMA**, clean. Nyquist 10 MHz covers 3–5 MHz probes.
- The "40 Msps ADC" is sized for 20 channels / oversampling, not for single-channel streaming; the
  peripheral-to-RAM path is the limit. Routes to real 40 Msps raw: (a) CPU at 200 MHz → 5-cycle loop
  with slack (needs PLL2 for the 320 MHz ADC clock; also lifts the DMA to 25 Msps); (b) keep the
  CPU-loop at 160 MHz and prove/tune the phase with a known tone; (c) `navg` sums (boxcar-N, 40 Msps
  inside each burst).
- Any capture-time code must keep the CPU off the SFR bus (NOP poll every ~1024 cycles, or
  interrupt + `pwrsav #1`). Timer1 is read only after DONE.

## Related
[[0008-devkit-minUS_10102026]] (board + bench state), `firmware/README.md` command table,
`docs/claude/specs/2026-10-27-acq-design.md` §11, `docs/claude/log/2026-10-28-session-06.md`.
