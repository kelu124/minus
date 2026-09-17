# BioGAP WULPUS-pro

**Full name:** BioGAP WULPUS-pro — 16-channel ultrasound front-end shield for the BioGAP-Ultra edge-AI platform
**Year:** 2026
**Origin:** ETH Zürich, Integrated Systems Laboratory (IIS) / PULP group
**Status:** open-source (Solderpad v0.51 HW; BSD/Apache-2.0 FW; Apache-2.0 host SW)
**References:** SIG-WUS OXP `biogap-wulpus-pro` (verified 2026-09-14); successor to WULPUS / WULPUS PRO
**Repository:** https://github.com/pulp-bio/sensei-us-shield (host SW: https://github.com/pulp-bio/biogui)
**License:** Solderpad v0.51 (HW) / BSD + Apache-2.0 (FW) / Apache-2.0 (SW)
**Design files:** `design/biogap-wulpus-pro/` (schematics PDF, assembly PDF, BOM; full Altium source + gerbers upstream)
**One-line summary:** WULPUS-PRO as a compact open shield for the BioGAP-Ultra wearable edge-AI platform — 16-channel time-muxed ultrasound front-end (HV pulse gen + T/R select + programmable RX + MSP430FR5043 controller) with on-device ML and BLE.

> Distinct from the WULPUS PRO *paper* platform ([[wulpus-pro]], arXiv 2607.12137):
> this is the open-hardware **BioGAP shield** productization, aimed at hand-gesture
> HMI and ultrasound–EMG fusion.

---

## 1. Classification

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | MCU (MSP430FR5043 SoC) on BioGAP-Ultra host | [D] |
| Intended application | Hand-gesture HMI, ultrasound–EMG fusion | [D] |
| Imaging modes | A-mode (non-imaging) | [D] |
| Single-channel only? | no — 16 channels (time-multiplexed to 1 RX) | [D] |
| Wireless? | Bluetooth LE | [D] |
| Open source? | yes (HW + FW + host SW) | [D] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | compact BioGAP-compatible shield | [D] |
| Weight | ? | |
| Volume | ? | |
| Wearable / benchtop | wearable (BioGAP-Ultra shield) | [D] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | MSP430FR5043 (TI) SoC — sequencer + on-device ML; on BioGAP-Ultra | [D] |
| Core clock | 16 MHz (MSP430) | [E] |
| On-board memory | FRAM (MSP430) | [E] |
| On-board DSP / beamforming | on-device ML (edge-AI, BioGAP) | [D] |
| Firmware toolchain | MSP430 (BSD/Apache-2.0 firmware) | [D] |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | unipolar (HV pulse gen) | [E] |
| TX voltage | 30 V | [D] |
| HV supply IC / topology | on-shield HV pulse generation | [D] |
| Pulser driver IC | ? (WULPUS-PRO lineage: IXDD604) | [E] |
| Excitation waveform | pulse (register-configured) | [E] |
| Excitation frequency range | up to 10 MHz | [D] |
| Transmit beamforming | none | [E] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | array / multi-element (16 ch) | [D] |
| Centre frequency | ≤10 MHz (application-dependent) | [D] |
| Element count | 16 | [D] |
| Pitch / aperture | ? | |
| T/R switch | on-shield T/R channel selection | [D] |
| HV multiplexer | 16-channel (16-to-1) | [D] |
| Channel scheme | time-multiplexed (16→1) | [D] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 (of 16 muxed) | [D] |
| Acquisition route | raw RF (programmable receive chain) | [D] |
| Pre-amplifier | programmable RX chain (WULPUS-PRO lineage: OPA836 + AD8338) | [E] |
| Gain type | VGA / TGC (programmable) | [E] |
| Gain range | ? | |
| TGC slope / control | ? | |
| Envelope detection | digital / host | [E] |
| ADC part | integrated in MSP430FR5043 | [D] |
| ADC sample rate | 8 MS/s | [D] |
| ADC resolution | 12-bit | [E] |
| ADC integrated vs external | integrated | [D] |
| End-to-end −3 dB bandwidth | ~1.4 MHz (MSP430 ceiling) | [E] |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | Bluetooth LE | [D] |
| Wireless throughput | raw, 1.4 Mbit/s | [D] |
| Wired interface | BioGAP host bus | [E] |
| Wired throughput | ? | |
| Host interface / handshake | BioGAP-Ultra; host SW `biogui` | [D] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | forearm muscle (A-mode) | [E] |
| Axial resolution | — | |
| Lateral resolution | — | |
| PRF range | 100 Hz frame rate | [D] |
| Frame rate (B-mode) | — | |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | ? (WULPUS-class, tens of mW) | [E] |
| Total system power | ? | |
| Battery | BioGAP-Ultra battery | [E] |
| Battery life | ? | |

## 10. Notes / constraints / relevance to *minus*

- The **open-hardware** (Solderpad) realization of the WULPUS-PRO front-end as a
  BioGAP-Ultra shield: HV pulse gen + 16-ch T/R select + programmable RX +
  MSP430FR5043, BLE, on-device ML. Repo `pulp-bio/sensei-us-shield` has schematics,
  gerbers, BOM.
- Same MSP430 8 MS/s ceiling (~1.4 MHz BW) as the WULPUS line.
- For *minus*: a fully open, documented multi-channel wearable A-mode front-end to
  mine for parts and layout — complements [[wulpus-pro]] (the paper) and [[iup]].
