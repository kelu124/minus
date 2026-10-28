# Design — `acq`: 4095-sample ADC capture on the PIC32AK, returned to the RP2354 console

Date: 2026-10-27. Status: **approved by the owner 2026-10-27** (fallback: build for 40 Msps, decide on the bench). Owner decisions (2026-10-27): **40 Msps full
speed**, input = **common ADC node AD1AN9 / RA9**, **start immediately on the command**, output =
**one decimal value per line on the RP USB console**, `rpcli.py` can save it to a file.

## 1. Intent

Give the devkit its first look at the analog path: type `acq` on the RP2354 USB console and get
4095 raw 12-bit samples of the PIC's ADC input back, so a tone or pulse injected at the ADC SMA (or a
real echo later) can be plotted on the PC. This is the first step of "PIC = capture engine"
(memory 0007/0008), after the link bring-up (`ping`) and before any pulser/TX work.

## 2. Goals / non-goals / anti-goals

- **Goals:** (1) one RP command → one PIC capture → values on the console; (2) the real sample
  rate is **measured and reported**, not assumed; (3) both firmwares still build headless; (4) the
  link protocol stays line-based ASCII for commands, with one binary payload for the data.
- **Non-goals (now):** TRIG/pulser synchronisation, selectable rate or input from the command,
  continuous streaming, gain/digipot control, higher UART baud, FE-A op-amp path (AD2AN1).
- **Anti-goals:** a capture that silently drops samples and looks like a clean 40 Msps record;
  a protocol that leaves the RP waiting forever when the PIC is absent or blank.

## 3. Hardware facts used (from the schematic netlist + DS70005592 + DS70005583)

| Item | Value | Source |
| --- | --- | --- |
| ADC node net `PIC32_ADC` | PIC pin 5 = **AD1AN9 / AD1ANN3 / RP10 / RA9** | `kicad-cli` netlist of `hardware/minUS_10102026` |
| ADC | 2 cores, 12-bit, ≤ 40 Msps, clock CLKGEN6 ≤ 320 MHz, TAD = clock/4, conversion 1.5 TAD + sample ≥ 0.5 TAD | DS70005592 §18.1, §18.4.3 |
| RAM | **16 KB** (0x4000–0x7FFF); 4095 × u16 = 8190 B | datasheet p.1, `.gld` |
| CPU/PLL | FRC 8 MHz; PLL VCO 500–1600 MHz; datasheet example: VCO 640 → CPU 160 MHz, ADC 320 MHz | Example 18-3 "OscillatorInitialization", OS51 |
| UART baud clock | CLKSEL=0 = "Standard Speed Peripheral Clock" = **system clock / 2** | Table 21-2, Table 26-2 note |
| Per-sample ADC trigger | TRG1SRC 01100 = "SCCP1 Trigger out" (time-base rollover, period = CCP1PR+1 clocks, clock = CLKGEN12 or peripheral clock) | Table 18-3, §27.4 |
| DMA trigger | Table 16-2: 0x2B = "ADC1 – AN0" … 0x3E = "ADC1 – AN19" (20 entries ⇒ **channel** numbers) | §16.4.3 |
| PWM as trigger | rejected: minimum period 0x100 counts ⇒ ≤ 25 MHz | Table 17-35 |
| Link | UART1 RP39/RP40 ↔ RP GPIO16/17, 115200 8N1 | firmware/README.md |

## 4. Protocol (RP ↔ PIC), PROTO_VERSION 1 → 2

```
RP → PIC:  ACQ\n
PIC → RP:  ACQ <n> <ticks> <tick_ns> <status>\n      status: ok | timeout | dmaerr | overrun | notready
           <n × u16 little-endian>                     only when status == ok
```
- `n` = 4095 (constant `ACQ_N`), samples **unsigned 12-bit right-aligned** (0–4095, full scale AVDD).
- `ticks` = Timer1 count between "trigger timer started" and "DMA done", `tick_ns` = Timer1 period
  in ns (100) so the RP prints the **effective sample rate** = n / (ticks·tick) without
  trusting the nominal 40 Msps. Expected fill time ≈ 102.4 µs.
- `timeout` = DMA did not finish within 5 ms (trigger or DMA path broken) → no payload.
- Binary payload at 115200 baud ≈ 0.71 s; the RP reads it with a 1.5 s deadline and reports a
  short read (`acq: short payload, got X of 8190 bytes`) instead of hanging.
- **Recovery (my call):** no PIC-side abort. The PIC always finishes sending the payload; the RP
  side `link_flush_rx()` becomes "drain until the link has been idle for 50 ms" and every command
  (`ping`, `raw`, `acq`, …) calls it first, so a timed-out `acq` cannot poison the next command.
- **Rate measurement is relative, not absolute (my call):** Timer1 and the SCCP trigger share the
  FRC→PLL chain, so the printed `fs` detects missed samples (DMA/trigger shortfall) but not the
  FRC's ±1.5 % absolute error. That is the anti-goal we care about (silent drops). The RP prints
  the FRC tolerance in the header comment; an absolute check (RP-timed via RDY) is a follow-up.

## 5. PIC side (`firmware/pic32/main.c`, fw 0.1.0 → 0.1.1)

1. **Clocks (new, executed at boot):** PLL1 from FRC: PLLPRE 1, PLLFBDIV 80 → VCO 640 MHz;
   POSTDIV1 4, POSTDIV2 1 → Fout **160 MHz** → CLKGEN1 (NOSC 5) = CPU/peripheral; VCO1DIV
   INTDIV 1 → **320 MHz** → CLKGEN6 (NOSC 7) = ADC. CLKGEN12 (NOSC 5, 160 MHz) = SCCP. This is the
   datasheet's own sequence (Example 18-3), chosen over 200 MHz CPU because one PLL then serves
   both CPU and ADC. `FCY` = 160 MHz, standard peripheral clock = 80 MHz.
2. **UART1 baud clock fix:** `U1BRG = 80 MHz / 115200 = 694` (fractional mode). The 0.1.0 code
   assumed FUART = 8 MHz where the datasheet says system/2; never exercised on hardware.
   Heartbeat divider scaled ×20.
3. **ADC1:** `ANSELA9 = 1`, `TRISA9 = 1`; `AD1CON.ON = 1`, wait `ADRDY`. Channel 0:
   `PINSEL 9`, `MODE 0` (single sample per trigger), `SAMC 0` (0.5 TAD), `DIFF 0`, `TRG1SRC 12`
   (SCCP1 trigger out). Result register `AD1CH0DATA`.
4. **SCCP1 as 40 MHz trigger:** 16-bit timer mode (`MOD 0`, `T32 0`), `CLKSEL 1` (CLKGEN12),
   `TMRPS 0`, `SYNC 0`, `CCP1PR = ACQ_TRIG_DIV - 1` with `ACQ_TRIG_DIV = 4` (160 MHz / 4 = 40 MHz).
   Timer is **ON only during a capture**. One `#define` to drop to 20 Msps (`8`).
5. **DMA0:** `DMACON.ON`, `DMALOW/DMAHIGH` = RAM span, `DMA0SRC = &AD1CH0DATA`,
   `DMA0DST = acq_buf`, `DMA0CNT = 4095`, `SIZE 1` (16-bit), `SAMODE 0`, `DAMODE 1`,
   `TRMODE 0` (one-shot), `DMA0SEL.CHSEL = 0x2B` (ADC1 channel 0 ready). Clear all DMA0STAT flags,
   `CHEN 1`, then start the SCCP timer, then poll `DMA0STAT.DONE` with a 5 ms deadline; stop timer;
   read Timer1; report `dmaerr` (ADRERR/BRERR/BWERR), `timeout`, or `overrun` (OVERRUN = a trigger
   arrived mid-transfer = dropped samples) before `ok`.
   `static uint16_t acq_buf[4095]` (8190 B of 16 KB RAM).
6. **Timer1** free-running 16-bit, prescaler **1:8** on the 80 MHz peripheral clock (100 ns/tick,
   6.5 ms range > the 5 ms DMA deadline, so a slow-but-completing capture cannot wrap and report a
   bogus rate; 0.1 % resolution over the expected 102 µs) — reset to 0 just before the SCCP start,
   read at DONE. *(Builder-check call: 1:1 would wrap at 819 µs.)*
7. **Command loop:** `ACQ` → `acq_run()` → header line → payload via `uart1_putc` loop. Also keep
   `PING/ID?/TRIG?`. `ID?` now reports proto 2.

## 6. RP side (`firmware/rp2354/main.c`, fw 0.1.3 → 0.1.4)

- New CLI command **`acq`**: flush link, send `ACQ\n`, `link_readline` header (500 ms), parse;
  on `ERR`/timeout print and return; read `2n` bytes with a 1.5 s deadline; then print
  `# acq n=4095 fill=102.4us fs=39.98Msps (nominal 40.00)` and 4095 lines `<value>`.
- Add to `help()` and to the command table in `firmware/README.md`; `PROTO_VERSION 2`.
- `tools/rpcli.py`: new `--out=FILE` writes the reply text of the last command to FILE (values are
  plain integers, one per line; comment lines start with `#`), e.g.
  `python3 tools/rpcli.py /dev/ttyACM0 acq --wait=3 --out=capture.csv`.

## 7. Verification plan

1. `make -C firmware/pic32` and the RP CMake build both succeed; RP image embeds the new PIC hex.
2. Bench (after R53 → 0 Ω and `pic flash`): `ping` ok → `acq`. With the ADC SMA open/biased: a
   flat line near mid-scale; with a 1–3 MHz tone injected: a sine at the right period
   (e.g. 2 MHz → 20 samples/period at 40 Msps).
3. Rate check: printed `fs` within ~0.5 % of 40 Msps (relative to the PIC's own clock) **and**
   `fill` ≈ 102 µs. If `fs` is lower or
   `status=timeout`, the DMA (or the trigger) cannot keep 40 Msps → set `ACQ_TRIG_DIV 8`
   (20 Msps) and record the finding; a CPU-loop reader is the next option for 40 Msps.
4. `ping` still works at the new clock (validates the UART baud fix).

## 8. Risks / unknowns (checked on hardware, not resolvable from the docs)

- **DMA throughput at 40 M transfers/s** is not specified; the measured fill time decides.
- **SCCP "Trigger out"**: implemented as the 32-bit Timer mode (T32 = 1) TMR == PR match, which
  the datasheet (§27.4.2.2, Example 18-10) says raises the Special Event Trigger; the dual-16-bit
  mode would instead need CCPxRB (§27.4.2.1.1). If the bench shows 32 MHz instead of 40, the period
  is PR + 2 → `CCP1PR = ACQ_TRIG_DIV - 2`.
- **DMA CHSEL** = 0x2B assumes "ADC1 – AN0" means channel 0; if DMA never triggers, try 0x34 (AN9).
- **PLL/clock bring-up** is untested on this board (FRC-only so far); PING at the new clock is the
  first proof. BIST/WDT untouched.
- RAM: 8 KB buffer + stack in 16 KB — linker map checked after build.

## 8b. Deliverable / stopping point (owner to confirm)

The board is off the bench (R53 rework pending, PIC never flashed). This change is **done when
both firmwares build headless, the RP image embeds the new PIC hex, and the register sequence
has been reviewed against the datasheet**; §7 bench steps run when the board returns. If the bench
then shows the DMA cannot sustain 40 Msps, the fallback is decided at that point (owner decision
2026-10-27: no CPU-loop reader in this change; `ACQ_TRIG_DIV` is the only knob).

## 9. Left to the builder

Exact register write order and waits (follow the datasheet examples quoted above), timeout
values, header string format details, `rpcli.py` option name, README wording.

## 10. Not in this change (follow-ups in TODO)

`acq trig` (arm + TRIG edge), rate/input arguments, FE-A path (ADC2), packed 12-bit transfer or a
faster link baud, continuous mode, TX/RX sequencing.

## 11. Bench findings 2026-10-28 (session 06) — supersede §8

- **Risk "DMA throughput" resolved:** one 16-bit transfer per 4 standard-bus clocks (8 CPU clocks,
  50 ns at 160 MHz) → **20 Msps ceiling**, `ACQ_TRIG_DIV` default is now 8. At div 4–6 exactly every
  other trigger is lost (no overrun flag: a trigger arriving while the channel is busy is simply ignored).
- **The §5.5 poll loop was wrong:** polling `DMA0STAT`/`TMR1` back-to-back makes the CPU win the SFR bus
  and the DMA then *duplicates* samples (~30 %, visible as repeated values in the settling ramp) while
  appearing faster than the trigger (the "26.6 Msps" of session 05 and the non-linear div table). The
  wait loop now polls once per ~1024 NOPs and counts iterations instead of reading Timer1.
- **SCCP period semantics confirmed:** period = `div` × 6.25 ns (div 8 → 50.3 ns, 16 → 100.5 ns,
  32 → 195 ns RP-timed; the FRC is ≈ +0.5 % slow).
- **ADC core:** 4095 back-to-back conversions in 102.6 µs = 25.05 ns each — the 40 Msps is real.
  Integration/oversampling modes work (`navg`), each triggered sequence costs ≈ 40 ns extra.
- **Inputs:** `in` selects AD1AN9 (node), AD1AN0 (OA1OUT, op amp 1 on), AD1AN1 (OA1IN+). OA1OUT reads the
  rail (3.27 V) because the RX node sits at the D7 clamp (0.60 V) × 11 → TODO_HARDWARE bias fix.
- **CPU-loop reader (`ACQCPU`):** 4 cycles per read, phase-locked; clean at 50 ns triggers, marginal at
  25 ns (CPU reads collide with the ADC result write). Back-to-back / repeat-timer trigger sources do
  not fire in single-sample mode on this part.

## 12. Two-channel interleave (2026-10-28, `acqil`, pic 0.1.19 / rp 0.1.27)
- Goal: "20 Msps integrated over 2 samples". One channel cannot (§11: 88 ns per 2-sum; TRG1SRC 2/3 are
  Reserved so no self-retrigger; oversampling starts at 4).
- Build: ADC1 CH0 (TRG1SRC 12 = SCCP1) and CH1 (TRG1SRC 13 = SCCP2) both PINSEL = last input, MODE 2,
  TRG2SRC 2, CNT = navg (2). SCCP2 = copy of SCCP1 with CCP2TMR preloaded `off` (default div/2+1) so it
  fires about half a period after/before CH0. DMA0 ← AD1CH0DATA → acq_buf[0..2047), DMA1 (CHSEL 0x2C) ←
  AD1CH1DATA → acq_buf1[2047]; after both DONE the halves are merged backwards in place into acq_buf
  (CH0[i], CH1[i]). Reply = `ACQ 4094 …` so the RP path is unchanged.
- Measured (`acqil 16`): 206.0 µs → 19.87 M sums/s, no overrun; `acq 16 0 9 2` single channel 9.94 M/s.
  Even/odd tail means equal (−0.0 / +0.1 LSB) for off 5, 9, 12 → the saturated ADC core packs the four
  conversions per 100 ns on its 25 ns grid, so the trigger phase does not matter. div 20 → 10–22 LSB
  channel offset (5 slots per channel cannot split evenly); `acqil 32 0 4` 4-sums 9.94 M/s clean;
  `acqil 24 0 4` overload (fill 929 µs, scrambled order). Pending: tone test.
