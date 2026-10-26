# minus devkit — PIC32AK1216GC41048 firmware, built headless with Microchip XC-DSC.
# Usage:  make            -> build/minus_pic.hex
#         make flash      -> program via MPLAB IPE's ipecmd + a PICkit on J1 (Tag-Connect)
# Adjust XC_DSC / MPLABX to the installed versions (see firmware/README.md).
DEVICE   ?= 32AK1216GC41048
XC_DSC   ?= /opt/microchip/xc-dsc/v3.30
MPLABX   ?= /opt/microchip/mplabx/v6.25
DFP      ?= $(firstword $(wildcard $(MPLABX)/packs/Microchip/PIC32A-K_DFP/*))
TOOL     ?= PK5            # ipecmd tool code: PK5 = PICkit 5, PK4 = PICkit 4, ICD4, ICD5

CC   := $(XC_DSC)/bin/xc-dsc-gcc
BIN2HEX := $(XC_DSC)/bin/xc-dsc-bin2hex
CFLAGS := -mcpu=$(DEVICE) -O1 -Wall -std=gnu99 -msmart-io=1 \
          $(if $(DFP),-mdfp=$(DFP)/xc-dsc,)
LDFLAGS := -mcpu=$(DEVICE) -Wl,--gc-sections,-Map=build/minus_pic.map \
          $(if $(DFP),-mdfp=$(DFP)/xc-dsc,)

SRC := main.c
OBJ := $(SRC:%.c=build/%.o)

all: build/minus_pic.hex

build/%.o: %.c | build
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

.PHONY: all flash clean
