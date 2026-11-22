# minus firmware — RP2354A + PIC32AK (minus v1.1 = board 3)

Two MCUs, two firmwares, one USB-C cable: the RP2354A is the USB device, the CLI, the pulser
and the **only programmer of the PIC** (the RP UF2 embeds the PIC hex and `pic flash` writes it
over bit-banged ICSP). Versions are in [`VERSIONS.md`](VERSIONS.md); the host side is the Python
library [`python/library/minus/`](../python/library/minus/) (kept in sync by `python3 -m minus.fwsync`).

| Dir | Chip | Toolchain | Output (committed) | Status |
|-----|------|-----------|--------------------|--------|
| `rp2354/` | **RP2354A** (U8, QFN-60, 2 MB in-package flash) | pico-sdk 2.1.0 + arm-none-eabi-gcc + CMake/Ninja | `build/minus_rp.uf2` (embeds the PIC hex) | **rp 1.1.9**, running on board 3 |
| `pic32/`  | **PIC32AK1216GC41048** (U9, TQFP-48, LCSC C46545915) | Microchip **XC-DSC 3.31.01** + PIC32AK-GC_DFP 1.1.53 | `build/minus_pic.hex` | **pic 1.1.6, proto 15**, flashed by the RP |

Toolchain install and the build/flash walk-through are in the top-level
[`README.md`](../README.md#getting-started). The older devkits (boards 1/2, `minUS_10102026`) are in git
history; their pin map and flaws are in `docs/claude/memory/0008-devkit-minUS_10102026.md`.

## Inter-MCU wiring (board 3 netlist, `kicad-cli sch export netlist hardware/minUS.kicad_sch`)

| Net | RP2354A (U8) | PIC32AK (U9) | Notes |
|-----|--------------|--------------|-------|
| `UART_TX` | GPIO16 (UART0 TX) | RC6 / **RP39**, pin 25 (→ U1RX via PPS) | also CN1.9, H6.7. Net names are RP-side! |
| `UART_RX` | GPIO17 (UART0 RX) | RC7 / **RP40**, pin 26 (← U1TX via PPS) | also H6.8 |
| `SPI_CLK` | GPIO2 (SPI0 SCK) | RD1 / RP50 (**TCK**) → SCK1, pin 38 | CN1.23; capture payload link since proto 11 (RP master, PIC client, mode 0) |
| `SPI_MOSI` | GPIO3 (SPI0 TX) | RD2 / RP51 (**TDO**) → SDI1 (disabled), pin 39 | CN1.24; unused (RP sends 0x00) |
| `SPI_MISO` | GPIO4 (SPI0 RX) | RC2 / RP35 (PGC3) ← SDO1, pin 31 | CN1.22; the frame data |
| `SPI_CS` | GPIO5 (SIO, idle high) | RD0 / RP49 → SS1, pin 37 | CN1.21 |
| `TRIG` | GPIO6 (out) | RA0 / RP1 (PGD2), pin 1 | CN1.19; counted by `TRIG?` |
| `RDY` | GPIO7 (in) | RA7 / RP8, pin 2 | CN1.20; rises when the ADC capture starts (`pe` sync) |
| `SDA`/`SCL` | GPIO0/1 (I2C0) | RD8 / RD7 (ASDA2/ASCL2), pins 44/43 | 10 kΩ pull-ups R15/R16; also LP5562 U5 (0x30), CN1.25/26, SCL on H6.2 |
| `PGC1` | GPIO21 → R22 0 Ω | RB4, pin 22 | GPIO21 also on CN1.4 |
| `PGD1` | GPIO22 → R23 0 Ω | RB3, pin 21 | GPIO22 also on CN1.3 |
| `MCLR` | GPIO24 → R27 0 Ω → node | pin 48 via R19 442 Ω | R18 10 kΩ pull-up on the node; no MCLR capacitor; GPIO24 also on CN1.40 |

Other RP pins: GPIO8/9 → U3 (4427 gate driver) → Q2 / Q1 pulser FETs (`pulse`, `pe`); GPIO25/23 → SN74HC4052 U1
S0/S1 (gain legs, `gain`); GPIO10–15, 18–20, 26–29, SWD and QSPI → CN1 (2×20) only. SW2 on QSPI_SS = BOOTSEL,
SW1 = RUN.
Other PIC pins: RC5 → LED1 (red, R21 330 Ω, heartbeat); RD4 ← SW3 (R20 10 k pull-up); RC0/RC1 (OSC) only reach
H6, so the PIC **runs on its internal FRC** (8 MHz) through PLL1; op amps OA1 (pins 8–10, also J1) and OA2
(pins 16–18, also J2), ADC node PIC32_ADC = AD2AN9 pin 4 (R67/R68/C86/C87 filter from OA2OUT, D1 clamp, H6.13).

## How the RP2354 controls the PIC32

1. **Reset**: GPIO24 → MCLR (open-drain style: drive low, release to Hi-Z). R27 = 0 Ω so the node really
   reaches 0 V (the devkit's 4.7 kΩ divider bug is gone).
2. **ICSP programming**: GPIO21 = PGC1, GPIO22 = PGD1, GPIO24 = MCLR. Protocol (DS70005583 §2–3): MCLR low →
   key 0x8A12C2B2 on PGD with 32 PGC clocks → MCLR high → 2×34 clocks; then 2-bit commands + 32-bit shifts that
   execute CPU instructions / read VISI / write W0-indexed memory. Implemented in `rp2354/pic_icsp.c`
   (bit-banged, ~1.2 MHz; bulk erase §3.1, quadword program §3.3, read §3.5) and exposed as `pic …`. The PIC hex
   is converted by `rp2354/tools/hex2c.py` into `build/pic_image.c` at RP build time. **Working on board 3**
   (`pic id` → DEVID `0x09DA2053`, `pic flash` + verify). There is no ICSP header on v1.1, so the RP is the
   only way in (recovery header: `TODO_HARDWARE.md`).
3. **Run time**: UART link for commands (below), **SPI for capture payloads** (proto 11), TRIG/RDY GPIOs, shared I²C (RP is master).

## Hardware notes that still apply on board 3

1. **JTAG pins are the SPI pins.** An erased PIC has JTAG enabled (TCK = RD1 = SPI_CLK, TDO = RD2 = SPI_MOSI,
   TDI = RD3 → H6.3, TMS = RB1 = OA2IN-). The firmware sets `JTAGEN = OFF` (`pic32/main.c`); a blank PIC will not
   answer on SPI and its TMS pin sits on the OA2 gain network.
2. **One I²C master.** Both MCUs and the LP5562 sit on SDA/SCL; the PIC keeps its I²C pins Hi-Z, the RP is
   the only master.
3. **GPIO21/22/24 stay Hi-Z** when the RP is not programming, so the PIC runs undisturbed.
4. PIC `RC0/RC1` have no crystal: all PIC timing comes from the FRC (±1.5 %), which is enough for 115 200 Bd.

Fixed since the devkit (for reference): the R68‖R69 50 Ω MOSI↔MISO short is gone (R67/R68 are now the ADC
input filter); MCLR R53 4.7 kΩ / C31 / JP1 → R27 0 Ω and no capacitor; PGC1/PGD1 no longer share J1 with the
RP's SWD (SWD is on CN1.5/CN1.10 only); WS2812/SK6812 on GPIO10 → LP5562 RGB driver on I²C.

## Build / flash

```bash
make -C firmware/pic32                                  # PIC first -> build/minus_pic.hex
export PICO_SDK_PATH=/home/kelu/projets/pico-sdk        # 2.1.0
cmake -S firmware/rp2354 -B firmware/rp2354/build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build firmware/rp2354/build -j                  # -> build/minus_rp.uf2 (embeds the PIC hex)
```
Flash the RP: `reboot dfu` on the CLI (or hold SW2 BOOTSEL while tapping SW1 RUN), wait for the `RP2350`
drive to mount, copy `minus_rp.uf2` to it (picotool needs sudo here: no `2e8a` udev rule). Then flash the PIC
from the RP: `pic flash`, and check with `version` + `raw ID?`.
Talk to it: `/dev/ttyACM0` (USB CDC, any baud; since rp 1.1.4 it enumerates as manufacturer `kelu124`, product
`minUS badge`, serial = RP unique id, e.g. `/dev/serial/by-id/usb-kelu124_minUS_badge_7D4466C63B374C98-if00`; VID:PID stays 2E8A:0009), type `help`, or script it:
`python3 firmware/rp2354/tools/rpcli.py /dev/ttyACM0 "version" "pic id" --wait=2` — or use the Python library.

The `make -C firmware/pic32 flash` target (MPLAB IPE + PICkit/Snap) is for boards with an ICSP header only;
v1.1 has none.

## RP CLI commands (rp 1.1.9)

| Command | Does |
|---------|------|
| `version` | firmware name/version, build date, pico-sdk version, chip id / package / revision, 64-bit unique id |
| `rgb R G B [pct]` | RGB LED: **LP5562 U5** (I²C 0x30) at `pct` % brightness (0–100, default 25). Reply `rgb R G B pct% (LP5562 0x30: ok\|not found)`. Also drives GPIO10 as a WS2812 line (devkit legacy). Until `rgb` is used the LED shows the link status |
| `reboot` / `reboot dfu` | reset the RP2354 / reboot into BOOTSEL so the UF2 drive appears |
| `ping`, `auto`, `stop`, `stat` | one PING/PONG, PING every 500 ms, stop, counters |
| `lb` | RP UART0 internal loopback self-test |
| `reset` | pulse PIC MCLR low via GPIO24 |
| `rdy`, `trig` | read RDY (GPIO7), 2 µs pulse on TRIG (GPIO6) |
| `raw <text>` | send any line to the PIC, print its reply (e.g. `raw ID?`, `raw AMP1 0`, `raw PC?`) |
| `pulse [hi [lo [dead]]]` | one pulser shot now: +5 V for `hi` ns (200), both FETs off `dead` ns (27, min 4 PIO cycles), GND `lo` ns (500), then released. PIO at 150 MHz = 6.67 ns steps. GPIO8 HIGH = Q2 (N) to GND, GPIO9 LOW = Q1 (P) to +5 V |
| `pe [hi [lo [in [dead]]]]` | pulse-echo: the pulser fires on the PIC's RDY rise (= ADC start), then `ACQ 4 0 <in> 1` = 4095 samples at ≈ 25 Msps; retried (≤ 8 shots) while the PIC flags the capture `slow`. `in` 25 = AD2AN9 ADC node (default), 17 OA2OUT, 0 OA1OUT, 1 LNA out / OA1IN+. Data: `docs/bench/2026-11-19-pe/` |
| `acq [div [samc [in [navg]]]]` | PIC captures **4095 samples via DMA**; RP prints `# acq n=4095 fill=…us fs=…Msps rp_fill=…` then one value per line. `div` = SCCP1 trigger period in 5 ns counts (**4 = 25 Msps**, default; 10 = 20 Msps; 5..9 irregular), `samc` 0..7 (0.5 + 2n TAD) or -1 auto, `in` = input code 0..15 ADC1 / 16..31 ADC2 (25 default, as `pe`), `navg` 1 or 2..16 conversions summed per trigger. Arguments persist on the PIC. `rpcli.py … acq --wait=3 --out=capture.csv` saves it |
| `link [uart\|spi [MHz]]` | payload path for `acq`/`pe`/`acqcpu`/`acqil`: **SPI frame** (default 12.5 MHz = 5.7 ms per capture; 18.75 and 25 MHz also clean in mode 1; CRC-32 checked, UART fallback counted) or UART only (0.71 s). No args = counters. The `# acq` line ends with `link=spi@12.50MHz xfer=…us`. `acq`/`pe` send `RELOCK` to the PIC after 3 slow captures in a row |
| `linktest [count [MHz]]` | SPI link self-test without a capture: the PIC fills its buffer with an LFSR pattern (`XTEST`), the RP pulls it `count` times (default 10), checks every word + CRC, then once over the UART and compares. Data: `docs/bench/2026-11-21-spi-dac/` |
| `dac [off \| dc <code> \| tri <lo> <hi> <slope> \| sine <hz> [amp [mid]]]` | PIC DAC1 test signal on DACOUT1 (U9 pin 3 = H6.16 on board 3, = `acq` input **19** = AD2AN3). Codes 205..3890 = 5..95 % of 3.3 V. `tri` = hardware triangle (half period (hi−lo)·16/slope × 4 ns; no bus traffic, use it during captures); `sine` = DMA-fed table, ≤ 128 points, ≥ 1 µs per update — **makes 20–25 Msps captures come back `slow`** (bench 2026-11-21). DAC clock = PLL2 → CLKGEN7 500 MHz |
| `acqos <4\|16> [in [pe]]` | capture with **ADC hardware oversampling**: each sample = 4 / 16 back-to-back 32 ns conversions → 13 / 14-bit (2× / 4× a 12-bit code), 185 / 565 ns per sample, 0.76 / 2.32 ms window, noise ÷2.1 / ÷3.1; one pulse (`pe 1`), averaging inside each sample. **Not for the 3.3 MHz RF echo**: 5.4 / 1.77 Msps alias it (Nyquist 2.7 / 0.88 MHz) and the 128 / 512 ns average cancels it — use `pe` (RF), `env` (strength) or `tof` (range). Printed like `acq` |
| `tof <thr> [blank_ns [in [ref]]]` | pulse + **time of flight on the PIC**: first sample after `blank_ns` with \|x−ref\| > thr (ADC channel comparator armed on ref±thr; ref 0 = capture mean, comparator then on 2048±thr), plus the peak in the next 64 samples; one line (index, ns, mm), 8.9 ms end to end |
| `env <dec> [shots [in]]` | pulse + **envelope computed on the PIC** (\|x−mean\| over `dec` = 4..64 samples), averaged over `shots` pulses, then pulled: 4095/dec values in 1/16 LSB (`# env n=… dec=… shots=… dt=…ns`) |
| `envbp <dec> [shots [in [fc_khz [bw_khz]]]]` | pulse + **band-pass envelope on the PIC**: Gaussian complex filter at fc (3300 kHz) with FWHM bw (2500 kHz) — an FFT band-pass + Hilbert envelope done as a ~21-tap filter at the decimated outputs; values = in-band amplitude (1/16 LSB); +12 dB peak/floor over `env` on the bench echoes (datasheet §5.2) |
| `fmt [text\|b64]` | sample output of acq/pe/acqos/env: one decimal per line (default) or `# b64 <bytes>` + base64 lines of u16 LE: 11.4 KB / 30 ms instead of 24.8 KB / 110 ms per capture (USB CDC is the limit); the Python library switches to b64 on connect |
| `tgc [off \| <t_us> <leg> ...]` | time-gain steps: the 4052 gain leg (both stages) switched at up to 4 times after the pulse during every capture (acq/pe/acqos/tof/env), restored after; each switch costs ~2 µs of saturation + ~15 µs of settling (break-before-make; `docs/bench/2026-11-22-tgc-b64/`) |
| `gain [leg [u1 [u2]]]` | RX gain: `leg` 0..3 = 74HC4052 Rf 2.2k/4.7k/6.8k/10k on both stages (Rg 1 k → ×3.2/×5.7/×7.8/×11 each), `u1`/`u2` = 1 → OA1/OA2 at ×1 via the PIC's `UGE`. No args = show. Data: `docs/bench/2026-11-19-gain/` |
| `pc [0\|1]` | PIC-side removal of the period-4 fixed pattern (≈ 10.5 LSB rms) from `acq`/`pe` captures, on at boot; shows the last per-phase offsets |
| `i2c` | scan I2C0. Board 3: 0x30 LP5562 only (the other names are devkit parts) |
| `pic id` / `image` / `flash` / `verify` / `erase` | ICSP: read DEVID/REVID (expect `0x09DA2053`) / list the embedded PIC image / bulk erase + program + verify + run / compare / blank |
| `pic pins`, `pic mclr low\|hiz\|rise`, `pic slow\|fast`, `pic pair 1\|2`, `pic rdraw`, `pic seq` | ICSP diagnostics (`pic help`) |
| `acqcpu …`, `acqil …`, `raw ADCBB n [ovs]` | throughput experiments from the devkit (CPU-loop read, two-channel interleave — parked since the 200 MHz clock change, back-to-back conversion timing); see memory 0011 |
| `pot <0\|1> [n]`, `raw AMP2 0\|1` (U11 text) | devkit-only: the MCP4531 digipots are not on board 3 (OA2 gain = `gain`); `AMP2` still switches op amp 2 |

The firmware `help()` text still mentions some devkit parts (R53, U11/MCP4531, OLED); the table above is the
board 3 truth.

## Link protocol (proto 15)

ASCII lines, `\n`-terminated, 115 200 8N1 (PIC: FUART = FPB = 100 MHz, `U1BRG` = FPB/115200 = 868, fractional).
The RP drains the link until it is idle 50 ms before every command.

| RP → PIC | PIC → RP |
|----------|----------|
| `PING <n>` | `PONG <n>` (and RDY toggles) |
| `ID?` | `PIC32AK1216GC41048 minus-pic32 1.1.6 proto 15` |
| `TRIG?` | `TRIG <edges counted on RA0>` |
| `ACQ [div [samc [in [navg]]]]` | `ACQ <n> <ticks> <tick_ns> <ok\|timeout\|dmaerr\|overrun\|slow\|notready>` — header only since proto 11; the payload stays on the PIC until pulled (`SPIX` / `UTX`). Since proto 14, `navg` goes back to 1 unless given. `ticks × tick_ns` = fill time on the PIC (Timer1, 80 ns); `slow` = the PIC saw a non-uniform fill (proto 10) |
| `SPIX` | proto 12: **no UART reply** (only `SPIX 0` when nothing is pending). The PIC drops RDY, preloads SPI1, raises RDY = "clock now", feeds the frame `A5 5A 'M' '1'`, n u16, seq u16, n × u16 LE, CRC-32/IEEE LE of all before (12 + 2n bytes, CRC computed while feeding), drops RDY. SPI mode 1. The RP clocks it with CS low and checks magic / n (from the ACQ header) / CRC (`link_frame.c`) |
| `ACQOS <4\|16> [in]` | as `ACQ` (header only), oversampled capture (proto 13) |
| `TOF <thr> [blank [in [ref]]]` | `TOF <idx\|-1> <peak_idx> <peak> <ref> <hw> <ticks> <tick_ns> <status>`; blank in samples; the A-line stays pullable (proto 13) |
| `ENV <dec> [in [acc]]` | `ENV <n> <dec> <shots> <ticks> <tick_ns> <status>`; acc 1 adds to the running average; n values pulled by SPIX / UTX (proto 13) |
| `ENVBP <dec> [in [acc [fc_khz [bw_khz]]]]` | as `ENV` (proto 15) |
| `LOCK?` / `RELOCK` | `LOCK <locks tried> <slow test captures of 8>` — the boot-time PLL1 lock check (re-lock until no test capture is slow); `RELOCK` redoes it now (re-runs acq_init: op amps / UGE back to boot state) |
| `UTX` | `UTX <n>` then n × u16 little-endian over the UART (fallback, `link uart`, reference) |
| `XTEST [seed]` | `XTEST 4095 <seed>` — buffer = 16-bit Galois LFSR (0xB400) from seed; for `linktest` |
| `DAC 0` / `DAC 1 <code>` / `DAC 2 <lo> <hi> <slp>` / `DAC 3 <hz> [amp [mid]]` / `DAC?` | `DAC 0`, `DAC 1 <code>`, `DAC 2 <lo> <hi> <slp>`, `DAC 3 <hz> <points> <update counts> <amp> <mid>`, or `DAC ERR args\|noclk` |
| `AMP1 0\|1` / `AMP2 0\|1` | `AMP1 <0\|1>` / `AMP2 <0\|1>` — op amp enable (OA1 on at boot, OA2 off) |
| `UGE <a1> <a2>` | `UGE <a1> <a2>` — op amp unity-gain bypass (proto 8) |
| `PC 0\|1` / `PC?` | `PC <on> <o0> <o1> <o2> <o3>` — fixed-pattern correction state + last offsets (proto 9) |
| `ACQIL [div [off [navg]]]` | as `ACQ` with n = 4094 (two-channel interleave; parked); payload pulled the same way |
| `ACQCPU <trg> [rptcnt [gap [phase]]]` | as `ACQ` (CPU-loop capture experiment) |
| `ADCBB <n> [ovs]` | `ADCBB <n> <ovs> <ticks> <tick_ns> <sum>` — DMA-free ADC throughput test |
| `CLK12 <nosc>` | `CLK12 cosc=<n> rdy=<n>` — diagnostic: re-source CLKGEN12 (SCCP1 clock) |
| anything else | `ERR` |

## PIC clocking and throughput

Since pic 0.1.20: PLL1 from the FRC, VCO 1000 MHz → CPU **200 MHz** (rated maximum), FPB 100 MHz, ADC
**250 MHz** (TAD 62.5 MHz → 32 ns conversions), SCCP 200 MHz (**5 ns per `div` count**), Timer1 tick 80 ns.
The DMA costs 40 ns per sample → `acq` default div 4 = uniform 25 Msps (the 32 ns ADC takes every other 20 ns
trigger); the capture wait loop must not touch SFRs. Full story: `docs/claude/memory/0011-adc-dma-throughput.md`;
the sample-comb phase and whole-sample slips are in memory 0020 and `docs/bench/2026-11-19-jitter/`.
