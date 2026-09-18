# Ultrasound RX gain ICs — LNA + variable-gain (VGA/AFE) survey

Catalog of receive-path gain ICs used in ultrasound, from **single-channel VGAs** to
**8/16-channel integrated AFEs**, to inform the *minus* gain stage (see
[`../options.md`](../options.md) §2 for the minus-specific shortlist and
[`by-ic.md`](by-ic.md) for which surveyed designs use what).

## Integration levels (what "LNA + variable gain" can include)

1. **VGA only** — variable-gain amp, no LNA (add your own low-noise first stage). Cheap,
   flexible. e.g. AD603, VCA810.
2. **LNA + VGA (+ post-amp)** — the classic ultrasound front-end block. e.g. AD8331/2/4,
   AD8338.
3. **Full AFE** = LNA + VGA/PGA + anti-alias filter **+ ADC** (often + CW-Doppler mixer),
   usually 8/16-channel. e.g. AFE5808, AD9276.
4. **Transceiver** = full AFE **+ HV transmit** on one die. e.g. MAX2082.

> **TGC note:** these parts are built for **TGC** (a fast gain ramp within a line).
> *minus dropped TGC* (per-line settable gain only, see `requirements.md` F6/A3) — so
> the gain-control input is just held at a static value per line, and the multi-channel
> AFEs are heavily over-spec for a single channel. They matter here mainly as (a)
> single/dual options and (b) the reference path if minus ever goes multi-channel.

---

## Single-channel

| Part | Vendor | Blocks | Gain range (approx) | BW | Notes |
|------|--------|--------|---------------------|-----|-------|
| **AD8331** | ADI | LNA (~19 dB) + VGA + prog. post-amp | ~48 dB variable (to ~59 dB) | ~120 MHz | Ultrasound-grade; **used by un0rick/pic0rick** (DP5). options.md **G2**, ~$10, in stock. |
| **AD8338** | ADI | LNA + VGA | **0–80 dB** | ~18 MHz | Low-power, cheaper (~$4); WULPUS-PRO. options.md **G1** (often OOS at LCSC). |
| **AD8337** | ADI | VGA (low-cost) | ~24 dB span | ~80 MHz | Small/cheap single VGA; light LNA. |
| **AD8336** | ADI | VGA | ~−14…+46 dB | ~85 MHz | General-purpose VGA. |
| **AD603** | ADI | VGA only | **−11…+31 dB** (linear-in-dB) | 90 MHz | Classic; add an LNA. options.md **G3** (BOM-floor). |
| **VCA810** | TI | VGA only | **±40 dB** (−40…+40) | ~35 MHz | Wideband linear-in-dB VGA; pair with an LNA. |
| **VCA821 / VCA824** | TI | VGA only | ~40 dB | very wide (>200 MHz) | Wideband; overkill BW for 3–4 MHz. |
| *(non-US PGAs)* | — | digital PGA | steps | lower | LTC6910/6911, MCP6S2x, **LMH6401** (digital VGA) — cheap, but not ultrasound-optimised. |

## Dual-channel

| Part | Vendor | Blocks | Notes |
|------|--------|--------|-------|
| **AD8332** | ADI | 2× (LNA + VGA + post-amp) | Dual AD8331; very common in 2-ch/paired TX-RX designs. |
| **VCA2612/2613/2614/2616/2617** | TI (Burr-Brown) | 2× (LNA + VGA) | Legacy ultrasound dual LNA+VGA; different noise/gain grades. |
| **LMH6521** | TI | 2× digitally-controlled VGA (DVGA) | Step gain set over SPI; RF/IF, usable for RX. |

## Quad-channel

| Part | Vendor | Blocks | Notes |
|------|--------|--------|-------|
| **AD8334 / AD8335** | ADI | 4× (LNA + VGA) | Quad ultrasound front-end (8335 = lower power variant). |
| **LMH6522** | TI | 4× DVGA | Digitally-set quad VGA. |
| **AFE5401** | TI | 4× (LNA + PGA) **+ 12-bit ADC** | 4-ch AFE with ADC (automotive/industrial ultrasound). |

## Octal (8-channel)

**Full AFE (LNA + VGA/PGA + AAF + ADC, usually + CW-Doppler mixer):**

| Part | Vendor | ADC | Notes |
|------|--------|-----|-------|
| **AFE5808A** | TI | 12/14-bit, ≤65 MSPS | The classic 8-ch: LNA + VCAT + PGA + LPF + ADC + CW mixer. |
| **AFE5809 / AFE5812 / AFE5816 / AFE5818** | TI | 12/14-bit | Successors — lower noise / more programmability (AFE5818 newest). |
| **AFE58JD18 / AFE58JD48** | TI | 14-bit, JESD204B | Serial-output 8-ch AFEs. |
| **AD9276** | ADI | **12-bit / 80 MSPS** | 8× LNA(15.6/17.9/21.3 dB) + VGA + AAF + ADC + CWD crosspoint; ~0.75–0.98 nV/√Hz. |
| **AD9277** | ADI | **14-bit / 50 MSPS** | Same front-end as AD9276, 14-bit. |
| **AD9278 / AD9279** | ADI | 12-bit | Variants (mixer / integrated CW Doppler). |
| **AD9670 / AD9671** | ADI | 14-bit (AD9671 ≤125 MSPS) | Newer octal AFE, JESD204B. |
| **MAX2082** | ADI (Maxim) | 10-bit | **Transceiver:** HV transmit + 8-ch RX AFE + ADC on one die. |

**Octal VGA/AFE without ADC** (pair with your own ADC — e.g. the PIC32A):

| Part | Vendor | Notes |
|------|--------|-------|
| **VCA5807 / VCA5808** | TI | The AFE58xx **front-end without the on-chip ADC** (LNA+VCAT+PGA+LPF). |
| **VCA8500** | TI | Octal low-power VGA. |
| **VCA8617** | TI | Octal VGA + LPF. |
| **MAX2078 / MAX2079** | ADI (Maxim) | Octal ultrasound AFE (LNA+VGA), CW-Doppler, no ADC. |

## 16-channel

| Part | Vendor | Notes |
|------|--------|-------|
| **AFE5832 / AFE5832LP** | TI | 16-ch LNA + PGA + ADC, **low power** — aimed at portable/handheld/POCUS. |

---

## Pairing a VGA-only part with an LNA (VCA810 / AD603)

**Why an LNA is needed.** A bare VGA sets the noise floor at its own input-noise density,
which is too high for weak echoes: **VCA810 ≈ 2.4 nV/√Hz**, **AD603 ≈ 1.3 nV/√Hz**. So
you put a **low-noise fixed-gain first stage (~15–25 dB, < ~1 nV/√Hz)** ahead of it — the
LNA sets sensitivity; the VGA then does the *variable* part. Chain:

`transducer → T/R protection → LNA (fixed, low-noise) → VGA (VCA810 / AD603) → AAF → ADC`

(VCA810 and AD603 are functionally interchangeable — same −40…+40 / −11…+31 dB
linear-in-dB VGA role; TI positions VCA810 as an AD603 replacement.)

**LNAs commonly used** (low-noise wideband op-amps configured at fixed gain):

| LNA | Vendor | Input noise | GBW / BW | Notes |
|-----|--------|-------------|----------|-------|
| **OPA847** | TI | **0.85 nV/√Hz** | 3.9 GHz GBW | Classic HF LNA; stable at gain ≥ ~12. |
| **LMH6629** | TI | **0.69 nV/√Hz** | ~4 GHz GBW | Lowest-noise; decompensated (min gain ~10). |
| **AD8099** | ADI | 0.95 nV/√Hz | 550 MHz | Low-noise, easy to apply. |
| **ADA4898-1/2** | ADI | 0.9 nV/√Hz | 65 MHz | Good value single/dual LNA. |
| **AD797** | ADI | 0.9 nV/√Hz | 110 MHz GBW | Precision low-noise; ample for 3–4 MHz. |
| **AD8432** | ADI | 0.85 nV/√Hz | ~tens of MHz | **Purpose-built dual ultrasound LNA** — resistor-set gain, active input impedance, **integrated overvoltage/T-R protection**; designed to precede a VGA. |

**Input protection / T-R** (the LNA must survive the TX pulse): back-to-back diode
limiter (e.g. BAV99 to rails), a shunt-diode **T/R switch (MD0100-class)**, or an LNA
with a **built-in clamp** (AD8432, or the AD8331/AD8332 LNA). At the minus HV level
(~5–50 V unipolar) a simple diode clamp or MD0100 suffices (req A2).

**Reference-design reality:** most modern ultrasound front-ends **skip the discrete LNA**
by using a VGA/AFE with an **integrated LNA** — **AD8331/AD8332** (fixed 15.6/17.9/21.3 dB
LNA, 0.74 nV/√Hz; used by un0rick/pic0rick, DP5), **AD8338** (WULPUS-PRO), or the octal
**AFE5808 / AD9276** (0.63–0.98 nV/√Hz internal LNA). The **discrete VGA + separate LNA**
route (VCA810/AD603 + OPA847/AD8099/AD8432…) is the older / more flexible / DIY path —
more parts and layout, but lets you tune the LNA noise and the VGA independently.

## Relevance to *minus* (single-channel, low-cost, no TGC)

- **Best single-channel fits** are already in `options.md`: **AD8331** (proven/in-stock,
  ~$10) or **AD8338** (cheaper/low-power, often OOS). For per-line settable gain, hold
  their gain-control pin at a static voltage (RP2350 PWM+RC, no DAC IC).
- **With the PIC32A concept** ([`../design/pic32/`](../design/pic32/README.md)), a full
  VGA IC may be unnecessary: use the **PIC32A op-amp + a digipot/MDAC** (or a bare
  **VGA-only** part like VCA810 / AD603 + a low-noise LNA — see the pairing section
  above) feeding the PIC's ADC. Or feed an **AD8331/AD8338** straight into the PIC ADC
  and skip the PIC op-amps. If the PIC op-amp's own noise is the limit, the **AD8432**
  (dual ultrasound LNA + protection) is a clean fixed first stage (req A3a).
- **Octal AFEs (AFE5808 / AD9276-family)** are **over-spec and expensive** ($10–40+) for
  one channel — but they're **the** reference if minus ever grows to multi-channel /
  B-mode. Handy detail: TI's **VCA5807/VCA8500** and **MAX2078/79** give the LNA+VGA
  **without an ADC**, so they could pair with an external digitiser (though the PIC32A
  has only 2 ADC cores, not 8 — true 8-ch needs the AFE's own ADC).
- **Availability/cost caveat (N2/B2):** most ultrasound AFE/VGA parts are pricey and
  frequently **not LCSC-stocked** — verify on LCSC before choosing (see
  [`memory/0006-pricing-basis`](memory/0006-pricing-basis.md)). This is why the
  low-cost minus baseline leans on AD8331/AD8338 or the PIC32A-op-amp path, not an AFE.

## Prices (LCSC, checked 2026-09-18)

Qty ~50 basis (workshop batch, [[0006-pricing-basis]]); "1-off" = qty 1. Stock is
volatile — re-check before ordering.

| Part | Role | LCSC | ~qty50 | 1-off | Stock |
|------|------|------|--------|-------|-------|
| **AD8331ARQZ** | 1-ch LNA+VGA | C203731 | **$14.23** (56+) | $18.01 | 48 ✓ |
| AD8332ACPZ-R7 | 2-ch LNA+VGA | C578698 | ~$16 (tiers n/a) | $16.44 | **OOS** |
| AD8338ACPZ-RL | 1-ch LNA+VGA | C652715 | **$7.72** (30+) / $7.04 (100+) | $9.84 | **OOS** (both reels) |
| **AD603ARZ-REEL** | VGA-only | C578331 | **$8.92** (50+) | $12.31 | 2459 ✓ |
| VCA810 | VGA-only | — | — | — | **not on LCSC** → Digikey |
| VCA820IDGSR *(VCA810 fam.)* | VGA-only | C702457 | $14.49 (30+) | $16.51 | 7 (low) |
| **OPA847IDBVR** | LNA | C160422 | **$5.06** (50+) | $6.33 | 85 ✓ |
| **LMH6629MFE** | LNA | C206003 | **$4.98** (50+) | $6.56 | 65 ✓ |
| **ADA4898-1YRDZ-R7** | LNA | C207523 | **$5.06** (50+) / $4.16 (100+) | $6.41 | 126 ✓ |
| AD797ARZ | LNA | C50658 | ~$11 | $11.13 | 49 |
| AD8099ACPZ | LNA | *verify* | — | — | LCSC ? / Digikey ~$5–7 |
| AD8432 | dual US LNA | — | — | — | **not on LCSC** → Digikey |
| AFE5808 / AD9276 | 8-ch AFE | — | — | — | **not on LCSC** (Digikey/Mouser ~$25–45, ref only) |

**Read-out:**
- **In-stock, cheap single-channel gain today:** **AD603 (VGA-only, ~$9) + a $5 LNA**
  (ADA4898-1 / LMH6629 / OPA847) ≈ **~$14** for LNA+VGA — comparable to the integrated
  **AD8331 (~$14, in stock)** but with a lower-noise, selectable LNA.
- **AD8338** (the cheap integrated favourite) and **AD8332** (dual) are **OOS at LCSC**.
- **VCA810** and the dedicated **AD8432** LNA and the **octal AFEs** are **not LCSC-
  stocked** → Digikey/Mouser only (matters for the JLCPCB flow, N2).
- **Cheapest LNAs** on LCSC: **LMH6629 (~$5, 0.69 nV/√Hz)** and **ADA4898-1 (~$5,
  0.9 nV/√Hz)** — both in stock; OPA847 (~$5, 0.85) also in stock.

## Sources
- ADI AD927x/AD967x octal ultrasound AFE product family (product highlight).
- TI AFE5808 / AFE5818 product pages; AFE5807 vs VCA5807 (VCA = AFE without ADC).
- TI VCA810 (input noise 2.4 nV/√Hz; positioned as an AD603 replacement); LNA specs
  from OPA847 / LMH6629 / AD8099 / AD797 / ADA4898 / AD8432 datasheets.
- Owner's echomods "Choosing components" bench notes (kelu124.gitbooks.io/echomods).
- Part specs are **approximate — verify against each datasheet + LCSC** before use.
