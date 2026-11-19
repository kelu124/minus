#!/usr/bin/env python3
"""Assemble the GitHub Pages site from README.md.

Usage: python3 .github/pages/build.py <out_dir>   (run from the repo root)

- README.md becomes <out_dir>/index.md (Jekyll front matter added, first H1 dropped:
  the theme header already shows the title).
- Images and PDFs referenced by relative links are copied into the site at the same path,
  so they are served by Pages directly.
- Every other relative link (source files, folders) is rewritten to the GitHub repo
  (blob/ for files, tree/ for folders), because the site only carries the README.
"""
import re
import shutil
import sys
from pathlib import Path

REPO_URL = "https://github.com/kelu124/minus"
BRANCH = "main"
COPY_EXT = {".png", ".jpg", ".jpeg", ".gif", ".svg", ".webp", ".pdf"}
MAX_COPY = 45 * 1024 * 1024

root = Path.cwd()
out = Path(sys.argv[1] if len(sys.argv) > 1 else "_site_src")
out.mkdir(parents=True, exist_ok=True)

text = (root / "README.md").read_text(encoding="utf-8")
lines = text.splitlines()
if lines and lines[0].startswith("# "):
    lines = lines[1:]
text = "\n".join(lines).lstrip("\n") + "\n"

LINK = re.compile(r"(!?)\[([^\]]*)\]\(([^)\s]+)\)")


def rewrite(m: re.Match) -> str:
    bang, label, target = m.groups()
    if re.match(r"^[a-z][a-z0-9+.-]*:", target, re.I) or target.startswith(("#", "/")):
        return m.group(0)
    path, _, frag = target.partition("#")
    src = (root / path).resolve()
    rel = src.relative_to(root).as_posix() if src.exists() else path.rstrip("/")
    if src.is_file() and src.suffix.lower() in COPY_EXT and src.stat().st_size <= MAX_COPY:
        dst = out / rel
        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src, dst)
        new = rel
    else:
        kind = "tree" if (src.is_dir() or path.endswith("/")) else "blob"
        new = f"{REPO_URL}/{kind}/{BRANCH}/{rel}"
    if frag:
        new += "#" + frag
    return f"{bang}[{label}]({new})"


text = LINK.sub(rewrite, text)

front = (
    "---\n"
    "layout: default\n"
    "title: minus\n"
    "---\n\n"
)
(out / "index.md").write_text(front + text, encoding="utf-8")
shutil.copy2(Path(__file__).with_name("_config.yml"), out / "_config.yml")
print(f"site source written to {out}/")
