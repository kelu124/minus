"""ENV check with the DAC triangle (512..3584, period 24.58 us nominal) on AD2AN3: one shot and averaged shots.
Expected: |tri - mean| = a triangle between ~0 and ~1500 LSB at half the period (12.3 us), mean ~750 LSB (x16 = 12000);
averaging shots with a random triangle phase flattens it toward its mean. Usage (repo root):
    /usr/bin/python3 docs/bench/2026-11-22-adc-extras/env_check.py [dec=8]"""
import sys, re, json
sys.path.insert(0, "python/library")
import numpy as np
from minus import Minus
dec = int(sys.argv[1]) if len(sys.argv) > 1 else 8
d = Minus(check_firmware=False)
d.dac("tri", 512, 3584, 16)
out = {}
for shots in (1, 16):
    ln = d.exchange(f"env {dec} {shots} 19", timeout=30).lines
    h = next(i for i, l in enumerate(ln) if l.startswith("# env "))
    n = int(re.search(r"n=(\d+)", ln[h])[1]); dt = float(re.search(r"dt=([\d.]+)ns", ln[h])[1])
    v = np.array([int(x) for x in ln[h + 1:h + 1 + n]]) / 16.0
    t = np.arange(n) * dt / 1000
    vc = v - (v.max() + v.min()) / 2
    i = np.where((vc[:-1] < 0) & (vc[1:] >= 0))[0]
    per = np.diff(t[i]).mean() if len(i) > 2 else float("nan")
    print(ln[h][:150])
    print(f"shots {shots:2d}: n {n}, dt {dt:.1f} ns, envelope mean {v.mean():.0f} LSB, min {v.min():.0f}, max {v.max():.0f}, "
          f"std {v.std():.0f}, period {per:.2f} us (expect 12.3)")
    out[shots] = dict(n=n, dt_ns=dt, mean=v.mean(), min=v.min(), max=v.max(), std=v.std(), period_us=per)
d.dac("off"); d.close()
json.dump(out, open(f"docs/bench/2026-11-22-adc-extras/env_check_dec{dec}.json", "w"), indent=1)
