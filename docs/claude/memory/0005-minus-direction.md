# 0005 — minus direction (provisional)

**Status:** provisional first analysis (2026-09-17) · type: project

First architecture analysis lives in the repo root **`analysis.md`**. Summary:

- **Target assumed:** single-channel pulse-echo A-mode, **1–5 MHz piezo**, cheap/light.
- **Route B (external high-speed ADC)** is the fit for 1–5 MHz. Route A (MSP430
  integrated, 8 MSps) is capped ≤~3 MHz; Route A2 (TUSS4470 AFE) is ≤1 MHz
  envelope-only.
- **Lightest in-band pulsers:** STHV748 (1 IC, bipolar + integrated T/R) or
  MD1213+TC6320 (2 ICs, proven kelu124/IUP standard) or unipolar MOSFET+boost
  (simplest). Datasheets in `pdfs/datasheets/`.
- Closest starting design on disk: `design/pic0rick/panel_adc_pulser_hv/` (3-in-1
  ADC+pulser+HV KiCad panel).

**Requirements draft:** `requirements.md` (root) — MoSCoW requirements + a §4 list of
open decisions **TBD-1..7** (clinical?, target freq, TX polarity, host link, imaging
mode, BOM cost ≤$150 target, controller). Resolving those → requirements v1.0 → BOM.

**Not yet decided (open):** exact target frequency (≤3 MHz would reopen Route A),
unipolar vs bipolar, ADC (speed/bits), controller (RP2040/RP2350 vs iCE40), plus the
TBDs above.

See [[0003-systems-survey]], [[0001-project-scope]].
