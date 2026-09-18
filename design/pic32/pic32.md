# PIC32 (PIC32A) — how it is programmed / flashed

Practical reference for flashing the **PIC32AK…GC41** ("PIC32A") in *minus*
([DesignA](../designA/README.md)). Covers the on-board header, tools, the two flashing
paths, and the MCLR network. See also the concept ([`README.md`](README.md) §3d) and
requirements S4a / T4a.

> **Architecture note:** despite the "PIC32" name, the **PIC32AK is a 32-bit dsPIC**
> core. It builds with Microchip's **XC-DSC** compiler in **MPLAB X** — a *closed*
> toolchain (anti-req N1). Building firmware needs XC-DSC; **flashing a prebuilt `.hex`
> does not** (free MPLAB IPE + a PICkit suffices).

## How a PIC32 is usually flashed

**ICSP (In-Circuit Serial Programming)** is the native method — a 2-wire serial protocol
over three device pins plus power:

| ICSP signal | PIC32A pin | Role |
|-------------|-----------|------|
| **MCLR / Vpp** | `MCLR` | reset + program-mode entry |
| **PGD / ICSPDAT** | one of `PGD1/2/3` | serial data (bidirectional) |
| **PGC / ICSPCLK** | matching `PGC1/2/3` | serial clock |
| **VDD** | `VDD` (3.3 V) | target power / reference |
| **VSS** | `GND` | ground |

The PIC32A brings out **three PGEC/PGED pairs** (PGC1/PGD1 … PGC3/PGD3) plus **JTAG**;
you **pick one pair**, route it + MCLR to the header, and tell the programmer which pair
it is. (Product brief: "two-wire ICSP with non-intrusive access … IEEE 1149.2 JTAG".)

### Tools
- **Programmer/debugger:** **PICkit 4 / PICkit 5**, **MPLAB Snap** (cheapest), or MPLAB
  ICD 4/5. All speak ICSP over the 5 pins above.
- **Software:** **MPLAB X IDE** (build + program + debug, needs the **XC-DSC** compiler
  to *build*), or **MPLAB IPE** (Integrated Programming Environment) to just **flash a
  provided `.hex`** — free, no compiler. Command-line: `ipecmd`.
- **Vpp / LVP:** modern PIC32/dsPIC support **Low-Voltage Programming** (LVP) — MCLR is
  driven at VDD levels with a key sequence, **no ~9 V Vpp needed**. A PICkit can still use
  HV Vpp on MCLR; **LVP is what lets another MCU (the RP2354) bit-bang ICSP** over plain
  GPIO. Confirm the LVP entry sequence in the PIC32/dsPIC **Flash Programming Spec**.
- **Alternative:** a **UART/serial bootloader** flashed once via ICSP then self-updates
  over UART (PIC32A has no USB). Optional; ICSP stays the bring-up/recovery path.

### Standard programming header (what to put on the board)
The Microchip **5-pin ICSP** header, in order:

```
  1  MCLR/Vpp
  2  VDD (3V3)
  3  VSS (GND)
  4  PGD (ICSPDAT)   ← chosen PGEDx
  5  PGC (ICSPCLK)   ← chosen PGECx
 (6  PGM/LVP — usually NC)
```

(PICkit uses a 6-pin 0.1″ SIL; pin 1 is marked by the triangle.) A 5-pin header **or
just 5 test pads** works.

### MCLR network (important)
- **10 kΩ pull-up** from `MCLR` to VDD.
- **Do not** hang a large capacitor directly on MCLR (it corrupts the Vpp edge). If a
  reset cap is wanted, put a **series ~1 kΩ** between the pull-up/cap node and the MCLR
  pin, or omit the cap. Keep the MCLR track short.
- No diode to VDD that would clamp Vpp below the programmer's level (only relevant if HV
  Vpp is used; harmless under LVP).

## On the minus board (DesignA)

Two flashing paths share the **same PGC/PGD/MCLR net**:

1. **Direct (PICkit):** header **J3** = `MCLR, VDD, GND, PGD, PGC` → PICkit/Snap + MPLAB
   IPE. This is the requested "flash the PIC32 directly" path (req S4a).
2. **Via RP2354:** the RP2354 bit-bangs **LVP ICSP** on the same three lines (§3d) so one
   USB-C port programs both MCUs (RP2354 via UF2 → then flashes the PIC).

**Coexistence:** because both the PICkit and the RP2354 sit on the same net, when a
**PICkit drives J3 the RP2354's PGC/PGD/MCLR pins must be Hi-Z** (inputs) — handle in
firmware/boot, or add series resistors so the PICkit wins. Only one programmer active at
a time.

## To verify
- [ ] Which **PGECx/PGEDx pair** to expose (pin-map vs the SPI/handshake pins, §3c/§3d).
- [ ] **LVP entry sequence** + whether the RP2354 GPIO timing meets it (Flash Prog Spec).
- [ ] MCLR network values on the final schematic; PICkit-vs-RP2354 **bus contention**
      handling on the shared ICSP net.
- [ ] Confirm **MPLAB Snap** (cheapest) supports the PIC32AK, or require PICkit 4/5.
