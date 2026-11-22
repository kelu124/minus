# minus — Python

Host-side code for the minus board: a library that wraps every RP2354A CLI command, and notebooks that walk
through them with the real bytes on the wire.

| Path | What's there |
|------|--------------|
| [`library/minus/`](library/minus/) | the `minus` package: `Minus` (one method per CLI command), reply parsers, the firmware-sync check |
| [`library/tests/`](library/tests/) | offline tests replaying replies recorded from a real board (`fixtures/board3_transcript.json`) |
| [`notebooks/`](notebooks/) | step-by-step worked examples, executed on a board (outputs kept) |

Written for firmware **rp 1.1.8 / pic 1.1.5, link protocol 14** (`minus.FIRMWARE`). On connect the library reads
both versions and warns if the board runs something else.

## Install

```bash
pip install -e python/library            # pyserial + numpy; add [notebooks] for matplotlib + jupyter
```
(or just `sys.path.insert(0, "python/library")`, as the notebooks do). Linux: your user needs access to
`/dev/ttyACM*` (`dialout` group).

## Use

```python
from minus import Minus
dev = Minus()                      # auto-detects the port; or Minus("/dev/ttyACM0")
print(dev.version().version, dev.pic_ident().version)
dev.gain(2, 0, 0)                  # Rf 6.8k on both stages, x61
a = dev.pe()                       # pulse-echo A-line: a.samples (uint16), a.t_us, a.depth_mm(), a.fs_msps
dev.last.show()                    # the exchange as it went over the wire
```

How a command is framed: the CLI has no prompt, so the library sends `<command>\n#end<k>\n`. The firmware handles
lines in order and answers the sentinel with `unknown '#end<k>' — try help`, so everything before that line is the
reply. Long captures (`pe`, ~0.9 s, 4097 lines) frame the same way as one-liners.

| CLI | Python | returns |
|-----|--------|---------|
| `version` / `raw ID?` | `version()` / `pic_ident()` | `Version` / `PicIdent` |
| `ping`, `auto`/`stop`, `stat`, `reset`, `rdy`, `trig`, `raw TRIG?`, `lb` | `ping()`, `auto_ping(on)`, `stat()`, `reset_pic()`, `rdy()`, `trig()`, `trig_count()`, `loopback()` | |
| `raw <text>` | `raw(text)` | the PIC's reply line |
| `acq [div [samc [in [navg]]]]` | `acq(div, samc, in_, navg)` | `Capture` |
| `pe [hi [lo [in [dead]]]]` | `pe(hi, lo, in_, dead)` | `Capture` (+ `pulse_fired`, `shots`) |
| `acqcpu …`, `acqil …` (experiments) | `acqcpu(...)`, `acqil(...)` | `Capture` |
| `pulse [hi [lo [dead]]]` | `pulse(hi, lo, dead)` | `Pulse` |
| `gain [leg [u1 [u2]]]` | `gain(leg, u1, u2)` | `Gain` |
| `pc [0\|1]` | `pattern_correction(on)` | `PatternCorrection` |
| `rgb R G B [pct]` | `rgb(r, g, b, pct)` (pct = LP5562 brightness %, default 25) | True if the LP5562 acknowledged |
| `i2c`, `pot <0\|1> [n]` | `i2c_scan()`, `pot(i, n)` | `I2CScan`, `Pot` |
| `raw AMP1/AMP2 0\|1`, `raw ADCBB n [ovs]` | `amp1(on)`, `amp2(on)`, `adcbb(n, ovs)` | |
| `pic id/image/flash/verify/erase/pins/mclr/slow/fast/help` | `pic_id()`, `pic_image()`, `pic_flash()`, … | `PicProg`, `PicImage` |
| `link`, `linktest`, `dac …` | `link(mode, mhz)`, `linktest(n, mhz)`, `dac(mode, *values)` | `LinkStatus`, `LinkTest`, `Dac` |
| `acqos <4\|16> [in [pe]]` | `acqos(os, in_, pe)` (oversampling; **not for 3.3 MHz RF**) | `Capture` |
| `tof …`, `env …` | `tof(thr, blank_ns, in_, ref)`, `env(dec, shots, in_)` | `Tof`, `Envelope` |
| `tgc …`, `fmt …` | `tgc((t_us, leg), …)`, `fmt("b64"\|"text")` (b64 is set on connect) | `Tgc`; `Capture.tgc_valid()` masks the switch transients |
| `raw LOCK?` / `RELOCK` | `pic_lock(relock)` | `PicLock` |
| `reboot [dfu]` | `reboot(dfu)` | closes the port |
| anything else | `raw_cli(line)` / `exchange(line)` | reply lines / `Exchange` |

## Live viewer

`minus.live` shows each shot as three panels — the A-line, its envelope (dB) and a scrolling M-mode image — in `pe`
(pulse + RF), `acq`, `env` (envelope computed on the PIC) or `tof` mode:

It needs a Python whose matplotlib has a GUI backend (Qt or Tk) and can import `minus`: run it from `python/library`, or
`pip install -e python/library` once. On this machine the system Python has both (`/usr/bin/python3`); the pyenv 3.11 has
matplotlib with only the non-interactive `agg` backend (no `_tkinter`, no Qt) — the viewer then stops with a message
instead of drawing into nothing; `pip install PyQt5` there fixes it.

```bash
cd python/library
/usr/bin/python3 -m minus.live                       # desktop window (QtAgg/TkAgg picked automatically), pe on input 25
python3 -m minus.live --mode env --dec 8 --shots 4   # PIC envelope, 4 shots averaged per frame
python3 -m minus.live --frames 20 --save live.png --backend Agg   # headless
```

In Jupyter, `LiveView(dev)` is a live object (ipywidgets, no ipympl needed): run / mode / input / gain controls over an
image that updates in place from a background thread (`start()` / `stop()`, or `run(frames=n)` synchronously; ~5 frames/s
because every frame is rendered to PNG). While it runs it owns the serial port. Example: `notebooks/04_live_viewer.ipynb`.

## Keeping the library in sync with the firmware

`python -m minus.fwsync` (run from `python/library`) reads the firmware sources and fails if:
- a CLI command, a `help` usage line, a `pic` sub-command or a PIC link command was added, removed or changed
  without `minus/commands.py` (and the matching method) following;
- `FW_NAME` / version / `PROTO_VERSION` in either `version.h` differ from `minus.FIRMWARE`;
- any firmware source file changed since the library was last checked against it (fingerprint in
  `minus/firmware_sync.json`).

After a firmware change: update `commands.py` / `device.py` / `protocol.py`, flash the board, re-record the test
fixture (`python3 tests/record_fixture.py`), re-run the notebooks, run the tests
(`python3 -m unittest discover -s tests`), then `python3 -m minus.fwsync --update`.

The check runs automatically:
- in Claude Code, after every edit of `firmware/**` or `python/library/minus/**`
  (`.claude/hooks/fwsync-check.sh`);
- on `git commit` when `firmware/` or `python/library/` is staged (`.githooks/pre-commit`; enable per clone with
  `git config core.hooksPath .githooks`). It also runs the offline tests.

## Notebooks

1. [`01_getting_started.ipynb`](notebooks/01_getting_started.ipynb): connect, versions, the wire framing, link tests, LED, errors.
2. [`02_acquisition.ipynb`](notebooks/02_acquisition.ipynb): `acq` and `pe` captures, time/depth axes, gain, pattern correction, averaging.
3. [`03_frontend_and_pic.ipynb`](notebooks/03_frontend_and_pic.ipynb): pulser, I²C, op amps, ADC timing, PIC programmer, reboot;
   SPI payload link and the PIC DAC test signal.
4. [`04_live_viewer.ipynb`](notebooks/04_live_viewer.ipynb): the live A-line / envelope / M-mode view (`LiveView`).

Notebook 02 also covers the ADC extras (`acqos`, `tof`, `env`).

Re-execute them on a board with
`jupyter nbconvert --to notebook --execute --inplace python/notebooks/*.ipynb` (kernel with numpy, pyserial and matplotlib).
