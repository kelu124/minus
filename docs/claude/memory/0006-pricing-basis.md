# 0006 — Parts pricing basis

**Status:** current (as of 2026-09-17) · type: project

**When costing minus parts, use LCSC prices at low-quantity (~20–50 unit,
workshop-batch) orders.** Not qty-1, not reels/thousands — the workshop builds ~20–50
badges.

- Price references live in `options_prices.csv` (active parts only; passives ignored)
  and are summed per option in [[minus-direction]]'s `options.md`.
- Values there are **indicative** — refresh against live LCSC (qty 20–50) before
  committing to a BOM.
- Design for **JLCPCB assembly** ⇒ prefer LCSC/JLCPCB-stocked ("basic"/in-stock) parts
  (ties to req B2).

**LCSC availability findings (2026-09-17):** the cheap parts are OOS — **AD8338**
(gain) and **AD9200** (ADC) out of stock; **MD1213** (reuse pulser) not on LCSC.
In-stock picks: **AD8331 ~$10**, **AD9235-20 ~$17.9** (the ADC dominates BOM),
**TC6320 ~$2.03**, **LM2776 ~$0.48**, **RP2350B ~$1.06**. Realistic in-stock active-IC
front-end ≈ **$33** (ADC is the cost + availability bottleneck). Source URLs in
`options_prices.csv`.

Related: [[0005-minus-direction]].
