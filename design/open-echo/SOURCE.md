# Open Echo — design file source

- Upstream: https://github.com/Neumi/open_echo (branch `main`)
- Commit at retrieval: `cd689daf673c2dfd92088045f38cc9ba9184944c`
- Retrieved: 2026-09-17
- License: open-source hardware + software (see repo; no root LICENSE file at
  retrieval — check the repo/README for terms before redistribution)

## Files — current board `TUSS4470_shield_002` (Arduino UNO R3 shield)

Mirrored from `TUSS4470_shield_002/TUSS4470_shield_hardware/TUSS4470_shield/`:

| File | What it is |
|------|-----------|
| `TUSS4470_shield.kicad_sch` | KiCad schematic. |
| `TUSS4470_shield.kicad_pcb` | KiCad PCB layout. |
| `TUSS4470_shield.kicad_pro` | KiCad project. |
| `TUSS4470_shield-gerbers.zip` | Production gerbers. |
| `TUSS4470_shield-bom.csv` | Bill of materials. |

Upstream also has an older `development/TUSS4470_PCB_ECHO/` board, firmware
(`arduino/`, RAW + NMEA0183 DBT), a Python interface (`echo_interface.py`), a PicoW
UDP variant, and an experimental `phased_array_001_pico` (RP2040 phased array) —
not mirrored. Datasheet: `systems/open-echo/open-echo.md`.
