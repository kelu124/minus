# pdfs/datasheets — component datasheets

Datasheets / app-notes for candidate ICs (esp. pulser options — see
[`../../analysis.md`](../../analysis.md)).

| File | IC / doc | Role |
|------|----------|------|
| `MD1213_pulser-driver.pdf` | Microchip MD1213 | 3-state HV MOSFET driver (single-channel ultrasound pulser driver). |
| `MD1213DB1_pulser_demoboard_MD1213+TC6320.pdf` | MD1213DB1 demoboard | **Reference design**: MD1213 + TC6320 = ±100 V, 2 A single-channel pulser (the un0rick/pic0rick/IUP pulser). |
| `AN-H53_HV-pulser-circuits.pdf` | Microchip AN-H53 | HV pulser circuit app note (MD1210/MD1213). |
| `TUSS4470_AFE.pdf` | TI TUSS4470 | Integrated single-channel AFE (TX H-bridge + LNA + log-amp + envelope), 30 kHz–1 MHz. |

Not mirrored (host blocked download — links):
- **TC6320** (Microchip HV P/N MOSFET pair, ±100 V, 2 A) — covered in MD1213DB1; product page: microchip.com/TC6320.
- **STHV748** (ST quad ±90 V, ±2 A, 3/5-level pulser **with integrated T/R switch**) — st.com/en/switches-and-multiplexers/sthv748s.html.
