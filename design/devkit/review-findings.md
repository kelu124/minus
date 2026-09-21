# DesignA-DK — design review findings

**Date:** 2026-09-21 · **Method:** multi-agent flaw review (4 parallel reviewers) of the
devkit against the design docs and the PIC32AK datasheet (DS70005592 / DS70005583, mirrored
in `../../pdfs/datasheets/`). De-duplicated and severity-ranked. Reviewer domain tags:
**AFE** = RX analog / signal integrity · **PWR** = pulser + power · **DIG** = digital /
two-MCU / programming · **DS** = datasheet fact-check.

> Status: findings only — not yet applied to the schematics/docs. Deep redesign calls
> (gain-stage restructure, driver choice, LNA) are flagged as decisions, not silent
> rewrites. Track fixes here as they land.

## A. Confirmed factual errors in the docs — fix regardless (DS)

| # | Error | Correct value | Where |
|---|-------|---------------|-------|
| A1 | Claims an **external VREF+ pin** | **No such pin — ADC reference = AVDD** | pic32 §4; designA §5a + power table; devkit §3 + §7 |
| A2 | Op-amp **100 MHz / 100 V/µs** stated flat | **High-Power mode only; Low-Power = 50 MHz / 10 V/µs**; offset **±3 mV max** (not just ±1 mV typ) | pic32 §4; designA §5 |
| A3 | ADC "12-bit" implies 12 effective bits | **12-bit nominal, ENOB ≈ 10.5 bits** | pic32 §4; designA §5a |
| A4 | "differential ±VREF/4" as a PIC32AK fact | **Not in DS70005592** (from generic dsPIC33A docs) — keep tagged "verify" | designA §5a; pic32 §4 |
| A5 | "TC4427A has built-in dead-band" | **False — plain non-inverting driver, no interlock** | designA §4; devkit §6/B6 |
| A6 | "TC4427A in SOT-23-5" | **Impossible — the dual is 8-pin** | designA/devkit BOM |

**Confirmed CORRECT by DS** (no change): 40 Msps/12-bit ADC; single-ended 0→VREF
(LSB ≈ 0.8 mV); no internal PGA/GSEL ladder; PWM/PTG ADC-trigger + window/gate mode;
`6416` = 64 KB flash / 16 KB RAM (150 µs @ 40 Msps = 12 KB fits); 3× PGEC/PGED pairs +
JTAG; op-amp→ADC internal routing (OMONEN); 22 analog inputs (64-pin); 3.0–3.6 V.
**Op-amp input-noise density is unspecified in the datasheet → the LNA decision cannot be
closed on paper; the devkit must measure it.**

## B. High-severity design flaws

- **B1 — Gain chain can't meet spec at frequency** (AFE, compounded by DS/A2). OA2 at
  +42 dB → BW ≈ GBW/gain ≈ 0.78 MHz; realistic usable chain ≈ **~34 dB, not +56.5 dB**
  (worse in op-amp Low-Power mode, 50 MHz). *Fix:* distribute gain across more stages;
  the top of the range needs the LNA (FE-B) or a real VGA (FE-C/D).
- **B2 — Digipot as the small feedback Rg is invalid at high gain** (AFE). At 129× the
  needed Rg (~78 Ω) ≈ the pot wiper resistance (75–160 Ω) → uncontrolled, nonlinear,
  non-monotonic gain; the 10 kΩ MCP4531's own BW (~1–2 MHz) is below band. *Fix:* use the
  pot as an attenuator/divider, keep Rg ≫ Rw, or use the resistor-mux.
- **B3 — Anti-alias corner ~28 MHz is far too high** (AFE): ≈ −3.5 dB at Nyquist = no
  alias rejection for a 40/20 Msps ADC. *Fix:* move the RC corner to ~6–8 MHz.
- **B4 — Missing USB-C `Rd` (5.1 kΩ CC1/CC2 pull-downs)** (DIG): many USB-C sources never
  enable VBUS → board won't power up. Also verify RP2354 DP/DM 27 Ω terminations.
- **B5 — MCLR over-voltage can damage the RP2354** (DIG): a PICkit in HV-Vpp drives
  ~7.5–9 V onto the RP2354's 3.3 V GPIO on the shared ICSP net. *Fix:* **mandate LVP-only**
  and/or isolate the RP2354 MCLR tap (series R + clamp, or a lift jumper).
- **B6 — 40 Mbps SPI is the PIC's *master* spec, but the PIC is the *slave* here** (DIG):
  slave max SCK + output-valid delay are likely much lower → burst/PRF budget optimistic,
  data may corrupt. *Fix:* verify PIC SPI **slave** SCK/Tvalid (open — see §E).
- **B7 — HV-rail select incompatible with the P-FET totem** (PWR): a 5 V-referenced driver
  can't turn off a high-side P-FET on a boosted rail → destructive shoot-through. *Fix:*
  boost/external-HV = **MD1213 path only**; IRLML totem stays on 5 V (interlock it).

## C. Medium-severity

- **C1** Pulser topology ambiguous (tied-gate CMOS totem — recommended, 1 signal, no
  dead-time — vs complementary pair, which a 3-pin JP1 can't route) (PWR).
- **C2** TC4427A edges ~20–30 ns at 5 V, not 4–5 ns; use a faster driver (e.g. UCC27524A)
  if sharp edges matter (PWR).
- **C3** JP1 floating driver input → add a **10 kΩ pull-down** (pulser defaults OFF) (PWR).
- **C4** BAV99 clamps to ~4.3 V > PIC abs-max (~3.6 V); keep MD0100, add series R if BAV99,
  mark 5 V-TX-only (PWR).
- **C5** On-board boost >~18 V exceeds IRLML 20 V rating; clamp it — high V is MD1213-only (PWR).
- **C6** 100 µF on VBUS violates USB inrush (ferrite doesn't limit inrush); soft-start /
  split the bulk. Run-time VBUS sag is fine (PWR).
- **C7** Clamp diodes on the high-Z 40 Msps ADC node → leakage offset + nonlinear C; use a
  <1 pF low-leakage clamp behind a series R (AFE).
- **C8** Shared RX/ADC nodes: stubs + accumulated C + floating unselected inputs — prefer
  **0 Ω links soldered at the nodes over pin headers**; tie unused FE inputs to mid-rail;
  no analog muxes on the ADC node (AFE).
- **C9** Mid-rail bias/AC-couple at the *shared* ADC node can't serve FE-0 (bipolar!), FE-A
  and the 5 V VGAs without contention — give **each path its own AC-couple + bias-through-R**;
  explicitly level-shift FE-0 (AFE).
- **C10** 40 Msps ADC on internal FRC (no crystal): RC jitter degrades ENOB + breaks
  coherent averaging; ±1–2 % skews depth cal. Provide an optional clean clock and measure (DIG).
- **C11** Cross-boundary TRIG jitter → **averaging requires the PIC-owns-TX JP1 setting**;
  RP2354-owns-TX is single-shot only. Make explicit (DIG).
- **C12** Designate a **single I²C master** (RP2354) for the gain/OLED bus (DIG).
- **C13** Add series R on the RP2354's PGC/PGD/MCLR taps too (not just firmware Hi-Z) (DIG).
- **C14** Document PICkit **target-power OFF** / pin-2 sense-only vs the on-board LDO (DIG).
- **C15** ADC S/H settling through ~200 Ω + tap/jumper C unverified — check acquisition time
  & max source-Z; low-Z element at the pin (AFE; open — §E).
- **C16** Op-amp noise unspecified → treat the LNA (FE-B) as **probably-needed, not
  optional** (AFE/DS).
- **C17** Don't reuse ICSP pins for the 40 MHz SPI (stub + PICkit C); dedicated pins (DIG).
- **C18** 2N7002 minimal variant is impulse-only; use AO3400 (logic-level) + defined
  pull-up; note it can't do clean multi-cycle coded excitation (PWR).

## D. Low / documentation

- **D1** ICSP header inconsistency: designA §6b says 5-pin, others 6-pin → standardize on
  **6-pin** (pin 6 = NC) (DIG).
- **D2** Frame rate is **SPI-transfer-limited** (~400–800 lines/s at real SPI), not
  acoustically limited — state it; consider on-PIC decimation (DIG).
- **D3** Shunt damping R loads RX (prefer series/switched); add small series **gate
  resistors**; ensure the **3V3 LDO taps VBUS before the pulser ferrite** (PWR).

## E. Still open — need bench or a spec not in hand

PIC SPI **slave** max SCK & Tvalid (B6) · ADC **S/H** acquisition time / max source-Z (C15)
· op-amp **input noise** → LNA decision (C16) · MCP4531 exact BW / wiper R (B2) · LVP entry
P-timings for the RP2354 bit-bang · FRC-vs-crystal **ENOB** (C10). **These are exactly what
the devkit exists to measure — the modular approach is validated.**

## Meta-conclusion

The **jumper/modular devkit concept is sound** (jumper inductance is negligible at
3–4 MHz), with two refinements: **0 Ω links instead of pin headers at the RX/ADC nodes**
(C8) and **per-path bias** (C9). The **FE-A "DesignA path" as drawn will under-perform**
(B1/B2) — which is precisely why building the derisk devkit before freezing DesignA is the
right call.

## Fix tracker

- [ ] A1–A6 doc corrections applied
- [ ] B1–B7 addressed in schematic / flagged as decisions
- [ ] C1–C18 addressed
- [ ] D1–D3 addressed
- [ ] E-items scheduled as bench measurements
