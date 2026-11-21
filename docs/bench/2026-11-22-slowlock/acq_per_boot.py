"""End-to-end check of the slow-lock fix: N PIC boots, M library acq() calls each; counts failures and RP auto-relocks.
Usage (repo root): /usr/bin/python3 docs/bench/2026-11-22-slowlock/acq_per_boot.py [boots=20] [acqs=5]"""
import sys, time, json
sys.path.insert(0, "python/library")
from minus import Minus, MinusError
boots = int(sys.argv[1]) if len(sys.argv) > 1 else 20
acqs = int(sys.argv[2]) if len(sys.argv) > 2 else 5
d = Minus(check_firmware=False)
rows = []; fails = relocks = 0
for b in range(boots):
    d.reset_pic(); time.sleep(0.3); d.raw("ID?")
    row = {"boot": b, "lock": d.raw("LOCK?"), "ok": 0, "fail": 0, "relock": 0}
    for k in range(acqs):
        try:
            d.acq(4, 0, 25, 1); row["ok"] += 1
        except MinusError:
            row["fail"] += 1
        row["relock"] += d.last.text.count("re-locked its PLL")
    fails += row["fail"]; relocks += row["relock"]; rows.append(row); print(row, flush=True)
print(f"total: {boots * acqs - fails}/{boots * acqs} captures ok, {relocks} automatic re-locks")
d.close()
json.dump(rows, open(f"docs/bench/2026-11-22-slowlock/acq_per_boot_{time.strftime('%H%M%S')}.json", "w"), indent=1)
