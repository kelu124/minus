# 2026-11-22 — PIC ADC extras for pulse-echo (acqos / tof / env), board 3, no piezo

Firmware **rp 1.1.6 / pic 1.1.3, proto 13**. Design: `docs/claude/specs/2026-11-22-adc-extras-design.md`. Every check reads
the PIC DAC on AD2AN3 (input 19). Scripts from the repo root with `/usr/bin/python3`.

## Oversampling (`acqos`) — `os_noise.py 2048 5` → `os_noise_2048.json`
| Mode | raw at DC 2048 | noise (12-bit LSB rms) | dt | window |
|---|---|---|---|---|
| `acq 4 0 19 1` | 2030 | 1.16 | 40.2 ns | 164.6 µs |
| `acqos 4 19` | 4064 (= 2 × 12-bit, 13-bit) | 0.55 | 180.9 ns | 740.9 µs |
| `acqos 16 19` | 8122 (= 4 × 12-bit, 14-bit) | 0.37 | 560.4 ns | 2294.7 µs |
√4 = 2 → measured 2.1; √16 = 4 → 3.1 (approaching the DAC/pin floor). Notebook 02 run: 0.85 / 0.53 / 0.33.

## Time of flight (`tof`) — manual commands (rpcli), and `tests/test_minus.py::test_adc_extras`
- DC 3100, `tof 1000 0 19 2048` → crossing at sample 0, hardware comparator tripped. DC 2900 → none, comparator quiet.
- Triangle 512..3584, ref 2048, thr 1000 → first crossing at sample 105, peak 1485 LSB at 157 (52 samples later = the
  slope from 3048 to the 3540 top at ~9.5 LSB/sample); blank 8000 ns → search starts at sample 200.
- `tof` = **8.9 ms** end to end vs 106 ms for `acq` (one line instead of the A-line).

## Envelope (`env`) — `env_check.py 8` → `env_check_dec8.json`
- Triangle, dec 8 (321.6 ns per value, 511 values): 1 shot → period 12.32 µs (half the triangle's 24.7), mean 772 LSB
  (expected ~750), max 1490; 16 shots → std 441 → 161 LSB (random triangle phase per shot averages out — real echoes keep
  their timing). `env 8 1` = 20.7 ms, `env 8 16` = 122 ms end to end.
