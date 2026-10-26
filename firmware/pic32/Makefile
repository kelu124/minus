# minus devkit — PIC32AK1216GC41048 firmware, built headless with Microchip XC-DSC.
# Usage:  make            -> build/minus_pic.hex
#         make flash      -> program via MPLAB IPE's ipecmd + a PICkit on J1 (Tag-Connect)
# Adjust XC_DSC / MPLABX to the installed versions (see firmware/README.md).
DEVICE   ?= 32AK1216GC41048
XC_DSC   ?= $(lastword $(sort $(wildcard /opt/microchip/xc-dsc/v*)))
MPLABX   ?= $(lastword $(sort $(wildcard /opt/microchip/mplabx/v*)))
# Device Family Pack "Microchip.PIC32AK-GC_DFP" (packs.download.microchip.com). Either the copy
# unpacked under ~/microchip/packs (see STEP1.md) or the one MPLAB X installs.
DFP      ?= $(firstword $(wildcard $(HOME)/microchip/packs/PIC32AK-GC_DFP/*) $(wildcard $(MPLABX)/packs/Microchip/PIC32AK-GC_DFP/*))
TOOL     ?= PK5            # ipecmd tool code: PK5 = PICkit 5, PK4 = PICkit 4, ICD4, ICD5

CC   := $(XC_DSC)/bin/xc-dsc-gcc
BIN2HEX := $(XC_DSC)/bin/xc-dsc-bin2hex
# NB: this DFP ships its support files under <pack>/xc32/ (PIC32A naming); XC-DSC >= 3.31 compiles
# PIC32AK with it. If the compiler cannot find p32AK1216GC41048.h, try DFPSUB=xc32 or DFPSUB=.
DFPSUB   ?= xc32
CFLAGS := -mcpu=$(DEVICE) -O1 -Wall -std=gnu99 -msmart-io=1 \
          $(if $(DFP),-mdfp=$(DFP)/$(DFPSUB),)
LDFLAGS := -mcpu=$(DEVICE) -Wl,--gc-sections,-Map=build/minus_pic.map \
          $(if $(DFP),-mdfp=$(DFP)/$(DFPSUB),)

SRC := main.c
OBJ := $(SRC:%.c=build/%.o)

all: build/minus_pic.hex

info:
	@echo "XC_DSC=$(XC_DSC)"; echo "MPLABX=$(MPLABX)"; echo "DFP=$(DFP)"; echo "CC=$(CC)"
	@test -x "$(CC)" && $(CC) --version | head -1 || echo "xc-dsc-gcc not found"
	@grep -h "FW_VERSION_\(MAJOR\|MINOR\|PATCH\)" version.h | tr -s ' ' | cut -d' ' -f2,3 | tr '\n' ' '; echo

build/%.o: %.c version.h | build
	$(CC) $(CFLAGS) -c $< -o $@

build/minus_pic.elf: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

build/minus_pic.hex: build/minus_pic.elf
	$(BIN2HEX) $< -a -omf=elf
	@mv -f build/minus_pic.hex $@ 2>/dev/null || true
	@ls -l $@

build:
	mkdir -p build

flash: build/minus_pic.hex
	$(MPLABX)/mplab_platform/mplab_ipe/ipecmd.sh -TP$(TOOL) -P$(DEVICE) -F$< -M -OL

clean:
	rm -rf build

.PHONY: all flash clean info
