# minus — component options (filtered shortlist)

A **filtered subset** of the landscape in [`analysis.md`](analysis.md), keeping only
options that pass minus's criteria, with indicative pricing. The full landscape and
rationale live in `analysis.md`; the requirements in [`requirements.md`](requirements.md).

**Filter criteria (from requirements):** 3–4 MHz, **raw RF** (see open item RF-ACCESS),
**RP2350 + external ADC** route, **unipolar preferred** (bipolar only if a cheap ± rail),
**cheapest BOM / fewest parts** (DP1–DP3), **derisk by reusing** the owner's proven
blocks (DP5).

**Prices:** from [`options_prices.csv`](options_prices.csv) — **reference is LCSC at
low-quantity (~20–50 unit, workshop-batch) pricing**, active parts only (passives
ignored), each with a **source URL** in the CSV. Totals are active-IC only (exclude
passives, connectors, PCB, and badge peripherals).

> **⚠ Availability reality-check (LCSC, 2026-09-17).** The *theoretically cheapest*
> parts are **out of stock**: **AD8338** (gain) and **AD9200** (ADC) are OOS at LCSC,
> and **MD1213** (reuse pulser driver) is **not listed** on LCSC. The in-stock picks
> are pricier: **AD8331 ~$10**, **AD9235-20 ~$17.88** (not the ~$10 first estimated),
> **TC6320 ~$2.03**, **LM2776 ~$0.48**, **RP2350B ~$1.06**. **The high-speed ADC is
> the cost + availability bottleneck** (a known pain for DIY ultrasound). So the
> realistic in-stock BOM is dearer than the theoretical floor — see build table §4.

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

| Option | Part(s) | Gain | $ (incl gain-ctrl) | Stock | Notes |
|--------|---------|------|:------------------:|:-----:|-------|
| **G2 — AD8331** *(derisked, DP5)* | AD8331 (+ PWM) | 48 dB | **~$10.0** | **in stock** | un0rick/pic0rick VGA; ultrasound-grade |
| G1 — AD8338 | AD8338 (+ PWM ramp) | 0–80 dB | ~$4.0 | **OOS** | cheaper/low-power (WULPUS PRO) but **out of stock at LCSC** |
| G3 — AD603 + LNA | AD603 + LNA op-amp | ~40 dB | ~$5.0 | check | BOM-floor; lower dynamic range |

**Lean pick:** **G2 (AD8331)** is now the pragmatic choice — **in stock**, proven
(DP5), ~$10. G1 (AD8338) would be cheaper/lower-power **if** back in stock. **BOM
saver:** set the gain-control voltage from **RP2350 PWM + RC** (no DAC IC).

## 3. ADC — shortlist

Applies only if **RF-ACCESS = raw RF** (else the RP2350 internal 500 kSps ADC and no
external ADC). Need ≥16 MSps (4× 4 MHz), target 20–30 MSps, ≥10-bit, parallel output
for PIO capture. Excluded: LTC2203 (16-bit, ~$25 — over-spec/large).

| Option | Part | Spec | $ | Stock | Notes |
|--------|------|------|:--:|:-----:|-------|
| **A1 — AD9235-20** | AD9235BRUZ-20 | 12-bit 20 MSps | **~$17.9** | **in stock** | LCSC C514274; pricey but available; the ADC dominates the BOM |
| A2 — AD9200 | AD9200ARSZRL | 10-bit 20 MSps | ~$4.7 | **OOS** | cheap + enough (P4) but **out of stock at LCSC** |
| A3 — ADC10065 *(DP5)* | ADC10065 | 10-bit 65 MSps | ~$10 | check | un0rick/pic0rick part; verify LCSC stock |
| A4 — AD9280 | AD9280 | 8-bit 32 MSps | ~$4 | check | cheapest, but ~48 dB only — marginal vs P5 |

**Lean pick:** **A1 (AD9235-20)** is the only *confirmed* in-stock option, but at
~$18 it **dominates the BOM**. Cheaper 8-bit candidates to **verify directly on LCSC**
(search was inconclusive): **TLC5540** (8-bit 40 MSps, ~$3), **ADS830** (8-bit
60 MSps), **AD9280** (8-bit 32 MSps) — all ~$3–5 but **8-bit ≈ 48 dB (marginal vs
P5 ≥50 dB)**. Also check **ADC10065** (DP5) stock. **This is the open cost driver
(ADEC)** — needs a direct LCSC check.

---

## 4. Candidate builds (active-IC BOM only, excl. passives/connectors/PCB)

| Build | Pulser | Gain | ADC | MCU | ~Active-IC $ | All in stock? |
|-------|--------|------|-----|-----|:------------:|:-------------:|
| **In-stock realistic** | U0 5V-only (~4.5) | G2 AD8331 (10.0) | A1 AD9235-20 (17.9) | RP2350B (1.06) | **~$33** | ✅ (verify T/R) |
| **Theoretical floor** *(if restocked)* | U0 (~4.5) | G1 AD8338 (4.0) | A2 AD9200 (4.7) | RP2350B (1.06) | **~$14** | ❌ AD8338+AD9200 OOS |
| **Derisked (DP5 reuse)** | U2 MD1213+TC6320 (~11.5) | G2 AD8331 (10.0) | A3 ADC10065 (10.0) | RP2350B (1.06) | **~$33** | ⚠ MD1213 not on LCSC; ADC10065 verify |

Badge peripherals add ~a few $ (OLED ~$1.5, RGB LED ~$0.1, USB-C ~$0.3, RPi header,
SMA/uFL) — outside this options pricing (passives/connectors ignored per scope).

**Reading:** with **in-stock LCSC parts today**, a coherent minus front-end is
**~$33 in active ICs**, and the **AD9235-20 ADC (~$18) is over half of it** — the
ADC is the cost + availability bottleneck. The theoretical floor (~$14) needs AD8338
and AD9200 back in stock. Reusing the exact un0rick pulser (MD1213) is blocked by LCSC
availability, nudging toward the discrete U0/U1 unipolar path for a JLCPCB-buildable
badge. All still meet 3–4 MHz raw-RF, coded excitation, and on-device DSP.

_Prices from `options_prices.csv` (LCSC, qty ~20–50, with source URLs); refresh live._
