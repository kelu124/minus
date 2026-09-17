# pic0rick — design file source

- Upstream: https://github.com/kelu124/pic0rick (branch `main`)
- Commit at retrieval: `fae3e60929c881d0cf5adeedc20b2a19c92fd164`
- Retrieved: 2026-09-17
- License: open hardware (KiCad; see repo `LICENSE.txt`)

Design is modular (KiCad). Three boards mirrored here, each with KiCad source
(`.kicad_sch/.kicad_pcb/.kicad_pro`), schematic PDF, gerbers, and BOM:

| Subfolder | Board | Key parts |
|-----------|-------|-----------|
| `adc/` | AFE + ADC test board | AD8331 VGA/TGC, ADC10065 (65 Msps, 10-bit) |
| `mux/` | 8-channel HV mux PMOD | MAX14866 |
| `panel_adc_pulser_hv/` | **3-in-1 panel: ADC + pulser + HV** | MD1213+TC6320 pulser, ±24 V HV, AFE, ADC |

The `panel_adc_pulser_hv` board is the most relevant single-file reference for a
*minus* front-end (pulser + HV + AFE + ADC on one panel).

The article PDF (`docs/article/pic0rick_full.pdf`) was placed in `../../pdfs/`.
Chip datasheets bundled in the repo (`hardware/adc/datasheets/`: AD8331, adc10065,
pico, PMOD) were not all mirrored — pull individually into `pdfs/` if needed.
Datasheet: `systems/pic0rick/pic0rick.md`.
