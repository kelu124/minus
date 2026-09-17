# DONE

Completed work items, newest first. Each line: `YYYY-MM-DD — what was done`.

- 2026-09-17 — requirements.md v0.3: NDT/education; **workshop-badge** for an US
  conference (muscle-monitoring topic; **piezo provided**); **3–4 MHz**; **unipolar**
  pulser; **A-/M-mode**; **programmable/coded excitation** (RP2350 PIO); transducer
  connectors **SMA + 2×1 header + uFL**; controller precise timing + gap-free ADC
  streaming; **DP5 derisk-by-reuse** of the owner's Murgen/un0rick/lit3rick/pic0rick;
  on-body-use safety; BOM as-low-as-possible. Updated memory 0005.
- 2026-09-17 — requirements.md v0.2: locked owner decisions — MCU **RP2350**, on-board
  **USB-C** bus-powered, and design principles **small/cheap/simple** (DP1–DP4). Added
  the RP2350-internal-ADC-too-slow note ⇒ external ADC required; updated §4/§10/§11/
  §12/D1–D2 and memory 0005.
- 2026-09-17 — Drafted `requirements.md` (root, v0.1): MoSCoW requirements across
  functional/performance/AFE/pulser/data/control/power/mechanical/cost/SW/openness/
  safety + verification + traceability, with §4 open-decision list (TBD-1..7).
- 2026-09-17 — Added "Piezo 1–5 MHz" + "ADC sampling" attributes to all 19 system
  sheets (+ template + quick-ref table). Wrote root `analysis.md` (integrated vs
  external-ADC routes + light-BOM pulser options). Pulled pulser datasheets into
  `pdfs/datasheets/`. Added memory 0005 (provisional direction).
- 2026-09-17 — Identified designs by key IC (`systems/by-ic.md`): MSP430FR5043
  (WULPUS family + TI EVM) and TUSS4470 (**Open Echo** + TI EVM). Added the Open
  Echo datasheet (systems/ = 19) and pulled BioGAP + Open Echo design files into
  `design/`. Checked opensourceimaging.org (only un0rick + echOpen, already covered).
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
