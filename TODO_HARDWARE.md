# TODO_HARDWARE — changes for the next board revision

**Current board:** minus v1.1 ("board 3"), KiCad project in [`hardware/`](hardware/),
firmware rp 1.1.3 / pic 1.1.0. Items below come from the bench bring-up (session logs in `docs/claude/log/`,
campaigns in `docs/bench/2026-11-19-*`), the datasheet errata (E1–E11, `datasheet/minus-datasheet.pdf`) and the
design reviews (repo memory `docs/claude/memory/0014`, `0016`, `0017`, `0020`).

Legend: **[must]** blocks a function or an order · **[should]** works today with a workaround · **[nice]** convenience.
The devkit (`minUS_10102026`) list this file used to hold is summarised at the end; the full text is in git
history (this file before 2026-11-19).

## Before the next order

- **[must] U3 = MIC4427YMM (LCSC C152165) — done in the design files 2026-11-21:** schematic (value, datasheet, LCSC),
  PCB footprint fields and `hardware/production/bom.csv` now say MIC4427YMM / C152165 (was TC4427AEUA713 / C628548, out
  of stock). Same MSOP-8 footprint and pin order. Still to do: check live stock at order time (13 on 2026-10-24);
  fallback TC4427AEOA713 (C20551, SOIC-8, footprint change). Datasheet E9.
- **[should] TX at +5 V during power-up (E1) — in schematic + placed, routing pending (2026-11-21):** GPIO9
  (`RP2354 PIO-PWM_L` → U3 IN B → Q1 P-FET) had no pull-up, so the RP2350 pad pull-down turned Q1 on until the firmware
  idled the pins (a few ms). Added **R70 10 kΩ pull-up GPIO9 → +3V3_DVDD** and **R71 10 kΩ pull-down GPIO8
  (`RP2354 PIO-PWM_H`) → GND** (0402, LCSC C25744 like R18), sheet PULSER/PUSH_PULL; footprints placed below U3, next to its input pins 2/4.
  Routed by the owner 2026-11-21; still to do: re-export JLC outputs.
- **[should] Single-connector probe (E11) — in schematic + placed, routing pending (2026-11-21):** **R69 0 Ω between TX**
  (`Transducer`, Q1/Q2 drains, RF3/RF1/H5) **and RX** (`TRANSDUCER`, C45, RF22/RF23/H10), so a single-element probe works
  without an external tee. 0402, LCSC C844673 like R29, sheet RX_FRONT_END/TRANSDUCER; footprint placed below RF1.
  **R69 is fitted by default** (owner, 2026-11-21): TX and RX are joined, either connector drives and receives. RX is
  protected by C45 10 nF + D2 BAV99 (±0.6 V). Remove R69 (or mark it DNP in the BOM) for separate TX/RX probes.
  Routed by the owner 2026-11-21; still to do: re-export JLC outputs.
- **[should] Gain-mux select pull-downs — in schematic + placed, routing pending (2026-11-21, owner):** **R72 10 kΩ
  `RP_GC1` (GPIO25 → U1 S0, pin 10) → GND** and **R73 10 kΩ `RP_GC2` (GPIO23 → U1 S1, pin 9) → GND** (0402, C25744 like
  R33), sheet RX_FRONT_END/FE_A. Defined 74HC4052 selects (leg 0, Rf 2.2 k) while the RP is in reset/boot; 10 kΩ rather
  than 100 kΩ so it also stays below the ~8.2 kΩ-class external pull-down suggested for the RP2350 GPIO erratum E9 (to
  confirm for our stepping). Footprints: R72 above U1, R73 between C87/C86 (nearest free spots). Routed by the owner 2026-11-21.
- **[should] In1 GND plane slots (review 2026-11-21):** `TRANSDUCER` (R69 → H10, 22.5 mm) and `+3V3_DVDD` (R70 feed,
  18.5 mm, crossed by SPI_CLK/CS/MOSI on F.Cu) are routed on In1.Cu, a solid GND plane → move to B.Cu. Also remove the two
  0.1 mm In1 stubs on Net-(U9-RP38/PWM4L/RC5) near (107.5, 93.6).
- **[should] DRC:** the two silkscreen QR codes cause all 25 remaining clearance errors — keep one, on a clear area.
  Delete the dangling stubs on OA2OUT, PIC32_ADC, AVDD; enlarge the C5 reference text.

## Signal chain

- **[should] Anti-alias filter:** C86/C87 56 pF → ~100 pF (corner ~10.6 → ~6 MHz).
- **[should] Interference lines (E5)** at 2.72 MHz (in band) and 0.49 MHz enter at the front end and are up to half the
  in-band noise at high gain. Find the source (supply / RP / LP5562 or OSC1 harmonics / layout) before the next
  layout; at least extra filtering on the LNA supply and Vmid.
- **[should] Period-4 fixed pattern (E4):** a 10.5 LSB rms pattern locked to the sample clock on external ADC inputs,
  removed in firmware (`pc`), coupling path not found. Check ADC reference/AVDD decoupling and the routing of the ADC
  node near digital lines (DMA/bus activity).
- **[should] LNA output tap (E6):** input 1 (AD1AN1) reads 26 mV rms of flat, aliased wideband noise that does not
  reach OA1OUT, and sits at a 1.06 V baseline. Add a series R (and/or RC) before the PIC pin, or drop the tap.
- **[should] OA2 gain 10–20 % above nominal** (bench 2026-11-19, `docs/bench/2026-11-19-gain/`): check the 4052 Ron
  and C44 in the gain leg; consider Rf values that absorb Ron.
- **[nice] Internal AVDD channel (E10)** reads 3480 instead of 3840 codes (internal references need SAMC ≥ 3): check
  AVDD/ADC-reference filtering.
- **[nice]** DNP Cf (1–3 pF) OUT→IN− on OA1/OA2; optional 1–10 kΩ bleed at the D2 node; 100 kΩ pull-downs on the
  4052 S0/S1 (today the RP2350 pad pull-downs hold them at reset).

## Timing and data path

- **[should] Common clock for pulse and sampling (E2/E3):** the RP fires the pulse and the PIC samples on unrelated
  clocks (RP 12 MHz oscillator U7, PIC internal FRC ±1.5 %, no crystal). Shot to shot the pulse falls anywhere in
  one 40 ns sample, and 14–31 % of captures slip by a whole sample (`docs/bench/2026-11-19-jitter/`). A shared
  clock (e.g. RP clock output → PIC clock input, or a PIC REFO → RP GPIN) would make the pulse-to-comb phase
  deterministic and give an absolute sample rate; route the pins even if the firmware does not use them yet.
- **[should] Faster RP↔PIC data path:** the 115 200 Bd UART makes one 4095-sample shot take ~0.9 s, which is too slow
  for live M-mode. Route the PIC SPI (or a faster UART / parallel lines into the RP PIO) between the MCUs, without
  sharing the PIC JTAG pins (TCK/TDO/TMS default on in a blank PIC).
- **[nice] Net names by direction:** `UART_TX`/`UART_RX` are RP-side names (`RP_TX_PIC_RX`, `PIC_TX_RP_RX` would be
  clearer), and `PWM_H`/`PWM_L` are swapped vs function (PWM_H drives the low-side N-FET).

## Programming, clocks, LEDs

- **[nice] Recovery ICSP header:** v1.1 has no J1; the PIC is programmed only by the RP (works: `pic flash`, ~1 s).
  A plain 6-pin 2.54 mm ICSP header (1 MCLR, 2 VDD, 3 GND, 4 PGD1, 5 PGC1, 6 NC) or test points on MCLR/PGC1/PGD1
  would allow a Microchip tool or a logic analyser for recovery.
- **[nice] OSC1 (32.768 kHz) can be DNP:** it only feeds the LP5562, and the firmware uses the LP5562 internal clock.
- **[nice]** Keep LED2 (PIC heartbeat) — the only PIC sign of life without the USB console.

## Resolved in v1.1 (from the devkit `minUS_10102026` list)

MCLR reachable by the RP (series 0 Ω, no MCLR capacitor blocking ICSP entry); RP is the only PIC programmer, no
Tag-Connect; 4052 gain selects driven by the RP (GPIO25/23); ×1 per stage via the PIC `AMPxCON1.UGE` bit (no 0 Ω
Rf needed); RX on its own net with 10 nF DC blocks and a BAV99 clamp antiparallel to GND; BGA2817 LNA terminated in
51 Ω; Vmid-biased, AC-coupled op-amp stages (the devkit's ground-referenced FE-A and RX bias conflict are gone);
ADC node on ADC2 (AD2AN9) with a buffered path; AVDD via a ferrite; digipots, external op-amps, HV parts and the
SPI MOSI/MISO coupling resistors removed; the WS2812/SK6812 pair replaced by an LP5562 driver (`rgb`, rp ≥ 1.1.1).
Board 1 (dead PIC) and board 2 were devkits; board 3 (`7D4466C63B374C98`) is the v1.1 reference unit.
