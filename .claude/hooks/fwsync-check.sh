#!/usr/bin/env bash
# PostToolUse (Edit|Write|MultiEdit): when a firmware source or the Python library changes, run the
# firmware <-> library sync check (python/library/minus/fwsync.py). On mismatch, report back to Claude
# (exit 2 + stderr) so the library, tests and notebooks get updated in the same piece of work.
root="$(cd "$(dirname "$0")/../.." && pwd)"
f="$(/usr/bin/python3 -c 'import json,sys; d=json.load(sys.stdin); print((d.get("tool_input") or {}).get("file_path") or (d.get("tool_response") or {}).get("filePath") or "")')"
case "$f" in
  "$root"/firmware/*/build/*) exit 0 ;;
  "$root"/firmware/*|"$root"/python/library/minus/*) ;;
  *) exit 0 ;;
esac
out="$(cd "$root/python/library" && /usr/bin/python3 -m minus.fwsync 2>&1)" && exit 0
{ echo "$out"
  echo "(fwsync hook: $f was edited — bring python/library + notebooks in line, re-record tests/fixtures if replies changed, then run 'python3 -m minus.fwsync --update' from python/library)"; } >&2
exit 2
