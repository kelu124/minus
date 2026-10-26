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
| `UART_TX` | GPIO16 (UART0 TX) | RC7 / **RP40** (→ U1RX via PPS) | also on H2.7 and CN1.7 (sniff with a USB-UART) |
| `UART_RX` | GPIO17 (UART0 RX) | RC6 / **RP39** (← U1TX via PPS) | also on H2.8 and CN1.9 |
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

## Link protocol (step 1)

ASCII lines, `\n`-terminated, 115200 8N1:

| RP → PIC | PIC → RP |
|----------|----------|
| `PING <n>` | `PONG <n>` (and RDY toggles) |
| `ID?` | `PIC32AK1216GC41048 minus-devkit-pic32 0.1.0 proto 1` |
| `TRIG?` | `TRIG <edges counted on RA0>` |
| anything else | `ERR` |

Once this works, step 2 is the real data path: PIC = SPI client (SS1 ← RP49, SCK1 ← RP50,
SDI1 ← RP51, SDO1 → RP35), RDY = "A-line captured", TRIG = capture start; and the RP-side
ICSP programmer so one USB-C cable programs both chips.
