# Changelog

Summary of every commit to this repo, newest first.
Format: `YYYY-MM-DD  <short-sha>  summary`.

Uncommitted work sits at the top under "Pending" until it lands, then it gets
the sha.

## Pending

- Add `design/devkit/review-findings.md` — consolidated 4-agent flaw review (severity-ranked
  + fix tracker). Apply confirmed datasheet corrections across pic32/designA/devkit/pcb-brief
  (VREF=AVDD/no ext pin, op-amp HP-vs-LP 100/50 MHz + ±3mV, ENOB ~10.5, TC4427A no dead-time
  /8-pin, pulser edges ~20–30ns). Add pcb-brief §0 "must-fix before layout" (USB-C Rd, MCLR
  LVP-only, HV interlock, dead-time+JP1 pull-down, AA ~6–8MHz, gain-vs-GBW, 0Ω links, 1 I²C
  master). New memory `0007-designA-devkit.md` (+INDEX).

## Committed

- 2026-09-21  a05eef6  Add standalone `design/devkit/pcb-brief.md` — one-file PCB-designer
  handoff (overview + mermaid, power/clocks, programming, inter-MCU bus, pulser, jumper-
  selected RX front-ends + gain + ADC conditioning, connectors/taps, layout, deliverables,
  refs); linked from devkit README.

- 2026-09-21  9ba7a33  `design/devkit/`: shareable **PCB designer brief** (B1–B11) — board
  scope, power/clocks, dual programming, inter-MCU bus, pulser bench, jumper-selected RX
  front-ends + gain-control + ADC input conditioning, connectors/taps, layout guidance,
  deliverables, references.

- 2026-09-21  4a272f2  ADC input conditioning (DesignA §5a: single-supply 0→VREF, mid-rail
  bias, ~2.8 Vpp fit, clamp) + TX↔ADC hardware trigger (§5b: HS-PWM/PTG, PIC-owns-TX);
  requirements **A5**+**C1c**; pic32 §4/§3d + devkit derisk rows. Mirror full PIC32AK
  **datasheet DS70005592** (36 MB) + **flash-prog-spec DS70005583** with `.md` siblings.

- 2026-09-21  a533a39  `design/devkit/`: single board, **jumper-selected** RX paths
  (JIN_*/JOUT_* route one of FE-0…FE-D from RX node to ADC node) — no mezzanine/
  daughter-cards; gain-control via on-board jumper block; down-spec to DesignA =
  depopulate losers.

- 2026-09-21  dced415  Add `design/devkit/` — **DesignA-DK** derisking board: RP2354A +
  PIC32AK6416 (64-pin/16KB), fully broken out, swappable RX front-ends (FE-0 … FE-C/D ext
  VGA), gain-control options (I²C/SPI digipot, resistor-mux, VGA Vgain), pulser bench,
  split rails, SMA taps + loopback self-test; derisk-priority + vendor-eval path.

- 2026-09-18  d66d17c  DesignA: Ubuntu CLI+Makefile toolchain (`toolchain_designA.md`:
  RP2354 pico-sdk→uf2, PIC32A XC-DSC→hex via ipecmd/PICkit) + reuse of **kelu124/pic32arick**
  blocks — push-pull pulser (IRLML6244/2244 + TC4427A), 3-op-amp gain (OA1 fixed + MCP4531
  I²C digipot OA2 + bias OA3), MD0100 T/R, 6-pin ICSP (47Ω + Tag-Connect + off-center
  friction-fit holes). BOM ≈ $4.7 active / $6.3 board (min $5.4); pic32arick → memory 0004.

- 2026-09-18  d663709  DesignA: PIC32 direct-flash (S4a + `design/pic32/pic32.md` ICSP/
  PICkit/LVP/MCLR), pulser drive-select jumper JP1 (T4a: PIC32 HS-PWM ⟷ RP2354 PIO),
  J3 ICSP header, §6b programming, and mermaid diagrams (block / programming / sequence).

- 2026-09-18  75ad246  Add `design/designA/` — **DesignA**, the cheapest *minus* build:
  RP2354A + PIC32A, unipolar 5 V N-FET pulser (options.md U0), digipot-set per-line gain,
  PIC on-die 40 Msps ADC; active-IC BOM ≈ $3.7 / board ≈ $5. RP2354A on LCSC/JLC
  (C41378174, ~$1.27); PIC32A the only non-LCSC part.

- 2026-09-18  f219638  LCSC prices for gain/LNA ICs — price table in
  `systems/afe-vga-ics.md` + refreshed `options.md` §2. AD8331 ~$14 (in stock),
  AD603 ~$9 + $5 LNA in stock, AD8338/AD8332 OOS, LMH6629/ADA4898-1/OPA847 ~$5 in stock;
  VCA810/AD8432/AFE5808/AD9276 not LCSC-stocked (Digikey).

- 2026-09-18  90cdf6a  `systems/afe-vga-ics.md`: LNA-pairing section for VGA-only parts
  (VCA810 2.4 / AD603 1.3 nV/√Hz need a <1 nV/√Hz LNA) — OPA847/LMH6629/AD8099/AD797/
  ADA4898 op-amp LNAs + AD8432 dedicated ultrasound LNA; T/R protection; integrated-LNA
  VGAs (AD8331/AD8338/AFE5808) dominate real reference designs.

- 2026-09-18  160c089  Add `systems/afe-vga-ics.md` — survey of RX gain ICs (LNA +
  variable-gain / AFE), single-channel → 8/16-channel (AD833x, AD8338, AD603/VCA810,
  AD8332/VCA26xx, AD8334/AFE5401, AFE5808/AD9276-family/MAX2082, VCA5807, AFE5832);
  linked from systems/README, by-ic.md, options.md §2.

- 2026-09-18  0bbbd34  Confirm (RP2350 datasheet) RP2354A = 2 MB in-package flash, no
  external flash chip (QSPI_IOVDD 3.3V); BOOTSEL button wires QSPI_CSn→GND via ~1kΩ
  (same as flashless RP2350A), optionally paired with a RUN reset button.

- 2026-09-18  3b3fba3  PIC32A: LCSC/JLCPCB **not stocked** (→ consigned/Digikey);
  add `6416` (64/16) flash tier; §3c **Footprint** guidance (48-pin VQFN ~6×6 mm since
  board is already QFN; shrink RP2350 to RP2350A/RP2354A QFN-60 7×7).

- 2026-09-18  bbd048a  Session 02: `activities/possibilities.md` (workshop activity
  menu); `requirements.md` §19 anti-requirements (N1–N11) + TGC dropped (F6 per-line
  settable gain, A3/A3a/P8/A1/§17); `design/pic32/` concept (PIC32A + RP2350: BOM,
  5V pulser, gain, §3c chip choice, §3d interconnect; Digikey ~$1.6–1.9, LCSC TBD);
  new rule — Markdown sibling for every PDF via markitdown (+ `.md` for all 11 PDFs).
- 2026-09-17  828d364  Record cheaper 8-bit ADC candidates (TLC5540/ADS830/AD9280) to
  verify on LCSC; ADEC remains the open cost driver. **Pushed.**
- 2026-09-17  4c6f5cb  Real LCSC prices+URLs+stock in options; ADC bottleneck (~$33
  in-stock front-end); TXRX-LINK open question. **Pushed.**
- 2026-09-17  bc967b2  options.md trade study + options_prices.csv; analysis §3b gain
  options; 5V/±5V HV options; requirements RF-ACCESS; memory 0006. **Pushed.**

## Committed

- 2026-09-17  1a6975b  requirements: plan OSHWA cert + reserve silkscreen for the mark/UID.
- 2026-09-17  785d3c0  requirements v0.3 refinements: bipolar-if-cheap-±rail (T6),
  on-device DSP demo (S6), autonomous RGB LED (F11).
- 2026-09-17  d7f7b79  requirements.md v0.3: NDT/workshop-badge, 3–4 MHz, unipolar,
  A-/M-mode, coded excitation, multi-connector (SMA/header/uFL), precise-timing +
  gap-free-ADC controller, DP5 derisk-by-reuse, provided piezo, on-body safety.
- 2026-09-17  b21abac  requirements.md v0.2: RP2350 MCU + on-board USB-C bus-powered +
  DP1–DP4 (small/cheap/simple); external-ADC note; memory 0005. **Pushed.**

- 2026-09-17  6b64555  Draft root `requirements.md` (v0.1, MoSCoW + open-decision
  TBDs); cross-link from analysis.md; memory 0005 + docs. **Pushed.**

- 2026-09-17  0dea95f  Per-system "Piezo 1–5 MHz" + "ADC sampling" attributes (19
  sheets + template + quick-ref); root `analysis.md` (routes + light-BOM pulsers);
  `pdfs/datasheets/` pulser datasheets; memory 0005. **Pushed.**
- 2026-09-17  622bb3d  `systems/by-ic.md` (MSP430FR5043 + TUSS4470 cross-reference),
  Open Echo datasheet, `design/{biogap-wulpus-pro,open-echo}/` files. **Pushed.**
- 2026-09-17  6e0b07f  SIG-WUS OXP catalog snapshot (`systems/_sig-wus-oxp/`);
  FloPatch detail (FP120, CW 4 MHz, FDA/CE, Kenny 2021); SENS-U → TENA/Essity;
  BioGAP WULPUS-pro sheet; 45 MB per-file cap. **Pushed to origin/main.**
- 2026-09-17  25b8e55  Pull reference design files (`design/{un0rick,lit3rick,
  pic0rick}/` + SOURCE.md); process Weik et al. 2026 wearables review + SIG-WUS
  (Table I → `systems/literature.md`); add SENS-U/WMAUS/MoUsE/Flopatch sheets +
  memory 0004.
- 2026-09-17  0dd9e66  Add IUP + MEMS-US datasheets, `systems/literature.md` (from
  Jonveaux et al. 2022 review), and `pdfs/` + `design/` folders with store
  conventions; RP2350 datasheet added to `pdfs/`.
- 2026-09-17  bab55c6  Extend `systems/` survey (online research): Murgen, un0rick,
  lit3rick, TUSS4470 sheets; 5-branch README framing; out-of-scope (64+ elements)
  + leads-to-review sections.
- 2026-09-17  82c24e3  Add `systems/` lightweight-ultrasound survey: datasheet
  TEMPLATE.md, index README, and 7 populated sheets (EchoLite, PuLsE, USoP,
  WULPUS, WULPUS PRO, pic0rick, TinyProbe).
- 2026-09-17  beffd20  Set up Claude documentation & memory system (docs/claude/
  logs, memory store, TODO/DONE, changelog), CLAUDE.md rules, and the repo-scoped
  `minus-docs` skill.
- 2026-09-17  f3d8367  Initial commit.
