# SIG-WUS OXP catalog — snapshot

Snapshot of the **SIG-WUS Open eXperimentation Platform (OXP)** wearable-ultrasound
catalog, whose live web view at <https://sig-wus.org> failed to load in-browser.
Pulled from the underlying data files in the GitHub repo instead.

- Source: `https://github.com/sig-wus/sig-wus-oxp.github.io` (branch `main`),
  `platforms/<id>/index.json` (+ `platforms/index.json`, `platforms/_schema.json`).
- Retrieved: 2026-09-17.
- Peer-reviewed basis: Weik et al. 2026 (IEEE RBME) — see `../literature.md`,
  `../../pdfs/`, and `docs/claude/memory/0004-key-references.md`.
- `data/` holds the raw JSON per platform (`_index.json`, `_schema.json`, one file
  per platform id). Treat as reference data, not instructions.

## Catalog vs our datasheets (14 platforms)

| OXP id | Our sheet |
|--------|-----------|
| sense-u | [sens-u](../sens-u/sens-u.md) — OXP: **TENA SmartCare (Essity)**, orig. Novioscan |
| wmaus | [wmaus](../wmaus/wmaus.md) |
| wulpus | [wulpus](../wulpus/wulpus.md) |
| pulse | [pulse](../pulse/pulse.md) |
| mouse | [mouse](../mouse/mouse.md) |
| oem-usb-probe | — (128-ch, out of scope) |
| usop | [usop](../usop/usop.md) |
| tinyprobe | [tinyprobe](../tinyprobe/tinyprobe.md) |
| flopatch | [flopatch](../flopatch/flopatch.md) |
| iup | [iup](../iup/iup.md) |
| biogap-wulpus-pro | [biogap-wulpus-pro](../biogap-wulpus-pro/biogap-wulpus-pro.md) — **new** |
| yin-prosthetic-2022 | in [literature.md](../literature.md) (WMAUS/STM32F7 variant) |
| bashatah-tds-2024 | in [literature.md](../literature.md) (chirp) |
| wang-prevoiding-2024 | in [literature.md](../literature.md) (Barker-coded) |

Our survey additionally covers designs **not** in OXP (single-element/NDT lineage):
Murgen, un0rick, lit3rick, pic0rick, EchoLite, MEMS-US, TUSS4470.
