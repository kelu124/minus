# 0022 — Lessons learnt, session 13 (2026-11-20/21)

**Status:** current · type: feedback/reference · companion of [[0019-lessons-session-11]] and [[0021-spi-link-and-dac]]

## Sources
- The PIC32AK datasheet **DS70005592** (PDF + a text `.md` export) is no longer in the repo (2026-11-19 cleanup); it is in the
  owner's desktop Trash: `~/.local/share/Trash/files/pdfs/datasheets/PIC32AK1216GC41064-family-datasheet-DS70005592.{pdf,md}`
  (+ product brief DS70005582, programming spec DS70005583). Read it in place, do not restore or move it. `grep -n` on the `.md`
  is the fast way in (register tables are mangled, prose and electrical tables are fine).
- **Register names: trust the device header, not the datasheet examples** (`…/PIC32AK-GC_DFP/1.1.53/xc32/support/PIC32A/h/
  p32AK1216GC41048.h`): e.g. the examples write `SLP1CONbits`, the header has `DAC1SLPCONbits`. Enumerate peripherals with
  `grep -oE "#define (PG[0-9]CON|DMA[0-9]CH|…) "` before promising a feature.

## PIC32AK peripherals
- Only **16 KB RAM** (0x4000–0x7FFF, DMA window = all of it); the capture buffers take ~12 KB. Stream, don't copy.
- The capture DMA runs at its bus ceiling: **any other DMA during a 20–25 Msps capture costs samples** (the DMA sine made
  12/12 captures `slow`). Test such interactions by counting `raw ACQ …` statuses, not by eye.
- DMA cannot be triggered by an SCCP timer period (CCTx); use **dual 16-bit timer mode**: the secondary timer's match raises
  CCPxIF (DMA trigger "CCPx IC/OC"). Its period is **PRH + 2** counts (same off-by-one family as SCCP1's note in acq.c).
- PIC SPI client tops out at **25 MHz** (SP10); on board 3, 25 MHz fails every frame, 18.75 is clean. RP SPI clocks are
  150 MHz / even divisors: 25, 18.75, 15, 12.5, …
- The first UART link line after an RP reboot is often unanswered (known since session 12) — retry before concluding.

## Analysis
- A 4095-sample, 164 µs capture has **6 kHz FFT bins**: measure periods from interpolated crossings, never from the FFT peak.
- Write the test before the frame checker: it caught a check-order bug (a header mismatch must be reported before a length
  mismatch, because the RP reads the length the reply announced).

## KiCad by script (no GUI)
- Schematic edits as text work; **always verify with `kicad-cli sch export netlist` + `nets.py`**, then render the sheet
  (`kicad-cli sch export svg` → inkscape PNG, crop with the sheet's paper size: A4 297 / A3 420 / A2 594 mm).
- Global label orientation: angle 90 draws the label body *below* its connection point, 270 *above*, 180 to the left.
  A vertical stub dropped across a stack of pin wires is electrically fine but reads as ambiguous: put the label at the
  wire's free corner instead.
- PCB placement with pcbnew: the free-space test must include **F.Cu tracks, vias and silk text**, not just footprint
  bounding boxes (first try put R69 on a GND via, R71 on a PWM track). Check with
  `kicad-cli pcb drc --schematic-parity --refill-zones` against the baseline (17 clearance = QR code).
- When the owner has uncommitted PCB / production edits (board open in KiCad), **do not write the .kicad_pcb**; tell them to
  run Update PCB from Schematic (F8) and leave hardware/ out of commits.

## Tooling
- The rtk hook rewrites commands; in auto mode a rewritten call can get "no verdict" — re-issue exactly the rewritten text.
- Library parsers: `_fail_if_error` treats any `<cmd>: ` line as an error; commands whose normal output starts that way
  (`link`, `linktest`, `dac`) use `_fail_on_usage`.
