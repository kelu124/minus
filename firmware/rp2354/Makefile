# minus devkit — RP2354A firmware. Thin wrapper around the pico-sdk CMake build.
#   make            -> build/minus_rp.uf2
#   make flash      -> picotool load -x (board must be in BOOTSEL: hold SW2, tap SW1, or CLI "reboot dfu")
#   make monitor    -> open the USB CLI (picocom)
#   make clean
PICO_SDK_PATH ?= /home/kelu/projets/pico-sdk
BUILD   ?= build
TYPE    ?= Release
PORT    ?= /dev/ttyACM0
export PICO_SDK_PATH

all: $(BUILD)/minus_rp.uf2

$(BUILD)/build.ninja: CMakeLists.txt board/minus_devkit.h
	cmake -S . -B $(BUILD) -G Ninja -DCMAKE_BUILD_TYPE=$(TYPE)

$(BUILD)/minus_rp.uf2: $(BUILD)/build.ninja main.c version.h ws2812.pio
	cmake --build $(BUILD) -j
	@ls -l $@

flash: $(BUILD)/minus_rp.uf2
	picotool load -x $< || { echo "no board in BOOTSEL — hold SW2 (BOOTSEL), tap SW1 (RUN), or type 'reboot dfu' on the CLI"; exit 1; }

monitor:
	@command -v picocom >/dev/null && picocom -b 115200 --imap lfcrlf $(PORT) || echo "install picocom (sudo apt install picocom) or use: screen $(PORT) 115200"

info:
	@echo "PICO_SDK_PATH=$(PICO_SDK_PATH)"; cmake --version | head -1; arm-none-eabi-gcc --version | head -1; picotool version | head -1
	@grep -h "FW_VERSION_\(MAJOR\|MINOR\|PATCH\)" version.h | tr -s ' ' | cut -d' ' -f2,3 | tr '\n' ' '; echo

clean:
	rm -rf $(BUILD)

.PHONY: all flash monitor info clean
