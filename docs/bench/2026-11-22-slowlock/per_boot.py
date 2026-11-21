"""Is the PIC's 'slow' ADC lock (40/60/60 ns pattern, memory 0011/0020, datasheet E2) a per-boot state?
Resets the PIC N times (MCLR from the RP), then counts ACQ statuses per boot. Usage (repo root):
    /usr/bin/python3 docs/bench/2026-11-22-slowlock/per_boot.py [boots=12] [captures=20] [inputs=25,19]"""
import sys, time, json
sys.path.insert(0, "python/library")
from collections import Counter
from minus import Minus
boots = int(sys.argv[1]) if len(sys.argv) > 1 else 12
caps = int(sys.argv[2]) if len(sys.argv) > 2 else 20
inputs = [int(x) for x in (sys.argv[3] if len(sys.argv) > 3 else "25,19").split(",")]
d = Minus(check_firmware=False)
out = []
for b in range(boots):
    d.reset_pic(); time.sleep(0.3); d.raw("ID?")
    row = {"boot": b, "pic": d.pic_ident().version, "lock": d.raw("LOCK?")}
    for inp in inputs:
        c = Counter((d.raw(f"ACQ 4 0 {inp} 1") or "none").split()[-1] for _ in range(caps))
        row[f"in{inp}"] = dict(c)
    out.append(row); print(row, flush=True)
d.close()
json.dump(out, open(f"docs/bench/2026-11-22-slowlock/per_boot_{time.strftime('%H%M%S')}.json", "w"), indent=1)
