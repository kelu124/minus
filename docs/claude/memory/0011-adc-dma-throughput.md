# 0011 — PIC32AK ADC / DMA / CPU throughput facts (bench, board 2, 2026-10-28)

**Status:** current — **since pic 0.1.20 (2026-11-02) the PIC runs CPU 200 MHz / ADC 250 MHz; the table below was measured at 160/320 MHz, see the 200 MHz section** (tone-verified 2026-11-02, session 08) · type: project/reference · source: session 06/08 logs, DS70005592 §7.3, §15, §16, §18

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
| 20 M sums/s ("20 Msps integrated over 2") on one channel | **not possible**: CNT=2 sequence = 88 ns → 11.4 M sums/s max (div 15) | oversampling mode starts at ACCNUM=4, so CNT=2 integration is the only hardware 2-sum; the ≈ 40 ns per-trigger overhead cannot be skipped (no self-retrigger for TRG1SRC) |
| **Two-channel interleave `acqil` (CH0 on SCCP1, CH1 on SCCP2 preloaded ~half a period, CNT=2 each, DMA0 + DMA1)** | **works: `acqil 16` = 4094 2-sums in 206.0 µs = 19.87 M sums/s** (pic 0.1.19 / rp 0.1.27) | both DMAs finish, no overrun; with 4 conversions per 100 ns the ADC core is saturated and packs conversions on its 25 ns grid → even/odd channel means equal to 0.1 LSB for any `off` (uniform 40 Msps comb, pairs summed, 13-bit). Period must be a multiple of 2×25 ns per channel: div 20 (5 slots) gives 10–22 LSB channel offset, `acqil 24 0 4` overloads (fill ×2, order scrambled); `acqil 32 0 4` = 4-sums at 9.94 M/s. The first pair can come out swapped (startup); `off 5` at div 16 avoids it. Still to prove with a known tone |

## Tone verification (2026-11-02, 1 MHz square at RF7 = PIC32_ADC node, `bench/2026-11-02-tone/`)
| Path | samples per 1 MHz period | verdict |
| --- | --- | --- |
| `acq 8` (DMA, 50 ns) | 20 | **20 Msps proven** |
| `acq 4` (DMA, 25 ns triggers) | 20, no duplicates | **DMA ceiling proven** (every other trigger lost) |
| `acqcpu` 25 ns, phases 0/1/2/4/5/6/8 | 40 but every value twice | 40 reads/s of a 20 Msps stream — **not 40 Msps** |
| `acqcpu` phases 3 (1 of 2 runs) / 7 | 40, un-duplicated, plateau slope halves | distinct 25 ns samples exist, but the values carry a **+425 LSB offset** (same amplitude) — reading an intermediate/uncorrected result? unusable until understood |
| `acqil 16` | 3 of 4 runs: CH0 100 ns, **CH1 200 ns** (fill 412 µs); 1 of 4: both 100 ns (206 µs) | two transfers per 100 ns = exactly the 50 ns DMA cost → **zero margin, phase-luck**; session-06 19.87 M was a lucky run |
| `acq 8` intermittent | 2 of 5 runs fill 218–232 µs, periods 13–17 | open issue (interrupt/SFR traffic during capture?) |

Clock facts settled the same day: 200 MHz CPU is the **rated** maximum (DS70005592 OS25 TCY ≥ 5 ns,
3.0–3.6 V, flash wait states fixed at 3), not an overclock. 160 MHz is only a PLL-sharing constraint
(CPU Fout vs ADC VCO/(2·INTDIV)). VCO 1000 → CPU 200 + ADC 250 MHz = **25 Msps clean DMA (40 ns)
with no PLL2**; PLL2 (VCO 640 → 320 MHz, CLKGEN6 source 1000) needed only for the 40 Msps core.

## After the clock change (pic 0.1.20 / rp 0.1.28, 2026-11-02, session 08 part 2, `bench/2026-11-02-tone/clk200*`)
PLL1 VCO 1000 MHz: CPU **200 MHz** (rated max, not an overclock), ADC **250 MHz** (TAD 62.5 MHz), SCCP counts **5 ns**,
Timer1 tick **80 ns**. One PLL cannot give 200 MHz Fout and 320 MHz VCO-div at once; 320 MHz for the ADC needs PLL2 (todo).
| Path | Measured (1 MHz tone) | Why |
| --- | --- | --- |
| ADC core | **32.04 ns / conversion** (`ADCBB 4095` = 1640 ticks) | 1.5 + 0.5 TAD at 16 ns |
| DMA | **40 ns / transfer**: `acq 4` (20 ns triggers) = 164.6 µs, 25 samples/period, even/odd steps equal → **uniform 25 Msps, the new default** | 4 standard-bus clocks at 100 MHz; the 32 ns ADC ignores every other 20 ns trigger |
| `acq 8` (40 ns triggers) | 226 µs, 18–19 samples/period, regular drops | trigger period = DMA cost is a **razor edge** (div 8 at 160 MHz had been the same edge and worked by phase luck); div 5/6 jitter, div 10 = clean 20 Msps |
| `navg 2` | sequence ≈ 2 × 32 + 40 = 104 ns → div ≥ 21 | per-trigger overhead unchanged (~40 ns) |
| `acqil` | **parked**: two channels × two 32 ns conversions = 128 ns of core time per period, cannot fit 100–120 ns | needs the 320 MHz ADC clock (PLL2) |
| `acqcpu` | 8-cycle (40 ns) reads after `acq 4` give a 25 Msps copy (phase-dependent duplicates); 4-cycle 20 ns reads = 64 % duplicates | CPU 200 / ADC 250 share the PLL at 4:5, no integer lock any more; stays an experiment |
Rule learned: **never set the trigger period equal to the DMA cost — over-trigger and let the ADC busy time decimate.**
Also: `navg`/`div`/`in` persist on the PIC between `acq` calls; `acq 8 0 9` after `acq 16 0 9 2` runs with navg 2.

## What it means for minus
- **Default capture = `acq` (div 4 since pic 0.1.20) = uniform 25 Msps via DMA**, tone-proven; was div 8 = 20 Msps at 160 MHz. Nyquist 12.5 MHz covers 3–5 MHz probes.
- Route (b) below is **dead at 160 MHz** (duplicated reads / offset reads, session 08); route (d) `acqil` has **no DMA margin** at 160 MHz. Both point at the 200 MHz CPU step.
- The "40 Msps ADC" is sized for 20 channels / oversampling, not for single-channel streaming; the
  peripheral-to-RAM path is the limit. Routes to real 40 Msps raw: (a) CPU at 200 MHz → 5-cycle loop
  with slack (needs PLL2 for the 320 MHz ADC clock; also lifts the DMA to 25 Msps); (b) keep the
  CPU-loop at 160 MHz and prove/tune the phase with a known tone; (c) `navg` sums (boxcar-N, 40 Msps
  inside each burst); (d) **`acqil` = two-channel interleave: 20 M 2-sums/s today**, i.e. 40 Msps
  boxcar-2 decimated by 2 (13-bit), the practical answer to "20 Msps integrated over 2 samples".
- Any capture-time code must keep the CPU off the SFR bus (NOP poll every ~1024 cycles, or
  interrupt + `pwrsav #1`). Timer1 is read only after DONE.

## Related
[[0008-devkit-minUS_10102026]] (board + bench state), `firmware/README.md` command table,
`docs/claude/specs/2026-10-27-acq-design.md` §11, `docs/claude/log/2026-10-28-session-06.md`.
