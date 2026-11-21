# 2026-11-22 — the PIC "slow" ADC lock is a per-PLL-lock state (and a self-heal)

Board 3 (RP unique id 7D4466C63B374C98), no piezo, USB only. "slow" = the PIC's ACQ status when the capture fill exceeds the
expected time by > 5 % (ADC locked to a 40/60/60 ns sample pattern instead of a uniform 40 ns; memory 0011/0020, datasheet E2).
Scripts run from the repo root with `/usr/bin/python3`; each writes a timestamped JSON next to itself.

| Step | Firmware | Script | Result |
|---|---|---|---|
| found by accident | pic 1.1.2 (pre-fix) | `raw ACQ 4 0 <in> 1` × 30 | after hours of use: in 25/19/17 slow 30/30, in 0 slow 7/30; a PIC reset → 30/30 ok on every input, with or without the DAC / PLL2 |
| not the SPI link | same | 5 × acq, linktest 50 @12.5 and @25 | 20/20 ok before and after each |
| **per boot** | same | `per_boot.py 12 20` | **6/12 boots: 100 % ok; 6/12: 85–100 % slow until the next reset** (`per_boot_*.json`, first file) |
| re-sourcing CLKGEN12 (SCCP clock) | same | `resync.py 12` | does not heal a bad boot (still 60–90 % slow) → the phase that matters is inside PLL1's dividers (CPU/SCCP = VCO/5, ADC = VCO/4) |
| self-heal v1 (4 test captures, < 2 slow) | pic 1.1.2 | `per_boot.py 12 20` | 10/12 clean, 2 boots in a *mixed* state (30–45 % slow) slipped through |
| **self-heal v2** (8 test captures, 0 slow, ≤ 12 locks) | pic 1.1.2 | `per_boot.py 20 20` | **19/20 boots clean** (locks needed: 1–10), 1 mixed boot (35/20 % slow) |
| end to end, + RP `RELOCK` after 3 slow | rp 1.1.5 / pic 1.1.2 | `acq_per_boot.py 20 5` | **100/100 library `acq()` ok**, 0 automatic re-locks needed in this run |

The self-heal: `firmware/pic32/main.c` `lock_until_uniform()` (CPU/ADC/SCCP clocks to FRC, PLL1 off, `clocks_init()` again,
`acq_init()` again); `raw LOCK?` reports `LOCK <locks tried> <slow of 8>`; `RELOCK` redoes it.
Root cause (why some divider phases make the 32 ns ADC lock to 40/60/60 on 20 ns triggers) is still open; the comb slips
of memory 0020 (E3) may share it — re-measure them on a good lock.
