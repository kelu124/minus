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

## 4b. Store artifacts (PDFs & design files)

- Downloaded PDFs (papers, datasheets, reference-design docs) → `pdfs/` with a
  descriptive name; index them in `pdfs/README.md`. Never leave them in a temp dir.
- Schematics / design files (KiCad, Gerbers, PDF schematics, BOMs) →
  `design/<name>/`, one subfolder per design (slug matching `systems/<name>/`); note
  the upstream source (repo URL + version) in a short `SOURCE.md`.
- Survey/datasheet work lives in `systems/` (one subfolder per design, `TEMPLATE.md`
  at root, `literature.md` for the broad review).

## 5. On every commit

- Add at least a one-line summary to `docs/claude/changelog.md`
  (`YYYY-MM-DD  <short-sha>  summary`, newest first).
- Keep a "Pending" section at the top for uncommitted work; move it under
  "Committed" with the sha once it lands.
- Stage the changelog update together with the commit.

## Scope

This skill and its instructions apply **only within the minus repo**. Do not
apply these conventions to, or invoke this skill from, any other repository.
