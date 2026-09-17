# Murgen (echOpen dev-kit)

**Full name:** A low-cost, arduino-like dev-kit for single-element ultrasound imaging
**Year:** 2016 (submitted Nov 2016, rev. Feb 2017)
**Origin:** Luc Jonveaux (kelu124) / echomods, echOpen context
**Status:** open-source (echomods)
**References:** arXiv:1611.10174 ; github.com/kelu124/echomods
**Repository:** https://github.com/kelu124/echomods
**License:** open hardware/software
**One-line summary:** The origin of the un0rick lineage — open, Arduino-like modular building blocks forming a complete single-channel analog front-end, using repurposed medical/mechanical-scanner transducers.

> Earliest, most modular design in the family; the paper publishes the concept and
> module set rather than a single fixed BOM, so many exact parts are per-build.

---

## 1. Classification

**Piezo 1–5 MHz:** Yes (repurposed 2–5 MHz medical/scanner probes) · **ADC sampling:** external, build-dependent

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | MCU/module-based (Arduino-like) + external ADC/host | [P] |
| Intended application | Low-cost single-element imaging for makers/academics | [P] |
| Imaging modes | A-mode (B-mode via mechanical scan) | [E] |
| Single-channel only? | yes (single channel AFE) | [P] |
| Wireless? | none | [E] |
| Open source? | yes | [P] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | modular (stacked shields/modules) | [P] |
| Weight | ? | |
| Volume | ? | |
| Wearable / benchtop | benchtop | [E] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | Arduino-like MCU for control; host PC for capture | [P] |
| Core clock | ? | |
| On-board memory | ? | |
| On-board DSP / beamforming | none (host-side) | [E] |
| Firmware toolchain | Arduino | [P] |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | unipolar (HV pulser module) | [E] |
| TX voltage | ? (HV pulser module) | |
| HV supply IC / topology | dedicated pulser module | [P] |
| Pulser driver IC | ? (MD-class in later boards) | [E] |
| Excitation waveform | pulse | [E] |
| Excitation frequency range | transducer-dependent | |
| Transmit beamforming | none | [E] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | repurposed single-element probes / mechanical scanner heads | [P] |
| Centre frequency | transducer-dependent | |
| Element count | 1 | [P] |
| Pitch / aperture | — | |
| T/R switch | module | [E] |
| HV multiplexer | none | [E] |
| Channel scheme | single | [P] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 | [P] |
| Acquisition route | raw RF | [E] |
| Pre-amplifier | VGA module (AD8331/AD8332-class in the lineage) | [E] |
| Gain type | TGC (analog VGA) | [E] |
| Gain range | ? | |
| TGC slope / control | ? | |
| Envelope detection | digital (host) | [E] |
| ADC part | external (host / Red Pitaya / dedicated module, per build) | [E] |
| ADC sample rate | build-dependent | |
| ADC resolution | build-dependent | |
| ADC integrated vs external | external | [E] |
| End-to-end −3 dB bandwidth | ? | |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | none | [E] |
| Wireless throughput | — | |
| Wired interface | USB / serial to host | [E] |
| Wired throughput | ? | |
| Host interface / handshake | PC-side capture & processing | [P] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | setup-dependent | |
| Axial resolution | transducer-dependent | |
| Lateral resolution | — | |
| PRF range | ? | |
| Frame rate (B-mode) | offline | [E] |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | — | |
| Total system power | ? | |
| Battery | — | |
| Battery life | — | |

## 10. Notes / constraints / relevance to *minus*

- The conceptual root of un0rick → lit3rick → pic0rick: "build a complete
  single-channel AFE from open, cheap, Arduino-like modules." Establishes the
  reuse-repurposed-transducer philosophy that keeps cost down.
- For *minus*: primarily historical/architectural context; the modular AFE
  decomposition (pulser / T-R / VGA-TGC / ADC / host) is a good scaffolding for a
  minimal BOM. See [[un0rick]].
