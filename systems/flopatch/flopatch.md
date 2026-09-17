# Flopatch

**Full name:** FloPatch — wearable continuous-wave Doppler blood-flow patch
**Year:** ~2023 (commercial; Flosonics Medical)
**Origin:** Flosonics Medical (commercial)
**Status:** commercial (closed); TRL 8 per Weik et al.
**References:** Weik et al. 2026 (IEEE RBME) Table I, ref [35]; refs [47,111,112]
**Repository:** —
**License:** — (commercial)
**One-line summary:** Wearable continuous-wave Doppler patch for real-time carotid blood-flow velocity — 2-element integrated transducer (separate TX/RX), analog homodyne demodulation to an audio-band signal, Bluetooth.

> The archetype **non-pulse-echo** wearable: CW Doppler, not imaging. Very low data
> rate (audio band) — a distinct minimal architecture worth contrasting with A-mode.

---

## 1. Classification

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | integrated (closed), CW Doppler | [P] |
| Intended application | Continuous carotid blood-flow velocity | [P] |
| Imaging modes | Continuous-wave Doppler (non-imaging) | [P] |
| Single-channel only? | no — 2 elements (1 TX + 1 RX), continuous | [P] |
| Wireless? | Bluetooth | [P] |
| Open source? | no | [P] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | 54 × 35 × 18 mm | [P] |
| Weight | 22 g | [P] |
| Volume | ? | |
| Wearable / benchtop | wearable (neck patch) | [P] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | integrated (not disclosed) | [P] |
| Core clock | ? | |
| On-board memory | ? | |
| On-board DSP / beamforming | homodyne demod → audio-band Doppler | [P] |
| Firmware toolchain | ? | |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | continuous wave (not pulsed) | [P] |
| TX voltage | ? | |
| HV supply IC / topology | ? (low, CW) | [E] |
| Pulser driver IC | ? | |
| Excitation waveform | continuous wave, 4 MHz | [P] |
| Excitation frequency range | 4 MHz | [P] |
| Transmit beamforming | none (fixed 60° angle) | [P] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | 2-element integrated, 60° angle (separate TX/RX) | [P] |
| Centre frequency | 4 MHz | [P] |
| Element count | 2 (1 TX, 1 RX) | [P] |
| Pitch / aperture | ~23 mm width FOV | [P] |
| T/R switch | none (separate TX/RX elements) | [P] |
| HV multiplexer | none | [P] |
| Channel scheme | 1 TX + 1 RX (CW) | [P] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 | [P] |
| Acquisition route | analog homodyne demodulation → audio band | [P] |
| Pre-amplifier | ? | |
| Gain type | ? | |
| Gain range | ? | |
| TGC slope / control | — (CW, no depth gating) | [P] |
| Envelope detection | analog demodulation (Doppler audio) | [P] |
| ADC part | low-rate (audio band) | [E] |
| ADC sample rate | audio-rate (kHz) | [E] |
| ADC resolution | ? | |
| ADC integrated vs external | integrated | [E] |
| End-to-end −3 dB bandwidth | audio band (Doppler shift) | [P] |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | Bluetooth | [P] |
| Wireless throughput | low (audio-band Doppler) | [P] |
| Wired interface | — | |
| Wired throughput | — | |
| Host interface / handshake | app / host | [E] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | carotid (fixed 60° insonation) | [P] |
| Axial resolution | — (CW, no range gating) | [P] |
| Lateral resolution | ~23 mm FOV | [P] |
| PRF range | — (continuous) | [P] |
| Frame rate (B-mode) | — | |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | ? | |
| Total system power | ? | |
| Battery | integrated | [P] |
| Battery life | ~180 min | [P] |

## 10. Notes / constraints / relevance to *minus*

- The **continuous-wave Doppler** minimal architecture: two elements, no HV
  pulser, no T/R switch, no range gating — analog homodyne to an audio-band signal
  ⇒ tiny data rate and 22 g. Different information (flow velocity, no depth) from
  pulse-echo A-mode.
- For *minus*: relevant only if the target is flow velocity rather than
  depth/structure. CW trades away ranging for extreme simplicity. See [[literature]]
  ("Non pulse-echo" section), [[pulse]].
