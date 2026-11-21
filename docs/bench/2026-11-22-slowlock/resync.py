"""Can a bad ('slow') boot be healed by re-sourcing CLKGEN12 (SCCP1 trigger clock) FRC -> PLL1 Fout, i.e. re-rolling its
phase against the ADC clock (CLKGEN6), without a reset? Usage (repo root): /usr/bin/python3 docs/bench/2026-11-22-slowlock/resync.py [tries=20]"""
import sys, time, json
sys.path.insert(0, "python/library")
from collections import Counter
from minus import Minus
tries = int(sys.argv[1]) if len(sys.argv) > 1 else 20
d = Minus(check_firmware=False)
def rate(n=10):
    return Counter((d.raw("ACQ 4 0 25 1") or "none").split()[-1] for _ in range(n))
for b in range(20):                                   # find a bad boot first
    d.reset_pic(); time.sleep(0.3); d.raw("ID?")
    r = rate()
    if r.get("slow", 0) >= 8: break
print("bad boot found after", b + 1, "resets:", dict(r))
log = []
for t in range(tries):
    a = d.raw("CLK12 1"); b2 = d.raw("CLK12 5")
    r = rate()
    log.append({"try": t, "clk12": [a, b2], "status": dict(r)}); print(log[-1], flush=True)
d.close()
json.dump(log, open(f"docs/bench/2026-11-22-slowlock/resync_{time.strftime('%H%M%S')}.json", "w"), indent=1)
