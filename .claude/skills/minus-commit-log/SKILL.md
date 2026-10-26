---
name: minus-commit-log
description: Use when committing in the minus repo, when asked what Claude committed and why, or when resuming work and needing the list of past Claude commits with their purpose. minus repo ONLY.
---

# minus commit log

## Overview
`COMMITS.md` in this folder is the running list of every commit Claude made in this repo:
`YYYY-MM-DD  <sha>  <subject>` plus one line on *why / what it enabled*. It complements
`docs/claude/changelog.md` (per-commit summary, repo convention) and `git log`; the extra
value is the one-line purpose and that it survives squashes/rebases as a readable file.

## On every commit
1. Make the commit (message ends with the Co-Authored-By line from the session reminder).
2. Append a row to `COMMITS.md` (newest first) with the real sha from `git rev-parse --short HEAD`.
3. Record the sha in `docs/claude/changelog.md` ("Pending" → "Committed") — repo rule.
4. Commit 2+3 together as `docs: changelog — record <sha> under Committed`, then push
   (`git push origin main`): the owner wants commits pushed as work progresses.

A commit cannot contain its own sha: the row for the bookkeeping commit itself is written
at the *next* cycle (or in a tiny follow-up). Never `--amend` after writing a sha into the file.

## Regenerate / audit
```bash
git log --format='%h %ad %s' --date=short --grep='Co-Authored-By: Claude' --all | head -50
```
Compare with `COMMITS.md`; any sha missing from the file gets a row with its purpose.
