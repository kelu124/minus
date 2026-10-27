# pic32prog — how an RP2040 programs a PIC32 (kiffie), and what applies to minus

Study of two GitHub repos by Stephan "kiffie" (GPL-2.0), vendored here as git submodules
(2026-10-27) so they can be grepped offline:

| Folder | Upstream | Branch / commit | What it is |
| --- | --- | --- | --- |
| `pic32probe/` | github.com/kiffie/pic32probe | master @ 5a03cf2 (2025-11-08) | Rust `no_std` firmware for an **RP2040** breakout (QT Py / ItsyBitsy): a 2-wire ICSP dongle + USB-UART |
| `pic32prog-kvh/` | github.com/kiffie/pic32prog-kvh | **pic32probe** @ 93805d6 (2026-07-08) | Fork of Serge Vakulenko's `pic32prog` host tool with an `adapter-pic32probe.c` backend (libusb) |

Fetch after a fresh clone: `git submodule update --init pic32prog/pic32probe pic32prog/pic32prog-kvh`.

## 1. The split: dumb dongle, smart host

The design puts almost nothing in the RP2040. The host program (`pic32prog`) owns the device
table, the Intel-HEX parser, the per-family programming algorithms and the Programming
Executive (PE) blobs; the dongle only knows how to wiggle three pins and run a handful of
primitives. The two talk over a vendor-class **USB bulk** pair (EP1 OUT / EP1 IN, VID:PID
16c0:05dc, identified by manufacturer/product strings) with a 4-byte header
`{u16 code, u16 len}` + payload, little-endian (`src/adapter.rs`, `src/usb.rs`):

| Request | Code | Dongle does |
| --- | --- | --- |
| ConnectReset | 0x0001 | pins to output, MCLR reset + "MCHP" key, (re)program the PIO clock divider from the requested ICSP Hz |
| Disconnect | 0x0002 | TAP to Test-Logic-Reset, MCLR low/high pulse, all three pins back to Hi-Z |
| GetIdCode | 0x0003 | JTAG IDCODE via the MTAP |
| ReadWordClassic / Micromips | 0x0004/5 | "serial execution": feed 6 MIPS instructions through EJTAG, read the word back via FastData |
| EraseChip | 0x0006 | MTAP command 0xFC + poll FCBUSY |
| LoadExecutiveClassic / Micromips | 0x0010/11 | push the PE loader + PE into RAM by serial execution, jump to it, read back its version |
| ExecutiveTransaction | 0x0012 | stream a PE command through FastData, collect the PE's answer until it reads from dmseg |

Status codes: 0 OK, 1 invalid arg, 2 code-protected, 3 timeout, 4 PE not loaded, 5 buffer
overrun. A second USB interface is a plain CDC-ACM bridge to the target's debug UART (baud rate
follows the host's line coding); a third is a tiny vendor "log channel" read by `usb-logread`.

## 2. Physical layer: PIO does the 4-phase ICSP

MIPS-core PIC32s (MX/MM/MK/MZ) expose **EJTAG over two wires**: each JTAG step is one
"4-phase" ICSP transaction of 4 PGC clocks carrying TDI, TMS, (unused), TDO on PGD. The dongle
runs this in a PIO state machine (`src/probe.rs`), 8 instructions, side-set = PGC, out/set/in
= PGD:

```
out pins,1  side 1 ; nop side 0      ; TDI
out pins,1  side 1 ; nop side 0      ; TMS
set pindirs,0 side 1 ; nop side 0    ; third clock: PGD released
in pins,1   side 1 ; set pindirs,1 side 0   ; TDO sampled on the 4th rising edge, PGD re-driven
```

Each 2-bit TX FIFO word = {TMS,TDI} (autopull, threshold 2); TDO bits accumulate in the ISR and
are read back with a forced `push` once the TX FIFO is empty and the SM is back at wrap_target.
The clock divider is `ceil(125 MHz / (2·f_icsp))`, default **1 MHz** ICSP clock. A sub-32-bit
read returns the ISR's top bits (`read_tdo_u8` = ISR >> 24). The PIO handles timing; the CPU
only does framing, so there is no busy-wait jitter in the data phase.

Entry (`iscp_connect_key_sequence`) is *not* PIO: the SM is stopped, pins driven by SIO,
sequence = PGC low + MCLR high → 1 ms → MCLR low → 1 ms → 32 key bits **MSB first** of
0x4D434850 ("MCHP") at 100 kHz (5 µs half periods) → PGC low → 1 ms → MCLR high → 1 ms →
SM restarted. Exit = 5 × TMS=1 (TLR) → MCLR low → one PGC pulse → MCLR high → pins Hi-Z.
The MCLR pad also gets the RP's **weak pull-up** (PUE) at boot so an unconnected MCLR idles high.

## 3. Logical layer (MIPS only)

After the key the dongle speaks JTAG: 5-bit TAP instructions (`MTAP_SW_MTAP` 0x04,
`MTAP_SW_ETAP` 0x05, `MTAP_COMMAND` 0x07, `ETAP_CONTROL` 0x0A, `ETAP_DATA` 0x09,
`ETAP_FASTDATA` 0x0E, …), MTAP 8-bit commands (status 0x00, assert/deassert reset 0xD1/0xD0,
erase 0xFC, flash enable 0xFE) and the EJTAG control register (PRACC/PROBEN/PROBTRAP bits).
"Serial execution" = check CPS, assert reset, `EJTAGBOOT`, deassert reset, then for every MIPS
opcode: wait PRACC, write the opcode into ETAP_DATA, clear PRACC. Programming goes through the
PE (per-family `.hex` blob in `pic32prog-kvh/pic32-pe*.h`) using FastData: commands
`PE_ROW_PROGRAM 0`, `PE_READ 1`, `PE_WORD_PROGRAM 3`, `PE_CHIP_ERASE 4`,
`PE_DOUBLE_WORD_PGRM`, `PE_GET_CRC`. The host adapter (`adapter-pic32probe.c`) implements
`get_idcode / load_executive / read_word / read_data / erase_chip / program_word /
program_dword / program_row`; without a PE it can only read.

`pic32prog-kvh` also ships `adapter-bitbang.c` + `bitbang/ICSP_v1E.ino`: an **ASCII-over-serial**
protocol (one char per 4-phase transaction, 4-bit packed symbols, PrAcc accumulation) that lets
an Arduino Nano act as the dongle. That is the closest published model of "host script drives a
dumb serial dongle", the pattern our `tools/rpcli.py` could grow into.

## 4. Applicability to minus (RP2354A → PIC32AK1216GC41048)

**The logical layer does not apply at all.** Our PIC32AK is a **dsPIC33A core**, not MIPS: no
EJTAG, no MTAP/ETAP, no Programming Executive. Its ICSP (DS70005583 §2–3, already transcribed
in `firmware/rp2354/pic_icsp.c`) is the dsPIC "serial instruction execution" scheme: 2-bit
command (CMDEXEC/CMDRD/CMDSEQWR/CMDSEQRD) + 32-bit opcode or VISI read, NVMCON driven directly
by MOV instructions, quadword (§3.3) and row (§3.4, 500 µs/row) programming, WR-bit polling.
`pic32prog-kvh/target.c` has no dsPIC / 33A / 32AK entry, so the host tool cannot be pointed at
our part either. Nothing in §3 is reusable; `pic_icsp.c` stays our own transcription.

**The physical/entry layer is the useful part.** Side-by-side:

| Aspect | pic32probe (MIPS PIC32) | PIC32AK spec / our `pic_icsp.c` | Verdict |
| --- | --- | --- | --- |
| Key | 0x4D434850 "MCHP", MSB first | 0x8A12C2B2 LSB first = bytes 4D 43 48 **51** "MCHQ" | Same on-wire framing, last byte differs; our LSB-first emission is correct |
| MCLR before key | high 1 ms → low 1 ms → key | low ≥1 ms → **pulse high ≤2 µs** → key (§2.2 step 5) | PIC32AK needs the extra pulse; we do it (≈0.2 µs) |
| MCLR after key | PGC low 1 ms, then MCLR high, 1 ms | MCLR high right after the 32nd falling edge, then ≥500 µs PGC low | ours matches spec |
| Post-entry | 5 TMS=1 to reach TLR | 2 × 34 clocks (`00` + 0x00801000) | ours matches spec |
| Key clock | 100 kHz, 5 µs halves | no minimum; we use ~1.2 MHz | **slow the key to ~100 kHz** as a free margin (TODO) |
| Data clock | PIO, 1 MHz, exact 50 % | bit-bang ~1.2 MHz (`busy_wait_at_least_cycles(60)`), min period 60 ns | fine; a PIO port is optional |
| TDO/VISI sampling | PIO samples on the 4th rising edge | spec: target updates PGD ≤20 ns after **falling** edge; we sample after the next rising edge | consistent |
| MCLR idle | RP pad weak pull-up, Hi-Z otherwise | Hi-Z, R5 10k on board | same idea; keep Hi-Z, do not add the pad pull-up (J1 may drive it) |
| MCLR drive | push-pull low/high during the session | push-pull in `icsp_enter`, Hi-Z in `icsp_exit` | same; needs **R53 = 0 Ω** on our board (open bench item) |
| Exit | MCLR low → PGC pulse → MCLR high → Hi-Z | MCLR low 1 ms, PGC/PGD Hi-Z, then release MCLR | ours matches spec |
| Pins | 3 GPIO + GND, target self-powered at 3.3 V | GPIO21/22/24 + R56/R57 0R, J1 Tag-Connect in parallel (47 Ω) | same topology |

**Architecture lesson worth taking.** pic32probe keeps the dongle generic and re-flashes nothing
when the target image changes; we embed the PIC hex in the RP image (`tools/hex2c.py`,
`pic_image.c`), so every PIC change rebuilds and re-flashes the RP. Both are valid: ours makes the
devkit self-contained (one USB port, `pic flash` with no host tool). A cheap middle ground, if PIC
iteration gets frequent, is a `pic raw` / streaming mode on the USB CLI (hex segments pushed by
`tools/rpcli.py`, programmed on the fly) — exactly the role `adapter-bitbang.c` plays for
`pic32prog`. Not needed for bring-up.

**What to borrow, concretely (now or later):**
1. Slow the entry key to 100 kHz (5 µs half periods) and add a `pic speed <khz>` knob — the
   first thing to try if `pic id` still returns 0xFFFFFFFF with MCLR verified low.
2. Status-code discipline: our CLI already prints timeouts; keep code-protect detection in mind
   (PIC32AK: a protected device still answers DEVID but refuses reads — check `pic verify` output).
3. If bit-bang jitter ever matters (it should not at 1 MHz), port the 2-bit-command + 32-bit
   shift to PIO the way `probe.rs` does: side-set PGC, `out`/`in` PGD, forced `push` for reads.
4. The `usb-log` channel idea (ring-buffer log over a vendor interface) is a nice debugging aid
   but our CDC console already covers it.

**Not applicable:** JTAG TAP commands, MTAP status/erase, EJTAG serial execution, PE loading,
`pic32prog` device table, the Rust/rp2040-hal toolchain (we are pico-sdk C on RP2354A).
