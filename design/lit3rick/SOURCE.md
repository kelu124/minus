# lit3rick — design file source

- Upstream: https://github.com/kelu124/lit3rick (branch `master`)
- Commit at retrieval: `ca4ad983046943fae0694a609154839e8c051283`
- Retrieved: 2026-09-17
- License: TAPR open hardware (see repo `TAPR.txt`)

## Files (from repo `hardware/`)

| File | What it is |
|------|-----------|
| `lit3rick_schematics.pdf` | Board schematics. |
| `lit3rick_bom.csv`, `lit3rick_bom_split.csv` | Bill of materials. |
| `lit3rick_pickplace.csv` | Pick-and-place. |
| `lit3rick_gerber.zip` | Fabrication gerbers. |
| `lit3rick_drills.zip` | Drill files. |

The Verilog gateway + micropython live in the repo (`verilog/`, `micropython/`),
not mirrored here. Datasheet: `systems/lit3rick/lit3rick.md`.
The schematics here are the authoritative source to confirm the sheet's `[E]`
fields (ADC part, HV module, pulser driver).
