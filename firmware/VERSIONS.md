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
| 2026-11-22 | rp2354 | 1.1.8 | review fixes (no protocol change, proto 14): acqos timing text 185 / 565 ns; embeds pic 1.1.5 |
| 2026-11-22 | pic32  | 1.1.5 | review fixes: `tof`/`env`/`RELOCK` use the standard capture settings; `acqos` div 37 / 113 + its own slow check; RDY held low ~8 µs before a capture / frame when PING left it high; `SPIX 0` drops RDY; ENV result zeroed on error and invalidated after ACQIL (`docs/bench/2026-11-22-pc-robust/`) |
| 2026-11-22 | rp2354 | 1.1.7 | **proto 14**: `fmt [text\|b64]` (base64 sample output: 11.4 KB / 30 ms instead of 24.8 KB / 110 ms; shared `print_samples`, `link_b64_encode` + host test), `tgc [off \| <t_us> <leg> ...]` (4052 gain-leg steps during each capture, run from the RDY window in acq/pe/acqos/tof/env; restored after), `acqos` RF warning; embeds pic 1.1.4 |
| 2026-11-22 | pic32  | 1.1.4 | **proto 14**: `ACQ` resets navg to 1 unless given (it used to persist) |
| 2026-11-22 | rp2354 | 1.1.6 | **proto 13**: `acqos <4\|16> [in [pe]]` (ADC oversampling capture), `tof <thr> [blank_ns [in [ref]]]` (pulse + time of flight on the PIC, one line), `env <dec> [shots [in]]` (pulse + on-PIC envelope, multi-shot average); shared slow-retry / RELOCK loop; embeds pic 1.1.3 |
| 2026-11-22 | pic32  | 1.1.3 | **proto 13**: `ACQOS` (MODE 11 oversampling 4 / 16, 13 / 14-bit, div raised to fit), `TOF` (channel-0 comparator out of [ref±thr] + first-crossing / peak search), `ENV` (|x−mean| integrate-and-dump, running average in the acqil buffer as u32); `pe_ext.c` |
| 2026-11-22 | rp2354 | 1.1.5 | **proto 12**: `SPIX` without reply — waits for RDY high, then clocks; SPI **mode 1** (the PL022 in mode 0 left a 1-bit gap per byte, +19 %): 5.7 ms per capture at 12.5 MHz, 25 MHz now clean (3000/3000); `link_frame_check` takes n from the ACQ header (no reply CRC); `acq`/`pe` send `RELOCK` after 3 slow captures and restore UGE; link idle window 50 → 2 ms; capture text written in 4 KB blocks (185 → 107 ms per `acq` end to end); embeds pic 1.1.2 |
| 2026-11-22 | pic32  | 1.1.2 | **proto 12**: `SPIX` announced on RDY (low → preload → high → feed → low), CRC-32 computed while feeding, no UART reply (`SPIX 0` if nothing pending); SPI1 mode 1 (CKE 0); **slow-lock self-heal**: at boot test 8 captures and re-lock PLL1 (≤ 12 times) until none is slow (19/20 boots clean vs 10/20 before), `LOCK?` / `RELOCK` |
| 2026-11-21 | rp2354 | 1.1.4 | **proto 11**: capture payload pulled as an SPI0 frame (12.5 MHz default, `link [uart\|spi [MHz]]`, CRC-32, UART fallback; `link_frame.c` + host test), `linktest [count [MHz]]`, `dac …` (PIC DAC1 test signal); `acq` reports when all 8 captures were `slow`; USB strings manufacturer `kelu124` / product `minUS badge` (serial = unique id); embeds pic 1.1.1 |
| 2026-11-21 | pic32  | 1.1.1 | **proto 11**: `ACQ`/`ACQCPU`/`ACQIL` reply header only; `SPIX` (SPI1 client frame), `UTX` (UART payload), `XTEST [seed]` (LFSR), `DAC 0..3` (dc / hardware triangle / DMA sine on DACOUT1, clock PLL2 → CLKGEN7 500 MHz, factory trims from FPDMDAC) |
| 2026-11-20 | rp2354 | 1.1.3 | `version` "board:" line and boot banner print `minus v1.1` (the `minUS_08112026` name is dropped); no functional change; proto 10; embeds pic 1.1.0 |
| 2026-11-19 | rp2354 | 1.1.2 | `rgb R G B [pct]`: LP5562 brightness in % (0–100, **default 25** = dim), scales the PWM; reply `rgb R G B pct% (LP5562 0x30: ok\|not found)`; WS2812 line unscaled; proto 10; embeds pic 1.1.0 |
| 2026-11-19 | rp2354 | 1.1.1 | `rgb R G B` also drives the **LP5562 U5** (I²C 0x30, internal clock, I²C PWM control) → reply `rgb R G B (LP5562 0x30: ok\|not found)`; `i2c` names 0x30; proto 10; embeds pic 1.1.0 |
| 2026-11-19 | rp2354 | 1.1.0 | **owner: v1.1** (MAJOR.MINOR set by the owner). FW_NAME `minus-rp2354`; `version`/banner/help print `minus v1.1 (minUS_08112026)` instead of the devkit name; no functional change; proto 10; embeds pic 1.1.0 |
| 2026-11-19 | pic32  | 1.1.0 | **owner: v1.1**. FW_NAME `minus-pic32` (`ID?` → `PIC32AK1216GC41048 minus-pic32 1.1.0 proto 10`); no functional change; proto 10 |
| 2026-11-19 | rp2354 | 0.1.34 | `acq_receive` re-shoots on PIC status `slow` (`pe` and `acq`, ≤ 8, no payload transfer); proto 10; embeds pic 0.1.25 |
| 2026-11-19 | pic32  | 0.1.25 | **ACQ status `slow`**: fill > expected + 5 % (smallest multiple of the trigger period ≥ 32 ns, SAMC 0, navg 1) → no payload, so a re-shot costs ms instead of 0.76 s; proto 10 |
| 2026-11-19 | rp2354 | 0.1.33 | `pc [0\|1]` (pattern-correction state + last offsets); proto 9; embeds pic 0.1.24 |
| 2026-11-19 | pic32  | 0.1.24 | **period-4 fixed-pattern correction** in `acq_run`/`acq_run_adc2` (per-phase mean of samples 64..N minus the mean, 1/16 LSB, clamped; navg 1 only; on at boot), `PC 0\|1` / `PC?`; proto 9. Bench: σ 8.94 → 3.57 LSB at ×1, residual pattern 0.17 LSB rms (`docs/bench/2026-11-19-pc/`) |
| 2026-11-19 | rp2354 | 0.1.32 | `pe` retries (up to 8 shots) when the fill exceeds 4095 × 40 ns + 5 % (ADC locked to the 40/60/60 ns pattern); `acq_receive` returns a status |
| 2026-11-19 | rp2354 | 0.1.31 | `gain [leg [u1 [u2]]]`: 4052 selects GPIO25 (S0) / GPIO23 (S1) driven low at boot, PIC `UGE` per stage; gain printed in the `pe` header; proto 8; embeds pic 0.1.23 |
| 2026-11-19 | pic32  | 0.1.23 | `UGE a1 a2` link command: AMP1/AMP2 `UGE` (unity-gain, internal OUT→IN−), amp disabled around the change; proto 8 |
| 2026-11-19 | rp2354 | 0.1.30 | **pulser** on board 3: `pulser.pio` (pio1 SM0, GPIO8/9 → U3 → Q2/Q1, idle set first in `main`), `pulse [hi [lo [dead]]]` one shot, `pe [hi [lo [in [dead]]]]` pulse-echo (shot on the PIC's RDY rise = ADC start, then `ACQ 4 0 <in> 1`); `acq` input codes 0..31, default 25; proto 7; embeds pic 0.1.22 |
| 2026-11-19 | pic32  | 0.1.22 | **ADC2 capture**: input codes 16..31 = ADC2 PINSEL (+16), `acq_run_adc2` (AD2CH0 on SCCP1, DMA0 CHSEL 0x40); default input 25 = AD2AN9 (PIC32_ADC on board 3); op amp 2 on at boot; proto 7 |
| 2026-11-02 | rp2354 | 0.1.29 | `i2c` bus scan, `pot <0|1> [n]` MCP4531 wiper read/set (U11 = OA2 feedback, gain print); proto 6; embeds pic 0.1.21 |
| 2026-11-02 | pic32  | 0.1.21 | `AMP2 0\|1` op amp 2 enable (OA2: IN+ = OA1OUT, IN- = U11 wiper / R49, OUT = FE_A_OUT); proto 6 |
| 2026-11-02 | rp2354 | 0.1.28 | clock-change strings: SCCP counts are 5 ns, `acq 8` = 25 Msps, `acqil` default div 24 (120 ns), 32 ns conversions; embeds pic 0.1.20 |
| 2026-11-02 | pic32  | 0.1.20 | **CPU 200 MHz / ADC 250 MHz** (PLL1 VCO 1000: FBDIV 125, POSTDIV1 5, VCO1DIV INTDIV 2; datasheet "clocks_initialize" recipe): DMA 40 ns = 25 Msps at div 8, Timer1 tick 80 ns (`ACQ_TICK_NS`), SAMC auto for TAD 16 ns, heartbeat 5e6; default `ACQ_TRIG_DIV` 4 (20 ns triggers -> uniform 40 ns comb; div 8 proved to sit on the DMA edge). 160/320 MHz until 0.1.19 (commit 963d11a and before) |
| 2026-10-28 | rp2354 | 0.1.27 | `acqil [div [off [navg]]]` two-channel interleave (20 M 2-sums/s); proto 5; embeds pic 0.1.19 |
| 2026-10-28 | pic32  | 0.1.19 | `ACQIL [div [off [navg]]]`: ADC1 CH0 (SCCP1) + CH1 (SCCP2, preloaded offset) integration sums, DMA0 + DMA1 into two halves merged into `acq_buf`; proto 5 |
| 2026-10-28 | rp2354 | 0.1.26 | `acq [div [samc [in [navg]]]]` (0.1.19/0.1.20), `acqcpu [trg [rptcnt [gap [phase]]]]` CPU-loop experiment (0.1.21–0.1.26, default trigger = SCCP1), default div printed as 8, help for `raw AMP1` / `raw ADCBB`; embeds pic 0.1.18 |
| 2026-10-28 | pic32  | 0.1.18 | `ACQ [div [samc [in [navg]]]]` (input select + op amp 1 on at boot + `AMP1 0\|1`, 0.1.8; integration-mode `navg`, 0.1.11); **bus-quiet DMA wait loop** (0.1.9/0.1.10 — the tight poll duplicated samples); `ADCBB` ADC throughput test (0.1.12); `ACQCPU` CPU-loop reader with trg/gap/phase knobs (0.1.13–0.1.18); default `ACQ_TRIG_DIV` 8 = 20 Msps (0.1.17) |
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
