"""Parsers for the text the minus RP2354A CLI prints.

Every function here is pure (text in, dataclass out) so it can be unit-tested without a board.
The CLI reply formats are defined by ``printf`` calls in ``firmware/rp2354/main.c``; if one changes,
the matching parser here must change too (``python -m minus.fwsync`` flags firmware edits).
"""
from __future__ import annotations

import re
from dataclasses import dataclass, field
from typing import List, Optional, Tuple

import numpy as np


class MinusError(RuntimeError):
    """The board answered with an error / usage message instead of the expected reply."""


def _fail_on_usage(lines: List[str], cmd: str) -> None:
    """For commands whose normal output lines start with ``<cmd>:`` (link, linktest, dac)."""
    for ln in lines:
        s = ln.strip()
        if s.startswith(("usage:", "unknown '")):
            raise MinusError(f"{cmd!r} -> {s}")


def _fail_if_error(lines: List[str], cmd: str) -> None:
    for ln in lines:
        s = ln.strip()
        if s.startswith(("usage:", "unknown '")) or (s.startswith(f"{cmd}: ") and not s.startswith("pulse: +")):
            raise MinusError(f"{cmd!r} -> {s}")


def _match(rx: str, line: str, what: str) -> re.Match:
    m = re.search(rx, line)
    if not m:
        raise MinusError(f"cannot parse {what}: {line!r}")
    return m


# ------------------------------------------------------------------------------------------------ version
@dataclass
class Version:
    name: str              # FW_NAME, e.g. "minus-rp2354"
    version: str           # "MAJOR.MINOR.PATCH"
    proto: int             # RP<->PIC link protocol
    built: str
    pico_sdk: str
    board: str             # e.g. "minus v1.1"
    flash_kb: int
    chip: str
    chip_id: int
    package_sel: int
    chip_rev: str
    unique_id: str
    raw: str = field(default="", repr=False)


def parse_version(lines: List[str]) -> Version:
    m0 = _match(r"^(\S+) (\d+\.\d+\.\d+) proto (\d+) \(built (.+), pico-sdk (\S+)\)$", lines[0], "version line")
    m1 = _match(r"^board: (.+), flash (\d+) kB$", lines[1], "board line")
    m2 = _match(r"^chip: (\S+)\s+chip_id=0x([0-9a-fA-F]+) package_sel=0x([0-9a-fA-F]+) version=(\S+)$", lines[2], "chip line")
    m3 = _match(r"^unique id: (\S+)$", lines[3], "unique id line")
    return Version(m0[1], m0[2], int(m0[3]), m0[4], m0[5], m1[1], int(m1[2]), m2[1], int(m2[2], 16),
                   int(m2[3], 16), m2[4], m3[1])


# ------------------------------------------------------------------------------------------------ link
@dataclass
class Ping:
    seq: int
    ok: bool
    round_trip_us: Optional[int]
    rdy: Optional[int]
    error: Optional[str] = None
    raw: str = field(default="", repr=False)


def parse_ping(lines: List[str]) -> Ping:
    ln = lines[0]
    m = re.match(r"^ping (\d+): ok, (-?\d+) us, rdy=(\d)$", ln)
    if m:
        return Ping(int(m[1]), True, int(m[2]), int(m[3]))
    m = re.match(r"^ping (\d+): timeout \((-?\d+) us\)$", ln)
    if m:
        return Ping(int(m[1]), False, int(m[2]), None, "timeout")
    m = _match(r"^ping (\d+): bad reply '(.*)' \((-?\d+) us\)$", ln, "ping reply")
    return Ping(int(m[1]), False, int(m[3]), None, f"bad reply {m[2]!r}")


@dataclass
class Stat:
    sent: int
    ok: int
    bad: int
    timeout: int
    raw: str = field(default="", repr=False)


def parse_stat(lines: List[str]) -> Stat:
    m = _match(r"^sent=(\d+) ok=(\d+) bad=(\d+) timeout=(\d+)$", lines[0], "stat")
    return Stat(*(int(x) for x in m.groups()))


def parse_rdy(lines: List[str]) -> int:
    return int(_match(r"^RDY=(\d)$", lines[0], "rdy")[1])


def parse_raw(lines: List[str]) -> Optional[str]:
    """``raw <text>`` -> the PIC's one-line reply, or None if it did not answer within the link timeout."""
    m = re.match(r"^reply: '(.*)'$", lines[0])
    if m:
        return m[1]
    _match(r"^no reply \('(.*)' partial\)$", lines[0], "raw reply")
    return None


def parse_lb(lines: List[str]) -> bool:
    m = _match(r"^uart0 loopback: (.*)$", lines[0], "loopback")
    return m[1] == "ok"


@dataclass
class PicIdent:
    part: str
    name: str
    version: str
    proto: int
    raw: str = field(default="", repr=False)


def parse_pic_ident(reply: Optional[str]) -> PicIdent:
    if reply is None:
        raise MinusError("PIC did not answer ID? (not flashed, held in reset, or link down)")
    m = _match(r"^(\S+) (\S+) (\d+\.\d+\.\d+) proto (\d+)$", reply, "ID? reply")
    return PicIdent(m[1], m[2], m[3], int(m[4]))


# ------------------------------------------------------------------------------------------------ front end
@dataclass
class Gain:
    leg: int
    rf_ohm: float
    oa1: float
    oa1_unity: bool
    oa2: float
    oa2_unity: bool
    total: float           # OA1 x OA2 (the LNA gain is not included)
    total_db: float
    raw: str = field(default="", repr=False)


def parse_gain(lines: List[str]) -> Gain:
    _fail_if_error(lines, "gain")
    m = _match(r"^gain leg (\d) \(Rf ([\d.]+)k\) OA1 x([\d.]+)( \(UGE\))? OA2 x([\d.]+)( \(UGE\))? = x([\d.]+) \(([-\d.]+) dB",
               lines[0], "gain")
    return Gain(int(m[1]), float(m[2]) * 1000, float(m[3]), bool(m[4]), float(m[5]), bool(m[6]), float(m[7]), float(m[8]))


@dataclass
class PatternCorrection:
    on: bool
    offsets_lsb: Tuple[float, float, float, float]   # per phase 0..3, from the last capture
    raw: str = field(default="", repr=False)


def parse_pc(lines: List[str]) -> PatternCorrection:
    _fail_if_error(lines, "pc")
    m = _match(r"^pattern correction (ON|off); last capture offsets \(LSB, phase 0\.\.3\): (\S+) (\S+) (\S+) (\S+)$",
               lines[0], "pc")
    return PatternCorrection(m[1] == "ON", tuple(float(x) for x in m.groups()[1:]))


@dataclass
class Pulse:
    hi_ns: float           # +5 V phase
    dead_ns: float         # both FETs off
    lo_ns: float           # GND phase
    clk_sys_mhz: int
    fired: bool
    raw: str = field(default="", repr=False)


def parse_pulse(lines: List[str]) -> Pulse:
    _fail_if_error(lines, "pulse")
    m = _match(r"^pulse: \+5V ([\d.]+) ns, off ([\d.]+) ns, GND ([\d.]+) ns, then released \(clk_sys (\d+) MHz\)$",
               lines[0], "pulse")
    return Pulse(float(m[1]), float(m[2]), float(m[3]), int(m[4]), lines[1].strip() == "fired")


@dataclass
class I2CScan:
    devices: List[Tuple[int, str]]      # (7-bit address, name the firmware knows or "?")
    raw: str = field(default="", repr=False)


def parse_i2c(lines: List[str]) -> I2CScan:
    devs = []
    for ln in lines:
        m = re.match(r"^\s+0x([0-9A-Fa-f]{2})\s+(.*)$", ln)
        if m:
            devs.append((int(m[1], 16), m[2]))
    m = _match(r"^i2c scan: (\d+) device\(s\)$", lines[-1], "i2c scan")
    if int(m[1]) != len(devs):
        raise MinusError(f"i2c scan count mismatch: {lines!r}")
    return I2CScan(devs)


@dataclass
class Pot:
    index: int             # 0 = U11 (OA2 feedback), 1 = U18 (AD8338)
    wiper: int             # 0..128
    r_aw_ohm: float
    oa2_gain: Optional[float]
    was_set: bool
    raw: str = field(default="", repr=False)


def parse_pot(lines: List[str]) -> Pot:
    _fail_if_error(lines, "pot")
    m = re.match(r"^pot (\d) .*: wiper (\d+) -> R_AW ~ (\d+) ohm(?: -> OA2 gain = 1 \+ R_AW / R49 1k ~ x([\d.]+))?( \(set\))?$", lines[0])
    if not m:
        raise MinusError(f"pot -> {lines[0]}")
    return Pot(int(m[1]), int(m[2]), float(m[3]), float(m[4]) if m[4] else None, bool(m[5]))


# ------------------------------------------------------------------------------------------------ captures
@dataclass
class Capture:
    """One A-line (``acq``, ``pe``, ``acqcpu``, ``acqil``)."""
    samples: np.ndarray    # uint16 ADC codes (12-bit, or 12 + log2(navg) bits when navg > 1)
    n: int
    fill_us: float         # capture window measured by the PIC Timer1
    fs_msps: Optional[float]
    rp_fill_us: int        # same window timed by the RP from the RDY line (-1 = not seen)
    note: str              # the firmware's description of the settings
    pulse_fired: Optional[bool] = None   # pe only
    shots: Optional[int] = None          # pe only: how many shots it took to get a uniform 40 ns capture
    link: Optional[str] = None           # proto 11: how the payload came, e.g. "spi@12.50MHz", "uart", "uart(spi failed: frame crc)"
    xfer_us: Optional[int] = None        # proto 11: payload transfer time (request + frame), RP clock
    raw: str = field(default="", repr=False)

    @property
    def dt_ns(self) -> float:
        """Mean sample period in ns (fill / n)."""
        return self.fill_us * 1000.0 / self.n

    @property
    def t_us(self) -> np.ndarray:
        """Time axis in microseconds, one value per sample."""
        return np.arange(self.n) * self.dt_ns / 1000.0

    def depth_mm(self, c_m_s: float = 1540.0) -> np.ndarray:
        """Round-trip depth axis in mm for a sound speed c (default soft tissue, 1540 m/s)."""
        return self.t_us * 1e-6 * c_m_s / 2 * 1000.0


_ACQ_HDR = re.compile(r"^# acq n=(\d+) fill=([\d.]+)us fs=([\d.]+|\?)(?:Msps)? rp_fill=(-?\d+)us "
                      r"\(RDY window timed by the RP crystal\) ?(.*)$")


def parse_capture(lines: List[str], cmd: str = "acq") -> Capture:
    hdr_i = next((i for i, ln in enumerate(lines) if ln.startswith("# acq ")), None)
    if hdr_i is None:
        bad = [ln for ln in lines if ln.strip()]
        raise MinusError(f"{cmd!r} -> {bad[0] if bad else 'no output'}")
    m = _ACQ_HDR.match(lines[hdr_i])
    if not m:
        raise MinusError(f"cannot parse capture header: {lines[hdr_i]!r}")
    n = int(m[1])
    body = lines[hdr_i + 1: hdr_i + 1 + n]
    if len(body) != n or not all(s.strip().isdigit() for s in body):
        raise MinusError(f"{cmd}: expected {n} samples, got {len(body)} lines")
    fired = shots = None
    for ln in lines[hdr_i + 1 + n:]:
        p = re.match(r"^# pulse (fired|did NOT fire.*), (\d+) shot\(s\)$", ln)
        if p:
            fired, shots = p[1] == "fired", int(p[2])
    note, link, xfer = m[5], None, None
    lk = _LINK_TAIL.search(note)
    if lk:
        note, link, xfer = note[:lk.start()], lk[1], int(lk[2])
    return Capture(np.array([int(s) for s in body], dtype=np.uint16), n, float(m[2]),
                   None if m[3] == "?" else float(m[3]), int(m[4]), note, fired, shots, link, xfer)


_LINK_TAIL = re.compile(r" link=(spi@[\d.]+MHz|uart(?:\(.*\))?) xfer=(\d+)us$")


# ------------------------------------------------------------------------------------------------ SPI link + DAC (proto 11)
@dataclass
class LinkStatus:
    """``link``: payload path and counters since the RP booted."""
    spi: bool                  # True = SPI frame (UART fallback), False = UART only
    mhz: float                 # SPI0 clock actually set
    frames: int
    frame_errors: int
    fallbacks: int
    no_reply: int
    last_bytes: Optional[int] = None
    last_us: Optional[int] = None
    raw: str = field(default="", repr=False)


def parse_link(lines: List[str]) -> LinkStatus:
    _fail_on_usage(lines, "link")
    ln = next((l for l in lines if l.startswith("link: payload over")), None)
    if ln is None:
        raise MinusError(f"link -> {lines[0] if lines else 'no output'}")
    m = _match(r"^link: payload over (SPI|UART)[^;]*; SPI0 ([\d.]+) MHz .*frames ok=(\d+) frame errors=(\d+) "
               r"uart fallbacks=(\d+) no-reply=(\d+)", ln, "link")
    last = re.search(r"last frame (\d+) B in (\d+) us", ln)
    return LinkStatus(m[1] == "SPI", float(m[2]), int(m[3]), int(m[4]), int(m[5]), int(m[6]),
                      int(last[1]) if last else None, int(last[2]) if last else None)


@dataclass
class LinkTest:
    """``linktest``: PIC LFSR pattern pulled over SPI ``count`` times, then once over the UART."""
    count: int
    frame_bytes: int
    mhz: float
    ok: int
    frame_errors: int
    pattern_error_frames: int
    pattern_error_words: int
    no_reply: int
    mean_us: Optional[float] = None
    min_us: Optional[int] = None
    max_us: Optional[int] = None
    kbytes_per_s: Optional[float] = None
    uart_identical: Optional[bool] = None
    errors: List[str] = field(default_factory=list)   # per-frame failure lines
    raw: str = field(default="", repr=False)

    @property
    def passed(self) -> bool:
        return self.ok == self.count and self.uart_identical is True


def parse_linktest(lines: List[str]) -> LinkTest:
    _fail_on_usage(lines, "linktest")
    head = next((l for l in lines if re.match(r"^linktest: \d+ frames of", l)), None)
    if head is None:
        raise MinusError(f"linktest -> {lines[0] if lines else 'no output'}")
    m = _match(r"^linktest: (\d+) frames of (\d+) B at ([\d.]+) MHz: ok=(\d+) frame errors=(\d+) pattern errors=(\d+) "
               r"frames / (\d+) words, no reply=(\d+)$", head, "linktest")
    r = LinkTest(int(m[1]), int(m[2]), float(m[3]), int(m[4]), int(m[5]), int(m[6]), int(m[7]), int(m[8]))
    for ln in lines:
        t = re.match(r"^linktest: SPIX request\+frame (\d+) us mean \(min (\d+), max (\d+)\) = (\d+) kB/s", ln)
        if t:
            r.mean_us, r.min_us, r.max_us, r.kbytes_per_s = float(t[1]), int(t[2]), int(t[3]), float(t[4])
        u = re.match(r"^linktest: same buffer over the UART: (identical|DIFFERS)", ln)
        if u:
            r.uart_identical = u[1] == "identical"
        if ln.startswith("linktest: UART cross-check failed"):
            r.uart_identical = False
        if re.match(r"^linktest \d+: ", ln):
            r.errors.append(ln)
    return r


@dataclass
class Dac:
    """``dac``: state of the PIC DAC1 test signal on DACOUT1 (codes 205..3890 = 5..95 % of 3.3 V)."""
    mode: str                          # "off" | "dc" | "tri" | "sine"
    code: Optional[int] = None         # dc
    lo: Optional[int] = None           # tri
    hi: Optional[int] = None
    slope: Optional[int] = None
    period_us: Optional[float] = None  # tri: nominal period
    hz: Optional[float] = None         # sine: actual frequency
    points: Optional[int] = None
    update_us: Optional[float] = None
    amp: Optional[int] = None
    mid: Optional[int] = None
    raw: str = field(default="", repr=False)


def parse_dac(lines: List[str]) -> Dac:
    _fail_on_usage(lines, "dac")
    for ln in lines:
        if ln.startswith("dac: PIC refused") or ln.startswith("dac: no reply") \
                or ln.startswith("dac: unexpected"):
            raise MinusError(ln)
        if ln == "dac: off":
            return Dac("off")
        m = re.match(r"^dac: dc (\d+) = ", ln)
        if m:
            return Dac("dc", code=int(m[1]))
        m = re.match(r"^dac: triangle (\d+)\.\.(\d+) .*, slope (\d+) .*period ~([\d.]+) us", ln)
        if m:
            return Dac("tri", lo=int(m[1]), hi=int(m[2]), slope=int(m[3]), period_us=float(m[4]))
        m = re.match(r"^dac: sine ([\d.]+) Hz, (\d+) points, update every ([\d.]+) us, .*\(codes (\d+) \+- (\d+)\)", ln)
        if m:
            return Dac("sine", hz=float(m[1]), points=int(m[2]), update_us=float(m[3]), mid=int(m[4]), amp=int(m[5]))
    raise MinusError(f"dac -> {lines[0] if lines else 'no output'}")


# ------------------------------------------------------------------------------------------------ PIC programmer
@dataclass
class PicProg:
    """Result of ``pic id | flash | verify | erase``."""
    devid: Optional[int] = None
    devrev: Optional[int] = None
    part: Optional[str] = None
    erase_ok: Optional[bool] = None
    program_ok: Optional[bool] = None
    verify_ok: Optional[bool] = None
    bad_words: Optional[int] = None
    total_words: Optional[int] = None
    lines: List[str] = field(default_factory=list)
    raw: str = field(default="", repr=False)

    @property
    def ok(self) -> bool:
        steps = [self.erase_ok, self.program_ok, self.verify_ok]
        return self.devid is not None and all(s is not False for s in steps)


def parse_pic_prog(lines: List[str]) -> PicProg:
    _fail_if_error(lines, "pic")
    r = PicProg(lines=list(lines))
    for ln in lines:
        if (m := re.search(r"DEVID 0x([0-9a-fA-F]+) DEVREV (\d+) -> (.+)$", ln)):
            r.devid, r.devrev, r.part = int(m[1], 16), int(m[2]), m[3]
        elif (m := re.match(r"^bulk erase: (\S+)", ln)):
            r.erase_ok = m[1] == "ok"
        elif (m := re.match(r"^program: (\S+)", ln)):
            r.program_ok = m[1] == "ok"
        elif (m := re.match(r"^verify: (\S+) \((\d+) bad words of (\d+)\)", ln)):
            r.verify_ok, r.bad_words, r.total_words = m[1] == "ok", int(m[2]), int(m[3])
    if r.devid is None:
        raise MinusError("pic: no DEVID read — " + " / ".join(lines))
    return r


@dataclass
class PicImage:
    name: str
    nbytes: int
    segments: List[Tuple[int, int, str]]   # (address, length, kind)
    raw: str = field(default="", repr=False)


def parse_pic_image(lines: List[str]) -> PicImage:
    m = _match(r"^image '(.*)': (\d+) segment\(s\), (\d+) bytes$", lines[0], "pic image")
    segs = []
    for ln in lines[1:]:
        s = re.match(r"^\s+0x([0-9a-fA-F]+) \+(\d+) (.*)$", ln)
        if s:
            segs.append((int(s[1], 16), int(s[2]), s[3]))
    return PicImage(m[1], int(m[3]), segs)


@dataclass
class AdcBB:
    n: int
    ovs: int
    ticks: int
    tick_ns: int
    data: int
    raw: str = field(default="", repr=False)

    @property
    def ns_per_conversion(self) -> float:
        return self.ticks * self.tick_ns / self.n if self.n else float("nan")


def parse_adcbb(reply: Optional[str]) -> AdcBB:
    m = _match(r"^ADCBB (\d+) (\d+) (\d+) (\d+) (\d+)$", reply or "", "ADCBB reply")
    return AdcBB(*(int(x) for x in m.groups()))
