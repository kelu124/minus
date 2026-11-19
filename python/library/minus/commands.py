"""Single source of truth: which firmware commands the library covers, and the firmware it was written for.

``python -m minus.fwsync`` compares these tables with the C sources (dispatch tables, ``help()`` usage lines,
``version.h``). When the firmware changes, update this file, the matching ``Minus`` method / parser, the tests and
the notebooks, then run ``python -m minus.fwsync --update``.
"""
from __future__ import annotations

from dataclasses import dataclass
from typing import Dict, Optional

# Firmware this library version was written and tested against.
FIRMWARE = {
    "rp": {"name": "minus-rp2354", "version": "1.1.2"},
    "pic": {"name": "minus-pic32", "version": "1.1.0"},
    "proto": 10,
}


@dataclass(frozen=True)
class Cmd:
    usage: Optional[str]     # usage exactly as printed by the RP `help` (None = not listed there)
    method: Optional[str]    # Minus method that sends it (None = intentionally not wrapped)
    summary: str


# RP2354A USB CLI: dispatch token -> Cmd
RP_COMMANDS: Dict[str, Cmd] = {
    "help":    Cmd(None, "help", "command list"),
    "?":       Cmd(None, None, "alias of help"),
    "version": Cmd("version", "version", "RP firmware version, board, chip id, unique id"),
    "rgb":     Cmd("rgb R G B [pct]", "rgb", "set the status LED colour; pct = LP5562 brightness % (default 25)"),
    "reboot":  Cmd("reboot", "reboot", "reset the RP2354; `reboot dfu` = UF2 bootloader"),
    "ping":    Cmd("ping", "ping", "PING n -> PONG n round trip to the PIC"),
    "auto":    Cmd("auto|stop", "auto_ping", "ping every 500 ms"),
    "stop":    Cmd(None, "auto_ping", "stop auto ping"),
    "reset":   Cmd("reset", "reset_pic", "pulse the PIC MCLR low"),
    "rdy":     Cmd("rdy", "rdy", "read the RDY line (PIC -> RP)"),
    "trig":    Cmd("trig", "trig", "2 us pulse on TRIG (RP -> PIC)"),
    "raw":     Cmd("raw <text>", "raw", "send one line to the PIC, return its reply"),
    "stat":    Cmd("stat", "stat", "ping counters"),
    "lb":      Cmd("lb", "loopback", "RP UART0 internal loopback self-test"),
    "acq":     Cmd("acq [div [samc [in [navg]]]]", "acq", "capture 4095 ADC samples"),
    "acqcpu":  Cmd("acqcpu [trg [rptcnt [gap [phase]]]]", "acqcpu", "experiment: CPU-loop capture"),
    "acqil":   Cmd("acqil [div [off [navg]]]", "acqil", "experiment: two-channel interleaved capture"),
    "pulse":   Cmd("pulse [hi [lo [dead]]]", "pulse", "one pulser shot, no capture"),
    "pe":      Cmd("pe [hi [lo [in [dead]]]]", "pe", "pulse-echo: pulse + 4095-sample capture"),
    "gain":    Cmd("gain [leg [u1 [u2]]]", "gain", "RX gain (mux leg + unity-gain bypass per stage)"),
    "pc":      Cmd("pc [0|1]", "pattern_correction", "period-4 fixed-pattern correction"),
    "i2c":     Cmd("i2c", "i2c_scan", "scan the I2C bus"),
    "pot":     Cmd("pot <0|1> [n]", "pot", "MCP4531 digipot wiper read / set"),
    "pic":     Cmd("pic ...", "pic_id", "ICSP programmer (see PIC_SUBCOMMANDS)"),
}

# `raw <PIC command>` lines that `help` documents: usage -> Minus method
RAW_HELPERS: Dict[str, str] = {
    "raw AMP1 0|1": "amp1",
    "raw AMP2 0|1": "amp2",
    "raw ADCBB n [ovs]": "adcbb",
}

# `pic <sub>` tokens dispatched in cmd_pic -> Minus method (None = bring-up diagnostic, use `raw_cli`)
PIC_SUBCOMMANDS: Dict[str, Optional[str]] = {
    "help": "pic_help",
    "id": "pic_id",
    "image": "pic_image",
    "flash": "pic_flash",
    "verify": "pic_verify",
    "erase": "pic_erase",
    "pins": "pic_pins",
    "mclr": "pic_mclr", "low": "pic_mclr", "hiz": "pic_mclr", "rise": "pic_mclr",
    "slow": "pic_icsp_speed", "fast": "pic_icsp_speed",
    "pair": None, "rdraw": None, "seq": None,
}

# PIC32 UART link commands (what the RP sends to the PIC) -> Minus method that ends up sending it
PIC_LINK: Dict[str, Optional[str]] = {
    "PING": "ping",
    "TRIG?": "trig_count",
    "ACQ": "acq",            # also sent by pe
    "ACQCPU": "acqcpu",
    "ACQIL": "acqil",
    "AMP1": "amp1",
    "AMP2": "amp2",
    "PC": "pattern_correction",
    "UGE": "gain",
    "ADCBB": "adcbb",
    "ID?": "pic_ident",
    "CLK12": None,           # clock-source diagnostic: raw("CLK12 n")
}

# ACQ input codes (board minUS_08112026, PIC fw >= 0.1.22): 0..15 = ADC1 PINSEL, 16..31 = ADC2 PINSEL + 16
INPUTS = {
    25: "AD2AN9: OA2 output after the anti-alias filter (default)",
    17: "AD2AN1: OA2 output before the filter",
    0: "AD1AN0: OA1 output",
    1: "AD1AN1: OA1 input = LNA output",
}
