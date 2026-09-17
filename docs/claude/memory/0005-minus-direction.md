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

**Requirements draft:** `requirements.md` (root) — MoSCoW requirements + open decisions.

**Owner decisions locked (2026-09-17, req v0.2):**
- **MCU = RP2350** (RP2350B preferred for GPIO). Controller/PIO drives an external
  high-speed ADC (RP2350 internal ADC = 500 kSps, too slow for 1–5 MHz raw RF).
- **On-board USB connector, USB-C preferred; USB bus-powered** (host + power).
- Design principles: **smallest board, cheapest BOM, simplest design** (DP1–DP3).
- ⇒ minus ≈ a trimmed **pic0rick on RP2350** (RP2350 + external ADC via PIO).

**Owner decisions locked (req v0.3):**
- Non-clinical **NDT/education**; **workshop badge** for an ultrasound conference
  (many units, limited budget). Example topic: **muscle-contraction monitoring**
  (A-/M-mode). **Piezo provided** with the kit (~3–4 MHz), not in board BOM.
- Target **3–4 MHz**; **unipolar** pulser (simplest); **A-mode + M-mode** (B-mode deferred).
- **Programmable/coded excitation** required (workshop feature) via RP2350 PIO —
  unipolar supports chirp/pulse-train/OOK; true bipolar phase codes need a bipolar
  pulser (possible expansion).
- Transducer connectors: **SMA/coax + 2×1 2.54 mm header + uFL** (multiple footprints).
- Controller (RP2350) must do **precise ns pulse-sequence timing (PIO)** + **fast
  gap-free ADC streaming (PIO+DMA)**.
- **DP5 Derisk by reuse:** reuse proven blocks from the owner's own designs
  (Murgen/un0rick/lit3rick/pic0rick — owner is happy with them; un0rick already has a
  unipolar HV pulser). Design files in `design/`.
- **BOM: as low as possible** (no fixed cap); costed BOM is a deliverable.
- **Pulser (refined):** unipolar **preferred**; **bipolar accepted iff** a cheap
  symmetric ± rail is found (explore charge pump / SEPIC-Ćuk / dual-boost /
  transformer). Bipolar would unlock true ±1 phase-coded excitation (synergy w/ coded
  excitation) via a pic0rick-style MD1213+TC6320 pulser (DP5).
- **On-device DSP [S]:** firmware should demo RP2350 (dual M33 + DSP/FPU) processing —
  bandpass, Hilbert/envelope, decimation, matched filter for coded excitation — vs
  host processing; modular so it never blocks raw capture.
- **RGB LED [S]:** addressable RGB (WS2812/SK6812, PIO-driven) for **autonomous**
  on-badge visual feedback (status; echo/M-mode → colour) without a host.
- **OSHWA [S]:** plan OSHWA certification (like un0rick/lit3rick/pic0rick); reserve
  silkscreen space for the OSHWA mark + UID.
- **Layout/extensibility [S]:** user-friendly silkscreen (label blocks, pins,
  function hints — the board teaches itself); test points on key logic/analog nodes;
  **HV rail(s) on a header with jumper** so on-board HV can be isolated/replaced by
  external HV (T7, M5, M6).
- **Standardised extension header [S]:** expose the RP2350 on a **Raspberry Pi 2×20
  (40-pin) header** (UART/I²C/SPI/GPIO/power), HAT-style, as un0rick did (DP5) — carries
  add-ons and the OLED (C5).
- **Displays [S]:** addressable **RGB LED** (F11) + small **I²C OLED** (SSD1306-class,
  F12) for autonomous on-badge display without a host.

**Component options (trade study):** `options.md` (root) + `options_prices.csv` — a
filtered shortlist from analysis.md, priced per option (LCSC qty 20–50, see [[0006-pricing-basis]]):
- **Pulser:** U0 5V-rail-only (cheapest, no boost) / U1 +boost / U2 MD1213+TC6320
  (reuse) / B0 ±5V via +5→−5V charge pump (cheap bipolar, true phase codes) / B1/B2
  higher-V bipolar. HV node on a header (T7) for external-HV upgrade.
- **Gain:** G1 AD8338 (front-runner, cheap/low-power) / G2 AD8331 (reuse) / G3 AD603+LNA.
- **ADC:** A1 AD9235-20 (12-bit, LCSC) / A2 AD9200 (10-bit, cheaper) / A3 ADC10065
  (reuse) / A4 AD9280 (8-bit, marginal).
- Candidate active-IC BOM: **~$16 cheapest** (U0+AD8338+AD9200+RP2350) → **~$44 derisked**.

**Open question RF-ACCESS (req §4):** do users need **raw RF** (not just envelope)?
Raw RF justifies the DSP (S6) + coded excitation (T4) + external ADC; envelope-only
would be cheaper but drop those. Working assumption = raw RF.

**Still open:** RF-ACCESS confirmation; ADEC (ADC pick); HV level (5V vs boost vs ±5V);
then draft the costed BOM + block diagram.

**Not yet decided (open):** exact target frequency (≤3 MHz would reopen Route A),
unipolar vs bipolar, ADC (speed/bits), controller (RP2040/RP2350 vs iCE40), plus the
TBDs above.

See [[0003-systems-survey]], [[0001-project-scope]].
