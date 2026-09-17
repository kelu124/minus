# Claude working notes

This directory logs the design discussions and persistent decisions behind
**minus**, a minimal single-channel, low-cost ultrasound imaging platform.

## Layout

| Path              | Purpose                                                                 |
|-------------------|-------------------------------------------------------------------------|
| `log/`            | Chronological session logs — one file per working session, append-only. |
| `memory/`         | Durable decisions & facts, one topic per file. This is the memory store. |
| `memory/INDEX.md` | One-line pointer to every memory file. Loaded first to find things.      |
| `TODO.md`         | Open work items.                                                        |
| `DONE.md`         | Completed work items, dated, newest first.                             |
| `changelog.md`    | Summary of every commit, newest first.                                 |

## Conventions

- **Log** = *what was discussed* (narrative, timestamped, chronological).
- **Memory** = *what we decided / what is true* (distilled, deduplicated, current).
- **TODO/DONE** = *what's left / what's finished*. Finishing an item moves it
  from `TODO.md` to `DONE.md` with the date.
- **Changelog** = *what changed in the repo*. Every commit gets at least a
  one-line summary; staged together with the commit.
- When a discussion produces a durable decision, capture it in `memory/` and
  add its pointer to `INDEX.md`; the log records that it happened.
- Memory files are numbered `NNNN-slug.md`. Keep each to one topic.
- Convert relative dates ("next week") to absolute dates when writing.
- Supersede rather than silently rewrite: if a decision changes, update the
  memory file and note the change, so the current state is always what's there.

## Session start-up

To come up to speed at the beginning of a session, read (in order):
`memory/INDEX.md` → the memory files → `TODO.md`/`DONE.md` → the latest `log/` file.
(This is codified in the repo root `CLAUDE.md`.)

## File naming

- Logs:   `log/YYYY-MM-DD-session-NN.md`
- Memory: `memory/NNNN-slug.md`
