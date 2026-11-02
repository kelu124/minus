# 2026-11-02 — 1 MHz square wave at the PIC32_ADC node (RF7)

Board 2, rp 0.1.27 / pic 0.1.19. DS203 1 MHz square into RF7 (= H6, AD1AN9). One value per line,
`#` header from `rpcli.py`. `period.py <csv…>` prints rise-to-rise distances (samples per 1 MHz
period = effective Msps), duplicate-pair counts and the even/odd (CH0/CH1) split for `acqil`.

| file | command | result |
| --- | --- | --- |
| tone20_acq8.csv, tone20_acq8_b.csv, r2_acq8_before.csv | `acq 8 0 9` | 20/period, clean |
| r2_acq8_after.csv (and the first boot capture, not kept) | `acq 8 0 9` | fill 231.6 µs, periods 13–17: intermittent fault |
| tone_acq4.csv, r2_acq4.csv | `acq 4 0 9` | 20/period: DMA ceiling |
| tone_acqcpu_p{0,1,2,5}.csv, r2_acqcpu_p{4,6,8}_*.csv, r2_acqcpu_p3_21677.csv | `acqcpu 12 1 0 <p>` | 40/period, every value twice |
| tone_acqcpu_p3.csv, r2_acqcpu_p3_3527.csv, r2_acqcpu_p7_*.csv | `acqcpu 12 1 0 <3|7>` | 40/period, no duplicates, +425 LSB offset |
| tone_acqil16.csv, r2_acqil16_{a,b}.csv, r2_acqil16_off5.csv | `acqil 16 [5]` | CH1 at 200 ns (DMA1 loses triggers), fill 412 µs |
| r2_acqil16_c.csv | `acqil 16` | the good case: 20/period, fill 206 µs |

Discussion: `docs/claude/log/2026-11-02-session-08.md`; durable facts: memory 0011.

## Part 2 — after the clock change (pic 0.1.20 / rp 0.1.28: CPU 200 MHz, ADC 250 MHz, 5 ns `div` counts, 80 ns ticks)

| file | command | result |
| --- | --- | --- |
| clk200_acq_4_0_9.csv, clk200b_acq_4_0_9*.csv, clk200c_acq_default.csv | `acq 4 0 9` / `acq` (new default) | fill 164.6 µs, 25/period, even/odd steps equal: **uniform 25 Msps** |
| clk200_acq_8_0_9*.csv, clk200b_acq_8_0_9*.csv | `acq 8 0 9` (40 ns triggers) | fill 226.4 µs, 18–19/period: DMA razor edge, ~1 in 4.5 triggers dropped |
| clk200b_acq_5_0_9.csv, clk200_acq_6_0_9.csv | `acq 5` / `acq 6` | 185 µs, irregular |
| clk200_acq_10_0_9.csv | `acq 10 0 9` | 205.8 µs, 20/period: clean 20 Msps |
| clk200_acq_8_0_9_2.csv, clk200_acq_16_0_9_2.csv, clk200_acq8_c.csv | `navg 2` (the last one by accident: navg persists) | 442 µs, scrambled: 2-sum needs div ≥ 21 |
| clk200_acqil_2*.csv | `acqil 20/21/24` | 412–495 µs, scrambled: parked until the ADC clock is back to 320 MHz (PLL2) |
| clk200_acqcpu_12_1_4_0.csv, clk200b_acqcpu_12_1_4_*.csv | `acqcpu 12 1 4 <phase>` after `acq 4` | 164 µs, 25/period; phase 0 = 26 % duplicates, phase 2 clean |
| clk200_acqcpu_12_1_0_0.csv, clk200_acqcpu_12_1_1_0.csv | 4-cycle reads / gap 1 | 64 % duplicates / generic NOP loop, meaningless |
