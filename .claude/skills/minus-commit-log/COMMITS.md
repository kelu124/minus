# Claude commits in the minus repo

Newest first. One row per commit Claude authored (all carry `Co-Authored-By: Claude`).
Maintained by the `minus-commit-log` skill on every commit; audit with
`git log --format='%h %ad %s' --date=short --grep='Co-Authored-By: Claude'`.

| Date | Commit | Subject | Why / what it enabled |
|------|--------|---------|------------------------|
| 2026-10-27 | `1bb6e51` | docs: bench conclusion — U2 silent with power/reset/sequence verified at its pins; replace the PIC | Power 3.28 V and MCLR 3.13 V at the chip: conclusion = replace U2. |
| 2026-10-27 | `8c472d4` | docs: pair-2 ICSP test also silent; remaining physical checks | Second pair silent too. |
| 2026-10-27 | `6776397` | feat(rp2354): pic pair 1|2 — ICSP via the PIC's second pair (fw 0.1.7) | Bypass pins 21/22 with one jumper to separate joints from a dead chip. |
| 2026-10-27 | `053bba5` | docs: LA capture prog1 proves the full ICSP entry at the PIC pins; PIC silent -> physical suspects | MCLR probe fixed; entire §2.2 sequence verified at J1 incl. the reset blip. |
| 2026-10-27 | `6fe5854` | tools: la_decode_icsp.py (decode sigrok captures of the ICSP entry); log LA findings | Owner's logic-analyser dump decoded bit by bit: key/opcodes correct on the wire. |
| 2026-10-27 | `d3b8b36` | docs: bench debug log — pic id still silent with R53 shorted; SWD pad pull-up finding | Systematic-debugging evidence trail. |
| 2026-10-27 | `8462b2a` | feat(rp2354): ICSP bench diagnostics — pic mclr rise, pic slow|fast, SWD pad pulls off (fw 0.1.6) | pic id still silent after the R53 fix; found the RP SWD pad pull-ups faking 'PIC alive'. |
| 2026-10-28 | `d43320b` | feat(pic32): CLK12 <nosc> diagnostic (pic 0.1.7 / rp 0.1.18); log trigger-period measurements and handoff | Board-2 bring-up night: see log session 05. |
| 2026-10-28 | `fbea3e3` | feat: acq [div [samc]] + RDY capture window timed by the RP (pic 0.1.6 / rp 0.1.17); board-2 bring-up logged; TODO_HARDWARE analog findings | Board-2 bring-up night: see log session 05. |
| 2026-10-28 | `cad3e91` | feat: first working RP<->PIC link and acq on board 2 — PIC UART pins fixed (pic 0.1.2), ACQ [div] with period-matched SAMC (pic 0.1.3 / rp 0 | Board-2 bring-up night: see log session 05. |
| 2026-10-28 | `d955c6d` | docs(TODO_HARDWARE): remove the Tag-Connect, use a plain 6-pin ICSP header | Board-2 bring-up night: see log session 05. |
| 2026-10-28 | `2e8d175` | docs: TODO_HARDWARE.md — corrections for the next devkit revision (ICSP reset path, JP1 default, SWD/J1, bus, LEDs, batch notes) | Board-2 bring-up night: see log session 05. |
| 2026-10-28 | `2ab4282` | docs: changelog/commit log — record the 2026-10-27 bench-debug commits; TODO RESUME HERE = replace U2 | Board-2 bring-up night: see log session 05. |
| 2026-10-28 | `a225141` | docs: changelog — record 1185885 under Committed | Board-2 bring-up night: see log session 05. |
| 2026-10-27 | `1185885` | docs: R17/R18 decision (keep; remove only as an isolation step if pic id still fails) | Owner asked whether to pull the RP-SWD↔J1 links with the R53 rework; netlist says they only add the RP's passive SWD pads to PGC1/PGD1. |
| 2026-10-27 | `6d40b42` | fix(acq): review pass — SCCP1 32-bit timer trigger, DMA status clear + overrun reporting, bounded ADRDY wait, Makefile acq.h dep, capped link drain, parser bounds n | Fresh-reviewer findings before the bench: trigger mode per datasheet §27.4.2.2, dropped samples now reported as `overrun`, no boot hang if the ADC fails, 20 Msps fallback really rebuilds. |
| 2026-10-27 | `7995e59` | docs: acq command (RP + PIC), link protocol v2, bench plan, TODO/DONE/changelog/memory | README/TODO/DONE/memory 0008 carry the new command and the bench expectation (fill ≈ 102 µs). |
| 2026-10-27 | `49a2f66` | feat(tools): rpcli.py --out=FILE saves the last reply (acq captures); untrack host test binary | Captures land in a file for plotting; removed a committed binary. |
| 2026-10-27 | `fbd29c7` | feat(rp2354): acq — fetch and print 4095 PIC ADC samples, host-tested header parser, link drain-until-idle, proto 2 (fw 0.1.4) | Owner-facing command; parser tested on the host (caught a rate-scaling bug); link recovery after timeouts. |
| 2026-10-27 | `c4cf6ca` | feat(pic32): ACQ — 4095-sample ADC1 capture via SCCP1 trigger + DMA0, proto 2 (fw 0.1.1) | The capture engine step 1: trigger/ADC/DMA/Timer1 chain + header/payload reply. |
| 2026-10-27 | `10d72d5` | feat(pic32): PLL 160/320 MHz clocks, UART baud clock fix (fw 0.1.1 wip) | ADC needs 320 MHz; found and fixed the 0.1.0 UART divisor (FUART = Fsys/2). |
| 2026-10-27 | `f647df4` | docs: acq implementation plan | Five-task plan (PIC clocks, PIC ACQ, RP acq + host tests, rpcli --out, docs) for inline execution. |
| 2026-10-27 | `5e07f2b` | docs: acq design (4095-sample ADC capture PIC -> RP), approved; log session 05 | Owner asked for a PIC ADC capture command; brainstormed (40 Msps, AN9, immediate start, values on console), datasheet-grounded design, builder-checked. |
| 2026-10-27 | `3823ffa` | docs: assess Microchip MDFU bootloader as an update path for the PIC32AK (log 05, TODO) | Owner asked whether a bootloader beats raw ICSP: relevant for field updates via UART + pymdfu, but blank boards and bootloader entry still need ICSP/MCLR, so the R53 + pic id path stays first. |
| 2026-10-27 | `2651219` | docs: pic32prog study — vendor kiffie/pic32probe + pic32prog-kvh as submodules, applicability to the PIC32AK ICSP driver | Owner asked how an RP programs a PIC32 (kiffie repos): confirmed pic32probe is MIPS/EJTAG-only, our dsPIC33A-style driver stays, slow-key knob queued for the bench. |
| 2026-10-26 | `b874cfb` | feat(claude): SessionStart resume hook + minus-resume skill; TODO RESUME HERE on top | Owner wants the next session to pick up from the last exchanges automatically: hook injects the context, skill says how to use it. |
| 2026-10-26 | `872b0df` | docs: persist bench findings + resume plan (MCLR 2.88 V, R53 -> 0R); add tools/rpcli.py | Session handoff: everything needed to resume the PIC flash after the R53 rework is in memory 0008, TODO and the private memory. |
| 2026-10-26 | `5b05ef2` | feat(rp2354): pic pins / pic mclr diagnostics (fw 0.1.3); log first on-hardware run | First real-board session: RP firmware and reboot dfu verified; PIC alive but no ICSP reply → bench diagnostics to separate the MCLR divider from firmware timing. |
| 2026-10-26 | `f3ed78a` | feat(rp2354): ICSP programmer for the PIC32 — pic id/image/flash/verify/erase (fw 0.1.2) | One USB-C cable programs both chips: the RP carries the PIC image and flashes it over GPIO21/22/24 (owner asked; embed-at-build chosen). |
| 2026-10-26 | `a28855d` | feat(pic32): first successful build with XC-DSC 3.31.01 (DFP linker script, bin2hex -mdfp) | Toolchain milestone: both firmwares build on this machine; the two XC-DSC link/hex gotchas are encoded in the Makefile. |
| 2026-10-26 | `9638149` | chore: programmer = Snap/PICkit Basic; ipecmd tool codes from installed MPLAB X 6.35; udev note | Owner chose a cheap programmer; wire the right ipecmd code into the Makefile and docs. |
| 2026-10-26 | `678fde8` | docs: list supported programmers for the PIC32AK (Snap, PICkit Basic, PICkit 4/5, ICD 4/5, ICE 4) | Answer "can I use something other than a PICkit?" from the MPLAB device-support list; cheaper Snap / PICkit Basic are valid. |
| 2026-10-26 | `ebb3e15` | docs(commit-log): correct sha of b6aef06 row; note the self-sha rule | Fix the one wrong sha produced by an amend; document why the newest row always lags one commit. |
| 2026-10-26 | `b6aef06` | docs: changelog — record e456800 under Committed; add COMMITS.md | Changelog bookkeeping + first version of this file. |
| 2026-10-26 | `e456800` | chore(skills): fix kicad-netlist-reading after retrieval test; add minus-commit-log skill | Close the gaps a fresh agent hit when following the KiCad skill; start the commit log the owner asked for. |
| 2026-10-26 | `1024135` | docs: changelog — record 276750c under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-10-26 | `276750c` | docs(pdfs): add MPLAB X / IPE / MDB user guides with markitdown siblings + index | Keep the Microchip tooling docs greppable next to the PIC32 toolchain work. |
| 2026-10-26 | `157de5a` | docs: changelog — record 3e33b15 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-10-26 | `3e33b15` | feat(firmware): STEP1.md, RP CLI (version/rgb/reboot dfu), semver rule, Makefiles, repo skills | Give the owner a step-by-step bring-up (STEP1.md), the requested CLI commands, the firmware semver rule, make-based builds, and reusable skills. |
| 2026-10-26 | `7c9480f` | docs: changelog — record 67576a0 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-10-26 | `67576a0` | feat: devkit KiCad project (minUS_10102026) + first inter-MCU link firmware | Bring the as-built devkit into the repo and start firmware: netlist-verified pin map, RP2354A link-test firmware (builds), PIC32 UART source, flaw list. |
| 2026-09-21 | `9575d82` | docs: changelog — record c8eb87d under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-21 | `c8eb87d` | docs: save design review findings + apply datasheet corrections across devkit | 2026-09-21 four-agent flaw review of the devkit concept; datasheet corrections (VREF=AVDD, op-amp specs, TC4427A). |
| 2026-09-21 | `7dd467a` | docs: changelog — record a05eef6 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-21 | `a05eef6` | docs(devkit): add standalone PCB design brief for handoff | One-file PCB brief a designer can work from. |
| 2026-09-21 | `84f635e` | docs: changelog — record 9ba7a33 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-21 | `9ba7a33` | docs(devkit): add shareable PCB designer brief (B1–B11) | (see docs/claude/changelog.md) |
| 2026-09-21 | `e19c11b` | docs: changelog — record 4a272f2 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-21 | `4a272f2` | docs: ADC input conditioning + TX-coupled acquisition + PIC32AK datasheet | (see docs/claude/changelog.md) |
| 2026-09-21 | `fcd8315` | docs: changelog — record a533a39 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-21 | `a533a39` | design(devkit): single-board, jumper-selected paths (no mezzanine) | (see docs/claude/changelog.md) |
| 2026-09-21 | `06681ee` | docs: changelog — record dced415 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-21 | `dced415` | design: add DesignA-DK devkit (derisking board) spec | (see docs/claude/changelog.md) |
| 2026-09-18 | `540bb80` | docs: changelog — record d66d17c under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-18 | `d66d17c` | design(A): Ubuntu CLI toolchain + reuse of kelu124/pic32arick blocks | (see docs/claude/changelog.md) |
| 2026-09-18 | `9c6644b` | docs: changelog — record d663709 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-18 | `d663709` | design(A): PIC32 direct-flash (ICSP), pulser drive-select jumper, mermaid | (see docs/claude/changelog.md) |
| 2026-09-18 | `9e3a84f` | docs: changelog — record 75ad246 (DesignA) under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-18 | `75ad246` | design: add DesignA — cheapest RP2354A + PIC32A pulse-echo badge | (see docs/claude/changelog.md) |
| 2026-09-18 | `25ca713` | docs: changelog — record f219638 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-18 | `f219638` | docs: LCSC prices for gain/LNA ICs (2026-09-18) | (see docs/claude/changelog.md) |
| 2026-09-18 | `61feef4` | docs: changelog — record 90cdf6a under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-18 | `90cdf6a` | docs(afe): LNA pairing for VGA-only parts (VCA810/AD603) | (see docs/claude/changelog.md) |
| 2026-09-18 | `e02915e` | docs: changelog — record 160c089 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-18 | `160c089` | docs: survey of RX gain ICs (LNA + variable gain / AFE), 1→8/16 channel | (see docs/claude/changelog.md) |
| 2026-09-18 | `639216a` | docs: changelog — record 0bbbd34 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-18 | `0bbbd34` | docs(pic32): confirm RP2354A internal flash + BOOTSEL wiring | (see docs/claude/changelog.md) |
| 2026-09-18 | `52fc147` | docs: changelog — record 3b3fba3 under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-18 | `3b3fba3` | docs(pic32): LCSC/JLCPCB availability check + footprint guidance | (see docs/claude/changelog.md) |
| 2026-09-18 | `1e008de` | docs: changelog — record bbd048a under Committed | Changelog bookkeeping: move the previous commit from Pending to Committed with its sha. |
| 2026-09-18 | `bbd048a` | docs: workshop activities, anti-requirements, PIC32A concept, PDF→md rule | (see docs/claude/changelog.md) |
| 2026-09-17 | `6a38407` | docs: rewrite root README as a project overview for visitors | (see docs/claude/changelog.md) |
| 2026-09-17 | `4b7c2c6` | docs: session-close log note + changelog catch-up | (see docs/claude/changelog.md) |
| 2026-09-17 | `828d364` | docs: record cheaper 8-bit ADC candidates to verify on LCSC (ADEC) | (see docs/claude/changelog.md) |
| 2026-09-17 | `4c6f5cb` | docs: real LCSC prices+URLs+stock in options; ADC bottleneck; TXRX-LINK question | (see docs/claude/changelog.md) |
| 2026-09-17 | `bc967b2` | docs: options.md trade study + priced CSV; gain alternatives; 5V/±5V HV | (see docs/claude/changelog.md) |
| 2026-09-17 | `bd81776` | docs: requirements — I2C OLED + Raspberry Pi 2x20 standardized extension header | (see docs/claude/changelog.md) |
| 2026-09-17 | `1078423` | docs: requirements — friendly-layout, test points, extension + external-HV headers | (see docs/claude/changelog.md) |
| 2026-09-17 | `1a6975b` | docs: requirements — plan OSHWA cert + reserve silkscreen for the mark/UID | (see docs/claude/changelog.md) |
| 2026-09-17 | `785d3c0` | docs: requirements v0.3 refinements — bipolar-if-cheap-rail, on-device DSP, RGB LED | (see docs/claude/changelog.md) |
| 2026-09-17 | `d7f7b79` | docs: requirements v0.3 — NDT workshop badge, 3-4 MHz unipolar, coded excitation | (see docs/claude/changelog.md) |
| 2026-09-17 | `b21abac` | docs: requirements v0.2 — RP2350 MCU, on-board USB-C, small/cheap/simple | (see docs/claude/changelog.md) |
| 2026-09-17 | `6b64555` | docs: draft requirements.md (v0.1) | (see docs/claude/changelog.md) |
| 2026-09-17 | `0dea95f` | analysis: routes + light-BOM pulsers; per-system 1-5 MHz + sampling attrs | (see docs/claude/changelog.md) |
| 2026-09-17 | `622bb3d` | survey: by-IC cross-ref (MSP430FR5043, TUSS4470) + Open Echo + design files | (see docs/claude/changelog.md) |
| 2026-09-17 | `6e0b07f` | survey: SIG-WUS OXP catalog data, FloPatch detail, BioGAP shield | (see docs/claude/changelog.md) |
| 2026-09-17 | `25b8e55` | survey: design files + Weik 2026 review + SIG-WUS, 4 new sheets | (see docs/claude/changelog.md) |
| 2026-09-17 | `0dd9e66` | survey: add IUP + MEMS-US, literature review, pdfs/ & design/ | (see docs/claude/changelog.md) |
| 2026-09-17 | `bab55c6` | survey: add kelu124-family + AFE-IC designs, scope 64+ out | (see docs/claude/changelog.md) |
| 2026-09-17 | `82c24e3` | survey: add lightweight ultrasound systems datasheets | (see docs/claude/changelog.md) |
| 2026-09-17 | `beffd20` | docs: set up Claude documentation & memory system | (see docs/claude/changelog.md) |
