# PuLsE

**Full name:** PuLsE — Accurate and Robust Ultrasound-based Continuous Heart-Rate Monitoring on a Wrist-Worn IoT Device
**Year:** 2025
**Origin:** ETH Zurich (Integrated Systems Laboratory; D-ITET) — Giordano, Leitner, Vogt, Benini, Magno
**Status:** closed (hardware not fully published; not open-source)
**References:** IEEE IoT Journal Vol.12 2025, DOI 10.1109/JIOT.2025.3557089 ; arXiv 2410.16219
**Repository:** —
**License:** —
**One-line summary:** Wrist-worn single-element ultrasound heart-rate monitor using analog envelope detection to reach 5.8 mW — the lowest power in the survey.

---

## 1. Classification

**Piezo 1–5 MHz:** Yes (≤10 MHz excitation; ~5 MHz wrist) · **ADC sampling:** ~1–2 MSps (analog-envelope, >5× reduced)

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | MCU (ARM Cortex-M4 class) | [P] |
| Intended application | Wrist heart-rate (radial artery pulsatile flow) | [P] |
| Imaging modes | A-mode (envelope only) | [P] |
| Single-channel only? | yes (1 channel) | [P] |
| Wireless? | not specified | [?] |
| Open source? | no | [P] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | ? | |
| Weight | ? (not reported) | [P] |
| Volume | 12.6 cm³ | [S] |
| Wearable / benchtop | wearable (wrist) | [P] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | ARM Cortex-M4 class MCU (specific part not disclosed) | [P] |
| Core clock | ? | |
| On-board memory | ? | |
| On-board DSP / beamforming | none (envelope done in analog) | [P] |
| Firmware toolchain | ? | |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | ? (est. ±15 V per WULPUS PRO comparison) | [E] |
| TX voltage | <15 V est. | [E] |
| HV supply IC / topology | custom low-power pulser | [P] |
| Pulser driver IC | ? | |
| Excitation waveform | single-cycle | [P] |
| Excitation frequency range | ? (compatible with 5–10 mm radial depth) | [P] |
| Transmit beamforming | none | [P] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | single-element focused | [P] |
| Centre frequency | ? (~5 MHz est.) | [E] |
| Element count | 1 | [P] |
| Pitch / aperture | — | |
| T/R switch | ? | |
| HV multiplexer | none (no mux) | [P] |
| Channel scheme | single | [P] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 | [P] |
| Acquisition route | analog envelope (before ADC) | [P] |
| Pre-amplifier | ? | |
| Gain type | ? (no TGC) | [P] |
| Gain range | ? | |
| TGC slope / control | none | [P] |
| Envelope detection | analog (custom circuit) — reduces ADC BW >5× | [P] |
| ADC part | integrated in MCU | [P] |
| ADC sample rate | low (1–2 Msps est., >5× reduction vs raw RF) | [E] |
| ADC resolution | ? | |
| ADC integrated vs external | integrated | [P] |
| End-to-end −3 dB bandwidth | ? | |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | not specified | [?] |
| Wireless throughput | ? | |
| Wired interface | ? | |
| Wired throughput | ? | |
| Host interface / handshake | ? | |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | ~5–10 mm (radial artery) | [P] |
| Axial resolution | — | |
| Lateral resolution | — | |
| PRF range | low (heart-rate) | [E] |
| Frame rate (B-mode) | — | |
| SNR / SINAD | ? |  |
| Accuracy vs ECG | r=0.99, mean error 0.69 ± 1.99 bpm | [P] |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | ? | |
| Total system power | 5.8 mW | [S] |
| Battery | ? | |
| Battery life | ? | |

## 10. Notes / constraints / relevance to *minus*

- Lowest power of the survey (5.8 mW) via analog envelope + shallow target + single
  element + no mux. Envelope discards phase (no Doppler/matched filtering).
- Architecturally the "analog envelope" branch — same idea as TUSS4470 industrial
  parts, tuned for wearable IoT.
- For *minus*: the extreme minimal end. If the goal accepts envelope-only output,
  an analog-envelope front-end is the cheapest, lowest-power route; if raw RF is
  required, this path is ruled out.
