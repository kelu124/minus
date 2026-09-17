# IUP (Integrated Ultrasound Platform)

**Full name:** IUP — Integrated Ultrasound Platform (distributed UDV sensor node for the DRESDYN precession experiment)
**Year:** ~2025 (SSRN preprint, not yet peer-reviewed)
**Origin:** HZDR (Helmholtz-Zentrum Dresden-Rossendorf), DRESDYN team
**Status:** research prototype (preprint; open-source status not stated)
**References:** SSRN preprint 6946751 (`pdfs/ssrn-6946751.pdf`)
**Repository:** — (raw validation data referenced in-paper)
**License:** ?
**One-line summary:** Self-contained single-channel ultrasonic Doppler-velocimetry (UDV) node — un0rick-class analog chain + STM32H7/iCE40 control + SD/SDRAM raw-data storage + Wi-Fi, battery-powered, in a 3-PCB stack.

> Not medical imaging: it measures 1-D flow velocity profiles in liquid metal.
> But the hardware architecture is the closest full-system match to *minus*.

---

## 1. Classification

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | hybrid MCU (STM32H7) + FPGA (iCE40) | [P] |
| Intended application | Distributed ultrasonic Doppler velocimetry in liquid sodium | [P] |
| Imaging modes | UDV Doppler velocity profiles (A-line based; not B-mode) | [P] |
| Single-channel only? | yes (single transducer/channel per node) | [P] |
| Wireless? | Wi-Fi (ESP32-S3) | [P] |
| Open source? | ? (not stated) | |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | 62 × 45 × 23 mm (stack of 3 PCBs) | [P] |
| Weight | 43.4 g | [P] |
| Volume | ~64 cm³ | [E] |
| Wearable / benchtop | embedded sensor node (in flange housing) | [P] |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor | STM32H725IGK (Cortex-M7, up to 480 MHz) + iCE40HX4K FPGA | [P] |
| Core clock | MCU up to 480 MHz | [P] |
| On-board memory | SDRAM IS42VM16160K (100 MT/s, 16-bit) + SD card (≤2 TB) | [P] |
| On-board DSP / beamforming | FPGA timing/capture; MCU signal processing; host-side Doppler | [P] |
| Firmware toolchain | ? | |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | bipolar (3-state), symmetric ±32 V | [P] |
| TX voltage | ±32 V rail (LT8582); 46 Vpp pulse amplitude used | [P] |
| HV supply IC / topology | LT8582 dual DC-DC → ±32 V | [P] |
| Pulser driver IC | MD1213 + TC6320 (Microchip), FPGA-controlled | [P] |
| Excitation waveform | N-cycle burst (4 periods used) | [P] |
| Excitation frequency range | fe up to 2 MHz (design); 2 MHz used | [P] |
| Transmit beamforming | none (single element) | [P] |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | single-element (TR0210LH, Signal Processing SA, in validation) | [P] |
| Centre frequency | 2 MHz (validation transducer) | [P] |
| Element count | 1 | [P] |
| Pitch / aperture | 10 mm dia. class (D≤12 mm integration limit) | [P] |
| T/R switch | MD0100 (Microchip) | [P] |
| HV multiplexer | none | [P] |
| Channel scheme | single | [P] |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | 1 | [P] |
| Acquisition route | raw RF (16-bit, stored for offline Doppler processing) | [P] |
| Pre-amplifier | AD8331 AFE (VGA) | [P] |
| Gain type | TGC (voltage-controlled amplifier in AD8331) | [P] |
| Gain range | AD8331 range; 30 dB used | [P] |
| TGC slope / control | MAX5184 DAC (FPGA-controlled) sets gain ramp | [P] |
| Envelope detection | digital / host (2D autocorrelation Doppler) | [P] |
| ADC part | LTC2203 (Analog Devices), external | [P] |
| ADC sample rate | 16 MHz (fs); design max 16 MHz sufficient | [P] |
| ADC resolution | 16-bit (chosen to maximize dynamic range) | [P] |
| ADC integrated vs external | external (parallel bus to FPGA) | [P] |
| End-to-end −3 dB bandwidth | analog anti-alias filter; 200 kHz BW 10th-order Butterworth in processing | [P] |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | Wi-Fi (ESP32-S3-MINI-1U, external 2.4 GHz antenna) | [P] |
| Wireless throughput | control/status only (raw data not streamed) | [P] |
| Wired interface | USB (to MCU); SD card removable | [P] |
| Wired throughput | ADC→FPGA FIFO 32 MB/s; FPGA→MCU 64 MB/s; SD write ≥30 MB/s | [P] |
| Host interface / handshake | Wi-Fi start/stop + status; raw data via SD/USB to PC | [P] |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | up to ~1 m measurement depth (flow, full-scale); 0.16 m down-scaled | [P] |
| Axial resolution | range gates 4.8 mm width (128 gates) | [P] |
| Lateral resolution | beam-limited (−6 dB width ~15 mm at ROI) | [P] |
| PRF range | fPRR 727 Hz used (≤~4.6 kHz by depth) | [P] |
| Frame rate (B-mode) | — (100 velocity profiles at 150 ms spacing) | [P] |
| SNR / SINAD | 16-bit ADC for max dynamic range; validated vs PIV (−2.2%) | [P] |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | — | |
| Total system power | 2.96 W (continuous measure + SD + Wi-Fi) | [P] |
| Battery | 18650 Li-ion (14.4 Wh) | [P] |
| Battery life | sustains a full experimental run (~4 h target) | [P] |

## 10. Notes / constraints / relevance to *minus*

- **Closest full-system template for a self-contained single-channel node.** Shares
  the kelu124-family analog chain almost part-for-part (iCE40HX4K + MD1213/TC6320
  pulser + AD8331 VGA/TGC + MD0100 T/R + DAC-driven gain), then adds: **16-bit ADC
  (LTC2203) at 16 MHz** (dynamic range over raw speed), **on-board SD + SDRAM raw
  buffering**, **ESP32 Wi-Fi control**, and **battery** — in a 43 g 3-PCB stack.
- Data strategy worth copying: store raw to SD (32 MB/s = fs·B), send only
  control/status over Wi-Fi; DMA + SDRAM FIFO decouple ADC bursts from SD writes.
- Caveats for *minus*: 2.96 W (not low-power); Doppler/flow app, so B-mode imaging
  is not demonstrated; ±32 V bipolar HV. See [[un0rick]], [[pic0rick]], [[wulpus-pro]].
