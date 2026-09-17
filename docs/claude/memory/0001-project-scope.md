# 0001 — Project scope

**Status:** current (as of 2026-09-17)

## What "minus" is

A **minimal, single-channel, low-cost ultrasound imaging platform**.

Guiding constraints (as stated by the user at kickoff):

- **Minimal** — smallest viable design; avoid unnecessary parts and complexity.
- **Single channel** — one transmit/receive path, not a phased array.
- **Cheap** — cost is a first-class design driver.

## Open questions (to resolve in discussion)

These are not yet decided — placeholders for upcoming exchanges:

- Target application / imaging depth & frequency range.
- Transducer choice (single-element, and how it scans — if at all).
- Pulser and analog front-end approach.
- Digitizer / ADC and sampling strategy.
- Compute/host (MCU, FPGA, PC) and display path.
- Related prior work in the user's other repos (e.g. `we_gate`).

_Update this file as scope firms up; supersede rather than rewrite silently._
