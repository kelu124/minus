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
- **Bench data** (captures, analysis scripts, plots) → `docs/bench/<YYYY-MM-DD>-<topic>/`
  with a README (commands, firmware versions, results), so every number can be reproduced.
- **Reference PDFs / third-party datasheets are not stored in the repo** (removed in the
  2026-11-19 cleanup; they live in git history before that date). Link to them instead.
- **Built firmware images are committed**: `firmware/rp2354/build/minus_rp.uf2` and
  `firmware/pic32/build/minus_pic.hex` (everything else under `build/` is ignored).
  Rebuild both and commit them with every firmware version bump.
- **Firmware ↔ Python library stay in sync**: any change to a CLI command, a reply format, a PIC link command or a
  firmware version must be reflected in `python/library/minus/` (commands.py / device.py / protocol.py), the test
  fixture (`tests/record_fixture.py`) and the notebooks; then `python3 -m minus.fwsync --update` (from
  `python/library`). A PostToolUse hook (`.claude/hooks/fwsync-check.sh`) and the git pre-commit hook
  (`.githooks/pre-commit`, `git config core.hooksPath .githooks`) enforce it.
- **Repo size:** overall size is fine, but **never commit a single file larger than
  45 MB**. Skip/trim oversized files (or note them and link instead).

## Project layout

- `hardware/` — the current board (KiCad project `minUS.*`, board 3 = minus v1.1),
  `production/` (JLCPCB outputs), `3dmodels/`, `render_3d.py`. Older boards: git history.
- `firmware/` — `rp2354/` (pico-sdk) and `pic32/` (XC-DSC) + `VERSIONS.md`.
- `python/` — `library/minus/` (one `Minus` method per CLI command, parsers, `fwsync` check, offline tests)
  and `notebooks/` (worked examples, executed on a board).
- `datasheet/` — the product datasheet (LaTeX → `minus-datasheet.pdf`).
- `docs/` — `claude/` (memory, logs, TODO/DONE, changelog), `bench/` (test data);
  will also hold the GitHub Pages material.
- `LICENSE.md` + `LICENSES/` — per-folder licenses.

## On every commit

- Add a summary line to `docs/claude/changelog.md` (at minimum a one-line
  summary; keep newest first). Stage the changelog update with the commit so the
  log and the code stay in sync.

## Reference

- Repo-local skill **`minus-docs`** (`.claude/skills/minus-docs/`) packages these
  rules and is scoped to this repo only.
- See `docs/claude/README.md` for the full convention and file-naming rules.
