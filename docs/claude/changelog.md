# Changelog

Summary of every commit to this repo, newest first.
Format: `YYYY-MM-DD  <short-sha>  summary`.

Uncommitted work sits at the top under "Pending" until it lands, then it gets
the sha.

## Pending

- Add `options.md` (filtered pulser/gain/ADC shortlist + priced builds) +
  `options_prices.csv` (LCSC qty 20–50); analysis §3b gain options; requirements
  RF-ACCESS + 5V/±5V HV options; memory 0006 (pricing basis); earlier bd81776..
  requirements bits (OLED/RPi header/silkscreen/etc. already committed).

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
