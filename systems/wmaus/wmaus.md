# WMAUS

**Full name:** WMAUS — Wearable Multichannel A-mode UltraSound (wristband)
**Year:** ~2018–2020 (research; later commercialized)
**Origin:** research group behind the WULPUS/HMI line (see Weik et al.)
**Status:** open research → later commercialized; API available
**References:** Weik et al. 2026 (IEEE RBME) Table I, ref [81]; related [93–95, 99–101]
**Repository:** — (API; commercialized variant [101])
**License:** ?
**One-line summary:** 8-element A-mode wristband for hand-gesture / HMI tracking — dsPIC33 DSP, 8→1 mux at 40 MS/s, streamed raw over BT/Ethernet/Wi-Fi. The research ancestor of the WULPUS HMI line.

---

## 1. Classification

**Piezo 1–5 MHz:** Yes (5 MHz transducer, 77% BW) · **ADC sampling:** 20 MSps (external)

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | MCU/DSP (dsPIC33) | [P] |
| Intended application | Hand-gesture tracking / HMI; sEMG fusion | [P] |
| Imaging modes | A-mode | [P] |
| Single-channel only? | no — 8 elements, TDM to 1 RX | [P] |
| Wireless? | BT / Wi-Fi (also Ethernet) | [P] |
| Open source? | partial (docs/API; commercial variant) | [P] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | 132 × 90 × 30 mm (wristband) | [P] |
| Weight | 190 g | [P] |
| Volume | ? | |
| Wearable / benchtop | wearable (wrist) | [P] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | dsPIC33 (DSP) — sequencer + computation | [P] |
| Core clock | ? | |
| On-board memory | ? | |
| On-board DSP / beamforming | envelope + host/edge feature extraction | [P] |
| Firmware toolchain | ? | |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | bipolar ±15 V | [P] |
| TX voltage | ±15 V | [P] |
| HV supply IC / topology | ? | |
| Pulser driver IC | ? | |
| Excitation waveform | pulse | [E] |
| Excitation frequency range | 5 MHz centre (77% BW) | [P] |
| Transmit beamforming | none | [P] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | 8 individual elements (wristband) | [P] |
| Centre frequency | 5 MHz | [P] |
| Element count | 8 | [P] |
| Pitch / aperture | ? | |
| T/R switch | ? | |
| HV multiplexer | 8-to-1 MUX | [P] |
| Channel scheme | time-division multiplexed (8→1) | [P] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 (of 8 muxed) | [P] |
| Acquisition route | raw data (post-AFE) | [P] |
| Pre-amplifier | AFE (VGA) | [E] |
| Gain type | VGA (post-AFE sampling) | [P] |
| Gain range | ? | |
| TGC slope / control | ? | |
| Envelope detection | digital | [E] |
| ADC part | ? | |
| ADC sample rate | 20 MS/s | [P] |
| ADC resolution | ? | |
| ADC integrated vs external | ? | |
| End-to-end −3 dB bandwidth | ~77% of 5 MHz | [P] |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | BT / Wi-Fi (also Ethernet) | [P] |
| Wireless throughput | raw ~0.1 Mbit/s demonstrated (Ethernet ≤30 Mbit/s) | [P] |
| Wired interface | Ethernet / USB | [P] |
| Wired throughput | Ethernet up to 30 Mbit/s (0.1 used) | [P] |
| Host interface / handshake | data to host PC | [P] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | forearm muscle (A-mode) | [P] |
| Axial resolution | — | |
| Lateral resolution | — | |
| PRF range | 10 Hz frame rate | [P] |
| Frame rate (B-mode) | — | |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | 3.5 W total | [P] |
| Total system power | 3.5 W | [P] |
| Battery | 3000 mAh | [P] |
| Battery life | 10 h | [P] |
| Energy metric | 0.03 Mbit/J | [P] |

## 10. Notes / constraints / relevance to *minus*

- The research **origin of the WULPUS/HMI A-mode line** (8-ch muxed to one RX, raw
  streaming). Heavy (190 g) and power-hungry (3.5 W) vs its successors — shows the
  value of the WULPUS SoC integration.
- **Yin et al.** re-designed WMAUS around an **STM32F7** MCU (4 ch, 1 MHz, ±50 V,
  2.4 MS/s, 85 g, 5 W, 1 Mbit/J) for real-time prosthesis control — same lineage,
  different compute core.
- For *minus*: a cautionary baseline — how NOT to do power/weight for a single-node
  A-mode. See [[wulpus]], [[literature]].
