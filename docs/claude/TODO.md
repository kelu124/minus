# TODO

Open work items for **minus**. Newest ideas at the top of their section.
When an item is finished, move it to [`DONE.md`](DONE.md) with the date.

## Now

- **RESUME HERE:** owner bridges **R53 → 0 Ω** (JP1 already cut; measured MCLR 2.88 V with
    GPIO24 low → ratio wrong on the board). Then `pic mclr low` + meter on J1.1 (≈ 0 V) →
    `pic mclr hiz` → `pic id` (DEVID 0x09DA2053) → `pic flash` → `ping`. If `pic id` still
    fails, debug `pic_icsp.c` entry timing (scope / slower clock) or compare with the Snap.
  - From the pic32probe study (`pic32prog/README.md`, memory 0010): first knob = slow the
    entry key to ~100 kHz (5 µs halves) + add `pic speed <khz>`; then scope PGC/PGD/MCLR.

- **pic32prog follow-ups (optional, after `pic id` works):** PIO port of the 2-bit-cmd + 32-bit
  shift (exact timing, as `pic32probe/src/probe.rs`); `pic raw` streaming mode so
  `tools/rpcli.py` can push a hex without rebuilding the RP image (pic32prog `adapter-bitbang`
  pattern); row programming (§3.4) for speed.
- **MDFU bootloader option (decide after `ping` works):** Microchip `dspic-bootloader-mdfu`
  (dsPIC33AK demos, UART/CAN-FD, `pymdfu` host) ported to the PIC32AK1216; RP ICSP then only
  installs the bootloader once, app updates go over the existing UART with the RP as a
  USB-CDC↔UART bridge. Check footprint, linker layout and MCC support for our part first.

- **Devkit firmware bring-up** (`firmware/`, see `firmware/README.md`, memory 0008):
  - ~~Install MPLAB X + XC-DSC~~ done 2026-10-26 (6.35 / 3.31.01); **both firmwares build**.
  - Get an **MPLAB Snap or PICkit Basic** + TC2030-NL cable; flash `firmware/pic32/build/minus_pic.hex`
    (`make -C firmware/pic32 flash`).
  - Board fixes before the link test: **R68/R69 → one 1–4.7 kΩ** (MOSI–MISO), **R53 → 0 Ω**
    (MCLR drive), cut **JP1** (C31 on MCLR) when programming from the RP.
  - First flash: confirm `ipecmd.sh -TPSNAP -P32AK1216GC41048 -F … -M -OL` works (codes verified
    in the installed readme; the option set itself is untested on hardware).
  - Run the UART PING/PONG test (`ping` / `auto` on the RP USB console); confirm RDY/TRIG.
  - Measure the real R53 / R5 values (board unpowered) and record them in
    `design/devkit/review-findings.md`. Optional: row programming (§3.4) for speed.
  - Step 2: PIC SPI client + ADC capture → RP.
  - Fold the 2026-10-26 flaws into `design/devkit/review-findings.md`; add `hardware/` to the
    docs conventions (design files now live there, not only `design/`).

- Requirements v0.3: NDT/workshop-badge, 3–4 MHz, unipolar, A-/M-mode, RP2350 + USB-C,
  provided piezo, coded excitation, multi-connector, derisk-by-reuse (DP5) all locked.
  Only ADEC (external ADC choice) + exact HV level remain open.
- Confirm **RF-ACCESS** (raw RF vs envelope) — gates the external-ADC section.
- Pick from `options.md`: pulser (U0/U1/U2/B0), gain (AD8338 vs AD8331), ADC
  (AD9200/AD9235); refresh `options_prices.csv` from live LCSC (qty 20–50).
- Then draft a **costed BOM + block diagram** reusing un0rick/pic0rick blocks on RP2350.
- **PIC32A concept** (`design/pic32/`): evaluate RP2350 + PIC32AK3208GC41064 (on-die
  40 Msps ADC + 100 MHz op-amps) as an alternative to external ADC+VGA. Open:
  - ~~LCSC stock for the PIC32A~~ → resolved 2026-10-26: 48-pin PIC32AK1216GC41048 is LCSC C46545915 (in the devkit BOM).
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
