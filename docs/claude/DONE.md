# DONE

Completed work items, newest first. Each line: `YYYY-MM-DD — what was done`.

- 2026-09-17 — Retrieved the SIG-WUS OXP catalog from its repo JSON (live site
  broken); snapshot → `systems/_sig-wus-oxp/` (14 platforms). Enriched FloPatch
  (FP120, CW 4 MHz, FDA K200337, Kenny 2021), corrected SENS-U (TENA/Essity), added
  BioGAP WULPUS-pro sheet (systems/ = 18). Added the 45 MB per-file cap rule.
- 2026-09-17 — Pulled design files (schematics/KiCad/gerbers/BOMs) into
  `design/{un0rick,lit3rick,pic0rick}/` with `SOURCE.md` + commit SHAs; cross-linked
  from datasheets; pic0rick article → `pdfs/`.
- 2026-09-17 — Processed the Weik et al. 2026 wearables system-architecture review
  (IEEE RBME) + SIG-WUS OXP: captured its Table I in `systems/literature.md`; added
  datasheets SENS-U, WMAUS, MoUsE, Flopatch (systems/ now 17 sheets); added
  reference memory 0004.
- 2026-09-17 — Processed 3 user-provided PDFs: added IUP and MEMS-US datasheets;
  built `systems/literature.md` from the Jonveaux et al. 2022 open-hardware review
  (Table 2 filtered to ≤32 el. + component menus). Set up `pdfs/` (indexed) and
  `design/` folders + conventions (store PDFs / design files); copied RP2350
  datasheet into `pdfs/`.
- 2026-09-17 — Extended survey with online research: added Murgen, un0rick,
  lit3rick, TUSS4470 sheets (4); framed the design space into 5 branches; recorded
  64+ element systems (ULA-OP, SARUS, open-UST) as out of scope + leads to review.
  systems/ now holds 11 sheets.
- 2026-09-17 — Surveyed 7 lightweight ultrasound systems (EchoLite, PuLsE, USoP,
  WULPUS, WULPUS PRO, pic0rick, TinyProbe); built `systems/` with datasheet
  template + one populated sheet per system + index.
- 2026-09-17 — Added repo-scoped skill `minus-docs` (`.claude/skills/`) packaging
  the documentation rules; scoped to this repo only.
- 2026-09-17 — Set up `docs/claude/` logging & memory scaffold (log, memory,
  TODO, DONE, changelog) and repo rules in `CLAUDE.md`.
