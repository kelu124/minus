# 0003 — Lightweight ultrasound systems survey

**Status:** current (as of 2026-09-17), first pass

Background survey of lightweight/low-cost ultrasound acquisition designs, to
inform *minus*. Lives in [`systems/`](../../../systems/README.md); template at
`systems/TEMPLATE.md`, one subfolder per design.

Source: wulrick "extended platform survey"
(github.com/kelu124/wulrick, `OtherSystems/`) + each system's primary papers/repos.

## Systems captured (7)

| System | Arch | Ch | Pulser | ADC | Gain | Link | Power |
|--------|------|----|--------|-----|------|------|-------|
| EchoLite | MCU | 1 | ? | ? | ? | ? | 33 mW |
| PuLsE | MCU M4 | 1 | <15 V est. | integ. low-rate | none (analog envelope) | ? | 5.8 mW |
| USoP | MCU flex | 1 | ~10–30 V | integ. | ? | BT | 614 mW |
| WULPUS | MSP430 | 8 mux | +15 V unipolar | 8 Msps integ. | fixed PGA | BLE 320 kbps | 22 mW |
| WULPUS PRO | MSP430 | 16 mux | ±30 V | 8 Msps integ. | VGA+TGC AD8338 | BLE/WiFi | 35–58 mW |
| pic0rick | RP2040 | 1(+8) | ±24 V bipolar | 65 Msps ext. | TGC AD8331+DAC | USB | ~300–400 mW |
| TinyProbe | FPGA | 32 || | 64 Vpp | 30 Msps ext. | prog. TGC | WiFi 21.6 Mb/s | <1 W |

## Design-space takeaways (first pass)

- Four branches: analog-envelope ultra-low-power (PuLsE); integrated-ADC MCU
  (WULPUS/PRO, capped ~1.4 MHz BW by 8 Msps ADC); external high-speed-ADC
  (pic0rick 65 Msps, high freq, USB); FPGA multi-channel (TinyProbe).
- Most relevant to *minus*: **pic0rick** (open single-channel baseline to trim),
  **WULPUS** (minimal-power A-mode), **PuLsE** (analog-envelope minimalism limit).
- Candidate parts noted: AD8338 (low-power TGC VGA), LT3463 (dual ±30 V supply),
  AD8331+MCP4812 DAC (pic0rick TGC), MD0100/MD0101 T/R switch.

## Open confirmations

- EchoLite: paper not public; nearly all fields unconfirmed.
- PuLsE/USoP: closed hardware; MCU part, TX voltage, wireless partly unknown.
- pic0rick dimensions/SNR: not characterized here yet.

See [[0001-project-scope]] for how this feeds the *minus* design.
