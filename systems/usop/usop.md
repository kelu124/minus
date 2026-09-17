# USoP

**Full name:** USoP — Ultrasonic System on Patch (fully integrated wearable ultrasound patch)
**Year:** 2023 (Nature Biotech; survey lists 2021/2024 — see note)
**Origin:** UC San Diego, Dept. of Nanoengineering — group of Sheng Xu (Lin, Zhang et al.)
**Status:** closed (no open-source repo; supplementary-level detail only)
**References:** Nature Biotechnology 2023, DOI 10.1038/s41587-023-01800-0
**Repository:** —
**License:** —
**One-line summary:** First cable-free, autonomous wearable ultrasound patch — flexible/stretchable PZT electronics for deep-tissue (6 cm) cardiovascular monitoring in moving subjects.

---

## 1. Classification

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | MCU (custom flexible integrated electronics) | [P] |
| Intended application | Continuous cardiovascular monitoring (central BP, HR, CO) | [P] |
| Imaging modes | A-mode | [P] |
| Single-channel only? | yes (single-element focused) | [P] |
| Wireless? | Bluetooth | [P] |
| Open source? | no | [P] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | skin patch | [P] |
| Weight | 16.2 g | [S] |
| Volume | ? | |
| Wearable / benchtop | wearable (conformable skin patch) | [P] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | onboard MCU with ADCs (part not published) | [P] |
| Core clock | ? | |
| On-board memory | ? | |
| On-board DSP / beamforming | on-patch acquisition; host-side ML tracking | [P] |
| Firmware toolchain | ? | |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | ? | |
| TX voltage | ~10–30 V | [S] |
| HV supply IC / topology | ? | |
| Pulser driver IC | ? | |
| Excitation waveform | pulse | [E] |
| Excitation frequency range | ~3–5 MHz (est., not disclosed) | [E] |
| Transmit beamforming | none | [E] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | flexible PZT-5H, serpentine Cu/PI electrodes | [P] |
| Centre frequency | ~3–5 MHz est. | [E] |
| Element count | 1 (single-element focused) | [P] |
| Pitch / aperture | — | |
| T/R switch | ? | |
| HV multiplexer | ? | |
| Channel scheme | single | [P] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 | [P] |
| Acquisition route | raw RF (host-side ML processing) | [P] |
| Pre-amplifier | ? | |
| Gain type | ? | |
| Gain range | ? | |
| TGC slope / control | ? | |
| Envelope detection | digital (host) | [E] |
| ADC part | integrated in MCU | [P] |
| ADC sample rate | ? | |
| ADC resolution | ? | |
| ADC integrated vs external | integrated | [P] |
| End-to-end −3 dB bandwidth | ? | |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | Bluetooth (spec not disclosed) | [P] |
| Wireless throughput | ? | |
| Wired interface | — (cable-free) | [P] |
| Wired throughput | — | |
| Host interface / handshake | ? | |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | ~6 cm | [P] |
| Axial resolution | 102.3 µm | [S] |
| Lateral resolution | ? | |
| PRF range | ? | |
| Frame rate (B-mode) | — | |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | ? | |
| Total system power | 614 mW (continuous) | [S] |
| Battery | onboard Li-ion | [P] |
| Battery life | ~12 h continuous | [P] |

## 10. Notes / constraints / relevance to *minus*

- Optimizes a different axis: mechanical conformability (stretchable patch) over
  power efficiency (614 mW, 28× WULPUS). Resolution traded for flexibility (102 µm).
- Date note: survey tags vary (2021/2024); Nature Biotech online May 2023, with a
  2024 BP-validation follow-on.
- For *minus*: mostly orthogonal (flexible patch ≠ rigid cheap PCB), but validates
  that single-element A-mode deep-tissue monitoring is clinically meaningful.
