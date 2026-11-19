"""Keep the Python library in lock-step with the firmware.

``python -m minus.fwsync``            check (exit 1 + a report if anything is out of sync)
``python -m minus.fwsync --update``   after reviewing a firmware change: re-record the firmware fingerprint
                                      (refused while a hard check still fails)

What is checked, straight from the C sources:

1. **RP CLI commands**: every command token dispatched in ``firmware/rp2354/main.c`` (``strcmp/strncmp(line, ...)``)
   must be in ``commands.RP_COMMANDS`` and vice versa, and each must map to an existing ``Minus`` method.
2. **RP help usages**: every usage line printed by ``help()`` (e.g. ``acq [div [samc [in [navg]]]]``) must be
   recorded in ``commands.RP_COMMANDS`` / ``commands.RAW_HELPERS`` exactly, so an argument change is noticed.
3. **``pic`` sub-commands** dispatched in ``cmd_pic`` and **PIC link commands** dispatched in
   ``firmware/pic32/main.c`` must all be in ``commands.PIC_SUBCOMMANDS`` / ``commands.PIC_LINK``.
4. **Versions**: ``FW_NAME``, ``FW_VERSION_*`` and ``PROTO_VERSION`` of both ``version.h`` must equal
   ``commands.FIRMWARE``.
5. **Fingerprint**: a SHA-256 of every firmware source file (``*.c *.h *.pio CMakeLists.txt``) must match
   ``firmware_sync.json``. Any firmware edit trips this until someone has checked the library against it and run
   ``--update``.
"""
from __future__ import annotations

import hashlib
import json
import re
import sys
from pathlib import Path
from typing import Dict, List, Set

HERE = Path(__file__).resolve().parent
REPO = HERE.parents[2]                      # python/library/minus -> repo root
FW = REPO / "firmware"
SYNC_FILE = HERE / "firmware_sync.json"


# ------------------------------------------------------------------------------------------------ extraction
def _c_strings(text: str) -> str:
    """Concatenate adjacent C string literals inside a printf(...) block (help text)."""
    return "".join(bytes(s, "utf-8").decode("unicode_escape") for s in re.findall(r'"((?:[^"\\]|\\.)*)"', text))


def _function_body(src: str, signature_rx: str) -> str:
    m = re.search(signature_rx, src)
    if not m:
        raise RuntimeError(f"function not found: {signature_rx}")
    i, depth = src.index("{", m.end() - 1), 0
    for j in range(i, len(src)):
        depth += {"{": 1, "}": -1}.get(src[j], 0)
        if depth == 0:
            return src[i:j + 1]
    raise RuntimeError("unbalanced braces")


def rp_dispatch_tokens(src: str) -> Set[str]:
    body = _function_body(src, r"int main\(void\)\s*\{")
    return {t.strip() for t in re.findall(r'str(?:n)?cmp\(line, "([^"]+)"', body)}


def rp_help_usages(src: str) -> List[str]:
    text = _c_strings(_function_body(src, r"static void help\(void\)\s*\{"))
    usages = []
    for ln in text.splitlines()[1:]:                     # first line is the title
        if ln.startswith("  "):
            usages.append(re.split(r"\s{2,}", ln.strip(), maxsplit=1)[0])
    return usages


def rp_pic_subcommands(src: str) -> Set[str]:
    body = _function_body(src, r"static void cmd_pic\(const char \*arg\)\s*\{")
    return {t.strip() for t in re.findall(r'str(?:n)?cmp\((?:arg|m), "([^"]+)"', body)}


def pic_link_tokens(src: str) -> Set[str]:
    body = _function_body(src, r"int main\(void\)\s*\{")
    return {t.strip() for t in re.findall(r'str(?:n)?cmp\(line, "([^"]+)"', body)}


def version_h(path: Path) -> Dict[str, object]:
    t = path.read_text()
    g = lambda k: re.search(rf"#define {k}\s+(\S+)", t)[1]
    return {"name": g("FW_NAME").strip('"'),
            "version": f"{g('FW_VERSION_MAJOR')}.{g('FW_VERSION_MINOR')}.{g('FW_VERSION_PATCH')}",
            "proto": int(g("PROTO_VERSION"))}


def source_files() -> List[Path]:
    out = []
    for sub in ("rp2354", "pic32"):
        for p in sorted((FW / sub).rglob("*")):
            if "build" in p.relative_to(FW).parts or not p.is_file():
                continue
            if p.suffix in (".c", ".h", ".pio") or p.name == "CMakeLists.txt":
                out.append(p)
    return out


def fingerprint() -> Dict[str, str]:
    return {str(p.relative_to(REPO)): hashlib.sha256(p.read_bytes().replace(b"\r\n", b"\n")).hexdigest()
            for p in source_files()}


# ------------------------------------------------------------------------------------------------ check
def check(verbose: bool = False) -> List[str]:
    """Return a list of problems (empty = in sync). Fingerprint problems are prefixed 'fingerprint:'."""
    from . import commands
    from .device import Minus

    problems: List[str] = []
    rp_src = (FW / "rp2354" / "main.c").read_text()
    pic_src = (FW / "pic32" / "main.c").read_text()

    def compare(kind: str, found: Set[str], known: Set[str]) -> None:
        for t in sorted(found - known):
            problems.append(f"{kind}: firmware has '{t}' but the library does not know it")
        for t in sorted(known - found):
            problems.append(f"{kind}: library lists '{t}' but the firmware no longer has it")

    compare("RP CLI command", rp_dispatch_tokens(rp_src), set(commands.RP_COMMANDS))
    known_usages = {c.usage for c in commands.RP_COMMANDS.values() if c.usage} | set(commands.RAW_HELPERS)
    compare("RP help usage", set(rp_help_usages(rp_src)), known_usages)
    compare("'pic' sub-command", rp_pic_subcommands(rp_src), set(commands.PIC_SUBCOMMANDS))
    compare("PIC link command", pic_link_tokens(pic_src), set(commands.PIC_LINK))

    methods = [c.method for c in commands.RP_COMMANDS.values()] + list(commands.RAW_HELPERS.values()) + \
              list(commands.PIC_SUBCOMMANDS.values()) + list(commands.PIC_LINK.values())
    for m in methods:
        if m and not callable(getattr(Minus, m, None)):
            problems.append(f"library: commands.py maps to Minus.{m}() which does not exist")

    for side, path in (("rp", FW / "rp2354" / "version.h"), ("pic", FW / "pic32" / "version.h")):
        v = version_h(path)
        want = commands.FIRMWARE[side]
        if v["name"] != want["name"] or v["version"] != want["version"]:
            problems.append(f"version: {side} firmware is {v['name']} {v['version']}, "
                            f"library expects {want['name']} {want['version']} (commands.FIRMWARE)")
        if v["proto"] != commands.FIRMWARE["proto"]:
            problems.append(f"version: {side} PROTO_VERSION {v['proto']} != library {commands.FIRMWARE['proto']}")

    recorded = json.loads(SYNC_FILE.read_text())["files"] if SYNC_FILE.exists() else {}
    now = fingerprint()
    for f in sorted(set(now) | set(recorded)):
        if now.get(f) != recorded.get(f):
            state = "added" if f not in recorded else "removed" if f not in now else "changed"
            problems.append(f"fingerprint: {f} {state} since the library was last synced")
    return problems


def update() -> int:
    hard = [p for p in check() if not p.startswith("fingerprint:")]
    if hard:
        print("refusing --update, fix these first:\n  " + "\n  ".join(hard))
        return 1
    SYNC_FILE.write_text(json.dumps({"comment": "written by `python -m minus.fwsync --update` after the library "
                                                "was checked against these firmware sources",
                                     "files": fingerprint()}, indent=1) + "\n")
    print(f"recorded fingerprint of {len(fingerprint())} firmware files in {SYNC_FILE.relative_to(REPO)}")
    return 0


def main(argv: List[str]) -> int:
    if "--update" in argv:
        return update()
    if "--dump" in argv:     # what the extractor sees (handy when editing commands.py)
        rp_src = (FW / "rp2354" / "main.c").read_text()
        pic_src = (FW / "pic32" / "main.c").read_text()
        print("RP dispatch:", sorted(rp_dispatch_tokens(rp_src)))
        print("RP help usages:"); [print("  ", u) for u in rp_help_usages(rp_src)]
        print("pic subcommands:", sorted(rp_pic_subcommands(rp_src)))
        print("PIC link:", sorted(pic_link_tokens(pic_src)))
        print("rp version.h:", version_h(FW / "rp2354" / "version.h"))
        print("pic version.h:", version_h(FW / "pic32" / "version.h"))
        return 0
    problems = check()
    if not problems:
        print("minus.fwsync: library in sync with firmware "
              f"(rp {version_h(FW / 'rp2354' / 'version.h')['version']}, pic {version_h(FW / 'pic32' / 'version.h')['version']})")
        return 0
    print("minus.fwsync: the Python library is OUT OF SYNC with the firmware:")
    for p in problems:
        print("  - " + p)
    print("Update python/library/minus (commands.py, device.py, protocol.py, tests, notebooks) to match, then run\n"
          "  python3 -m minus.fwsync --update   (from python/library)")
    return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
