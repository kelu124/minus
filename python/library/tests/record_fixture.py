#!/usr/bin/env python3
"""Re-record tests/fixtures/board3_transcript.json from a connected board (after a firmware change).

usage (from python/library):   python3 tests/record_fixture.py [PORT]
Every command test_minus.py replays must be listed here. Fires the pulser a few times.
"""
import json
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
from minus import Minus  # noqa: E402

CMDS = ["help", "version", "raw ID?", "ping", "stat", "rdy", "trig", "raw TRIG?", "lb", "gain", "gain 2 0 0",
        "gain 0 1 1", "gain 7", "gain 0 0 0", "pc", "pc 1", "pulse", "pulse 100 500 27", "i2c", "rgb 0 0 20", "rgb 255 0 0 100", "rgb 1 2 3 101",
        "raw AMP1 1", "raw AMP2 0", "raw ADCBB 100 0", "pot 0", "acq 4 0 25 1", "pe", "pe 200 500 25 27",
        "link spi 12.5", "linktest 3", "dac tri 512 3584 16", "acq 4 0 19 1", "dac dc 2048", "dac sine 20000 800 2048",
        "dac off", "dac", "link",
        "pic help", "pic image", "pic id", "bogus"]

if __name__ == "__main__":
    dev = Minus(sys.argv[1] if len(sys.argv) > 1 else None, check_firmware=True)
    replies = {c: dev.exchange(c, timeout=30).lines for c in CMDS}
    dev.rgb(0, 0, 0)
    out = {"firmware": {"rp": dev.version().version, "pic": dev.pic_ident().version}, "replies": replies}
    (HERE / "fixtures" / "board3_transcript.json").write_text(json.dumps(out, indent=0))
    print(f"recorded {len(CMDS)} replies, rp {out['firmware']['rp']} / pic {out['firmware']['pic']}")
