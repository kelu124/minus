# pdfs — source documents

Papers, datasheets, and reference-design documents backing the survey and the
*minus* design work. Store any PDF you download here (rather than a temp dir), with
a descriptive name.

| File | What it is |
|------|-----------|
| `28-952-1-PB.pdf` | Jonveaux, Schloh, Meng, Arija, Rintoul — *Review of Current Simple Ultrasound Hardware Considerations, Designs, and Processing Opportunities*, Journal of Open Hardware 6(1):3, 2022 (DOI 10.5334/joh.28). Anchor survey → `systems/literature.md`. |
| `ssrn-6946751.pdf` | HZDR — *Integrated Ultrasound Platform (IUP)*, distributed UDV sensor node for DRESDYN (SSRN preprint). → `systems/iup/`. |
| `s41598-020-63529-z.pdf` | Choi et al. — *Versatile Single-Element Ultrasound Imaging Platform using a Water-Proofed MEMS Scanner*, Scientific Reports 10:6544, 2020. → `systems/mems-us/`. |
| `rp2350-datasheet.pdf` | Raspberry Pi RP2350 datasheet (RP2350A/B; on-chip 12-bit SAR ADC = 500 kSps). Context for MCU/ADC choice. |
| `pic0rick_full.pdf` | pic0rick article (full version), from the kelu124/pic0rick repo. → `systems/pic0rick/`; design files in `design/pic0rick/`. |
| `Current_Trends_in_Ultrasound_Wearables_Spotlight_on_System_Architecture_early_access.pdf` | Weik et al., *Current Trends in Ultrasound Wearables: Spotlight on System Architecture*, IEEE Reviews in Biomedical Engineering (early access, 2026). Peer-reviewed basis of the SIG-WUS catalog. |

Component **datasheets** live in [`datasheets/`](datasheets/README.md) (pulser ICs
etc. — see `analysis.md`).

Related: schematics and design files (KiCad/Gerber/PDF schematics) go in
[`../design/<name>/`](../design/), one subfolder per design.
