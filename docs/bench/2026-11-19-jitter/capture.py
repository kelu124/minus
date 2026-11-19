#!/usr/bin/env python3
"""E3 sample-comb phase / jitter campaign: many pe shots at a fixed setting, saved with per-shot metadata.

usage (repo root):  /usr/bin/python3 docs/bench/2026-11-19-jitter/capture.py [N_BACK_TO_BACK [N_RANDOM_DELAY]]
writes docs/bench/2026-11-19-jitter/shots.npz (samples [N, 4095] uint16 + per-shot arrays) and meta.json
"""
import json, random, sys, time
from pathlib import Path
import numpy as np
sys.path.insert(0, str(Path(__file__).resolve().parents[3] / "python" / "library"))
from minus import Minus

D = Path(__file__).resolve().parent
n_a = int(sys.argv[1]) if len(sys.argv) > 1 else 300
n_b = int(sys.argv[2]) if len(sys.argv) > 2 else 100
dev = Minus()
ver, pic = dev.version(), dev.pic_ident()
dev.acq(4, 0, 25, 1)                     # known PIC acquisition state (div 4, samc 0, in 25, navg 1)
g = dev.gain(2, 0, 0)
pc = dev.pattern_correction(True)
rows = {k: [] for k in ("samples", "t_unix", "set", "delay_s", "shots", "fill_us", "rp_fill_us", "fired")}
random.seed(1)
for i in range(n_a + n_b):
    s = "A" if i < n_a else "B"
    d = 0.0 if s == "A" else random.uniform(0, 0.05)
    time.sleep(d)
    c = dev.pe(200, 500, 25, 27)
    for k, v in (("samples", c.samples), ("t_unix", time.time()), ("set", s), ("delay_s", d), ("shots", c.shots),
                 ("fill_us", c.fill_us), ("rp_fill_us", c.rp_fill_us), ("fired", c.pulse_fired)):
        rows[k].append(v)
    if i % 50 == 0:
        print(f"{i}/{n_a + n_b} shots={c.shots} fill={c.fill_us}", flush=True)
np.savez_compressed(D / "shots.npz", **{k: np.array(v) for k, v in rows.items()})
(D / "meta.json").write_text(json.dumps({
    "date": time.strftime("%Y-%m-%d %H:%M:%S"), "rp": ver.version, "pic": pic.version, "proto": ver.proto,
    "board": ver.board, "unique_id": ver.unique_id, "command": "pe 200 500 25 27", "gain": g.raw,
    "pattern_correction": pc.on, "n_back_to_back": n_a, "n_random_delay": n_b,
    "note": "set A = back-to-back shots; set B = random 0-50 ms sleep before each shot"}, indent=1))
dev.gain(0, 0, 0)
print("done", len(rows["samples"]), "shots")
