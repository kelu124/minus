"""minus — Python interface to the minus single-channel ultrasound board (RP2354A + PIC32AK).

    from minus import Minus
    dev = Minus()                 # auto-detects /dev/ttyACM*, checks both firmware versions
    a = dev.pe()                  # one pulse-echo A-line: a.samples, a.t_us, a.fs_msps
    dev.last.show()               # what was sent / received

See python/notebooks/ for worked examples, and ``python -m minus.fwsync`` for the firmware-sync check.
"""
from .commands import FIRMWARE, INPUTS
from .device import Exchange, FirmwareMismatch, Minus
from .protocol import Capture, MinusError

__all__ = ["Minus", "Exchange", "Capture", "MinusError", "FirmwareMismatch", "FIRMWARE", "INPUTS"]
__version__ = "1.1.7"
