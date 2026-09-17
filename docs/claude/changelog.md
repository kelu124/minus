# Changelog

Summary of every commit to this repo, newest first.
Format: `YYYY-MM-DD  <short-sha>  summary`.

Uncommitted work sits at the top under "Pending" until it lands, then it gets
the sha.

## Pending

- Add `systems/by-ic.md` (MSP430FR5043 + TUSS4470 design cross-reference), Open Echo
  datasheet, and `design/{biogap-wulpus-pro,open-echo}/` files.

## Committed

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
