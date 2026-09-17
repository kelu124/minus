# 0003 — Lightweight ultrasound systems survey

**Status:** current (as of 2026-09-17), first pass

Background survey of lightweight/low-cost ultrasound acquisition designs, to
inform *minus*. Lives in [`systems/`](../../../systems/README.md); template at
`systems/TEMPLATE.md`, one subfolder per design.

Source: wulrick "extended platform survey"
(github.com/kelu124/wulrick, `OtherSystems/`) + each system's primary papers/repos.

## Systems captured (11 sheets)

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
