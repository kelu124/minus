"""TGC check without a piezo: the RX-chain noise on the ADC node (input 25) rises with the 4052 gain leg. With 'tgc 60 3'
(leg 0 -> leg 3 at 60 us) the noise rms after 60 us should match a plain leg-3 capture and before it a plain leg-0 one.
Usage (repo root): /usr/bin/python3 docs/bench/2026-11-22-tgc-b64/tgc_noise.py [reps=5]"""
import sys, json, re
sys.path.insert(0, "python/library")
import numpy as np
from minus import Minus, protocol as P
reps = int(sys.argv[1]) if len(sys.argv) > 1 else 5
d = Minus(check_firmware=False)
def seg_rms(c, t0, t1):
    t = c.t_us; y = c.samples.astype(float); m = (t >= t0) & (t < t1)
    return y[m].std()
res = {}
for name, leg, tgc in [("leg 0", 0, "off"), ("leg 3", 3, "off"), ("leg 0 + tgc 60 3", 0, "60 3")]:
    d.gain(leg, 0, 0); d.exchange(f"tgc {tgc}")
    a, b = [], []
    for r in range(reps):
        c = P.parse_capture(d.exchange("acq 4 0 25 1", timeout=10).lines)
        a.append(seg_rms(c, 10, 55)); b.append(seg_rms(c, 70, 160))
    res[name] = dict(rms_10_55us=float(np.mean(a)), rms_70_160us=float(np.mean(b)), note_tail=c.note[-60:])
    print(f"{name:18s} rms 10-55 us {np.mean(a):6.2f} LSB   rms 70-160 us {np.mean(b):6.2f} LSB   ({c.note[-40:]})")
d.exchange("tgc off"); d.gain(0, 0, 0); d.close()
json.dump(res, open("docs/bench/2026-11-22-tgc-b64/tgc_noise.json", "w"), indent=1)
