---
name: minus-firmware
description: Use when editing, building, versioning or flashing the minus devkit firmware under firmware/ (RP2354A pico-sdk side or PIC32AK side), adding CLI commands, or changing the RP<->PIC link protocol. minus repo ONLY.
---

# minus firmware conventions

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
make -C firmware/pic32 info && make -C firmware/pic32 && make -C firmware/pic32 flash TOOL=PK5
```
Board header: `firmware/rp2354/board/minus_devkit.h` (`PICO_BOARD=minus_devkit`, 2 MB flash,
`MINUS_PIN_*` names). Always rebuild the RP side before claiming a change works; the PIC side
is uncompiled until XC-DSC is installed (**REQUIRED SUB-SKILL:** pic32ak-xcdsc-toolchain).

## CLI (USB CDC on the RP) — keep it this shape
One line in, text out, `help` lists everything. Existing: `version`, `rgb R G B`, `reboot [dfu]`,
`ping/auto/stop/stat`, `reset`, `rdy`, `trig`, `raw <text>`. New commands: add to the dispatch
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
- Pin map and board flaws: `firmware/README.md`; bring-up procedure: `STEP1.md`.
