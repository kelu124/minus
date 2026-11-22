"""Live A-scan viewer for a minus board: a desktop window (``python -m minus.live``) and a Jupyter widget (``LiveView``).

Each frame is one shot (``pe`` by default: pulse + 4095 samples at 25 Msps over the SPI link, base64 to the host, ~0.1 s)
shown as three panels:

* the A-line (RF, ADC codes minus the mean) against depth,
* its envelope (host-side Hilbert magnitude, or the PIC's ``env`` values) in dB,
* an M-mode image: the last ``history`` envelopes over time, depth vertical.

Desktop (needs a GUI matplotlib backend; ``--save`` + ``--frames`` work headless)::

    python3 -m minus.live                       # pe on input 25, until the window is closed
    python3 -m minus.live --mode env --dec 8 --shots 4
    python3 -m minus.live --frames 20 --save live.png --backend Agg

Jupyter::

    from minus import Minus
    from minus.live import LiveView
    dev = Minus()
    view = LiveView(dev)           # controls + image; displays itself
    view.start()                   # background thread, the image updates in place
    view.stop()
    view.run(frames=10)            # or: synchronous, N frames (works in nbconvert / nbclient too)

While a view is running it owns the serial port: do not call ``dev`` methods from other cells until ``stop()``.
"""
from __future__ import annotations

import argparse
import io
import threading
import time
from collections import deque
from dataclasses import dataclass, field
from typing import Deque, List, Optional

import numpy as np

from . import protocol as P
from .device import Minus

C_M_S = 1540.0


def hilbert_envelope(y: np.ndarray) -> np.ndarray:
    """|analytic signal| of a real trace (FFT Hilbert transform, numpy only)."""
    n = len(y)
    Y = np.fft.fft(y - y.mean())
    h = np.zeros(n)
    h[0] = 1
    if n % 2 == 0:
        h[n // 2] = 1
        h[1:n // 2] = 2
    else:
        h[1:(n + 1) // 2] = 2
    return np.abs(np.fft.ifft(Y * h))


@dataclass
class Frame:
    """One shot, ready to draw."""
    depth_mm: np.ndarray          # axis of rf / env
    rf: Optional[np.ndarray]      # ADC codes minus the mean (None for mode env)
    env: np.ndarray               # envelope, LSB
    t: float                      # time.time() of the shot
    info: str                     # one-line status
    tof_mm: Optional[float] = None
    raw: object = field(default=None, repr=False)   # the Capture / Envelope / Tof


class LiveSource:
    """Produces frames from a board: mode ``pe`` (pulse + RF), ``acq`` (no pulse), ``env`` (PIC envelope, ``dec``/``shots``)
    or ``tof`` (``pe`` + the PIC's time of flight on top, ``thr``/``blank_ns``)."""

    MODES = ("pe", "acq", "env", "tof")

    def __init__(self, dev: Minus, mode: str = "pe", in_: int = 25, dec: int = 8, shots: int = 1,
                 thr: int = 200, blank_ns: int = 3000):
        if mode not in self.MODES:
            raise ValueError(f"mode is one of {self.MODES}")
        self.dev, self.mode, self.in_, self.dec, self.shots = dev, mode, in_, dec, shots
        self.thr, self.blank_ns = thr, blank_ns

    def grab(self) -> Frame:
        d, now = self.dev, time.time()
        if self.mode == "env":
            e = d.env(self.dec, self.shots, self.in_)
            return Frame(e.depth_mm(C_M_S), None, e.values, now,
                         f"env dec {e.dec} x{e.shots} shots, {e.n} pts, {e.link or ''}", raw=e)
        c = d.acq(4, 0, self.in_, 1) if self.mode == "acq" else d.pe(200, 500, self.in_, 27)
        y = c.samples.astype(float)
        rf = y - y.mean()
        tof_mm = None
        info = f"{self.mode} in {self.in_}: {c.n} samples, {c.dt_ns:.1f} ns, {c.link or ''} {c.xfer_us or ''}us"
        if self.mode == "tof":
            t = d.tof(self.thr, self.blank_ns, self.in_)
            tof_mm = t.depth_mm if t.found else None
            info += f" | tof {('%.1f mm' % tof_mm) if t.found else 'none'} (thr {self.thr})"
        return Frame(c.depth_mm(C_M_S), rf, hilbert_envelope(y), now, info, tof_mm, c)


class LiveFigure:
    """The three-panel matplotlib figure; ``update(frame)`` redraws it."""

    def __init__(self, history: int = 120, mm_points: int = 512, figsize=(10, 6.5)):
        import matplotlib.pyplot as plt
        self.plt = plt
        self.fig, (self.ax_rf, self.ax_env, self.ax_mm) = plt.subplots(3, 1, figsize=figsize,
                                                                         gridspec_kw={"height_ratios": [1, 1, 1.4]})
        self.history, self.mm_points = history, mm_points
        self.cols: Deque[np.ndarray] = deque(maxlen=history)
        self.times: Deque[float] = deque(maxlen=60)
        self.l_rf, = self.ax_rf.plot([], [], lw=0.6)
        self.l_env, = self.ax_env.plot([], [], lw=0.8)
        self.v_tof = self.ax_env.axvline(np.nan, color="r", lw=0.8)
        self.img = None
        self.ax_rf.set_ylabel("RF (codes - mean)")
        self.ax_env.set_ylabel("envelope (dB re 1 LSB)")
        self.ax_mm.set_ylabel("depth (mm)")
        self.ax_mm.set_xlabel("frame (newest right)")
        self.ax_env.set_xlabel("depth (mm, c = 1540 m/s)")
        self.title = self.fig.suptitle("minus live")
        self.fig.tight_layout()

    def update(self, f: Frame) -> None:
        self.times.append(f.t)
        fps = (len(self.times) - 1) / (self.times[-1] - self.times[0]) if len(self.times) > 1 else 0.0
        x = f.depth_mm
        if f.rf is None and not getattr(self, "_rf_note", None):
            self.l_rf.set_data([], [])
            self._rf_note = self.ax_rf.text(0.5, 0.5, "mode env: the A-line stays on the PIC, only its envelope is sent",
                                            ha="center", va="center", transform=self.ax_rf.transAxes, color="gray")
        if f.rf is not None and getattr(self, "_rf_note", None):
            self._rf_note.remove(); self._rf_note = None
        if f.rf is not None:
            self.l_rf.set_data(x, f.rf)
            self.ax_rf.set_xlim(x[0], x[-1])
            lim = max(10.0, float(np.abs(f.rf).max()) * 1.1)
            self.ax_rf.set_ylim(-lim, lim)
        e_db = 20 * np.log10(np.maximum(f.env, 0.5))
        self.l_env.set_data(x, e_db)
        self.ax_env.set_xlim(x[0], x[-1])
        self.ax_env.set_ylim(-10, max(40.0, float(e_db.max()) + 3))
        self.v_tof.set_xdata([f.tof_mm, f.tof_mm] if f.tof_mm is not None else [np.nan, np.nan])
        # M-mode column: envelope resampled to mm_points depths
        col = np.interp(np.linspace(x[0], x[-1], self.mm_points), x, e_db)
        self.cols.append(col)
        mm = np.array(self.cols).T
        if self.img is None or self.img.get_array().shape != mm.shape:
            self.ax_mm.cla()
            self.img = self.ax_mm.imshow(mm, aspect="auto", origin="upper", cmap="gray", vmin=0, vmax=60,
                                         extent=(0, mm.shape[1], x[-1], x[0]))
            self.ax_mm.set_ylabel("depth (mm)")
            self.ax_mm.set_xlabel("frame (newest right)")
        else:
            self.img.set_data(mm)
        lo, hi = np.percentile(mm, 5), np.percentile(mm, 99.5)     # automatic contrast: noise floor -> echoes
        self.img.set_clim(lo, max(hi, lo + 6.0))
        self.title.set_text(f"minus live — {f.info} — {fps:.1f} frames/s")

    def png(self) -> bytes:
        buf = io.BytesIO()
        self.fig.savefig(buf, format="png", dpi=80)
        return buf.getvalue()


class LiveView:
    """Jupyter live view: controls + an image that updates in place (ipywidgets; no ipympl needed)."""

    def __init__(self, dev: Minus, mode: str = "pe", in_: int = 25, display: bool = True, **source_kw):
        import ipywidgets as W
        import matplotlib
        matplotlib.use("Agg", force=False)
        self.dev = dev
        self.src = LiveSource(dev, mode, in_, **source_kw)
        self.figure = LiveFigure()
        self.figure.plt.close(self.figure.fig)          # keep it out of the notebook's own output
        self._stop = threading.Event()
        self._thread: Optional[threading.Thread] = None
        self.frames = 0
        self.error: Optional[str] = None
        self.w_img = W.Image(format="png")
        self.w_mode = W.Dropdown(options=list(LiveSource.MODES), value=mode, description="mode")
        self.w_in = W.Dropdown(options=[("25 RX node", 25), ("17 OA2 out", 17), ("19 DAC", 19), ("0 OA1 out", 0)],
                               value=in_, description="input")
        self.w_gain = W.Dropdown(options=[("leg 0 (x10)", 0), ("leg 1 (x32)", 1), ("leg 2 (x61)", 2), ("leg 3 (x121)", 3)],
                                 value=0, description="gain")
        self.w_run = W.ToggleButton(value=False, description="run", icon="play")
        self.w_status = W.Label("stopped")
        self.w_run.observe(lambda ch: self.start() if ch["new"] else self.stop(), names="value")
        self.w_mode.observe(lambda ch: setattr(self.src, "mode", ch["new"]), names="value")
        self.w_in.observe(lambda ch: setattr(self.src, "in_", ch["new"]), names="value")
        self.w_gain.observe(lambda ch: self._pending_gain.append(ch["new"]), names="value")
        self._pending_gain: List[int] = []
        self.widget = W.VBox([W.HBox([self.w_run, self.w_mode, self.w_in, self.w_gain]), self.w_status, self.w_img])
        if display:
            from IPython.display import display as _display
            _display(self.widget)

    def _ipython_display_(self):
        from IPython.display import display as _display
        _display(self.widget)

    def step(self) -> Frame:
        """One frame: apply a pending gain change, grab, redraw, push the PNG to the widget."""
        while self._pending_gain:
            self.dev.gain(self._pending_gain.pop(0), 0, 0)
        f = self.src.grab()
        self.figure.update(f)
        self.w_img.value = self.figure.png()
        self.frames += 1
        self.w_status.value = f"frame {self.frames}: {f.info}"
        return f

    def run(self, frames: int = 10) -> Frame:
        """Synchronous: grab and draw ``frames`` frames (also works when the notebook is executed headless)."""
        f = None
        for _ in range(frames):
            f = self.step()
        return f

    def _loop(self):
        try:
            while not self._stop.is_set():
                self.step()
        except Exception as e:                           # keep the notebook alive; show what happened
            self.error = f"{type(e).__name__}: {e}"
            self.w_status.value = f"stopped on error: {self.error}"
        finally:
            self.w_run.value = False

    def start(self) -> None:
        if self._thread and self._thread.is_alive():
            return
        self._stop.clear()
        self._thread = threading.Thread(target=self._loop, daemon=True)
        self._thread.start()
        if not self.w_run.value:
            self.w_run.value = True

    def stop(self, timeout: float = 5.0) -> None:
        self._stop.set()
        if self._thread and self._thread is not threading.current_thread():   # stop() can run on the worker (via the
            self._thread.join(timeout)                                          # run toggle in its finally): no self-join
        if self.w_run.value:
            self.w_run.value = False
        if not self.error:
            self.w_status.value = f"stopped after {self.frames} frames"


NON_INTERACTIVE = ("agg", "pdf", "svg", "ps", "cairo", "pgf", "template")


def pick_backend(requested: Optional[str] = None) -> str:
    """The matplotlib backend for the window: ``requested`` if given, else the first of QtAgg / TkAgg / GTK3Agg that loads.
    Returns the backend in use (possibly a non-interactive one when nothing else is installed)."""
    import matplotlib
    if requested:
        matplotlib.use(requested, force=True)
        return matplotlib.get_backend()
    if matplotlib.get_backend().lower() not in NON_INTERACTIVE:
        return matplotlib.get_backend()
    for cand in ("QtAgg", "TkAgg", "GTK3Agg"):
        try:
            matplotlib.use(cand, force=True)
            import matplotlib.pyplot as plt          # noqa: F401  (raises if the toolkit is missing)
            plt.figure(); plt.close("all")
            return matplotlib.get_backend()
        except Exception:
            continue
    matplotlib.use("Agg", force=True)
    return "agg"


def run_window(port: Optional[str] = None, mode: str = "pe", in_: int = 25, frames: Optional[int] = None,
               save: Optional[str] = None, backend: Optional[str] = None, gain: Optional[int] = None, **source_kw) -> int:
    """Desktop loop: draws until the window is closed (or ``frames`` frames); ``save`` writes the last frame as PNG."""
    import sys
    used = pick_backend(backend)
    interactive = used.lower() not in NON_INTERACTIVE
    if not interactive and not save:
        sys.exit("minus.live: no GUI backend for matplotlib in this Python (%s, backend %s): nothing could be shown.\n"
                 "  Use a Python with Tk or Qt, e.g.   /usr/bin/python3 -m minus.live\n"
                 "  or install one here:              pip install PyQt5\n"
                 "  (or run headless:                 --frames 20 --save live.png)" % (sys.executable, used))
    import matplotlib.pyplot as plt
    print(f"minus.live: {mode} on input {in_}, backend {used} — " +
          ("close the window or Ctrl-C to stop" if interactive else f"headless, {frames or 'endless'} frames -> {save}"), flush=True)
    dev = Minus(port)
    try:
        if gain is not None:
            dev.gain(gain, 0, 0)
        src = LiveSource(dev, mode, in_, **source_kw)
        fig = LiveFigure()
        if interactive:
            plt.ion()
            plt.show(block=False)
        n, t_print = 0, time.time()
        while frames is None or n < frames:
            f = src.grab()
            fig.update(f)
            n += 1
            if time.time() - t_print > 2:                # a sign of life in the terminal
                print(f"  frame {n}: {f.info}", flush=True); t_print = time.time()
            if interactive:
                if not plt.fignum_exists(fig.fig.number):
                    break
                fig.fig.canvas.draw_idle()
                plt.pause(0.001)
        if save:
            fig.fig.savefig(save, dpi=100)
        return n
    finally:
        dev.close()


def main(argv=None) -> None:
    ap = argparse.ArgumentParser(prog="python -m minus.live", description="Live A-scan / envelope / M-mode viewer")
    ap.add_argument("--port")
    ap.add_argument("--mode", default="pe", choices=LiveSource.MODES)
    ap.add_argument("--in", dest="in_", type=int, default=25, help="input code (25 RX node, 19 = PIC DAC)")
    ap.add_argument("--gain", type=int, choices=range(4), help="4052 gain leg for both stages")
    ap.add_argument("--dec", type=int, default=8, help="env: samples per value")
    ap.add_argument("--shots", type=int, default=1, help="env: shots averaged per frame")
    ap.add_argument("--thr", type=int, default=200, help="tof: threshold (LSB)")
    ap.add_argument("--blank-ns", type=int, default=3000, help="tof: dead zone after the pulse")
    ap.add_argument("--frames", type=int, help="stop after N frames (default: until the window is closed)")
    ap.add_argument("--save", help="write the last frame as PNG")
    ap.add_argument("--backend", help="matplotlib backend (e.g. Agg for headless, TkAgg, QtAgg)")
    a = ap.parse_args(argv)
    try:
        n = run_window(a.port, a.mode, a.in_, a.frames, a.save, a.backend, a.gain,
                       dec=a.dec, shots=a.shots, thr=a.thr, blank_ns=a.blank_ns)
    except KeyboardInterrupt:
        n = "stopped:"
    print(f"{n} frames" if isinstance(n, int) else "stopped")


if __name__ == "__main__":
    main()
