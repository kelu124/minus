# Licenses

minus is open hardware, open software and open documentation. Each part of the repository has its own license.
The full texts are in [`LICENSES/`](LICENSES/).

| Part | Paths | License | Text |
|---|---|---|---|
| Hardware design | `hardware/` (except `hardware/3dmodels/`, see below) | TAPR Open Hardware License v1.0 | [`LICENSES/TAPR-OHL-1.0.txt`](LICENSES/TAPR-OHL-1.0.txt) |
| Firmware (sources and the built `.uf2` / `.hex` images) | `firmware/` | GNU General Public License v3.0 or later (`GPL-3.0-or-later`) | [`LICENSES/GPL-3.0-or-later.txt`](LICENSES/GPL-3.0-or-later.txt) |
| Python library, notebooks and scripts (bench capture / analysis, rendering) | `python/`, `docs/bench/**/*.py`, `docs/bench/**/*.sh`, `hardware/render_3d.py`, `firmware/rp2354/tools/` | GNU General Public License v3.0 or later (`GPL-3.0-or-later`) | [`LICENSES/GPL-3.0-or-later.txt`](LICENSES/GPL-3.0-or-later.txt) |
| Documentation, datasheet and bench data | `datasheet/`, `docs/`, the Markdown files at the root and in the other folders | Creative Commons Attribution-ShareAlike 4.0 International (`CC-BY-SA-4.0`) | [`LICENSES/CC-BY-SA-4.0.txt`](LICENSES/CC-BY-SA-4.0.txt) |

Copyright © kelu124

The firmware, the Python library and the scripts are free software: you can redistribute them and/or modify them under the terms of the
GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at
your option) any later version. They are distributed in the hope that they will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

## Third-party material

These files are not covered by the table above and keep their own licenses:

- `hardware/3dmodels/EasyEDA/` — 3D component models from EasyEDA / LCSC, vendored only so the renders can be
  reproduced; they remain under their providers' terms.
- `firmware/rp2354/ws2812.pio` is derived from the Raspberry Pi `pico-examples` WS2812 program (BSD-3-Clause,
  Raspberry Pi Ltd).
- The Raspberry Pi Pico SDK (BSD-3-Clause, with TinyUSB under MIT) and Microchip's XC-DSC compiler and
  `PIC32AK-GC_DFP` device pack are not stored in this repository. They are used at build time and keep their own
  licenses; firmware images built from this repository include parts of them (Pico SDK runtime, Microchip
  device startup code).

minus is **not a medical device**. It is intended for research, education and non-destructive testing only.
