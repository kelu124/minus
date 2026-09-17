# minus — component options (filtered shortlist)

A **filtered subset** of the landscape in [`analysis.md`](analysis.md), keeping only
options that pass minus's criteria, with indicative pricing. The full landscape and
rationale live in `analysis.md`; the requirements in [`requirements.md`](requirements.md).

**Filter criteria (from requirements):** 3–4 MHz, **raw RF** (see open item RF-ACCESS),
**RP2350 + external ADC** route, **unipolar preferred** (bipolar only if a cheap ± rail),
**cheapest BOM / fewest parts** (DP1–DP3), **derisk by reusing** the owner's proven
blocks (DP5).

**Prices:** from [`options_prices.csv`](options_prices.csv) — **reference is LCSC at
low-quantity (~20–50 unit, i.e. workshop-batch) pricing**, active parts only (passives
ignored); values are indicative, refresh against live LCSC. Totals are active-IC only
and exclude passives, connectors, PCB, and the badge peripherals (OLED/LED/USB-C).

---

## 1. Pulser (TX) — shortlist

Excluded by filter: TUSS4470 / log-amp (≤1 MHz, envelope-only — out of the 3–4 MHz
raw-RF band).

| Option | Parts | Polarity | TX-subsystem $ (incl T/R) | Notes |
|--------|-------|----------|:--------------------------:|-------|
| **U0 — 5V-rail only** *(absolute simplest)* | N-MOSFET + gate driver + MD0100 (**no boost**) | unipolar +5V | **~$4.5** | pulse straight off USB 5V; low amplitude (shallow/weaker echo) but fewest parts; **upgrade to real HV via the HV header (T7)** |
| **U1 — Unipolar discrete** *(+boost)* | HV N-MOSFET + gate driver + HV boost + MD0100 | unipolar (15–50 V) | **~$6.0** | adds a boost rail for stronger pulse; 0.6+0.9+1.5+3.0 |
| **U2 — MD1213+TC6320 unipolar** *(derisked, DP5)* | MD1213 + TC6320 + HV boost + MD0100 | unipolar | **~$11.5** | 4+3+1.5+3; the un0rick pulser run unipolar (25–75 V) |
| **B0 — ±5V (charge-pump)** *(cheap bipolar)* | U0 + **−5V charge pump** (TPS60403/ICL7660/LM2776) | bipolar ±5V | **~$4.9** | +5V rail + ~$0.4 inverter ⇒ **cheap symmetric ±5V** (T6); low amplitude but **enables true ±1 phase codes** |
| B1 — MD1213+TC6320 bipolar | + inverting/charge-pump − rail | bipolar (higher V) | ~$14.5 | for higher-voltage bipolar; unlocks ±1 phase codes at higher amplitude |
| B2 — STHV748 (integrated + T/R) | STHV748 + ± rail | bipolar | ~$14.5 | fewest ICs for bipolar; T/R on-chip (no MD0100) |

**Lean pick:** **U0 (5V-rail only)** for the cheapest, simplest possible TX — accept
low pulse amplitude, and rely on the **HV header (T7)** so users can add external HV
when they want more. Step up to **U1** (add a boost) if the 5V pulse proves too weak
for muscle depth, or **U2** to derisk by reusing the proven un0rick pulser (DP5).
For cheap **bipolar** (true ±1 phase codes on a budget), **B0** adds only a ~$0.4
+5→−5V charge pump for a symmetric **±5V** rail — the low-cost answer to T6, at low
amplitude. B1/B2 are for higher-voltage bipolar.

## 2. Gain / TGC (RX) — shortlist

Excluded by filter: integrated multichannel AFEs (AFE58xx / AD927x — over-spec,
pricey, power-hungry for one channel); log-amp/envelope (no linear RF TGC).

| Option | Part(s) | Gain | $ (incl gain-ctrl) | Notes |
|--------|---------|------|:------------------:|-------|
| **G1 — AD8338** *(front-runner)* | AD8338 (+ RP2350 PWM ramp) | 0–80 dB | **~$4.0** | low-power, cheap, proven in WULPUS PRO/BioGAP |
| **G2 — AD8331** *(derisked, DP5)* | AD8331 (+ PWM, or MCP4812 +$1.5) | 48 dB | **~$10.0** | your un0rick/pic0rick VGA; ultrasound-grade |
| G3 — AD603 + LNA | AD603 + LNA op-amp (+ PWM) | ~40 dB | ~$5.0 | BOM-floor; lower dynamic range |

**Lean pick:** **G1 (AD8338)** — cheaper, lower power than AD8331, field-proven.
**G2 (AD8331)** is the derisked fallback. **BOM saver:** set the gain-control voltage
from **RP2350 PWM + RC** (no DAC IC).

## 3. ADC — shortlist

Applies only if **RF-ACCESS = raw RF** (else the RP2350 internal 500 kSps ADC and no
external ADC). Need ≥16 MSps (4× 4 MHz), target 20–30 MSps, ≥10-bit, parallel output
for PIO capture. Excluded: LTC2203 (16-bit, ~$25 — over-spec/large).

| Option | Part | Spec | $ | Notes |
|--------|------|------|:--:|-------|
| **A1 — AD9235-20** *(front-runner)* | AD9235BRUZ-20 | 12-bit 20 MSps || **~$10** | LCSC-stocked (C514274); ultrasound-suited; -40 (~$13) if margin wanted |
| **A2 — AD9200** | AD9200 | 10-bit 20 MSps | ~$6 | cheaper, 10-bit is enough (P4) |
| **A3 — ADC10065** *(derisked, DP5)* | ADC10065 | 10-bit 65 MSps | ~$10 | un0rick/pic0rick part; faster/costlier than needed at 3–4 MHz |
| A4 — AD9280 | AD9280 | 8-bit 32 MSps | ~$4 | cheapest, but ~48 dB only — marginal vs P5 (≥50 dB SNR) |

**Lean pick:** **A2 (AD9200, 10-bit)** for lowest cost that meets P3/P4/P5, or
**A1 (AD9235-20, 12-bit)** for headroom + confirmed LCSC stock. Reuse fallback: A3.

---

## 4. Candidate builds (active-IC BOM only, excl. passives/connectors/PCB)

| Build | Pulser | Gain | ADC | MCU | ~Active-IC $ |
|-------|--------|------|-----|-----|:------------:|
| **Cheapest** | U0 5V-only (~4.5) | G1 AD8338 (4.0) | A2 AD9200 (6.0) | RP2350 (1.1) | **~$16** |
| **Balanced** | U1 (~6.0) | G1 AD8338 (4.0) | A1 AD9235-20 (10.0) | RP2350 (1.1) | **~$21** |
| **Derisked (DP5 reuse)** | U2 (~11.5) | G2 AD8331 (10.0)+DAC(1.5) | A3 ADC10065 (10.0) | RP2350 (1.1) | **~$44** |

Badge peripherals add ~a few $ (OLED ~$1.5, RGB LED ~$0.1, USB-C ~$0.3, RPi header,
SMA/uFL) — outside this options pricing (passives/connectors ignored per scope).

**Reading:** a coherent minus front-end is **~$17–21 in active ICs** with the
cheap/low-power parts (AD8338 + AD9200/AD9235 + unipolar pulser + RP2350), or **~$44**
if we maximise derisking by reusing the exact un0rick/pic0rick blocks. The lean build
still meets 3–4 MHz raw-RF, coded excitation, and on-device DSP.

_Prices indicative — refresh from `options_prices.csv` against live LCSC/Digikey._
