# TODO

Open work items for **minus**. Newest ideas at the top of their section.
When an item is finished, move it to [`DONE.md`](DONE.md) with the date.

## Now

- **RESUME HERE (2026-11-22 night, session 13): rp 1.1.7 / pic 1.1.4, proto 14 on board 3** (no piezo on the bench). Done
  tonight: SPI payload (5.7 ms), slow-lock self-heal, ADC extras (`acqos`/`tof`/`env`), `fmt b64` (30 ms per capture over USB),
  `tgc` gain steps (~17 µs switch transient), `navg` reset, live viewer (`python3 -m minus.live`, Jupyter `LiveView`,
  notebook 04). Next:
  (a) **with a piezo**: run `tof` / `env` / the live viewer on real echoes (thr / blank from a `pe`), try `tgc` on a deep
  target and judge the 17 µs switch transient; (b) TGC without the transient = hardware (make-before-break or a parallel Rf
  switched in; TODO_HARDWARE); (c) RP ADC0 read of the DAC once v1.2 has the DACOUT1 → GPIO26 trace; (d) an external sine
  generator for the ADC ENOB test; (e) re-measure the E3 comb slips on a good lock; datasheet E2 (per-lock state, self-heal)
  and the new commands at the next datasheet rev.
- **Closed / parked 2026-11-22** (from the older resume points below): faster link (SPI, proto 11–12); LP5562 `rgb` (rp 1.1.1);
  GPIO9 pull-up (R70, v1.2); `acq` retry on slow + slow-lock root cause (per-PLL-lock state, boot re-lock + RELOCK);
  "`acq` should reset navg" (pic 1.1.4); TGC (`tgc`, rp 1.1.7); averaging over shots (`env … shots`); PC viewer
  (`minus.live`); `reboot dfu` returning to the app — **not reproduced** in ~15 reflashes on 2026-11-21/22, parked (ask the
  owner for SW2 BOOTSEL if it comes back); PLL2 → 320 MHz ADC clock (40 Msps) and the +425 LSB offset of the CPU-loop reader
  → **Someday** (see there).
- **RESUME HERE (2026-11-19, session 12): minus v1.1** — rp 1.1.1 / pic 1.1.0 (proto 10) flashed on board 3; `rgb` drives the
  LP5562; Python library `python/library/minus` + notebooks; fwsync hooks; E3 jitter study (`docs/bench/2026-11-19-jitter/`):
  φ uniform-ish over one sample (11.3 ns rms, independent shots) **plus whole-sample comb slips in 14 % (37 µs) / 31 % (76 µs) of
  captures**, phase-dependent. Next: (a) root-cause the slips + slow lock (start SCCP1 from the ADC clock domain / time-stamp
  conversions; check slips with `acq` on a CW tone); (b) host-side shot rejection on slips in the library (`Capture` helper);
  then the older items below (sine ENOB, scope pulse, LNA gain, supply current,
  faster link).
- **RESUME HERE (2026-11-19, part 6): datasheet rev 0.1 done** (`datasheet/`, rp 0.1.34 / pic 0.1.25, proto 10).
  Next: sine test (SINAD ENOB), measure the pulse on a scope (TX node, effective t_hi + 48 ns), LNA gain at 3 MHz, supply current,
  drive the LP5562 RGB (I²C 0x30) instead of WS2812, faster RP↔PIC link (115 200 Bd = 0.71 s/shot), sample-comb phase fix.
- **RESUME HERE (2026-11-19, part 3): gain works on board 3** (rp 0.1.32 / pic 0.1.23, `gain [leg [u1 [u2]]]`, sweep in
  `bench/2026-11-19-gain/`). Next: (a) root-cause the ADC 40/60/60 ns lock (start phase SCCP1 vs ADC; `pe` retries for now; plain
  `acq` has no retry yet); (b) `reboot dfu` intermittently returns to the app instead of BOOTSEL (since 0.1.30?); (c) TGC = gain
  steps during the A-line (mux + UGE switching mid-capture, e.g. timed by the RP); (d) LNA-tap baseline 1.06 V; (e) averaging over
  shots + a PC viewer; (f) TODO_HARDWARE GPIO9 pull-up; OA2 measured 10–20 % above nominal (Ron/C44?).
  **Noise (part 4, `bench/2026-11-19-noise/`):** (g) period-4 fixed pattern on all external ADC inputs (fs/4, fs/2; ~10.5 LSB rms,
  gain-independent) → subtract per capture in firmware/host, then hunt the coupling (DMA/SFR traffic, AVDD); (h) 2.72 MHz + 0.49 MHz
  interference entering at the front end (in band at high gain); (i) LNA output = 26 mV rms aliased wideband noise at AD1AN1 → check
  for LNA oscillation; (j) sine test (DS203 generator) for a real SINAD-based ENOB.
- Check `HPEN = 1` on OA2 in the `AMP2` code (session 09).
- **RESUME HERE (2026-11-02 evening): pic 0.1.20 / rp 0.1.28 = CPU 200 MHz / ADC 250 MHz on board 2; `acq` default
    div 4 = uniform 25 Msps (tone-proven, session 08 part 2, memory 0011). Open from the change: PLL2 → 320 MHz
    ADC clock (restores 40 Msps core, un-parks `acqil`, then 5-cycle CPU loop); `acq` should reset `navg` when not
    given (it persists on the PIC and silently poisons the next capture).**
  - **OA2 gain (owner asked 2026-11-02, memory 0012):** firmware side done (pic 0.1.21 `AMP2`, rp 0.1.29 `i2c`/`pot`; U11 answers at
    0x2E, wiper 64 = ×6.08 at power-on, settable ×1.07–×11.07). Still to do: (a) **measure** it: `raw AMP1 0`, tone into J6.1,
    `raw AMP2 1`, `pot 0 <n>`, read J6.2/RF13 (scope) or U.FL RF13→RF7 + `acq 4 0 9`; (b) **hardware**: MCP4531-103 in the
    feedback caps OA2 at ~1 MHz (datasheet −3 dB 1 MHz, CW 120 pF) — rethink (5 k part, fixed R + switch, or pot as a
    DC control only); (c) ADC2 capture of AD2AN1 (= FE_A_OUT) so OA2OUT can be read without cabling.
    **Direction (2026-11-02, part 4): GPIO-switched gain legs, no digipot, no VGA** (BOM/simplicity). Owner rework: lift U11,
    10 k J6.2–J6.3, 1 k + 2.2 k from J6.3 to H2.1 (RD6) / H2.4 (RD5) → Claude adds `GAIN <mask>` on the PIC, then measure the
    steps with the tone (J6.1 in with `raw AMP1 0`, RF13 → RF7 U.FL out, `acq 4 0 9`). Design-level: AD8338, MCP4531 ×2,
    MCP4131 ×2, MCP4728 leave the minimal BOM; TGC = GPIO steps during the A-line + software.
- Was: **RESUME HERE (2026-11-02): tone test done (session 08, `bench/2026-11-02-tone/`). 1 MHz square at
    RF7/H6 (PIC32_ADC node): `acq 8` = 20 samples/period clean; `acq 4` = 20 too (DMA ceiling proven);
    `acqcpu` at 25 ns = every value twice at 7 of 9 phases, phases 3/7 un-duplicated but +425 LSB offset
    (not usable); `acqil 16` = DMA at its ceiling, CH1 loses every other trigger in 3 of 4 runs.**
    Next: (1) ~~clock change~~ done (pic 0.1.20); later PLL2 → 320 MHz ADC + 5-cycle loop for raw 40 Msps; (2) chase the +425 LSB offset of the un-duplicated CPU reads (which
    ADC register/correction stage is being read?); (3) reproduce the intermittent slow `acq 8`
    (218–232 µs, scrambled periods, 2 of 5 runs — interrupt/SFR traffic during capture?);
    (4) fix the RX-node bias (TODO_HARDWARE: D7/R28/R36) so OA1 stops sitting at the rail, then
    `acq 8 0 0` with the transducer. Note: there is no "ADC SMA" — RF7 is IPEX, H6 the pin header.
  - `acqil 16` cannot be the default capture until the DMA has margin (200 MHz CPU) or a fill-time
    check retries a half-speed run (fill 412 µs instead of 206 µs).
  - Also: the wait loop could use the DMA0 interrupt + `pwrsav #1` instead of the NOP poll (zero SFR
    traffic during the capture); `acq` default input should be settable once (`acq in <n>`).
  - Board 1: replace U2 (dead PIC) when convenient; remove its H2.16–CN1.17 jumper first.
- **Was: RESUME HERE (2026-10-28): replace U2** (PIC32AK1216GC41048-I/PT, LCSC C46545915). Bench
    proof 2026-10-27: R53 shorted, MCLR 0.2 V low / 3.13 V released at pin 48, 3.28 V at the chip,
    full ICSP entry sequence verified on the pins with a logic analyser, silent on pairs 1 and 2.
    Before the swap remove the H2.16–CN1.17 jumper. Then `pic id` (fw 0.1.7, pair 1 fast) →
    `pic flash` → `ping` → `acq`.
  - Previous resume text: owner bridges **R53 → 0 Ω** (done 2026-10-27; JP1 already cut). Then `pic mclr low` + meter on J1.1 (≈ 0 V) →
    `pic mclr hiz` → `pic id` (DEVID 0x09DA2053) → `pic flash` → `ping` → **`acq`** (expect
    `fill≈102us fs≈40Msps`; if lower or `status=timeout`, set `ACQ_TRIG_DIV 8` = 20 Msps and
    rebuild both). If `pic id` still fails, debug `pic_icsp.c` entry timing (scope / slower
    clock) or compare with the Snap. Optional isolation step before scoping: remove **R17/R18**
    (RP SWD ↔ J1/PGC1/PGD1 links); costs only RP SWD on J1.
  - From the pic32probe study (`pic32prog/README.md`, memory 0010): first knob = slow the
    entry key to ~100 kHz (5 µs halves) + add `pic speed <khz>`; then scope PGC/PGD/MCLR.

- **acq review minors (deferred):** read AD1CH0DATA before `CHEN=1` (stale sample 0); don't print `fs` on
  non-ok status; `rpcli --out` should exit non-zero when the reply is not a capture; fix the
  indentation of the `stat` dispatch line; heartbeat divider is a loop count.
- **acq follow-ups:** `acq trig` (arm, start on the RP TRIG edge); FE-A full path input (OA2OUT = AD2AN1,
  needs an ADC2 channel); faster link baud or packed 12-bit payload (8190 B at 115200 = 0.7 s per capture).
- **pic32prog follow-ups (optional, after `pic id` works):** PIO port of the 2-bit-cmd + 32-bit
  shift (exact timing, as `pic32probe/src/probe.rs`); `pic raw` streaming mode so
  `tools/rpcli.py` can push a hex without rebuilding the RP image (pic32prog `adapter-bitbang`
  pattern); row programming (§3.4) for speed.
- **MDFU bootloader option (decide after `ping` works):** Microchip `dspic-bootloader-mdfu`
  (dsPIC33AK demos, UART/CAN-FD, `pymdfu` host) ported to the PIC32AK1216; RP ICSP then only
  installs the bootloader once, app updates go over the existing UART with the RP as a
  USB-CDC↔UART bridge. Check footprint, linker layout and MCC support for our part first.

- **Devkit firmware bring-up** (`firmware/`, see `firmware/README.md`, memory 0008):
  - ~~Install MPLAB X + XC-DSC~~ done 2026-10-26 (6.35 / 3.31.01); **both firmwares build**.
  - Get an **MPLAB Snap or PICkit Basic** + TC2030-NL cable; flash `firmware/pic32/build/minus_pic.hex`
    (`make -C firmware/pic32 flash`).
  - Board fixes before the link test: **R68/R69 → one 1–4.7 kΩ** (MOSI–MISO), **R53 → 0 Ω**
    (MCLR drive), cut **JP1** (C31 on MCLR) when programming from the RP.
  - First flash: confirm `ipecmd.sh -TPSNAP -P32AK1216GC41048 -F … -M -OL` works (codes verified
    in the installed readme; the option set itself is untested on hardware).
  - Run the UART PING/PONG test (`ping` / `auto` on the RP USB console); confirm RDY/TRIG.
  - Measure the real R53 / R5 values (board unpowered) and record them in
    `design/devkit/review-findings.md`. Optional: row programming (§3.4) for speed.
  - Step 2: PIC SPI client + ADC capture → RP.
  - Fold the 2026-10-26 flaws into `design/devkit/review-findings.md`; add `hardware/` to the
    docs conventions (design files now live there, not only `design/`).

- Requirements v0.3: NDT/workshop-badge, 3–4 MHz, unipolar, A-/M-mode, RP2350 + USB-C,
  provided piezo, coded excitation, multi-connector, derisk-by-reuse (DP5) all locked.
  Only ADEC (external ADC choice) + exact HV level remain open.
- Confirm **RF-ACCESS** (raw RF vs envelope) — gates the external-ADC section.
- Pick from `options.md`: pulser (U0/U1/U2/B0), gain (AD8338 vs AD8331), ADC
  (AD9200/AD9235); refresh `options_prices.csv` from live LCSC (qty 20–50).
- Then draft a **costed BOM + block diagram** reusing un0rick/pic0rick blocks on RP2350.
- **PIC32A concept** (`design/pic32/`): evaluate RP2350 + PIC32AK3208GC41064 (on-die
  40 Msps ADC + 100 MHz op-amps) as an alternative to external ADC+VGA. Open:
  - ~~LCSC stock for the PIC32A~~ → resolved 2026-10-26: 48-pin PIC32AK1216GC41048 is LCSC C46545915 (in the devkit BOM).
  - Verify whether the PIC32A op-amp has an **internal PGA (GSEL) ladder** (→ per-line
    gain with zero extra parts) or needs an external **digipot/MDAC/resistor-mux**.
  - Check PIC32A op-amp **input noise** vs echo level → decide if a fixed **LNA** (A3a)
    first stage is needed.
  - Decide TX sequencer ownership (PIC32A HS-PWM+PTG vs RP2350 PIO) + inter-MCU SPI
    protocol; test **ICSP-from-RP2350** (one USB port programs both).

## Next

- Firmware text cleanup at the next rp PATCH bump (2026-11-20): RP `help()` (`reset` "needs R53", `raw AMP2` U11, `i2c`/`pot` MCP4531/OLED), `pic help` ("R53 = 0R, JP1 cut, J1"), `i2c_name`, `firmware/pic32/Makefile` header (J1 Tag-Connect) still describe the devkit; `firmware/README.md` is the board 3 truth.

- **Firmware for board 3 (v1.1) (memory 0014):** ADC2 capture of AD2AN9 (filtered node) with ADC2 DMA trigger;
    dual-gain capture ADC1 (OA1OUT/LNA) + ADC2; gain command = RP GPIO25/23 (4052 S0/S1) + PIC `AMPxCON1.UGE` per stage.
- **Board redesign candidate — RX LNA (owner 2026-11-06, memory 0013):** BGA2817 MMIC (24 dB, 3.3 V, LCSC C2654187)
    ahead of OA1, with the FE-A bias/coupling fixes (TODO_HARDWARE). No devkit test now; bench-check its 1–5 MHz gain
    when the redesign is prepared.
- (optional) Mirror the full BioGAP Altium source + gerbers, and the Open Echo
  firmware/Python interface, if wanted beyond the current schematic+fab files.
- Sheet remaining leads: Measurement-2024 compact modular platform (32 el., get PDF
  → `pdfs/`), rtl-ultrasound (Meng 2019, SDR), compressive single-sensor 3D
  (Kruizinga 2017); optionally Bashatah (chirp) + Wang (Barker) from Weik Table I.
- Confirm lit3rick `[E]` fields from `design/lit3rick/lit3rick_schematics.pdf`.
- Collect more design files (IUP if released); add `design/` subfolders as sheeted.
- Fill survey gaps: EchoLite (await IEEE IUS 2025 paper), PuLsE/USoP MCU parts & TX
  voltages, pic0rick dimensions/SNR.
- Advance `analysis.md`: fix minus target frequency, unipolar vs bipolar, pick
  pulser (STHV748 vs MD1213+TC6320 vs unipolar), ADC + controller; then draft a BOM.
- Decide which reference systems `minus` derives from (kelu124 family / IUP / WULPUS
  / PuLsE / TUSS4470 route).

- Define target application, imaging depth, and centre frequency.
- Choose the single-element transducer and how (or whether) it scans.
- Decide pulser / analog front-end approach.
- Decide digitizer / ADC and sampling strategy.
- Decide compute/host (MCU, FPGA, PC) and display path.

## Someday / maybe

- **40 Msps raw** (PLL2 → 320 MHz ADC clock, `acqil` un-parked, 5-cycle CPU loop) and the **+425 LSB offset** of the
  un-duplicated CPU-loop reads: parked 2026-11-22. Any capture into RAM is capped by the DMA at 40 ns/sample (25 Msps)
  whatever the ADC clock; the only 40 Msps routes are the CPU-loop reader (duplicates + the offset) and the two-channel
  interleave (no bus margin). 25 Msps = 7.5 samples per 3.3 MHz period is enough for this probe, and re-clocking the ADC now
  risks the slow-lock behaviour that was just tamed. Revisit only for a ≥ 7 MHz transducer.

- Review prior work in sibling repos (e.g. `we_gate`) for reusable pieces.
