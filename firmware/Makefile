# minus devkit firmware — top level. Builds both chips.
#   make            -> both (PIC only if xc-dsc-gcc is installed)
#   make rp | pic   -> one side        make flash-rp | flash-pic   make info   make clean
all: rp pic

rp:
	$(MAKE) -C rp2354

pic:
	@if [ -x "$$($(MAKE) -s -C pic32 info | sed -n 's/^CC=//p')" ]; then $(MAKE) -C pic32; \
	 else echo "pic32: skipped — xc-dsc-gcc not installed (see STEP1.md §2b)"; fi

flash-rp:
	$(MAKE) -C rp2354 flash

flash-pic:
	$(MAKE) -C pic32 flash

info:
	@echo "== rp2354 =="; $(MAKE) -s -C rp2354 info
	@echo "== pic32 =="; $(MAKE) -s -C pic32 info

clean:
	$(MAKE) -C rp2354 clean; $(MAKE) -C pic32 clean

.PHONY: all rp pic flash-rp flash-pic info clean
