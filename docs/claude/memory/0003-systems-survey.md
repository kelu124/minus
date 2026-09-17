# 0003 — Lightweight ultrasound systems survey

**Status:** current (as of 2026-09-17), first pass

Background survey of lightweight/low-cost ultrasound acquisition designs, to
inform *minus*. Lives in [`systems/`](../../../systems/README.md); template at
`systems/TEMPLATE.md`, one subfolder per design.

Source: wulrick "extended platform survey"
(github.com/kelu124/wulrick, `OtherSystems/`) + each system's primary papers/repos.

## Anchor literature (user-provided PDFs in `pdfs/`)

- **Jonveaux, Schloh, Meng, Arija, Rintoul**, "Review of Current Simple Ultrasound
  Hardware...", *J. Open Hardware* 6(1):3, 2022, DOI 10.5334/joh.28
  (`pdfs/28-952-1-PB.pdf`). The user's own review — anchor for the whole survey.
  Distilled into `systems/literature.md` (Table 2 filtered to ≤32 elements +
  component menus: pulsers, HV sources, TGC/VGA, ADCs, AFEs, mux; single-element
  B-mode strategies; bandwidth-reduction).
- **IUP** (`pdfs/ssrn-6946751.pdf`) and **MEMS-US** (`pdfs/s41598-020-63529-z.pdf`)
  — device papers, each with a datasheet in `systems/`.

## Second anchor + SIG-WUS + design files (2026-09-17, later)

- **Weik et al. 2026** (IEEE RBME, `pdfs/Current_Trends_..._early_access.pdf`) —
  wearable-US system-architecture review; **Table I** compares SOTA systems
  (captured in `systems/literature.md`). Peer-reviewed basis of **SIG-WUS OXP**
  catalog (<https://sig-wus.org>, GitHub `sig-wus`; live catalog data failed to load
  — revisit).
- New sheets from Weik Table I: **SENS-U** (commercial 4-ch bladder monitor),
  **WMAUS** (8-ch dsPIC33 wristband; Yin et al. = STM32F7 re-design, noted inside),
  **MoUsE** (32-ch ZYNQ-7 open imaging), **Flopatch** (commercial CW-Doppler patch).
  Bashatah (chirp) + Wang (Barker bladder) captured in literature.md only.
- **Design files** pulled into `design/<name>/` (with `SOURCE.md` + commit SHA):
  un0rick, lit3rick, pic0rick (adc / mux / 3-in-1 adc+pulser+hv panel — KiCad +
  schematic PDFs + gerbers + BOMs). pic0rick article → `pdfs/pic0rick_full.pdf`.

## SIG-WUS OXP catalog retrieved (2026-09-17)

Live site failed to load; pulled the repo JSON instead (`github.com/sig-wus/
sig-wus-oxp.github.io`, `platforms/*/index.json`). Snapshot →
`systems/_sig-wus-oxp/` (14 platforms + reconciliation table). New from it:
**BioGAP WULPUS-pro** (ETH open shield `pulp-bio/sensei-us-shield`, 16-ch MSP430,
BLE 1.4 Mbit/s — sheeted). Corrections: **SENS-U → TENA SmartCare (Essity)**, 2021,
pediatric. **FloPatch** confirmed: model FP120, CW 4 MHz, FDA K200337 (2020), CE,
Flosonics Medical (Toronto), validated Kenny et al. Sci. Reports 2021
(10.1038/s41598-021-87116-y), iOS app (velocity/VTI/ccFT).

## Per-system attributes + first analysis (2026-09-17, later)

- Added two attributes to **every** system sheet (callout under §1): **"Piezo
  1–5 MHz"** compatibility and **ADC sampling speed**; consolidated quick-reference
  table in `systems/README.md`; fields added to `TEMPLATE.md`.
- Root **`analysis.md`** (first pass): integrated routes (MSP430 A / TUSS4470 A2) vs
  external-ADC route (B). For a 1–5 MHz pulse-echo *minus*, Route B fits; A is ≤3 MHz,
  A2 is ≤1 MHz. Includes a **light-BOM pulser options** table (TUSS4470 / STHV748 /
  MD1213+TC6320 / unipolar MOSFET+boost / TC6320+driver).
- Pulled pulser datasheets → `pdfs/datasheets/` (MD1213, MD1213DB1 [MD1213+TC6320
  reference], AN-H53, TUSS4470; STHV748 + TC6320 host-blocked → linked).

## By-IC cross-reference + Open Echo + more design files (2026-09-17, later)

- Added `systems/by-ic.md` — designs grouped by key IC (user asked to identify
  **MSP430FR5043**- and **TUSS4470**-based designs):
  - MSP430FR5043: WULPUS, WULPUS PRO, BioGAP WULPUS-pro, EMG+A-mode fusion
    (arXiv 2510.02000), TI EVM430-FR6043/FR5043. Ceiling ~1.4 MHz BW.
  - TUSS4470: **Open Echo** (Neumi/open_echo — open Arduino shield sonar, now
    sheeted, design files in `design/open-echo/`) + TI BOOSTXL-TUSS4470 EVM.
- Design files pulled: `design/biogap-wulpus-pro/` (schematics/assembly PDF + BOM;
  `pulp-bio/sensei-us-shield@238b470`) and `design/open-echo/` (KiCad + gerbers +
  BOM; `Neumi/open_echo@cd689da`).
- opensourceimaging.org/projects checked: only un0rick + echOpen (=Murgen), already
  sheeted. No new designs there.

## Systems captured (19 sheets)

New since first pass: **IUP** (HZDR DRESDYN UDV node — STM32H725 + iCE40HX4K +
MD1213/TC6320 + AD8331 + MD0100 + MAX5184 DAC + LTC2203 16-bit @16 MHz + SD/SDRAM +
ESP32 Wi-Fi + 18650, 2.96 W, 43 g; closest full-system template for *minus*).
**MEMS-US** (POSTECH single-element real-time B-mode via a MEMS acoustic-mirror
scanner; commercial Olympus 5073PR + AlazarTech ATS9350 100 MSps electronics — the
*scanning idea* is the takeaway, not the cheap BOM).

kelu124 family (the direct lineage for *minus*): **Murgen** (2016, arXiv
1611.10174, Arduino-like modular AFE) → **un0rick** (2019, iCE40HX4K, 65 Msps
ADC10065 10-bit, AD8331 TGC, MD1210+TC6320, 25/50/75 V) → **lit3rick** (2021,
iCE40 UP5K, 12-bit ADC, AD8332, external HV) → **pic0rick** (2024, RP2040, ±24 V).
Plus wearables: EchoLite, PuLsE, USoP, WULPUS, WULPUS PRO, TinyProbe. Plus
**TUSS4470** as the integrated analog-envelope AFE-IC route (30 kHz–1 MHz,
envelope-only) — same branch as PuLsE but off-the-shelf.

## Design-space takeaways

Five branches, minimal → capable:
1. Integrated analog-envelope AFE IC — TUSS4470 (≤1 MHz, envelope-only). Floor.
2. Analog-envelope + low-rate ADC — PuLsE (5.8 mW, envelope-only).
3. Integrated-ADC MCU — WULPUS/PRO (8 Msps ⇒ ~1.4 MHz BW; PRO adds AD8338 TGC,
   LT3463 dual ±30 V). Lowest power for raw-RF A-mode.
4. External high-speed-ADC single channel — kelu124 family (65 Msps, AD833x TGC,
   MD-class pulser). High freq, USB/SPI, higher power. **Most relevant to minus.**
5. FPGA multi-channel — TinyProbe (32 ch, Wi-Fi, ~45× power). Upper bound.

Core tension for *minus*: external high-speed ADC (frequency + cost + power) vs
integrated slow ADC (cheap + low-power, capped ~1.4 MHz).

Candidate parts: AD8331/AD8332/AD8338 (VGA/TGC), MCP4812 DAC, LT3463 (dual ±30 V),
MD1210/MD1213+TC6320 (pulser), MD0100/MD0101 (T/R), ADC10065 (65 Msps 10-bit).

## Out of scope (64+ elements) — reviewed, set aside

ULA-OP / ULA-OP 256 (Florence, 64→256 ch), SARUS (DTU, up to 1024 ch), open-UST
(tomography ring array). Recorded in systems/README so we don't re-review.

## Leads to review (not yet sheeted)

- "Compact modular open platform for low-cost US imaging", Measurement 2024
  (S0263224124022516) — confirm channel count (fetch blocked).
- Water-proofed MEMS-scanner single-element platform (Sci. Reports 2020).
- AI portable US (arXiv 2311.00482) uses TI AFE58xx (likely 64+ ch).

## Open confirmations

- EchoLite: paper not public; nearly all fields unconfirmed.
- PuLsE/USoP: closed hardware; MCU part, TX voltage, wireless partly unknown.
- lit3rick: exact ADC part, HV module, power — confirm against repo/paper.
- pic0rick dimensions/SNR: not characterized here yet.

See [[0001-project-scope]] for how this feeds the *minus* design.
