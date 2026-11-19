"""Byte transports for the RP2354A USB-CDC console.

``SerialTransport`` talks to a real board (pyserial). Anything with ``write(bytes)``, ``read() -> bytes`` and
``close()`` works, e.g. ``ReplayTransport`` in the tests.
"""
from __future__ import annotations

import glob
from typing import Optional


class SerialTransport:
    def __init__(self, port: Optional[str] = None, read_timeout: float = 0.02):
        import serial  # pyserial

        self.port = port or find_port()
        self.ser = serial.Serial(self.port, 115200, timeout=read_timeout)   # baud is ignored by USB CDC

    def write(self, data: bytes) -> None:
        self.ser.write(data)
        self.ser.flush()

    def read(self) -> bytes:
        n = self.ser.in_waiting
        return self.ser.read(n if n else 1)

    def close(self) -> None:
        self.ser.close()


def find_port() -> str:
    """First USB-CDC port that looks like the RP2354 (``/dev/ttyACM*`` on Linux, ``usbmodem`` on macOS)."""
    try:
        from serial.tools import list_ports

        for p in list_ports.comports():
            if p.vid == 0x2E8A:                       # Raspberry Pi
                return p.device
    except Exception:
        pass
    ports = sorted(glob.glob("/dev/ttyACM*")) + sorted(glob.glob("/dev/cu.usbmodem*"))
    if not ports:
        raise IOError("no minus board found (no /dev/ttyACM*); pass port='...' explicitly")
    return ports[0]
