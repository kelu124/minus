# systems — lightweight ultrasound acquisition survey

A survey of "lightweight" / low-cost single- and few-channel ultrasound
acquisition designs, used as background for **minus**. Source: the
[wulrick extended platform survey](https://github.com/kelu124/wulrick#othersystems-extended-platform-survey)
and its `OtherSystems/` files, plus each system's primary papers/repos.

- **[`TEMPLATE.md`](TEMPLATE.md)** — the datasheet template. Copy into a new
  subfolder as `<slug>/<slug>.md` and fill it in. Covers MCU/FPGA, pulser
  (polarity/voltage), acquisition route, ADC, gain/TGC, connectivity bandwidth,
  wireless, channel scheme, performance, and power.
- One subfolder per design/product.

## Systems at a glance

| System | Year | Arch | Channels | Pulser | ADC | Gain/TGC | Link | Power | Sheet |
|--------|------|------|----------|--------|-----|----------|------|-------|-------|
| EchoLite | 2025 | MCU | 1 | ? | ? | ? | ? | 33 mW | [echolite](echolite/echolite.md) |
| PuLsE | 2025 | MCU (M4) | 1 | <15 V est. | integ., low-rate | none (analog envelope) | ? | **5.8 mW** | [pulse](pulse/pulse.md) |
| USoP | 2023 | MCU (flex) | 1 | ~10–30 V | integ. | ? | BT | 614 mW | [usop](usop/usop.md) |
| WULPUS | 2022 | MCU (MSP430) | 8 mux | +15 V unipolar | 8 Msps integ. | fixed PGA | BLE 320 kbps | 22 mW | [wulpus](wulpus/wulpus.md) |
| WULPUS PRO | 2026 | MCU (MSP430) | 16 mux | ±30 V | 8 Msps integ. | VGA + TGC (AD8338) | BLE/Wi-Fi | 35–58 mW | [wulpus-pro](wulpus-pro/wulpus-pro.md) |
| pic0rick | 2024 | MCU (RP2040) | 1 (+8 opt) | ±24 V bipolar | 65 Msps ext. | TGC (AD8331+DAC) | USB | ~300–400 mW | [pic0rick](pic0rick/pic0rick.md) |
| TinyProbe | 2025 | FPGA | 32 parallel | 64 Vpp (±32 V) | 30 Msps ext. | programmable TGC | Wi-Fi 21.6 Mb/s | <1 W | [tinyprobe](tinyprobe/tinyprobe.md) |

*`?` = not disclosed / to confirm. See each sheet for source tags and detail.*

## Reading the design space (first pass)

- **Analog-envelope, ultra-low-power branch:** PuLsE (5.8 mW). Cheapest/lowest
  power, but discards RF phase — envelope-only.
- **Integrated-ADC MCU branch:** WULPUS / WULPUS PRO. 8 Msps integrated ADC caps
  end-to-end BW at ~1.4 MHz (≤3 MHz transducers). WULPUS PRO adds analog TGC
  (AD8338) and a dual ±30 V supply (LT3463).
- **External high-speed-ADC branch:** pic0rick (65 Msps) — high frequency, USB,
  variable TGC, at higher power. The incumbent open single-channel board.
- **FPGA multi-channel branch:** TinyProbe (32 ch, Wi-Fi) — the high-capability,
  high-power counter-example.
- **Integration-first branch:** USoP — flexible skin patch, power spent on
  conformability rather than efficiency.

**For minus** (minimal, single-channel, cheap), the most relevant references are
pic0rick (open single-channel baseline to trim), WULPUS (minimal-power A-mode
template), and PuLsE (how far analog-envelope minimalism can go).
