# 2026-11-19 — first pulse-echo on board 3 (minUS_08112026, RP id 7D4466C63B374C98)

Firmware rp 0.1.30 / pic 0.1.22 (proto 7). Pulse +5 V 200 ns / both off 27 ns / GND 500 ns / released,
fired by the RP PIO on the PIC's RDY rise (= ADC start). 4095 samples at 24.86 Msps (40.2 ns), single conversions,
4052 mux at reset state (S0 = S1 = 0 → Rf 2.2 k on both stages), op amps external gain, HPEN.

| File | Command | Input |
|---|---|---|
| `pe_in25.txt` | `pe 200 500 25` | AD2AN9 = PIC32_ADC (OA2OUT after R67/C86/R68/C87) |
| `pe_in17.txt` | `pe 200 500 17` | AD2AN1 = OA2OUT |
| `pe_in0.txt`  | `pe 200 500 0`  | AD1AN0 = OA1OUT |
| `pe_in1.txt`  | `pe 200 500 1`  | AD1AN1 = OA1IN+ (LNA out after C40) |
| `acq_in25_nopulse.txt` | `acq 4 0 25 1` | AD2AN9, no pulse (noise floor) |

Each file = second of two identical runs (the first capture after an input change came back at 18 Msps twice).
Capture: `python3 firmware/rp2354/tools/rpcli.py /dev/ttyACM0 "pe 200 500 25" --wait=4 > pe_in25.txt`.
Plots: `/usr/bin/python3 bench/2026-11-19-pe/plot_pe.py bench/2026-11-19-pe` → `pe_full.png`, `pe_zoom.png` (first 12 µs).

Result: echo train every 40.2 µs (31 mm one way at 1540 m/s), centre ~3.3 MHz (first) → 2.7 MHz (later).
Peak-to-peak (LSB) at 40.7 / 80.5 / 120.7 / 161 µs: in25 3890 (clipped) / 2717 / 869 / 312; in0 2362 / 797 / 293 / 125;
in1 665 / 204 / 76 / –. OA1 stage ≈ ×3.5 (in0/in1), OA2 stage ≈ ×3.7. Noise sd: in25 22.8, in0 17.5, in1 4.1 LSB.
Main bang + ringing until ~6 µs (~5 mm dead zone); in1 baseline sits at 1321 (1.06 V), not mid-rail.
