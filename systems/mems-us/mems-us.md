# MEMS-US (water-proofed MEMS-scanner single-element imager)

**Full name:** Versatile Single-Element Ultrasound Imaging Platform using a Water-Proofed MEMS Scanner for Animals and Humans
**Year:** 2020
**Origin:** POSTECH (Pohang Univ. of Science and Technology) — Choi, Kim, Lim, Baik, H.H. Kim, C. Kim
**Status:** research prototype (published; not an open BOM — uses commercial instruments)
**References:** Scientific Reports 10:6544 (2020), DOI 10.1038/s41598-020-63529-z (`pdfs/s41598-020-63529-z.pdf`)
**Repository:** —
**License:** — (paper open access; hardware uses off-the-shelf lab instruments)
**One-line summary:** Real-time B-mode from a **single element** by steering the acoustic beam with a water-proofed MEMS acoustic-mirror scanner — tabletop (3D, animals) and handheld (<60 g probe, human wrist) variants.

> Key idea for a single-channel imager: get B-mode without an array by *steering
> the beam* (MEMS mirror), not by moving the transducer. Electronics here are
> commercial lab-grade (not cheap), but the scanning concept is the relevant part.

---

## 1. Classification

**Piezo 1–5 MHz:** Yes (broadband pulser-receiver + 100 MSps; paper used 16.7 MHz) · **ADC sampling:** 100 MSps (12-bit)

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | single-element + MEMS mirror scanner + PC/DAQ | [P] |
| Intended application | Preclinical (small-animal cardiac) & clinical (wrist, ophthalmic) imaging | [P] |
| Imaging modes | B-mode, M-mode, 3D volumetric (+ motorized stage) | [P] |
| Single-channel only? | yes (single-element transducer, single channel) | [P] |
| Wireless? | none (PC-connected) | [P] |
| Open source? | no | [P] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | handheld probe 50 × 20 × 20 mm (MEMS + transducer) | [P] |
| Weight | handheld probe <60 g | [P] |
| Volume | — | |
| Wearable / benchtop | benchtop (tabletop) + handheld probe | [P] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | PC + NI-PCIe-6321 DAQ (steer + trigger); LabVIEW/MATLAB, GPU | [P] |
| Core clock | host | |
| On-board memory | host | |
| On-board DSP / beamforming | host-side B-mode; GPU parallel compute (handheld real-time) | [P] |
| Firmware toolchain | LabVIEW (control/GUI), MATLAB (3D volume) | [P] |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | commercial pulser-receiver (Olympus 5073PR) | [P] |
| TX voltage | 5073PR pulser (not specified in-paper) | [P] |
| HV supply IC / topology | commercial instrument | [P] |
| Pulser driver IC | Olympus 5073PR pulser-receiver | [P] |
| Excitation waveform | pulse | [P] |
| Excitation frequency range | matched to 16.7 MHz transducer (adaptable 7.5–30 MHz) | [P] |
| Transmit beamforming | none — **MEMS acoustic-mirror beam steering** instead | [P] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | single-element, LiNbO3 (lithium niobate) | [P] |
| Centre frequency | 16.7 MHz (aperture 9 mm, focal 21.8 mm, FBW 51.7%, DoF 4.1 mm) | [P] |
| Element count | 1 | [P] |
| Pitch / aperture | 9 mm aperture | [P] |
| T/R switch | in 5073PR pulser-receiver | [P] |
| HV multiplexer | none | [P] |
| Channel scheme | single (beam scanned by MEMS mirror) | [P] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 | [P] |
| Acquisition route | raw RF (digitized, host-side B-mode) | [P] |
| Pre-amplifier | voltage amplifier TCA0372 (ON Semi) for mirror-steer; RX via 5073PR | [P] |
| Gain type | TGC applied in processing (log compression, TGC in software) | [P] |
| Gain range | ? | |
| TGC slope / control | software (post-acquisition) | [P] |
| Envelope detection | digital (frequency demodulation + log compression) | [P] |
| ADC part | ATS9350 (AlazarTech) high-speed digitizer | [P] |
| ADC sample rate | 100 MS/s | [P] |
| ADC resolution | 12-bit | [P] |
| ADC integrated vs external | external instrument | [P] |
| End-to-end −3 dB bandwidth | transducer 16.7 MHz, FBW 51.7% | [P] |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | none | [P] |
| Wireless throughput | — | |
| Wired interface | PCIe (DAQ + digitizer to PC) | [P] |
| Wired throughput | 100 MS/s digitizer to host | [P] |
| Host interface / handshake | LabVIEW GUI; PRF 10 kHz trigger from DAQ | [P] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | superficial (16.7 MHz; wrist, mouse heart) | [P] |
| Axial resolution | 100 µm | [P] |
| Lateral resolution | 203 µm | [P] |
| PRF range | 10 kHz (pulser-receiver limited) | [P] |
| Frame rate (B-mode) | 40 Hz | [P] |
| SNR / SINAD | ATS9350 dynamic range 400 mV | [P] |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | — (lab instruments) | |
| Total system power | mains (benchtop instruments) | [E] |
| Battery | — | |
| Battery life | — | |

## 10. Notes / constraints / relevance to *minus*

- **Most relevant idea: single-element real-time B-mode via MEMS acoustic-mirror
  beam steering** — a way to get 2-D images from ONE channel without an array or a
  bulky motorized transducer. Frame rate 40 Hz, lateral 203 µm / axial 100 µm at
  16.7 MHz.
- Not a low-cost BOM: relies on commercial Olympus 5073PR pulser-receiver +
  AlazarTech ATS9350 (100 MS/s) digitizer + NI DAQ. The *scanning mechanism* is the
  transferable part; the electronics would be replaced by a kelu124-style AFE.
- Constraints: fixed focal zone (out-of-focus blur), PRF capped at 10 kHz, 3D needs
  motorized stages. See [[pic0rick]] (as the cheap AFE that could replace the
  instruments), [[iup]].
