# MoUsE

**Full name:** MoUsE — open POCUS-style modular ultrasound platform
**Year:** ~2023 (research)
**Origin:** research (see Weik et al. Table I, ref [108])
**Status:** open platform (POCUS-style; access n/a in Table I)
**References:** Weik et al. 2026 (IEEE RBME) Table I, ref [108]
**Repository:** ? (referenced as an open POCUS platform)
**License:** ?
**One-line summary:** 32-channel ZYNQ-7 FPGA imaging platform with transmit beamforming (0.01–10 MHz, ≤±100 V), raw-data streaming at 500 Mbit/s — a benchtop-class open research platform, at the upper edge of this survey's scope.

> 32 channels = the in-scope ceiling (avoid 64+). Included as the "full imaging
> platform" reference against which minimal single-channel designs are contrasted.

---

## 1. Classification

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | FPGA (Xilinx ZYNQ-7) | [P] |
| Intended application | Bladder, wrist/hand tracking, prosthetic control | [P] |
| Imaging modes | B-mode imaging (beamformed) | [P] |
| Single-channel only? | no — 32 parallel channels | [P] |
| Wireless? | none (raw data out) | [P] |
| Open source? | open platform (access n/a) | [P] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | 184 × 123 × 33 mm | [P] |
| Weight | 610 g | [P] |
| Volume | ? | |
| Wearable / benchtop | benchtop | [P] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | ZYNQ-7 (FPGA + ARM SoC) — sequencer + computation | [P] |
| Core clock | ? | |
| On-board memory | ? | |
| On-board DSP / beamforming | TX beamforming; on-board compute | [P] |
| Firmware toolchain | ? | |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | bipolar, up to ±100 V | [P] |
| TX voltage | ≤±100 V | [P] |
| HV supply IC / topology | ? | |
| Pulser driver IC | ? | |
| Excitation waveform | pulse (0.01–10 MHz) | [P] |
| Excitation frequency range | 0.01–10 MHz | [P] |
| Transmit beamforming | yes (bf) | [P] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | 32-channel array | [P] |
| Centre frequency | 0.01–10 MHz range | [P] |
| Element count | 32 | [P] |
| Pitch / aperture | ? | |
| T/R switch | ? | |
| HV multiplexer | ? | |
| Channel scheme | parallel (32) | [P] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 32 | [P] |
| Acquisition route | raw data | [P] |
| Pre-amplifier | AFE | [E] |
| Gain type | TGC/VGA | [E] |
| Gain range | ? | |
| TGC slope / control | ? | |
| Envelope detection | digital | [E] |
| ADC part | ? | |
| ADC sample rate | 50 MS/s | [P] |
| ADC resolution | ? | |
| ADC integrated vs external | external | [E] |
| End-to-end −3 dB bandwidth | ? | |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | none | [P] |
| Wireless throughput | — | |
| Wired interface | raw data link | [P] |
| Wired throughput | 500 Mbit/s | [P] |
| Host interface / handshake | host PC | [E] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | application-dependent | |
| Axial resolution | ? | |
| Lateral resolution | ? | |
| PRF range | 23 Hz frame rate | [P] |
| Frame rate (B-mode) | 23 Hz | [P] |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | — | |
| Total system power | 12 W | [P] |
| Battery | — | |
| Battery life | — | |
| Energy metric | 40 Mbit/J | [P] |

## 10. Notes / constraints / relevance to *minus*

- Upper-edge (32-ch) open imaging platform: ZYNQ-7 FPGA, TX beamforming, ±100 V,
  500 Mbit/s raw — 610 g, 12 W. Benchtop, not wearable.
- For *minus*: a counter-example / full-capability anchor, like [[tinyprobe]].
  Not a build target; useful for its beamforming + high-voltage architecture.
