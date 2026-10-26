cmake_minimum_required(VERSION 3.13)

# minus devkit — RP2354A side ("manager": USB-C CLI, inter-MCU link, PIC reset/ICSP taps)
set(PICO_PLATFORM rp2350-arm-s CACHE STRING "")
set(PICO_BOARD minus_devkit CACHE STRING "")
list(APPEND PICO_BOARD_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR}/board)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(minus_rp C CXX ASM)
set(CMAKE_C_STANDARD 11)
pico_sdk_init()

add_executable(minus_rp main.c)
pico_generate_pio_header(minus_rp ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)
target_link_libraries(minus_rp pico_stdlib hardware_uart hardware_pio hardware_gpio pico_unique_id pico_bootrom)

pico_enable_stdio_usb(minus_rp 1)    # CLI over USB-C CDC
pico_enable_stdio_uart(minus_rp 0)   # UART0 is the PIC link, not a console
pico_add_extra_outputs(minus_rp)     # .uf2 / .bin / .hex
