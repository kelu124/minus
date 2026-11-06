# 0013 — RX front: a cheap MMIC LNA (BGA2817) ahead of the PIC op-amps, and the FE-A fixes

**Status:** proposal (session 09, 2026-11-06, discussion only — nothing built or measured) · type: project ·
sources: `pdfs/datasheets/BGA2817_MMIC-wideband-amp_24dB_3V3.md` (NXP Rev. 7, 2017),
`pdfs/datasheets/BGA2869_MMIC-wideband-amp_31dB_5V.md` (NXP Rev. 3, 2015), memory 0012, `TODO_HARDWARE.md`.

## Why
- PIC op-amp: GBW 100 MHz (High-Power mode only; Low-Power 50 MHz, slew 10 V/µs → ~0.6 Vpp at 5 MHz).
  Practical ceiling **≈ ×10 (20 dB) per stage** for a ≤ 5 MHz echo; two stages ≈ 34 dB (−1 dB at 5 MHz) …
  44 dB (−3 dB); three stages (OA3) ≈ 45–60 dB. Op-amp input noise is unspecified (review C16).
- 40 dB turns a 100 µV deep echo into 10 mV ≈ 12 LSB — too little. A low-noise fixed-gain block in front
  fixes both gain and the noise unknown for < 1 €.

## Candidates (datasheet facts; all SOT363, internally matched 50 Ω, "DC to 2.2 GHz", unconditionally stable K > 1)
| Part | Supply | Gain (250 MHz) | NF | Out P1dB | In P1dB (≈) | Abs. max drive | LCSC |
| --- | --- | --- | --- | --- | --- | --- | --- |
| **BGA2817** | **3.0–3.6 V**, 20 mA | **24.2 dB** (23.6–24.8) | 3.9 dB | +6 dBm (≈1.26 Vpp/50 Ω) | ≈ −18 dBm (≈80 mVpp) | +10 dBm | C2654187 (JLCPCB-listed; one stale snapshot $0.09 — verify) |
| BGA2869 | 4.5–5.5 V, 24 mA | 31.1 dB | 3.1 dB | +10 dBm (≈2 Vpp/50 Ω) | ≈ −20 dBm | +10 dBm | C515583 ($0.65 or $1.50 on two LCSC pages) |
| BGA2801 / BGA2818 / BGA2851 | — | ~22 / 30 / 25 dB (search snippets, not verified) | | | | | C2688109 / C440700 / — |

**Pick: BGA2817** — runs from the 3.3 V rail (no 5 V), 24 dB ≈ ×16 (close to the 20 dB asked), JLCPCB-listed.
BGA2869 if more gain / lower NF / more headroom is wanted and 5 V (VBUS, filtered) is acceptable.

**Unverified at our frequency:** both datasheets characterise only ≥ 250 MHz. Gain flatness, input impedance and
NF at 3–5 MHz must be bench-measured (1 MHz–5 MHz tone, DS203). Datasheet: DC blocks "should be increased
below 100 MHz".

## Proposed circuit
```
MD0100 T/R ─┬─ BAV99 (±0.7 V to GND ≈ +7 dBm < +10 dBm abs max)
            └─[10 nF]─ RF_IN  BGA2817  RF_OUT ─[10 nF]─┬─ OA1 IN+   (OA1 ×≤10, OA2 ×1…×10 via 74HC4051 legs)
                         VCC ← 3V3 via 10 Ω/ferrite    └─[51 Ω]─ Vmid (≈1.65 V, 10 µF to GND = AC ground)
                               + 1 µF + 470 pF at pin 1;  pins 2/4/5 to a solid ground with several vias
```
- **10 nF couplers, not 100 nF:** HP corner ≈ 320 kHz (also cuts LF/pulser tail) and a short 0.5 µs recovery
  after the TX overload charges the caps (100 nF × 50 Ω = 5 µs ≈ 4 mm dead zone).
- **51 Ω to a decoupled Vmid** both terminates the MMIC (defined 24 dB voltage gain in a 50/50 system;
  unterminated ≈ +6 dB) and DC-biases OA1 IN+ at mid-rail — fixes the FE-A ground-reference bug in one part.
- Gain budget: 24 dB + OA1 (≤ 20 dB) + OA2 0–20 dB ≈ **44–64 dB**. Noise at the MMIC input
  ≈ 1.4 nV/√Hz (50 Ω, NF 3.9 dB) → ~3 µV rms in 5 MHz → ~5 mV rms (≈ 7 LSB) at 64 dB: the ADC is no longer
  the limit; more gain only lifts noise. If the PIC op-amp noise is > ~20 nV/√Hz it still matters → BGA2869.
- Cost ≈ MMIC + 6 passives; 66 mW (can be gated by a P-FET between frames if power matters).

## FE-A fixes that go with it (from the same discussion, also in TODO_HARDWARE)
1. One mid-rail bias domain: AC-couple the RX node, bias to Vmid, clamp around Vmid (D7 now clamps to −0.6 V,
   likely beyond the PIC pin's −0.3 V abs max); R28/R36 → C + R.
2. Gain legs R47/R49 (or the switched legs) get a series cap → DC gain ×1 (offset ±3 mV × 121 = ±0.36 V otherwise).
3. AC coupling + re-bias between OA1 OUT and OA2 IN+ (e.g. 330 pF, 2 × 10 k to Vmid ≈ 100 kHz HP).
4. Clean Vmid (divider + 10 µF, or OA3 as Vmid buffer).
5. HPEN = 1 on every op-amp used (OA1 confirmed in `firmware/pic32/acq.c`; OA2 to check).
6. OA2 gain: GPIO legs or 74HC4051 at the **ground end** of the legs, Rf ≈ 20 k so the 4051's
   100–200 Ω Ron is a few % (8 steps from 3 GPIOs; one 4051 cannot serve OA1 and OA2 at once — use a 4052/4053).
7. Small IN− nodes; OA2 IN− is also TMS (stub). Anti-alias RC at 6–8 MHz; FE_A_OUT routed to the ADC node.

## Devkit test idea
A small U.FL-in/U.FL-out BGA2817 board fed from the RX node, output into **RF5 (OA1 IN+ IPEX)** with the
51 Ω-to-Vmid termination; measure gain vs frequency with the tone first.

## Related
[[0012-rx-chain-oa2-gain]], [[0007-designA-devkit]] (review B1/C16), [[0006-pricing-basis]].
