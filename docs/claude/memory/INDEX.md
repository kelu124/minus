# Memory index

One line per memory file. Read this first to find the right topic.

- [0001-project-scope.md](0001-project-scope.md) — What "minus" is: minimal, single-channel, low-cost ultrasound imaging platform.
- [0002-working-conventions.md](0002-working-conventions.md) — How we log discussions and persist memory in this repo.
- [0003-systems-survey.md](0003-systems-survey.md) — Survey of lightweight ultrasound systems (17 datasheets + template + literature.md + design files).
- [0004-key-references.md](0004-key-references.md) — Anchor reviews (Jonveaux 2022, Weik 2026), SIG-WUS OXP catalog, un0rick.cc.
- [0005-minus-direction.md](0005-minus-direction.md) — Provisional direction + all locked owner requirements (RP2350, USB-C, 3–4 MHz, unipolar, badge, …).
- [0006-pricing-basis.md](0006-pricing-basis.md) — Parts pricing basis: LCSC at qty ~20–50 (workshop batch), JLCPCB-stocked.
- [0007-designA-devkit.md](0007-designA-devkit.md) — DesignA (cheap RP2354A+PIC32AK board) + DesignA-DK jumper-selected devkit; key decisions + the 2026-09-21 flaw review.
- [0008-devkit-minUS_10102026.md](0008-devkit-minUS_10102026.md) — Devkit as built (KiCad, 48-pin PIC on LCSC), inter-MCU pin map, RP→PIC reset/ICSP taps, 2026-10-26 flaws (R68/R69, R53/MCLR, JTAG), toolchain status, firmware/ layout.
- [0009-firmware-versioning.md](0009-firmware-versioning.md) — Firmware semver rule: owner = MAJOR.MINOR, Claude = PATCH; `version.h` + `firmware/VERSIONS.md`; repo skills list.
- [0010-pic32prog-study.md](0010-pic32prog-study.md) — kiffie pic32probe/pic32prog-kvh study (RP2040 ICSP dongle for MIPS PIC32): what transfers to our dsPIC33A-core PIC32AK (entry/physical layer only).
- [0012-rx-chain-oa2-gain.md](0012-rx-chain-oa2-gain.md) — RX chain OA1 → OA2 (U11 digipot gain ×1–×11, I2C 0x2E, `pot`/`AMP2`) → FE_A_OUT (AD2AN1 only); digipot caps OA2 at ~1 MHz (hardware TODO); how to measure the gain.
- [0011-adc-dma-throughput.md](0011-adc-dma-throughput.md) — Bench-proven PIC32AK throughput: ADC core 25 ns, DMA 50 ns (20 Msps ceiling), CPU loop 25 ns = duplicated reads (tone-proven 2026-11-02), acqil at the DMA ceiling, 200 MHz is rated not overclock; what it means for the 40 Msps goal.
- [0013-rx-lna-mmic.md](0013-rx-lna-mmic.md) — RX LNA for the next board redesign: BGA2817 MMIC (24 dB, 3.3 V, LCSC C2654187) ahead of OA1 + the FE-A bias/coupling fixes; PIC op-amp ≈ ×10/stage limit; 74HC4051 gain legs.
- [0014-board-minUS_07112026.md](0014-board-minUS_07112026.md) — New slim board (BGA2817 LNA + 74HC4052 gain mux) and its 2026-11-07 review: 4 must-fix items (floating mux selects, 330 pF LNA input cap, MCLR R17, input clamp).
- [0015-3d-renders.md](0015-3d-renders.md) — `hardware/render_3d.py`: kicad-cli top/bottom/angled renders; vendored EasyEDA models + stock substitutes; always omit 2×N/IDC headers and SMA.
- [0016-pulser-pulse-echo.md](0016-pulser-pulse-echo.md) — Board 3 pulser wiring/polarity, `pe` sync on RDY, ADC input codes, first echoes.
- [0017-noise-enob.md](0017-noise-enob.md) — Board 3 noise/ENOB: ADC 10.2–10.5 bits, period-4 pin pattern, chain 6.3–8.3 bits full band / 8.2–11.4 in band, front-end limited at max gain.
- [0018-datasheet.md](0018-datasheet.md) — Board 3 LaTeX datasheet: where it lives, how values/figures are generated, key measured facts.
- [0019-lessons-session-11.md](0019-lessons-session-11.md) — Lessons learnt: netlist-before-flash, lying net names, ADC phase luck + on-chip slow flag, align-before-average, fixed-pattern check, UF2 flashing race, rpcli timing, LaTeX pitfalls.
- [0020-python-library-and-comb-phase.md](0020-python-library-and-comb-phase.md) — Python library framing + fwsync rule/hooks, minus v1.1 naming, LP5562 init, E3 comb phase: uniform over 1 sample + whole-sample slips.
- [0021-spi-link-and-dac.md](0021-spi-link-and-dac.md) — proto 11/12 (SPIX on RDY, SPI mode 1, 25 MHz ok; slow lock = per-PLL-lock state, self-heal): capture payload over SPI (frame + CRC, 12.5 MHz ok / 25 fails, UART fallback, linktest) + PIC DAC1 test signal on DACOUT1 (triangle = in-capture reference, DMA sine breaks captures), USB strings.
- [0022-lessons-session-13.md](0022-lessons-session-13.md) — Lessons: datasheet lives in the owner Trash (read in place), header names over datasheet examples, 16 KB RAM, DMA contention during capture, SCCP dual-16 DMA trigger (PRH+2), FFT bins vs crossings, KiCad-by-script checks, owner WIP hardware files.
