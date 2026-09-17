# SENS-U

**Full name:** SENS-U Bladder Sensor — now **TENA SmartCare Bladder Sensor**
**Year:** 2021 (SENS-U orig. Novioscan; now TENA/Essity)
**Origin:** TENA (Essity); originally Novioscan (NL)
**Status:** commercial (closed hardware)
**References:** Weik et al. 2026 (IEEE RBME) Table I, ref [36]; SIG-WUS OXP `sense-u`; bladdersensor.tena.com
**Repository:** —
**License:** — (commercial)
**One-line summary:** Fully wearable, closed, non-imaging A-mode pediatric bladder-fullness monitor (enuresis/incontinence) — 4-element transducer muxed to one RX channel, Bluetooth alert to a phone.

> Cited by the Weik review as the archetypal *closed* wearable non-imaging system:
> mature and market-available, but not usable as a generic platform.

---

## 1. Classification

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | integrated (closed) | [P] |
| Intended application | Pediatric bladder-fullness monitoring (enuresis/incontinence) | [P] |
| Imaging modes | A-mode (wall tracking / fill level) | [P] |
| Single-channel only? | no — 4 elements, muxed to 1 RX | [P] |
| Wireless? | Bluetooth | [P] |
| Open source? | no | [P] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | lower-abdomen adhesive patch | [P] |
| Weight | 55 g (incl. battery) | [P] |
| Volume | ? | |
| Wearable / benchtop | wearable | [P] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | integrated controller (not disclosed) | [P] |
| Core clock | ? | |
| On-board memory | ? | |
| On-board DSP / beamforming | wall-position tracking over time | [P] |
| Firmware toolchain | ? | |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | ? | |
| TX voltage | ? | |
| HV supply IC / topology | ? | |
| Pulser driver IC | ? | |
| Excitation waveform | pulse | [E] |
| Excitation frequency range | ? | |
| Transmit beamforming | none | [E] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | 4-element, integrated | [P] |
| Centre frequency | ? | |
| Element count | 4 | [P] |
| Pitch / aperture | 30° effective field of view | [P] |
| T/R switch | ? | |
| HV multiplexer | 4-to-1 MUX | [P] |
| Channel scheme | time-multiplexed (4→1) | [P] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 (of 4 muxed) | [P] |
| Acquisition route | raw data | [P] |
| Pre-amplifier | ? | |
| Gain type | ? | |
| Gain range | ? | |
| TGC slope / control | ? | |
| Envelope detection | ? | |
| ADC part | ? | |
| ADC sample rate | ? | |
| ADC resolution | ? | |
| ADC integrated vs external | integrated | [E] |
| End-to-end −3 dB bandwidth | ? | |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | Bluetooth | [P] |
| Wireless throughput | ? (alerts to phone app) | [P] |
| Wired interface | — | |
| Wired throughput | — | |
| Host interface / handshake | smartphone app; high-fill alerts | [P] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | bladder wall (lower abdomen) | [P] |
| Axial resolution | ? | |
| Lateral resolution | ? | |
| PRF range | ? | |
| Frame rate (B-mode) | — | |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | ? | |
| Total system power | ? | |
| Battery | integrated | [P] |
| Battery life | ≥36 h continuous | [P] |

## 10. Notes / constraints / relevance to *minus*

- A proof that a **closed, fully-wearable, few-element A-mode** product ships and
  works (55 g, 36 h, BT). Non-imaging bladder monitoring is a validated use case.
- Closed design ⇒ not a platform to build on; relevant only as a target-form
  reference. See [[wulpus]] (open counterpart), [[literature]].
