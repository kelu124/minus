# design — schematics & design files

Schematics, PCB / layout, Gerbers, BOMs, and other design source files for
reference designs (and, later, for *minus* itself). **One subfolder per design**,
named to match the system slug in [`../systems/`](../systems/) where one exists.

Convention:
- `design/<name>/` — e.g. `design/un0rick/`, `design/pic0rick/`, `design/iup/`.
- Put the raw design files here (KiCad, Gerbers, PDF schematics, BOM CSVs).
- Cross-link from the matching `systems/<name>/<name>.md` datasheet.
- Large binaries are fine, but prefer the canonical/original files; note the
  upstream source (repo URL + commit/version) in a short `SOURCE.md` per subfolder.

Datasheets and papers (not editable design files) go in
[`../pdfs/`](../pdfs/) instead.

## Collected so far

| Subfolder | Design | Contents |
|-----------|--------|----------|
| `un0rick/` | un0rick (iCE40 single-channel) | schematic PDF, BOM, gerbers, drills |
| `lit3rick/` | lit3rick (UP5K single-channel) | schematics PDF, BOM, gerbers, drills |
| `pic0rick/` | pic0rick (RP2040) — 3 boards | KiCad + schematic PDFs + gerbers for `adc/`, `mux/`, `panel_adc_pulser_hv/` |

Each has a `SOURCE.md` with the upstream repo URL + commit + retrieval date.
More to come (IUP if released, and the leads in `docs/claude/TODO.md`).
