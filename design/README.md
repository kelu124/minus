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

_Empty for now — populated as reference design files are collected (see
`docs/claude/TODO.md`)._
