cmake_minimum_required(VERSION 3.13)

# minus v1.1 — RP2354A side ("manager": USB-C CLI, inter-MCU link, PIC reset/ICSP taps)
set(PICO_PLATFORM rp2350-arm-s CACHE STRING "")
set(PICO_BOARD minus_devkit CACHE STRING "")
list(APPEND PICO_BOARD_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR}/board)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(minus_rp C CXX ASM)
set(CMAKE_C_STANDARD 11)
pico_sdk_init()

# Embedded PIC32 image: converted from the PIC build's hex at build time (empty image if absent).
set(PIC_HEX ${CMAKE_CURRENT_LIST_DIR}/../pic32/build/minus_pic.hex CACHE FILEPATH "PIC32 Intel HEX to embed")
if(EXISTS ${PIC_HEX})
  set(PIC_HEX_DEP ${PIC_HEX})
  set(PIC_HEX_ARG ${PIC_HEX})
else()
  message(WARNING "PIC hex not found at ${PIC_HEX}: building with an empty PIC image")
  set(PIC_HEX_DEP "")
  set(PIC_HEX_ARG NONE)
endif()
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/pic_image.c
  COMMAND python3 ${CMAKE_CURRENT_LIST_DIR}/tools/hex2c.py ${PIC_HEX_ARG} ${CMAKE_CURRENT_BINARY_DIR}/pic_image.c minus_pic.hex
  DEPENDS ${CMAKE_CURRENT_LIST_DIR}/tools/hex2c.py ${PIC_HEX_DEP}
  COMMENT "Embedding PIC32 image from ${PIC_HEX_ARG}")

add_executable(minus_rp main.c pic_icsp.c acq_parse.c link_frame.c ${CMAKE_CURRENT_BINARY_DIR}/pic_image.c)
target_include_directories(minus_rp PRIVATE ${CMAKE_CURRENT_LIST_DIR})
pico_generate_pio_header(minus_rp ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)
pico_generate_pio_header(minus_rp ${CMAKE_CURRENT_LIST_DIR}/pulser.pio)
target_link_libraries(minus_rp pico_stdlib hardware_uart hardware_spi hardware_pio hardware_gpio hardware_i2c pico_unique_id pico_bootrom)

pico_enable_stdio_usb(minus_rp 1)    # CLI over USB-C CDC
# USB descriptor strings (owner, 2026-11-21); VID/PID stay 2E8A:0009 (pico-sdk CDC), serial = the RP unique board id (sdk default)
target_compile_definitions(minus_rp PRIVATE USBD_MANUFACTURER="kelu124" USBD_PRODUCT="minUS badge")
# (USB CDC TX buffer: pico-sdk hard-codes 256 B in pico_stdio_usb/include/tusb_config.h, which caps capture text at ~270 kB/s
#  — a -D here has no effect; bench 2026-11-22.)
pico_enable_stdio_uart(minus_rp 0)   # UART0 is the PIC link, not a console
pico_add_extra_outputs(minus_rp)     # .uf2 / .bin / .hex
