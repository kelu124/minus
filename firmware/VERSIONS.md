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
| 2026-10-28 | rp2354 | 0.1.18 | `acq [div [samc]]` (0.1.17); embeds pic 0.1.7 |
| 2026-10-28 | pic32  | 0.1.7 | `ACQ [div [samc]]` (0.1.6, SAMC default fixed 0); `CLK12 <nosc>` diagnostic re-sources the SCCP1 trigger clock |
| 2026-10-28 | rp2354 | 0.1.16 | `acq [div]` (proto 3), RP-crystal timing of the RDY capture window (`rp_fill`), waits for the RDY drop first |
| 2026-10-28 | pic32  | 0.1.5 | `ACQ [div]` trigger divider + period-matched SAMC (proto 3); RDY = capture window (low on ACQ receipt, high trigger→DMA done) |
| 2026-10-28 | rp2354 | 0.1.13 | embeds pic 0.1.2; `lb` UART0 loopback self-test (0.1.12); DEVID expected = 0x9DA2 register value (0.1.11); `pic seq` / `pic rdraw` ICSP stream diagnostics (0.1.8–0.1.10) |
| 2026-10-28 | pic32  | 0.1.2 | **UART pins swapped to match the board**: U1RX = RP39/RC6 (net UART_TX), U1TX = RP40/RC7 (net UART_RX) |
| 2026-10-27 | rp2354 | 0.1.7 | `pic pair 1|2`: ICSP through PGC2/PGD2 (RA1 via jumper H2.16→CN1.17, RA0 = TRIG/GPIO6) to bypass pins 21/22 |
| 2026-10-27 | rp2354 | 0.1.6 | RP SWD pad pull-ups disabled at boot (they held PGC1/PGD1 high through R17/R18 + 47R and faked a 'PIC alive' reading) |
| 2026-10-27 | rp2354 | 0.1.5 | diagnostics: `pic mclr rise` (C31 check), `pic slow|fast` ICSP clock, PGC clock count in `pic id` |
| 2026-10-27 | rp2354 | 0.1.4 | `acq` command (4095-sample capture from the PIC, one value per line), link drain-until-idle, proto 2 |
| 2026-10-27 | pic32  | 0.1.1 | PLL 160 MHz CPU / 320 MHz ADC, UART baud clock fix (FPB = Fsys/2), `ACQ` 4095-sample capture, proto 2 |
| 2026-10-26 | rp2354 | 0.1.3 | `pic pins`, `pic mclr low|hiz` bench diagnostics |
| 2026-10-26 | rp2354 | 0.1.2 | `pic id/image/flash/verify/erase`: ICSP programmer on GPIO21/22/24, PIC hex embedded at build time |
| 2026-10-26 | rp2354 | 0.1.1 | CLI: `version`, `rgb R G B`, `reboot [dfu]`; status LED override |
| 2026-10-26 | rp2354 | 0.1.0 | First build: USB CLI, UART PING/PONG, TRIG/RDY, MCLR tap, WS2812 |
| 2026-10-26 | pic32  | 0.1.0 | First source: FRC 8 MHz, UART1 on RP39/RP40, PONG, RDY toggle, TRIG counter (uncompiled) |
