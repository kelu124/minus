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
Paths below are relative to the repo root (or use the absolute path of this skill folder).
```bash
S=<scratch dir>; N=.claude/skills/kicad-netlist-reading/nets.py
kicad-cli sch export netlist --format kicadxml -o $S/net.xml path/to/top.kicad_sch
python3 $N $S/net.xml shared U1 U2      # 1. nets touching BOTH parts directly (power nets hidden)
python3 $N $S/net.xml pins U2           # 2. every pin of a part: number, pin function, net, other nodes
python3 $N $S/net.xml net MCLR SPI_     # 3. all nodes on nets whose name contains the text
python3 $N $S/net.xml pins R53 R5 JP1   # 4. FOLLOW PASSIVES: a link through R/JP/C never shows in
                                        #    "shared" — list each passive's pins and hop net by net
python3 $N $S/net.xml comps             # ref -> value / footprint (pipe into grep for one ref)
```
Step 4 is where the answers hide: an MCU pin that reaches another chip's reset through
R → node → R is invisible to `shared`; iterate `pins <ref>` on each resistor/jumper until
you hit the target pin. Optional: `kicad-cli sch export pdf -o $S/sch.pdf top.kicad_sch`;
`production/bom.csv` (JLCPCB fabrication toolkit) gives LCSC part numbers per ref.

## Review checklist (each item found a real bug on the minus devkit, 2026-10-26 — examples, not
## facts about the board you are reading; re-derive the numbers from your own netlist + datasheet)
- **Follow passives to their other end.** A "0 Ω link", a series R, or two resistors in
  parallel between two nets change the story (example: 2 × 100 Ω MOSI↔MISO = 50 Ω short).
- **Pull-up vs drive divider.** GPIO through Rseries against a pull-up: compute the node
  voltage and compare to the target's VIL from its datasheet (example: 4k7 vs 10k pull-up →
  1.05 V, against a VIL max of 0.2·VDD = 0.66 V → the GPIO cannot pull the line low).
- **Alternate functions on shared pins.** JTAG (TCK/TDO/TDI/TMS), PGCx/PGDx, SWD on the same
  pins as a bus → check reset defaults (JTAG enabled on erased PIC) and who else drives them.
- **Nets with 3+ drivers** (shared SPI/I²C): list every node and decide ownership.
- **Parallel DIN on addressable LEDs**, 5 V logic parts on 3.3 V outputs.
- **Capacitors on reset/program lines** (MCLR + C behind a solder jumper).

## Common mistakes
- Greping `.kicad_sch` text for labels: hierarchical labels/power symbols hide connectivity.
- Trusting net *names* on both ends (`UART_TX` on both chips): read the pin functions.
- Treating KiCad `-backups/` zips and `~*.lck` files as design files (gitignore them).
- Stopping at `shared`: if a known control line (reset, enable, PGC/PGD) is missing there,
  it is behind a passive — go to step 4, do not conclude "not connected".
