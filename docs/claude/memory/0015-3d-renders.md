# 3D board renders (2026-11-11)

**How:** `python3 hardware/render_3d.py hardware/<board>` (add `--quick` for a fast draft) →
`<board>/minUS_F.png`, `minUS_B.png`, `minUS_angled.png` via `kicad-cli pcb render` (KiCad 10.0.6).
The design file is never edited; the script patches a temp copy.

**Why a script is needed:** the PCB's model paths point at the original author's Windows
library (`D:/Nzoia Systems/.../EasyEDA.3dshapes/`) or at an unset `${KICAD_3RD_PARTY}`.
Rendered as-is, the board shows bare pads only.

- EasyEDA models we have are vendored in `hardware/3dmodels/EasyEDA/` (~14 MB, collected from
  the sibling we_* repos).
- Missing EasyEDA models → closest stock KiCad model (`SUBST` table): RP2354A QFN-60 → QFN-56 7×7
  (body right, pin count not), PIC32AK → TQFP-48, TSSOP-16, SOT-23-5, SC-70-6, MSOP-8, LED 0603,
  2520 osc, 2016 inductor, U.FL (RF1/RF23 → Hirose U.FL-R-SMT-1).
- Substitutes whose native orientation differs get a `FIXUPS` entry: TSSOP-16 rot 270;
  U.FL offset (0, 0.4, 0) rot 90. U1 also had a stray duplicate model offset by 5.5 mm (dropped).
- **Owner rule:** always omit the 2×N pin headers (H6), the IDC box header (CN1) and the SMA
  edge connectors (RF3, RF22) from renders (`OMIT` list). The 1×1 headers H5/H10 have no model.
- Check new boards by cropping the render around each substituted part (orientation, pin-1 dot).
