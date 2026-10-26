# pdfs/mplab — Microchip MPLAB tooling documentation

User guides for the PIC32AK toolchain (MPLAB X 6.35 / IPE / MDB), kept here so the
`.md` siblings are greppable. Generated with `markitdown foo.pdf -o foo.md`.

| File | What it is | Use it for |
|------|-----------|-----------|
| `MPLAB_X_IDE_Users_Guide_50002027.pdf` | MPLAB X IDE User's Guide (DS50002027) | Linux install, pack manager (Device Family Packs), project/`make` flow, debugger setup |
| `MPLAB_IPE_Integrated_Programming_Environment_Users_Guide_50002227.pdf` | MPLAB IPE User's Guide (DS50002227) | **`ipecmd`** command-line options (`-TP`, `-P`, `-F`, `-M`, `-OL`) used by `firmware/pic32/Makefile flash` |
| `MDB-Users-Guide-DS50002102.pdf` | MPLAB Debugger (MDB) command-line User's Guide (DS50002102) | scripted debugging / memory reads over PICkit without the IDE |
| `HWToolDebugFeatures.pdf` | Hardware tool debug features matrix | which breakpoints/trace features the PICkit 4/5 and ICD 4/5 offer per device family |
| `Device_Support.pdf` | MPLAB X device support list | confirms PIC32AK1216GC41048 support level (compiler, programmer, debugger) |

See `STEP1.md` §2b and the repo skill `pic32ak-xcdsc-toolchain` for the install sequence.
