# un0rick

**Full name:** un0rick — open iCE40 single-element ultrasound board
**Year:** 2019 (project since 2016; echomods lineage)
**Origin:** Luc Jonveaux (kelu124)
**Status:** open-source (OSHWA FR000005; TAPR/GPLv3); on Tindie ~$489
**References:** ResearchGate "un0rick: open-source FPGA board for single element ultrasound imaging"; un0rick.cc
**Repository:** https://github.com/kelu124/un0rick
**Design files:** `design/un0rick/` (schematic PDF, BOM, gerbers, drills)
**License:** open hardware (TAPR) / GPLv3 software
**One-line summary:** Single-channel iCE40 FPGA pulse-echo board with a 65 Msps ADC and DAC-controlled TGC, controlled over SPI from USB / Raspberry Pi / Arduino.

---

## 1. Classification

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | FPGA (iCE40) | [D] |
| Intended application | Single-element imaging, NDT, teaching, research | [D] |
| Imaging modes | A-mode (B-mode offline via mechanical scan) | [D] |
| Single-channel only? | yes (single SMA; TX/RX shared) | [D] |
| Wireless? | none (USB / RPi) | [D] |
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
| Main processor | Lattice iCE40HX4K (TQFP-144) | [D] |
| Core clock | ? | |
| On-board memory | 8 Mbit SRAM (10 ns, 512k×16) + 8 Mb SPI flash | [D] |
| On-board DSP / beamforming | none (host-side) | [D] |
| Firmware toolchain | IceStorm/iceprog (open) | [D] |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | unipolar (HV pulse) | [D] |
| TX voltage | 25 V / 50 V / 75 V (selectable) | [D] |
| HV supply IC / topology | on-board HV | [D] |
| Pulser driver IC | MD1210 + TC6320 | [D] |
| Excitation waveform | pulse (programmable width, line delays) | [D] |
| Excitation frequency range | transducer-dependent (65 Msps sampling) | [E] |
| Transmit beamforming | none | [D] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | single-element piezo (repurposed probes / scanner heads) | [D] |
| Centre frequency | transducer-dependent | |
| Element count | 1 | [D] |
| Pitch / aperture | — | |
| T/R switch | shared TX/RX path | [D] |
| HV multiplexer | none (base board) | [D] |
| Channel scheme | single | [D] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 | [D] |
| Acquisition route | raw RF | [D] |
| Pre-amplifier | AD8331 (VGA) | [D] |
| Gain type | TGC (analog VGA, DAC-driven) | [D] |
| Gain range | AD8331 range | [D] |
| TGC slope / control | 8-bit DAC, updated every 5 µs over 200 µs window | [D] |
| Envelope detection | digital (host) | [D] |
| ADC part | ADC10065 (external) | [D] |
| ADC sample rate | 65 Msps | [D] |
| ADC resolution | 10-bit | [D] |
| ADC integrated vs external | external | [D] |
| End-to-end −3 dB bandwidth | ? | |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | none | [D] |
| Wireless throughput | — | |
| Wired interface | SPI (via USB / Raspberry Pi / Arduino) | [D] |
| Wired throughput | SPI; SRAM buffers a frame, read back after acquisition | [D] |
| Host interface / handshake | full board control over SPI; 2× PMOD | [D] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | transducer/setup-dependent | |
| Axial resolution | transducer-dependent | |
| Lateral resolution | — | |
| PRF range | programmable (line delays) | [D] |
| Frame rate (B-mode) | offline (mechanical scan) | [D] |
| SNR / SINAD | ? | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | — | |
| Total system power | ~1.75–2.25 W (350–450 mA @ 5 V) | [D] |
| Battery | — (USB/RPi powered) | |
| Battery life | — | |

## 10. Notes / constraints / relevance to *minus*

- Direct ancestor of pic0rick and the closest "cheap single-channel" reference in
  the family: same ADC10065 / AD8331 / MD1210+TC6320 building blocks, but on an
  iCE40 (open toolchain) instead of RP2040.
- For *minus*: the canonical minimal single-channel open design. The main levers
  to make it *cheaper/simpler* are the FPGA vs MCU choice, the external 65 Msps ADC
  (cost + power), and dropping the 3-level HV supply. See [[pic0rick]], [[lit3rick]].
