# minus

**A minimal, single-channel, low-cost, open-source ultrasound pulse-echo platform —
built as a conference-workshop badge.**

`minus` drives one piezo transducer with a high-voltage pulse, amplifies and digitizes
the returning echo, and streams the raw data to a host. It is designed to be **cheap,
small, simple, and hackable** — a badge attendees can use in an ultrasound-conference
workshop (e.g. **muscle-contraction monitoring**, A-/M-mode) and then extend and
experiment with (coded excitation, on-device DSP, add-on boards).

> ⚠️ **Status: early design.** This repository currently holds the **requirements,
> a survey of comparable systems, a component trade study, and reference designs** —
> not yet a finished board. Non-clinical, for **research / education / NDT** only;
> not a medical device.

## What it is (at a glance)

- **MCU:** Raspberry Pi **RP2350** — precise pulse timing + fast ADC capture via PIO.
- **Signal:** **3–4 MHz** piezo (provided with the kit), **raw RF** A-mode + M-mode.
- **Front end:** unipolar HV pulser (bipolar option) → T/R switch → VGA/TGC → external
  high-speed ADC. Reuses proven blocks from the author's open boards.
- **Badge:** on-board **USB-C** (host + power), **RGB LED + small OLED** for standalone
  display, **Raspberry-Pi 40-pin** extension header, transducer via **SMA / header / uFL**,
  friendly silkscreen + test points, OSHWA certification planned.
- **Open:** open hardware + firmware + host software; designed for JLCPCB fabrication.

## Repository map

| Path | What's there |
|------|--------------|
| [`requirements.md`](requirements.md) | The design requirements (MoSCoW), with open decisions. |
| [`analysis.md`](analysis.md) | Architecture analysis — integrated vs external-ADC routes; pulser and gain options. |
| [`options.md`](options.md) + [`options_prices.csv`](options_prices.csv) | Component trade study (pulser / gain / ADC) with LCSC-referenced pricing. |
| [`systems/`](systems/README.md) | Survey of ~19 comparable ultrasound systems (datasheets, literature, by-IC index). |
| [`design/`](design/README.md) | Reference design files (un0rick, lit3rick, pic0rick, Open Echo, BioGAP shield). |
| [`pdfs/`](pdfs/README.md) | Source papers and component datasheets. |
| [`docs/claude/`](docs/claude/README.md) | Working notes: session logs, decision memory, TODO/DONE, changelog. |

## Lineage & credits

`minus` builds on the open single-channel ultrasound work of **Luc Jonveaux (kelu124)** —
[echomods/Murgen](https://github.com/kelu124/echomods),
[un0rick](https://github.com/kelu124/un0rick),
[lit3rick](https://github.com/kelu124/lit3rick), and
[pic0rick](https://github.com/kelu124/pic0rick) — reusing their proven building blocks
to reduce risk. See [`systems/`](systems/README.md) for the broader field survey.

## License

Intended to be released as **open hardware + open software** (OSHWA certification
planned), following the licensing of the boards above.
