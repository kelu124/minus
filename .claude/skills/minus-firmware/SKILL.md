---
name: minus-firmware
description: Use when editing, building, versioning or flashing the minus firmware under firmware/ (RP2354A pico-sdk side or PIC32AK side) on the devkit or board 3 (v1.1), adding CLI commands, running pulse-echo/gain/noise bench captures, or changing the RP<->PIC link protocol. minus repo ONLY.
---

# minus firmware conventions

## Python library sync (2026-11-19)
Every CLI / reply-format / link-protocol / version change must land in `python/library/minus/` in the same commit:
`commands.py` (dispatch token, exact `help` usage, method, `FIRMWARE`), `device.py`, `protocol.py`, re-record
`tests/fixtures` with `tests/record_fixture.py`, re-run the notebooks, `python3 -m unittest discover -s tests`, then
`python3 -m minus.fwsync --update` (cwd `python/library`). The PostToolUse hook reports drift after each firmware edit.
Board 3 LED = LP5562 at I²C 0x30 (`rgb R G B [pct]`, pct default 25 %, rp ≥ 1.1.2).

## Versioning (owner rule, 2026-10-26)
Each firmware has `version.h` with `FW_VERSION_MAJOR/MINOR/PATCH` + `PROTO_VERSION`.
**Owner controls MAJOR.MINOR; Claude bumps PATCH on every change that alters a binary** and
adds a row to `firmware/VERSIONS.md` (newest first). Doc-only changes: no bump. Never touch
MAJOR/MINOR unless the owner says so.

## Build / flash
```bash
export PICO_SDK_PATH=/home/kelu/projets/pico-sdk        # 2.1.0
cmake -S firmware/rp2354 -B firmware/rp2354/build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build firmware/rp2354/build -j && picotool load -x firmware/rp2354/build/minus_rp.uf2
make -C firmware/pic32 info && make -C firmware/pic32 && make -C firmware/pic32 flash TOOL=SNAP   # or PKBASIC/PK4/PK5/ICD4/ICD5/ICE4
```
Board header: `firmware/rp2354/board/minus_devkit.h` (`PICO_BOARD=minus_devkit`, 2 MB flash,
`MINUS_PIN_*` names). Always rebuild the RP side before claiming a change works; the PIC side
is uncompiled until XC-DSC is installed (**REQUIRED SUB-SKILL:** pic32ak-xcdsc-toolchain).

## Bench driving
`python3 firmware/rp2354/tools/rpcli.py /dev/ttyACM0 "cmd1" "cmd2" --wait=2` sends CLI lines and
prints replies. Flash: `reboot dfu` on the CLI → UF2 drive appears at `/media/kelu/RP2350` → copy
the `.uf2` there (picotool needs sudo on this machine). Wait for `/dev/ttyACM0` to come back.

## CLI (USB CDC on the RP) — keep it this shape
One line in, text out, `help` lists everything. Existing: `version`, `rgb R G B`, `reboot [dfu]`,
`ping/auto/stop/stat`, `reset`, `rdy`, `trig`, `raw <text>`, `pic id|image|flash|verify|erase`
(ICSP programmer, `pic_icsp.c`; PIC hex embedded via `tools/hex2c.py` → `build/pic_image.c`,
so **rebuild the RP after every PIC build** to refresh the image). New commands: add to the dispatch
chain in `main.c`, to `help()`, to the table in `firmware/README.md`, bump PATCH.

## Link protocol (RP ↔ PIC, UART0 ↔ UART1, 115200 8N1, ASCII lines)
`PING n`→`PONG n`, `ID?`→`<chip> <fw name> <version> proto <n>`, `TRIG?`→`TRIG <count>`,
else `ERR`. Changing it = bump `PROTO_VERSION` on both sides, same commit.

## Hardware rules baked into firmware
- RP GPIO21/22/24 (PGC1/PGD1/MCLR taps) stay **Hi-Z** unless programming; `reset` = drive
  low then release, never drive high.
- RP is the **only master** of digipots/I²C; PIC SPI/I²C pins stay Hi-Z until the SPI-client
  step is designed.
- PIC config: `JTAGEN = OFF`, `WDTEN = SW`, `WINDIS = ON`. PIC runs on FRC 8 MHz (no crystal).
- Pin map and board flaws: `firmware/README.md`; setup/flash procedure: `README.md` (Getting started).

## Board 3 (v1.1, KiCad in `hardware/`) — current target = minus v1.1 (2026-11-19, rp 1.1.2 / pic 1.1.0, proto 10)
Same RP pin map as the devkit build (`minus_devkit` header). Differences that the firmware handles:
- **Pulser** GPIO8 HIGH = Q2 N-FET → GND, GPIO9 LOW = Q1 P-FET → +5 V (names PWM_H/PWM_L swapped). Idle 8=0/9=1; never
  8=1+9=0 (shoot-through). `pulser.pio` on pio1 SM0, `pulser_init()` first in `main()`.
- **Gain**: 74HC4052 S0 = GPIO25, S1 = GPIO23 (both stages share them), Rf 2.2/4.7/6.8/10 k, Rg 1 k; PIC `UGE a1 a2` = ×1 per stage.
- **ADC input codes**: 0–15 ADC1 PINSEL, 16–31 ADC2 + 16. 25 = AD2AN9 ADC node (default), 17 OA2OUT, 0 OA1OUT, 1 LNA tap
  (aliased noise, not a real measurement), 15/31 band gap, 14/30 15/16 AVDD. DMA trigger ADC2 ch0 = CHSEL 0x40.
- **Commands**: `pe [hi [lo [in [dead]]]]`, `pulse`, `gain [leg [u1 [u2]]]`, `pc [0|1]` (period-4 pattern correction, on).
- **ACQ status `slow`** (PIC, no payload) = ADC locked to 40/60/60 ns; `pe`/`acq` re-shoot ≤ 8.
- Not driven: LP5562 RGB at I²C 0x30 (WS2812 code targets GPIO10 = nothing on board 3). LED1 = PIC RC5 heartbeat.

## Flashing pitfalls (learnt the hard way)
```bash
python3 firmware/rp2354/tools/rpcli.py /dev/ttyACM0 "reboot dfu" --wait=1
for i in $(seq 1 40); do [ -e /media/kelu/RP2350/INFO_UF2.TXT ] && break; sleep 0.5; done   # wait for the MOUNT, not the USB id
cp firmware/rp2354/build/minus_rp.uf2 /media/kelu/RP2350/ && sync
for i in $(seq 1 40); do [ -e /dev/ttyACM0 ] && break; sleep 0.5; done; sleep 2               # may come back as ttyACM1
python3 firmware/rp2354/tools/rpcli.py /dev/ttyACM0 "version" "pic flash" --wait=30            # then: raw ID? (PIC may need ~1 s)
```
- If cp fails, `pic flash` still runs and writes the OLD embedded PIC image — always check `version` before `pic flash`.
- `reboot dfu` intermittently comes back as the app (`2e8a:0009`): ask the owner to hold SW2 (BOOTSEL) at plug-in.
- `rpcli.py --wait=S` waits at least S seconds: fine for captures (`--wait=2` per `pe`), useless for timing.

## Bench captures
Keep each campaign as a script + raw files in `docs/bench/<date>-<topic>/` with a README (commands, firmware versions, results).
`/usr/bin/python3` has matplotlib. Noise: look at per-phase means (mod 4) first; align shots before averaging (sample-comb
phase is random over one sample). Datasheet numbers come from `docs/bench/2026-11-19-datasheet/analyze.py` → `datasheet/`.
