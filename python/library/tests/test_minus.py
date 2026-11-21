"""Offline tests: the library against replies recorded from a real board 3 (tests/fixtures/board3_transcript.json).

Run from python/library:   python3 -m unittest discover -s tests -v
Re-record the fixture after a firmware change (board connected):   python3 tests/record_fixture.py
"""
import json
import sys
import unittest
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))

from minus import FIRMWARE, Minus, MinusError, commands, fwsync, protocol as P  # noqa: E402

FIX = json.loads((HERE / "fixtures" / "board3_transcript.json").read_text())
REPLIES = FIX["replies"]


class ReplayTransport:
    """Answers each CLI line with the recorded reply, then the sentinel echo, like the firmware does."""

    def __init__(self, replies):
        self.replies, self.out, self.sent = replies, b"", []

    def write(self, data: bytes):
        for line in data.decode().split("\n"):
            if not line:
                continue
            if line.startswith("#end"):
                self.out += f"unknown '{line}' — try help\r\n".encode()
                continue
            self.sent.append(line)
            if line not in self.replies:
                raise AssertionError(f"no recorded reply for {line!r}")
            self.out += "".join(ln + "\r\n" for ln in self.replies[line]).encode()

    def read(self) -> bytes:
        out, self.out = self.out[:512], self.out[512:]
        return out

    def close(self):
        pass


def device() -> Minus:
    return Minus(transport=ReplayTransport(REPLIES), check_firmware=False)


class TestFixtureMatchesLibrary(unittest.TestCase):
    def test_fixture_recorded_on_expected_firmware(self):
        self.assertEqual(FIX["firmware"]["rp"], FIRMWARE["rp"]["version"], "re-record the fixture")
        self.assertEqual(FIX["firmware"]["pic"], FIRMWARE["pic"]["version"], "re-record the fixture")


class TestDevice(unittest.TestCase):
    def setUp(self):
        self.d = device()

    def test_version_and_ident(self):
        v = self.d.version()
        self.assertEqual((v.name, v.version, v.proto), ("minus-rp2354", FIRMWARE["rp"]["version"], FIRMWARE["proto"]))
        self.assertIn("minus v1.1", v.board)
        p = self.d.pic_ident()
        self.assertEqual((p.part, p.name, p.proto), ("PIC32AK1216GC41048", "minus-pic32", FIRMWARE["proto"]))
        self.d.check_firmware(strict=True)

    def test_link(self):
        self.assertTrue(self.d.ping().ok)
        self.assertGreaterEqual(self.d.stat().sent, 1)
        self.assertIn(self.d.rdy(), (0, 1))
        self.assertTrue(self.d.loopback())
        self.assertGreaterEqual(self.d.trig_count(), 0)

    def test_gain(self):
        g = self.d.gain(2, 0, 0)
        self.assertEqual((g.leg, g.rf_ohm, g.oa1_unity), (2, 6800.0, False))
        self.assertAlmostEqual(g.total, 60.8, places=1)
        g = self.d.gain(0, 1, 1)
        self.assertTrue(g.oa1_unity and g.oa2_unity)
        self.assertEqual(g.total, 1.0)
        with self.assertRaises(MinusError):
            self.d.gain(7)

    def test_frontend(self):
        self.assertTrue(self.d.pattern_correction().on)
        p = self.d.pulse(100, 500, 27)
        self.assertTrue(p.fired)
        self.assertAlmostEqual(p.hi_ns, 100, delta=7)
        self.assertEqual(self.d.i2c_scan().devices[0][0], 0x30)
        self.assertTrue(self.d.rgb(0, 0, 20))
        self.assertIn("25%", self.d.last.text)              # firmware default brightness
        self.assertTrue(self.d.rgb(255, 0, 0, 100))
        self.assertIn("100%", self.d.last.text)
        with self.assertRaises(ValueError):
            self.d.rgb(1, 2, 3, 101)
        self.assertIn("usage: rgb R G B [pct]", REPLIES["rgb 1 2 3 101"][0])
        self.assertTrue(self.d.amp1(True))
        self.assertFalse(self.d.amp2(False))
        self.assertGreater(self.d.adcbb(100).ns_per_conversion, 0)
        with self.assertRaises(MinusError):
            self.d.pot(0)                           # no MCP4531 on board 3

    def test_captures(self):
        a = self.d.acq(4, 0, 25, 1)
        self.assertEqual((a.n, len(a.samples)), (4095, 4095))
        self.assertAlmostEqual(a.fs_msps, 24.87, places=1)
        self.assertAlmostEqual(a.dt_ns, 40.2, delta=0.5)
        self.assertIsNone(a.pulse_fired)
        e = self.d.pe(200, 500, 25, 27)
        self.assertTrue(e.pulse_fired)
        self.assertGreaterEqual(e.shots, 1)
        self.assertEqual(e.samples.dtype.name, "uint16")
        self.assertAlmostEqual(e.t_us[-1], 4094 * e.dt_ns / 1000)
        self.assertGreater(e.depth_mm()[-1], 100)
        with self.assertRaises(ValueError):
            self.d.acq(in_=25)

    def test_spi_link_and_dac(self):
        s = self.d.link("spi", 12.5)
        self.assertTrue(s.spi)
        self.assertAlmostEqual(s.mhz, 12.5)
        t = self.d.linktest(3)
        self.assertTrue(t.passed, t.raw)
        self.assertEqual((t.count, t.frame_bytes, t.ok), (3, 8202, 3))
        self.assertLess(t.mean_us, 50000)                   # vs ~710 000 us over the UART
        tri = self.d.dac("tri", 512, 3584, 16)
        self.assertEqual((tri.mode, tri.lo, tri.hi, tri.slope), ("tri", 512, 3584, 16))
        self.assertAlmostEqual(tri.period_us, 24.58, places=1)
        c = self.d.acq(4, 0, 19, 1)                          # the triangle on AD2AN3, over SPI
        self.assertTrue(c.link.startswith("spi@"))
        self.assertLess(c.xfer_us, 50000)
        self.assertGreater(int(c.samples.max()) - int(c.samples.min()), 2500)
        self.assertNotIn("link=", c.note)
        self.assertEqual(self.d.dac("dc", 2048).code, 2048)
        sn = self.d.dac("sine", 20000, 800, 2048)
        self.assertEqual((sn.mode, sn.points, sn.amp, sn.mid), ("sine", 50, 800, 2048))
        self.assertEqual(self.d.dac("off").mode, "off")
        self.assertEqual(self.d.dac().mode, "off")
        lk = self.d.pic_lock()
        self.assertTrue(lk.good and lk.tries >= 1)
        with self.assertRaises(ValueError):
            self.d.dac("tri", 1, 2)

    def test_adc_extras(self):
        self.d.dac("dc", 2048)
        a4, a16 = self.d.acqos(4, 19), self.d.acqos(16, 19)
        self.assertAlmostEqual(a4.samples.mean() / 2, 2030, delta=40)          # 13-bit = 2 x the 12-bit code
        self.assertAlmostEqual(a16.samples.mean() / 4, 2030, delta=40)         # 14-bit = 4 x
        self.assertAlmostEqual(a16.dt_ns, 565, delta=20)
        self.assertLess(a16.samples[64:].std() / 4, 1.0)                       # < 1 LSB rms after 16x oversampling
        self.d.dac("dc", 3100)
        t = self.d.tof(1000, 0, 19, 2048)
        self.assertTrue(t.found and t.index == 0 and t.hw_tripped and t.pulse_fired)
        self.d.dac("dc", 2900)                                                 # (distinct command text: the fixture is keyed by it)
        t = self.d.tof(1000, 40, 19, 2048)
        self.assertFalse(t.found or t.hw_tripped)
        self.d.dac("tri", 512, 3584, 16)
        e1, e4 = self.d.env(8, 1, 19), self.d.env(8, 4, 19)
        self.assertEqual((e1.n, e1.dec, e1.shots, e4.shots), (511, 8, 1, 4))
        self.assertAlmostEqual(e1.values.max(), 1490, delta=100)
        self.assertAlmostEqual(e1.values.mean(), 760, delta=120)
        self.assertLess(e4.values.std(), e1.values.std())                     # random triangle phase averages out
        self.assertAlmostEqual(e1.dt_ns, 321.7, delta=2)
        self.d.dac("off")

    def test_pic_programmer(self):
        self.assertEqual(self.d.pic_id().part, "PIC32AK1216GC41048")
        img = self.d.pic_image()
        self.assertEqual(img.name, "minus_pic.hex")
        self.assertEqual(sum(s[1] for s in img.segments), img.nbytes)

    def test_history_and_framing(self):
        self.d.version()
        self.assertEqual(self.d.last.command, "version")
        self.assertEqual(len(self.d.last.lines), 4)
        self.assertNotIn("#end", self.d.last.text)

    def test_help_lists_every_known_usage(self):
        text = self.d.help()
        for c in commands.RP_COMMANDS.values():
            if c.usage:
                self.assertIn(c.usage, text)


class TestParsers(unittest.TestCase):
    def test_ping_variants(self):
        self.assertFalse(P.parse_ping(["ping 3: timeout (20000 us)"]).ok)
        self.assertEqual(P.parse_ping(["ping 4: bad reply 'ERR' (900 us)"]).error, "bad reply 'ERR'")

    def test_raw_no_reply(self):
        self.assertIsNone(P.parse_raw(["no reply ('' partial)"]))
        with self.assertRaises(MinusError):
            P.parse_pic_ident(None)

    def test_capture_errors(self):
        with self.assertRaises(MinusError):
            P.parse_capture(["acq: no reply from PIC"])
        with self.assertRaises(MinusError):
            P.parse_capture(["pe: 8 shots, every capture had a non-uniform (slow) sample clock — nothing printed",
                             "# pulse fired, 8 shot(s)"], "pe")

    def test_link_parsers(self):
        c = P.parse_capture(["# acq n=2 fill=0.1us fs=20.00Msps rp_fill=0us (RDY window timed by the RP crystal) trigger div 4; "
                             "in=19 x link=uart(spi failed: frame crc) xfer=709000us", "1", "2"])
        self.assertEqual((c.link, c.xfer_us), ("uart(spi failed: frame crc)", 709000))
        self.assertTrue(c.note.endswith("in=19 x"))
        with self.assertRaises(MinusError):
            P.parse_dac(["dac: PIC refused (args)", "usage: dac ..."])
        t = P.parse_linktest(["linktest 0: frame crc",
                              "linktest: 2 frames of 8202 B at 25.000 MHz: ok=1 frame errors=1 pattern errors=0 frames / 0 words, no reply=0",
                              "linktest: same buffer over the UART: identical (0 word errors) in 0.71 s"])
        self.assertFalse(t.passed)
        self.assertEqual(t.errors, ["linktest 0: frame crc"])

    def test_pic_flash_lines(self):
        r = P.parse_pic_prog(["ICSP pair 1 fast, 276 PGC clocks. DEVID 0x9da2 DEVREV 2 -> PIC32AK1216GC41048",
                              "bulk erase: ok (19 ms)", "  program 0x800000 +16976: ok",
                              "program: ok (592 ms, 570116 PGC clocks)", "verify: ok (0 bad words of 4260)",
                              "ICSP exit, PIC released (MCLR Hi-Z) — try 'ping'"])
        self.assertTrue(r.ok and r.verify_ok)
        self.assertEqual((r.bad_words, r.total_words), (0, 4260))


class TestFirmwareSync(unittest.TestCase):
    def test_library_matches_firmware_sources(self):
        problems = fwsync.check()
        self.assertEqual(problems, [], "\n" + "\n".join(problems))


if __name__ == "__main__":
    unittest.main()
