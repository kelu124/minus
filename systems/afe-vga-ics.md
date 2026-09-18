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

## Relevance to *minus* (single-channel, low-cost, no TGC)

- **Best single-channel fits** are already in `options.md`: **AD8331** (proven/in-stock,
  ~$10) or **AD8338** (cheaper/low-power, often OOS). For per-line settable gain, hold
  their gain-control pin at a static voltage (RP2350 PWM+RC, no DAC IC).
- **With the PIC32A concept** ([`../design/pic32/`](../design/pic32/README.md)), a full
  VGA IC may be unnecessary: use the **PIC32A op-amp + a digipot/MDAC** (or a bare
  **VGA-only** part like VCA810 / AD603 + LNA) feeding the PIC's ADC. Or feed an
  **AD8331/AD8338** straight into the PIC ADC and skip the PIC op-amps.
- **Octal AFEs (AFE5808 / AD9276-family)** are **over-spec and expensive** ($10–40+) for
  one channel — but they're **the** reference if minus ever grows to multi-channel /
  B-mode. Handy detail: TI's **VCA5807/VCA8500** and **MAX2078/79** give the LNA+VGA
  **without an ADC**, so they could pair with an external digitiser (though the PIC32A
  has only 2 ADC cores, not 8 — true 8-ch needs the AFE's own ADC).
- **Availability/cost caveat (N2/B2):** most ultrasound AFE/VGA parts are pricey and
  frequently **not LCSC-stocked** — verify on LCSC before choosing (see
  [`memory/0006-pricing-basis`](memory/0006-pricing-basis.md)). This is why the
  low-cost minus baseline leans on AD8331/AD8338 or the PIC32A-op-amp path, not an AFE.

## Sources
- ADI AD927x/AD967x octal ultrasound AFE product family (product highlight).
- TI AFE5808 / AFE5818 product pages; AFE5807 vs VCA5807 (VCA = AFE without ADC).
- Owner's echomods "Choosing components" bench notes (kelu124.gitbooks.io/echomods).
- Part specs are **approximate — verify against each datasheet + LCSC** before use.
