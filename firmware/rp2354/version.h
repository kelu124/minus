// Firmware version — see ../VERSIONS.md for the ownership rule (owner: MAJOR.MINOR, Claude: PATCH).
#pragma once
#define FW_NAME           "minus-devkit-rp2354"
#define FW_VERSION_MAJOR  0
#define FW_VERSION_MINOR  1
#define FW_VERSION_PATCH  18
#define PROTO_VERSION     3   // RP<->PIC link protocol (PING/PONG/ID?/TRIG?; 2: ACQ; 3: ACQ [div])
#define _FW_STR(x) #x
#define FW_STR(x) _FW_STR(x)
#define FW_VERSION FW_STR(FW_VERSION_MAJOR) "." FW_STR(FW_VERSION_MINOR) "." FW_STR(FW_VERSION_PATCH)
