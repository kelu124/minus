# TODO

Open work items for **minus**. Newest ideas at the top of their section.
When an item is finished, move it to [`DONE.md`](DONE.md) with the date.

## Now

- Requirements v0.2: MCU=RP2350, on-board USB-C bus-powered, small/cheap/simple
  locked. Remaining open: clinical? (TBD-1), target freq (TBD-2), TX polarity
  (TBD-3), imaging mode (TBD-5), BOM cost (TBD-6), external-ADC choice (ADEC) → v1.0.
- Then: pick the external ADC + pulser, draft a costed BOM and block diagram
  (start from `design/pic0rick/panel_adc_pulser_hv/`, port RP2040→RP2350).

## Next

- (optional) Mirror the full BioGAP Altium source + gerbers, and the Open Echo
  firmware/Python interface, if wanted beyond the current schematic+fab files.
- Sheet remaining leads: Measurement-2024 compact modular platform (32 el., get PDF
  → `pdfs/`), rtl-ultrasound (Meng 2019, SDR), compressive single-sensor 3D
  (Kruizinga 2017); optionally Bashatah (chirp) + Wang (Barker) from Weik Table I.
- Confirm lit3rick `[E]` fields from `design/lit3rick/lit3rick_schematics.pdf`.
- Collect more design files (IUP if released); add `design/` subfolders as sheeted.
- Fill survey gaps: EchoLite (await IEEE IUS 2025 paper), PuLsE/USoP MCU parts & TX
  voltages, pic0rick dimensions/SNR.
- Advance `analysis.md`: fix minus target frequency, unipolar vs bipolar, pick
  pulser (STHV748 vs MD1213+TC6320 vs unipolar), ADC + controller; then draft a BOM.
- Decide which reference systems `minus` derives from (kelu124 family / IUP / WULPUS
  / PuLsE / TUSS4470 route).

- Define target application, imaging depth, and centre frequency.
- Choose the single-element transducer and how (or whether) it scans.
- Decide pulser / analog front-end approach.
- Decide digitizer / ADC and sampling strategy.
- Decide compute/host (MCU, FPGA, PC) and display path.

## Someday / maybe

- Review prior work in sibling repos (e.g. `we_gate`) for reusable pieces.
