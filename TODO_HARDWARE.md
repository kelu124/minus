# TODO_HARDWARE — corrections for the next revision of the minus devkit

Board under test: `hardware/minUS_10102026` (JLCPCB batch, 2 boards). This file lists what the
next hardware revision must change, learned while bringing up this one. Keep it updated as the
exploration progresses (session logs in `docs/claude/log/`, flaw review in
`design/devkit/review-findings.md`, as-built notes in `docs/claude/memory/0008-*.md`).

Legend: **[must]** blocks a function · **[should]** works with rework · **[nice]** convenience.

## PIC32 reset / programming (ICSP from the RP2354A)

- **[must] R53 → 0 Ω** (GPIO24 → MCLR node). As built (4.7 kΩ against R5 10 kΩ) the RP cannot pull
  MCLR below VIL; measured 2.88 V on board 1. Both boards were reworked by shorting R53.
  Alternative: drive MCLR from the RP through a small N-FET (open-drain) so J1/PICkit can share it.
- **[must] No capacitor on MCLR when ICSP is driven by the RP.** C31 (470 nF via JP1) kills the
  ≥ 20 ns / < 2 µs reset blip the entry sequence needs. Either drop C31 or keep JP1 as a *normally
  open* solder jumper; note the current footprint has no copper bridge, so assembly may or may
  not close it (board 1 had to be cut, board 2 came open). Document the default on the silkscreen.
- **[should] Keep R17/R18 (RP SWD ↔ J1)** but remember the RP2350 SWCLK/SWDIO pads default to
  pull-ups: they pulled PGC1/PGD1 high through 47 Ω and faked a "PIC alive" reading. Firmware now
  disables those pulls; a cleaner board puts the RP SWD on its own header and leaves J1 as a pure
  Microchip ICSP connector (pins 1 MCLR, 2 VDD, 3 GND, 4 PGD1, 5 PGC1).
- **[nice] Second ICSP pair reachable without a jumper:** PGD2 = RA0 is already the TRIG line
  (GPIO6); route PGC2 = RA1 to a spare RP GPIO (today it only reaches H2.16) so a board can be
  diagnosed on two pairs without a flying wire.
- **[must] Remove the Tag-Connect footprint (J1).** Replace it with a plain 6-pin 2.54 mm ICSP
  header (1 MCLR, 2 VDD, 3 GND, 4 PGD1, 5 PGC1, 6 NC — Snap / PICkit Basic pin order) so a
  programmer, a meter or an analyser can be attached without a special cable or pogo pins.
  (Owner decision 2026-10-28.)
- **[nice] Test points** on MCLR (PIC side of R9), PGC1, PGD1: the Tag-Connect pads are 1 mm and
  hard to probe with hook clips; a 1 Hz MCLR blink was needed to find pad 1 on the analyser.

## RP ↔ PIC bus (from the 2026-10-26 schematic review, memory 0008)

- **[must] R68 ‖ R69 = 50 Ω between SPI_MOSI and SPI_MISO** (MCP4131 SDI/SDO coupling): keep one
  resistor of 1–4.7 kΩ. Removing both kills the digipot writes.
- **[should] JTAG defaults on and hijacks the SPI pins** (TCK = RD1, TDO = RD2, TMS = RB1): the PIC
  firmware sets `JTAGEN = OFF`; a blank PIC cannot talk SPI. Prefer not sharing SPI with JTAG pins.
- **[should] Bus ownership:** the RP is the only master of the digipots (SPI MCP4131, I²C
  MCP4531/MCP4728); the PIC's SPI/I²C pins must stay Hi-Z or get their own bus.

## Naming

- **[nice] Name the UART nets by direction** (e.g. `RP_TX_PIC_RX`, `PIC_TX_RP_RX`): `UART_TX`/`UART_RX`
  are RP-side names and the first PIC firmware mapped them the wrong way round (both chips drove
  the same wire until it was caught on 2026-10-28). Same for `SPI_MOSI/MISO`, `TRIG`, `RDY`.

## Power / clocks / LEDs

- **[should] PIC crystal:** no crystal on the PIC (OSC pins only on H2); everything runs on the
  FRC (8 MHz ± 1.5 %). Fine for 115200 baud and a 40 Msps capture whose rate is reported, not
  trusted; add a crystal footprint if absolute sample timing matters.
- **[should] WS2812 (U5) and SK6812 (LED1) DIN in parallel on GPIO10**, 5 V parts driven at 3.3 V
  logic: marginal; use one LED and a level shifter or a 3.3 V-tolerant part.
- **[nice] LED2 (red, PIC RC5)** is the only PIC sign of life; keep it. On board 1 it is lit steady
  with a blank/dead PIC (RC5 stuck high) — a useful symptom.

## Analog path — first measurements (board 2, 2026-10-28)

- **[should] The bare ADC node needs a low-impedance driver.** With no FE path connected the node
  sits on the R43/R44 10 k‖10 k bias (≈ 5 kΩ source) and the 12-bit ADC cannot charge its hold
  capacitor in a 6.25 ns sampling window: the reading settles over ~60 samples and the mean drops
  from 1.58 V (slow rate, long sampling) to 1.07 V at 26 Msps. Every FE path (op-amp output
  through 100 Ω) must stay connected, or add a buffer at the node; keep the bias divider but make
  it ≤ 1 kΩ Thevenin or AC-couple into a buffered mid-rail.
- **[nice] Trigger-rate observation:** the SCCP1-triggered ADC + DMA chain tops out at ~26.6 Msps
  (one 16-bit DMA transfer per ~6 CPU clocks); 40 Msps needs a different data path (CPU loop or
  the ADC's own buffering). Not a board issue, noted for the design (RP2350 PIO/SPI readout vs
  PIC DMA).

- **[should] FE-A (PIC op-amps) is ground-referenced:** the RX node (`OA1IN+`) is clamped to ±0.6 V
  around GND by D7 and OA1's gain leg R47 goes to GND, so on the single 3.3 V supply OA1 (×11) and
  OA2 can only reproduce the positive half of the echo. Next revision: AC-couple the RX node into
  OA1IN+ with a mid-rail bias (2 × R to 1.65 V), reference R47 to the same mid-rail, and clamp D7
  around that bias instead of GND. Same for OA2/OA3 if used as gain stages.
- **[must] RX node bias conflict:** R28/R36 (50 Ω) DC-couple the RX node to the OPA847/LMH6629
  non-inverting inputs, which are biased at 2.5 V (10k/10k from 5 V), while D7 clamps the node to
  ±0.6 V around GND: as built, the node sits at ≈ +0.6 V and both external op-amp inputs are
  pulled off their bias. Fix: one bias domain for the node (series cap after the T/R switch, 2 × R
  to a mid-rail, clamp D7 around that rail) and AC-couple every FE input to it (R28/R36 → C + R);
  OA1/OA2 gain legs R47/R49 get a series cap (DC gain 1) or the same mid-rail reference.
- **[nice] OA1OUT is also AD1AN0**: the op-amp output can be sampled with no external wiring
  (`PINSEL 0`), which bypasses the node's clamp and anti-alias filter; a 0 Ω option from OA1OUT to
  the ADC-node input (H5) would make the filtered path jumper-free too.

## Analog path (from `design/devkit/review-findings.md`, not yet re-checked on hardware)

- Gain distribution / digipot bandwidth, anti-alias RC corner (~6–8 MHz), LVP-only programming
  (never 9 V VPP on the shared ICSP net), HV P-FET gate drive — see sections B–E of the review.

## Assembly / batch notes

- Board 1 (RP id `11A3B335E9E91355`): PIC32AK **dead** (silent on ICSP pairs 1 and 2 with the full
  entry sequence verified by logic analyser at its pins; MCLR pin sinks ~16 µA). U2 to be replaced.
- Board 2 (RP id `3E47314186FE29C3`): PIC answers ICSP (2026-10-28).
- The U2 QFP-48 footprint is an EasyEDA import placed at 90°; orientation was correct on board 1.
  Keep a clear pin-1 mark on the silkscreen.

- **2026-10-28 measured (board 2, firmware `acq 8 0 1` / `acq 8 0 0`):** RX node (OA1IN+) = **0.596 V** DC
  — exactly the D7 clamp fed by the R28/R36 paths — and OA1OUT = **3.27 V** (×11 → rail). With `AMP1 0`
  OA1OUT falls to 0.03 V, so the op amp works and is simply saturated. Until D7/R28/R36 are fixed, the
  PIC op-amp path cannot show an echo.
