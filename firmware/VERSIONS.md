# Firmware versions

Both firmwares carry a **semantic version `MAJOR.MINOR.PATCH`**, kept in one place each:

| Firmware | Version file | Reported by |
|----------|--------------|-------------|
| RP2354A (`rp2354/`) | `rp2354/version.h` → `FW_VERSION_MAJOR/MINOR/PATCH` | `version` on the USB CLI |
| PIC32AK (`pic32/`) | `pic32/version.h` → `FW_VERSION_MAJOR/MINOR/PATCH` | `ID?` over the UART link |

**Rule (owner decision, 2026-10-26):**
- **MAJOR and MINOR are owned by the project owner.** Claude never changes them.
- **PATCH is owned by Claude**: bump it on every change that alters the built binary
  (features, fixes, protocol tweaks). Doc-only changes do not bump.
- Record every bump in the table below (newest first). The two firmwares version
  independently; the link protocol version is reported separately (`PROTO_VERSION`).

| Date | Firmware | Version | What changed |
|------|----------|---------|--------------|
| 2026-10-26 | rp2354 | 0.1.1 | CLI: `version`, `rgb R G B`, `reboot [dfu]`; status LED override |
| 2026-10-26 | rp2354 | 0.1.0 | First build: USB CLI, UART PING/PONG, TRIG/RDY, MCLR tap, WS2812 |
| 2026-10-26 | pic32  | 0.1.0 | First source: FRC 8 MHz, UART1 on RP39/RP40, PONG, RDY toggle, TRIG counter (uncompiled) |
