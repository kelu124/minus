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
