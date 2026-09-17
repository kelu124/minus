# BioGAP WULPUS-pro — design file source

- Upstream: https://github.com/pulp-bio/sensei-us-shield (branch `main`)
- Commit at retrieval: `238b470902a968ca2e8e6c8fe5528b7a498e9658`
- Retrieved: 2026-09-17
- License: Solderpad v0.51 (hardware), per repo

## Files (mirrored from `hardware/wulpus_pro_shield/docs/`)

| File | What it is |
|------|-----------|
| `WULPUS_pro_schematics.pdf` | Full shield schematics (Altium export). |
| `WULPUS_pro_shield_assembly.pdf` | Assembly drawing. |
| `BOM_WULPUS_pro_BioGAP_shield.xlsx` | Bill of materials. |

The **Altium source** (`.SchDoc`, `.PcbDoc`, `.PrjPcb`, libs) and the full **Gerber
/ NC-drill / pick-place** sets live in the upstream repo under
`hardware/wulpus_pro_shield/` — not all mirrored here. Key parts visible in the
schematic: IXDD609 gate driver, MD0100 T/R, CMUT connector, host connectors.
Datasheet: `systems/biogap-wulpus-pro/biogap-wulpus-pro.md`.
