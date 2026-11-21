"""A/B of the period-4 pattern-correction estimators on the same raw captures (pc 0), with and without a tgc step.
old = per-phase mean minus overall mean (pic <= 1.1.4); new = per 4-sample block deviation, blocks with range > 96 skipped
(pic 1.1.5). Metric: rms of the 4 phase means after correction, in windows before / after the step.
Usage (repo root): /usr/bin/python3 docs/bench/2026-11-22-pc-robust/pc_ab.py [n=20]"""
import sys, json
sys.path.insert(0, "python/library")
import numpy as np
from minus import Minus, protocol as P
n = int(sys.argv[1]) if len(sys.argv) > 1 else 20
def off_old(y):
    z = y[64:]; idx = np.arange(64, len(y)) & 3
    return np.array([z[idx == k].mean() - z.mean() for k in range(4)])
def off_new(y, rmax=96):
    b = y[64:64 + (len(y) - 64) // 4 * 4].reshape(-1, 4)
    ok = (b.max(1) - b.min(1)) <= rmax
    if ok.sum() < 64: return np.zeros(4)
    return (b[ok] - b[ok].mean(1, keepdims=True)).mean(0)
def resid(y, off, t, a, b):
    c = y - off[np.arange(len(y)) & 3]; m = (t >= a) & (t < b); z = c[m]; ph = np.arange(len(y))[m] & 3
    pm = np.array([z[ph == k].mean() for k in range(4)]); return float(np.sqrt(((pm - pm.mean()) ** 2).mean()))
d = Minus(); d.gain(0, 0, 0); d.exchange("pc 0")
out = {}
for tag, tgc in (("no tgc", None), ("tgc 60 3", (60, 3))):
    d.tgc(tgc) if tgc else d.tgc("off")
    rows = []
    for i in range(n):
        c = P.parse_capture(d.exchange("acq 4 0 25", timeout=10).lines); y = c.samples.astype(float); t = c.t_us
        for name, f in (("raw", lambda y: np.zeros(4)), ("old", off_old), ("new", off_new)):
            o = f(y); rows.append((name, resid(y, o, t, 3, 55), resid(y, o, t, 80, 164)))
    res = {}
    for name in ("raw", "old", "new"):
        r = np.array([(a, b) for nm, a, b in rows if nm == name])
        res[name] = dict(before_median=float(np.median(r[:, 0])), after_median=float(np.median(r[:, 1])))
        print(f"{tag:9s} {name}: residual pattern rms  3-55 us {np.median(r[:,0]):5.2f}  80-164 us {np.median(r[:,1]):5.2f} LSB (median of {n})")
    out[tag] = res
d.tgc("off"); d.exchange("pc 1"); d.close()
json.dump(out, open("docs/bench/2026-11-22-pc-robust/pc_ab.json", "w"), indent=1)
