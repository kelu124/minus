# 0007 — DesignA + DesignA-DK devkit (RP2354A + PIC32AK)

**Status:** active design direction (as of 2026-09-21) · type: project

## The concept
A cheap single-channel pulse-echo ultrasound board pairing:
- **RP2354A** (QFN-60, 2 MB in-package flash → no external flash; USB-C, manager, DSP,
  ICSP programmer). On LCSC/JLC: `C41378174`, ~$1.27, in stock.
- **PIC32AK** (dsPIC-based "PIC32A") as the **analog capture engine**: on-die 40 Msps
  12-bit ADC + 3× op-amps (RX gain) + HS-PWM (pulser + ADC trigger). **Not LCSC/JLC
  stocked** (Digikey/consign) — the one N2 sourcing risk. Datasheet DS70005592, flash spec
  DS70005583 (in `pdfs/datasheets/`, with `.md` siblings). Reuses the owner's
  **[[minus-overview]]**-family board **kelu124/pic32arick** (push-pull pulser + TC4427A,
  3-op-amp gain chain + MCP4531 I²C digipot, MD0100 T/R, ICSP header).

## Files
- `design/designA/` — the cheap product board (README + `toolchain_designA.md` Ubuntu CLI/
  Makefile: RP2354 pico-sdk→uf2, PIC32 XC-DSC→hex via ipecmd/PICkit).
- `design/pic32/` — concept/trade study (`README.md`) + `pic32.md` (ICSP/flashing).
- `design/devkit/` — **DesignA-DK**: large, one-board, **jumper-selected** derisk board
  (no daughter-cards). `README.md` (full), `pcb-brief.md` (shareable handoff),
  `review-findings.md` (the flaw review).

## Key locked decisions
- **No TGC** — per-line settable gain only (digipot). Gain lives in a resistor ratio.
- **Single-supply ADC** (0→VREF=AVDD, no external VREF pin): 0-centred RF must be
  AC-coupled + biased to mid-rail (1.65 V) + scaled to ~2.6–2.8 Vpp; never bipolar.
- **TX↔ADC tightly coupled** via PIC HS-PWM emitting the ADC trigger off the same counter
  (PIC-owns-TX = zero jitter; needed for coherent averaging). JP1 selects PIC HS-PWM vs
  RP2354 PIO to the pulser.
- **Devkit swaps front-ends by jumper** (FE-0 straight … FE-A PIC-opamp … FE-B LNA+opamp
  … FE-C AD8331 … FE-D AD8338) on a common RX node → ADC node.

## Design review (2026-09-21) — 4-agent flaw audit → `design/devkit/review-findings.md`
Confirmed **datasheet corrections applied**: no external VREF pin (ref=AVDD); op-amp
100 MHz/100 V/µs is High-Power only (LP=50 MHz/10 V/µs), offset ±3 mV max; ADC ENOB ≈10.5;
op-amp input noise **unspecified** (LNA need is bench-only); TC4427A has **no internal
dead-time** and is **8-pin** (not SOT-23-5). Top open flaws: gain-vs-GBW caps usable gain
≈+34 dB (B1); digipot-as-small-Rg invalid at high gain (B2); anti-alias corner too high
(B3); missing USB-C Rd (B4); MCLR over-voltage risk (B5); SPI **slave** SCK unverified
(B6); HV-rail incompatible with P-FET totem (B7). See the file's fix tracker.

See [[0004-key-references]] (pic32arick), [[0005-minus-direction]], [[0006-pricing-basis]].
