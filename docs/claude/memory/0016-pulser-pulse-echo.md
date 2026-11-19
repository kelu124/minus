# 0016 — Board 3 pulser and pulse-echo (2026-11-19, session 11)

**Status:** working on hardware · type: project
- Pulser: GPIO8 HIGH = Q2 N-FET → GND; GPIO9 LOW = Q1 P-FET → +5 V (net names PWM_H/PWM_L are swapped vs function).
  Idle = GPIO8 0 / GPIO9 1. Never 0b01 (GPIO8 1 + GPIO9 0 = shoot-through). RP pad default pull-down on GPIO9 = Q1 on at boot.
- `firmware/rp2354/pulser.pio` (pio1 SM0) fires on the PIC's RDY rising edge; PIC raises RDY one instruction before SCCP1 ON,
  so sample 0 ≈ pulse start (main bang visible from sample 0–1). Phases hi+2 / dead+4 / lo+2 cycles at 150 MHz.
- ADC input codes (PIC ≥ 0.1.22): 0..15 ADC1, 16..31 ADC2. Board 3: 25 AD2AN9 filtered node (default), 17 OA2OUT, 0 OA1OUT,
  1 LNA out. DMA trigger ADC2 ch0 = 0x40.
- First result: echoes every 40.2 µs, ~3.3 MHz, OA2 clips first echo at the reset mux gain (Rf 2.2 k, ≈ ×3.5 per stage).
Related: [[0014-board-minUS_07112026]], [[0011-adc-dma-throughput]], `bench/2026-11-19-pe/`.
