# Workshop possibilities — what participants can *do* with minus

**Status:** brainstorm / living list (started 2026-09-18) · type: activities

**Context.** *minus* is a workshop badge: a single-channel pulse-echo ultrasound
board built around an **RP2350** + external high-speed ADC, a **unipolar HV pulser**,
a **3–4 MHz piezo** (provided with the kit), targeting **A-mode + M-mode**, with
**programmable/coded excitation**, on-device **DSP**, an addressable **RGB LED**, an
**I²C OLED**, and a **Raspberry-Pi 40-pin extension header**. See
`docs/claude/memory/0005-minus-direction.md` and `requirements.md`.

The board deliberately spans four layers — **hardware**, **ultrasound/physics**,
**embedded firmware**, and **computer/host side** — so a participant can go as deep
as they like on any one axis. This file catalogues candidate activities per layer,
tagged by difficulty:

- 🟢 **intro** — no prior experience, ~15–45 min, guided.
- 🟡 **core** — the "main" workshop track, ~1–3 h.
- 🔴 **deep** — for participants who want to push further / take home.

Each activity notes what it *teaches* and what it *needs* (board feature, tool, or
prior activity). Activities are meant to be mixed into a menu, not all done by
everyone.

---

## 1. Hardware layer

*Soldering, bring-up, measurement, and modification of the board itself.*

- 🟢 **Assemble / bring up the badge.** Solder the through-hole / hand-solder parts
  (headers, connectors, LED), plug in USB-C, confirm the RGB LED blinks and the board
  enumerates. *Teaches:* soldering, first power-on, USB enumeration. *Needs:* kit,
  iron, host with serial.
- 🟢 **Attach the transducer.** Mount the provided ~3–4 MHz piezo to a coupling
  surface; choose a connector footprint (SMA/coax vs 2×1 header vs uFL) and understand
  why several are provided. *Teaches:* transducer handling, coupling gel, connector
  trade-offs.
- 🟡 **Scope the pulse.** Probe the HV pulser output and T/R node with an oscilloscope;
  measure pulse width, amplitude, and ring-down. *Teaches:* HV pulsing, damping,
  reading test points. *Needs:* test points (board feature T7/TPs), scope.
- 🟡 **Walk the signal chain.** Follow pulser → T/R switch → gain (VGA) → ADC on the
  silkscreen; identify each block and its test point. *Teaches:* front-end architecture,
  self-documenting layout. *Needs:* labelled silkscreen (board feature).
- 🟡 **Tune the analog gain.** Change the VGA (AD8338-class) control voltage / TGC
  ramp and watch the effect on echo amplitude and noise floor. *Teaches:* time-gain
  compensation, dynamic range, SNR.
- 🔴 **HV rail swap.** Use the HV-on-header jumper to isolate the on-board pulser rail
  and drive from an external supply / different HV level; compare penetration.
  *Teaches:* HV headroom vs depth, safe rail isolation. *Needs:* HV header + jumper
  (board feature T7).
- 🔴 **Build an add-on HAT.** Design/populate something on the 40-pin extension header
  (extra LEDs, a second sensor, a battery/boost, a bigger display). *Teaches:*
  extension design, pin budgeting. *Needs:* RPi 40-pin header (board feature).
- 🔴 **Pulser experiments.** Compare unipolar excitation vs (if fitted) a bipolar
  ±rail option; measure how bandwidth/phase-coding capability changes. *Teaches:*
  pulser topologies. *Needs:* bipolar option (design expansion).

## 2. Ultrasound / physics layer

*Using the badge as an instrument to explore acoustics — the "aha" experiments.*

- 🟢 **Time-of-flight ranging.** Bounce off a reflector at a known distance; read the
  echo delay and compute distance from the speed of sound. *Teaches:* pulse-echo
  principle, c ≈ 1480 m/s in water / 1540 in tissue.
- 🟢 **Speed-of-sound measurement.** Reverse the above: known distance → solve for c in
  water vs oil vs gel. *Teaches:* material acoustics, calibration.
- 🟡 **A-mode line.** Capture a single RF/envelope A-line through a phantom (gel block,
  layered materials) and identify interfaces. *Teaches:* A-mode reading, impedance
  boundaries. *Needs:* A-mode firmware.
- 🟡 **M-mode motion.** Point at something moving (a finger tap, a pulsing tube, muscle
  contraction) and watch the M-mode strip. *Teaches:* motion over time; the flagship
  demo (muscle-contraction monitoring). *Needs:* M-mode firmware.
- 🟡 **Attenuation & depth.** Measure echo amplitude vs depth in different media;
  observe frequency-dependent attenuation. *Teaches:* attenuation, why frequency ↔
  depth trade-off.
- 🔴 **Resolution limits.** Vary pulse length and measure axial resolution against a
  known target spacing; relate to bandwidth. *Teaches:* axial resolution = f(pulse
  length / bandwidth).
- 🔴 **Coded excitation gains.** Transmit a chirp / Barker code vs a single pulse; use
  matched filtering to show SNR / penetration improvement. *Teaches:* pulse compression.
  *Needs:* coded-excitation firmware + matched filter (board feature T4/S6).
- 🔴 **Make your own phantom.** Build gelatin/agar phantoms with inclusions and image
  them. *Teaches:* tissue-mimicking materials, controlled targets.

## 3. Embedded firmware layer

*RP2350 code — PIO, DMA, DSP, and the on-badge UI.*

- 🟢 **Blink & LED status.** Modify the RGB LED (WS2812/SK6812 via PIO) to signal
  states / map echo strength to colour. *Teaches:* PIO basics, addressable LEDs.
  *Needs:* RGB LED (board feature F11).
- 🟢 **Hello, OLED.** Draw text/a waveform to the I²C OLED (SSD1306-class). *Teaches:*
  I²C, framebuffers, autonomous display. *Needs:* OLED (board feature F12).
- 🟡 **Generate the pulse (PIO).** Write/adjust the PIO program that produces the ns-
  precise TX pulse sequence; change frequency, pulse count, PRF. *Teaches:* PIO timing,
  deterministic waveform generation. *Needs:* PIO pulser driver.
- 🟡 **Gap-free ADC capture (PIO + DMA).** Configure the PIO+DMA path that streams the
  external ADC without gaps; adjust sample count / rate / trigger. *Teaches:* high-speed
  streaming, double-buffering. *Needs:* ADC capture firmware.
- 🟡 **On-device envelope.** Implement/extend bandpass → Hilbert/envelope → decimation
  on the RP2350 (dual M33 + FPU) and display the result on the OLED. *Teaches:* real-time
  DSP on an MCU, on- vs off-device processing. *Needs:* DSP module (board feature S6).
- 🔴 **Coded excitation + matched filter.** Author a chirp/pulse-train/OOK sequence in
  PIO and run the matched filter on-device; compare against host processing. *Teaches:*
  coded excitation end-to-end. *Needs:* coded-excitation path (T4/S6).
- 🔴 **Dual-core split.** Put acquisition on one M33 core and DSP/UI on the other; keep
  raw capture non-blocking. *Teaches:* multicore partitioning, real-time guarantees.
- 🔴 **Autonomous mode.** Make the badge run a full A-/M-mode loop with LED + OLED
  feedback and *no host attached*. *Teaches:* standalone embedded product design.

## 4. Computer / host side

*What runs on the laptop — capture, visualization, DSP, and beyond.*

- 🟢 **Talk to the badge.** Open the USB-CDC serial CLI; run version / capture commands
  and see raw numbers come back. *Teaches:* serial protocols, host↔device handshake.
  *Needs:* host serial + firmware CLI.
- 🟢 **Plot an A-line.** Capture one frame and plot it in Python (numpy/matplotlib) or a
  provided web page. *Teaches:* reading a data stream, basic plotting.
- 🟡 **Live scrolling M-mode.** Stream frames and render a live M-mode image on the host.
  *Teaches:* real-time visualization, buffering, framerate. *Needs:* streaming firmware.
- 🟡 **Host-side DSP.** Filter / envelope-detect / decimate the raw RF in Python or the
  browser; compare with the on-device result. *Teaches:* the DSP pipeline, on- vs off-
  device trade-offs.
- 🟡 **Browser oscilloscope.** Use Web Serial / WebUSB to pull data straight into a web
  page — no install. *Teaches:* WebSerial, zero-install tooling; great for a badge demo.
- 🔴 **Matched filtering & pulse compression.** Reconstruct coded-excitation captures on
  the host; quantify the SNR gain. *Teaches:* correlation processing.
- 🔴 **Log & analyse a dataset.** Record a muscle-contraction session and post-process
  (peak tracking, motion vs time). *Teaches:* dataset handling, biosignal analysis.
- 🔴 **Build a mini-app.** Wrap capture + display + a measurement (distance, rate) into a
  small GUI or web app participants take home. *Teaches:* full application assembly.

---

## 5. Cross-cutting / whole-workshop ideas

- **A guided "golden path"** through one activity per layer (assemble → range → tune a
  PIO pulse → plot on host) as the default 2–3 h track; the rest is a self-serve menu.
- **Station format:** four tables (HW / physics / firmware / host), each with one 🟡
  anchor activity and a 🔴 stretch card.
- **Challenge / competition:** e.g. best axial resolution, deepest reliable echo,
  cleverest coded-excitation gain, or nicest OLED UI — voted at the end.
- **Take-home kit:** the badge itself + a repo with the firmware, host scripts, and this
  activity menu so participants can keep going.
- **Progressive reveal:** ship a working default firmware so *everyone* gets an image
  first; deeper layers modify from a known-good baseline (never a blank board).

---

## Open questions for the workshop design

- Session length and audience skill mix (conference attendees — mixed) → which anchor
  activities are the default track?
- How much is pre-assembled vs soldered live? (Bring-up as an activity vs a working
  board handed out.)
- Do we ship raw-RF access to everyone (unlocks coded excitation + DSP activities) or
  gate it behind the deep track? (ties to the open **RF-ACCESS** decision.)
- Which phantoms/targets are practical to bring to a conference room?
- What host tooling do we standardise on — Python scripts, a WebSerial page, or both?
