# TODO

Open work items for **minus**. Newest ideas at the top of their section.
When an item is finished, move it to [`DONE.md`](DONE.md) with the date.

## Now

- Requirements v0.3: NDT/workshop-badge, 3–4 MHz, unipolar, A-/M-mode, RP2350 + USB-C,
  provided piezo, coded excitation, multi-connector, derisk-by-reuse (DP5) all locked.
  Only ADEC (external ADC choice) + exact HV level remain open.
- Confirm **RF-ACCESS** (raw RF vs envelope) — gates the external-ADC section.
- Pick from `options.md`: pulser (U0/U1/U2/B0), gain (AD8338 vs AD8331), ADC
  (AD9200/AD9235); refresh `options_prices.csv` from live LCSC (qty 20–50).
- Then draft a **costed BOM + block diagram** reusing un0rick/pic0rick blocks on RP2350.
- **PIC32A concept** (`design/pic32/`): evaluate RP2350 + PIC32AK3208GC41064 (on-die
  40 Msps ADC + 100 MHz op-amps) as an alternative to external ADC+VGA. Open:
  - Confirm **LCSC stock + JLCPCB assembly** for the PIC32A (Digikey ~$1.6–1.9 known;
    LCSC/JLCPCB TBD — the go/no-go for the project's fab flow).
  - Verify whether the PIC32A op-amp has an **internal PGA (GSEL) ladder** (→ per-line
    gain with zero extra parts) or needs an external **digipot/MDAC/resistor-mux**.
  - Check PIC32A op-amp **input noise** vs echo level → decide if a fixed **LNA** (A3a)
    first stage is needed.
  - Decide TX sequencer ownership (PIC32A HS-PWM+PTG vs RP2350 PIO) + inter-MCU SPI
    protocol; test **ICSP-from-RP2350** (one USB port programs both).

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
