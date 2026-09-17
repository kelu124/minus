# minus — first analysis: acquisition routes & minimal pulser options

**Status:** first pass, 2026-09-17. Based on the survey in [`systems/`](systems/README.md)
(19 datasheets + `literature.md` + `by-ic.md`) and the reference designs in
[`design/`](design/README.md). To be refined once *minus*'s exact target is fixed.

**Target assumed here:** minimal, single-channel, cheap, **pulse-echo A-mode** with a
**1–5 MHz piezo** (the band most medical/NDT single-element probes live in).

---

## 1. The two forks

Every surveyed design answers two questions, which set cost/power/BOM:

1. **How is the echo digitized?** → *integrated ADC* (in the MCU/AFE) vs
   *external high-speed ADC*.
2. **How is the HV transmit pulse generated?** → *integrated pulser* vs *discrete
   driver + HV FETs*.

The first fork decides whether 1–5 MHz is even reachable; the second dominates the
BOM weight. This analysis takes them in turn.

---

## 2. Acquisition routes

### Route A — Integrated MCU (TI MSP430FR5043 / USS_A)
- **What:** one MCU with a built-in pulse generator, **8 MSps 12-bit ADC**, and PGA
  (+ FRAM/DMA). Add only an HV supply, T/R switch and (optional) mux.
- **BOM/power:** fewest parts, **lowest power** (WULPUS = 22 mW).
- **Limit:** ~1.4 MHz end-to-end −3 dB bandwidth (CIC decimation) ⇒ **≤~3 MHz piezo**.
- **1–5 MHz fit:** **Partial** — loses the 3–5 MHz top of the band.
- **Refs:** [WULPUS](systems/wulpus/wulpus.md), [WULPUS PRO](systems/wulpus-pro/wulpus-pro.md),
  [BioGAP WULPUS-pro](systems/biogap-wulpus-pro/biogap-wulpus-pro.md).

### Route A2 — Integrated AFE IC (TI TUSS4470)
- **What:** a **single IC** = TX H-bridge/pre-driver + RX LNA + log-amp + analog
  envelope. Digitize the envelope with any host ADC.
- **BOM/power:** absolute lightest (≈1 IC), low power.
- **Limit:** **30 kHz – 1 MHz**, envelope-only (no RF phase, no linear TGC).
- **1–5 MHz fit:** **No** — out of band. Only relevant if the target is lowered to
  ≤1 MHz (sonar/ToF-style).
- **Refs:** [Open Echo](systems/open-echo/open-echo.md), [TUSS4470](systems/tuss4470/tuss4470.md).

### Route B — External high-speed ADC (kelu124 family / IUP)
- **What:** discrete chain — pulser + T/R + VGA/TGC + **external 30–65 MSps ADC** +
  controller (MCU or FPGA). Captures raw RF with depth-variable gain.
- **BOM/power:** heaviest of the three, but **covers 1–5 MHz (and well beyond)**.
  Power ~300 mW (pic0rick) → ~2–3 W (un0rick/IUP).
- **1–5 MHz fit:** **Yes.**
- **Refs:** [pic0rick](systems/pic0rick/pic0rick.md) (esp. the on-disk 3-in-1
  adc+pulser+hv panel), [un0rick](systems/un0rick/un0rick.md),
  [lit3rick](systems/lit3rick/lit3rick.md), [IUP](systems/iup/iup.md).

### Routes at a glance
| | A — MSP430 integrated | A2 — TUSS4470 AFE | B — external ADC |
|---|---|---|---|
| BOM parts | few | fewest (1 IC) | most |
| **1–5 MHz piezo** | partial (≤3 MHz) | no (≤1 MHz) | **yes** |
| Sampling | 8 MSps | host ADC (~kSps) | 30–65 MSps |
| Raw RF | yes (≤1.4 MHz BW) | no (envelope) | yes |
| Gain | fixed PGA (AD8338 in PRO) | log-amp | VGA/TGC (AD833x) |
| Power | lowest (22 mW) | low | higher (0.3–3 W) |
| Example | WULPUS | Open Echo | pic0rick, IUP |

**Read:** for a genuine **1–5 MHz pulse-echo** *minus*, **Route B (external ADC)**
is the fit. Route A is viable only if the target is capped at ≤3 MHz; Route A2 only
if capped at ≤1 MHz. The remaining question for Route B is how light the BOM — above
all the **pulser** — can be.

---

## 3. Pulser options — lightest BOM first

The HV transmit pulser is the biggest BOM / power / complexity lever. Options ordered
from simplest, all usable across 1–5 MHz unless noted. (Datasheets in
[`pdfs/datasheets/`](pdfs/datasheets/).)

| # | Option | ICs | Polarity | Voltage | 1–5 MHz | Notes / reference |
|---|--------|-----|----------|---------|:-------:|-------------------|
| 1 | **TUSS4470** integrated AFE (TX+RX) | 1 | bipolar H-bridge | direct / ext-FET | No (≤1 MHz) | lightest of all, but envelope-only ≤1 MHz — [Open Echo] |
| 2 | **STHV748** integrated pulser **+ T/R** | 1 | bipolar, 3/5-level | ±90 V | **Yes** | one IC does pulse-gen **and** T/R (4 ch, use 1); fewest parts for a bipolar 1–5 MHz pulser |
| 3 | **MD1213 + TC6320** driver + HV FET pair | 2 | bipolar | ±100 V | **Yes** | the un0rick/pic0rick/IUP standard; reference design = MD1213DB1 |
| 4 | **Unipolar MOSFET + gate driver + boost** | ~2 | unipolar | +15–30 V | **Yes** | WULPUS-style; simplest/cheapest if unipolar excitation is acceptable |
| 5 | **TC6320 + logic gate-driver** | ~2 | bipolar | ±100 V | **Yes** | minimal discrete bipolar for simple pulses |

**Trade-offs**
- **Fewest parts, bipolar, in-band:** **STHV748** — a single IC integrates the
  multilevel pulser *and* the T/R switch, so it removes both the discrete FET pair
  and a separate T/R part. Best "light BOM" bipolar choice for 1–5 MHz.
- **Most proven / most replicable:** **MD1213 + TC6320** — two ICs, ±100 V, 2 A,
  extensively documented (MD1213DB1 demoboard) and already validated in every
  kelu124 board and IUP. Slightly heavier BOM than STHV748 but battle-tested and
  cheap; needs a separate T/R switch (e.g. MD0100/MD0101).
- **Absolute simplest (unipolar):** a single HV N-MOSFET + gate driver + a small
  boost rail. Unipolar drive is a touch less symmetric but fine at ≤5 MHz; this is
  the WULPUS transmit approach and the lowest part count if bipolar isn't required.

**Rest of the RX chain (Route B):** T/R switch (MD0100/MD0101, or integrated in
STHV748) → VGA/TGC (AD8331/AD8332, or the low-power AD8338) → external ADC
(≈40–65 MSps 10–12-bit ADC10065-class for bandwidth, **or** 16-bit ~16–25 MSps
LTC2203-class for dynamic range, as IUP chose) → controller (RP2040/RP2350 or an
iCE40 FPGA).

---

## 3b. Receive gain / TGC options

The VGA/TGC stage is the other analog choice. What the field uses (from the survey):

| Part | Gain | Notes | Used by |
|------|------|-------|---------|
| **AD8331** (/8332/8334) | 48 dB (LNA+VGA) | ultrasound-grade, linear-in-dB, to 120 MHz | un0rick, pic0rick, IUP, Murgen, W. Qiu |
| **AD8338** | 0–80 dB | low-power (mW), single-ended, RC-ramp TGC | **WULPUS PRO, BioGAP** |
| AD8330 | ~50 dB | ADI "low-cost" wideband VGA (differential) | — |
| AD603 / AD8367 | ~40–45 dB | cheap VGA, **needs external LNA**, lower DR | cheap/DIY designs |
| VCA8500 / MAX2077 | VGA | | Govindan/Vasudevan; Weng |
| **AFE58xx / AD927x** | integrated LNA+VGA+ADC | one chip, but **multi-channel, pricey, power-hungry** | 8-ch research boards |
| TUSS4470 / LT5507 / AD830x | log-amp / envelope | compresses DR, **no linear TGC**, ≤1 MHz | Open Echo; WULPUS PRO envelope |
| MSP430 PGA | fixed | no TGC (fixed gain) | WULPUS original |

**Contenders for minus (single-channel, cheap, 3–4 MHz):**
- **AD8331** — derisked reuse (DP5, your boards), 48 dB, ~$8–12.
- **AD8338** — cheaper, lower power, proven in the WULPUS wearables → likely the
  better badge fit.
- **AD603 + external LNA** — BOM-floor option, ~40 dB, lower dynamic range.
- Integrated AFEs (AFE58xx/AD927x) are over-spec/expensive for one channel.
- **BOM saver:** drive the analog gain-control voltage from **RP2350 PWM + RC** rather
  than a dedicated DAC IC (pic0rick used an MCP4812) — one fewer part.

_Decision pending with ADEC; AD8338 is the current front-runner for cost/power,
AD8331 the derisked fallback._

## 4. Where to start (reference designs on disk)
- [`design/pic0rick/panel_adc_pulser_hv/`](design/pic0rick/) — a KiCad **3-in-1
  ADC + pulser + HV** panel = the closest single-board starting point for Route B.
- [`design/un0rick/`](design/), [`design/lit3rick/`](design/) — iCE40 single-channel variants.
- [`design/iup/`] (not yet pulled) — the self-contained wireless node blueprint.
- [`design/biogap-wulpus-pro/`](design/) — the MSP430 integrated-route reference (if Route A).
- [`design/open-echo/`](design/) — the TUSS4470 route (if target ≤1 MHz).

---

These open decisions are captured as **TBD-1..7** in the requirements draft,
[`requirements.md`](requirements.md).

## 5. Open questions → next decisions
1. **Fix minus's target frequency** (e.g. 2.25 / 3.5 / 5 MHz). ≤3 MHz keeps Route A
   (MSP430) on the table; 3–5 MHz forces Route B.
2. **Unipolar vs bipolar** transmit (BOM/simplicity vs excitation symmetry).
3. **Pulser choice:** STHV748 (lightest bipolar) vs MD1213+TC6320 (proven) vs
   unipolar MOSFET (simplest).
4. **ADC + controller:** speed/bits/cost; RP2040/RP2350 vs iCE40 FPGA.

_This is a first analysis; it will be updated as the target is set and a BOM is drafted._
