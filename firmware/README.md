# minus devkit firmware (hardware/minUS_10102026)

Two MCUs, two firmwares:

| Dir | Chip | Toolchain | Output | Status |
|-----|------|-----------|--------|--------|
| `rp2354/` | **RP2354A** (U1, QFN-60, 2 MB in-package flash) | pico-sdk ≥ 2.0 + arm-none-eabi-gcc + CMake/Ninja (all installed) | `build/minus_rp.uf2` (embeds the PIC hex) | **builds** (pico-sdk 2.1.0, picotool 2.3.0) |
| `pic32/`  | **PIC32AK1216GC41048** (U2, TQFP-48, LCSC C46545915) | Microchip **XC-DSC 3.31.01** + MPLAB X 6.35 `ipecmd` + PIC32AK-GC_DFP 1.1.53 (all installed) | `build/minus_pic.hex` | **builds** (~7 kB code, 36 B RAM); not yet flashed |

Step 1 (this code) only proves the two chips can talk: UART ping/pong + the GPIO handshake
lines + the PIC reset tap. Everything else (ADC capture, SPI streaming, pulser, ICSP
programmer) comes after the link is confirmed on real hardware.

## Inter-MCU wiring (from the schematic netlist, `kicad-cli sch export netlist`)

| Net | RP2354A | PIC32AK | Notes |
|-----|---------|---------|-------|
| `UART_TX` | GPIO16 (UART0 TX) | RC6 / **RP39**, pin 25 (→ PIC U1RX via PPS) | also on H2.7 and CN1.7 (sniff with a USB-UART). Net names are RP-side! |
| `UART_RX` | GPIO17 (UART0 RX) | RC7 / **RP40**, pin 26 (← PIC U1TX via PPS) | also on H2.8 and CN1.9 |
| `SPI_CLK` | GPIO2 (SPI0 SCK) | RD1 / RP50 (**TCK**) | shared with MCP4131 U12/U14 |
| `SPI_MOSI` | GPIO3 (SPI0 TX) | RD2 / RP51 (**TDO**) | **R68‖R69 = 50 Ω to MISO — see flaw 1** |
| `SPI_MISO` | GPIO4 (SPI0 RX) | RC2 / RP35 (PGC3) | MCP4131 SDI/SDO also here |
| `SPI_CS` | GPIO5 | RD0 / RP49 (→ SS1 via PPS) | PIC = SPI client |
| `TRIG` | GPIO6 (out) | RA0 / RP1 | RP → PIC trigger / GPIO |
| `RDY` | GPIO7 (in) | RA7 / RP8 | PIC → RP "data ready" / GPIO |
| `SDA`/`SCL` | GPIO0/1 (I2C0) | RD8 / RD7 (ASDA2/ASCL2) | shared with OLED, MCP4531×2, MCP4728; **one master only** (RP) |
| `PGC1` | GPIO21 via R56 (0 Ω) | RB4 | also J1.5 via R10 47 Ω (and RP SWDIO via R18!) |
| `PGD1` | GPIO22 via R57 (0 Ω) | RB3 | also J1.4 via R8 47 Ω (and RP SWCLK via R17!) |
| `MCLR` | GPIO24 via R53 (4.7 kΩ) | pin 48 via R9 442 Ω | R5 10 kΩ pull-up; C31 470 nF behind solder jumper JP1; J1.1 direct |

Other PIC pins used: RC5 → LED2 (red, via 330 Ω); RD4 ← SW3 (button, 10 k pull-up);
RC0/RC1 (OSC) only go to H2 → the PIC **runs on its internal FRC** (8 MHz, ±1.5 %).
RP GPIO10 → WS2812 (U5) **and** SK6812 (LED1) DIN **in parallel** (same colour on both; 5 V
parts driven at 3.3 V — WS2812 VIH is 0.7·VDD = 3.5 V, so expect marginal/no response from U5).

## Does the RP2354 control the PIC32?

Yes, three ways:
1. **Reset**: GPIO24 → MCLR (open-drain style in firmware: drive low, release to Hi-Z).
2. **ICSP programming**: GPIO21 = PGC1, GPIO22 = PGD1, GPIO24 = MCLR. The protocol
   (DS70005583 §2–3) is a plain 2-wire bit-bang: entry = MCLR low → key 0x8A12C2B2 on PGD
   with 32 PGC clocks → MCLR high → 2×34 clocks; then 2-bit commands + 32-bit shifts that
   execute CPU instructions / read VISI / write W0-indexed memory. **Implemented** in
   `rp2354/pic_icsp.c` (bit-banged GPIO, ~1 MHz; bulk erase §3.1, quadword program §3.3,
   read §3.5) and exposed as the `pic …` CLI commands. The PIC hex is converted by
   `rp2354/tools/hex2c.py` into `build/pic_image.c` at RP build time, so one UF2 carries both
   firmwares. **Untested on hardware** until a board with the R53/JP1 fixes exists.
3. **Run-time**: TRIG/RDY GPIOs, UART, SPI (RP master), shared I²C.

**But the as-built MCLR network defeats 1 and 2** (flaw 2 below) until R53 is changed.

## Hardware flaws found while reading the schematic (fix before trusting the link)

1. **R68 ‖ R69 (2 × 100 Ω) tie SPI_MOSI to SPI_MISO = 50 Ω short.** They are there so the
   MCP4131's single SDI/SDO pin (on MISO) receives MOSI data, but when the PIC drives MISO
   while the RP drives MOSI they fight through 50 Ω (~66 mA). → **Keep one resistor, remove
   the other, and raise it to 1–4.7 kΩ.** Do not remove both: the digipots would never see
   MOSI and writes would stop working. (Bus ownership: RP is the only digipot master; the
   PIC's SPI/I²C pins stay Hi-Z.)
2. **MCLR cannot be pulled low by GPIO24.** R53 = 4.7 kΩ against R5 = 10 kΩ pull-up gives
   3.3·4.7/14.7 ≈ **1.05 V**, above the PIC's VIL max of 0.2·VDD = **0.66 V** (DS70005583
   Table 2-2). → **Fit R53 = 0 Ω (≤ 470 Ω)**. For ICSP also **cut JP1** to isolate C31
   (470 nF): the entry sequence wants an MCLR pulse ≤ 2 µs and the datasheet says to isolate
   any MCLR cap during programming.
3. **JTAG pins are the SPI pins.** An erased PIC has JTAG enabled (TCK = RD1 = SPI_CLK,
   TDO = RD2 = SPI_MOSI, TDI = RD3, TMS = RB1 = digipot node). Firmware must set
   `JTAGEN = OFF` (done in `pic32/main.c`), and a blank chip will not respond on SPI.
4. **ICSP pins are shared with the RP's SWD.** J1 pins 4/5 carry PGD1/PGC1 (47 Ω) *and*
   RP SWCLK/SWDIO (0 Ω R17/R18). Bit-banging ICSP from GPIO21/22 wiggles the RP's own
   SWD pins through 47 Ω (harmless in practice; SWD needs a specific 50-clock reset
   sequence) and a PICkit on J1 does the same. To debug the RP over SWD, lift R56/R57.
   When the RP is not programming, GPIO21/22/24 **must stay Hi-Z** (done).
5. **Only one I²C master.** Both MCUs sit on SDA/SCL; the PIC must be an I²C client or
   stay off the bus. Step-1 firmware keeps the PIC off it.

## Build / flash

### RP2354A (works today)
```bash
export PICO_SDK_PATH=/home/kelu/projets/pico-sdk          # 2.1.0, has RP2350 support
cmake -S firmware/rp2354 -B firmware/rp2354/build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build firmware/rp2354/build -j
# flash: hold BOOTSEL (SW2, QSPI_SS→GND) while tapping RUN (SW1), then
picotool load -x firmware/rp2354/build/minus_rp.uf2      # or copy the .uf2 to the RP2350 drive
```
Then open the USB CDC port (`/dev/ttyACM0`, any baud) and type `help` — or script it:
`python3 firmware/rp2354/tools/rpcli.py /dev/ttyACM0 "version" "pic id" --wait=2`.
(picotool needs sudo here: no `2e8a` udev rule; copying the UF2 to `/media/kelu/RP2350` works.)

| Command | Does |
|---------|------|
| `version` | firmware name/version, build date, pico-sdk version, chip id / package / revision, 64-bit unique id |
| `rgb R G B` | set the WS2812/SK6812 colour, 0–255 per channel (`rgb 255 255 255` = white); disables status colours |
| `reboot` / `reboot dfu` | reset the RP2354 / reboot into BOOTSEL so the UF2 drive appears (no button needed) |
| `ping`, `auto`, `stop`, `stat` | one PING/PONG, PING every 500 ms, stop, counters |
| `reset` | pulse PIC MCLR low via GPIO24 (needs the R53 fix) |
| `rdy`, `trig` | read RDY (GPIO7), 2 µs pulse on TRIG (GPIO6) |
| `raw <text>` | send any line to the PIC, print its reply |
| `acq [div [samc [in [navg]]]]` | PIC captures **4095 samples via DMA** and sends them back; RP prints a `# acq n=4095 fill=…us fs=…Msps rp_fill=…` line then one value per line. `div` = SCCP1 trigger period in 6.25 ns counts (**8 = 20 Msps = the DMA ceiling**, default; 4 loses every other trigger), `samc` = sampling 0..7 (0.5 + 2n TAD) or -1 auto, `in` = ADC1 input (**9** PIC32_ADC node, **0** OA1OUT = op amp 1 ×11 on the RX node, **1** OA1IN+ = raw RX node), `navg` = 1 single conversion or 2..16 back-to-back conversions summed per trigger (ADC core at 40 Msps, result 12+log2(navg) bits; needs trigger period ≥ 25·navg + 40 ns). `rpcli.py … acq --wait=3 --out=capture.csv` saves it. Design: `docs/claude/specs/2026-10-27-acq-design.md`; throughput findings: memory 0011 |
| `acqcpu [trg [rptcnt [gap [phase]]]]` | **Experiment**: CPU-loop capture, no DMA — the CPU copies `AD1CH0DATA` to RAM every 4 cycles (25 ns), phase-locked to the ADC (same PLL). `trg` 12 (default) = SCCP1 at the last `acq` div (`acq 4 …` first → 40 Msps triggers); `gap` = extra NOPs per read (4 → 50 ns reads); `phase` = NOPs before the loop. Bench 2026-10-28: at 50 ns triggers every sample is caught exactly once/twice as expected; at 25 ns it is **marginal** (phase 0/1/5 ≈ 10 % duplicated pairs, other phases every other result lost: CPU reads win the bus over the ADC's result write). trg 2 (back-to-back) / 3 (repeat timer) never fire in single-sample mode |
| `acqil [div [off [navg]]]` | **Two-channel interleave = 20 M 2-sums/s** (the "20 Msps integrated over 2 samples" route). ADC1 CH0 and CH1 both read the last `acq` input, each summing `navg` (default 2) back-to-back 25 ns conversions per trigger; CH0 is triggered by SCCP1, CH1 by SCCP2 (same period, timer preloaded by `off` counts, 0 = div/2+1); two one-shot DMA channels (DMA0/DMA1, 0x2B/0x2C) fill two halves that the PIC merges into one stream (CH0[i], CH1[i], …). `div` = **per-channel** period in 6.25 ns counts (default 16 = 100 ns). Reply as `acq` with n = 4094. Bench 2026-10-28: `acqil 16` → 4094 sums in 206.0 µs = **19.87 M sums/s** (single channel `acq 16 0 9 2` = 9.94 M/s); the ADC core is then saturated (4 conversions per 100 ns) and packs them on its 25 ns grid, so the even/odd channel means agree to 0.1 LSB for any `off` (5, 9, 12), i.e. a uniform 40 Msps comb summed in pairs (13-bit). At div 20 (5 slots per channel) the two channels cannot be spaced evenly: means differ by 10–22 LSB. `acqil 32 0 4` = 4-sums at 9.94 M/s (same packing); `acqil 24 0 4` overloads the core (fill doubles, order scrambled). Decisive check still pending: a known tone at the ADC SMA |
| `raw AMP1 0\|1` | op amp 1 off/on (on at boot, high-power mode, external gain R47/R48) |
| `raw ADCBB n [ovs]` | **Experiment**: time `n` back-to-back conversions without DMA (integration mode; `ovs` 1 = oversampling burst, n = 4/16/64/256). Reply `ADCBB n ovs ticks 100 sum`. Bench: 4095 → 1026 ticks = **25.05 ns per conversion**, the ADC core really does 40 Msps on one channel |
| `pic id` | enter ICSP on GPIO21/22/24, read DEVID/REVID (expect `0x09DA2053`), exit. No write. |
| `pic image` | list the PIC image embedded in this RP firmware (from `firmware/pic32/build/minus_pic.hex` at build time) |
| `pic flash` | bulk erase, program by quadwords, read-back verify, release MCLR so the PIC boots |
| `pic verify` / `pic erase` | compare flash with the image / blank the PIC |

Status LED (until `rgb` is used): **blue** = no PIC reply, **green** = PONG ok, **red** = wrong reply.

The board header `rp2354/board/minus_devkit.h` (2 MB flash, our pin names) is selected with
`PICO_BOARD=minus_devkit`.

### PIC32AK (needs toolchain install — see [`../STEP1.md`](../STEP1.md) §2b)
Short version: **MPLAB X 6.35** (gives `ipecmd`), **XC-DSC 4.00** (free; ≥ 3.31.01 supports
`32AK1216GC41048`), and the **`Microchip.PIC32AK-GC_DFP` 1.1.53** device pack (already unpacked
in `~/microchip/packs/`). Then:
```bash
make -C firmware/pic32 info      # paths it resolved
make -C firmware/pic32           # -> build/minus_pic.hex
make -C firmware/pic32 flash TOOL=SNAP     # or PKBASIC / PK4 / PK5 / ICD4 / ICD5 / ICE4
```
The register bitfield names (`U1CONbits.CLKMOD/TXEN/RXEN/MODE/ON`, `U1STATbits.TXBF/RXBE`,
`RPINR9bits.U1RXR`, `RPOR9bits.RP39R`, `RPCONbits.IOLOCK`, `PACCON2bits.RPCONWR`,
`ANSELAbits.ANSELA0/7`) and the config pragmas (`JTAGEN = OFF`, `WDTEN = SW`, `WINDIS = ON`;
there is no `ICS` setting in this family) were verified against the DFP's
`p32AK1216GC41048.h` and `config_docs`; the source compiles clean (no warnings) with XC-DSC 3.31.01.

## Link protocol (proto 5)

ASCII lines, `\n`-terminated, 115200 8N1 (PIC side: FUART = FPB = 80 MHz, `U1BRG` 694):

| RP → PIC | PIC → RP |
|----------|----------|
| `PING <n>` | `PONG <n>` (and RDY toggles) |
| `ID?` | `PIC32AK1216GC41048 minus-devkit-pic32 0.1.1 proto 2` |
| `TRIG?` | `TRIG <edges counted on RA0>` |
| `ACQ [div [samc [in [navg]]]]` | `ACQ <n> <ticks> <tick_ns> <ok\|timeout\|dmaerr\|overrun\|notready>` then, only on `ok`, **n × u16 little-endian** (8190 bytes, ~0.71 s). `ticks × tick_ns` = fill time measured on the PIC (Timer1), so the RP can print the effective rate and spot dropped triggers. Arguments persist on the PIC between calls. The RP drains the link until it is idle 50 ms before every command, so a timed-out `ACQ` cannot poison the next one. |
| `ACQIL [div [off [navg]]]` | same reply format as `ACQ` with n = 4094 (two 2047-sample halves interleaved on the PIC); two-channel interleaved integration capture (see `acqil`). proto 5 |
| `ACQCPU <trg> [rptcnt [gap [phase]]]` | same reply format as `ACQ`; CPU-loop capture (see `acqcpu`) |
| `AMP1 0\|1` | `AMP1 <0\|1>` — op amp 1 enable |
| `ADCBB <n> [ovs]` | `ADCBB <n> <ovs> <ticks> <tick_ns> <sum>` — DMA-free ADC throughput test |
| `CLK12 <nosc>` | `CLK12 cosc=<n> rdy=<n>` — diagnostic: re-source CLKGEN12 (SCCP1 trigger clock) |
| anything else | `ERR` |

PIC clocking since fw 0.1.1: PLL1 from the FRC → CPU 160 MHz (CLKGEN1), ADC 320 MHz (CLKGEN6 → TAD
80 MHz → 40 Msps), SCCP 160 MHz (CLKGEN12). **Throughput facts (bench 2026-10-28, memory 0011):** the
DMA (standard-speed bus = CPU/2) moves one 16-bit sample per 4 bus clocks = **50 ns → 20 Msps ceiling**
(div 8); the ADC core converts at 25 ns; the capture wait loop must not touch SFRs (a tight poll of
`DMA0STAT`/`TMR1` made the DMA duplicate ~30 % of the samples and fake 26.6 Msps). 40 Msps raw is only
reachable with the CPU-loop reader (`acqcpu`, marginal at 160 MHz) or by raising the CPU to 200 MHz.

Once this works, step 2 is the real data path: PIC = SPI client (SS1 ← RP49, SCK1 ← RP50,
SDI1 ← RP51, SDO1 → RP35), RDY = "A-line captured", TRIG = capture start; and the RP-side
ICSP programmer so one USB-C cable programs both chips.
