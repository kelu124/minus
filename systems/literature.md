# Literature review — simple ultrasound hardware

Distilled from the anchor survey **Jonveaux, Schloh, Meng, Arija, Rintoul,
"Review of Current Simple Ultrasound Hardware Considerations, Designs, and
Processing Opportunities", *Journal of Open Hardware* 6(1):3, 2022,
DOI 10.5334/joh.28** (`pdfs/28-952-1-PB.pdf`) — plus the two device papers in
`pdfs/`. Scope filter: **single- to ≤32-element designs** (64+ omitted, per the
project rule; a count is noted).

## Design targets for a simple B-mode scanner

From the minimal spec set (Kurjak & Breyer 1986) the review frames:
- Linear/convex scan-head, **3.5–5 MHz**, depth **up to 18 cm**.
- Image tissue at **SNR ≥ 50 dB ⇒ ADC ≥ 9-bit**.
- **128 lines/image** (≥40° view), 512×512 display (4-bit grey), **5–10 fps**.
- A-mode is the building block of B-mode; M-mode is A-mode over time.

## Functional blocks (the reference architecture)

`Sensor → Pulser → T/R switch (receiver protect) → TGC amplifier → ADC → controller (FPGA) → host`

Analog parts are the hard part (low signals). A controller (usually an FPGA, for
parallel timing) coordinates the blocks; ADC data is exported to a host.

## Table 2 (filtered) — single / few-element designs

Columns from the review: Elements · TX Voltage · MSPS · Res(bit) · AFE/TGC · Year.
`NA` = not stated. (64/128-element rows omitted — see count below.)

| Reference | El. | Voltage | MSPS | Res | AFE/TGC | Year |
|-----------|-----|---------|------|-----|---------|------|
| Chang-hong Hu, Zhou, Shung | 1 | 15 V | 120 | 12 | — | 2008 |
| Ricci et al. | 1 | 100 V | 64 | 14 | MAX4107 | 2006 |
| FRITSCH (NDE, full FPGA) | 1 | 50–400 V | 80 | — | NA | n.d. |
| Y. Qiu et al. | 1 | 60 V | 250 | — | TC6320 | 2020 |
| Jonveaux (Murgen) | Single | 100 Vpp | 22 | 9 | AD8331 | 2017/18 |
| H. Li et al. | Single | 80 V | 40 | 12 | AD9276 | 2014 |
| Kushi & Suresh Babu | Single | NA | 100 | 14 | NA | 2017 |
| Weibao Qiu, J. Xia, et al. | Single | +48 V | 160 | — | AD8331 | 2018 |
| Kruizinga et al. (compressive 3D, 1 sensor) | Single | 100 Vpp | 200 | 12 | NA | 2017 |
| Vasudevan, Govindan, Saniie | Single | 100 Vpp | 250 | 12 | VCA8500 | 2014 |
| Nguyen et al. | 2 | 18 V | 40 | 10 | — | 2019 |
| R. Bharath, Reddy, et al. | 8 | ±50 V | 40 | 12 | AFE5808 | 2016 |
| Dusa et al. | 8 | 100 Vpp | 65 | 12 | AFE5809 | 2014 |
| Bharath et al. | 8 | 105 V | 50 | 16 | AFE5809 | 2018 |
| Pramod Govindan et al. | 8 | NA | 250 | 8 | VCA8500 | 2015 |
| Matera et al. | 8 | 6 V | 75 | 14 | AFE5809 | 2018 |
| Pashaei, Dehghanzadeh, et al. | 8 | 10 V | 80 | 12 | AD9276 | 2020 |
| D.-l. Zhang et al. | 8 | 70 V | 250 | 16 | QT1138 | 2017 |
| Ahn et al. | 16 | 70 V | 40 | 10 | AFE5808 | 2015 |
| Y. Lee et al. | 16 | NA | 40 | — | AFE5808 | 2014 |
| Weng, Chen, Huang | 16 | 100 V | 150 | 10 | MAX2077 | 2015 |
| Chatar & George | 16 | NA | 150 | 14 | NA | 2016 |
| Fournelle et al. | 32 | ±100 V | 40 | — | NA | 2020 |
| Peyton, Boutelle, Drakakis | 32 | NA | 20 | — | Custom | 2018 |
| Amauri Amorin Assef | NA | 100 Vpp | 40 | 12 | AFE5805 | 2015 |
| Wall | NA | 12 V | 65 | — | NA | 2010 |
| R. Bharath, Chandrashekar | NA | NA | NA | — | NA | 2015 |

*Omitted as out of scope (64+ elements): ~9 rows — A.A. Assef & Maia 2014 (128),
Amauri A. Assef 2012 (128), Cheung 2012 (128, AD9272), Hager 2017 (64, AFE5851),
Hewener 2012 (128, AD9273), Ibrahim & Zhang 2018 (64), J.H. Kim 2017 (128/32-ch),
Roman 2018 (64, AD9276), Q. Zhang 2019 (64). Batbayar 2018 "4×32" is borderline
multichannel.*

Read of the table: single-element designs cluster at **1–15 MHz, 40–250 MSps,
10–14 bit**, with discrete VGAs (AD8331/VCA8500/MAX4107); 8–16-element designs
lean on integrated AFEs (**AFE58xx**, **AD927x**).

## Component menus (for a minus BOM)

**Pulsers (Table 3 typology):**
- Discrete driver + HV FETs: MD1213+MD1711, TC7320+MD1810, EL7158+TC6320,
  MD1210+TC6320, MD1812/MD1813 composite. (kelu124 family + IUP use MD121x+TC6320.)
- Integrated pulser ICs: HV7361, **HV7351** (8-ch, predetermined TX patterns),
  HV748, STHV800, STHV748, LM96551.
- Mux / switches: MAX14808, **MAX14866**, LM96530, HV2605, HV2201, HV20220.
- T/R protect / clipping: **MD0100/MD0101**, MMBD4148/MMBD3004.
- Signal gen + power amp: THS5651A+LT1210CS, TCA0372.

**HV supply sources:** RECOM 0–120 V, NMT0572SC (24/48/72 V), LT3494 (≤39 V),
MAX668 (0–150 V), MAX1856 (−80…−24 V), MIC3172/HV9150 (≤200 V), MAX15031 (≤80 V),
DRV8662/DRV2700 (≤105 V), PICO 5SM250S, **LT8582** (bipolar ±32 V, per IUP), SEPIC
bipolar (Granata 2020). Impedance matching (low-cost VNA / NanoVNA) improves SNR.

**TGC / VGA amps:** AD8331 family (0–40/80 dB), AD8335 (80 dB), AD604 (dual, 48 dB),
MAX4107, VCA8500, MAX2077. Gain typically 0–40/80 dB, DAC-ramped for depth.

**ADCs:** single-frequency 1–15 MHz sensors ⇒ **40–150 MSps, 10–14 bit**; FIFO
(e.g. AL422B) between ADC and controller. IUP uses a 16-bit LTC2203 at 16 MHz.

**Integrated AFEs (multi-channel; for ≤8-ch, not single-element):**
- **AD927x** — 8-ch, 12-bit, 10–80 MHz, integrated TGC.
- **AFE58xx** — 8–32-ch, 50–65 MSps, LNA+VCAT+PGA+LPF+ADC (+optional CW).
- **MAX2082/MAX2077** — 8-ch, HV pulser + T/R switch, **no digitizer**.

**Controllers:** FPGA preferred (parallel timing, DMA); often + MCU/USB bridge
(Cypress USB2/3), Ethernet (CP2200), or Wi-Fi. Open FPGA toolchains (icestorm) make
iCE40 attractive. Jonveaux 2019b used the Raspberry Pi 40-pin header as a standard
extension bus.

## Getting B-mode from a single element (no array)

- **Mechanical sweeping** — motorized / voice-coil scan of one element (Smith 2015
  reports ~95% cost saving vs array; Lei 2018 single-element at 130 fps). Common in
  intra-cavity probes.
- **MEMS acoustic-mirror steering** — Choi et al. 2020 (see [[mems-us]]), real-time
  B-mode at 40 Hz from one element.
- **Synthetic aperture** — SAF, monostatic SA scanners (MSAS), monostatic fixed-
  focus (MFFS); Kruizinga 2017 does **compressive 3D imaging with a single sensor**
  via a coded aperture mask.

## Bandwidth-reduction strategies (lean data path)

- Hardware **envelope detector** before ADC (fixed cutoff = per-transducer limit) —
  cf. [[pulse]], [[tuss4470]].
- **Quadrature sampling + frequency downconversion** — preserves amplitude+phase at
  reduced rate.
- **SDR-based capture** — "rtl-ultrasound" (Meng 2019, a review co-author) uses SDR
  quadrature hardware as a drop-in acquisition path.

## Signal-processing opportunities (host side)

General filtering (near ADC on DSP/FPGA) → envelope detection (Hilbert) →
deconvolution with a measured PSF (sharpen) → amplitude compression (ITU-T G.711
a-law, 12→8-bit) → scan conversion (polar→Cartesian). Advanced: synthetic-aperture
focusing, Barker/chirp coded excitation, compressed sensing (fewer samples than
Nyquist; enables single-element volumetric), and machine learning (image quality,
A-mode interpretation).

## Second anchor: Weik et al. 2026 (system-architecture review) + SIG-WUS

**Weik, Nauber, Kaiser, Kirsch, Kunz, Schierling, Leitner, Benini, Liu, Zhou,
Hampe, Fettweis, Herzog, Kupsch, "Current Trends in Ultrasound Wearables:
Spotlight on System Architecture", IEEE Reviews in Biomedical Engineering, 2026
(early access)** (`pdfs/Current_Trends_..._early_access.pdf`). Peer-reviewed basis
of the **SIG-WUS OXP** (Open eXperimentation/Exchange Platform) catalog at
<https://sig-wus.org> (GitHub org `sig-wus`; the live catalog data failed to load
on fetch — revisit). Same "converge on a modular/scalable common platform" thesis
as the *minus* motivation.

Framework: it splits wearable US into **non-imaging** (≤8 RX ch, muxed to 1) vs
**imaging** (≥32 ch) vs **non-pulse-echo** (CW / chirp / coded). Building blocks
match `literature.md` above (TX gen + amp → HV protection/TR → AFE (VGA+filter+ADC)
→ sequencer/control → compute → comms). Energy metric: **Mbit/J** (data rate ÷
power).

### Table I (its state-of-the-art comparison; 64+ ch omitted)

| Platform | Transducer | TX | RX | Compute | Link | Key specs | Mbit/J | App | Access |
|----------|-----------|----|----|---------|------|-----------|--------|-----|--------|
| **SENS-U** | 4 ch integ. | n/a | 4→1 MUX | n/a | BT, raw | 30° FOV, 55 g, 36 h | n/a | bladder | commercial |
| **WMAUS** | 8 ch, 5 MHz | ±15 V | 8→1 MUX, 40 MS/s | dsPIC33 (DSP) | BT/Eth/WiFi, raw | 10 Hz, 190 g, 132×90×30, 10 h | 0.03 | HMI/sEMG | commercial/API |
| **Yin et al.** | 4 ch, 1 MHz | ±50 V | 4→1 MUX, 2.4 MS/s | STM32F7 | BT/WiFi, raw | 85 g, 5 W, 3.5 h | 0.2 | prosthesis ctrl | n/a |
| WULPUS | 8 ch, ≤4 MHz | 15 V | 8→1 MUX, 8 MS/s | MSP430FR5043 | BLE, raw | 50 Hz, 13 g, 46×25×13, 28 mW | 11 | HMI/heart | open |
| PuLsE | 1 ch, ≤10 MHz | 15 V | analog envelope, 2.4 MS/s | STM32L496 | BT, HR | 25 Hz, 5.8 mW, 7 d, 15 g, ⌀40 | 52 | heart rate | open (planned) |
| **MoUsE** | 32 ch array | ≤±100 V, 0.01–10 MHz bf | 32 ch, 50 MS/s | ZYNQ-7 FPGA | raw | 23 Hz, 610 g, 184×123×33, 12 W | 40 | bladder/hand | n/a |
| USoP | 32 ch array | ≤100 V, 6 MHz | 32→1 MUX, 12 MS/s | PIC32 + flex PCB | WiFi, raw | 31 Hz, 100×30×5, 0.614 W, 12 h | 5.5 | mobile BP | schematics |
| TinyProbe | 32 ch array | ±32 V, ≤15 MHz bf | 32 ch, 30 MS/s | STM32F4 + Igloo2 FPGA | WiFi, raw | 33 Hz, 57×35×20, 35 g, 0.97 W, 2 h | 22 | flow/muscle | open |
| **Flopatch** | 2 ch integ., 60° | CW, 4 MHz | 1 ch | n/a | BT, raw | ~23 mm FOV, 22 g, 54×35×18, 180 min | n/a | carotid flow | commercial |
| **Bashatah et al.** | 4 ch band | sweep 10 ms, 0.5–5 MHz | 4 ch demod, 40 kS/s | TMS320F2 | A-mode | 50 Hz, 100×200×20, 0.82 W | 1.1 | muscle | n/a |
| **Wang et al.** | 11 ch array, 2 MHz | Barker 5-bit, ±10 V | 11→1 MUX | Arduino Due | raw | 240×200×20 | n/a | bladder | n/a |

*(OEM USB Probe [27], 128-ch, omitted — out of scope.)* Bold = **new to this survey**
(sheeted where notable; the rest captured here). Note: this table's WULPUS/PuLsE/
USoP/TinyProbe rows corroborate their own datasheets.

The **SIG-WUS OXP catalog** was retrieved from its repo JSON (the live site failed
to load) — snapshot in [`_sig-wus-oxp/`](_sig-wus-oxp/README.md). It lists 14
platforms; beyond Weik Table I it adds **BioGAP WULPUS-pro** (ETH open shield,
`pulp-bio/sensei-us-shield` — sheeted) and corrects SENS-U → **TENA SmartCare
(Essity)**. FloPatch confirmed as **model FP120, continuous-wave 4 MHz**, FDA
K200337 (2020), validated in Kenny et al. *Sci. Reports* 2021.

### New in-scope systems from Weik Table I

- **SENS-U** — commercial 4-ch bladder-volume monitor; wearable, BT, 36 h. → sheeted.
- **WMAUS** (Wearable Multichannel A-mode UltraSound) — 8-ch dsPIC33 wristband, the
  research origin of the WULPUS/HMI line. → sheeted. **Yin et al.** is a WMAUS
  re-design on an STM32F7 for prosthesis control (noted in the WMAUS sheet).
- **MoUsE** — 32-ch ZYNQ-7 FPGA open POCUS-style imaging platform. → sheeted.
- **Flopatch** — commercial continuous-wave Doppler patch (2-ch, carotid). → sheeted.
- **Bashatah et al.** (chirp, 4-ch) and **Wang et al.** (Barker-coded, bladder) —
  captured here; sheet on request.

## Related open designs by the review authors (kelu124 / co-authors)

- Murgen / Arduino-like AFE (Jonveaux 2017) — see [[murgen]].
- un0rick (2019b), lit3rick (2021b), pyusbus "opening USB ultrasound probes"
  (2021c), a MAX14866 dev board (2021a) — see [[un0rick]], [[lit3rick]].
- rtl-ultrasound (Meng 2019) — SDR acquisition; **lead to sheet**.
- Compressive single-sensor 3D (Kruizinga 2017) — **lead to sheet**.

## Designs grouped by key IC

See [`by-ic.md`](by-ic.md) for which designs use which critical IC. Highlights:
- **MSP430FR5043** (integrated USS_A MCU): WULPUS, WULPUS PRO, BioGAP WULPUS-pro,
  the EMG+A-mode fusion works, TI EVM430-FR6043/FR5043. Bandwidth wall ~1.4 MHz.
- **TUSS4470** (integrated ToF AFE, ≤1 MHz, envelope/log-amp): **Open Echo**
  (Neumi/open_echo — open Arduino shield, sheeted, design files in `design/open-echo/`)
  and TI's BOOSTXL-TUSS4470 EVM. PuLsE is the custom analog-envelope cousin.

## Other open-source imaging catalogs checked

- **opensourceimaging.org/projects** (Open Source Imaging Initiative) — its
  ultrasound entries are only **un0rick** and **echOpen** (= Murgen), both already
  sheeted. No new designs from there (checked 2026-09-17).
