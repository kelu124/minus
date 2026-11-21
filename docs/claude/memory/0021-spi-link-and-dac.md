# 0021 — SPI capture payload link + PIC DAC test signal (2026-11-21, session 13)

**Status:** current · rp 1.1.5 / pic 1.1.2, **proto 12** (was 11 on 2026-11-21) · design `docs/claude/specs/2026-11-21-dac-spi-link-design.md` ·
bench `docs/bench/2026-11-21-spi-dac/`

## SPI payload link
- The PIC no longer pushes the 8190-byte payload after `ACQ`/`ACQCPU`/`ACQIL`: the RP pulls it with `SPIX` (SPI frame) or
  `UTX` (old UART stream). Frame: `A5 5A 'M' '1'`, n u16, seq u16, n × u16 LE, CRC-32/IEEE LE (12 + 2n B). The PIC replies
  `SPIX n seq crc` on the UART after preloading its FIFO, then feeds SPI1 from a CPU loop (16 KB RAM: no frame copy).
- Wiring (board 3, no change): RP SPI0 master GPIO2 SCK / GPIO4 MISO / GPIO3 MOSI (unused) / GPIO5 CS (SIO) ↔ PIC SPI1 client
  RD1 SCK1 (RPINR10 SCK1R 50) / RC2 SDO1 (RPOR8 RP35R = 13) / RD2 SDI1 (DISSDI) / RD0 SS1 (SS1R 49); mode 0 (CKP 0, CKE 1).
- Bench: 12.5 MHz (default, owner) and 18.75 MHz clean (500/500 frames), **25 MHz fails every frame** (PIC client limit SP10).
  10.6 ms per capture at 12.5 MHz; ~5 ms of that is the `SPIX` UART round trip, not SPI. RP clock steps: 150 MHz / even
  divisor → 25, 18.75, 15, 12.5 MHz.
- `linktest [n [MHz]]` = `XTEST seed` (16-bit Galois LFSR 0xB400 in acq_buf) + SPIX + per-word check + one UART comparison.

## DAC1 test signal (DACOUT1 = U9 pin 3 = RA1 = AD2AN3 → `acq … 19`; AD1AN7 → 7; board 3 H6.16; v1.2 + RP GPIO26/ADC0)
- PDM DAC + RC filter, codes 0x0CD..0xF32 (5–95 % AVDD), settling 0.75 µs typ / 2 µs max. Clock CLKGEN7 = **PLL2 VCO-div
  500 MHz** (FRC × 125 = 1000 MHz VCO, VCO2DIV 1, NOSC 8), so PLL1 (CPU 200 / ADC 250) is untouched; started lazily on the
  first `DAC` command. Factory trims FPDMDAC @ 0x7F20B0 → DACCTRL1 (POSINLADJ 21:16, NEGINLADJ 14:8, DNLADJ 4:0). Register
  names in the header are `DAC1SLPCON` / `DAC1SLPDAT` (the datasheet examples say SLP1CON).
- `tri lo hi slp`: hardware Triangle Wave mode; half period = (hi−lo)·16/slp × 4 ns. Bench: 512..3584 slope 16 → 24.70 µs
  (nominal 24.58), read 548..3543. **No bus traffic: the reference to use during captures.**
- `sine hz [amp [mid]]`: DMA2 (repeated one-shot, 32-bit) table ≤ 128 points → DAC1DAT, triggered by **SCCP3 in dual 16-bit
  timer mode** (the secondary timer's match raises CCP3IF = DMA trigger 0x1A; DMA cannot trigger on CCTx); the secondary
  period is **PRH + 2** counts. **Each update costs the capture DMA ~1 sample → 20/25 Msps captures come back `slow`** while
  it runs. Best quality 42 dB SINAD (amp 800): a shape reference, not an ADC ENOB source.

## Also
- USB descriptors: manufacturer `kelu124`, product `minUS badge` (CMake `USBD_MANUFACTURER`/`USBD_PRODUCT`), serial = RP unique
  id, VID:PID 2E8A:0009 (the library finds the port by VID only).
- `acq` now prints a line when all 8 tries were `slow` (it used to print nothing).
- Library: `Minus.link()`, `linktest()`, `dac()`; `Capture.link` / `.xfer_us` from the `# acq` line tail; parsers use
  `_fail_on_usage` because their normal lines start with `<cmd>:`.

## Proto 12 (2026-11-22, rp 1.1.5 / pic 1.1.2)
- `SPIX` has **no reply line**: the PIC drops RDY, preloads its FIFO, raises RDY ("clock now"), computes the CRC while
  feeding, drops RDY when done. The RP waits for the `SPIX\n` to leave its UART + 20 us, then for RDY high (5 ms max).
  SPIX → RDY = 455 us (5 UART characters).
- **SPI mode 1** (RP CPHA 1, PIC CKE 0): the PL022 in mode 0 pulses its frame signal between bytes (+1 bit each, +19 %).
  12.5 MHz → 5.7 ms per capture; 18.75 → 3.96; **25 MHz now clean** (3000/3000 frames) — mode 1 samples on the other edge.
- Host side: an `acq` took 185 ms end to end; 50 ms was `link_flush_rx`'s idle window (now 2 ms) and the rest the 24.8 KB
  of text at ~200 kB/s → 4 KB blocks give 107 ms. The cap left is pico-sdk's hard-coded 256-byte CDC TX buffer
  (~270 kB/s; a `-DCFG_TUD_CDC_TX_BUFSIZE` has no effect). Next lever: a compact output format (base64 ~11 KB).

## Slow lock = per-PLL-lock state (bench docs/bench/2026-11-22-slowlock/)
- After a PLL1 lock the ADC either never or almost always (85–100 %) locks to the 40/60/60 ns pattern; ~half the boots;
  plus a rarer mixed state (~35 %). Re-sourcing CLKGEN12 does not change it; a new PLL1 lock does.
- pic 1.1.2 re-locks at boot until 8 test captures are all uniform (≤ 12 locks): 19/20 boots clean; `raw LOCK?` reports it.
  The RP sends `RELOCK` after 3 slow captures in a row and restores UGE (RELOCK re-runs acq_init).

## ADC extras for pulse-echo (2026-11-22, rp 1.1.6 / pic 1.1.3, proto 13; design docs/claude/specs/2026-11-22-adc-extras-design.md)
- `acqos 4|16`: MODE 11 oversampling, ACCBRST, TRG2SRC 2; result is **scaled** (4 → 13-bit = 2× a 12-bit code, 16 → 14-bit
  = 4×), not a raw sum; trigger period must cover N·32 + ~48 ns (div 35 / 113 → 181 / 560 ns measured). Noise ÷2.1 / ÷3.1.
  64/256 not offered: fill 8.6 / 34 ms > Timer1's 5.2 ms (80 ns × 16 bit).
- `tof`: CMPMOD 001 (out of [lo, hi]) on ADnCH0CMPLO/HI, flag ADnCMPSTAT.CH0CMP (cleared before the capture), then a CPU
  scan for the first crossing after the blank + the peak in 64 samples. 8.9 ms end to end.
- `env`: |x − mean| integrate-and-dump over dec 4..64, running u32 sum in acq_buf1 (1023 words = dec ≥ 4), average (1/16 LSB)
  written back into acq_buf for SPIX. Envelopes can be averaged across shots despite the random comb phase (E3).
- Without a piezo all three are checked with the DAC on input 19 (`docs/bench/2026-11-22-adc-extras/`).
