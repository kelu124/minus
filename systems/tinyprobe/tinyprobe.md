# TinyProbe

**Full name:** TinyProbe — A Wearable 32-Channel Multimodal Wireless Ultrasound Probe
**Year:** 2025
**Origin:** ETH Zurich, IIS / PULP group (Vostrikov, Tille, et al.)
**Status:** partially open (github.com/pulp-bio/TinyProbe)
**References:** IEEE TUFFC Vol.72(1) pp.64–76, Jan 2025, DOI 10.1109/TUFFC.2024.3496474
**Repository:** https://github.com/pulp-bio/TinyProbe
**License:** partial
**One-line summary:** FPGA-based 32-channel wearable probe with transmit beamforming, Wi-Fi, and ML virtual-channel reconstruction — B-mode + Doppler to 15 cm.

---

## 1. Classification

**Piezo 1–5 MHz:** Yes (≤15 MHz; arrays used 2.25/5 MHz-class) · **ADC sampling:** 30 MSps (10-bit, external)

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | FPGA (+ custom mux ASICs) | [P] |
| Intended application | Wearable B-mode imaging + Doppler | [P] |
| Imaging modes | B-mode, high-PRF Doppler | [P] |
| Single-channel only? | no — 32 parallel channels | [P] |
| Wireless? | Wi-Fi | [P] |
| Open source? | partial | [S] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | ? | |
| Weight | 39.9 g | [P] |
| Volume | ? | |
| Wearable / benchtop | wearable | [P] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | FPGA (specific part not disclosed) | [P] |
| Core clock | ? | |
| On-board memory | ? | |
| On-board DSP / beamforming | TX beamforming + ML virtual-channel reconstruction | [P] |
| Firmware toolchain | ? | |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | bipolar (±32 V) | [P] |
| TX voltage | 64 Vpp | [P] |
| HV supply IC / topology | ? | |
| Pulser driver IC | ? | |
| Excitation waveform | pulse | [P] |
| Excitation frequency range | ? | |
| Transmit beamforming | yes — 16 programmable delay profiles | [P] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | linear array | [P] |
| Centre frequency | ? | |
| Element count | 32 | [P] |
| Pitch / aperture | 83.2 mm × 16 mm aperture | [P] |
| T/R switch | ? (custom ASIC) | [P] |
| HV multiplexer | custom ASICs (preamp + mux) | [P] |
| Channel scheme | parallel (32) | [P] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 32 | [P] |
| Acquisition route | raw RF | [P] |
| Pre-amplifier | custom ASIC local preamps | [P] |
| Gain type | programmable (TGC) | [P] |
| Gain range | ? | |
| TGC slope / control | programmable | [P] |
| Envelope detection | digital | [E] |
| ADC part | external high-speed ADC | [P] |
| ADC sample rate | up to 30 Msps | [P] |
| ADC resolution | 10-bit | [P] |
| ADC integrated vs external | external | [P] |
| End-to-end −3 dB bandwidth | ? | |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | Wi-Fi | [P] |
| Wireless throughput | 21.6 Mb/s (UDP) | [P] |
| Wired interface | ? | |
| Wired throughput | ? | |
| Host interface / handshake | ? | |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | 15 cm | [P] |
| Axial resolution | 2 µm | [S] |
| Lateral resolution | ? | |
| PRF range | up to 1400 Hz (Doppler) | [P] |
| Frame rate (B-mode) | 33 Hz | [P] |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | 30.3 mW/channel (normalized); 2 mW/MHz | [S] |
| Total system power | <1 W (32-ch B-mode); <1.3 W (Doppler) | [P] |
| Battery | 500 mAh Li-Po | [P] |
| Battery life | intermittent sessions (not multi-day) | [P] |

## 10. Notes / constraints / relevance to *minus*

- The high-capability end: FPGA + Wi-Fi + TX beamforming + ML reconstruction, at
  ~45× WULPUS power. Establishes the boundary: 32-ch B-mode at wearable power needs
  FPGA-class compute and Wi-Fi bandwidth.
- For *minus*: mostly a counter-example — everything *minus* is trying NOT to be
  (multi-channel, FPGA, heavy, power-hungry). Useful as the upper bound of the
  design space and for its 30 Msps external-ADC data path.
