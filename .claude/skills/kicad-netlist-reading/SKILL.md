---
name: kicad-netlist-reading
description: Use when you must answer "what connects to what" from KiCad schematics (.kicad_sch / .kicad_pro) — which MCU pins link two chips, what a net touches, which resistor sits on a line — or when reviewing a schematic for wiring flaws without opening the GUI.
---

# Reading KiCad schematics by netlist

## Overview
Do not parse `.kicad_sch` S-expressions by hand. Export the netlist once with `kicad-cli`
(KiCad ≥ 7, installed here as `kicad-cli` 10.x) and query the XML with the bundled script.
Every pin carries its **pinfunction** (e.g. `PGC1/AD2AN5/.../RB4`), so alternate functions
(JTAG, PGx, RPn, SPI) are visible without the datasheet.

## Steps
```bash
S=<scratch dir>
kicad-cli sch export netlist --format kicadxml -o $S/net.xml path/to/top.kicad_sch
python3 .claude/skills/kicad-netlist-reading/nets.py $S/net.xml shared U1 U2   # inter-chip links
python3 .claude/skills/kicad-netlist-reading/nets.py $S/net.xml pins U2        # every pin of a part
python3 .claude/skills/kicad-netlist-reading/nets.py $S/net.xml net MCLR SPI_  # follow a net
python3 .claude/skills/kicad-netlist-reading/nets.py $S/net.xml comps          # ref -> value
```
Optional: `kicad-cli sch export pdf -o $S/sch.pdf top.kicad_sch` for a human-readable copy;
`production/bom.csv` (JLCPCB fabrication toolkit) gives LCSC part numbers per ref.

## Review checklist that found real bugs
- **Follow passives to their other end.** A "0 Ω link", a series R, or two resistors in
  parallel between two nets change the story (R68‖R69 = 50 Ω MOSI→MISO short).
- **Pull-up vs drive divider.** GPIO through Rseries against a pull-up: compute the node
  voltage and compare to the target's VIL (R53 4k7 vs R5 10k → 1.05 V, VIL 0.66 V → fails).
- **Alternate functions on shared pins.** JTAG (TCK/TDO/TDI/TMS), PGCx/PGDx, SWD on the same
  pins as a bus → check reset defaults (JTAG enabled on erased PIC) and who else drives them.
- **Nets with 3+ drivers** (shared SPI/I²C): list every node and decide ownership.
- **Parallel DIN on addressable LEDs**, 5 V logic parts on 3.3 V outputs.
- **Capacitors on reset/program lines** (MCLR + C behind a solder jumper).

## Common mistakes
- Greping `.kicad_sch` text for labels: hierarchical labels/power symbols hide connectivity.
- Trusting net *names* on both ends (`UART_TX` on both chips): read the pin functions.
- Treating KiCad `-backups/` zips and `~*.lck` files as design files (gitignore them).
