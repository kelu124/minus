# STEP 1 — make the two MCUs talk (devkit `hardware/minUS_10102026`)

Goal: RP2354A (U1) and PIC32AK1216GC41048 (U2) exchange `PING n` / `PONG n` over the UART
link, with the RP's USB-C console as the human interface. Three parts: **board fixes**,
**software install**, **test**. Details and pin map: [`firmware/README.md`](firmware/README.md).

---

## 1. Board fixes (before trusting any result)

| # | What | Why | Fix |
|---|------|-----|-----|
| 1 | **R53 4.7 kΩ → 0 Ω** (RP GPIO24 → MCLR node) | With R5 = 10 k pull-up, GPIO24 low only reaches ~1.05 V; PIC VIL max is 0.66 V → the RP cannot reset or program the PIC | Replace R53 with 0 Ω (≤ 470 Ω is fine) |
| 2 | **Cut solder jumper JP1** (C31 470 nF on MCLR) when the RP is the programmer | ICSP entry wants an MCLR pulse ≤ 2 µs; the datasheet says to isolate any MCLR cap during programming | Cut JP1; re-bridge later if you want a slow power-on reset |
| 3 | **R68 ‖ R69 (2 × 100 Ω between SPI_MOSI and SPI_MISO)** | They exist so the MCP4131 digipots (single SDI/SDO pin on MISO) receive MOSI data — but 50 Ω makes the PIC's MISO fight the RP's MOSI | **Keep one, remove the other, and make it 1–4.7 kΩ** (do *not* remove both: digipot writes would stop working) |
| 4 | Nothing to solder, firmware only | An erased PIC has JTAG on (TCK = SPI_CLK, TDO = SPI_MOSI, TMS = digipot node) | `JTAGEN = OFF` is set in `firmware/pic32/main.c` |
| 5 | Keep RP GPIO21/22/24 Hi-Z unless programming | PGC1/PGD1/MCLR are shared with J1 (PICkit) and RP SWD | Done in `firmware/rp2354/main.c` |

Bus ownership (decided 2026-10-26): **the RP2354 is the only master of the digipots**
(MCP4131 ×2 on SPI, MCP4531 ×2 + MCP4728 on I²C). The PIC's SPI and I²C pins stay Hi-Z.
Not needed for the UART test: U5/LED1 (WS2812/SK6812) are 5 V parts driven at 3.3 V; if the
RGB LED stays dark that is why (a 3.3→5 V level shifter or a 3.3 V-tolerant LED fixes it).

## 2. Software install (Ubuntu 22.04, x86-64 — this machine)

### 2a. RP2354A side — already complete
pico-sdk 2.1.0 (`/home/kelu/projets/pico-sdk`, `PICO_SDK_PATH` set), arm-none-eabi-gcc, cmake,
ninja, picotool 2.3.0. `firmware/rp2354` builds → `build/minus_rp.uf2`.

### 2b. PIC32AK side — three pieces
**Why these:** the PIC32AK is a dsPIC33A-core part, so it is compiled by **MPLAB XC-DSC**
(XC-DSC ≥ 3.31.01 lists `32AK1216GC41048` explicitly; the old "XC32 for PIC32A" is retired).
Device support is a separate **Device Family Pack** (`Microchip.PIC32AK-GC_DFP`), and flashing
uses **`ipecmd`**, which ships inside **MPLAB X IDE** (the IPE is a component of that installer).

1. **MPLAB X IDE v6.35** — **installed 2026-10-26** at `/opt/microchip/mplabx/v6.35` (it also
   installed the `PIC32AK-GC_DFP` 1.1.53 pack under `packs/Microchip/`). For reference:
   ```bash
   cd ~/Downloads && tar xf MPLABX-v6.35-linux-installer.tar      # -> MPLABX-v6.35-linux-installer.sh
   sudo ./MPLABX-v6.35-linux-installer.sh                           # GUI; or add: --mode text
   #   keep "MPLAB IPE" ticked (ipecmd), keep the 16-bit/dsPIC + PIC32 device families ticked
   #   default path: /opt/microchip/mplabx/v6.35   (needs ~3 GB; / has 16 GB free)
   ```
   Programmer access without root: **done** — `/etc/udev/rules.d/z010_mchp_tools.rules` (from
   MPLABCOMM) grants mode 666 to Microchip VID 04d8 PIDs 8xxx/9xxx/a0xx (Snap, PICkit Basic,
   PICkit 4/5, ICD). If a tool is still not seen: `sudo udevadm control --reload && sudo udevadm trigger`, replug.
2. **XC-DSC compiler** — **installed 2026-10-26: v3.31.01** at `/opt/microchip/xc-dsc/v3.31.01`
   (supports `32AK1216GC41048`; v4.00 is current but not required). For reference:
   download the Linux `.run` from https://www.microchip.com/xcdsc (file like
   `xc-dsc-v4.00-full-install-linux-x64-installer.run`), then
   ```bash
   chmod +x ~/Downloads/xc-dsc-v4.*-full-install-linux-x64-installer.run
   sudo ~/Downloads/xc-dsc-v4.*-full-install-linux-x64-installer.run   # -> /opt/microchip/xc-dsc/v4.00
   echo 'export PATH=$PATH:/opt/microchip/xc-dsc/v4.00/bin' >> ~/.bashrc
   ```
3. **Device Family Pack** `Microchip.PIC32AK-GC_DFP` v1.1.53 — **already fetched and unpacked** to
   `~/microchip/packs/PIC32AK-GC_DFP/1.1.53/` (from https://packs.download.microchip.com/,
   the `.atpack` is a zip). It holds `xc32/support/PIC32A/h/p32AK1216GC41048.h`, the linker
   script and the config-bit docs; the firmware's register and `#pragma config` names were
   checked against it. MPLAB X can also install it from *Tools → Packs* if you prefer.
4. **Hardware — any of these on J1** (Tag-Connect TC2030-NL, Microchip ICSP pinout
   1 MCLR · 2 VDD · 3 GND · 4 PGD · 5 PGC · 6 NC). Per Microchip's device-support list
   (`pdfs/mplab/Device_Support.pdf`, MPLAB X ≥ 6.25) the PIC32AK1216GC41048 is programmable
   **and** debuggable with: **MPLAB Snap** (cheapest, ~€30, LVP-only — fine, this part is
   LVP-only anyway), **PICkit Basic** (~€30), **PICkit 4 / 5**, **ICD 4 / 5**, **ICE 4**.
   Not supported: Atmel-ICE/EDBG/nEDBG tools, PM3. **Decision 2026-10-26: aim at MPLAB Snap
   or PICkit Basic.** Both are powered by their own USB cable and do not power the target, so
   the devkit must be on USB-C while flashing. `ipecmd` tool codes (from the installed
   `docs/Readme for IPECMD.htm`): `SNAP`, `PKBASIC`, `PK4`, `PK5`, `ICD4`, `ICD5`, `ICE4` →
   `make -C firmware/pic32 flash TOOL=SNAP` (default) or `TOOL=PKBASIC`. The **RP2354 as programmer** (GPIO21/22/24) is step 2:
   feasible per the programming spec, but keep a Microchip tool as the known-good reference
   while that code is being written.

Check — **both now build on this machine (2026-10-26)**:
```bash
make -C firmware/pic32 info      # shows XC_DSC / MPLABX / DFP paths it will use
make -C firmware/pic32           # -> firmware/pic32/build/minus_pic.hex (~7 kB code, 36 B RAM)
```
Two XC-DSC gotchas are already handled in the Makefile: the device linker script must be passed
explicitly (`-T <DFP>/xc32/support/PIC32A/gld/p32AK1216GC41048.gld`, else the linker targets
"30Fxxxx"), and `xc-dsc-bin2hex` also needs `-mdfp=`.

**Disk:** MPLAB X installs ~97 device packs (8 GB) — the root volume hit 0 MB during the first
build. Keep ≥ 2 GB free; delete the installer tar once installed.

## 3. Test

1. **Flash the RP2354A:** hold BOOTSEL (SW2) while tapping RUN (SW1); a UF2 drive appears.
   `picotool load -x firmware/rp2354/build/minus_rp.uf2` (or copy the file to the drive).
   Later you can do it from the CLI: `reboot dfu`.
2. **Open the console:** `picocom -b 115200 /dev/ttyACM0` (or `screen`, `minicom`; baud is
   ignored on USB CDC). Type `help`, then `version` (firmware version, chip id, unique id) and
   `rgb 255 255 255` to check the LED. `rgb` takes 0–255 per channel.
3. **Flash the PIC32:** `make -C firmware/pic32 flash` (TOOL defaults to `SNAP`; `TOOL=PKBASIC` for PICkit Basic).
   LED2 (red, next to the PIC) starts blinking ≈ once per second.
4. **Link test:** on the RP console type `ping` → expect `ping 1: ok, ~1000 us, rdy=…`; `auto`
   pings every 500 ms (LED green = PONG ok, blue = no reply, red = garbage); `stat` shows
   counters; `raw ID?` should print `PIC32AK1216GC41048 minus-devkit-pic32 0.1.0 proto 1`.
5. **Handshake lines:** `trig` pulses GPIO6 → PIC RA0; `raw TRIG?` returns the edge count.
   `rdy` reads GPIO7 ← PIC RA7 (toggles on every PONG).
6. **Reset tap** (after fix #1): `reset` pulses MCLR; the PIC prints `PIC32 up` on restart
   (visible with `raw` immediately after, or with a USB-UART sniffer on H2.7/H2.8).

Pass criteria: 100 consecutive `ok` in `auto` mode, `rdy` toggling, `reset` restarts the PIC.
Then step 2: PIC as SPI client + ADC capture → RP, and the RP-side ICSP programmer.
