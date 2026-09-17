# WULPUS PRO

**Full name:** WULPUS PRO — Multi-mode Ultra-Low-Power Wearable Ultrasound and Array Imaging with CMUT Support
**Year:** 2026
**Origin:** ETH Zurich PULP group / University of British Columbia
**Status:** open-source
**References:** arXiv 2607.12137v1 (Vostrikov, Villani, Hirschi, Lu, Welsch, Angerer, Cretu, Rohling, Cossettini, Benini)
**Repository:** https://github.com/pulp-bio/wulpus-pro
**Related:** the open BioGAP-shield productization is [[biogap-wulpus-pro]] (repo `pulp-bio/sensei-us-shield`)
**License:** open hardware/software
**One-line summary:** Second-gen WULPUS adding analog TGC, CMUT support, 16-channel B-mode synthetic aperture — same MSP430 core, 5 g.

---

## 1. Classification

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | MCU | [P] |
| Intended application | Wearable A/B-mode monitoring (muscle, bladder, cardiovascular) | [P] |
| Imaging modes | A-mode RF, A-mode envelope, B-mode (SA) | [P] |
| Single-channel only? | no — 16 channels (time-multiplexed) | [P] |
| Wireless? | BLE (nRF52832) + optional Wi-Fi (ESP32-C6) | [P] |
| Open source? | yes | [P] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | 39 × 21 × 6 mm | [P] |
| Weight | 5 g | [P] |
| Volume | ? | |
| Wearable / benchtop | wearable | [P] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | MSP430FR5043 (TI) — USS_A | [P] |
| Core clock | 16 MHz | [D] |
| On-board memory | FRAM (MSP430) | [P] |
| On-board DSP / beamforming | DAS + coherence-factor weighting (B-mode, host) | [P] |
| Firmware toolchain | MSP430 | [D] |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | unipolar (0–30 V); −30 V rail for CMUT bias | [P] |
| TX voltage | 0–30 V (CMUT: up to ±30 V) | [P] |
| HV supply IC / topology | LT3463 dual DC-DC buck-boost (+30 V / −30 V) | [P] |
| Pulser driver IC | IXDD604 (MOSFET gate driver, tri-state) | [P] |
| Excitation waveform | PPG register-configured pulse | [P] |
| Excitation frequency range | 0.2–10 MHz | [P] |
| Transmit beamforming | plane-wave TX (synthetic aperture on RX) | [P] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | linear array (Vermon LA-2.25-32 / LA-5-32); 16-ch polyCMUT | [P] |
| Centre frequency | 2.25 / 5 MHz arrays; CMUT 3 MHz nominal (1.46 MHz measured) | [P] |
| Element count | 32 (array) / 16 (CMUT) | [P] |
| Pitch / aperture | 0.6 mm pitch, 19.2 mm aperture (LA-2.25-32) | [P] |
| T/R switch | MD0100 (passive limiter, ±2.5 V clamp, ~5 µs recovery) | [P] |
| HV multiplexer | HV2707 (16-ch, ±100 V, SPI) | [P] |
| Channel scheme | time-multiplexed (16) | [P] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 16 (time-multiplexed through one chain) | [P] |
| Acquisition route | raw RF or analog envelope (selectable) | [P] |
| Pre-amplifier | OPA836 (6 dB) | [P] |
| Gain type | VGA + analog TGC | [P] |
| Gain range | up to 70 dB total (OPA836 + AD8338) | [P] |
| TGC slope / control | 40 dB slope via RC ramp on AD8338 gain pin | [P] |
| Envelope detection | analog LT5507 (1.5 MHz BW, <2 mW; bypassable) | [P] |
| ADC part | integrated in MSP430FR5043 | [P] |
| ADC sample rate | 8 Msps | [P] |
| ADC resolution | 12-bit | [P] |
| ADC integrated vs external | integrated | [P] |
| End-to-end −3 dB bandwidth | 1.4 MHz (amp chain 305 kHz–10.2 MHz) | [P] |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | BLE (nRF52832) / optional Wi-Fi (ESP32-C6) | [P] |
| Wireless throughput | 320 kbps (BLE) / ~2 Mbps (Wi-Fi) | [P] |
| Wired interface | 4-wire SPI (host front-end) | [P] |
| Wired throughput | SPI @ 8 MHz | [P] |
| Host interface / handshake | data-ready + host-ready handshake; host-agnostic | [P] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | ~3 cm (B-mode demo) | [P] |
| Axial resolution | ~0.7 mm @ 3 cm (B-mode, 2.25 MHz) | [P] |
| Lateral resolution | 2.0–2.3 mm | [P] |
| PRF range | 1–300 Hz (mode-dependent) | [P] |
| Frame rate (B-mode) | 18.75 Hz (16 el × 300 Hz / 16) | [P] |
| SNR / SINAD | SNR 32 dB @ passband centre; SINAD 41 dB @1 MHz | [P] |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | 35 mW (A-mode) / 58 mW (B-mode) | [P] |
| Total system power | ~47 mW (A-mode + BLE); +314 mW with Wi-Fi | [P] |
| Battery | 300 mAh LiPo | [P] |
| Battery life | 1–2 days BLE @50 Hz; >3 h Wi-Fi @300 Hz | [P] |

## 10. Notes / constraints / relevance to *minus*

- Validates AD8338 as the low-power TGC VGA and LT3463 as a compact dual ±30 V
  supply — both candidate parts for a minimal analog chain.
- Same 8 Msps ADC ceiling as WULPUS (1.4 MHz BW) — proposed fix STM32L412 at
  12.3 Msps (~6 MHz BW). Passive MD0100 T/R gives a ~3.75 mm near-field dead zone.
- For *minus*: shows how much capability (TGC, B-mode, CMUT) can ride on the same
  cheap MCU core; the ADC bandwidth is the wall to design around.
