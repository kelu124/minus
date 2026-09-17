# minus — Requirements (draft)

**Status:** draft v0.2, 2026-09-17. Grounded in [`docs/claude/memory/0001-project-scope.md`],
the survey in [`systems/`](systems/README.md), and the route/pulser analysis in
[`analysis.md`](analysis.md). Requirement values marked **TBD** need a decision
(see §4). Priorities use MoSCoW: **[M]** must, **[S]** should, **[C]** could, **[W]** won't-yet.

**v0.2 firm requirements (from the owner):** smallest practical board, cheapest BOM,
design as simple as possible, and **RP2350 as the MCU** (resolves TBD-7; host link is
its native USB, resolving TBD-4). See **Design principles** below and §10.

## 0. Design principles (overriding [M])

- **DP1 — Small:** smallest practical single board.
- **DP2 — Cheap:** minimise BOM cost and part count.
- **DP3 — Simple:** simplest design that meets the functional requirements; fewest
  ICs, jelly-bean parts, easy hand-assembly and reproduction.
- **DP4 — RP2350 MCU:** the controller is the Raspberry Pi **RP2350** (see §10).

These principles are tie-breakers: when two designs meet the functional requirements,
prefer the smaller / cheaper / simpler one.

> **Architecture note (RP2350 + ADC).** The RP2350's on-chip SAR ADC is **12-bit,
> 500 kSps** — far too slow for 1–5 MHz raw RF (P3 needs ≥ 20 MSps). So minus uses
> **RP2350 + one external high-speed ADC** clocked into the RP2350 **PIO** (the
> pic0rick pattern on RP2350). Keeping that single external ADC minimal is the main
> tension against DP1–DP3. *If the 1–5 MHz raw-RF requirement were relaxed to
> ≤~1 MHz envelope/ToF, the internal ADC could be used and the board gets much
> simpler — that is the alternative, flagged as ADEC below, not the current baseline.*

---

## 1. Purpose & scope

**minus** is a **minimal, single-channel, low-cost, open** ultrasound pulse-echo
platform. It generates a high-voltage excitation on one piezo transducer, amplifies
and digitizes the returning echo, and delivers raw data to a host for processing.

**In scope:** single-element A-mode acquisition (raw RF), 1–5 MHz transducers,
depth-variable gain, host-side processing.
**Out of scope (this version):** multi-element phased-array beamforming, on-board
real-time B-mode reconstruction, clinical certification (see §16).

## 2. Intended use & users

- **Primary use:** research, education, experimentation, and NDT — a hackable,
  reproducible single-channel ultrasound front-end (in the un0rick/pic0rick lineage).
- **Assumed classification:** **non-clinical** research/lab instrument. *(TBD-1 — if
  any clinical intent, §16 requirements change substantially.)*
- **Users:** makers, students, researchers; able to solder/assemble a PCB and script
  a host in Python.

## 3. Definitions & references

- **A-mode** amplitude vs depth (1-D); **B-mode** 2-D image; **TGC** time-gain
  compensation; **T/R** transmit/receive switch; **AFE** analog front end; **PRF**
  pulse-repetition frequency; **fc** transducer centre frequency.
- References: [`analysis.md`](analysis.md), [`systems/by-ic.md`](systems/by-ic.md),
  [`systems/literature.md`](systems/literature.md), design files in [`design/`](design/README.md).

## 4. Assumptions & open decisions (must be resolved to freeze v1.0)

**Resolved (owner decisions):**
- **TBD-4 → RESOLVED:** host link is **USB**, via an **on-board USB connector,
  USB-C preferred**; the board is **USB bus-powered** (§10, §11).
- **TBD-7 → RESOLVED:** controller is the **RP2350** MCU (§10, DP4).

**Still open:**

| ID | Open decision | Working assumption in this draft |
|----|---------------|----------------------------------|
| TBD-1 | Clinical vs non-clinical | **non-clinical** research/education |
| TBD-2 | Target centre frequency within 1–5 MHz | design for the **full 1–5 MHz** band |
| TBD-3 | Transmit polarity | **bipolar** preferred; unipolar allowed if it wins on BOM (DP2/DP3) |
| TBD-5 | Imaging mode beyond A-mode | A-mode core; single-element scanned B-mode is [C] |
| TBD-6 | Target unit BOM cost | **≤ USD 150** target (to confirm) |
| ADEC | ADC architecture | **external high-speed ADC** on RP2350 PIO (keeps 1–5 MHz raw RF). Alt: internal 500 kSps ADC only if band relaxed to ≤~1 MHz envelope |

---

## 5. Functional requirements (F)

- **F1 [M]** The system shall drive a single piezo transducer with a configurable
  high-voltage pulse and receive the echo on the same or a paired element.
- **F2 [M]** The system shall support **single-element transducers in 1–5 MHz**
  (TBD-2), connected via a standard coax/SMA interface.
- **F3 [M]** The system shall acquire **raw RF** echo data (not envelope-only) for
  host-side processing.
- **F4 [M]** Acquisition parameters — pulse width, number of cycles, PRF, TGC curve,
  acquisition depth/length — shall be **host-configurable**.
- **F5 [S]** The system shall support a **T/R switch** so one element can transmit
  and receive.
- **F6 [S]** The system shall provide **depth-variable gain (TGC)**, host-programmable.
- **F7 [C]** The system should support a **dual-element** (separate TX/RX) mode via a
  second connector (cf. lit3rick).
- **F8 [C]** The system could support **single-element B-mode** via an external
  mechanical/scanning fixture (host-side reconstruction).
- **F9 [W]** Multi-channel / array beamforming is deferred to a later version.

## 6. Performance requirements (P)

- **P1 [M]** Excitation frequency range: **1–5 MHz** (TBD-2), transducer-dependent.
- **P2 [M]** Acquisition bandwidth (−3 dB): shall pass the transducer band up to
  **≥ 5 MHz** end-to-end (i.e., **not** bandwidth-capped below the target fc — this
  is the key differentiator from the MSP430 integrated route, see analysis §2).
- **P3 [M]** ADC sample rate: **≥ 4× fc** for the top of the band ⇒ **≥ 20 MSps**;
  **target ≥ 30–40 MSps** to preserve RF at 5 MHz.
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

- **T1 [M]** Generate a configurable HV pulse suitable for 1–5 MHz excitation.
- **T2 [M]** Pulse amplitude: **configurable**, baseline **±24 V**, target range up
  to **±50–100 V** capability (TBD-3). Unipolar +15–30 V acceptable if it meets the
  BOM goal.
- **T3 [M]** The pulser BOM shall be **as light as practical** — prefer an integrated
  pulser+T/R (STHV748-class) or the proven 2-IC MD1213+TC6320, per analysis §3.
- **T4 [S]** Pulse shape (single-cycle / N-cycle) host-configurable.
- **T5 [C]** Support multi-level / arbitrary excitation (coded pulses) if the chosen
  pulser allows (e.g., STHV748 3/5-level).

## 9. Digitization & data (D)

- **D1 [M]** Digitize raw RF at the P3/P4 rate/resolution using an **external
  high-speed ADC** (ADEC) — the RP2350 internal 500 kSps ADC is insufficient (§0).
- **D2 [M]** Buffer at least **one full acquisition line** in **RP2350 RAM** (via
  PIO/DMA FIFO), decoupling ADC bursts from the USB transfer.
- **D3 [S]** Sustain streaming of consecutive lines at the working PRF over the host
  link without loss (or buffer + burst).
- **D4 [C]** On-board persistent storage (SD) for untethered raw capture (cf. IUP).

## 10. Control, connectivity & host (C)

- **C1 [M]** The controller shall be the **Raspberry Pi RP2350** (DP4). It shall
  sequence TX/RX with **cycle-accurate timing** using **PIO**, and capture the
  external ADC (ADEC) into RAM via PIO/DMA. *(RP2350B preferred for the extra GPIO
  needed by a parallel ADC bus + control lines.)*
- **C2 [M]** Host interface: **USB** on the RP2350's native USB, via an **on-board
  USB connector (USB-C preferred)**, presenting a documented command/data protocol.
- **C3 [M]** A **Python** host API/reference client shall configure acquisitions and
  read back raw data.
- **C4 [C]** Wireless (BLE/Wi-Fi) host link for untethered use — only if it does not
  compromise DP1–DP3.
- **C5 [S]** Standard expansion header (e.g., PMOD) for options (mux, storage).

## 11. Power (PW)

- **PW1 [M]** **USB bus-powered** from the on-board USB-C connector (5 V); no
  separate power input required for baseline operation.
- **PW2 [S]** Total power within the USB budget and **≤ ~2 W** tethered.
- **PW3 [M]** On-board generation of the rails the chain needs (e.g., ADC/AFE
  supplies and the HV pulser rail) from USB 5 V, kept minimal per DP2/DP3.
- **PW4 [C]** Battery option for untethered use if C4 is pursued.

## 12. Mechanical / form factor (M)

- **M1 [M]** **Single small PCB** (DP1), fabricable by a standard low-cost house
  (e.g., JLCPCB) from the published files.
- **M2 [M]** On-board **USB-C** connector (host + power). Transducer via SMA/coax.
- **M3 [S]** Compact benchtop form factor; minimise board area.
- **M4 [C]** Wearable/handheld form factor is out of scope for v1.0.

## 13. Cost & BOM (B)

- **B1 [M]** Target unit BOM cost **≤ USD 150** (TBD-6) at low volume; minimise part
  count, especially the pulser/HV section (T3).
- **B2 [M]** Use **jelly-bean / widely-available** parts; avoid single-source or EOL
  ICs where possible; document alternates.
- **B3 [S]** Prefer parts already validated in the reference designs on disk
  (pic0rick, un0rick, IUP) to de-risk.

## 14. Software / firmware (S)

- **S1 [M]** Open firmware controlling TX/RX sequencing, TGC, and data transfer.
- **S2 [M]** Open host software (Python) for configuration, capture, and raw-data
  export in a documented, versioned format.
- **S3 [S]** Host-side reference processing: filtering + envelope (Hilbert) → A-line;
  optional M-mode.
- **S4 [C]** Reproducible build + flashing instructions (CMake/UF2 or FPGA toolchain).

## 15. Openness & licensing (O)

- **O1 [M]** Hardware, firmware, and host software shall be **open-source** under
  clearly stated licenses (e.g., TAPR/CERN-OHL for HW; permissive/GPL for SW).
- **O2 [M]** Design files shall be **fabricable from the repo** (schematic, PCB,
  gerbers, BOM) without proprietary tools where feasible (prefer KiCad).
- **O3 [S]** OSHWA-certifiable.

## 16. Safety & compliance (SF)

- **SF1 [M]** As a **non-clinical** device (TBD-1), it shall carry a clear "research/
  education use only, not a medical device" notice.
- **SF2 [M]** HV section shall be documented with safe-handling notes; exposed HV
  minimised and labelled.
- **SF3 [S]** Acoustic output kept to conservative, documented levels; if ever used
  on people, follow MI/TI guidance (IEC 62359 / IEC 60601-2-37) — **triggers a
  clinical re-scope**.
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
- Design starting point: [`design/pic0rick/panel_adc_pulser_hv/`](design/).

---

_Draft — resolve the TBDs in §4 to move to v1.0, then derive a costed BOM and a block
diagram._
