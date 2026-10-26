// Board header for the minus DesignA-DK devkit (hardware/minUS_10102026), RP2354A (QFN-60).
// Based on pico-sdk boards/pico2.h; differences: 2 MB in-package flash, our pin map.
#ifndef _BOARDS_MINUS_DEVKIT_H
#define _BOARDS_MINUS_DEVKIT_H

#define MINUS_DEVKIT
#define PICO_RP2350A 1                 // QFN-60 "A" package: GPIO0..29

// ---- inter-MCU link to the PIC32AK1216GC41048 (net names from the schematic) ----
#define MINUS_PIN_SDA        0   // I2C0 SDA  (shared bus: OLED, MCP4531 x2, MCP4728, PIC RD8/ASDA2)
#define MINUS_PIN_SCL        1   // I2C0 SCL  (PIC RD7/ASCL2)
#define MINUS_PIN_SPI_SCK    2   // SPI0 SCK  -> PIC RD1/RP50 (TCK!)  + MCP4131 x2 SCK
#define MINUS_PIN_SPI_MOSI   3   // SPI0 TX   -> PIC RD2/RP51 (TDO!)  (R68||R69 = 50R to MISO: see docs)
#define MINUS_PIN_SPI_MISO   4   // SPI0 RX   <- PIC RC2/RP35          + MCP4131 SDI/SDO
#define MINUS_PIN_SPI_CS     5   // SPI0 CSn  -> PIC RD0/RP49
#define MINUS_PIN_TRIG       6   // out -> PIC RA0/RP1   ("TRIG")
#define MINUS_PIN_RDY        7   // in  <- PIC RA7/RP8   ("RDY")
#define MINUS_PIN_PWM_H      8   // PIO -> JP8.B (pulser high-side drive, if JP8 set to RP)
#define MINUS_PIN_PWM_L      9   // PIO -> JP9.B
#define MINUS_PIN_RGB       10   // WS2812 (U5) + SK6812 (LED1) DIN in parallel, 5 V parts
#define MINUS_PIN_SPI_CS1   11   // MCP4131 U12 CS
#define MINUS_PIN_SPI_CS2   12   // MCP4131 U14 CS
#define MINUS_PIN_PWM       13   // "RP2354_PWM" -> R50
#define MINUS_PIN_UART_TX   16   // UART0 TX -> PIC RC7/RP40 (net UART_TX; also H2.7, CN1.7)
#define MINUS_PIN_UART_RX   17   // UART0 RX <- PIC RC6/RP39 (net UART_RX; also H2.8, CN1.9)
#define MINUS_PIN_PIC_PGC   21   // -> R56 (0R) -> PIC PGC1 (RB4)  [also J1.5 via 47R]
#define MINUS_PIN_PIC_PGD   22   // -> R57 (0R) -> PIC PGD1 (RB3)  [also J1.4 via 47R]
#define MINUS_PIN_PIC_MCLR  24   // -> R53 (4k7) -> MCLR node (R5 10k pull-up, C31 via JP1, R9 442R -> PIC MCLR)

#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 0
#endif
#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN MINUS_PIN_UART_TX
#endif
#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN MINUS_PIN_UART_RX
#endif
// no plain LED on the board (LED2 is on the PIC); RGB is on GPIO10
#ifndef PICO_DEFAULT_WS2812_PIN
#define PICO_DEFAULT_WS2812_PIN MINUS_PIN_RGB
#endif
#ifndef PICO_DEFAULT_I2C
#define PICO_DEFAULT_I2C 0
#endif
#ifndef PICO_DEFAULT_I2C_SDA_PIN
#define PICO_DEFAULT_I2C_SDA_PIN MINUS_PIN_SDA
#endif
#ifndef PICO_DEFAULT_I2C_SCL_PIN
#define PICO_DEFAULT_I2C_SCL_PIN MINUS_PIN_SCL
#endif
#ifndef PICO_DEFAULT_SPI
#define PICO_DEFAULT_SPI 0
#endif
#ifndef PICO_DEFAULT_SPI_SCK_PIN
#define PICO_DEFAULT_SPI_SCK_PIN MINUS_PIN_SPI_SCK
#endif
#ifndef PICO_DEFAULT_SPI_TX_PIN
#define PICO_DEFAULT_SPI_TX_PIN MINUS_PIN_SPI_MOSI
#endif
#ifndef PICO_DEFAULT_SPI_RX_PIN
#define PICO_DEFAULT_SPI_RX_PIN MINUS_PIN_SPI_MISO
#endif
#ifndef PICO_DEFAULT_SPI_CSN_PIN
#define PICO_DEFAULT_SPI_CSN_PIN MINUS_PIN_SPI_CS
#endif

// RP2354A: 2 MB flash in package, accessed over the (internal) QSPI like a W25Q-class part
#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1
#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif
#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (2 * 1024 * 1024)
#endif
#ifndef PICO_RP2350_A2_SUPPORTED
#define PICO_RP2350_A2_SUPPORTED 1
#endif
#endif
