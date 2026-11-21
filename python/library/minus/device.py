"""``Minus``: one Python method per RP2354A CLI command.

How a command is framed
-----------------------
The CLI has no prompt, so the library writes the command **followed by a sentinel line** ``#end<k>``.
The firmware handles lines in order and answers the sentinel with ``unknown '#end<k>' — try help``, so
everything printed before that line is the reply to the command, however long it takes (a ``pe`` capture is ~0.9 s
and 4097 lines). Every exchange is kept in ``Minus.history`` (command, reply lines, seconds) and ``Minus.last``,
and each parsed result carries the raw text in ``.raw``, so you can always see what went over the wire.
"""
from __future__ import annotations

import time
import warnings
from dataclasses import dataclass, field
from typing import List, Optional

from . import commands, protocol as P
from .protocol import MinusError
from .transport import SerialTransport


class FirmwareMismatch(UserWarning):
    """The board runs a firmware other than the one this library was written for (commands.FIRMWARE)."""


@dataclass
class Exchange:
    command: str
    lines: List[str]
    seconds: float

    @property
    def text(self) -> str:
        return "\n".join(self.lines)

    def show(self, max_lines: int = 12) -> None:
        """Print the exchange as it went over the wire (long replies elided)."""
        print(f">>> {self.command}")
        ls = self.lines
        if len(ls) > max_lines:
            ls = ls[: max_lines // 2] + [f"... ({len(self.lines) - max_lines} more lines) ..."] + ls[-max_lines // 2:]
        for ln in ls:
            print(f"<<< {ln}")
        print(f"    ({len(self.lines)} lines, {self.seconds * 1000:.0f} ms)")


def _args(*vals) -> str:
    """Positional optional arguments: stop at the first None (the CLI's `[a [b [c]]]` grammar)."""
    out = []
    for v in vals:
        if v is None:
            break
        out.append(str(int(v)))
    return (" " + " ".join(out)) if out else ""


class Minus:
    """A minus board on a USB serial port.

    >>> dev = Minus("/dev/ttyACM0")      # or Minus() to auto-detect
    >>> dev.version().version
    '1.1.1'
    """

    def __init__(self, port: Optional[str] = None, transport=None, check_firmware: bool = True,
                 timeout: float = 10.0, echo: bool = False):
        self.t = transport if transport is not None else SerialTransport(port)
        self.timeout = timeout
        self.echo = echo
        self.history: List[Exchange] = []
        self._seq = 0
        self._sync()
        if check_firmware:
            self.check_firmware()

    # ------------------------------------------------------------------ plumbing
    def close(self) -> None:
        self.t.close()

    def __enter__(self):
        return self

    def __exit__(self, *exc):
        self.close()

    @property
    def last(self) -> Exchange:
        return self.history[-1]

    def _sync(self) -> None:
        """Drop anything the board printed before we connected (banner, half-read lines)."""
        self.exchange("", record=False)

    def exchange(self, command: str, timeout: Optional[float] = None, record: bool = True) -> Exchange:
        """Send one CLI line, return every line printed in reply (see the module docstring for the framing)."""
        if "\n" in command:
            raise ValueError("one command per call")
        self._seq += 1
        marker = f"unknown '#end{self._seq}'"
        t0 = time.time()
        self.t.write(f"{command}\n#end{self._seq}\n".encode() if command else f"#end{self._seq}\n".encode())
        buf = b""
        deadline = t0 + (timeout or self.timeout)
        while marker.encode() not in buf:
            if time.time() > deadline:
                raise TimeoutError(f"no complete reply to {command!r} within {timeout or self.timeout} s "
                                   f"(got {len(buf)} bytes)")
            buf += self.t.read()
        text = buf.decode("utf-8", errors="replace").replace("\r\n", "\n").replace("\r", "\n")
        lines = text[: text.index(marker)].split("\n")
        lines = [ln for ln in lines if ln.strip() != ""]
        if lines and lines[0].startswith("unknown '#end"):      # leftover marker from a timed-out exchange
            lines = [ln for ln in lines if not ln.startswith("unknown '#end")]
        ex = Exchange(command, lines, time.time() - t0)
        if record:
            self.history.append(ex)
            if self.echo:
                ex.show()
        return ex

    def _run(self, command: str, parser, timeout: Optional[float] = None):
        ex = self.exchange(command, timeout)
        if not ex.lines:
            raise MinusError(f"{command!r}: no reply")
        res = parser(ex.lines)
        try:
            res.raw = ex.text
        except AttributeError:
            pass
        return res

    def check_firmware(self, strict: bool = False) -> dict:
        """Compare both firmwares with commands.FIRMWARE; warn (or raise if strict) on a mismatch."""
        rp, pic = self.version(), self.pic_ident()
        want = commands.FIRMWARE
        found = {"rp": (rp.name, rp.version), "pic": (pic.name, pic.version), "proto": (rp.proto, pic.proto)}
        msgs = []
        if (rp.name, rp.version) != (want["rp"]["name"], want["rp"]["version"]):
            msgs.append(f"RP runs {rp.name} {rp.version}, library expects {want['rp']['name']} {want['rp']['version']}")
        if (pic.name, pic.version) != (want["pic"]["name"], want["pic"]["version"]):
            msgs.append(f"PIC runs {pic.name} {pic.version}, library expects {want['pic']['name']} {want['pic']['version']}")
        if rp.proto != want["proto"] or pic.proto != want["proto"]:
            msgs.append(f"link protocol RP {rp.proto} / PIC {pic.proto}, library expects {want['proto']}")
        if msgs:
            msg = "; ".join(msgs) + " — reflash (README, Getting started) or use the matching library version"
            if strict:
                raise MinusError(msg)
            warnings.warn(msg, FirmwareMismatch, stacklevel=2)
        return found

    def raw_cli(self, line: str) -> List[str]:
        """Send any CLI line (diagnostics the library does not wrap) and return the reply lines."""
        return self.exchange(line).lines

    # ------------------------------------------------------------------ identity / housekeeping
    def help(self) -> str:
        return self.exchange("help").text

    def version(self) -> P.Version:
        return self._run("version", P.parse_version)

    def rgb(self, r: int, g: int, b: int, pct: Optional[int] = None) -> bool:
        """Set the RGB LED (0..255 each). ``pct`` = LP5562 brightness in % (0..100; firmware default 25 = dim),
        it scales the PWM. Returns True if the LP5562 (board v1.1) acknowledged."""
        for v in (r, g, b):
            if not 0 <= int(v) <= 255:
                raise ValueError("rgb values are 0..255")
        if pct is not None and not 0 <= int(pct) <= 100:
            raise ValueError("pct is 0..100")
        lines = self.exchange(f"rgb {int(r)} {int(g)} {int(b)}" + ("" if pct is None else f" {int(pct)}")).lines
        P._fail_if_error(lines, "rgb")
        return "LP5562 0x30: ok" in lines[0]

    def reboot(self, dfu: bool = False) -> None:
        """Reset the RP2354 (``dfu=True``: into the UF2 bootloader). Closes the port; reconnect afterwards."""
        self.t.write(b"reboot dfu\n" if dfu else b"reboot\n")
        time.sleep(0.2)
        self.close()

    # ------------------------------------------------------------------ RP <-> PIC link
    def ping(self) -> P.Ping:
        return self._run("ping", P.parse_ping)

    def auto_ping(self, on: bool) -> None:
        """Ping every 500 ms in the background (LED green = ok, blue = no reply, red = garbage)."""
        self.exchange("auto" if on else "stop")

    def stat(self) -> P.Stat:
        return self._run("stat", P.parse_stat)

    def reset_pic(self) -> None:
        self.exchange("reset")

    def rdy(self) -> int:
        return self._run("rdy", P.parse_rdy)

    def trig(self) -> None:
        self.exchange("trig")

    def loopback(self) -> bool:
        return self._run("lb", P.parse_lb)

    def raw(self, text: str) -> Optional[str]:
        """Send one line to the PIC over the UART link; return its one-line reply (None = no reply)."""
        return self._run(f"raw {text}", P.parse_raw)

    def pic_ident(self) -> P.PicIdent:
        """``raw ID?`` -> PIC part, firmware name, version, protocol. Retries once: the first link line after an RP
        reboot can go unanswered."""
        reply = self.raw("ID?")
        for _ in range(3):                  # no reply, or the boot banner of a PIC that was just reset (its boot now
            if reply and reply.startswith("PIC32AK"):   # includes the PLL lock check, pic >= 1.1.2): ask again
                break
            time.sleep(0.05)
            reply = self.raw("ID?")
        return P.parse_pic_ident(reply)

    def pic_lock(self, relock: bool = False) -> P.PicLock:
        """PIC PLL lock state (pic >= 1.1.2). At boot the PIC test-captures and re-locks PLL1 until its captures are uniform
        (the 'slow' 40/60/60 ns ADC pattern is a per-lock state, bench 2026-11-22). ``relock=True`` redoes it now; that
        re-runs the PIC's acq_init (op amps back to boot state: call ``gain(...)`` again)."""
        return P.parse_pic_lock(self.raw("RELOCK" if relock else "LOCK?"))

    def trig_count(self) -> int:
        """``raw TRIG?`` -> number of TRIG rising edges the PIC has counted."""
        r = self.raw("TRIG?") or ""
        if not r.startswith("TRIG "):
            raise MinusError(f"TRIG? -> {r!r}")
        return int(r.split()[1])

    def amp1(self, on: bool) -> bool:
        """PIC op amp 1 off/on (on at boot). Returns the new state."""
        return (self.raw(f"AMP1 {int(bool(on))}") or "").strip() == "AMP1 1"

    def amp2(self, on: bool) -> bool:
        """PIC op amp 2 off/on. Returns the new state."""
        return (self.raw(f"AMP2 {int(bool(on))}") or "").strip() == "AMP2 1"

    def adcbb(self, n: int, ovs: int = 0) -> P.AdcBB:
        """Experiment: time n back-to-back ADC conversions on the PIC (no DMA)."""
        return P.parse_adcbb(self.raw(f"ADCBB {int(n)} {int(ovs)}"))

    # ------------------------------------------------------------------ acquisition
    def acq(self, div: Optional[int] = None, samc: Optional[int] = None, in_: Optional[int] = None,
            navg: Optional[int] = None) -> P.Capture:
        """Capture 4095 samples, no pulse. ``acq(4, 0, 25, 1)`` = 25 Msps on the filtered RX node, single conversions.

        div: SCCP1 trigger period in 5 ns counts (4 = 25 Msps, 10 = 20, 20 = 10, 40 = 5); samc: ADC sampling time
        0..7 (or -1 auto); in_: input code (see ``commands.INPUTS``); navg: 1..16 conversions summed per trigger.
        The PIC keeps div/samc/in/navg between calls; arguments are positional, so giving ``in_`` needs ``samc``.
        """
        if in_ is not None and (div is None or samc is None):
            raise ValueError("acq: in_ needs div and samc (positional CLI arguments)")
        if navg is not None and in_ is None:
            raise ValueError("acq: navg needs div, samc and in_")
        return self._run("acq" + _args(div, samc, in_, navg), lambda ls: P.parse_capture(ls, "acq"))

    def pe(self, hi: Optional[int] = None, lo: Optional[int] = None, in_: Optional[int] = None,
           dead: Optional[int] = None) -> P.Capture:
        """Pulse-echo: one pulse (+5 V for hi ns, both off dead ns, GND for lo ns; defaults 200 / 27 / 500) fired on
        the ADC start, then 4095 samples at 25 Msps on ``in_`` (default 25). Retries (≤ 8 shots) until the sample
        clock is uniform; ``.shots`` says how many it took."""
        return self._run("pe" + _args(hi, lo, in_, dead), lambda ls: P.parse_capture(ls, "pe"))

    def acqcpu(self, trg: Optional[int] = None, rptcnt: Optional[int] = None, gap: Optional[int] = None,
               phase: Optional[int] = None) -> P.Capture:
        """Experiment: CPU-loop capture (no DMA). Leaves the PIC's last acq settings in place."""
        return self._run("acqcpu" + _args(trg, rptcnt, gap, phase), lambda ls: P.parse_capture(ls, "acqcpu"))

    def acqil(self, div: Optional[int] = None, off: Optional[int] = None, navg: Optional[int] = None) -> P.Capture:
        """Experiment: two-channel interleaved capture. **Changes the PIC's div** — run ``acq(4, 0, 25, 1)`` after."""
        return self._run("acqil" + _args(div, off, navg), lambda ls: P.parse_capture(ls, "acqil"))

    # ------------------------------------------------------------------ payload link + DAC test signal (proto 11)
    def link(self, mode: Optional[str] = None, mhz: Optional[float] = None) -> P.LinkStatus:
        """Payload path for every capture: ``link("spi", 12.5)`` (default; CRC-checked SPI frame with UART fallback),
        ``link("uart")`` (0.7 s per capture), ``link()`` = counters only. SPI0 runs at 150 MHz / even divisors:
        12.5 (default) and 18.75 are clean on board 3, 25 MHz fails (PIC client limit, bench 2026-11-21)."""
        if mode is None:
            cmd = "link"
        elif mode == "uart":
            cmd = "link uart"
        elif mode == "spi":
            cmd = "link spi" + (f" {float(mhz):g}" if mhz is not None else "")
        else:
            raise ValueError("link: mode is 'spi' or 'uart'")
        return self._run(cmd, P.parse_link)

    def linktest(self, count: Optional[int] = None, mhz: Optional[float] = None) -> P.LinkTest:
        """SPI link self-test: the PIC fills its buffer with an LFSR pattern, the RP pulls it ``count`` times (default
        10) and checks every word + CRC, then once over the UART. ``mhz`` also changes the link clock."""
        if mhz is not None and count is None:
            raise ValueError("linktest: mhz needs count (positional CLI arguments)")
        cmd = "linktest" + ("" if count is None else f" {int(count)}") + ("" if mhz is None else f" {float(mhz):g}")
        return self._run(cmd, P.parse_linktest, timeout=60)

    def dac(self, mode: Optional[str] = None, *values: float) -> P.Dac:
        """PIC DAC1 test signal on DACOUT1 (U9 pin 3, = acq input 19). ``dac()`` reads the state;
        ``dac("off")``, ``dac("dc", code)``, ``dac("tri", lo, hi, slope)`` (hardware triangle, safe during captures),
        ``dac("sine", hz[, amp[, mid]])`` (DMA-fed: captures at 20-25 Msps come back 'slow' while it runs).
        Codes 205..3890 = 5..95 % of 3.3 V."""
        if mode is None:
            cmd = "dac"
        elif mode == "off":
            cmd = "dac off"
        elif mode in ("dc", "tri", "sine"):
            n = {"dc": (1, 1), "tri": (3, 3), "sine": (1, 3)}[mode]
            if not n[0] <= len(values) <= n[1]:
                raise ValueError(f"dac {mode}: {n[0]}..{n[1]} values")
            vals = [f"{float(values[0]):g}"] + [str(int(v)) for v in values[1:]] if mode == "sine" else [str(int(v)) for v in values]
            cmd = f"dac {mode} " + " ".join(vals)
        else:
            raise ValueError("dac: mode is off | dc | tri | sine")
        return self._run(cmd, P.parse_dac)

    # ------------------------------------------------------------------ ADC extras for pulse-echo (proto 13)
    def acqos(self, os: int, in_: Optional[int] = None, pe: Optional[bool] = None) -> P.Capture:
        """Capture with ADC hardware oversampling: each sample = ``os`` (4 or 16) back-to-back 32 ns conversions, 13 / 14-bit
        (2x / 4x a 12-bit code), 175 / 565 ns per sample = 0.72 / 2.3 ms window. ``pe=True`` fires the pulser on RDY."""
        if os not in (4, 16):
            raise ValueError("acqos: os is 4 or 16")
        if pe is not None and in_ is None:
            in_ = 25
        cmd = f"acqos {os}" + ("" if in_ is None else f" {int(in_)}") + ("" if pe is None else f" {int(bool(pe))}")
        return self._run(cmd, lambda ls: P.parse_capture(ls, "acqos"))

    def tof(self, thr: int, blank_ns: Optional[int] = None, in_: Optional[int] = None, ref: Optional[int] = None) -> P.Tof:
        """Pulse-echo time of flight on the PIC: fires the pulser, captures, returns the first sample after ``blank_ns``
        with |x - ref| > thr and the peak in the next 64 samples (ref None/0 = capture mean). One line, no A-line transfer."""
        cmd = "tof" + _args(thr, blank_ns, in_, ref)
        return self._run(cmd, P.parse_tof)

    def env(self, dec: int, shots: Optional[int] = None, in_: Optional[int] = None) -> P.Envelope:
        """Pulse-echo envelope computed on the PIC: |x - mean| integrated over ``dec`` (4..64) samples, averaged over
        ``shots`` pulses (default 1), 4095/dec values."""
        cmd = "env" + _args(dec, shots, in_)
        return self._run(cmd, P.parse_env, timeout=60)

    # ------------------------------------------------------------------ front end
    def pulse(self, hi: Optional[int] = None, lo: Optional[int] = None, dead: Optional[int] = None) -> P.Pulse:
        """One pulser shot now, no capture (scope check)."""
        return self._run("pulse" + _args(hi, lo, dead), P.parse_pulse)

    def gain(self, leg: Optional[int] = None, u1: Optional[int] = None, u2: Optional[int] = None) -> P.Gain:
        """RX gain. leg 0..3 = Rf 2.2k/4.7k/6.8k/10k on both stages; u1/u2 = 1 puts that stage at x1. No args = read."""
        return self._run("gain" + _args(leg, u1, u2), P.parse_gain)

    def pattern_correction(self, on: Optional[bool] = None) -> P.PatternCorrection:
        """Period-4 fixed-pattern correction on the PIC (on at boot); None = read state + last offsets."""
        return self._run("pc" if on is None else f"pc {int(bool(on))}", P.parse_pc)

    def i2c_scan(self) -> P.I2CScan:
        return self._run("i2c", P.parse_i2c)

    def pot(self, index: int, wiper: Optional[int] = None) -> P.Pot:
        """MCP4531 digipot read / set (not fitted on board 3: raises MinusError there)."""
        return self._run(f"pot {int(index)}" + _args(wiper), P.parse_pot)

    # ------------------------------------------------------------------ PIC programmer (ICSP from the RP)
    def pic_help(self) -> str:
        return self.exchange("pic help").text

    def pic_id(self) -> P.PicProg:
        """Enter ICSP, read DEVID/REVID, exit. Expect part 'PIC32AK1216GC41048'."""
        return self._run("pic id", P.parse_pic_prog)

    def pic_image(self) -> P.PicImage:
        """What PIC image is embedded in the RP firmware (flashed by ``pic_flash``)."""
        return self._run("pic image", P.parse_pic_image)

    def pic_flash(self) -> P.PicProg:
        """Erase + program + verify the embedded PIC image (~1 s). Check ``version()`` first."""
        return self._run("pic flash", P.parse_pic_prog, timeout=30)

    def pic_verify(self) -> P.PicProg:
        return self._run("pic verify", P.parse_pic_prog, timeout=30)

    def pic_erase(self) -> P.PicProg:
        return self._run("pic erase", P.parse_pic_prog, timeout=30)

    def pic_pins(self) -> List[str]:
        """Diagnostic: levels of PGC/PGD/MCLR/RDY/UART_RX."""
        return self.exchange("pic pins").lines

    def pic_mclr(self, mode: str) -> List[str]:
        """Diagnostic: 'low' (hold MCLR low), 'hiz' (release), 'rise' (measure the MCLR rise time)."""
        if mode not in ("low", "hiz", "rise"):
            raise ValueError("mode is low | hiz | rise")
        return self.exchange(f"pic mclr {mode}").lines

    def pic_icsp_speed(self, slow: bool) -> str:
        """ICSP clock ~100 kHz (slow=True) or ~1.2 MHz (default)."""
        return self.exchange("pic slow" if slow else "pic fast").text
