# EchoLite

**Full name:** EchoLite — lightweight wearable ultrasound system (working name)
**Year:** 2025/2026 (IEEE IUS 2025; cited in IEEE CEEUS 2026 Anatomy slides)
**Origin:** not confirmed (author Lu et al.)
**Status:** closed / not public (hardware not released; paper not yet indexed as of 2026-06-30)
**References:** Lu et al., IEEE IUS 2025 ; Anatomy slides (Leitner & Giordano, CEEUS 2026)
**Repository:** —
**License:** —
**One-line summary:** Lightweight single-channel MCU wearable — 33 mW, 8.7 g (lightest in survey), 11 µm axial resolution at 3 cm.

> ⚠ Almost all fields are unconfirmed — sourced from survey slides, no primary
> hardware documentation. Update when the IEEE IUS 2025 paper is public.

---

## 1. Classification

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | MCU | [S] |
| Intended application | Lightweight wearable monitoring (superficial) | [E] |
| Imaging modes | A-mode | [E] |
| Single-channel only? | yes (1 channel) | [S] |
| Wireless? | ? | |
| Open source? | no | [S] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | ? | |
| Weight | 8.7 g (lightest in survey) | [S] |
| Volume | ? | |
| Wearable / benchtop | wearable | [S] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | MCU (part not disclosed; MSP430/ARM Cortex-M class) | [E] |
| Core clock | ? | |
| On-board memory | ? | |
| On-board DSP / beamforming | ? | |
| Firmware toolchain | ? | |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | ? | |
| TX voltage | ? (unknown) | [S] |
| HV supply IC / topology | ? | |
| Pulser driver IC | ? | |
| Excitation waveform | ? | |
| Excitation frequency range | ? (higher-freq transducer inferred from 11 µm / 3 cm) | [E] |
| Transmit beamforming | none | [E] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | single-element (higher frequency inferred) | [E] |
| Centre frequency | ? (~5 MHz est. from resolution/depth) | [E] |
| Element count | 1 | [S] |
| Pitch / aperture | — | |
| T/R switch | ? | |
| HV multiplexer | none | [E] |
| Channel scheme | single | [S] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 | [S] |
| Acquisition route | ? | |
| Pre-amplifier | ? | |
| Gain type | ? | |
| Gain range | ? | |
| TGC slope / control | ? | |
| Envelope detection | ? | |
| ADC part | ? (if >8 Msps, distinct from MSP430 class) | [E] |
| ADC sample rate | ? | |
| ADC resolution | ? | |
| ADC integrated vs external | ? | |
| End-to-end −3 dB bandwidth | ? | |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | ? | |
| Wireless throughput | ? | |
| Wired interface | ? | |
| Wired throughput | ? | |
| Host interface / handshake | ? | |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | 3 cm | [S] |
| Axial resolution | 11 µm | [S] |
| Lateral resolution | ? | |
| PRF range | ? | |
| Frame rate (B-mode) | — | |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | ? | |
| Total system power | 33 mW | [S] |
| Battery | ? | |
| Battery life | ? | |

## 10. Notes / constraints / relevance to *minus*

- Sits between WULPUS (22 mW, 5.5 µm, 4 cm) and USoP (614 mW, 102 µm, 6 cm).
  Notable mainly for weight (8.7 g) at comparable power.
- Shallower 3 cm depth + 11 µm resolution hints at a higher-frequency transducer
  and therefore an ADC above the MSP430's 8 Msps — unconfirmed.
- For *minus*: a data point on how light a single-channel MCU wearable can get;
  low information value until the paper is public.
