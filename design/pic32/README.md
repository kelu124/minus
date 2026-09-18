# design/pic32 — concept: PIC32A analog engine + RP2350 front-end

**Status:** concept / thoughts only (started 2026-09-18). No schematic yet.
This folder holds the *idea* of pairing a **Microchip PIC32AK…GC41064** ("PIC32A")
with the **RP2350** for *minus*. Datasheet/product brief:
[`pdfs/datasheets/PIC32AK1216GC41064-family-product-brief-DS70005582.pdf`](../../pdfs/datasheets/PIC32AK1216GC41064-family-product-brief-DS70005582.pdf).

> This is an **alternative architecture** to the current baseline (RP2350 + a
> separate high-speed ADC + separate VGA, per `requirements.md` §0 and
> `docs/claude/memory/0005-minus-direction.md`). It is not (yet) a decision — it's a
> trade study to capture the concept the owner raised.
>
> **Cheapest instantiation:** [`../designA/README.md`](../designA/README.md) — DesignA
> (RP2354A + PIC32A, 5 V N-FET pulser, digipot gain; active-IC BOM ≈ $3.7 / board ≈ $5).
>
> **PIC32 programming/flashing (practical):** [`pic32.md`](pic32.md) — ICSP header,
> PICkit/MPLAB, the two flashing paths, MCLR network.

---

## 1. The idea

Use the **PIC32A as the analog acquisition engine** and the **RP2350 as the open
USB/host front-end, manager, and DSP co-processor**:

- **PIC32A op-amps → the gain stage.** Its **three 100 MHz rail-to-rail op-amps**
  (100 V/µs slew, 1 mV offset) build the receive gain chain (LNA / filter / buffer)
  for a 3–4 MHz echo — no external VGA IC.
- **PIC32A ADC → digitize raw RF.** Its **two 12-bit ADCs at up to 40 Msps** sample
  the echo directly. It captures **one A-line (up to ~150 µs)** into its own SRAM.
- **PIC32A → RP2350 transfer.** The captured line is shipped to the RP2350 over a
  fast link (SPI, up to 40 Mbps on both parts).
- **RP2350 preprocesses + exposes.** RP2350 runs DSP (bandpass, Hilbert/envelope,
  decimation, matched filter), drives the OLED/RGB, and **exposes the data over its
  native USB-C** to the host — the role it already owns in the baseline.
- **RP2350 flashes the PIC.** RP2350 can program the PIC32A over its **2-wire ICSP**
  (bit-banged / PIO), so a **single USB-C port** boots and programs *both* chips: the
  RP2350 comes up via UF2 drag-and-drop, then flashes a bundled PIC image. No PICkit.

The division of labour is clean and plays to each chip's strength:

| Job | Chip | Why |
|-----|------|-----|
| HV pulse sequencing (coded excitation) | either | PIC32A HS-PWM (2.5 ns) + PTG, *or* RP2350 PIO — TBD |
| RX gain (LNA / filter) | **PIC32A** | 3× 100 MHz op-amps on-die |
| Digitize raw RF | **PIC32A** | 12-bit **40 Msps** ADC on-die |
| Buffer 1 line (~150 µs) | **PIC32A** | ADC → its SRAM, then burst out |
| USB host link | **RP2350** | PIC32A has **no USB**; RP2350 has native USB |
| Open reflash (UF2) | **RP2350** | RP2350 = open front door; flashes the PIC over ICSP |
| DSP / envelope / matched filter | **RP2350** (and/or PIC32A DSP) | both have FPU/DSP; RP2350 has more RAM |
| OLED / RGB / badge UI | **RP2350** | PIO for WS2812; existing plan |

## 2. Why this is *relevant* — the numbers line up

The PIC32A's on-die analog is the whole point: it **collapses the external ADC
(open item ADEC) and the external VGA (A3) into the MCU itself**.

- **Raw-RF sampling (P3/P4).** minus needs ≥ 16 MSps (target 20–30), ≥ 10-bit.
  PIC32A: **40 Msps, 12-bit** — clears both with headroom, and would even allow a
  higher fc later.
- **Analog bandwidth (P2).** Op-amps at **100 MHz** GBW / 100 V/µs comfortably pass
  a 3–4 MHz band.
- **150 µs capture vs SRAM.** This part (PIC32AK3208GC41064) has **8 KB SRAM**
  (Digikey: 8K×8) — smaller than the family max, so the depth math is tight:
  - At **20 Msps**: 150 µs → 3 000 samples × 2 B = **6 KB** ✓ fits (leaves ~2 KB for
    stack/vars — code runs from flash). Good match for the owner's "up to 150 µs".
  - At **40 Msps**: 150 µs → 12 KB ✗ **does not fit** in 8 KB. Full-rate grabs are
    capped at ~**80–100 µs** (or capture decimated / windowed). RP2350 (far more RAM)
    buffers longer lines and multiple lines. ⇒ **the PIC grabs one line within 8 KB and
    bursts it out; deep/multi-line buffering stays on the RP2350.**
- **3.3 V everywhere.** PIC32A runs 3.0–3.6 V, same domain as RP2350 → simple SPI
  interconnect, shared 3V3 rail.
- **Coordination built in.** HS-PWM has "flexible trigger configuration for ADC
  triggering" and there's a Peripheral Trigger Generator (PTG, a CPU-independent
  state machine) — good for firing TX and starting the ADC deterministically.

## 3. Trade-off vs the current baseline

**Baseline:** RP2350 + external high-speed ADC (on PIO) + external VGA (e.g. AD8338)
+ T/R + unipolar pulser.

**This concept:** RP2350 + PIC32A (ADC + op-amp gain in one) + T/R + pulser.

### Potential wins
- **Fewer analog ICs / smaller board (DP1–DP3).** One PIC32A replaces *both* the
  external ADC and the external VGA/LNA. Could be a net part-count reduction even
  though it adds a second MCU.
- **No PIO-clocked external-ADC bus to design.** The trickiest part of the baseline
  (gap-free parallel ADC capture over PIO+DMA, C1b) moves on-die into the PIC32A.
- **Better ADC than the cheap-ADC shortlist** (40 Msps/12-bit vs 20 Msps/10-bit
  candidates) — more dynamic range and future headroom.
- **Rich extra analog for free:** 3 comparators + 12-bit DACs (threshold/echo
  detect, gain-node bias, offset trim), current sources, HS-PWM for the pulser.

### Costs / risks / tensions
- **⚠️ Open-toolchain tension (anti-requirement N1 / S4).** PIC32A builds with
  Microchip's **MPLAB X + XC-DSC** (proprietary, closed; optimized tiers licensed) —
  **not** an open GCC flow like RP2350's pico-sdk (DP4). Mitigation: ship a
  **prebuilt PIC image** that the RP2350 flashes over ICSP, so *using/reflashing* the
  badge stays fully open (UF2 → RP2350 → ICSP → PIC). Only attendees who want to
  **modify the PIC firmware** need the closed toolchain. This is the single biggest
  philosophical cost and must be a conscious, documented trade (see §19 N1, N5).
- **Gain is set by external feedback resistors, not a built-in PGA.** For the PIC32AK
  op-amps, unity-gain mode needs no external parts; for gain you **disable unity-gain
  and add external R** (no confirmed internal GSEL resistor ladder like some dsPIC33/
  PIC24 — *verify in the datasheet; if present it'd give register-set gain with zero
  extra parts*). Since **TGC is not required** (see §3b), this is only a *per-line
  settable* gain — a digital pot / MDAC in the feedback path, cheap and simple.
- **Two MCUs = more firmware surface.** Two codebases, an inter-MCU protocol, and a
  boot/flash sequence to maintain. Against DP3 (simplicity) at the *firmware* level,
  even if the *hardware* gets simpler.
- **Sourcing / cost unknown (anti-req N2).** Need **LCSC stock + price at qty 20–50**
  and JLCPCB assemblability confirmed (see `docs/claude/memory/0006-pricing-basis`).
  Seen at RS/Digikey (TQFP-64 `-I/PT`, QFN `-I/M7`); **LCSC availability TBD** — if
  not JLCPCB-stocked, that's an N2 strike against it.
- **SRAM is small (8 KB).** Fine for one ~150 µs line at 20 Msps (6 KB); *not* enough
  for 150 µs at full 40 Msps, nor for deep multi-line buffering — that stays the
  RP2350's job (which has far more RAM). See §2.
- **Departs from DP5 (reuse).** None of the owner's proven designs
  (un0rick/lit3rick/pic0rick) use a PIC32A analog engine — this is new ground, so it
  carries integration risk the reuse principle was meant to avoid.

## 3a. BOM simplicity & the cheapest pulser

**Is the BOM relatively simple?** Yes — competitively so, because the PIC32A folds the
two costliest external analog parts into itself:

| Block | Baseline (RP2350 route) | PIC32A concept |
|-------|-------------------------|----------------|
| ADC | external high-speed ADC IC | **on-die (40 Msps)** — removed |
| RX gain / LNA / VGA | external VGA (e.g. AD8338) | **on-die op-amps** — removed |
| MCU flash | RP2350 needs **external QSPI flash** | PIC32A has internal flash; RP2350 still needs its flash (or use RP2354 = stacked flash) |
| Clock | RP2350 crystal | PIC32A internal FRC+PLL (no xtal); RP2350 xtal for USB |
| Controller | RP2350 | RP2350 **+ PIC32A** (adds one IC) |

Net: **delete the external ADC + VGA, add the PIC32A** → active-IC count comparable or
lower, and layout is easier (no PIO-clocked parallel-ADC bus to route).

**Price check (2026-09-18):** the PIC32A is **cheap** — Digikey lists
`PIC32AK3208GC41064-I/PT` (TQFP-64, 32 KB flash, 8 KB RAM) at **$1.91 / 1, $1.73 / 25,
$1.58 / 100**, **498 in stock**, 7-week factory lead. So it replaces the external
**ADC + VGA for < $2** — a clear win for DP2/cheapest, *better* than the baseline
"cheapest" active-IC BOM (≈ $16 with AD8338 + cheap ADC + RP2350).

**LCSC / JLCPCB availability (checked 2026-09-18): NOT confirmed — likely not stocked
yet (N2/B2 risk).** LCSC site-restricted search returned no listing, and JLCPCB's parts
library search surfaced nothing for `PIC32AK`; RS/Mouser list the family but mostly
out-of-stock / 2026 lead. It's a new part (2024 product brief). **Consequence:** for the
project's LCSC/JLCPCB assembly flow it would currently be a **consigned / "extended"
part** (self-supplied, feeder fee) or you source from **Digikey** and hand-place. This
is the main open sourcing risk — re-check `jlcpcb.com/parts` + the LCSC BOM tool
periodically, as new Microchip parts do get added over time.

**Cheapest pulser — 5 V PIO → transistor gating 5 V (= `options.md` U0).** Viable as
the low-cost baseline. Get four things right:
- **Topology / gate drive.** GPIO/PIO is 3.3 V → a **logic-level N-FET low-side**
  (2N7002-class) switches cleanly. Pushing +5 V high-side (P-FET) gives only ~−1.7 V
  Vgs from a 3.3 V swing — marginal; needs a logic-level P-FET or a level shift. Low-side
  N-FET is the simple answer.
- **Edge speed at 3–4 MHz.** Half-period ~125–165 ns ⇒ want edges < ~30 ns. A *small*
  FET (Ciss ~30–50 pF) can be driven straight from a pin (~20 ns) for a low-amplitude
  demo; for real punch add a **small gate driver** (hence T3's "MOSFET + gate driver").
- **Amplitude is low.** 5 V = weak pulse; fine for a superficial (1–4 cm) muscle demo
  with front-end gain + averaging + coded excitation. Keep the **HV node on a header
  (T7)** so higher HV can be jumpered in later.
- **Keep the T/R clamp (A2)** — even at 5 V the RX/op-amp inputs need protecting from
  the TX edge (a couple of diodes suffice at 5 V).
- **Synergy:** the PIC32A's high-current I/O + **2.5 ns HS-PWM with ADC trigger** can
  drive the gate with cleaner, better-timed (and coded/chirp) edges than a bare GPIO —
  a point in favour of letting the PIC own TX sequencing.

## 3b. Gain stage — no TGC, just per-line settable gain

**Decision (owner, 2026-09-18): TGC is NOT required.** No need to vary gain *during* a
line (depth-dependent ramp). Instead: **the user sets a fixed gain, and can change it
between firing lines.** This is much simpler than a VGA + fast DAC ramp, and it removes
the hardest part of the analog front-end (gain/depth timing sync). It supersedes the
TGC intent in `requirements.md` F6/A3/P8 — see the note there.

**What "set a gain between lines" needs:** a gain that is *static within a line* but
*digitally re-settable between lines* by firmware. On the PIC32A the op-amp gain is set
by **external feedback resistors** (unity-gain mode = no external parts; for gain,
disable unity-gain and add Rf/Rin). To make that gain programmable between lines,
options in rough order of cost/simplicity:

| Option | How | Cost | Notes |
|--------|-----|------|-------|
| **Digital potentiometer / MDAC in feedback** *(fits the owner's "DAC controls gain")* | Replace the feedback (or input) resistor of a PIC32A op-amp with a digipot (e.g. MCP41xxx, SPI) or a multiplying DAC; firmware sets the code between lines | ~$0.5–1 | Smooth/many-step gain, set over SPI/I²C by either MCU. **This is the recommended fit.** |
| **Resistor bank via analog mux/GPIO** | An analog switch selects among a few fixed feedback resistors → 3–4 discrete gain steps | ~$0.2–0.5 | Cheapest; stepped gain is fine if the user only needs a few levels between lines |
| **External VGA/PGA IC** | A real gain-controlled amp (e.g. AD8338) driven by a control voltage/DAC | ~$2–4 | Reintroduces the part we deleted; only worth it if the op-amps aren't good enough |

> **Note on "DAC controls op-amp gain":** an op-amp's gain lives in its **resistor
> ratio**, so the right primitive is a *digitally-controlled resistor* (digipot/MDAC)
> in the feedback path — not a DAC voltage into a summing node. A DAC voltage sets gain
> only in a true multiplier/VGA (e.g. AD8338), which is the external part we're avoiding.
> The PIC32A's on-die 12-bit DAC is still useful for **offset/bias trim** or a
> comparator threshold, not for setting op-amp gain directly.

**LNA-first alternative (the owner's other idea).** The PIC32A op-amps are
general-purpose 100 MHz parts; their input **noise** isn't specified as low. For weak
echoes (a 5 V pulser gives a small signal), put a **fixed low-noise LNA as the first
stage** to set the noise floor, then the settable-gain op-amp stage, then the ADC:

`transducer → T/R clamp → [fixed LNA] → settable-gain op-amp → anti-alias → ADC`

The LNA adds one cheap low-noise op-amp (~$0.3–1) but improves sensitivity/SNR — good
insurance given the low TX amplitude. Whether it's *needed* depends on the PIC32A
op-amp's measured noise vs the echo level (open item). Baseline can start **without**
it (op-amp gain only) and add it if SNR limits the demo.

**Verify:** does the PIC32AK op-amp have an internal programmable-gain (GSEL) resistor
ladder like some dsPIC33/PIC24 parts? The family notes point to *external* resistors,
but if a GSEL ladder exists it would give register-set per-line gain with **zero extra
parts** — the ideal outcome. Confirm in the full datasheet / op-amp FRM.

## 3c. Chip choice — package (pins) & program memory

The family comes in **three pin counts** and several **flash/RAM tiers**; pin count and
memory are independent axes of the part number
(`PIC32AK`**`<flash><ram>`**`GC41`**`<pins>`**, e.g. `3208…064` = 32 KB flash / 8 KB
RAM / 64-pin; `1216…` = the 128 KB / 16 KB top of family).

### Pins: 36 vs 48 vs 64
| Pins | Package | I/O / analog | Fit for *minus* |
|------|---------|--------------|-----------------|
| **36** | VQFN | fewest | Smallest, but tight — after the RX analog pins + SPI + ICSP/reset + a couple of handshake lines there's little spare. Only if a pin-budget pass confirms it fits. |
| **48** | TQFP / VQFN | mid | **Sweet spot.** Comfortable for one RX channel + SPI-to-RP2350 + ICSP + handshakes, still small. |
| **64** | TQFP / VQFN | 49 I/O, ≤22 analog | Generous headroom / test points, but larger. Less needed here since the **RP2350 owns the 40-pin extension header** (C5) — the PIC's I/O demand is modest. |

Rough pin budget (single channel): ~3–6 analog (op-amp in/out + echo in; the ADC can
tap the op-amp output internally) + SPI (4) + ICSP/reset (3, muxable) + IRQ + TRIG
(+ optional UART 2) + optional pulser-gate (1) ≈ **12–16 pins used** → **36 is
borderline, 48 is safe.** Recommend **48-pin** unless a layout pass proves 36 works.

### Program memory (flash) & the real lever: SRAM
- **Flash:** the PIC's firmware is small — ADC capture into RAM, SPI burst-out, TX
  sequencing, maybe light DSP. That's tens of KB at most, so **32 KB flash is ample**;
  only reach for a bigger tier if on-PIC DSP grows. *Confirm once firmware exists.*
- **SRAM is the binding constraint, not flash** (see §2): it sets how much of an A-line
  the PIC can hold.
  - **8 KB (the cheap `3208`)** → ~6 KB capture = **150 µs @ 20 Msps** ✓ (but not
    150 µs @ 40 Msps).
  - **16 KB** → **150 µs @ 40 Msps** (12 KB) fits. The cheapest way to 16 KB is the
    **`6416` tier (64 KB flash / 16 KB RAM)** — no need to jump to the 128 KB `1216`.
- Known flash/RAM tiers: **`3208`** (32/8), **`6416`** (64/16), **`1216`** (128/16).
- **Recommendation:** start with **`PIC32AK3208GC41048`** (32 KB / 8 KB, 48-pin) —
  cheapest, covers 150 µs @ 20 Msps. If full **40 Msps × 150 µs** is needed, step to
  **`PIC32AK6416GC41048`** (64/16, same 48-pin) rather than the 128 KB part. (Confirm
  the exact intermediate flash/RAM tiers
  and per-SKU prices on the Microchip product selector / LCSC.)

### Footprint — keep it as small as feasible (DP1)
Each pin count is offered as **TQFP** (`-…/PT`, gull-wing leads) *and* **VQFN**
(`-…/M7`, leadless). Approximate body sizes (confirm against the package drawing):

| Part / pins | TQFP body (0.5 mm pitch) | VQFN body |
|-------------|--------------------------|-----------|
| 36-pin | — | **≈ 5 × 5 mm** (smallest) |
| 48-pin | ≈ 7 × 7 mm (≈ 9 × 9 w/ leads) | **≈ 6 × 6 mm** |
| 64-pin | ≈ 10 × 10 mm (≈ 12 × 12 w/ leads) | ≈ 9 × 9 mm |

Guidance for the smallest board:
- **VQFN beats TQFP** on area (no gull-wing leads) — but it's **bottom-terminated /
  leadless**, which anti-req **N2** flags to avoid *where avoidable* (harder to hand-
  solder / visually inspect). **However, the board already carries a QFN RP2350**, so
  it's reflow/JLC-assembled anyway → a VQFN PIC adds no new assembly requirement. ⇒ For
  a JLC-assembled badge, **48-pin VQFN (~6×6 mm)** is the small-but-adequate pick;
  offer **48-pin TQFP** as the hand-solder-friendly alternate; **36-pin VQFN (~5×5 mm)**
  only if the pin budget (§3c) is confirmed and minimum area is paramount.
- **Shrink the RP2350 too:** with the PIC32A doing the ADC + analog, the RP2350 no
  longer needs a wide parallel-ADC GPIO bus → the **RP2350A (QFN-60, 7×7 mm)** likely
  suffices instead of the larger **RP2350B (QFN-80, 10×10 mm)**, and **RP2354A**
  (QFN-60, 7×7, 2 MB stacked flash) *also deletes the external QSPI flash chip* — both
  a smaller MCU and one fewer part. Re-check the RP2350 GPIO budget once the interconnect
  (§3d) is fixed.
- **RP2354A confirmed (datasheet §14.3, §2.1):** 2 MB **in-package** flash (a stacked
  Winbond W25Q16JVWI die), QFN-60, **pin-identical to RP2350A**, 30 GPIO / 4 analog. So
  **no external QSPI flash chip** on the BOM/PCB. **On LCSC/JLC: C41378174, ~$1.27, in
  stock** (JLC-assemblable ✓). Caveats: **QSPI_IOVDD must be 3.3 V**;
  an *extra* QSPI device (more flash / PSRAM) can still hang off the QSPI bus using a
  Bank-0 GPIO as chip-select if ever wanted.
- **BOOTSEL button (RP2354A):** the six QSPI pads (incl. **QSPI_CSn / SS**) are still
  bonded to package pins even though the flash is internal, and BOOTSEL is entered by
  **pulling QSPI_CSn low at reset/power-up** ("harmlessly selects the internal flash
  die"). ⇒ Wire the BOOTSEL button exactly as on a flashless RP2350A/Pico: **from the
  QSPI_CSn (SS) pin to GND, via a ~1 kΩ series resistor**, pressed during power-up. To
  enter BOOTSEL without a power cycle, pair it with a **RUN (reset) button** (hold
  BOOTSEL, pulse RUN low). On the badge these can be small tact switches or just test
  pads if we minimise buttons.
- Board size is ultimately also set by the **connectors** (USB-C, SMA, the 40-pin
  header) and test points — but on the silicon side, two ~6–7 mm QFNs is compact.

## 3d. RP2350 ↔ PIC32A interconnect

Division of roles (§1): **RP2350 = manager / USB / programmer / DSP; PIC32A = capture
engine.** So the RP2350 is the SPI **master** and the PIC's **programmer**, and the PIC
signals when a line is ready. Proposed signals:

| Link | Signals | Dir | Purpose |
|------|---------|-----|---------|
| **ICSP (program + reset)** | `MCLR`, `PGC`, `PGD` | RP2350 → PIC | RP2350 flashes the PIC over 2-wire **LVP ICSP** (PIC32 Flash Programming Spec DS60001145); `MCLR` doubles as the **reset** line so RP2350 can hold/boot the PIC. One USB-C port programs both (RP2350 via UF2 → then flashes the PIC). |
| **SPI (data)** | `SCK`, `MOSI`, `MISO`, `CS` | RP2350 master ↔ PIC slave | Burst the captured A-line out (PIC SPI ≤ 40 Mbps; ~6–12 KB ≈ 1–2.5 ms between pulses). Also carries config/commands. |
| **Data-ready / IRQ** | `RDY` | PIC → RP2350 | PIC raises it when a line is captured → RP2350 reads it (avoids polling). |
| **Trigger / sync** | `TRIG` | RP2350 → PIC | Hardware start for acquisition; if RP2350 owns TX (PIO), this fires the PIC's ADC via its external-trigger input so TX and RX stay time-aligned. (If the **PIC** owns TX via HS-PWM+PTG, `TRIG` just means "go" and TX↔ADC sync is on-chip.) |
| **UART (optional)** | `TX`, `RX` | ↔ | Cheap debug/log + low-rate control channel independent of SPI; PIC can emit logs the RP2350 forwards to USB. Drop it to save 2 pins if tight. |
| **Power** | shared **3V3**, GND | — | Both run 3.0–3.6 V → single rail; each with its own decoupling (+ PIC `VCAP`). |

Notes:
- **Pin reuse:** the ICSP pins (`PGC`/`PGD`) are muxed GPIO on the PIC — they can double
  as run-time handshake/SPI lines after programming, which helps the 36/48-pin budget.
- **Who is SPI master:** RP2350-master + PIC `RDY` interrupt is the clean default (the
  manager pulls data from the smart peripheral). PIC-as-master (pushing) is possible but
  complicates RP2350-side buffering.
- **Minimal set** if pins are tight: ICSP(3) + SPI(4) + `RDY`(1) + `TRIG`(1) = **9
  lines** (UART optional).

## 4. Confirmed part facts (from the product brief, DS70005582)

PIC32AK…GC41064 family:
- **Core:** 32-bit, **DC–200 MHz**, single+double-precision **FPU**, DSP (dual 72-bit
  accumulators), 2 KB I-cache. **3.0–3.6 V**, −40…+125 °C, AEC-Q100 Grade 1.
- **This part (PIC32AK3208GC41064):** **32 KB flash**, **8 KB SRAM** (Digikey: 8K×8),
  **64-pin** (TQFP `-I/PT` / QFN `-I/M7`), 49 I/O. Price **$1.91/1, $1.73/25, $1.58/100**
  (Digikey, 498 in stock, 7-wk factory lead). *LCSC/JLCPCB availability still TBD.*
- **ADC:** **two 12-bit ADCs, up to 40 Msps**, up to 22 analog input pins, 20 setting
  channels (single-ended or differential), oversampling / integration / window /
  single modes, per-channel digital comparator, 2nd-order filter accumulators on 3
  channels, band-gap ref + temp sensor.
- **Op-amps:** **three rail-to-rail 100 MHz** op-amps, **100 V/µs** slew, **1 mV**
  typ offset.
- **Comparators/DACs:** three 5 ns comparators with **12-bit PDM DACs** (slope comp,
  one output buffer).
- **Current sources:** four 10 µA constant + four programmable.
- **HS-PWM:** four generators (8 outputs), **2.5 ns** resolution, ADC-trigger.
- **Comms:** 3× SPI (**up to 40 Mbps**, 16-B FIFO, I²S), 2× I²C, 3× UART (LIN/DMX/
  ISO7816/IrDA), 2× SENT. **No USB** — the reason to pair with RP2350.
- **Other:** QEI, 4× CLC, PTG (peripheral trigger generator), CRC, ECC flash/RAM,
  2-wire ICSP + JTAG debug.
- **Variants (see §3c):** pin counts **36 / 48 / 64** (VQFN `-…/M7` or TQFP `-…/PT`);
  flash/RAM tiers **`3208`** (32/8), **`6416`** (64/16), **`1216`** (128/16); pins and
  memory are independent axes of the part number. Package bodies ≈ 36-VQFN 5×5,
  48-VQFN 6×6 / 48-TQFP 7×7, 64-VQFN 9×9 / 64-TQFP 10×10 mm.

## 5. Open questions / to verify

- [x] **Price** — Digikey ~$1.6–1.9 (32 KB flash / 8 KB RAM / TQFP-64). Cheap. ✓
- [~] **LCSC stock + JLCPCB assembly (N2)** — checked 2026-09-18: **not found on
      LCSC/JLCPCB** (new part; Digikey has it). ⇒ consigned/"extended" part for JLC
      assembly, or Digikey + hand-place. Main sourcing risk; re-check periodically.
- [ ] **Package/footprint (§3c):** smallest feasible → 48-pin **VQFN ~6×6 mm** (board is
      already QFN-assembled); consider **RP2350A/RP2354A (QFN-60, 7×7)** to shrink the
      MCU + drop the external flash.
- [ ] **Per-line settable gain** (TGC dropped): digipot/MDAC in feedback vs resistor-mux
      steps vs (verify) an internal GSEL op-amp ladder. Confirm the op-amp has an
      internal PGA ladder — if so, zero extra parts.
- [ ] **Op-amp noise / input range** — good enough alone, or add a fixed **LNA** first
      stage for weak 5 V-pulser echoes (§3b)?
- [ ] **Package/pin choice** (§3c): confirm the pin budget → **48-pin** (safe) vs
      **36-pin** (smallest, borderline).
- [ ] **Memory tier** (§3c): `3208` (32 KB/8 KB, 150 µs @ 20 Msps) vs a 16 KB-RAM tier
      (150 µs @ 40 Msps). Flash ~32 KB likely ample; SRAM is the lever.
- [ ] **Who sequences TX** (PIC32A HS-PWM+PTG vs RP2350 PIO) and how coded excitation
      + acquisition stay time-aligned across two chips (drives the `TRIG` line, §3d).
- [ ] **Inter-MCU protocol** (§3d): SPI framing, RP2350-master + PIC `RDY` IRQ, PRF vs
      transfer budget (6–12 KB over 40 Mbps ≈ 1–2.5 ms — fine between pulses).
- [ ] **ICSP-from-RP2350** feasibility (2-wire LVP ICSP timing over PIO, per DS60001145)
      so one USB port programs both; `MCLR` also as the reset line.
- [ ] Net **BOM & board-area** vs baseline — is it actually simpler/cheaper once the
      second MCU is counted?
- [ ] Reconcile with **DP4** ("controller is RP2350") and **DP5** (reuse) — is the
      PIC32A a *peripheral* (baseline unchanged) or a *co-controller* (revisit DP4)?

## 6. Sources

- Microchip product page — PIC32AK3208GC41064:
  https://www.microchip.com/en-us/product/pic32ak3208gc41064
- Family product brief DS70005582 (mirrored in `pdfs/datasheets/`, with `.md` sibling):
  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/ProductBrief/PIC32AK1216GC41064-Family-Product-Brief-DS70005582.pdf
- Variants: Microchip product pages for `…GC41048` (48-pin) / `…GC41036` (36-pin) /
  `…GC41064` (64-pin), and RS/Digikey listings (pin & 32 KB–128 KB flash options).
- Price: Digikey `PIC32AK3208GC41064-I/PT` (2026-09-18).
- PIC32 Flash Programming Specification DS60001145 (for RP2350→PIC ICSP/LVP).
