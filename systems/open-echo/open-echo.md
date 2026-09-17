# Open Echo

**Full name:** Open Echo — open-source TUSS4470 SONAR / echo-sounder
**Year:** 2024–2025 (active; TUSS4470_shield_002 = 2025)
**Origin:** Neumi (open-source project)
**Status:** open-source (HW + firmware + Python SW); pre-built on Elecrow
**References:** github.com/Neumi/open_echo ; Hackaday.io project 196793 ; Elecrow listing
**Repository:** https://github.com/Neumi/open_echo
**License:** open-source (see repo)
**Design files:** `design/open-echo/` (KiCad sch/pcb/pro + gerbers + BOM, TUSS4470_shield_002)
**One-line summary:** The concrete open **TUSS4470-based** single-channel pulse-echo board — an Arduino-UNO shield that drives 40 kHz–1 MHz transducers in air/water, captures raw echo via the host MCU ADC, and streams to a Python backend. The realized "TUSS4470 route" from `systems/tuss4470/`.

> SONAR/bathymetry rather than medical, but exactly the cheap, open, single-element
> TUSS4470 A-mode/ToF architecture — the most accessible entry point in this survey.

---

## 1. Classification

**Piezo 1–5 MHz:** No (40 kHz–1 MHz TUSS4470 band) · **ADC sampling:** ~75 kSps (host MCU ADC, 8-bit)

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | AFE IC (TUSS4470) + host MCU (Arduino UNO / Pico) | [D] |
| Intended application | SONAR / depth sounding / bathymetry; DIY ultrasound | [D] |
| Imaging modes | A-mode / echo (ToF), raw echo waterfall | [D] |
| Single-channel only? | yes (single transducer) | [D] |
| Wireless? | none on shield (PicoW variant streams RAW over UDP) | [D] |
| Open source? | yes (HW + FW + SW) | [D] |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | Arduino UNO R3 shield | [D] |
| Weight | ? | |
| Volume | ? | |
| Wearable / benchtop | benchtop / embeddable (boat, Pixhawk) | [D] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | Arduino UNO (ATmega328P); also PicoW (RP2040) / STM32F103 variants | [D] |
| Core clock | 16 MHz (UNO) | [E] |
| On-board memory | host MCU | [D] |
| On-board DSP / beamforming | none (host/Python processing) | [D] |
| Firmware toolchain | Arduino; RAW-data FW + NMEA0183 DBT output FW | [D] |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | bipolar (TUSS4470 internal H-bridge / FET pre-driver) | [D] |
| TX voltage | drive from Arduino VIN / XT30; ~15–20 V via MT3608 boost (USB) | [D] |
| HV supply IC / topology | MT3608 boost (external/optional; on-board boost on next board) | [D] |
| Pulser driver IC | TUSS4470 (TI) | [D] |
| Excitation waveform | burst (N-cycle), software-configurable | [D] |
| Excitation frequency range | 40 kHz – 1 MHz | [D] |
| Transmit beamforming | none (single element; phased-array variant experimental) | [D] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | single-element; many supported (parking sensor 40 kHz, boat 150/200 kHz, sidescan, 1 MHz flow) | [D] |
| Centre frequency | 40 kHz – 1 MHz (transducer-dependent) | [D] |
| Element count | 1 | [D] |
| Pitch / aperture | — | |
| T/R switch | integrated in TUSS4470 (burst-and-listen) | [D] |
| HV multiplexer | none | [D] |
| Channel scheme | single | [D] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 | [D] |
| Acquisition route | TUSS4470 LNA + bandpass + log-amp; digitized by host ADC | [D] |
| Pre-amplifier | TUSS4470 integrated LNA | [D] |
| Gain type | logarithmic amplifier (TUSS4470), not linear TGC | [D] |
| Gain range | TUSS4470 log-amp dynamic range | [D] |
| TGC slope / control | — (log-amp) | [D] |
| Envelope detection | TUSS4470 analog envelope path (or raw); host processing | [D] |
| ADC part | host MCU ADC (Arduino ~8-bit capture) | [D] |
| ADC sample rate | ~75 kSps (1800 samples @ 13.2 µs) | [D] |
| ADC resolution | 8-bit (capture) | [D] |
| ADC integrated vs external | host MCU integrated | [D] |
| End-to-end −3 dB bandwidth | ≤1 MHz (TUSS4470 band) | [D] |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | none (PicoW variant: UDP over WiFi) | [D] |
| Wireless throughput | UDP (PicoW), raw | [D] |
| Wired interface | USB (Arduino serial); XT30 power | [D] |
| Wired throughput | serial to Python backend | [D] |
| Host interface / handshake | Python interface (live echogram, TCP stream); NMEA0183 DBT out | [D] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | tested >50 m in water (~18 m per 1800-sample capture; extend via delays) | [D] |
| Axial resolution | coarse (13.2 µs/sample, envelope, ≤1 MHz) | [E] |
| Lateral resolution | — | |
| PRF range | software-configurable | [D] |
| Frame rate (B-mode) | — (waterfall echogram) | [D] |
| SNR / SINAD | log-amp high dynamic range | [D] |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | low (Arduino + TUSS4470) | [E] |
| Total system power | USB-powered | [D] |
| Battery | — | |
| Battery life | — | |

## 10. Notes / constraints / relevance to *minus*

- The **cheapest, most accessible open realization of the TUSS4470 route**: single
  IC front-end (pulser + LNA + log-amp + envelope) + a commodity MCU ADC. Buyable
  pre-built (Elecrow) or self-fab (KiCad + gerbers in `design/open-echo/`).
- Hard limits for medical imaging: ≤1 MHz band, envelope/log-amp (no linear TGC, no
  RF phase), ~75 kSps 8-bit host ADC. Great for ToF/depth/presence; not B-mode.
- For *minus*: the reference "how cheap/simple can a single-channel pulse-echo board
  be" if the target accepts ≤1 MHz envelope sensing. See [[tuss4470]], [[pulse]].
