#!/usr/bin/env bash
# SessionStart hook for the minus repo: inject "where we left off" into Claude's context.
# Prints JSON with hookSpecificOutput.additionalContext (never fails the session start).
set -u
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT" || exit 0
{
  echo "=== minus: RESUME CONTEXT (auto-injected by .claude/hooks/session-resume.sh) ==="
  echo "Follow the repo skill 'minus-resume': confirm this state with the user before acting."
  echo
  echo "--- git ---"
  git -c color.ui=never log --oneline -5 2>/dev/null
  st=$(git status --short 2>/dev/null | head -10); [ -n "$st" ] && { echo "uncommitted:"; echo "$st"; } || echo "working tree clean"
  echo
  echo "--- TODO.md: RESUME HERE / Now ---"
  awk '/^## Now/{p=1;next} /^## /{p=0} p' docs/claude/TODO.md | head -40
  echo
  LOG=$(ls docs/claude/log/*.md 2>/dev/null | sort | tail -1)
  echo "--- last session log: ${LOG:-none} (last 45 lines) ---"
  [ -n "$LOG" ] && tail -45 "$LOG"
  echo
  echo "--- memory 0008 'Bench state' ---"
  awk '/^## Bench state/{p=1;next} /^## /{p=0} p' docs/claude/memory/0008-devkit-minUS_10102026.md 2>/dev/null | head -30
  echo
  echo "--- hardware on USB right now ---"
  if command -v lsusb >/dev/null; then
    lsusb 2>/dev/null | grep -i -E "2e8a|04d8" || echo "no Raspberry Pi (2e8a) / Microchip (04d8) USB device attached"
  fi
  ls /dev/ttyACM* 2>/dev/null || echo "no /dev/ttyACM*"
  echo "=== end resume context ==="
} > /tmp/minus-resume-context.txt 2>&1
# Short summary SHOWN TO THE USER at session start (hook "systemMessage"): where we left off.
{
  echo "minus — where we left off (auto summary, .claude/hooks/session-resume.sh)"
  echo "last commit: $(git -c color.ui=never log -1 --format='%h %ad %s' --date=short 2>/dev/null | cut -c1-110)"
  ahead=$(git rev-list --count @{upstream}..HEAD 2>/dev/null); [ -n "$ahead" ] && [ "$ahead" != "0" ] && echo "unpushed commits: $ahead"
  echo "RESUME HERE: $(awk '/^- \*\*RESUME HERE/{p=1} p&&/^- \*\*Was:|^- \*\*[^R]/{exit} p' docs/claude/TODO.md | sed 's/^- \*\*RESUME HERE[^:]*:\*\*//; s/^    //' | tr '\n' ' ' | cut -c1-420)"
  LOG=$(ls docs/claude/log/*.md 2>/dev/null | sort | tail -1)
  if [ -n "$LOG" ]; then
    echo "last log: $LOG — final section:"
    awk '/^## /{sec=$0; buf=""} {buf=buf"\n"$0} END{print buf}' "$LOG" | sed '/^$/d' | head -14 | cut -c1-160 | sed 's/^/  /'
  fi
  if command -v lsusb >/dev/null; then
    lsusb 2>/dev/null | grep -q -i -E "2e8a|04d8" && echo "USB: a minus board is attached ($(ls /dev/ttyACM* 2>/dev/null | tr '\n' ' '))" || echo "USB: no board attached"
  fi
} > /tmp/minus-resume-summary.txt 2>&1
# Emit: additionalContext for Claude + systemMessage for the user (JSON via jq; plain text fallback)
if command -v jq >/dev/null; then
  jq -n --rawfile ctx /tmp/minus-resume-context.txt --rawfile msg /tmp/minus-resume-summary.txt \
     '{systemMessage:$msg, hookSpecificOutput:{hookEventName:"SessionStart",additionalContext:$ctx}}'
else
  cat /tmp/minus-resume-summary.txt /tmp/minus-resume-context.txt
fi
exit 0
