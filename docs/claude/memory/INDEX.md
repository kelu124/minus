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
- [0011-adc-dma-throughput.md](0011-adc-dma-throughput.md) — Bench-proven PIC32AK throughput: ADC core 25 ns, DMA 50 ns (20 Msps ceiling), CPU loop 25 ns marginal, tight SFR polling duplicates samples; what it means for the 40 Msps goal.
