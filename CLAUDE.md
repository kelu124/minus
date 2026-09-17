# minus — project guide for Claude

**minus** is a minimal, single-channel, low-cost ultrasound imaging platform.

All project documentation, discussion history, and decisions live under
[`docs/claude/`](docs/claude/README.md). Follow the rules below every session.

## On starting a new session (do this first)

Read, in order, to come up to speed:

1. `docs/claude/memory/INDEX.md` → the memory files it points to (durable decisions).
2. `docs/claude/TODO.md` (open work) and `docs/claude/DONE.md` (completed work).
3. The latest file in `docs/claude/log/` (where we left off).

Then you are "up and running" with the past discussions and discoveries.

## During a session

- **Log the discussion** in `docs/claude/log/YYYY-MM-DD-session-NN.md`
  (one file per session, append-only, narrative).
- **Durable decisions/facts** → write/update a file in `docs/claude/memory/`
  and add its pointer to `docs/claude/memory/INDEX.md`.
- **Work items** → keep `docs/claude/TODO.md` current; when done, move the item
  to `docs/claude/DONE.md` with the date.
- **Downloaded PDFs** (papers, datasheets, reference-design docs) → save into
  `pdfs/` (not a temp dir) with a descriptive name; index them in `pdfs/README.md`.
- **Schematics / design files** (KiCad, Gerbers, PDF schematics, BOMs) → save into
  `design/<name>/`, one subfolder per design (slug matching `systems/<name>/`).

## Project layout

- `systems/` — device datasheets (one subfolder per design) + `TEMPLATE.md` +
  `literature.md`. See `systems/README.md`.
- `pdfs/` — source PDFs (papers, datasheets, reference designs).
- `design/` — schematics & design files, one subfolder per design.

## On every commit

- Add a summary line to `docs/claude/changelog.md` (at minimum a one-line
  summary; keep newest first). Stage the changelog update with the commit so the
  log and the code stay in sync.

## Reference

- Repo-local skill **`minus-docs`** (`.claude/skills/minus-docs/`) packages these
  rules and is scoped to this repo only.
- See `docs/claude/README.md` for the full convention and file-naming rules.
