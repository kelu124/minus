# DesignA toolchain (Ubuntu / Linux, CLI + Makefile)

How to build and flash **both** firmwares of [DesignA](README.md) from the command
line on Ubuntu — RP2354A → `.uf2`, PIC32A → `.hex` — with a top-level `Makefile`.

DesignA has two build targets:

| Target | Chip | Toolchain | Output | Open? |
|--------|------|-----------|--------|-------|
| `rp` | **RP2354A** | pico-sdk + arm-none-eabi-gcc + CMake | `.uf2` (+ `.elf`) | **fully open** ✓ |
| `pic` | **PIC32A** | Microchip **XC-DSC** (Linux CLI) | `.hex` | **closed compiler** (N1) |

> **Openness (anti-req N1):** the RP2354 side is 100 % open and apt-installable. The
> PIC32A side needs Microchip's **XC-DSC** compiler (closed) — but it **runs headless on
> Linux** and builds via `make`. **Reflashing a prebuilt `.hex`** needs only the free
> **MPLAB IPE / `ipecmd`** (no compiler), or the RP2354-over-ICSP path — so end users
> never need the closed toolchain, only firmware developers do.

---

## 0. Prerequisites (Ubuntu)

### RP2354A (open, apt)
```bash
sudo apt update
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi \
                 build-essential git python3 pkg-config libusb-1.0-0-dev
# pico-sdk (>= 2.0 required for RP2350/RP2354)
git clone --depth 1 --branch master https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk && git submodule update --init && cd ..
export PICO_SDK_PATH=$PWD/pico-sdk        # put in ~/.bashrc
# picotool (CLI loader) — build from source or apt (recent Ubuntu):
sudo apt install picotool   # or build from github.com/raspberrypi/picotool
```

### PIC32A (Microchip, closed but Linux)
1. **XC-DSC compiler** (supports Linux + the PIC32A/dsPIC33A family; current v3.x):
   download the Linux installer from
   `microchip.com/.../mplab-xc-compilers/xc-dsc`, then:
   ```bash
   chmod +x xc-dsc-vX.YY-full-install-linux-x64-installer.run
   sudo ./xc-dsc-vX.YY-full-install-linux-x64-installer.run   # → /opt/microchip/xc-dsc/vX.YY
   ```
   The Free licence compiles/flashes fine (only optimisation levels are gated).
2. **MPLAB X IDE** (Linux `.sh`) — gives the headless build tools (`make`,
   `prjMakefilesGenerator.sh`) and the programmer CLIs **`ipecmd`** / **`mdb`**:
   ```bash
   chmod +x MPLABX-vX.YY-linux-installer.sh
   sudo ./MPLABX-vX.YY-linux-installer.sh    # → /opt/microchip/mplabx/vX.YY
   ```
3. **Device Family Pack (DFP)** for PIC32AK — install via MPLAB X's pack manager (or
   `pypackmanager`) so the compiler/programmer know the device.
4. **udev rules** for the PICkit so it's usable without root (MPLAB X ships them, or add
   a `/etc/udev/rules.d` entry for the PICkit VID `0x03eb`), then `sudo udevadm control
   --reload && sudo udevadm trigger`.

> Exact binary names/paths vary by version — confirm against the **XC-DSC C Compiler
> User's Guide (DS50003918)** and the Assembler/Linker guide (DS50003919).

---

## 1. RP2354A → `.uf2`

Standard pico-sdk CMake flow. RP2354 = RP2350 core + 2 MB internal flash, so build for
the `rp2350` platform and set the 2 MB flash size (via a board header or a define):

```bash
cmake -S firmware/rp2354 -B firmware/rp2354/build \
      -DPICO_PLATFORM=rp2350-arm-s \
      -DPICO_FLASH_SIZE_BYTES=2097152        # RP2354A = 2 MB in-package flash
cmake --build firmware/rp2354/build -j
# → firmware/rp2354/build/designA-rp.uf2  (+ .elf/.bin)
```

Flash (put the badge in BOOTSEL — hold BOOTSEL, tap RUN):
```bash
picotool load -x firmware/rp2354/build/designA-rp.uf2   # -x = reboot into app
# or just copy the .uf2 onto the RPI-RP2 mass-storage drive
```

## 2. PIC32A → `.hex`

Easiest reliable CLI path: keep an **MPLAB X project** (`firmware/pic32/designA.X`) and
build it headless with the MPLAB-generated makefiles (they already reference XC-DSC):

```bash
export PATH=/opt/microchip/mplabx/vX.YY/mplab_platform/bin:$PATH   # provides `make`
cd firmware/pic32/designA.X
prjMakefilesGenerator.sh .          # (re)generate makefiles from the project
make CONF=default                    # compiles with XC-DSC
# → firmware/pic32/designA.X/dist/default/production/designA.X.production.hex
```

*(Advanced, no IDE project: drive the compiler directly in your own Makefile — call the
XC-DSC compiler driver from `/opt/microchip/xc-dsc/vX.YY/bin/` with the device's linker
script + `-mcpu=<part>`; see the compiler User's Guide for the driver name and flags.)*

Flash with a **PICkit 4/5 or Snap** on header **J3** (ICSP), via `ipecmd`:

```bash
IPECMD="java -jar /opt/microchip/mplabx/vX.YY/mplab_platform/mplab_ipe/ipecmd.jar"
$IPECMD -TPPK4 -PPIC32AK3208GC41048 \
        -F firmware/pic32/designA.X/dist/default/production/designA.X.production.hex \
        -M -OL
#  -TPPK4 tool (PK4=PICkit4, PK5, SN=Snap)  -P<device>  -F<hex>  -M program  -OL run
```
Run `ipecmd` with no args to list the exact **tool codes** and **device strings** for
your install. Alternative CLI: **`mdb`** (MPLAB Debugger) with a script:
```
# flash.mdb :  mdb /opt/.../mdb.sh flash.mdb
device PIC32AK3208GC41048
hwtool PICKIT4
program firmware/pic32/designA.X/dist/default/production/designA.X.production.hex
quit
```

---

## 3. Top-level `Makefile` (build + flash both)

```make
# DesignA — build/flash both MCUs from Linux CLI
MPLABX ?= /opt/microchip/mplabx/v6.25
IPECMD := java -jar $(MPLABX)/mplab_platform/mplab_ipe/ipecmd.jar
PICTOOL:= $(MPLABX)/mplab_platform/bin           # MPLAB's make/generators
PIC_X  := firmware/pic32/designA.X
PIC_HEX:= $(PIC_X)/dist/default/production/designA.X.production.hex
RP_UF2 := firmware/rp2354/build/designA-rp.uf2
PIC_DEV:= PIC32AK3208GC41048
TOOL   := PK4                     # PK4 | PK5 | SN (Snap)

.PHONY: all rp pic flash-rp flash-pic flash clean
all: rp pic                                        ## build both

rp:                                                ## RP2354 -> uf2
	cmake -S firmware/rp2354 -B firmware/rp2354/build \
	      -DPICO_PLATFORM=rp2350-arm-s -DPICO_FLASH_SIZE_BYTES=2097152
	cmake --build firmware/rp2354/build -j

pic:                                               ## PIC32 -> hex
	PATH=$(PICTOOL):$$PATH $(MAKE) -C $(PIC_X) CONF=default

flash-rp: rp                                       ## load uf2 (board in BOOTSEL)
	picotool load -x $(RP_UF2)

flash-pic: pic                                     ## flash hex via PICkit on J3
	$(IPECMD) -TP$(TOOL) -P$(PIC_DEV) -F$(PIC_HEX) -M -OL

flash: flash-rp flash-pic                          ## flash both

clean:
	rm -rf firmware/rp2354/build
	PATH=$(PICTOOL):$$PATH $(MAKE) -C $(PIC_X) clean CONF=default
```

Usage: `make` (build both) · `make flash-rp` · `make flash-pic` · `make flash`.

## 4. One-USB field path (no PICkit)

For workshop/field reflash without a PICkit: flash the **RP2354 via UF2** (`make
flash-rp`), then let RP2354 firmware **bit-bang LVP ICSP** to program a bundled PIC
`.hex` over the shared PGC/PGD/MCLR net (DesignA §3d / §6b, [`../pic32/pic32.md`](../pic32/pic32.md)).
So attendees need only a USB-C cable; developers use the PICkit + `ipecmd` path above.

## 5. To verify
- [ ] Exact **XC-DSC** version/driver name + install path; free-licence limits.
- [ ] `ipecmd` **device string** for `PIC32AK3208GC41048` and the tool code for PICkit 5.
- [ ] pico-sdk **RP2354** board/flash config (2 MB) — board header vs `PICO_FLASH_SIZE_BYTES`.
- [ ] Whether **MPLAB Snap** supports the PIC32AK (cheapest programmer) or PICkit 4/5 req.
- [ ] RISC-V (Hazard3) build option for RP2354 if wanted (separate toolchain) — else ARM.

## Links
- DesignA: [`README.md`](README.md) · PIC32 flashing: [`../pic32/pic32.md`](../pic32/pic32.md).
- XC-DSC C Compiler User's Guide (DS50003918); Assembler/Linker (DS50003919).
- pico-sdk + picotool: github.com/raspberrypi/pico-sdk, /picotool.
