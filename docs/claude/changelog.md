# Changelog

Summary of every commit to this repo, newest first.
Format: `YYYY-MM-DD  <short-sha>  summary`.

Uncommitted work sits at the top under "Pending" until it lands, then it gets
the sha.

## Pending

- (none)

## Committed

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
