# 0012 — RX chain on the devkit: OA1 → OA2 (digipot gain) → FE_A_OUT, and the AD8338 branch

**Status:** current (netlist + bench 2026-11-02, session 08 part 3) · type: project/reference ·
source: `hardware/minUS_10102026/*.kicad_sch` (netlist via `kicad-netlist-reading`), DS70005592 ch. 32,
`pdfs/datasheets/MCP453X-…-DS22096B.md`, commit after e8c8c4e (pic 0.1.21 / rp 0.1.29)

## Wiring (U2 = PIC32AK1216GC41048)
| Stage | Pins / parts | Gain |
| --- | --- | --- |
| OA1 | IN+ = RX node (H4, D7 clamp, bias bug), IN- = R47 1k to GND, OUT = R48 10k feedback = **OA1OUT** (pin 8 = AD1AN0, J5.3/J6.1) | fixed ×11, on at boot (`AMP1`) |
| **OA2** | IN+ (pin 18) = **OA1OUT**; IN- (pin 17, also TMS → `JTAGEN OFF`) = **U11 MCP4531-103 wiper** + **R49 1k** to GND; OUT (pin 16) = **FE_A_OUT** = U11 terminal A, J6.2, RF13 (IPEX); OUT is **AD2AN1 only** (ADC2, no capture yet) | **1 + R_AW/1k**, R_AW = 10k·(128−n)/128 + 75 Ω → ×1.07 (n 128) … ×6.08 (n 64, power-on) … ×11.07 (n 0). Off at boot (`AMP2 0|1`, proto 6) |
| OA3 | IN+ = RF19/RF20 (H2.12), IN- = R51 1k / R52 10k, OUT = H2.14 / RF24 | fixed ×11, unused |
| AD8338 VGA (U10) | gain pin fed through JP6/JP7 from U18 MCP4531 (0x2F) or U14 MCP4131 (SPI) / MCP4728 DAC | the other controlled gain on the board |

I2C0 (RP GPIO0/1, 10k pull-ups): **0x2E U11, 0x2F U18, 0x60 MCP4728 U13** answer; OLED (0x3C) does not.
RP commands `i2c`, `pot <0|1> [n]`; PIC `AMP2 0|1`. Bench: wiper read-back 64 at power-on, set 0/128/64 ok.

## The catch: the digipot caps the OA2 bandwidth at ~1 MHz
MCP4531-103 datasheet: −3 dB bandwidth **1 MHz** (10 kΩ, mid code, 30 pF load), terminal capacitance 75 pF,
wiper capacitance 120 pF. Inside OA2's feedback that is a low-pass well below a 3–5 MHz echo (the gain
falls toward ×1 as the pot's reactance drops). Options: 5 kΩ part (2 MHz, still short), use the pot only to
*set a DC gain-control voltage* (AD8338 style) instead of being the feedback resistor, or fixed R + a
small analog switch. **Hardware TODO.**

## Direction decided 2026-11-02 (session 08 part 4): drop the digipot, switch gain legs with PIC GPIOs
Owner constraint: BOM cost + simple design, core = RP2354 + PIC32AK (AD8338 is too much BOM for the minimal
design). Chosen direction: **fixed Rf on OA2 + 2–3 ground-leg resistors each returned to a PIC GPIO**
(output-low = on, input = off) → ×2 / ×5.5 / ×11 steps, tens of MHz, zero extra parts; the PIC can step them
on a timer during the A-line (stepped TGC). Fallbacks: analog switch (74HC4053/SGM3157) in the leg, JFET VCR
from the PIC DAC, or no analog control + software TGC on the 12-bit ADC. Devkit rework to test: lift U11, 10 k
J6.2–J6.3, 1 k + 2.2 k from J6.3 to H2.1 (RD6) / H2.4 (RD5); firmware `GAIN <mask>` to add. Low-R digipots
(AD5273 1 kΩ ≈ 6 MHz, AD8400 1 kΩ ≈ 5 MHz) and PGAs (MCP6S91 ≤ 18 MHz) were the next-best options.
J6.1 (OA1OUT) has **no IPEX**; only RF5 (OA1IN+), RF13 (OA2OUT) and RF7 (ADC node) do.

## How to measure the OA2 gain (owner, with the DS203)
1. `raw AMP1 0` (OA1 output pin goes Hi-Z) → inject the 1 MHz tone at **J6.1** (OA1OUT net = OA2IN+), ≤ 0.3 V p-p,
   DC between 0.3 and 2.5 V (single supply).
2. `raw AMP2 1`, `pot 0 n` for n = 128 / 64 / 0.
3. Read OA2OUT at **J6.2** or RF13 with the scope, or U.FL-cable **RF13 → RF7** and `acq 4 0 9` (ADC node) — the
   ADC then sees OA2OUT directly (RF7 node: 56 pF + clamp, fine). Expect ×1.07 / ×6.08 / ×11.07 at low
   frequency and the roll-off above ~1 MHz.

## Related
[[0008-devkit-minUS_10102026]] (board), [[0011-adc-dma-throughput]] (capture), `firmware/README.md` command table.
