# 2026-11-21 — PIC DAC test signal + RP↔PIC SPI data link (design)

Owner request (session 13): (1) a PIC test function that puts a sine or a known wave on DACOUT1; (2) an SPI bus for
the PIC to send the captured signal back to the RP; test both **without a piezo** (board 3 / v1.1, no hardware change).

## Why
The 115 200 Bd UART carries 8190 B per capture = **0.71 s**; SPI (wired on board 3, unused) at ≥ 10 MHz makes it
a few ms → live A-scan, host averaging. The DAC gives a known waveform that the capture ADC can read on the same
pin (no piezo, no wiring), so the whole capture → link → USB path can be checked with a signal of known shape.

## Facts it rests on (DS70005592, device header, board 3 netlist)
- DACOUT1 = U9 pin 3 (RA1), also **AD2AN3** (acq input code 19) and AD1AN7 (code 7); on board 3 only H6.16
  (v1.2: also RP GPIO26/ADC0). PDM DAC + RC filter, 12-bit, codes 0x0CD..0xF32 (5–95 % AVDD), settling 750 ns typ /
  2 µs max (DA07), output ≤ 3 mA, ≤ 30 pF. CLKGEN7 = DAC clock, 500 MHz in the datasheet examples; slope step
  T_DAC = 2/F_DAC = 4 ns. Triangle mode (SLP1CON.TWME + SLOPEN) runs in hardware between DACLOW and DACDAT.
  Factory calibration word FPDMDAC @ 0x7F20B0 (POSINLADJ 21:16, NEGINLADJ 14:8, DNLADJ 4:0) → DACCTRL1.
- SPI client max SCK **25 MHz** with PPS pins (SP10). Pins: SCK1 ← RP50 (RD1), SDI1 ← RP51 (RD2), SS1 ← RP49 (RD0)
  (RPINR10), SDO1 (output fn 13) → RP35 (RC2, RPOR8). RP: SPI0 GPIO2 SCK / 3 MOSI / 4 MISO, CS = GPIO5 (SIO).
- PIC RAM = 16 KB (0x4000–0x7FFF), ~12 KB already acq_buf/acq_buf1 → no frame copy; sine table ≤ 128 points.
- Capture DMA runs at its 40 ns bus ceiling (memory 0011): anything else on the bus during `acq` can drop samples.

## Decisions
- **DAC modes** (PIC link `DAC …`, RP CLI `dac …`): `off`; `dc <code>`; `tri <lo> <hi> <step>` (hardware triangle,
  **no bus traffic → safe during any capture**); `sine <hz> [amp [mid]]` (DMA2 streams a ≤ 128-point table into
  DAC1DAT on SCCP3 period matches, update period ≥ 1 µs; one DMA transfer per µs **may cost capture samples at the
  25 Msps default** — measured, not assumed). DAC clock from **PLL2** (8 MHz × 125 = 1000 MHz VCO, Fout 500 MHz) so
  PLL1 (CPU 200 / ADC 250) is untouched; PLL2 waits are bounded, DAC reports `noclk` if PLL2 fails.
- **Payload is pulled, never pushed** (proto 10 → **11**): `ACQ`, `ACQCPU`, `ACQIL` reply with the header line only;
  the RP then asks for the payload with `SPIX` (SPI) or `UTX` (UART, the old byte stream) — the fallback and the
  reference for bit-exact comparison. The PIC keeps the last capture's length.
- **SPI frame** (PIC client, mode 0, 8-bit, MSB first, SSEN): `A5 5A 'M' '1'`, n (u16 LE), seq (u16 LE), 2n payload
  bytes (u16 LE samples), CRC-32/IEEE (LE) of all preceding bytes = 12 + 2n bytes (8202 B for 4095 samples).
  `SPIX` → PIC computes the CRC, preloads the TX FIFO, replies `SPIX <n> <seq> <crc hex>`, then feeds the FIFO from a
  CPU loop until all bytes went out or ~50 ms passed (then flushes). The RP checks magic, n, seq, CRC against both the
  frame and the reply; on any mismatch it falls back to `UTX` and counts the error.
- **Link test without a piezo**: `XTEST <seed>` fills acq_buf with a 16-bit LFSR pattern (no capture); RP
  `linktest [count [MHz]]` pulls it `count` times, checks every word + CRC, reports errors and throughput, and once
  compares SPI vs UART bytes. Real-signal check: `dac tri …` + `acq 4 0 19` (AD2AN3) over SPI vs UART.
- RP CLI: `link [uart|spi [MHz]]` (default spi 12.5 MHz; shows counters), `dac …`, `linktest …`. Output of `acq`/`pe`
  unchanged except the `# acq` line gains `link=spi@12.5MHz xfer=…us` (library parser tolerant, checked).
- Versions: pic 1.1.0 → 1.1.1, rp 1.1.3 → 1.1.4, proto 11; library + fixture + notebooks re-synced (`fwsync`).

## Not now
RP ADC0 read of the DAC (v1.2 trace), binary host mode, DMA-driven SPI TX on the PIC, PWM3 pulser drive.
