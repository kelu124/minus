# 0004 — Key references & catalogs

**Status:** current (as of 2026-09-17) · type: reference

Anchor sources for the *minus* survey (PDFs in `pdfs/`, distilled in
`systems/literature.md`):

- **Jonveaux, Schloh, Meng, Arija, Rintoul**, "Review of Current Simple Ultrasound
  Hardware Considerations, Designs, and Processing Opportunities", *Journal of Open
  Hardware* 6(1):3, 2022, DOI 10.5334/joh.28 (`pdfs/28-952-1-PB.pdf`). The user's own
  review — component menus + ≤32-element design table.
- **Weik, Nauber, Kaiser, Kirsch, Kunz, Schierling, Leitner, Benini, Liu, Zhou,
  Hampe, Fettweis, Herzog, Kupsch**, "Current Trends in Ultrasound Wearables:
  Spotlight on System Architecture", *IEEE Reviews in Biomedical Engineering*, 2026
  (early access) (`pdfs/Current_Trends_..._early_access.pdf`). Wearable
  system-architecture review + Table I comparison.

- **SIG-WUS** — Special Interest Group on Wearable UltraSound; runs the **OXP**
  (Open eXperimentation Platform) catalog of wearable US platforms at
  <https://sig-wus.org> (GitHub org `sig-wus`). Peer-reviewed basis = the Weik
  review. The live site's catalog failed to load, but the data is in
  `github.com/sig-wus/sig-wus-oxp.github.io` under `platforms/<id>/index.json` —
  snapshot committed at `systems/_sig-wus-oxp/` (14 platforms), retrieved 2026-09-17.

- **un0rick.cc** — hub for the kelu124 open-hardware family (un0rick, lit3rick,
  pic0rick, echomods/Murgen, pyusbus). Design files mirrored in `design/`.

- **[kelu124/pic32arick](https://github.com/kelu124/pic32arick)** — the owner's own
  **PIC32AK1216GC41064** ultrasound board (docs-only repo, no firmware yet): 5 V
  **push-pull pulser** (IRLML6244/2244 + TC4427A), **3-op-amp gain chain** (fixed OA1 +
  MCP4531 I²C-digipot OA2 + bias OA3), **MD0100** T/R, **Tag-Connect/6-pin ICSP** header,
  RPi-header + SAO. The proven PIC32-side reference reused by **DesignA**
  (`design/designA/`); details folded into `design/pic32/pic32.md` + `design/designA/`.

Related: [[0003-systems-survey]].
