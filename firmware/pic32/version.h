// Firmware version — see ../VERSIONS.md for the ownership rule (owner: MAJOR.MINOR, Claude: PATCH).
#ifndef VERSION_H
#define VERSION_H
#define FW_NAME           "minus-devkit-pic32"
#define FW_VERSION_MAJOR  0
#define FW_VERSION_MINOR  1
#define FW_VERSION_PATCH  7
#define PROTO_VERSION     3   // 3: ACQ [div]   // 2: + ACQ (4095-sample capture, header + binary payload)
#define _FW_STR(x) #x
#define FW_STR(x) _FW_STR(x)
#define FW_VERSION FW_STR(FW_VERSION_MAJOR) "." FW_STR(FW_VERSION_MINOR) "." FW_STR(FW_VERSION_PATCH)
#endif
