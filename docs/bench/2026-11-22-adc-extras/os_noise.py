"""ACQOS check: DAC DC level on AD2AN3 (input 19), noise of acq vs acqos 4 / 16. Usage (repo root):
    /usr/bin/python3 docs/bench/2026-11-22-adc-extras/os_noise.py [code=2048] [reps=5]"""
import sys, json, time
sys.path.insert(0, "python/library")
import numpy as np
from minus import Minus, protocol as P
code = int(sys.argv[1]) if len(sys.argv) > 1 else 2048
reps = int(sys.argv[2]) if len(sys.argv) > 2 else 5
d = Minus(check_firmware=False)
print(d.dac("dc", code)); time.sleep(0.05)
res = {}
for name, cmd, scale in [("acq 25 Msps", "acq 4 0 19 1", 1), ("acqos 4", "acqos 4 19", 2), ("acqos 16", "acqos 16 19", 4)]:
    rows = []
    for r in range(reps):
        c = P.parse_capture(d.exchange(cmd, timeout=10).lines, cmd)
        y = c.samples.astype(float) / scale                       # back to 12-bit LSB units
        rows.append((y.mean(), y[64:].std(), c.fill_us, c.dt_ns))
    a = np.array(rows)
    res[name] = dict(mean_lsb=a[:, 0].mean(), rms_lsb=a[:, 1].mean(), fill_us=a[0, 2], dt_ns=a[0, 3], raw_max=int(c.samples.max()))
    print(f"{name:12s} mean {a[:,0].mean():8.2f} LSB(12-bit)  rms {a[:,1].mean():5.2f} LSB  dt {a[0,3]:6.1f} ns  fill {a[0,2]:7.1f} us  raw max {int(c.samples.max())}")
d.dac("off"); d.close()
json.dump(res, open(f"docs/bench/2026-11-22-adc-extras/os_noise_{code}.json", "w"), indent=1)
