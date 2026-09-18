MD1213
High-Speed Dual-MOSFET Driver
Features General Description
• 6 ns Rise and Fall Time with 1000 pF Load The MD1213 is a high-speed dual-MOSFET driver. It is
• 2A Peak Output Source and Sink Currents designed to drive high-voltage P-channel and
N-channel MOSFETs for medical ultrasound and other
• 1.8V to 5V Input CMOS Compatible
applications requiring a high-output current for a
• 4.5V to 13V Total Supply Voltage
capacitive load. The high-speed input stage of the
• Smart Logic Threshold MD1213 can operate from 1.8V to 5V logic interface
• Low-Jitter Design with an optimum operating input signal range of 1.8V to
• Two Matched Channels 3.3V. An adaptive threshold circuit is used to set the
level translator switch threshold to the average of the
• Outputs can Swing Below Ground
input logic 0 and logic 1 levels. The input logic levels
• Low-Inductance Package
may be ground referenced even though the driver is
• Thermally Enhanced Package
putting out bipolar signals. The level translator uses a
proprietary circuit, which provides DC coupling
Applications
together with high-speed operation.
• Medical Ultrasound Imaging The output stage of the MD1213 has separate power
• Piezoelectric Transducer Drivers connections enabling the output signal L and H levels
to be chosen independently from the supply voltages
• Non-Destructive Testing
used for the majority of the circuit. As an example, the
• PIN Diode Driver
input logic levels may be 0V and 1.8V, the control logic
• CCD Clock Driver/Buffer may be powered by +5V to –5V, and the output L and
• High-Speed Level Translator H levels may be varied anywhere over the range of –5V
to +5V. The output stage is capable of peak currents of
up to ±2A, depending on the supply voltages used and
load capacitance present.
The OE pin serves a dual purpose. First, its
logic H level is used to compute the threshold voltage
level for the channel input level translators. Second,
when OE is low, the outputs are disabled with the A
output high and the B output low. This assists in
properly pre-charging the AC coupling capacitors that
may be used in series in the gate drive circuit of an
external PMOS and NMOS transistor pair.
Package Type
12-lead QFN
(Top view)
12
1
See Table2-1 for pin information.
 2017 Microchip Technology Inc. DS20005713B-page 1

MD1213
Functional Block Diagram
| VDD1  | VDD2 | VH  |
| ----- | ---- | --- |
Level
OE Shifter
| Level |     | OUTA |
| ----- | --- | ---- |
INA
Shifter
V 2
SS
VL
VH
V 2
DD
| Level |     | OUTB |
| ----- | --- | ---- |
INB
Shifter
SUB
| GND VSS1 | VSS2 | VL  |
| -------- | ---- | --- |
DS20005713B-page 2  2017 Microchip Technology Inc.

MD1213
Typical Application Circuit
+5.0V
|     | VDD1 | VDD2 VH | 0.47µF |     |
| --- | ---- | ------- | ------ | --- |
MD1213
| OE  | Level |     |     |     |
| --- | ----- | --- | --- | --- |
Shifter
|     |     |     | OUTA | +100V |
| --- | --- | --- | ---- | ----- |
INA
Level
|        | Shifter |        |      | 1.0µF         |
| ------ | ------- | ------ | ---- | ------------- |
|        |         |        | 10nF | To            |
| 3. 3V  |         | V 2 VL |      |               |
| CM O S |         | SS     |      | Piezoelectric |
Transducer
| Logic  |     | VH  |     |     |
| ------ | --- | --- | --- | --- |
| Inputs |     | V 2 |     |     |
DD
10nF
-100V
| INB | Level   |     |      |       |
| --- | ------- | --- | ---- | ----- |
|     | Shifter |     | OUTB | 1.0µF |
TC6320
-5.0V
0.47µF
|     | GND VSS1 | VSS2 VL |     |     |
| --- | -------- | ------- | --- | --- |
 2017 Microchip Technology Inc. DS20005713B-page 3

MD1213
1.0 ELECTRICAL CHARACTERISTICS
Absolute Maximum Ratings†
Level Translator Supply Voltage, V –V ...........................................................................................–0.5V to +13.5V
DD SS
Output High Supply Voltage, V .................................................................................................V –0.5V to V + 0.5V
|     |     | H   |     |     | L DD  |
| --- | --- | --- | --- | --- | ----- |
Output Low Supply Voltage, V L  ...................................................................................................V SS –0.5V to V H + 0.5V
Low-Side Supply Voltage, V ................................................................................................................. –7V to + 0.5V
SS
Logic Input Pins ..........................................................................................................................V –0.5V to GND +7V
SS
Maximum Junction Temperature, T .................................................................................................................. +125°C
J
Operating Ambient Temperature, T ..................................................................................................... –40°C to +85°C
A
Storage Temperature, T S  ......................................................................................................................–65°C to +150°C
ESD Rating (Note1) ............................................................................................................................... ESD Sensitive
† Notice: Stresses above those listed under “Absolute Maximum Ratings” may cause permanent damage to the
device. This is a stress rating only, and functional operation of the device at those or any other conditions above those
indicated in the operational sections of this specification is not intended. Exposure to maximum rating conditions for
extended periods may affect device reliability.
Note 1: Device is ESD sensitive. Handling precautions are recommended.
DC ELECTRICAL CHARACTERISTICS
Electrical Specifications: Over operating conditions unless otherwise specified, V  = V 1 = V 2 = 12V,
H DD DD
| V = V 1= V | 2 = 0V, V  = 3.3V, T |  = 25°C.  |           |           |            |
| ---------- | -------------------- | --------- | --------- | --------- | ---------- |
| L  SS      |   SS OE              | A         |           |           |            |
|            | Parameter            | Sym.      | Min. Typ. | Max. Unit | Conditions |
Level Translator
|                |     | V –V  | 4.5 — | 13 V | 2.5V ≤ V  ≤ 13V |
| -------------- | --- | ----- | ----- | ---- | --------------- |
| Supply Voltage |     | DD SS |       |      | DD              |
Level Translator Negative
|                            |     | V      | –5.5 —  | 0 V        |                          |
| -------------------------- | --- | ------ | ------- | ---------- | ------------------------ |
| Supply Voltage             |     | SS     |         |            |                          |
| Output High Supply Voltage |     | V      | V  +2 — | V V        |                          |
|                            |     | H      | SS      | DD         |                          |
| Output Low Supply Voltage  |     | V L    | V SS —  | V DD  –2 V |                          |
| V 1 Quiescent Current      |     | I      | — 0.55  | — mA       |                          |
| DD                         |     | DD1Q   |         |            |                          |
| V 2 Quiescent Current      |     | I      | — —     | 10 µA      | No input transitions     |
| DD                         |     | DD2Q   |         |            |                          |
| V  Quiescent Current       |     | I      | — —     | 10 µA      |                          |
| H                          |     | HQ     |         |            |                          |
| V 1 Average Current        |     | I 1    | — 0.88  | — mA       |                          |
| DD                         |     | DD     |         |            | One channel on at 5 MHz, |
| V DD 2 Average Current     |     | I DD 2 | — 6.6   | — mA       |                          |
no load
| V  Average Current       |     | I   | — 23     | — mA  |                              |
| ------------------------ | --- | --- | -------- | ----- | ---------------------------- |
| H                        |     | H   |          |       |                              |
| Input Logic Voltage High |     | V   | V –0.3 — | 5 V   |                              |
|                          |     | IH  | OE       |       |                              |
| Input logic Voltage Low  |     | V   | 0 —      | 0.3 V |                              |
|                          |     | IL  |          |       | For logic inputs INA and INB |
| Input Logic Current High |     | I   | — —      | 1 µA  |                              |
IH
| Input Logic Current Low     |     | I IL | — —   | 1 µA |     |
| --------------------------- | --- | ---- | ----- | ---- | --- |
| OE Input Logic Voltage High |     | V    | 1.8 — | 5 V  |     |
IH
| OE Input Logic Voltage Low |     | V   | 0 — | 0.3 V |                    |
| -------------------------- | --- | --- | --- | ----- | ------------------ |
|                            |     | IL  |     |       | For logic input OE |
OE Input Logic Impedance
|                         |     | R   | 12 20 | 30 KΩ |            |
| ----------------------- | --- | --- | ----- | ----- | ---------- |
| to GND                  |     | IN  |       |       |            |
| Logic Input Capacitance |     | C   | — 5   | 10 pF | All inputs |
IN
| Output Sink Resistance |     | R    | — — | 12.5 Ω | I  = 50 mA |
| ---------------------- | --- | ---- | --- | ------ | ---------- |
|                        |     | SINK |     |        | SINK       |
Output Source Resistance R SOURCE — — 12.5 Ω I SOURCE  = 50 mA
| Peak Output Sink Current |     | I   | — 2 | — A |     |
| ------------------------ | --- | --- | --- | --- | --- |
SINK
| Peak Output Source Current |     | I   | — 2 | — A |     |
| -------------------------- | --- | --- | --- | --- | --- |
SOURCE
| DS20005713B-page 4 |     |     |     |     |  2017 Microchip Technology Inc. |
| ------------------ | --- | --- | --- | --- | -------------------------------- |

MD1213
AC ELECTRICAL CHARACTERISTICS
Electrical Specifications: V H  = V DD 1 = V DD 2 = 12V, V L  = V SS 1 = V SS 2 = 0V, V OE  = 3.3V, T A  = 25°C.
|     | Parameter | Sym. | Min. | Typ. | Max. | Unit | Conditions |
| --- | --------- | ---- | ---- | ---- | ---- | ---- | ---------- |
Inputs or OE Rise                      Logic input edge speed
|     |     | t   | —   | —   | 10  | ns  |     |
| --- | --- | --- | --- | --- | --- | --- | --- |
irf
| and Fall Time |     |     |     |     |     | requirement |     |
| ------------- | --- | --- | --- | --- | --- | ----------- | --- |
Propagation Delay when
|                            |     | t   | —   | 7   | —   | ns   |                           |
| -------------------------- | --- | --- | --- | --- | --- | ---- | ------------------------- |
|                            |     | PLH |     |     |     | C    |  = 1000 pF, input signal  |
| Output is from Low to High |     |     |     |     |     | LOAD |                           |
rise/fall time of 2 ns (See Tim-
Propagation Delay when
|     |     | t   | —   | 7   | —   | ns ing Diagram and Figure3-1.) |     |
| --- | --- | --- | --- | --- | --- | ------------------------------ | --- |
PHL
Output is from High to Low
Propagation Delay OE
|            |     | t   | —   | 9   | —   | ns   |                           |
| ---------- | --- | --- | --- | --- | --- | ---- | ------------------------- |
|            |     | POE |     |     |     | C    |  = 1000 pF, input signal  |
| to Outputs |     |     |     |     |     | LOAD |                           |
rise/fall time of 2 ns (See Tim-
| Output Rise Time |     | t   | —   | 6   | —   | ns            |     |
| ---------------- | --- | --- | --- | --- | --- | ------------- | --- |
|                  |     | r   |     |     |     | ing Diagram.) |     |
| Output Fall Time |     | t   | —   | 6   | —   | ns            |     |
f
| Rise and Fall Time Matching |     | l t–t l | —   | 1   | —   | ns  |     |
| --------------------------- | --- | ------- | --- | --- | --- | --- | --- |
r f
For each channel
Propagation Low to High and
|                      |     | l t –t l | —   | 1   | —   | ns  |     |
| -------------------- | --- | -------- | --- | --- | --- | --- | --- |
| High-to-low Matching |     | PLH PHL  |     |     |     |     |     |
Propagation Delay Match ∆t — ±2 — ns Device-to-device delay match
dm
TEMPERATURE SPECIFICATIONS
|     | Parameter | Sym. | Min. | Typ. | Max. | Unit | Conditions |
| --- | --------- | ---- | ---- | ---- | ---- | ---- | ---------- |
TEMPERATURE RANGE
| Maximum Junction Temperature  |     | T J | —   | —   | +125 | °C  |     |
| ----------------------------- | --- | --- | --- | --- | ---- | --- | --- |
| Operating Ambient Temperature |     | T   | –40 | —   | +85  | °C  |     |
A
| Storage Temperature |     | T   | –65 | —   | +150 | °C  |     |
| ------------------- | --- | --- | --- | --- | ---- | --- | --- |
S
PACKAGE THERMAL RESISTANCE
| 12-lead QFN |     |    | —   | 47  | —   | °C/W Note1 |     |
| ----------- | --- | --- | --- | --- | --- | ---------- | --- |
JA
| Thermal Resistance to Case       |                                                                           | θ JC | —   | 7   | —   | °C/W |                    |
| -------------------------------- | ------------------------------------------------------------------------- | ---- | --- | --- | --- | ---- | ------------------ |
| Note                             | 1: On an 1 oz. 4-layer 3” x 4” PCB with thermal pad and thermal via array |      |     |     |     |      |                    |
|  2017 Microchip Technology Inc. |                                                                           |      |     |     |     |      | DS20005713B-page 5 |

MD1213
Timing Diagram
3.3V
|     | IN   | 50%  | 50%  |     |     |
| --- | ---- | ---- | ---- | --- | --- |
0V
|     |     | t    |      | t    |     |
| --- | --- | ---- | ---- | ---- | --- |
|     |     | PLH  |      | PHL  |     |
|     |     |      | 90%  | 90%  |     |
OUT
|     |     | 10%  |     | 10%  |     |
| --- | --- | ---- | --- | ---- | --- |
0V
t
t
|     |     |     | r   | f   |     |
| --- | --- | --- | --- | --- | --- |
TABLE 1-1: TRUTH FUNCTION TABLE
Logic Input Output
| OE  | INA |     | INB | OUTA | OUTB |
| --- | --- | --- | --- | ---- | ---- |
| H   | L   |     | L   | V    | V    |
|     |     |     |     | H    | H    |
| H   | L   |     | H   | V H  | V L  |
| H   | H   |     | L   | V L  | V H  |
| H   | H   |     | H   | V    | V    |
|     |     |     |     | L    | L    |
| L   | X   |     | X   | V    | V    |
|     |     |     |     | H    | L    |
DS20005713B-page 6  2017 Microchip Technology Inc.

MD1213
2.0 PIN DESCRIPTION
| The  details  | on  the  pins  | of  MD1213  | are  listed  on |     |
| ------------- | -------------- | ----------- | --------------- | --- |
Table2-1. See Package Type for the location of pins.
| TABLE 2-1: | PIN FUNCTION TABLE  |     |     |             |
| ---------- | ------------------- | --- | --- | ----------- |
| Pin Number | Pin Name            |     |     | Description |
Logic input. Controls OUTA when OE is high. Input logic high will cause the output to
| 1   | INA |     |     |     |
| --- | --- | --- | --- | --- |
swing to VL. Input logic low will cause the output to swing to VH. (See Figure3-2.)
| 2   | VL  | Supply voltage for N-channel output stage |     |     |
| --- | --- | ----------------------------------------- | --- | --- |
Logic input. Controls OUTB when OE is high. Input logic high will cause the output to
| 3   | INB |     |     |     |
| --- | --- | --- | --- | --- |
swing to VL. Input logic low will cause the output to swing to VH. (See Figure3-2.)
| 4   | GND | Logic input ground reference |     |     |
| --- | --- | ---------------------------- | --- | --- |
Low-side analog circuit and level translator supply voltage. VSS1 must be at the lowest
| 5   | VSS1 |     |     |     |
| --- | ---- | --- | --- | --- |
potential of the chip. Thermal Pad and Pin 5 must be connected externally.
6 VSS2 Low-side gate drive supply voltage. VSS2 should be at the same potential as VSS1.
Output driver. Swings from VH to VL. Intended to drive the gate of an external
7 OUTB N-channel MOSFET via a series capacitor. When OE is low, the output is disabled.
OUTB will swing to VL, turning off the external N-channel MOSFET.
| 8   | VH  | Supply voltage for P-channel output stage |     |     |
| --- | --- | ----------------------------------------- | --- | --- |
Output driver. Swings from VH to VL. Intended to drive the gate of an external
9 OUTA P-channel MOSFET via a series capacitor. When OE is low, the output is disabled.
OUTA will swing to VH, turning off the external P-channel MOSFET.
| 10  | VDD2 | High-side gate drive supply voltage |     |     |
| --- | ---- | ----------------------------------- | --- | --- |
High-side analog circuit and level shifter supply voltage. Should be at the same
| 11  | VDD1 |     |     |     |
| --- | ---- | --- | --- | --- |
potential as VDD2.
Output-enable logic input. When OE is high, (V  + V )/2 sets the threshold transi-
OE GND
12 OE tion between logic level high and low for INA and INB. When OE is low, OUTA is at VH
and OUTB is at VL regardless of INA and INB.
|     | Thermal Pad | Index Pad and Thermal Pad are connected internally. |     |     |
| --- | ----------- | --------------------------------------------------- | --- | --- |
 2017 Microchip Technology Inc. DS20005713B-page 7

MD1213
3.0 APPLICATION INFORMATION
| For proper operation of the MD1213, low-inductance |     |         |           |     |              |     |     |     | V vs. V |     |     |     |
| -------------------------------------------------- | --- | ------- | --------- | --- | ------------ | --- | --- | --- | ------- | --- | --- | --- |
|                                                    |     |         |           |     |              |     |     |     | TH      | OE  |     |     |
| bypass  capacitors                                 |     | should  | be  used  | on  | the  various |     |     |     |         |     |     |     |
2.5
supply pins. The GND input pin should be connected to
the digital ground. The INA, INB and OE pins should be
2.0
connected to their logic source with a swing of GND to
logic level 1.8V to 5V. Good PCB layout trace practices
V /2
should  be  followed  corresponding  to  the  desired )stlov( OE
1.5
operating speed. The internal circuitry of the MD1213
is capable of operating up to 100 MHz, with the primary
 HT
| speed limitation being the loading effect of the load |     |     |     |     |     |     | 1.0 |     |     |     |     |     |
| ----------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
V
| capacitance.  | Because  | of  | this  speed  | and  | the  high |     |     |     |     |     |     |     |
| ------------- | -------- | --- | ------------ | ---- | --------- | --- | --- | --- | --- | --- | --- | --- |
0.6V
transient currents due to the capacitive loads, the
0.5
bypass capacitors should be as close to the chip pins
| as  possible.        | Unless  | the   | load     | specifically      | requires |     |     |     |     |     |     |     |
| -------------------- | ------- | ----- | -------- | ----------------- | -------- | --- | --- | --- | --- | --- | --- | --- |
| bipolar drive, the V |         | 1, V  | 2, and V |  pins should have |          |     |     |     |     |     |     |     |
|                      |         | SS SS |          | L                 |          |     | 0   |     |     |     |     |     |
low-inductance feed-through connections to a ground 0            1.0           2.0           3.0          4.0           5.0
| plane. The power connections V |     |     |     | 1 and V | 2 should |     |     |     | V   | (volts) |     |     |
| ------------------------------ | --- | --- | --- | ------- | -------- | --- | --- | --- | --- | ------- | --- | --- |
|                                |     |     | DD  |         | DD       |     |     |     |     |         |     |     |
OE
have a ceramic bypass capacitor to the ground plane
with short leads and decoupling components to prevent
|     |     |     |     |     |     | FIGURE 3-2: |     |     | Logic Input Threshold.  |     |     |     |
| --- | --- | --- | --- | --- | --- | ----------- | --- | --- | ----------------------- | --- | --- | --- |
resonance in the power leads. A common capacitor
and voltage source may be used for these two pins, Pay particular attention to minimizing trace lengths and
| which  should  | always  | have  | the  | same  | applied  DC |        |             |     |               |             |             |     |
| -------------- | ------- | ----- | ---- | ----- | ----------- | ------ | ----------- | --- | ------------- | ----------- | ----------- | --- |
|                |         |       |      |       |             | using  | sufficient  |     | trace  width  | to  reduce  | inductance. |     |
voltage. For applications sensitive to jitter and noise, Surface-mount components are highly recommended.
separate decoupling networks may be used for V 1 Since the output impedance of this driver is very low, in
DD
and V 2. some cases, it may be desirable to add a small series
DD
resistor in series with the output signal to obtain better
|     |     |     |     |     |     | waveform  |     | integrity  | at  the  | load  terminals.  | This  | will |
| --- | --- | --- | --- | --- | --- | --------- | --- | ---------- | -------- | ----------------- | ----- | ---- |
Propagation Delay vs. Logic Voltage reduce the output voltage slew rate at the terminals of
10
a capacitive load.
Focus on parasitic coupling from the driver output to
)sn( yaleD noitagaporP the input signal terminals. This feedback may cause
9.0
oscillations or spurious waveform shapes on the edges
of signal transitions. Since the input operates with
| 8.0 |     |     |     |     |     | signals down to 1.8V, even small coupled voltages may |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | ----------------------------------------------------- | --- | --- | --- | --- | --- | --- |
cause problems. Use of a solid ground plane and good
power and signal layout practices will prevent this
problem. Make sure that the circulating ground return
7.0
|     |     |     |     |     |     | current  | from  | a  capacitive  |     | load  will  | not  react  | with |
| --- | --- | --- | --- | --- | --- | -------- | ----- | -------------- | --- | ----------- | ----------- | ---- |
common inductance and cause noise voltages in the
input logic circuitry.
6.0
1.0              1.5              2.0              2.5              3.0              3.5
Logic Voltage  (V)
| FIGURE 3-1:                |     |  Propagation Delay.  |        |               |     |     |     |     |     |     |     |     |
| -------------------------- | --- | -------------------- | ------ | ------------- | --- | --- | --- | --- | --- | --- | --- | --- |
| The supplied voltages of V |     |                      |  and V | determine the |     |     |     |     |     |     |     |     |
|                            |     |                      | H      | L             |     |     |     |     |     |     |     |     |
output logic levels. These two pins can draw fast
transient currents of up to 2A, so they should be
provided with a suitable bypass capacitor located next
to the chip pins. A ceramic capacitor of up to 1 µF may
be appropriate, with a series ferrite bead to prevent
| resonance  | in  the  | power  | supply  | lead  going  | to  the |     |     |     |     |     |     |     |
| ---------- | -------- | ------ | ------- | ------------ | ------- | --- | --- | --- | --- | --- | --- | --- |
capacitor.
| DS20005713B-page 8 |     |     |     |     |     |     |     |     |  2017 Microchip Technology Inc. |     |     |     |
| ------------------ | --- | --- | --- | --- | --- | --- | --- | --- | -------------------------------- | --- | --- | --- |

MD1213
4.0 PACKAGING INFORMATION
4.1 Package Marking Information
12-lead QFN Example
MMDD
XXXXXXXXXXXX
XXXXXXXXXXXX 11221133KK66
YYYYWWWW 11772211
e3 e3
NNNNNN 116655
Legend: XX...X Product Code or Customer-specific information
Y Year code (last digit of calendar year)
YY Year code (last 2 digits of calendar year)
WW Week code (week of January 1 is week ‘01’)
NNN Alphanumeric traceability code
e3 Pb-free JEDEC® designator for Matte Tin (Sn)
* This package is Pb-free. The Pb-free JEDEC designator ( e 3 )
can be found on the outer packaging for this package.
Note: In the event the full Microchip part number cannot be marked on one line, it will
be carried over to the next line, thus limiting the number of available characters
for product code or customer-specific information. Package may or not include
the corporate logo.
 2017 Microchip Technology Inc. DS20005713B-page 9

MD1213
Note:Forthemostcurrentpackagedrawings,seetheMicrochipPackagingSpecificationatwww.microchip.com/packaging.
DS20005713B-page 10  2017 Microchip Technology Inc.

MD1213
APPENDIX A: REVISION HISTORY
Revision B (June 2017)
The following is the list of modifications:
• Updated the operating ambient temperature in
Absolute Maximum Ratings† and in the
Temperature Specifications table.
• Made minor text changes throughout the
document.
Revision A (April 2017)
• Converted Supertex Doc# DSFP-MD1213 to
Microchip DS20005713B
• Updated the package marking format
• Changed the quantity of the 12-lead QFN K6
package from 3000/Reel to 5000/Reel
• Made minor text changes throughout the
document
 2017 Microchip Technology Inc. DS20005713B-page 11

MD1213
PRODUCT IDENTIFICATION SYSTEM
To order or obtain information, e.g., on pricing or delivery, contact your local Microchip representative or sales office.
Example:
| PART NO. |       XX | -           X            -                  X |
| -------- | -------- | --------------------------------------------- |
Device          Package               Environmental    Media Type
          Options a) MD1213K6-G:     High-Speed Dual-MOSFET Driver
12-lead (4x4) QFN, 5000/Reel
| Device:        | MD1213  | = High-Speed Dual-MOSFET Driver         |
| -------------- | ------- | --------------------------------------- |
| Package:       | K6      | = 12-lead QFN                           |
| Environmental: | G       | = Lead (Pb)-free/RoHS-compliant Package |
| Media Type:    | (blank) | = 5000/Reel for a K6 Package            |
DS20005713B-page 12  2017 Microchip Technology Inc.

Note the following details of the code protection feature on Microchip devices:
• Microchip products meet the specification contained in their particular Microchip Data Sheet.
• Microchip believes that its family of products is one of the most secure families of its kind on the market today, when used in the
intended manner and under normal conditions.
• There are dishonest and possibly illegal methods used to breach the code protection feature. All of these methods, to our
knowledge, require using the Microchip products in a manner outside the operating specifications contained in Microchip’s Data
Sheets. Most likely, the person doing so is engaged in theft of intellectual property.
• Microchip is willing to work with the customer who is concerned about the integrity of their code.
• Neither Microchip nor any other semiconductor manufacturer can guarantee the security of their code. Code protection does not
mean that we are guaranteeing the product as “unbreakable.”
Code protection is constantly evolving. We at Microchip are committed to continuously improving the code protection features of our
products. Attempts to break Microchip’s code protection feature may be a violation of the Digital Millennium Copyright Act. If such acts
allow unauthorized access to your software or other copyrighted work, you may have a right to sue for relief under that Act.
Information contained in this publication regarding device Trademarks
applications and the like is provided only for your convenience
The Microchip name and logo, the Microchip logo, AnyRate, AVR,
and may be superseded by updates. It is your responsibility to AVR logo, AVR Freaks, BeaconThings, BitCloud, CryptoMemory,
ensure that your application meets with your specifications. CryptoRF, dsPIC, FlashFlex, flexPWR, Heldo, JukeBlox, KEELOQ,
MICROCHIP MAKES NO REPRESENTATIONS OR KEELOQ logo, Kleer, LANCheck, LINK MD, maXStylus,
WARRANTIES OF ANY KIND WHETHER EXPRESS OR maXTouch, MediaLB, megaAVR, MOST, MOST logo, MPLAB,
IMPLIED, WRITTEN OR ORAL, STATUTORY OR OptoLyzer, PIC, picoPower, PICSTART, PIC32 logo, Prochip
OTHERWISE, RELATED TO THE INFORMATION, Designer, QTouch, RightTouch, SAM-BA, SpyNIC, SST, SST
INCLUDING BUT NOT LIMITED TO ITS CONDITION, Logo, SuperFlash, tinyAVR, UNI/O, and XMEGA are registered
QUALITY, PERFORMANCE, MERCHANTABILITY OR trademarks of Microchip Technology Incorporated in the U.S.A.
FITNESS FOR PURPOSE. Microchip disclaims all liability and other countries.
arising from this information and its use. Use of Microchip ClockWorks, The Embedded Control Solutions Company,
devices in life support and/or safety applications is entirely at EtherSynch, Hyper Speed Control, HyperLight Load, IntelliMOS,
the buyer’s risk, and the buyer agrees to defend, indemnify and mTouch, Precision Edge, and Quiet-Wire are registered
hold harmless Microchip from any and all damages, claims, trademarks of Microchip Technology Incorporated in the U.S.A.
suits, or expenses resulting from such use. No licenses are Adjacent Key Suppression, AKS, Analog-for-the-Digital Age, Any
conveyed, implicitly or otherwise, under any Microchip Capacitor, AnyIn, AnyOut, BodyCom, chipKIT, chipKIT logo,
intellectual property rights unless otherwise stated. CodeGuard, CryptoAuthentication, CryptoCompanion,
CryptoController, dsPICDEM, dsPICDEM.net, Dynamic Average
Matching, DAM, ECAN, EtherGREEN, In-Circuit Serial
Programming, ICSP, Inter-Chip Connectivity, JitterBlocker,
KleerNet, KleerNet logo, Mindi, MiWi, motorBench, MPASM, MPF,
MPLAB Certified logo, MPLIB, MPLINK, MultiTRAK, NetDetach,
Omniscient Code Generation, PICDEM, PICDEM.net, PICkit,
PICtail, PureSilicon, QMatrix, RightTouch logo, REAL ICE, Ripple
Blocker, SAM-ICE, Serial Quad I/O, SMART-I.S., SQI,
SuperSwitcher, SuperSwitcher II, Total Endurance, TSHARC,
USBCheck, VariSense, ViewSpan, WiperLock, Wireless DNA, and
ZENA are trademarks of Microchip Technology Incorporated in the
U.S.A. and other countries.
SQTP is a service mark of Microchip Technology Incorporated in
Microchip received ISO/TS-16949:2009 certification for its worldwide the U.S.A.
headquarters, design and wafer fabrication facilities in Chandler and
Tempe, Arizona; Gresham, Oregon and design centers in California Silicon Storage Technology is a registered trademark of Microchip
and India. The Company’s quality system processes and procedures Technology Inc. in other countries.
are for its PIC® MCUs and dsPIC® DSCs, KEELOQ® code hopping
devices, Serial EEPROMs, microperipherals, nonvolatile memory and GestIC is a registered trademark of Microchip Technology
analog products. In addition, Microchip’s quality system for the design Germany II GmbH & Co. KG, a subsidiary of Microchip Technology
and manufacture of development systems is ISO 9001:2000 certified.
Inc., in other countries.
All other trademarks mentioned herein are property of their
QUALITY MANAGEMENT SYSTEM respective companies.
© 2017, Microchip Technology Incorporated, All Rights Reserved.
CERTIFIED BY DNV
ISBN: 978-1-5224-1803-0
== ISO/TS 16949 ==
 2017 Microchip Technology Inc. DS20005713B-page 13

Worldwide Sales and Service
| AMERICAS | ASIA/PACIFIC | ASIA/PACIFIC | EUROPE |
| -------- | ------------ | ------------ | ------ |
Corporate Office Asia Pacific Office China - Xiamen Austria - Wels
2355 West Chandler Blvd. Suites 3707-14, 37th Floor Tel: 86-592-2388138  Tel: 43-7242-2244-39
Chandler, AZ 85224-6199 Tower 6, The Gateway Fax: 86-592-2388130 Fax: 43-7242-2244-393
| Tel: 480-792-7200  | Harbour City, Kowloon |                |                      |
| ------------------ | --------------------- | -------------- | -------------------- |
|                    |                       | China - Zhuhai | Denmark - Copenhagen |
Fax: 480-792-7277
|     | Hong Kong | Tel: 86-756-3210040  | Tel: 45-4450-2828  |
| --- | --------- | -------------------- | ------------------ |
Technical Support:
|     | Tel: 852-2943-5100 | Fax: 86-756-3210049 | Fax: 45-4485-2829 |
| --- | ------------------ | ------------------- | ----------------- |
http://www.microchip.com/
|     | Fax: 852-2401-3431 | India - Bangalore | Finland - Espoo |
| --- | ------------------ | ----------------- | --------------- |
support
|     | Australia - Sydney | Tel: 91-80-3090-4444  | Tel: 358-9-4520-820 |
| --- | ------------------ | --------------------- | ------------------- |
Web Address:
|                   | Tel: 61-2-9868-6733 | Fax: 91-80-3090-4123 |                        |
| ----------------- | ------------------- | -------------------- | ---------------------- |
| www.microchip.com |                     |                      | France - Paris         |
|                   | Fax: 61-2-9868-6755 |                      | Tel: 33-1-69-53-63-20  |
India - New Delhi
| Atlanta |     | Tel: 91-11-4160-8631 | Fax: 33-1-69-30-90-79 |
| ------- | --- | -------------------- | --------------------- |
China - Beijing
| Duluth, GA  | Tel: 86-10-8569-7000  | Fax: 91-11-4160-8632 |     |
| ----------- | --------------------- | -------------------- | --- |
France - Saint Cloud
| Tel: 678-957-9614  | Fax: 86-10-8528-2104 |              |                        |
| ------------------ | -------------------- | ------------ | ---------------------- |
|                    |                      | India - Pune | Tel: 33-1-30-60-70-00  |
Fax: 678-957-1455
|     | China - Chengdu | Tel: 91-20-3019-1500 | Germany - Garching |
| --- | --------------- | -------------------- | ------------------ |
Austin, TX
|     | Tel: 86-28-8665-5511 | Japan - Osaka | Tel: 49-8931-9700 |
| --- | -------------------- | ------------- | ----------------- |
Tel: 512-257-3370
|     | Fax: 86-28-8665-7889 | Tel: 81-6-6152-7160  | Germany - Haan |
| --- | -------------------- | -------------------- | -------------- |
Boston China - Chongqing Fax: 81-6-6152-9310 Tel: 49-2129-3766400
Westborough, MA
Tel: 86-23-8980-9588
| Tel: 774-760-0087  |     | Japan - Tokyo | Germany - Heilbronn |
| ------------------ | --- | ------------- | ------------------- |
Fax: 86-23-8980-9500
| Fax: 774-760-0088 |                  | Tel: 81-3-6880- 3770  | Tel: 49-7131-67-3636 |
| ----------------- | ---------------- | --------------------- | -------------------- |
|                   | China - Dongguan | Fax: 81-3-6880-3771   | Germany - Karlsruhe  |
Chicago
|     | Tel: 86-769-8702-9880  | Korea - Daegu | Tel: 49-721-625370 |
| --- | ---------------------- | ------------- | ------------------ |
Itasca, IL
|                    | China - Guangzhou     | Tel: 82-53-744-4301 |                       |
| ------------------ | --------------------- | ------------------- | --------------------- |
| Tel: 630-285-0071  |                       |                     | Germany - Munich      |
|                    | Tel: 86-20-8755-8029  | Fax: 82-53-744-4302 | Tel: 49-89-627-144-0  |
Fax: 630-285-0075
Fax: 49-89-627-144-44
| Dallas             | China - Hangzhou       | Korea - Seoul          |                      |
| ------------------ | ---------------------- | ---------------------- | -------------------- |
|                    | Tel: 86-571-8792-8115  | Tel: 82-2-554-7200     |                      |
| Addison, TX        |                        |                        | Germany - Rosenheim  |
|                    | Fax: 86-571-8792-8116  | Fax: 82-2-558-5932 or  |                      |
| Tel: 972-818-7423  |                        |                        | Tel: 49-8031-354-560 |
82-2-558-5934
| Fax: 972-818-2924 | China - Hong Kong SAR |                         | Israel - Ra’anana   |
| ----------------- | --------------------- | ----------------------- | ------------------- |
|                   | Tel: 852-2943-5100    | Malaysia - Kuala Lumpur | Tel: 972-9-744-7705 |
Detroit
|                   | Fax: 852-2401-3431   | Tel: 60-3-6201-9857 |                      |
| ----------------- | -------------------- | ------------------- | -------------------- |
| Novi, MI          |                      |                     | Italy - Milan        |
|                   | China - Nanjing      | Fax: 60-3-6201-9859 |                      |
| Tel: 248-848-4000 |                      |                     | Tel: 39-0331-742611  |
|                   | Tel: 86-25-8473-2460 | Malaysia - Penang   |                      |
| Houston, TX       |                      |                     | Fax: 39-0331-466781  |
|                   | Fax: 86-25-8473-2470 | Tel: 60-4-227-8870  |                      |
| Tel: 281-894-5983 |                      |                     | Italy - Padova       |
Fax: 60-4-227-4068
|     | China - Qingdao |     | Tel: 39-049-7625286  |
| --- | --------------- | --- | -------------------- |
Indianapolis
| Noblesville, IN  | Tel: 86-532-8502-7355 | Philippines - Manila |     |
| ---------------- | --------------------- | -------------------- | --- |
Netherlands - Drunen
Tel: 317-773-8323 Fax: 86-532-8502-7205 Tel: 63-2-634-9065 Tel: 31-416-690399
Fax: 317-773-5453 China - Shanghai Fax: 63-2-634-9069 Fax: 31-416-690340
| Tel: 317-536-2380 | Tel: 86-21-3326-8000  | Singapore |     |
| ----------------- | --------------------- | --------- | --- |
Norway - Trondheim
|             | Fax: 86-21-3326-8021 | Tel: 65-6334-8870 |                   |
| ----------- | -------------------- | ----------------- | ----------------- |
| Los Angeles |                      |                   | Tel: 47-7289-7561 |
Fax: 65-6334-8850
| Mission Viejo, CA  | China - Shenyang |     | Poland - Warsaw |
| ------------------ | ---------------- | --- | --------------- |
Tel: 86-24-2334-2829
| Tel: 949-462-9523 |                      | Taiwan - Hsin Chu   | Tel: 48-22-3325737  |
| ----------------- | -------------------- | ------------------- | ------------------- |
|                   | Fax: 86-24-2334-2393 | Tel: 886-3-5778-366 |                     |
Fax: 949-462-9608
|                    |                  | Fax: 886-3-5770-955 | Romania - Bucharest |
| ------------------ | ---------------- | ------------------- | ------------------- |
| Tel: 951-273-7800  | China - Shenzhen |                     |                     |
Tel: 40-21-407-87-50
| Raleigh, NC  | Tel: 86-755-8864-2200  | Taiwan - Kaohsiung |     |
| ------------ | ---------------------- | ------------------ | --- |
Tel: 919-844-7510 Fax: 86-755-8203-1760 Tel: 886-7-213-7830 Spain - Madrid
Tel: 34-91-708-08-90
|               | China - Wuhan        | Taiwan - Taipei       |                      |
| ------------- | -------------------- | --------------------- | -------------------- |
| New York, NY  |                      |                       | Fax: 34-91-708-08-91 |
|               | Tel: 86-27-5980-5300 | Tel: 886-2-2508-8600  |                      |
Tel: 631-435-6000
|     | Fax: 86-27-5980-5118 | Fax: 886-2-2508-0102 | Sweden - Gothenberg |
| --- | -------------------- | -------------------- | ------------------- |
San Jose, CA
Tel: 46-31-704-60-40
| Tel: 408-735-9110 | China - Xian | Thailand - Bangkok |     |
| ----------------- | ------------ | ------------------ | --- |
Sweden - Stockholm
| Tel: 408-436-4270 | Tel: 86-29-8833-7252 | Tel: 66-2-694-1351 |     |
| ----------------- | -------------------- | ------------------ | --- |
Tel: 46-8-5090-4654
|     | Fax: 86-29-8833-7256 | Fax: 66-2-694-1350 |     |
| --- | -------------------- | ------------------ | --- |
Canada - Toronto
| Tel: 905-695-1980  |     |     | UK - Wokingham       |
| ------------------ | --- | --- | -------------------- |
| Fax: 905-695-2078  |     |     | Tel: 44-118-921-5800 |
Fax: 44-118-921-5820
| DS20005713B-page 14 |     |     |  2017 Microchip Technology Inc. |
| ------------------- | --- | --- | -------------------------------- |
11/07/16