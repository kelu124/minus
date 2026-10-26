---
name: minus-resume
description: Use at the start of any minus session, or whenever the user says "pick up where we left off", "resume", "where were we", "continue from last time" — reconstructs the last exchanges and the pending next action before doing anything else. minus repo ONLY.
---

# Resuming a minus session

## Overview
The SessionStart hook (`.claude/hooks/session-resume.sh`, wired in `.claude/settings.json`)
injects a "RESUME CONTEXT" block: last 5 commits, uncommitted files, `TODO.md` "Now" block,
tail of the newest `docs/claude/log/*.md`, memory 0008 "Bench state", and what is on USB.
This skill is what to do with it.

## Steps (in order, before any other work)
1. Read the injected RESUME CONTEXT. If it is missing (hook did not fire), produce it yourself:
   `bash .claude/hooks/session-resume.sh | jq -r .hookSpecificOutput.additionalContext`.
2. Read the private memory index (`MEMORY.md` → `minus-bench-state` first) and repo memory
   `docs/claude/memory/INDEX.md` → the files it lists, as `CLAUDE.md` requires.
3. Open a new log file `docs/claude/log/YYYY-MM-DD-session-NN.md` whose first section is
   "Resumed from session <previous NN>" with a 5-line recap of the last exchanges.
4. **Tell the user, in ≤ 8 lines, where things stopped and what the next concrete action is**
   (the `TODO.md` "RESUME HERE" item), and ask only what the hook cannot know (e.g. "was R53
   reworked?"). Then proceed from that action.
5. Verify hardware claims live before relying on them: `lsusb | grep -E "2e8a|04d8"`,
   `python3 firmware/rp2354/tools/rpcli.py /dev/ttyACM0 version`.

## Keeping it resumable (every session end)
- Last log section = "handoff": what was measured/decided, the exact next command.
- `TODO.md` top item starts with **RESUME HERE:** and names the next physical/CLI step.
- Memory 0008 "Bench state" and private `minus-bench-state` updated; commit + push.
