# pic0rick

**Full name:** pic0rick — RP2040-based pulse-echo ultrasound acquisition board
**Year:** 2024
**Origin:** kelu124
**Status:** open-source (OSHWA certified; available on Tindie)
**References:** github.com/kelu124/pic0rick ; wulrick comparison
**Repository:** https://github.com/kelu124/pic0rick
**Design files:** `design/pic0rick/` (KiCad + schematic PDFs + gerbers for adc, mux, and the 3-in-1 adc+pulser+hv panel); article in `pdfs/pic0rick_full.pdf`
**License:** open hardware (KiCad, JLCPCB-compatible)
**One-line summary:** Open, USB-tethered single-channel raw-RF acquisition board with a 65 Msps ADC and variable TGC; PMOD-expandable to 8 channels.

---

## 1. Classification

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | MCU (RP2040) | [D] |
| Intended application | Experimenter / research raw RF capture | [D] |
| Imaging modes | A-mode (B-mode offline) | [D] |
| Single-channel only? | 1 by default; optional 8 via PMOD mux | [D] |
| Wireless? | none (USB) | [D] |
| Open source? | yes | [D] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | ? | |
| Weight | ? | |
| Volume | ? | |
| Wearable / benchtop | benchtop | [D] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | RP2040 (dual Cortex-M0+, PIO) | [D] |
| Core clock | 133 MHz | [D] |
| On-board memory | 264 KB SRAM + external flash | [D] |
| On-board DSP / beamforming | none (host-side envelope/processing) | [D] |
| Firmware toolchain | CMake / UF2 | [D] |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | bipolar | [D] |
| TX voltage | ±24 V | [D] |
| HV supply IC / topology | dual rail | [D] |
| Pulser driver IC | MD1213 + TC6320 | [D] |
| Excitation waveform | pulse (PIO nanosecond-resolution timing) | [D] |
| Excitation frequency range | up to ~32 MHz (transducer-dependent) | [D] |
| Transmit beamforming | none | [D] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | single-element (any up to ~32 MHz) | [D] |
| Centre frequency | 2–30 MHz range supported | [D] |
| Element count | 1 (up to 8 muxed) | [D] |
| Pitch / aperture | — | |
| T/R switch | MD0100 (MD0101 active upgrade optional) | [D] |
| HV multiplexer | MAX14866 (8-ch mux PMOD, optional) | [D] |
| Channel scheme | single (optional 8-ch PMOD) | [D] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 (of optional 8) | [D] |
| Acquisition route | raw RF | [D] |
| Pre-amplifier | AD8331 (VGA) | [D] |
| Gain type | TGC (analog VGA, DAC-driven) | [D] |
| Gain range | AD8331 range (~48 dB) | [E] |
| TGC slope / control | MCP4812 12-bit DAC drives AD8331 | [D] |
| Envelope detection | digital (host) | [D] |
| ADC part | ADC10065 (external) | [D] |
| ADC sample rate | 65 Msps | [D] |
| ADC resolution | 10-bit | [D] |
| ADC integrated vs external | external | [D] |
| End-to-end −3 dB bandwidth | ~32 MHz (transducer-limited) | [E] |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | none | [D] |
| Wireless throughput | — | |
| Wired interface | USB | [D] |
| Wired throughput | USB (no practical limit for research frame rates) | [D] |
| Host interface / handshake | Python-first API | [D] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | transducer-dependent | |
| Axial resolution | transducer-dependent (high-freq capable) | |
| Lateral resolution | — | |
| PRF range | configurable (PIO timing) | [D] |
| Frame rate (B-mode) | offline | [D] |
| SNR / SINAD | uncharacterized (no phantom data published) | [D] |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | ~300–400 mW | [S] |
| Total system power | ~300–400 mW (ADC10065 ~68 mW alone) | [S] |
| Battery | — (USB-powered) | |
| Battery life | — | |

## 10. Notes / constraints / relevance to *minus*

- The "better instrument" in the wulrick comparison: high frequency range,
  variable TGC (AD8331 + MCP4812 DAC), flexible transducers, KiCad reproducibility,
  Python scripting. The reference open baseline this project sits next to.
- Trade-off: USB-tethered and power-hungry (65 Msps external ADC dominates power).
- For *minus*: the incumbent single-channel open design; *minus* likely trims cost
  and parts from here rather than adding capability. Direct reuse candidate.
