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

**Still open:** external ADC choice (ADEC) — pick a low-cost ~20–30 MSps 10–12-bit
part; exact HV level; whether a cheap ± rail makes bipolar worthwhile; then draft the
costed BOM + block diagram.

**Not yet decided (open):** exact target frequency (≤3 MHz would reopen Route A),
unipolar vs bipolar, ADC (speed/bits), controller (RP2040/RP2350 vs iCE40), plus the
TBDs above.

See [[0003-systems-survey]], [[0001-project-scope]].
