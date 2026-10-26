# 0009 — Firmware versioning rule

**Status:** current (decided by owner 2026-10-26) · type: convention

- Every firmware (RP2354A `firmware/rp2354`, PIC32AK `firmware/pic32`) carries a semantic
  version **MAJOR.MINOR.PATCH** in its `version.h`, plus a `PROTO_VERSION` for the RP↔PIC link.
- **Owner controls MAJOR and MINOR. Claude controls PATCH only**: bump PATCH on every change
  that alters a built binary; log it in `firmware/VERSIONS.md` (newest first).
- The RP reports it with the `version` CLI command; the PIC with `ID?` over the link.
- Starting points: rp2354 **0.1.1**, pic32 **0.1.0**, proto 1.

Reusable know-how from this work is packaged as repo skills in `.claude/skills/`:
`kicad-netlist-reading`, `pic32ak-xcdsc-toolchain`, `minus-firmware`.

See [[0008-devkit-minUS_10102026]].
