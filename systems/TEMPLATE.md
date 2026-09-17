<!--
minus — system datasheet template
Copy this file to systems/<slug>/<slug>.md and fill it in.
Conventions:
  - Use "—" for a field that does not apply.
  - Use "?" for unknown / not disclosed (distinct from "—").
  - Keep the source/confidence tag in the last column where useful:
      [D] datasheet/repo/primary doc   [P] peer-reviewed paper
      [S] secondary (slides, survey)   [E] estimate/inferred   [?] unknown
  - Prefer numbers with units. Note "est." inline when a value is inferred.
  - One device per folder. Keep this template in sync as new fields appear.
-->

# <System name>

**Full name:** <full title>
**Year:** <first publication / release>
**Origin:** <lab / company / author group>
**Status:** open-source | partially open | closed | unknown
**References:** <paper DOI / arXiv / product page>
**Repository:** <url or —>
**License:** <hardware/software license or —>
**One-line summary:** <what it is, in a sentence>

---

## 1. Classification

**Piezo 1–5 MHz:** Yes / No / Partial / ? (short note) · **ADC sampling:** <MSps or "external/low-rate">

| Field | Value | Src |
|-------|-------|-----|
| Architecture class | MCU / FPGA / custom silicon / hybrid | |
| Intended application | | |
| Imaging modes | A-mode / B-mode / M-mode / Doppler | |
| Single-channel only? | yes / no | |
| Works with 1–5 MHz piezo? | yes / no / partial (why) | |
| ADC sampling speed | <MSps / low-rate / external> | |
| Wireless? | none / BLE / Wi-Fi / other | |
| Open source? | yes / partial / no | |

## 2. Form factor

| Field | Value | Src |
|-------|-------|-----|
| Dimensions | <L × W × H mm> | |
| Weight | <g> | |
| Volume | <cm³> | |
| Wearable / benchtop | | |

## 3. Compute & control

| Field | Value | Src |
|-------|-------|-----|
| Main processor (MCU/FPGA/ASIC) | <part> | |
| Core clock | | |
| On-board memory | <FRAM/SRAM/DRAM, size> | |
| On-board DSP / beamforming | none / envelope / DAS / ML | |
| Firmware toolchain | | |

## 4. Transmit / pulser

| Field | Value | Src |
|-------|-------|-----|
| Pulser polarity | unipolar / bipolar / arbitrary | |
| TX voltage | <V, e.g. +15 V, ±24 V, 64 Vpp> | |
| HV supply IC / topology | <part, boost/buck-boost/dual-rail> | |
| Pulser driver IC | <part> | |
| Excitation waveform | single-cycle / N-cycle / coded | |
| Excitation frequency range | <MHz> | |
| Transmit beamforming | none / delay profiles (N) | |

## 5. Front-end & transducer

| Field | Value | Src |
|-------|-------|-----|
| Transducer type | single-element / linear array / CMUT / PMUT / PZT patch | |
| Centre frequency | <MHz> | |
| Element count | | |
| Pitch / aperture | | |
| T/R switch | <part, RX recovery time> | |
| HV multiplexer | <part, channel count> | |
| Channel scheme | single / time-multiplexed (N) / parallel (N) | |

## 6. Receive / acquisition

| Field | Value | Src |
|-------|-------|-----|
| Active RX channels | | |
| Acquisition route | raw RF / analog envelope / on-chip DSP | |
| Pre-amplifier | <part, gain> | |
| Gain type | fixed PGA / VGA / TGC (analog) / TGC (digital DAC) | |
| Gain range | <dB> | |
| TGC slope / control | <dB, RC ramp / DAC part> | |
| Envelope detection | none / analog (<part>) / digital (firmware/host) | |
| ADC part | <part or "integrated in <MCU>"> | |
| ADC sample rate | <Msps> | |
| ADC resolution | <bits> | |
| ADC integrated vs external | | |
| End-to-end −3 dB bandwidth | <MHz> | |

## 7. Connectivity & data

| Field | Value | Src |
|-------|-------|-----|
| Wireless link | none / BLE / Wi-Fi / other | |
| Wireless throughput | <kbps / Mbps> | |
| Wired interface | USB / SPI / other | |
| Wired throughput | | |
| Host interface / handshake | | |

## 8. Performance

| Field | Value | Src |
|-------|-------|-----|
| Imaging depth | <cm> | |
| Axial resolution | <µm> | |
| Lateral resolution | <mm> | |
| PRF range | <Hz> | |
| Frame rate (B-mode) | <Hz> | |
| SNR / SINAD | <dB> | |

## 9. Power

| Field | Value | Src |
|-------|-------|-----|
| Core power | <mW> | |
| Total system power | <mW> | |
| Battery | <mAh, chemistry> | |
| Battery life | | |

## 10. Notes / constraints / relevance to *minus*

- <key trade-offs, what's reusable, open questions>

<!--
Field checklist the template must keep covering (per user request):
MCU/FPGA · pulser polarity+voltage · acquisition route · ADC · gain/TGC type ·
connection bandwidth · wireless y/n · single-channel y/n. Add fields, never drop.
-->
