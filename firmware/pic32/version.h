// Firmware version — see ../VERSIONS.md for the ownership rule (owner: MAJOR.MINOR, Claude: PATCH).
#ifndef VERSION_H
#define VERSION_H
#define FW_NAME           "minus-pic32"
#define FW_VERSION_MAJOR  1
#define FW_VERSION_MINOR  1
#define FW_VERSION_PATCH  6
#define PROTO_VERSION     15  // 15: + ENVBP <dec> [in [acc [fc_khz [bw_khz]]]] (band-pass envelope); lock check pauses the DAC sine DMA. 14: ACQ resets navg to 1 unless given (RP: fmt b64 output, tgc gain schedule). 13: + ACQOS <4|16> [in], TOF <thr> [blank [in [ref]]], ENV <dec> [in [acc]] (ADC extras). 12: SPIX has no UART reply: the frame is announced on RDY, CRC only in the frame tail. 11: payload pulled (ACQ/ACQCPU/ACQIL send the header only) + SPIX (SPI1 frame) / UTX (UART) / XTEST [seed] / DAC 0..3. 10: ACQ status "slow" (no payload). 9: + PC 0|1, PC?. 8: + UGE a1 a2. 7: ACQ input codes 16..31 = ADC2 (25 = AD2AN9, default); 6: + AMP2 0|1 (op amp 2 enable); 5: + ACQIL [div [off [navg]]] (two-channel interleave); 4: ACQ [div [samc [in [navg]]]] + AMP1 0|1   // 3: ACQ [div]   // 2: + ACQ (4095-sample capture, header + binary payload)
#define _FW_STR(x) #x
#define FW_STR(x) _FW_STR(x)
#define FW_VERSION FW_STR(FW_VERSION_MAJOR) "." FW_STR(FW_VERSION_MINOR) "." FW_STR(FW_VERSION_PATCH)
#endif
