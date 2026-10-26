---
name: pic32ak-xcdsc-toolchain
description: Use when building, checking or flashing firmware for Microchip PIC32AK / dsPIC33A-core parts (PIC32AK1216GC41048 etc.) on Linux — choosing the compiler, finding the Device Family Pack, verifying register bitfield or #pragma config names, or when xc-dsc-gcc / ipecmd are missing.
---

# PIC32AK (dsPIC33A core) toolchain on Linux

## Overview
PIC32AK is **not** a MIPS PIC32: it compiles with **MPLAB XC-DSC** (≥ 3.31.01 lists
`32AK1216GC41048`; 4.00 is current and free, no licence key). Device support comes from the
separate **Device Family Pack** `Microchip.PIC32AK-GC_DFP` (an `.atpack` = zip from
https://packs.download.microchip.com/), whose files sit under `<pack>/xc32/` (PIC32A naming).
Flashing uses **`ipecmd`**, shipped inside **MPLAB X IDE** (`/opt/microchip/mplabx/vX/mplab_platform/mplab_ipe/ipecmd.sh`).

## Quick reference
| Need | Do |
|------|----|
| Compiler | `xc-dsc-gcc -mcpu=32AK1216GC41048 -mdfp=<pack>/xc32 …`, hex via `xc-dsc-bin2hex` |
| DFP without MPLAB X | `curl -o p.atpack https://packs.download.microchip.com/Microchip.PIC32AK-GC_DFP.<ver>.atpack && unzip p.atpack -d <pack>` |
| Header / linker / config docs | `<pack>/xc32/support/PIC32A/{h,gld}/p32AK…`, `<pack>/xc32/docs/config_docs/32AK….html` |
| Flash with PICkit | `ipecmd.sh -TPPK5 -P32AK1216GC41048 -F fw.hex -M -OL` (PK4/ICD4/ICD5 likewise) |
| ICSP header | Microchip 6-pin: 1 MCLR · 2 VDD · 3 GND · 4 PGD · 5 PGC · 6 NC (Tag-Connect TC2030) |
| Toolchain present? | `command -v xc-dsc-gcc; ls /opt/microchip/` |

## Verify names before the compiler exists
```bash
python3 .claude/skills/pic32ak-xcdsc-toolchain/dfp_check.py <pack> 32AK1216GC41048 bits U1CON U1STAT RPCON RPOR9
python3 .claude/skills/pic32ak-xcdsc-toolchain/dfp_check.py <pack> 32AK1216GC41048 config JTAGEN WDTEN
python3 .claude/skills/pic32ak-xcdsc-toolchain/dfp_check.py <pack> 32AK1216GC41048 config   # all settings
```
Bitfield structs are `typedef struct tagU1CONBITS {...} U1CONBITS; extern volatile U1CONBITS U1CONbits;`.

## Family facts that bite
- **Erased device has JTAG enabled** on TCK/TDO/TDI/TMS → `#pragma config JTAGEN = OFF`.
- No `ICS` (debug pair) config setting; `WDTEN = SW|HW` (no OFF; SW = off unless WDTCON.ON).
- PPS: write `PACCON2bits.RPCONWR = 1`, then `RPCONbits.IOLOCK = 0`, map `RPINRx` inputs
  (pin number) and `RPORx.RPnR` outputs (function code, U1TX = 9), relock.
- UART: `U1CONbits.CLKMOD = 1` gives baud = F_UART / U1BRG (fractional); CLKSEL 0 = peripheral
  clock (= FRC 8 MHz at reset, ±1.5 %). FIFO regs `U1TXB` / `U1RXB`, status `U1STATbits.TXBF/RXBE`.
- ICSP (DS70005583): MCLR low → 32-bit key `0x8A12C2B2` LSB-first on PGD → MCLR high →
  2×34 clocks; VIL max 0.2·VDD on MCLR/PGx → any series R vs pull-up divider must reach that.
- MCLR: datasheet wants any capacitor isolated during programming (entry pulse ≤ 2 µs).

## Common mistakes
- Looking for an "XC32 for PIC32A" download: retired; XC32 ≥ 5.10 notes redirect to XC-DSC.
- Passing `-mdfp=<pack>/xc-dsc`: this pack has only `xc32/`. Try the root if `xc32/` fails.
- Installing MPLAB X with < 4 GB free; the IDE+IPE is ~3 GB plus a 1.1 GB tar.
