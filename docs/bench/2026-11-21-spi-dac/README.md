# 2026-11-21 — SPI payload link + PIC DAC test signal (board 3, no piezo)

Firmware: **rp 1.1.4 / pic 1.1.1, proto 11** (commits of session 13, 2026-11-21). Board 3 (RP unique id 7D4466C63B374C98),
USB only, nothing on the transducer connectors. Design: `docs/claude/specs/2026-11-21-dac-spi-link-design.md`.
Commands sent with `python3 firmware/rp2354/tools/rpcli.py /dev/ttyACM0 "<cmd>" --wait=N` from the repo root.

## SPI link (linktest = PIC LFSR pattern, every word + CRC checked, then once over the UART)
| Command | Result |
|---|---|
| `linktest 20` (12.5 MHz) | 20/20 ok, 10.58 ms per 8202-byte frame (request + frame; wire 5.25 ms), UART copy identical (0.71 s) |
| `linktest 200 18.75` | 200/200 ok, 8.61 ms per frame |
| `linktest 500 18.75` | 500/500 ok (4.1 MB), 8.65 ms mean (8.648–8.665) |
| `linktest 50 25` | **0/50** (frame magic / crc errors): 25 MHz = the PIC client datasheet limit (SP10), no margin on board 3 |
Default kept at **12.5 MHz** (owner, 2026-11-21). ~5 ms of each transfer is the `SPIX` round trip on the 115 200 Bd UART
(reply line + PIC CRC), not the SPI wire time. Speed-up vs the UART payload: 0.71 s → 10.6 ms (×67).

## DAC test signal read back by ADC2 on the same pin (AD2AN3, acq input 19)
- `dac tri 512 3584 16` + `acq 4 0 19` over SPI → `tri_spi.txt`, `tri_spi.png`: period **24.70 ± 0.01 µs** (nominal
  24.58 µs = (hi−lo)·16/slope × 4 ns × 2, +0.5 %), codes 548..3543 (asked 512..3584; the DAC RC filter rounds the
  corners). Same over the UART (`link uart`): `tri_uart.txt`, 24.70 µs, 553..3547, `xfer=709527us`.
  `python3 analyze_tri.py tri_spi.txt [png]`.
- `dac sine 20000 1500 2048` + `acq 10 0 19 1` (20 Msps): `sine_div10_spi.txt/.png` — fit 19.884 kHz (SCCP3 secondary
  timer counts PRH + 2: fixed in pic 1.1.1 final, `CCP3PR = (u-2) << 16`), 1416 LSB amplitude, residual 15 LSB rms
  concentrated near the peaks (DAC ripple near its 5/95 % rails) → 36.5 dB SINAD.
- `dac sine 20000 800 2048`: `sine800_div10_spi.txt/.png` — residual 4.1 LSB rms, 42.3 dB SINAD (6.7 "ENOB" of DAC +
  ADC together): the DAC limits it, so it is a shape reference, **not** an ADC ENOB source.
- **Sine vs capture:** with the DMA sine running, `raw ACQ 10 0 19 1` came back `slow` 12/12 (triangle 12/12 ok, off 12/12
  ok); `acq 4 0 19` (25 Msps) is always `slow` (fill 226 µs): each 1 µs DMA update costs the capture DMA ~one sample.
  `sine800_div10_after_fix_slow.txt` = the RP's new message after 8 slow captures. The two earlier div-10 "ok" sine
  captures were just under the +5 % threshold and carry ~1 dropped sample per µs.
- `pe` over SPI (no piezo): `pe_spi.txt` — pulse fired, 1 shot, `link=spi@12.50MHz xfer=10572us`.

## USB
`udevadm info -n /dev/ttyACM0`: ID_VENDOR=kelu124, ID_MODEL=minUS_badge, ID_SERIAL_SHORT=7D4466C63B374C98, 2e8a:0009.
