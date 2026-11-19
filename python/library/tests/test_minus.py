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
        self.assertEqual((v.name, v.version, v.proto), ("minus-rp2354", FIRMWARE["rp"]["version"], 10))
        self.assertIn("minus v1.1", v.board)
        p = self.d.pic_ident()
        self.assertEqual((p.part, p.name, p.proto), ("PIC32AK1216GC41048", "minus-pic32", 10))
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
