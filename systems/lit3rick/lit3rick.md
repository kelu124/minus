# lit3rick

**Full name:** lit3rick — up5k ultrasound pulse-echo device
**Year:** 2021
**Origin:** Luc Jonveaux (kelu124)
**Status:** open-source (OSHWA FR000006)
**References:** ResearchGate "lit3rick: an up5k ultrasound pulse-echo device" (2021); un0rick.cc
**Repository:** https://github.com/kelu124/lit3rick (see un0rick.cc)
**License:** open hardware / GPLv3
**One-line summary:** Lighter iCE40 UP5K single-channel pulse-echo board — 12-bit ADC, higher-gain AD8332 front-end, external HV modules, dual-SMA for split TX/RX.

> First pass — several fields from the un0rick "next board" notes and survey
> snippets; confirm against the lit3rick repo/paper.

---

## 1. Classification

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | FPGA (iCE40 UP5K) | [D] |
| Intended application | Single-element imaging, NDT, research | [D] |
| Imaging modes | A-mode | [E] |
| Single-channel only? | yes (dual-SMA option to split TX/RX for dual-element) | [D] |
| Wireless? | none | [E] |
| Open source? | yes | [D] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | ? (smaller/lighter than un0rick) | [S] |
| Weight | ? | |
| Volume | ? | |
| Wearable / benchtop | benchtop | [E] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | Lattice iCE40 UP5K (up5k) | [D] |
| Core clock | ? | |
| On-board memory | UP5K SPRAM (128 KB) | [E] |
| On-board DSP / beamforming | none (host-side) | [E] |
| Firmware toolchain | IceStorm/iceprog (open) | [E] |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | unipolar (HV pulse) | [E] |
| TX voltage | external HV modules | [S] |
| HV supply IC / topology | external HV module | [S] |
| Pulser driver IC | ? (MD-class, cf. un0rick) | [E] |
| Excitation waveform | pulse | [E] |
| Excitation frequency range | transducer-dependent | |
| Transmit beamforming | none | [E] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | single-element piezo | [D] |
| Centre frequency | transducer-dependent | |
| Element count | 1 (dual-element via double SMA) | [D] |
| Pitch / aperture | — | |
| T/R switch | double SMA to separate TX/RX path | [D] |
| HV multiplexer | none | [E] |
| Channel scheme | single | [D] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 | [D] |
| Acquisition route | raw RF | [E] |
| Pre-amplifier | AD8332 (dual VGA, more gain than un0rick's AD8331) | [D] |
| Gain type | TGC (analog VGA, DAC-driven) | [D] |
| Gain range | AD8332 range (higher than AD8331) | [D] |
| TGC slope / control | DAC-driven ramp (cf. un0rick) | [E] |
| Envelope detection | digital (host) | [E] |
| ADC part | 12-bit ADC (external) | [D] |
| ADC sample rate | ? (≤65 Msps est.) | [E] |
| ADC resolution | 12-bit (vs 10-bit on un0rick) | [D] |
| ADC integrated vs external | external | [D] |
| End-to-end −3 dB bandwidth | ? | |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | none | [E] |
| Wireless throughput | — | |
| Wired interface | SPI (USB / Raspberry Pi) | [E] |
| Wired throughput | ? | |
| Host interface / handshake | PMOD-compliant headers | [D] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | transducer/setup-dependent | |
| Axial resolution | transducer-dependent (12-bit ADC helps dynamic range) | [E] |
| Lateral resolution | — | |
| PRF range | programmable | [E] |
| Frame rate (B-mode) | offline | [E] |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | — | |
| Total system power | ? (lower than un0rick — up5k is low-power) | [E] |
| Battery | — | |
| Battery life | — | |

## 10. Notes / constraints / relevance to *minus*

- The "lighter" iteration in the un0rick family: UP5K (low-power FPGA) + 12-bit ADC
  + AD8332 (more gain) + external HV modules + split TX/RX SMA.
- For *minus*: the most directly comparable "minimal single-channel" open design;
  its UP5K + external-HV modularity is a template for trimming cost. Confirm exact
  ADC part, HV module, and power against the repo. See [[un0rick]], [[pic0rick]].
