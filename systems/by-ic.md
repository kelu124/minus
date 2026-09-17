# Designs grouped by key IC

Cross-reference of which surveyed designs use which critical ultrasound IC, so a
part choice for *minus* can be traced to working references. Links point to the
datasheet in `systems/<slug>/` or to `literature.md` for table-only entries.

---

## TI MSP430FR5043 (integrated ultrasonic MCU — USS_A)

**What it is:** 16 MHz MSP430 MCU with the **USS_A** peripheral: a programmable
pulse generator (0–5 MHz), a **12-bit 8 MSps sigma-delta ADC**, and a PGA, plus
64 KB FRAM + DMA. Sold by TI for ultrasonic flow metering; repurposed for wearable
A-mode ultrasound. **Ceiling:** ~1.4 MHz end-to-end −3 dB bandwidth (CIC decimation)
⇒ transducers ≤~3 MHz. Ultra-low standby (450 nA).

| Design | Role of the chip | Notes | Ref |
|--------|------------------|-------|-----|
| **WULPUS** | acquisition MCU (USS_A: pulse gen + ADC + PGA) + nRF52832 BLE | 8-ch mux A-mode, 22 mW | [wulpus](wulpus/wulpus.md) |
| **WULPUS PRO** | same USS_A core | adds AD8338 TGC, LT3463 ±30 V, 16-ch, B-mode | [wulpus-pro](wulpus-pro/wulpus-pro.md) |
| **BioGAP WULPUS-pro** | same USS_A core, on BioGAP-Ultra shield | 16-ch, BLE 1.4 Mbit/s, on-device ML, open HW | [biogap-wulpus-pro](biogap-wulpus-pro/biogap-wulpus-pro.md) |
| EMG + A-mode US fusion (arXiv 2510.02000) | WULPUS/BioGAP front-end | US–EMG hand-wrist tracking | lit |
| TI EVM430-FR6043 / FR5043 | vendor USS reference (FR6043 = sibling) | flow-meter EVM; the design template | vendor |

**Takeaway for minus:** the MSP430FR5043 route buys extreme integration + low power
(no external ADC/pulser/gain needed) at the cost of the ~1.4 MHz bandwidth wall.
Good for ≤3 MHz A-mode; wrong choice if raw RF > 3 MHz or imaging is required.

---

## TI TUSS4470 (integrated ultrasonic AFE)

**What it is:** single-channel **direct-drive AFE**: TX H-bridge / external-FET
pre-driver + RX LNA + bandpass + **logarithmic amplifier** with an analog envelope
output (VOUT), SPI-configured. Industrial ToF part, **30 kHz–1 MHz**. No on-chip
ADC (digitize VOUT with a host ADC). See [tuss4470](tuss4470/tuss4470.md).

| Design | Role of the chip | Notes | Ref |
|--------|------------------|-------|-----|
| **Open Echo** (Neumi/open_echo) | full TX+RX AFE on an Arduino-UNO shield | open sonar; 40 kHz–1 MHz; host-ADC ~75 kSps/8-bit; RAW + NMEA FW; buyable (Elecrow); design files in `design/open-echo/` | [open-echo](open-echo/open-echo.md) |
| TI BOOSTXL-TUSS4470 EVM (+ MSP-EXP430F5529LP) | vendor eval of the AFE | the reference eval platform | vendor |

**Takeaway for minus:** the TUSS4470 route is the lowest-part-count, cheapest,
lowest-power option — but **≤1 MHz and envelope/log-amp only** (no linear TGC, no RF
phase, no Doppler). Great for ToF/depth/presence; rules out medical B-mode. PuLsE
([pulse](pulse/pulse.md)) is the *custom* analog-envelope cousin of this route.

---

## Other recurring parts (quick index)

| IC | Function | Used by |
|----|----------|---------|
| **MD1213 + TC6320** | HV pulser driver + FET | un0rick (MD1210), pic0rick, IUP; (Table 3 typology) |
| **AD8331 / AD8332** | VGA / TGC | un0rick (AD8331), lit3rick (AD8332), pic0rick, IUP, MEMS-US-class |
| **AD8338** | low-power VGA/TGC | WULPUS PRO, (BioGAP) |
| **MD0100 / MD0101** | T/R switch (passive/active) | WULPUS PRO (MD0100), un0rick/pic0rick, IUP, BioGAP |
| **LT3463 / LT8582** | dual ±30/±32 V HV supply | WULPUS PRO (LT3463), IUP (LT8582) |
| **ADC10065** (65 MSps, 10-bit) | external fast ADC | un0rick, pic0rick |
| **LTC2203** (16-bit @16 MHz) | external ADC | IUP |
| **MAX14866** | 8-ch HV mux | pic0rick, un0rick MUX |

See [`literature.md`](literature.md) for the broader ≤32-element component menus
(AFE58xx, AD927x, HV sources, etc.).
