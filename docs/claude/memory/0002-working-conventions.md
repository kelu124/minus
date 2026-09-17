# 0002 — Working conventions

**Status:** current (as of 2026-09-17)

The user asked that all discussions be logged and that memory be persisted so we
keep track of the exchange across sessions, and that a new chat comes up already
knowing the past discussions/discoveries.

## Files under `docs/claude/`

- `log/` — chronological session logs, one file per session.
- `memory/` — durable decisions/facts, one topic per file, indexed by `INDEX.md`.
- `TODO.md` — open work items.
- `DONE.md` — completed work items, dated, newest first.
- `changelog.md` — summary of every commit, newest first.
- `.claude/` (repo root) — repo-local Claude Code config/notes.

## Rules (also codified in repo root `CLAUDE.md`)

**Session start:** read `memory/INDEX.md` → the memory files → `TODO.md`/`DONE.md`
→ the latest `log/` file, to come up to speed.

**During a session:** log the discussion; capture durable decisions in `memory/`
+ `INDEX.md`; keep `TODO.md` current and move finished items to `DONE.md`.

**On every commit:** add at least a one-line summary to `changelog.md`, staged
with the commit.

See `docs/claude/README.md` for the full convention.
