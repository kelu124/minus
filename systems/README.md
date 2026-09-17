# systems — lightweight ultrasound acquisition survey

A survey of "lightweight" / low-cost single- and few-channel ultrasound
acquisition designs, used as background for **minus**. Sources: the
[wulrick extended platform survey](https://github.com/kelu124/wulrick#othersystems-extended-platform-survey)
and its `OtherSystems/` files, each system's primary papers/repos, and online
datasheets. **Scope:** single- to few-channel designs; **64+ element systems are
out of scope** (listed at the bottom for context only).

- **[`TEMPLATE.md`](TEMPLATE.md)** — the datasheet template. Copy into a new
  subfolder as `<slug>/<slug>.md` and fill it in. Covers MCU/FPGA, pulser
  (polarity/voltage), acquisition route, ADC, gain/TGC, connectivity bandwidth,
  wireless, channel scheme, performance, and power.
- **[`literature.md`](literature.md)** — broad literature review (≤32-element
  designs) distilled from the Jonveaux et al. 2022 open-hardware survey, plus
  component menus (pulsers, HV, TGC, ADC, AFE) and single-element B-mode strategies.
- One subfolder per design/product. Source/confidence tags in each sheet:
  `[D]` datasheet/repo · `[P]` paper · `[S]` slides/survey · `[E]` estimate · `?` unknown.
- Source PDFs live in [`../pdfs/`](../pdfs/) (see its README).

## Systems at a glance

| System | Year | Arch | Channels | Pulser | ADC | Gain/TGC | Link | Power | Sheet |
|--------|------|------|----------|--------|-----|----------|------|-------|-------|
| **Murgen** (echOpen) | 2016 | MCU + modules | 1 | HV module | external | VGA (TGC) | USB | ? | [murgen](murgen/murgen.md) |
| **un0rick** | 2019 | FPGA (iCE40HX4K) | 1 | 25/50/75 V unipolar | 65 Msps ext. (10-bit) | TGC (AD8331+DAC) | SPI/USB/RPi | ~2 W | [un0rick](un0rick/un0rick.md) |
| **lit3rick** | 2021 | FPGA (iCE40 UP5K) | 1 | ext. HV module | ext. 12-bit | TGC (AD8332+DAC) | SPI/USB | ? | [lit3rick](lit3rick/lit3rick.md) |
| pic0rick | 2024 | MCU (RP2040) | 1 (+8 opt) | ±24 V bipolar | 65 Msps ext. (10-bit) | TGC (AD8331+DAC) | USB | ~300–400 mW | [pic0rick](pic0rick/pic0rick.md) |
| **IUP** (DRESDYN UDV node) | ~2025 | MCU+FPGA (STM32H7/iCE40) | 1 | ±32 V bipolar | 16 Msps ext. (16-bit) | TGC (AD8331+DAC) | Wi-Fi (ctrl) + SD | 2.96 W | [iup](iup/iup.md) |
| **MEMS-US** (single-el. scanner) | 2020 | single-el. + MEMS mirror + PC/DAQ | 1 | Olympus 5073PR | 100 Msps (12-bit) | SW TGC | PCIe | mains | [mems-us](mems-us/mems-us.md) |
| EchoLite | 2025 | MCU | 1 | ? | ? | ? | ? | 33 mW | [echolite](echolite/echolite.md) |
| PuLsE | 2025 | MCU (M4) | 1 | <15 V est. | integ., low-rate | none (analog envelope) | ? | **5.8 mW** | [pulse](pulse/pulse.md) |
| USoP | 2023 | MCU (flex) | 1 | ~10–30 V | integ. | ? | BT | 614 mW | [usop](usop/usop.md) |
| WULPUS | 2022 | MCU (MSP430) | 8 mux | +15 V unipolar | 8 Msps integ. (12-bit) | fixed PGA | BLE 320 kbps | 22 mW | [wulpus](wulpus/wulpus.md) |
| WULPUS PRO | 2026 | MCU (MSP430) | 16 mux | ±30 V | 8 Msps integ. (12-bit) | VGA + TGC (AD8338) | BLE/Wi-Fi | 35–58 mW | [wulpus-pro](wulpus-pro/wulpus-pro.md) |
| TinyProbe | 2025 | FPGA | 32 parallel | 64 Vpp (±32 V) | 30 Msps ext. (10-bit) | programmable TGC | Wi-Fi 21.6 Mb/s | <1 W | [tinyprobe](tinyprobe/tinyprobe.md) |
| TUSS4470 (IC route) | 2021 | AFE IC + MCU | 1 | bipolar H-bridge | external (envelope) | log-amp (not TGC) | SPI + VOUT | low | [tuss4470](tuss4470/tuss4470.md) |

*`?` = not disclosed / to confirm. See each sheet for source tags and detail.*

## Reading the design space

Five architectural branches, ordered roughly minimal → capable:

1. **Integrated analog-envelope front-end IC** — TUSS4470. Fewest parts, lowest
   power, but ≤1 MHz and envelope-only (no RF phase). The floor of the design space.
2. **Analog-envelope + low-rate ADC** — PuLsE (5.8 mW). Custom envelope circuit ⇒
   slow ADC + low-power MCU. Envelope-only; wearable HR.
3. **Integrated-ADC MCU** — WULPUS / WULPUS PRO. 8 Msps integrated ADC caps
   end-to-end BW at ~1.4 MHz (≤3 MHz transducers). PRO adds analog TGC (AD8338) and
   a dual ±30 V supply (LT3463). Lowest power for raw-RF A-mode.
4. **External high-speed-ADC, single channel** — Murgen → un0rick → lit3rick →
   pic0rick (the kelu124 family). 65 Msps (10–12-bit) external ADC + AD833x VGA/TGC
   + MD-class pulser. High frequency, USB/SPI, higher power. **The direct lineage
   for *minus*.**
5. **FPGA multi-channel** — TinyProbe (32 ch, Wi-Fi). High capability, ~45× the
   power. Upper bound of the "few-channel" space before going out of scope.

Plus an orthogonal axis — **integration-first**: USoP (flexible skin patch, power
spent on conformability, 614 mW).

**For minus** (minimal, single-channel, cheap), the most directly relevant are the
**kelu124 family** (un0rick / lit3rick / pic0rick — the baseline to trim), **WULPUS**
(minimal-power raw-RF A-mode), **PuLsE / TUSS4470** (how far envelope-only
minimalism can go). The core tension: external high-speed ADC (frequency + cost +
power) vs integrated slow ADC (cheap + low-power, but ≤~1.4 MHz).

## Out of scope — 64+ element / large systems (context only)

Not given datasheets (per the "avoid 64+ elements" guidance); recorded so we know
they were reviewed and set aside:

- **ULA-OP / ULA-OP 256** (Univ. Florence) — open research platform; base 64-ch,
  scalable to 256 (Artix-7 FPGA per 32-ch module). Powerful but large/expensive.
- **SARUS** (DTU, Denmark) — up to 1024 ch (64 boards × 16), 320 FPGAs + Linux
  cluster. Research beamforming reference; far out of scope.
- **open-UST** (arXiv 2302.10114) — open-source ultrasound *tomography* transducer
  array; many-element ring. Different modality; out of scope.

## Leads to review (not yet sheeted)

- **Compact modular open platform for low-cost ultrasound imaging**, *Measurement*
  2024 (ScienceDirect S0263224124022516) — **32 elements (in scope, confirmed).**
  To sheet: get the PDF into `pdfs/` and fill a datasheet.
- **rtl-ultrasound** (Meng 2019) — SDR-based quadrature acquisition path (a review
  co-author's project). In scope; sheet it.
- **Compressive single-sensor 3D** (Kruizinga et al. 2017) — single-element
  volumetric imaging via a coded aperture mask. In scope; sheet it.
- Historical context only: "Design of low-cost portable ultrasound systems: review"
  (PubMed 19963733).

*Dropped:* AFE58xx AI-portable US (arXiv 2311.00482) — 64+ channels, out of scope.
**Sheeted since:** MEMS-US (Sci. Reports 2020) now has its own datasheet.

## Literature & source PDFs

- **Anchor survey:** Jonveaux, Schloh, Meng, Arija, Rintoul, *Journal of Open
  Hardware* 6(1):3, 2022, DOI 10.5334/joh.28 (`pdfs/28-952-1-PB.pdf`) — distilled in
  [`literature.md`](literature.md).
- Device papers: IUP (`pdfs/ssrn-6946751.pdf`), MEMS-US (`pdfs/s41598-020-63529-z.pdf`).
- New PDFs (datasheets, reference designs) go in [`../pdfs/`](../pdfs/); any
  schematics / design files go in [`../design/<name>/`](../design/).
