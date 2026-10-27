# 0010 — pic32prog / pic32probe study (RP2040 as PIC32 ICSP dongle)

Date: 2026-10-27. Full write-up: `pic32prog/README.md` (repos vendored as submodules).

- **kiffie/pic32probe** = RP2040 Rust firmware, 2-wire ICSP dongle for **MIPS-core** PIC32
  (MX/MM/MK/MZ). PIO state machine does the 4-phase ICSP (TDI, TMS, idle, TDO per 4 PGC clocks),
  1 MHz default; entry key "MCHP" 0x4D434850 MSB-first bit-banged at 100 kHz; USB vendor bulk
  protocol `{u16 code,u16 len}`: ConnectReset/Disconnect/GetIdCode/ReadWord/EraseChip/
  LoadExecutive/ExecutiveTransaction. Host = **kiffie/pic32prog-kvh** (branch `pic32probe`,
  `adapter-pic32probe.c`) which owns hex parsing, device table and the Programming Executive.
- **Does not apply logically to our PIC32AK1216GC41048** (dsPIC33A core: no EJTAG/MTAP/PE;
  ICSP = 2-bit cmd + 32-bit opcode serial execution, DS70005583). `pic32prog` has no 33A/32AK
  device entry. Our `firmware/rp2354/pic_icsp.c` stays the reference implementation.
- **Physical/entry layer is comparable and ours matches the spec**: key on the wire is
  "MCH" + last byte (MCHP vs MCHQ = 0x8A12C2B2 LSB-first), MCLR push-pull during the session,
  Hi-Z + board pull-up idle, exit = MCLR low 1 ms then release. Differences to keep as debugging
  knobs: pic32probe clocks the key at 100 kHz (we use ~1.2 MHz) and uses PIO for exact timing.
- **Takeaways queued in TODO**: slow key / `pic speed` knob if `pic id` still fails with MCLR
  low; optional PIO port; optional host-streamed image (`pic raw` via `rpcli.py`) instead of the
  embedded hex, mirroring pic32prog's `adapter-bitbang` ASCII-dongle pattern.
