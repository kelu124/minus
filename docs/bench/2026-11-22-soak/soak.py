"""Overnight stability soak (no piezo): mixed commands through the Python library, every error counted and logged.
Usage (repo root): /usr/bin/python3 docs/bench/2026-11-22-soak/soak.py [rounds=300]"""
import sys, time, json, random, traceback
sys.path.insert(0, "python/library")
from collections import Counter
from minus import Minus, MinusError
rounds = int(sys.argv[1]) if len(sys.argv) > 1 else 300
random.seed(1)
d = Minus()
d.dac("tri", 512, 3584, 16)
ok, err, errs, times = Counter(), Counter(), [], {}
ops = {
    "pe": lambda: d.pe(),
    "acq": lambda: d.acq(4, 0, 25, 1),
    "acq19": lambda: d.acq(4, 0, 19, 1),
    "tof": lambda: d.tof(1000, 0, 19, 2048),
    "env": lambda: d.env(8, 4, 19),
    "acqos4": lambda: d.acqos(4, 19),
    "linktest": lambda: d.linktest(5),
    "tgc_pe": lambda: (d.tgc((60, 3)), d.pe(), d.tgc("off")),
    "relock": lambda: d.pic_lock(relock=True),
    "ping": lambda: d.ping(),                                # one PING toggles RDY: leaves it high half the time
}
t_start = time.time()
for r in range(rounds):
    if r and r % 100 == 0:                                   # a PIC reset now and then (boot lock check runs again)
        d.reset_pic(); time.sleep(0.3); d.pic_ident(); d.dac("tri", 512, 3584, 16); d.gain(0, 0, 0)
    for name in random.sample(list(ops), len(ops)):
        t0 = time.perf_counter()
        try:
            res = ops[name]()
            if name == "linktest" and not res.passed:
                raise MinusError(f"linktest failed: {res.raw[:200] if res.raw else res}")
            ok[name] += 1
        except Exception as e:
            err[name] += 1
            errs.append({"round": r, "op": name, "error": f"{type(e).__name__}: {e}"[:300], "last": d.last.text[-300:] if d.history else ""})
        times.setdefault(name, []).append(time.perf_counter() - t0)
    if r % 50 == 0:
        print(f"round {r}: ok {sum(ok.values())} err {sum(err.values())} ({time.time() - t_start:.0f} s)", flush=True)
d.tgc("off"); d.dac("off")
summary = {"rounds": rounds, "seconds": time.time() - t_start, "ok": dict(ok), "errors": dict(err),
           "median_ms": {k: 1000 * sorted(v)[len(v) // 2] for k, v in times.items()}, "link": str(d.link()),
           "lock": str(d.pic_lock()), "first_errors": errs[:20]}
d.close()
print(json.dumps(summary, indent=1))
json.dump(summary, open(f"docs/bench/2026-11-22-soak/soak_{time.strftime('%H%M%S')}.json", "w"), indent=1)
