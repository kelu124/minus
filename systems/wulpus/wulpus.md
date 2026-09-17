# WULPUS

**Full name:** WULPUS — Wearable Ultra-Low-Power Ultrasound probe
**Year:** 2022
**Origin:** ETH Zurich, IIS / PULP group
**Status:** open-source (Gerbers + firmware; schematic editing needs Altium)
**References:** github.com/pulp-bio/wulpus ; 7 application papers
**Repository:** https://github.com/pulp-bio/wulpus
**License:** open hardware (Altium source) / open firmware
**One-line summary:** Original open-source wearable A-mode ultrasound probe — 22 mW, BLE, multi-day body-worn physiological monitoring.

---

## 1. Classification

**Piezo 1–5 MHz:** Partial (1–3 MHz only; ~1.4 MHz BW ceiling) · **ADC sampling:** 8 MSps (12-bit, integrated MSP430)

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | MCU | [D] |
| Intended application | Wearable physiological monitoring (muscle, carotid) | [P] |
| Imaging modes | A-mode | [P] |
| Single-channel only? | no — 8 channels, but time-multiplexed (1 active at a time) | [D] |
| Wireless? | BLE | [D] |
| Open source? | yes | [D] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | 46 × 25 mm | [S] |
| Weight | ~13 g | [S] |
| Volume | ? | |
| Wearable / benchtop | wearable | [P] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | MSP430FR5043 (TI) — USS_A ultrasonic peripheral | [D] |
| Core clock | 16 MHz | [D] |
| On-board memory | 64 KB FRAM | [D] |
| On-board DSP / beamforming | envelope in firmware (host-side processing) | [P] |
| Firmware toolchain | TI Code Composer / MSP430 | [D] |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | unipolar | [D] |
| TX voltage | +15 V | [D] |
| HV supply IC / topology | MOSFET + boost converter | [D] |
| Pulser driver IC | MOSFET pulser (see HV survey) | [S] |
| Excitation waveform | pulse (PPG-configured) | [D] |
| Excitation frequency range | 0–5 MHz (USS_A); ~3 MHz practical ceiling | [D] |
| Transmit beamforming | none (single phase) | [P] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | single-element (1–3 MHz) | [D] |
| Centre frequency | 1–3 MHz | [D] |
| Element count | 1 active | [D] |
| Pitch / aperture | — | |
| T/R switch | MD0101 (active, ~100 ns recovery) | [S] |
| HV multiplexer | 8-channel (chip provisionally HV2707T-C/R8X) | [E] |
| Channel scheme | time-multiplexed (8 sites, 1 active) | [D] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 (of 8 muxed) | [D] |
| Acquisition route | raw RF | [P] |
| Pre-amplifier | OPA836 (~6 dB buffer) | [S] |
| Gain type | fixed PGA (MSP430 USS_A) — no TGC | [P] |
| Gain range | ? | |
| TGC slope / control | none | [P] |
| Envelope detection | digital (firmware/host) | [P] |
| ADC part | integrated in MSP430FR5043 (SDHS sigma-delta) | [D] |
| ADC sample rate | 8 Msps | [D] |
| ADC resolution | 12-bit | [D] |
| ADC integrated vs external | integrated | [D] |
| End-to-end −3 dB bandwidth | ~1.4 MHz (CIC decimation limit) | [E] |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | BLE (nRF52832) | [D] |
| Wireless throughput | 320 kbps effective | [P] |
| Wired interface | — | |
| Wired throughput | — | |
| Host interface / handshake | via BLE; FRAM buffers between acquisitions | [P] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | 4 cm | [S] |
| Axial resolution | 5.5 µm displacement precision (A-mode) | [S] |
| Lateral resolution | — | |
| PRF range | ? | |
| Frame rate (B-mode) | — (no B-mode) | |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | ~10 mW (est.) | [E] |
| Total system power | 22 mW | [P] |
| Battery | LiPo | [P] |
| Battery life | multi-day | [P] |

## 10. Notes / constraints / relevance to *minus*

- The low-power reference point: 22 mW via co-design (integrated ADC, LPM4 + RTC
  at 450 nA between acquisitions, FRAM/DMA capture, power-gated subsystems).
- Key ceiling: 8 Msps integrated ADC → ~1.4 MHz end-to-end BW; caps usable
  transducers at ≤3 MHz. Fixed gain (no TGC) limits general imaging.
- For *minus* (minimal, single-channel, cheap): the closest "single-channel A-mode
  at minimal power" template, but Altium and MSP430 USS_A are the accessibility
  frictions to weigh against an RP2040/pic0rick-style path.
