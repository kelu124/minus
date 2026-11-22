---
name: minus-docs
description: >-
  Maintain the minus project's documentation system under docs/claude/:
  session logs, the memory store (memory/ + INDEX.md), TODO.md/DONE.md, and
  changelog.md. Use at the start of a session to come up to speed, whenever a
  discussion produces a durable decision or a work item, and on every commit.
  minus repo ONLY — do not use outside …/ultrasounds/minus.
---

# minus-docs

The single source of truth for how work on **minus** is documented. All paths
are under `docs/claude/` unless noted. Repo root `CLAUDE.md` points here.

## 1. Session start — come up to speed

Read, in order, then briefly tell the user where things stand:

1. `docs/claude/memory/INDEX.md` → each memory file it lists (durable decisions).
2. `docs/claude/TODO.md` (open work) and `docs/claude/DONE.md` (finished work).
3. The most recent file in `docs/claude/log/` (where we left off).

## 2. Log the discussion

- One file per session: `docs/claude/log/YYYY-MM-DD-session-NN.md`
  (`NN` increments if multiple sessions occur the same day).
- Append-only, narrative: what was discussed, decided, and what's next.

## 3. Persist durable decisions (memory)

When a discussion settles something that should outlive the session:

- Write/update `docs/claude/memory/NNNN-slug.md` (one topic per file).
- Add or refresh its one-line pointer in `docs/claude/memory/INDEX.md`.
- Supersede, don't silently rewrite: note what changed; the file always
  reflects the current state. Convert relative dates to absolute.

## 4. Track work (TODO / DONE)

- Keep `docs/claude/TODO.md` current as items appear.
- When an item is finished, move it to `docs/claude/DONE.md` with the date
  (`YYYY-MM-DD — what was done`, newest first).

## 4b. Store artifacts (bench data, built firmware, design files)

- Bench data (captures, scripts, plots) → `docs/bench/<YYYY-MM-DD>-<topic>/` with a README
  (commands, firmware versions, results). **Owner preference (2026-11-22): keep data as compressed NumPy files
  (`np.savez_compressed`, one `.npz` per test, arrays + a `meta` JSON with firmware/date/board), not raw text dumps.**
  Pattern: `campaign.py` (records, each test in try/except so one failure does not stop the rest) + `analyze.py`
  (figures + LaTeX macros) — see `docs/bench/2026-11-22-datasheet-ext/`.
- Built images are committed: `firmware/rp2354/build/minus_rp.uf2`, `firmware/pic32/build/minus_pic.hex`.
- The current board lives flat in `hardware/` (KiCad `minUS.*` + `production/`); older boards,
  reference designs, the systems survey and source PDFs were removed on 2026-11-19 (see git history).
- Never commit a single file > 45 MB.

## 5. On every commit

- Add at least a one-line summary to `docs/claude/changelog.md`
  (`YYYY-MM-DD  <short-sha>  summary`, newest first).
- Keep a "Pending" section at the top for uncommitted work; move it under
  "Committed" with the sha once it lands.
- Stage the changelog update together with the commit.

## Scope

This skill and its instructions apply **only within the minus repo**. Do not
apply these conventions to, or invoke this skill from, any other repository.

## Datasheets / LaTeX (2026-11-19)
`datasheet/` holds `minus-datasheet.tex` + `Makefile` + generated `values.tex`/`noise_rows.tex`/`ext_values.tex` + `figures/` +
the PDF. Build with `make -C datasheet` (pdflatex ×3; no siunitx/latexmk here; declare Unicode symbols). Measured numbers are
macros written by the bench analysis script — never type a measured value by hand into the `.tex`; macro names letters only.
- Owner expectations (2026-11-22): every firmware feature gets a datasheet section with a **step-by-step explanation** of what
  the firmware does (numbered steps naming the source function), **figures** from real data, and a measured table; errata and
  revision history updated with each rev.
- `\ref` to an unnumbered `\section*` prints the last numbered section ("Annex 12" bug): use `\hyperref[label]{Annex A}`.
- Check the build log for `undefined` and render new pages (`pdftoppm -r 50`) before committing.

## Notebooks (2026-11-22)
`python/notebooks/01..04` must together **demonstrate every library function** (owner). Audit after any firmware/library
change: collect `dev.<method>(` from the code cells and compare with `commands.RP_COMMANDS/RAW_HELPERS/PIC_LINK/PIC_SUBCOMMANDS`
methods; only destructive or session-breaking ones (`pic_erase`, `reboot`) may be described without running. Re-execute all on
the board (nbclient) with 0 errors before committing.
