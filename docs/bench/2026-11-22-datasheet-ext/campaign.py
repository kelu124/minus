"""Datasheet rev 0.3 campaign: every feature added since rev 0.2, re-tested on board 3 WITH a transducer (echoes at ~42-45 us
and ~85-99 us), one compressed .npz per test in this folder (arrays + settings + firmware versions; no raw text dumps).

Run from the repo root:   /usr/bin/python3 docs/bench/2026-11-22-datasheet-ext/campaign.py [test ...]
Tests: pe_ref link fmt lock dac acqos tof env tgc pc   (default: all, in that order). Then analyze.py.
"""
import sys, time, json, re, traceback
from pathlib import Path
sys.path.insert(0, "python/library")
import numpy as np
from minus import Minus, protocol as P

OUT = Path(__file__).resolve().parent
d = Minus()
META = dict(rp=d.version().version, pic=d.pic_ident().version, proto=d.version().proto, date=time.strftime("%Y-%m-%d %H:%M"),
            board="minus v1.1 (board 3), RP unique id " + d.version().unique_id, transducer="3.3 MHz single element (Annex A)")
print(META, flush=True)


def save(name, **arrays):
    np.savez_compressed(OUT / f"{name}.npz", meta=json.dumps(META), **arrays)
    print(f"  -> {name}.npz", flush=True)


def caps(cmd, n):
    out = [P.parse_capture(d.exchange(cmd, timeout=20).lines, cmd) for _ in range(n)]
    return np.array([c.samples for c in out]), out


GAINS = [(0, 1, 1), (0, 1, 0), (0, 0, 0), (1, 0, 0), (2, 0, 0)]


def t_pe_ref():
    """pe at five gains, 16 shots each: the echo reference for everything else."""
    res = {}
    for leg, u1, u2 in GAINS:
        g = d.gain(leg, u1, u2)
        s, c = caps("pe", 16)
        res[f"g{leg}{u1}{u2}"] = s; res[f"g{leg}{u1}{u2}_total"] = g.total
        res[f"g{leg}{u1}{u2}_dt_ns"] = np.array([x.dt_ns for x in c])
    save("pe_ref", **res)


def t_link():
    """linktest at the three clean SPI clocks (mode 1), 200 frames each; SPIX->RDY and clocking times."""
    rows = []
    for mhz in (12.5, 18.75, 25.0):
        t = d.linktest(200, mhz)
        rdy = wire = np.nan
        for ln in t.raw.splitlines() if t.raw else d.last.lines:
            m = re.search(r"SPIX -> RDY (\d+) us, SPI clocking (\d+) us", ln)
            if m: rdy, wire = float(m[1]), float(m[2])
        rows.append((mhz, t.count, t.ok, t.frame_errors, t.pattern_error_frames, t.mean_us, t.min_us, t.max_us, rdy, wire,
                     float(t.uart_identical)))
    d.link("spi", 12.5)
    save("link", table=np.array(rows), columns=np.array(["mhz", "count", "ok", "frame_err", "pattern_err_frames", "mean_us",
                                                          "min_us", "max_us", "spix_to_rdy_us", "clocking_us", "uart_identical"]))


def t_fmt():
    """End-to-end time of a library acq() with the text and the base64 sample output, 20 each."""
    res = {}
    for f in ("text", "b64"):
        d.fmt(f); ts = []
        for _ in range(20):
            t0 = time.perf_counter(); d.acq(4, 0, 25, 1); ts.append(time.perf_counter() - t0)
        res[f"{f}_s"] = np.array(ts); res[f"{f}_chars"] = len(d.last.text)
    d.fmt("b64")
    save("fmt", **res)


def t_lock():
    """Boot-time PLL lock check: 10 PIC resets; locks needed and ACQ status counts (20 captures) per boot."""
    rows = []
    for b in range(10):
        d.reset_pic(); time.sleep(0.3); d.pic_ident()
        lk = d.pic_lock()
        st = [((d.raw("ACQ 4 0 25 1") or "x").split()[-1]) for _ in range(20)]
        rows.append((b, lk.tries, lk.slow, st.count("ok"), st.count("slow")))
        print("   boot", rows[-1], flush=True)
    d.gain(1, 0, 0); d.gain(0, 0, 0)                        # UGE back to the RP's state after the resets
    save("lock", table=np.array(rows), columns=np.array(["boot", "locks_tried", "slow_of_8", "ok_of_20", "slow_of_20"]))


def t_dac():
    """PIC DAC on AD2AN3 (input 19): triangle over SPI and UART, DC levels, sine at 20 Msps."""
    res = {}
    d.dac("tri", 512, 3584, 16)
    s, c = caps("acq 4 0 19 1", 4); res["tri_spi"] = s; res["tri_dt_ns"] = c[0].dt_ns
    d.link("uart"); s, _ = caps("acq 4 0 19 1", 1); res["tri_uart"] = s; d.link("spi", 12.5)
    for code in (512, 2048, 3584):
        d.dac("dc", code); time.sleep(0.01); s, _ = caps("acq 4 0 19 1", 3); res[f"dc_{code}"] = s
    d.dac("sine", 20000, 800, 2048); s, c = caps("acq 10 0 19 1", 3); res["sine_div10"] = s; res["sine_dt_ns"] = c[0].dt_ns
    d.dac("off")
    save("dac", **res)


def t_acqos():
    """Oversampling: noise on a DAC DC level, and on the echoes (pe 1) vs a plain pe — shows the RF aliasing warning."""
    res = {}
    d.dac("dc", 2048); time.sleep(0.01)
    for name, cmd in (("acq", "acq 4 0 19 1"), ("os4", "acqos 4 19"), ("os16", "acqos 16 19")):
        s, c = caps(cmd, 5); res[f"dc_{name}"] = s; res[f"dc_{name}_dt_ns"] = c[0].dt_ns
    d.dac("off")
    d.gain(0, 1, 0)
    for name, cmd in (("pe", "pe"), ("os4", "acqos 4 25 1"), ("os16", "acqos 16 25 1")):
        s, c = caps(cmd, 8); res[f"echo_{name}"] = s; res[f"echo_{name}_dt_ns"] = c[0].dt_ns
    save("acqos", **res)


def t_tof():
    """tof on the first echo (gain x3.2, blank 25 us): threshold sweep, 50 shots each, + pe captures for a host reference."""
    d.gain(0, 1, 0)
    rows = []
    for thr in (30, 60, 100, 150):
        for _ in range(50):
            t = d.tof(thr, 25000, 25)
            rows.append((thr, t.index if t.found else -1, t.peak_index if t.found else -1, t.peak_lsb or 0, t.ref, int(t.hw_tripped),
                         t.dt_ns))
    ref, c = caps("pe", 30)
    ts = []
    for _ in range(20):
        t0 = time.perf_counter(); d.tof(60, 25000, 25); ts.append(time.perf_counter() - t0)
    save("tof", table=np.array(rows, dtype=float), columns=np.array(["thr", "idx", "peak_idx", "peak", "ref", "hw", "dt_ns"]),
         pe_ref=ref, pe_dt_ns=c[0].dt_ns, tof_time_s=np.array(ts))


def t_env():
    """env on the echoes (gain x3.2): dec 4/8/16/32 x shots 1/4/16, 5 runs each; pe captures for the host check."""
    d.gain(0, 1, 0)
    res = {}
    for dec in (4, 8, 16, 32):
        for shots in (1, 4, 16):
            runs = [d.env(dec, shots, 25) for _ in range(5)]
            res[f"env_d{dec}_s{shots}"] = np.array([e.values for e in runs]); res[f"env_d{dec}_dt_ns"] = runs[0].dt_ns
    s, c = caps("pe", 16); res["pe_ref"] = s; res["pe_dt_ns"] = c[0].dt_ns
    ts = {}
    for shots in (1, 16):
        tt = []
        for _ in range(10):
            t0 = time.perf_counter(); d.env(8, shots, 25); tt.append(time.perf_counter() - t0)
        res[f"time_s{shots}"] = np.array(tt)
    save("env", **res)


def t_tgc():
    """tgc on the echoes: gain 0 0 0 (x10) with and without a step to leg 2 (x61) at 30 us, 16 shots each."""
    d.gain(0, 0, 0)
    res = {}
    d.tgc("off"); res["off"], c = caps("pe", 16); res["dt_ns"] = c[0].dt_ns
    d.tgc((30, 2)); res["step30_leg2"], c = caps("pe", 16)
    d.tgc("off")
    d.gain(2, 0, 0); res["leg2_const"], _ = caps("pe", 16)
    d.gain(0, 0, 0)
    save("tgc", **res)


def t_pc():
    """Period-4 pattern: 40 captures with the correction off and 40 on (no pulse, gain x10), + the PIC's offsets per capture."""
    d.gain(0, 0, 0)
    res = {}
    d.pattern_correction(False); res["raw"], _ = caps("acq 4 0 25 1", 40)
    d.pattern_correction(True)
    cs, offs = [], []
    for _ in range(40):
        c = P.parse_capture(d.exchange("acq 4 0 25 1", timeout=20).lines); cs.append(c.samples)
        offs.append(d.pattern_correction().offsets_lsb)
    res["corrected"] = np.array(cs); res["pic_offsets_lsb"] = np.array(offs, dtype=float)
    save("pc", **res)


TESTS = dict(pe_ref=t_pe_ref, link=t_link, fmt=t_fmt, lock=t_lock, dac=t_dac, acqos=t_acqos, tof=t_tof, env=t_env, tgc=t_tgc,
             pc=t_pc)
sel = sys.argv[1:] or list(TESTS)
failed = []
for name in sel:
    print(f"[{name}] {TESTS[name].__doc__.strip().splitlines()[0]}", flush=True)
    t0 = time.time()
    try:
        TESTS[name]()
    except Exception:
        failed.append(name); traceback.print_exc()
    print(f"  {time.time() - t0:.0f} s", flush=True)
d.gain(0, 0, 0); d.tgc("off"); d.close()
print("failed:", failed or "none")
