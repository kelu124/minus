# minus — Intended use case

## What it is
A low-cost, open-source, single-channel ultrasound pulse-echo board, designed as a badge for
ultrasound-conference workshops. Attendees use it hands-on during the workshop, then keep hacking
on it afterwards.

## What it does
It fires one single-element piezo transducer (3–4 MHz; the reference probe is 3.3 MHz,
characterised in datasheet Annex A), amplifies and digitises the echo, and streams the raw RF
A-line to a host over USB-C. One capture is 4095 samples at about 25 Msps, roughly 12.7 cm deep
in tissue.

## Primary scenario
Workshop demos of A-mode and M-mode, with muscle-contraction monitoring as the flagship example:
watching the echoes from tissue boundaries move as a muscle contracts.

## Secondary uses (the "extend and experiment" part)
- Teaching and research: the signal chain is open end to end (pulser → protected RX ->
  switchable gain → ADC), raw data is exposed, and there's a Python library plus step-by-step
  notebooks.
- Signal-processing experiments: averaging and alignment, coded excitation, on-device DSP.
- Hardware extension: add-on boards, and changes to the firmware on both MCUs (RP2354A and
  PIC32AK). Everything is open hardware, firmware and docs, built for cheap JLCPCB fabrication.
- Non-destructive testing (NDT): simple thickness or flaw echoes in materials.

## What it is not
A medical device. It is non-clinical and meant for research, education and NDT only, as the
README, datasheet and LICENSE all state.

## Practical limits today
- About 0.9 s per shot, because the link between the two chips runs at 115 200 Bd. M-mode is
  therefore slow (about 1 line per second), not real-time.
- Sample-comb phase jitter and slips (datasheet erratum E3): shots must be aligned before
  averaging.
- TX and RX are on separate connectors, so a single-element probe needs an external tee for now.
These are the main things to improve before the board works well as a live muscle-contraction
demo.
