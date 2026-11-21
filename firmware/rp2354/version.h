// Firmware version — see ../VERSIONS.md for the ownership rule (owner: MAJOR.MINOR, Claude: PATCH).
#pragma once
#define FW_NAME           "minus-rp2354"
#define FW_VERSION_MAJOR  1
#define FW_VERSION_MINOR  1
#define FW_VERSION_PATCH  6
#define PROTO_VERSION     13  // 13: + acqos / tof / env (PIC ACQOS, TOF, ENV: ADC oversampling, comparator, on-PIC envelope). 12: SPIX announced on RDY (no reply line), CRC in the frame tail only. 11: payload over SPI (SPIX) or UART (UTX), XTEST, DAC. 10: ACQ status slow. 9: + PC. 8: + UGE a1 a2. 7: ACQ input codes 16..31 = ADC2. 6: + AMP2 0|1. RP<->PIC link protocol (PING/PONG/ID?/TRIG?; 2: ACQ; 3: ACQ [div]; 4: ACQ [div [samc [in [navg]]]], AMP1)
#define _FW_STR(x) #x
#define FW_STR(x) _FW_STR(x)
#define FW_VERSION FW_STR(FW_VERSION_MAJOR) "." FW_STR(FW_VERSION_MINOR) "." FW_STR(FW_VERSION_PATCH)
