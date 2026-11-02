# TODO

Open work items for **minus**. Newest ideas at the top of their section.
When an item is finished, move it to [`DONE.md`](DONE.md) with the date.

## Now

- **RESUME HERE (2026-11-02 evening): pic 0.1.20 / rp 0.1.28 = CPU 200 MHz / ADC 250 MHz on board 2; `acq` default
    div 4 = uniform 25 Msps (tone-proven, session 08 part 2, memory 0011). Open from the change: PLL2 → 320 MHz
    ADC clock (restores 40 Msps core, un-parks `acqil`, then 5-cycle CPU loop); `acq` should reset `navg` when not
    given (it persists on the PIC and silently poisons the next capture).**
  - **OA2 gain (owner asked 2026-11-02, memory 0012):** firmware side done (pic 0.1.21 `AMP2`, rp 0.1.29 `i2c`/`pot`; U11 answers at
    0x2E, wiper 64 = ×6.08 at power-on, settable ×1.07–×11.07). Still to do: (a) **measure** it: `raw AMP1 0`, tone into J6.1,
    `raw AMP2 1`, `pot 0 <n>`, read J6.2/RF13 (scope) or U.FL RF13→RF7 + `acq 4 0 9`; (b) **hardware**: MCP4531-103 in the
    feedback caps OA2 at ~1 MHz (datasheet −3 dB 1 MHz, CW 120 pF) — rethink (5 k part, fixed R + switch, or pot as a
    DC control only); (c) ADC2 capture of AD2AN1 (= FE_A_OUT) so OA2OUT can be read without cabling.
- Was: **RESUME HERE (2026-11-02): tone test done (session 08, `bench/2026-11-02-tone/`). 1 MHz square at
    RF7/H6 (PIC32_ADC node): `acq 8` = 20 samples/period clean; `acq 4` = 20 too (DMA ceiling proven);
    `acqcpu` at 25 ns = every value twice at 7 of 9 phases, phases 3/7 un-duplicated but +425 LSB offset
    (not usable); `acqil 16` = DMA at its ceiling, CH1 loses every other trigger in 3 of 4 runs.**
    Next: (1) ~~clock change~~ done (pic 0.1.20); later PLL2 → 320 MHz ADC + 5-cycle loop for raw 40 Msps; (2) chase the +425 LSB offset of the un-duplicated CPU reads (which
    ADC register/correction stage is being read?); (3) reproduce the intermittent slow `acq 8`
    (218–232 µs, scrambled periods, 2 of 5 runs — interrupt/SFR traffic during capture?);
    (4) fix the RX-node bias (TODO_HARDWARE: D7/R28/R36) so OA1 stops sitting at the rail, then
    `acq 8 0 0` with the transducer. Note: there is no "ADC SMA" — RF7 is IPEX, H6 the pin header.
  - `acqil 16` cannot be the default capture until the DMA has margin (200 MHz CPU) or a fill-time
    check retries a half-speed run (fill 412 µs instead of 206 µs).
  - Also: the wait loop could use the DMA0 interrupt + `pwrsav #1` instead of the NOP poll (zero SFR
    traffic during the capture); `acq` default input should be settable once (`acq in <n>`).
  - Board 1: replace U2 (dead PIC) when convenient; remove its H2.16–CN1.17 jumper first.
- **Was: RESUME HERE (2026-10-28): replace U2** (PIC32AK1216GC41048-I/PT, LCSC C46545915). Bench
    proof 2026-10-27: R53 shorted, MCLR 0.2 V low / 3.13 V released at pin 48, 3.28 V at the chip,
    full ICSP entry sequence verified on the pins with a logic analyser, silent on pairs 1 and 2.
    Before the swap remove the H2.16–CN1.17 jumper. Then `pic id` (fw 0.1.7, pair 1 fast) →
    `pic flash` → `ping` → `acq`.
  - Previous resume text: owner bridges **R53 → 0 Ω** (done 2026-10-27; JP1 already cut). Then `pic mclr low` + meter on J1.1 (≈ 0 V) →
    `pic mclr hiz` → `pic id` (DEVID 0x09DA2053) → `pic flash` → `ping` → **`acq`** (expect
    `fill≈102us fs≈40Msps`; if lower or `status=timeout`, set `ACQ_TRIG_DIV 8` = 20 Msps and
    rebuild both). If `pic id` still fails, debug `pic_icsp.c` entry timing (scope / slower
    clock) or compare with the Snap. Optional isolation step before scoping: remove **R17/R18**
    (RP SWD ↔ J1/PGC1/PGD1 links); costs only RP SWD on J1.
  - From the pic32probe study (`pic32prog/README.md`, memory 0010): first knob = slow the
    entry key to ~100 kHz (5 µs halves) + add `pic speed <khz>`; then scope PGC/PGD/MCLR.

- **acq review minors (deferred):** read AD1CH0DATA before `CHEN=1` (stale sample 0); don't print `fs` on
  non-ok status; `rpcli --out` should exit non-zero when the reply is not a capture; fix the
  indentation of the `stat` dispatch line; heartbeat divider is a loop count.
- **acq follow-ups:** `acq trig` (arm, start on the RP TRIG edge); FE-A full path input (OA2OUT = AD2AN1,
  needs an ADC2 channel); faster link baud or packed 12-bit payload (8190 B at 115200 = 0.7 s per capture).
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
