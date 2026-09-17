# minus — Requirements (draft)

**Status:** draft v0.3, 2026-09-17. Grounded in [`docs/claude/memory/0001-project-scope.md`],
the survey in [`systems/`](systems/README.md), and the route/pulser analysis in
[`analysis.md`](analysis.md). Requirement values marked **TBD** need a decision
(see §4). Priorities use MoSCoW: **[M]** must, **[S]** should, **[C]** could, **[W]** won't-yet.

**v0.2 firm requirements (from the owner):** smallest practical board, cheapest BOM,
design as simple as possible, and **RP2350 as the MCU** (resolves TBD-7; host link is
its native USB, resolving TBD-4). See **Design principles** below and §10.

**v0.3 firm requirements (from the owner):** **non-clinical (NDT)** use (TBD-1);
target transducer **3–4 MHz** (TBD-2); **unipolar** pulser for simplicity (TBD-3);
**A-mode core, M-mode optional** (TBD-5); **drive BOM as low as possible** — actively
explore cheap options (TBD-6).

**v0.3 context (from the owner):** minus is the hands-on device for a **workshop at an
ultrasound conference**. It keeps a conference **"badge" form factor**, on a limited
budget (many units), and must let attendees **experiment** — e.g. try **coded/encoded
excitation** (see §8 T4). Example workshop topic: **muscle-contraction monitoring**
(A-/M-mode of superficial muscle). The **piezo transducer is provided** with the kit
(a known ~3–4 MHz single element), so the front-end can be tuned to it.

## 0. Design principles (overriding [M])

- **DP1 — Small:** smallest practical single board.
- **DP2 — Cheap:** minimise BOM cost and part count.
- **DP3 — Simple:** simplest design that meets the functional requirements; fewest
  ICs, jelly-bean parts, easy hand-assembly and reproduction.
- **DP4 — RP2350 MCU:** the controller is the Raspberry Pi **RP2350** (see §10).
- **DP5 — Derisk by reuse:** prefer **proven building blocks from the owner's own,
  validated designs** — echomods/**Murgen**, **un0rick**, **lit3rick**, **pic0rick**
  (the owner has built these and is happy with their performance). Reuse their pulser,
  T/R, VGA/TGC, ADC-capture, and PIO patterns rather than inventing new ones. Design
  files are on disk in [`design/`](design/README.md).

These principles are tie-breakers: when two designs meet the functional requirements,
prefer the smaller / cheaper / simpler one, and the one that **reuses proven blocks**.

> **Architecture note (RP2350 + ADC).** The RP2350's on-chip SAR ADC is **12-bit,
> 500 kSps** — far too slow for **3–4 MHz** raw RF (P3 needs ≥ ~16–30 MSps). So minus
> uses **RP2350 + one external high-speed ADC** clocked into the RP2350 **PIO** (the
> pic0rick pattern on RP2350). At 3–4 MHz a ~20–30 MSps 10–12-bit ADC is enough —
> cheaper and smaller than pic0rick's 65 MSps part, which helps DP1–DP3/BOM. *If the
> raw-RF requirement were relaxed to ≤~1 MHz envelope/ToF, the internal ADC could be
> used and the board gets much simpler — the alternative, not the current baseline.*

---

## 1. Purpose & scope

**minus** is a **minimal, single-channel, low-cost, open** ultrasound pulse-echo
platform, built as a **conference-workshop badge**. It generates a high-voltage
excitation on one (provided) piezo transducer, amplifies and digitizes the returning
echo, and delivers raw data to a host for processing. The workshop lets attendees
learn and experiment — e.g. **muscle-contraction monitoring** (A-/M-mode) and **coded
excitation**.

**In scope:** single-element A-/M-mode acquisition (raw RF) with a provided ~3–4 MHz
piezo; depth-variable gain; programmable/coded excitation; host-side processing;
badge form factor; low, workshop-scalable BOM.
**Out of scope (this version):** multi-element phased-array beamforming, on-board
real-time B-mode reconstruction, clinical use/certification (see §16).

## 2. Intended use & users

- **Primary use:** research, education, experimentation, and NDT — a hackable,
  reproducible single-channel ultrasound front-end (in the un0rick/pic0rick lineage).
- **Classification:** **non-clinical** — **NDT (non-destructive testing)**,
  research and education. Not a medical device (§16).
- **Users:** **ultrasound-conference workshop attendees** (and afterwards makers,
  students, researchers, NDT experimenters). Assume a range of skill; the device and
  its host software must be approachable for a guided workshop yet hackable for
  experimentation.

## 3. Definitions & references

- **A-mode** amplitude vs depth (1-D); **B-mode** 2-D image; **TGC** time-gain
  compensation; **T/R** transmit/receive switch; **AFE** analog front end; **PRF**
  pulse-repetition frequency; **fc** transducer centre frequency.
- References: [`analysis.md`](analysis.md), [`systems/by-ic.md`](systems/by-ic.md),
  [`systems/literature.md`](systems/literature.md), design files in [`design/`](design/README.md).

## 4. Assumptions & open decisions (must be resolved to freeze v1.0)

**Resolved (owner decisions):**
- **TBD-1 → RESOLVED:** **non-clinical / NDT** (§2, §16).
- **TBD-2 → RESOLVED:** target transducer **3–4 MHz** (design with margin ~2–5 MHz).
- **TBD-3 → RESOLVED (conditional):** **unipolar preferred** (simplicity, DP3);
  **bipolar accepted iff** a **cheap symmetric ± rail** can be produced (see §8 T6).
- **TBD-4 → RESOLVED:** host link is **USB**, via an **on-board USB-C** connector;
  **USB bus-powered** (§10, §11).
- **TBD-5 → RESOLVED:** **A-mode** core; **M-mode** optional [S] (host-side, no extra
  HW); B-mode deferred [W].
- **TBD-7 → RESOLVED:** controller is the **RP2350** MCU (§10, DP4).

**Still open:**

| ID | Open decision | Working assumption in this draft |
|----|---------------|----------------------------------|
| TBD-6 | Unit BOM cost | **drive as low as possible**; explore cheap options (no fixed cap yet) |
| ADEC | External ADC choice | **external high-speed ADC** on RP2350 PIO; at 3–4 MHz a **~20–30 MSps, 10–12-bit** part suffices (cheaper/smaller than 65 MSps) — pick the lowest-cost part that meets P3. See [`options.md`](options.md) §3 |
| RF-ACCESS | **Raw RF vs envelope?** | **Working assumption: raw RF** (F3). Key question: do we want users to access the **raw RF signal, not just the envelope?** Raw RF is what justifies the on-device **DSP** (S6), **coded excitation** + matched filtering (T4), and the external high-speed ADC. **Envelope-only would be simpler/cheaper but would not justify the DSP** and would collapse the external-ADC route (an internal 500 kSps ADC would do). **Decision pending** — if confirmed raw-RF, ADEC stands; if envelope-only, re-scope §0/§9 |

---

## 5. Functional requirements (F)

- **F1 [M]** The system shall drive a single piezo transducer with a configurable
  high-voltage pulse and receive the echo on the same or a paired element.
- **F2 [M]** The system shall drive the **provided single-element piezo (~3–4 MHz)**;
  the front-end may be tuned to that known element. Design margin ~2–5 MHz.
- **F2c [M]** The board shall offer **multiple transducer-connector footprints**:
  **SMA/coax**, a classical **2×1 2.54 mm header**, and a **uFL** (u.FL) connector
  (uFL for easy plug-in). Populating at least one is required; providing all footprints
  lets users pick per their transducer/lead.
- **F2a [S]** Suitable for **muscle-contraction monitoring** on superficial muscle
  (~1–4 cm depth) — the reference workshop application.
- **F3 [M]** The system shall acquire **raw RF** echo data (not envelope-only) for
  host-side processing.
- **F4 [M]** Acquisition parameters — pulse width, number of cycles, PRF, TGC curve,
  acquisition depth/length — shall be **host-configurable**.
- **F5 [S]** The system shall support a **T/R switch** so one element can transmit
  and receive.
- **F6 [S]** The system shall provide **depth-variable gain (TGC)**, host-programmable.
- **F7 [C]** The system should support a **dual-element** (separate TX/RX) mode via a
  second connector (cf. lit3rick).
- **F8 [S]** The system shall support **M-mode** (repeated A-lines over time,
  host-side; no extra hardware).
- **F9 [W]** Single-element B-mode (via an external scanning fixture) and
  multi-channel / array beamforming are deferred to a later version.
- **F10 [M]** The device shall be **hackable for workshop experimentation**: coded/
  encoded excitation (T4), adjustable acquisition parameters (F4), and open host
  processing (S2–S3) shall be exposed so attendees can try coded excitation, pulse
  compression, filtering, and M-mode of muscle contraction.
- **F11 [S]** **Autonomous RGB display:** the board shall carry at least one
  **addressable RGB LED** (e.g. WS2812/SK6812, RP2350 **PIO**-driven) so the badge
  gives **standalone visual feedback without a host** — status, and a demo that maps
  echo strength / muscle-contraction (M-mode) to colour. Reinforces the badge aspect.
- **F12 [S]** **Small OLED display** (common on workshop badges) — e.g. a 0.9″/1.3″
  **I²C SSD1306/SH1106** (128×32/128×64) — for standalone on-badge display (status, a
  live A-line / M-mode strip, simple menus) without a host. Shares the I²C bus (C5).

## 6. Performance requirements (P)

- **P1 [M]** Excitation frequency: **3–4 MHz** target (support ~2–5 MHz),
  transducer-dependent.
- **P2 [M]** Acquisition bandwidth (−3 dB): shall pass the transducer band up to
  **≥ 5 MHz** end-to-end (i.e., **not** bandwidth-capped below fc — the key
  differentiator from the MSP430 integrated route, see analysis §2).
- **P3 [M]** ADC sample rate: **≥ 4× fc** ⇒ **≥ 16 MSps** at 4 MHz; **target
  ≥ 20–30 MSps** (enough for 3–4 MHz RF; lets us pick a cheaper part than 65 MSps).
- **P4 [M]** ADC resolution: **≥ 10-bit** (≥ 9-bit gives ~50 dB SNR per the
  literature; 12-bit [S] for dynamic range).
- **P5 [S]** System SNR: **≥ 50 dB** on a reference reflector/phantom.
- **P6 [S]** Programmable **PRF** at least **100 Hz–10 kHz**.
- **P7 [S]** Acquisition depth: capture **≥ 120 µs** per line (≈ 9 cm at 1540 m/s),
  host-extendable.
- **P8 [C]** Total gain (fixed + TGC) adjustable over **≥ 40 dB**.

## 7. Analog front-end / signal chain (A)

- **A1 [M]** RX chain: transducer → T/R protection → low-noise amp → (TGC) VGA →
  anti-alias filter → ADC.
- **A2 [M]** RX input protection shall survive the transmit pulse (T/R switch or
  clamp, e.g., MD0100/MD0101-class).
- **A3 [S]** Gain shall be a **variable-gain amplifier** (e.g., AD8331/AD8332, or the
  low-power AD8338), controlled by a host-set DAC ramp for TGC.
- **A4 [S]** Anti-alias filtering matched to the ADC rate and transducer band.

## 8. Transmit / pulser (T)

- **T1 [M]** Generate a configurable **unipolar** HV pulse for ~3–4 MHz excitation.
- **T2 [M]** Pulse amplitude: unipolar, **configurable**, baseline **~+20–30 V**,
  capability up to **~+50 V** if cheap to do; single minimal HV rail (DP2/DP3).
- **T3 [M]** Simplest unipolar transmit: **single MOSFET + gate driver** driving the
  transducer, plus a T/R switch/clamp to protect RX (MD0100/MMBD-class). The HV rail
  may be as simple as the **USB +5 V rail directly** (no boost IC — cheapest, low
  amplitude) or a **small boost** for a stronger pulse; either way the HV node is on a
  header (T7) so users can **swap in external HV**. Choose per `options.md` (U0/U1).
- **T4 [M]** **Programmable / arbitrary excitation** — the pulser gate is driven by
  the **RP2350 PIO**, so workshop users can generate multi-cycle bursts, swept-
  frequency (chirp), pulse-position and on-off-keyed (OOK) **coded excitation** and
  experiment with pulse compression. This is a core workshop feature.
- **T5 [note]** True **bipolar phase codes** (e.g., ±1 Barker) need a *bipolar*
  pulser; the unipolar baseline supports frequency/pulse-train/OOK coding only.
- **T6 [S]** **Bipolar option (conditional):** bipolar transmit is accepted **iff** a
  **cheap, simple symmetric ± rail** can be generated. **Cheapest answer: a
  +5→−5V charge pump** (e.g. TPS60403 / ICL7660 / LM2776, ~$0.4) gives a symmetric
  **±5V** rail — low amplitude but enough to demo **true ±1 phase-coded excitation**
  (options.md B0). For higher voltage, explore an inverting/dual-output / SEPIC-Ćuk
  converter or two small boosts (one inverted). If a viable ± rail is used,
  a bipolar pulser (e.g. MD1210/MD1213 + TC6320, as in pic0rick — DP5) becomes
  viable and **unlocks true ±1 phase-coded excitation** for the workshop (synergy
  with T4). Otherwise, stay unipolar (T1–T3).
- **T7 [S]** **HV rail(s) on a header (external-HV option):** bring the HV rail(s) to
  an accessible header with a **jumper / solder-bridge** to isolate the on-board HV
  supply, so users can **feed external HV** or replace the on-board generator entirely
  (e.g. via an extension board, C5). Expose the relevant control PIO(s) too.

## 9. Digitization & data (D)

- **D1 [M]** Digitize raw RF at the P3/P4 rate/resolution using an **external
  high-speed ADC** (ADEC) — the RP2350 internal 500 kSps ADC is insufficient (§0).
- **D2 [M]** Buffer at least **one full acquisition line** in **RP2350 RAM** (via
  PIO/DMA FIFO), decoupling ADC bursts from the USB transfer.
- **D3 [S]** Sustain streaming of consecutive lines at the working PRF over the host
  link without loss (or buffer + burst).
- **D4 [C]** On-board persistent storage (SD) for untethered raw capture (cf. IUP).

## 10. Control, connectivity & host (C)

- **C1 [M]** The controller shall be the **Raspberry Pi RP2350** (DP4), with
  RP2350B preferred for the extra GPIO (parallel ADC bus + control lines).
- **C1a [M]** **Precise pulse-sequence timing:** the controller shall generate the
  TX pulse-sequence logic with **cycle-accurate, ~ns-resolution deterministic timing**
  (via **PIO**), enough to define pulse width, count, delays, and coded/chirp
  sequences (T4).
- **C1b [M]** **Fast, steady acquisition:** the controller shall capture the external
  ADC (ADEC) as a **continuous, gap-free** stream at the full P3 sample rate into RAM
  (**PIO + DMA**), sustaining one full acquisition line (D2) without dropped samples.
- **C2 [M]** Host interface: **USB** on the RP2350's native USB, via an **on-board
  USB connector (USB-C preferred)**, presenting a documented command/data protocol.
- **C3 [M]** A **Python** host API/reference client shall configure acquisitions and
  read back raw data.
- **C4 [C]** Wireless (BLE/Wi-Fi) host link for untethered use — only if it does not
  compromise DP1–DP3.
- **C5 [S]** **Standardised extension header:** expose the RP2350 on a **Raspberry Pi
  2×20 (40-pin) header** pinout — bringing out **UART, I²C, SPI**, GPIO/spare PIO,
  and power/ground — so extensions communicate in a **standard, HAT-style** way (as
  the owner's un0rick did — DP5). This carries the OLED (F12, I²C) and enables add-on
  boards (channel mux, storage, alternative front-ends, external HV — see T7). Document
  the pinout; note where it deviates from the RPi map (RP2350 ≠ RP1).

## 11. Power (PW)

- **PW1 [M]** **USB bus-powered** from the on-board USB-C connector (5 V); no
  separate power input required for baseline operation.
- **PW2 [S]** Total power within the USB budget and **≤ ~2 W** tethered.
- **PW3 [M]** On-board generation of the rails the chain needs (e.g., ADC/AFE
  supplies and the HV pulser rail) from USB 5 V, kept minimal per DP2/DP3.
- **PW4 [C]** Battery option for untethered use if C4 is pursued.

## 12. Mechanical / form factor (M)

- **M1 [M]** **Single small PCB** in a **conference-badge form factor** — flat,
  badge-sized, with a **lanyard hole** and room for **silkscreen artwork** and the
  **OSHWA certification mark + UID** (O3) — fabricable by a standard low-cost house
  (e.g., JLCPCB) from the published files (DP1).
- **M2 [M]** On-board **USB-C** connector (host + power). Transducer footprints per
  F2c: SMA/coax **+** 2×1 2.54 mm header **+** uFL.
- **M3 [S]** Minimise board area and component height so it wears as a badge.
- **M4 [C]** A handheld/on-body probe enclosure is out of scope for v1.0 (the piezo is
  applied by hand during the workshop).
- **M5 [S]** **User-friendly silkscreen (layout, not BOM):** label the functional
  blocks (pulser / HV / T-R / VGA-TGC / ADC / RP2350), name connectors and header
  pins, and add brief function hints — the board should teach itself for the workshop.
- **M6 [S]** **Test points** on key logic and analog nodes (e.g. TX gate, HV rail(s),
  AFE output, ADC clock/data, PIO lines) so attendees can probe/learn and debug.

## 13. Cost & BOM (B)

- **B1 [M]** Drive unit BOM cost **as low as possible** (TBD-6, DP2) — it must be
  affordable to build **many badges** for a workshop on **limited funding**. Minimise
  part count, especially the pulser/HV section (T3). A costed BOM is a deliverable
  (explore cheap ADC + minimal unipolar HV; see analysis TODO).
- **B2 [M]** Use **jelly-bean / widely-available** parts (JLCPCB-assemblable);
  avoid single-source or EOL ICs where possible; document alternates.
- **B3 [M]** **Derisk by reuse (DP5):** use parts and sub-circuits already validated
  in the owner's designs — **pic0rick / un0rick / lit3rick / Murgen** (e.g. the
  un0rick-style **unipolar HV pulser** at 25–75 V, the **AD8331** VGA/TGC, a
  PIO-clocked external ADC). un0rick already runs a unipolar HV pulser, matching T1–T3.
- **B4 [note]** The **piezo is provided** with the kit and is **not** counted in the
  board BOM; the board is designed for that known element.

## 14. Software / firmware (S)

- **S1 [M]** Open firmware controlling TX/RX sequencing, TGC, and data transfer.
- **S2 [M]** Open host software (Python) for configuration, capture, and raw-data
  export in a documented, versioned format.
- **S3 [S]** Host-side reference processing: filtering + envelope (Hilbert) → A-line;
  optional M-mode.
- **S4 [S]** Reproducible build + easy flashing (RP2350 UF2 drag-and-drop) so
  workshop attendees can reflash without a toolchain.
- **S5 [S]** **Workshop material:** approachable host UI / example notebooks — live
  A-line + **M-mode of muscle contraction**, and a **coded-excitation** demo — so
  attendees get results quickly, then can experiment.
- **S6 [S]** **On-device DSP (demonstrable):** the firmware should showcase on-badge
  signal processing on the RP2350 (dual Cortex-M33 + DSP/FPU) — e.g. bandpass
  filtering, Hilbert/envelope detection, decimation, and a **matched filter** for
  coded excitation — so attendees see what is feasible on-device vs on the host. Kept
  optional/modular so it never blocks raw-data capture.

## 15. Openness & licensing (O)

- **O1 [M]** Hardware, firmware, and host software shall be **open-source** under
  clearly stated licenses (e.g., TAPR/CERN-OHL for HW; permissive/GPL for SW).
- **O2 [M]** Design files shall be **fabricable from the repo** (schematic, PCB,
  gerbers, BOM) without proprietary tools where feasible (prefer KiCad).
- **O3 [S]** Plan **OSHWA certification** (as with the owner's un0rick/lit3rick/
  pic0rick — DP5). Reserve **silkscreen space for the OSHWA certification mark + UID**
  (e.g. `OSHW FRnnnnnn`) so the tag can be added once the cert is issued.

## 16. Safety & compliance (SF)

- **SF1 [M]** As a **non-clinical NDT/education** device, it shall carry a clear
  "research/education use only, not a medical device, not for diagnosis" notice.
- **SF2 [M]** HV section shall be documented with safe-handling notes; exposed HV
  minimised and labelled (unipolar ≤ ~+50 V keeps this modest — cf. T2).
- **SF3 [M]** The workshop applies the transducer to attendees' own muscle
  (non-diagnostic demo). Acoustic output shall be kept to **conservative, documented
  levels** (brief exposure; low MI/TI, per IEC 62359 guidance) and framed as a
  self-applied demonstration — **not** medical diagnosis. Any diagnostic intent would
  trigger a clinical re-scope (out of scope).
- **SF4 [S]** Materials/connectors rated for the selected HV.

## 17. Verification & acceptance (how each is checked)

| Area | Acceptance check |
|------|------------------|
| TX (T1–T2) | Scope the pulse into a known load: amplitude, shape, frequency vs config. |
| RX/AFE (A1–A3, P2) | Inject a tone / pulse-echo off a reflector; verify band, gain, TGC ramp. |
| ADC (P3–P4) | Capture a known signal; verify rate, bits, no clipping/aliasing. |
| SNR (P5) | Pulse-echo off a wire/phantom; measure SNR ≥ 50 dB. |
| Data path (D1–D3) | Stream N lines at working PRF; verify no sample loss. |
| Host (C2–C3, S2) | Python client configures + reads raw data; format documented. |
| Cost/BOM (B1) | Costed BOM ≤ target; all parts sourceable. |
| Openness (O1–O2) | Repo builds/fabs from published files under stated licenses. |

## 18. Traceability

- Route/architecture rationale and the pulser trade study: [`analysis.md`](analysis.md).
- Comparable systems and their measured values: [`systems/`](systems/README.md)
  (esp. [pic0rick](systems/pic0rick/pic0rick.md), [un0rick](systems/un0rick/un0rick.md),
  [IUP](systems/iup/iup.md)); IC choices: [`systems/by-ic.md`](systems/by-ic.md).
- **Owner-built, trusted lineage (DP5):** Murgen/echomods, un0rick, lit3rick,
  pic0rick — the owner has built these and is happy with their performance, so their
  blocks are the derisked starting point.
- Design starting point: [`design/pic0rick/panel_adc_pulser_hv/`](design/).

---

_Draft — resolve the TBDs in §4 to move to v1.0, then derive a costed BOM and a block
diagram._
