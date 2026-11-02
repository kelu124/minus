MCP453X/455X/463X/465X
2
7/8-Bit Single/Dual I C Digital POT with
Volatile Memory
| Features: | Description: |     |     |     |     |     |
| --------- | ------------ | --- | --- | --- | --- | --- |
• Single or Dual Resistor Network Options The MCP45XX and MCP46XX devices offer a wide
range of product offerings using an I2C interface. This
• Potentiometer or Rheostat Configuration Options
• Resistor Network Resolution family  of  devices  support  7-bit  and  8-bit  resistor
- 7-bit: 128 Resistors (129 Steps) networks,  volatile  memory  configurations,  and
- 8-bit: 256 Resistors (257 Steps) Potentiometer and Rheostat pinouts.
• R AB  Resistances Options of:
| - 5k | Package Types (top view)   |     |     |     |     |     |
| ----- | -------------------------- | --- | --- | --- | --- | --- |
- 10k
|     |     | MCP45X1  |     |     | MCP45X2  |     |
| --- | --- | -------- | --- | --- | -------- | --- |
- 50k
|     | Single Potentiometer |     |     |     | Single Rheostat |     |
| --- | -------------------- | --- | --- | --- | --------------- | --- |
- 100k
• Zero-Scale to Full-Scale Wiper Operation HVC / A0 1 8 V DD HVC / A0 1 8 V DD
| • Low Wiper Resistance: 75 (typical) |     | SCL 2  | 7 P0B |     | SCL 2  | 7 A1  |
| ------------------------------------- | --- | ------ | ----- | --- | ------ | ----- |
| • Low Tempco:                         |     | SDA 3  | 6 P0W |     | SDA 3  | 6 P0B |
|                                       |     |        | P0A   |     |        | P0W   |
| - Absolute (Rheostat): 50ppm typical  |     | V SS 4 | 5     |     | V SS 4 | 5     |
| (0°C to 70°C)                         |     | MSOP   |       |     | MSOP   |       |
- Ratiometric (Potentiometer): 15ppm typical
I2C Serial Interface
| •                                   | HVC / A0 | 1     | 8 V DD | HVC / A0 | 1     | 8 V DD |
| ----------------------------------- | -------- | ----- | ------ | -------- | ----- | ------ |
| - 100kHz, 400kHz and 3.4MHz Support |          | SCL 2 | 7 P0B  |          | SCL 2 | 7 A1   |
|                                     |          |       | EP     |          |       | EP     |
| • Serial Protocol Allows:           |          |       | 9      |          |       | 9      |
|                                     |          | SDA 3 | 6 P0W  | SDA      | 3     | 6 P0B  |
- High-Speed Read/Write to Wiper
|     |     | V 4 | 5 P0A |     | V 4 | 5 P0W |
| --- | --- | --- | ----- | --- | --- | ----- |
|     |     | SS  |       |     | SS  |       |
- Increment/Decrement of Wiper
|     |     | DFN 3x3 (MF) * |     |     | DFN 3x3 (MF) * |     |
| --- | --- | -------------- | --- | --- | -------------- | --- |
• Resistor Network Terminal Disconnect Feature
via the Terminal Control (TCON) Register  MCP46X1 Dual Potentiometers
| • Brown-Out Reset Protection (1.5V typical) |     |     |     |     | 0A/CVH |     |
| ------------------------------------------- | --- | --- | --- | --- | ------ | --- |
• Serial Interface Inactive Current (2.5uA typical)
DD
| • High-Voltage Tolerant Digital Inputs: up to 12.5V |     |     |     |     |     | 1A 2A |
| --------------------------------------------------- | --- | --- | --- | --- | --- | ----- |
V
|                                                   |        |       | V        |     | 16151413 |        |
| ------------------------------------------------- | ------ | ----- | -------- | --- | -------- | ------ |
| • Wide Operating Voltage:                         | HVC/A0 | 1     | 14 DD    |     |          |        |
|                                                   |        |       | 13 A1    | SCL | 1        | 12 NC  |
| - 2.7V to 5.5V - Device Characteristics Specified | SCL    | 2     |          |     |          |        |
|                                                   | SDA    | 3     | 12 A2    | SDA | 2        | 11 NC  |
| - 1.8V to 5.5V - Device Operation                 |        |       |          |     | EP       |        |
|                                                   | V      | 4     | 1 1 N C  | V   | 3 17     | 10 P0B |
| • Wide Bandwidth (-3dB) Operation:                |        | S S   |          | SS  |          |        |
|                                                   | P      | 1 B 5 | 1 0 P0 B | V   | 4        | 9 P0W  |
| - 2MHz (typical) for 5.0k Device                 |        |       |          | SS  |          |        |
|                                                   | P1W    | 6     | 9 P0W    |     | 5 6      | 7 8    |
|                                                   | P1A    |       | 8 P0A    |     |          |        |
| • Extended Temperature Range (-40°C to +125°C)    |        | 7     |          |     | B1P W1P  |        |
A1P A0P
TSSOP
QFN-16 4x4 (ML) *
MCP46X2 Dual Rheostat
|     | HVC/A0 | 1     | 10 V    | HVC / A0 | 1     | 10V   |
| --- | ------ | ----- | ------- | -------- | ----- | ----- |
|     |        |       | DD      |          |       | DD    |
|     | SCL    | 2     | 9 A1    |          | SCL 2 | 9 A1  |
|     | SDA    | 3     | 8 P0B   |          |       | EP    |
|     |        |       |         | SDA      | 3     | 8 P0B |
|     | V      | S S 4 | 7 P 0 W |          |       | 11    |
|     |        |       | P 1 W   |          | V 4   | 7 P0W |
|     | P      | 1 B 5 | 6       |          | SS    |       |
|     |        |       |         |          | P1B 5 | 6 P1W |
MSOP
DFN 3x3 (MF) *
* Includes Exposed Thermal Pad (EP); see Table3-1.
|  2008-2013 Microchip Technology Inc. |     |     |     |     | DS22096B-page 1 |     |
| ------------------------------------- | --- | --- | --- | --- | --------------- | --- |

MCP453X/455X/463X/465X
Device Block Diagram
| V   | Power-Up/ |          | P0A  |
| --- | --------- | -------- | ---- |
| DD  |           | Resistor |      |
Brown-Out
| V   |     | Network 0 |     |
| --- | --- | --------- | --- |
SS Control
(Pot 0)
P0W
|     | I2C Serial | Wiper 0  |     |
| --- | ---------- | -------- | --- |
A2
& TCON
A1 Interface
Register
|     | Module & |     | P0B  |
| --- | -------- | --- | ---- |
HVC/A0
Control
SCL  Logic
| SDA           | (WiperLock™  |          | P1A  |
| ------------- | ------------ | -------- | ---- |
| I2C Interface |              | Resistor |      |
Technology)
Network 1
(Pot 1)
P1W
Wiper 1
Memory (16x9)
& TCON
|     | Wiper0 (V) | Register  |     |
| --- | ---------- | --------- | --- |
P1B
Wiper1 (V)
TCON
|     | Reserved | For Dual Resistor Network  |     |
| --- | -------- | -------------------------- | --- |
Devices Only
Device Features
 kcoLrepiW  repiW ROP
| sTOP fo # |  yromeM  |                               | spetS fo # |
| --------- | -------- | ----------------------------- | ---------- |
|           |  lortnoC |  gnitteS Resistance (typical) | V          |
|           | epyT     |                               | DD         |
Wiper
Device Operating
| Configuration |     | Wiper -            |            |
| ------------- | --- | ------------------ | ---------- |
|               |     | R AB  Options (k) | Range  (2) |
R  ()
W
MCP4531 1 Potentiometer(1)  I2C RAM No Mid-Scale 5.0, 10.0, 50.0, 100.0 75 129 1.8V to 5.5V
I2C
MCP4532 1 Rheostat RAM No Mid-Scale 5.0, 10.0, 50.0, 100.0 75 129 1.8V to 5.5V
| Potentiometer(1)  | I2C |     |     |
| ----------------- | --- | --- | --- |
MCP4541 1 EE Yes NV Wiper 5.0, 10.0, 50.0, 100.0 75 129 2.7V to 5.5V
MCP4542 1 Rheostat I2C EE Yes NV Wiper 5.0, 10.0, 50.0, 100.0 75 129 2.7V to 5.5V
MCP4551  1 Potentiometer(1) I2C RAM No Mid-Scale 5.0, 10.0, 50.0, 100.0 75 257 1.8V to 5.5V
MCP4552 1 Rheostat I2C RAM No Mid-Scale 5.0, 10.0, 50.0, 100.0 75 257 1.8V to 5.5V
| Potentiometer(1)  | I2C |     |     |
| ----------------- | --- | --- | --- |
MCP4561 1 EE Yes NV Wiper 5.0, 10.0, 50.0, 100.0 75 257 2.7V to 5.5V
I2C
MCP4562 1 Rheostat EE Yes NV Wiper 5.0, 10.0, 50.0, 100.0 75 257 2.7V to 5.5V
MCP4631 2 Potentiometer(1) I2C RAM No Mid-Scale 5.0, 10.0, 50.0, 100.0 75 129 1.8V to 5.5V
MCP4632  2 Rheostat I2C RAM No Mid-Scale 5.0, 10.0, 50.0, 100.0 75 129 1.8V to 5.5V
MCP4641 2 Potentiometer(1)  I2C EE Yes NV Wiper 5.0, 10.0, 50.0, 100.0 75 129 2.7V to 5.5V
I2C
MCP4642 2 Rheostat EE Yes NV Wiper 5.0, 10.0, 50.0, 100.0 75 129 2.7V to 5.5V
| Potentiometer(1) | I2C |     |     |
| ---------------- | --- | --- | --- |
MCP4651 2 RAM No Mid-Scale 5.0, 10.0, 50.0, 100.0 75 257 1.8V to 5.5V
MCP4652 2 Rheostat I2C RAM No Mid-Scale 5.0, 10.0, 50.0, 100.0 75 257 1.8V to 5.5V
MCP4661 2 Potentiometer(1) I2C EE Yes NV Wiper 5.0, 10.0, 50.0, 100.0 75 257 2.7V to 5.5V
MCP4662 2 Rheostat I2C EE Yes NV Wiper 5.0, 10.0, 50.0, 100.0 75 257 2.7V to 5.5V
Note 1: Floating either terminal (A or B) allows the device to be used as a Rheostat (variable resistor).
2: Analog characteristics only tested from 2.7V to 5.5V unless otherwise noted.
DS22096B-page 2  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
1.0 ELECTRICAL CHARACTERISTICS
Absolute Maximum Ratings †
Voltage on V with respect to V .......................................................................................................... -0.6V to +7.0V
DD SS
Voltage on HVC/A0, A1, A2, SCL, and SDA with respect to V -0.6V to 12.5V
SS .............................................................................
Voltage on all other pins (PxA, PxW, and PxB) with respect to V -0.3V to V + 0.3V
SS............................................................. DD
Input clamp current, I IK (V I < 0, V I > V DD , V I > V PP ON HV pins)...........................................................................±20mA
Output clamp current, I (V < 0 or V > V )...................................................................................................±20mA
OK O O DD
Maximum output current sunk by any Output pin....................................................................................................25mA
Maximum output current sourced by any Output pin..............................................................................................25mA
Maximum current out of V pin...........................................................................................................................100mA
SS
Maximum current into V pin..............................................................................................................................100mA
DD
Maximum current into PXA, PXW & PXB pins......................................................................................................±2.5mA
Storage temperature...............................................................................................................................-65°C to +150°C
Ambient temperature with power applied................................................................................................-40°C to +125°C
Package power dissipation (T = +50°C, T = +150°C)
A J
MSSOP-8.......................................................................................................................................................473mW
MSSOP-8.......................................................................................................................................................473mW
MSSOP-10.....................................................................................................................................................495mW
DFN-8 (3x3)......................................................................................................................................................1.76W
DFN-10 (3x3)....................................................................................................................................................1.87W
TSSOP-14.........................................................................................................................................................1.00W
QFN-16 (4x4)....................................................................................................................................................2.18W
Soldering temperature of leads (10 seconds).......................................................................................................+300°C
ESD protection on all pins 4kV (HBM)
300V (MM)
Maximum Junction Temperature (T ) ...................................................................................................................+150°C
J
† Notice: Stresses above those listed under “Maximum Ratings” may cause permanent damage to the device. This
is a stress rating only and functional operation of the device at those or any other conditions above those indicated in
the operational listings of this specification is not implied. Exposure to maximum rating conditions for extended peri-
ods may affect device reliability.
 2008-2013 Microchip Technology Inc. DS22096B-page 3

MCP453X/455X/463X/465X
AC/DC CHARACTERISTICS
Standard Operating Conditions (unless otherwise specified)
|     |     |     | Operating Temperature |     |     |     | –40°C  T   +125°C (extended)  |     |     |
| --- | --- | --- | --------------------- | --- | --- | --- | ------------------------------- | --- | --- |
A
DC Characteristics All parameters apply across the specified operating ranges unless noted.
V  = +2.7V to 5.5V, 5k, 10k, 50k, 100k devices.
DD
|                 |            |     | Typical specifications represent values for V |     |         |       |     |  = 5.5V, T |  = +25°C. |
| --------------- | ---------- | --- | --------------------------------------------- | --- | ------- | ----- | --- | ---------- | --------- |
|                 |            |     |                                               |     |         |       | DD  |            | A         |
|                 | Parameters | Sym |                                               | Min | Typ Max | Units |     | Conditions |           |
| Supply Voltage  |            | V   |                                               | 2.7 | — 5.5   |       | V   |            |           |
DD
|     |     |     |     | 1.8 | — 2.7 |     | V Serial Interface only.  |     |     |
| --- | --- | --- | --- | --- | ----- | --- | ------------------------- | --- | --- |
HVC pin Voltage Range  V   V   — 12.5V V V    The HVC pin will be at one
|     |     | HV  |     | SS  |      |     | DD      |                        |            |
| --- | --- | --- | --- | --- | ---- | --- | ------- | ---------------------- | ---------- |
|     |     |     |     |     |      |     | 4.5V    | of three input levels  |            |
|     |     |     |     |     |      |     |         | (V , V  or V           | ). (Note6) |
|     |     |     |     | V   | — V  |  +  | V V  <  | IL IH                  | IHH        |
|     |     |     |     | SS  | DD   |     | DD      |                        |            |
|     |     |     |     |     | 8.0V |     | 4.5V    |                        |            |
V  Start Voltage to  V   — — 1.65 V RAM retention voltage (V ) < V
|     | DD  | BOR |     |     |     |     |     |     | RAM BOR |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | ------- |
ensure Wiper Reset
| V   |  Rise Rate to  | V    |     | (Note9) |     | V/ms |     |     |     |
| --- | -------------- | ---- | --- | ------- | --- | ---- | --- | --- | --- |
|     | DD             | DDRR |     |         |     |      |     |     |     |
ensure Power-on Reset
| Delay after device exits  |     | T   |     | —   | 10 20 | µs  |     |     |     |
| ------------------------- | --- | --- | --- | --- | ----- | --- | --- | --- | --- |
BORD
the reset state
| (V              | DD  > V BOR )  |      |     |     |       |     |                           |              |             |
| --------------- | -------------- | ---- | --- | --- | ----- | --- | ------------------------- | ------------ | ----------- |
| Supply Current |                | I DD |     | —   | — 600 | µA  | Serial Interface Active,  |              |             |
| (Note10)        |                |      |     |     |       |     | HVC/A0 = V                | IH  (or V IL | ) (Note11)  |
Write all 0’s to Volatile Wiper 0
|     |     |     |     |     |        |     | V  = 5.5V, F              |  = 3.4MHz  |             |
| --- | --- | --- | --- | --- | ------ | --- | ------------------------- | ---------- | ----------- |
|     |     |     |     |     |        |     | DD                        | SCL        |             |
|     |     |     |     | —   | — 250  | µA  | Serial Interface Active,  |            |             |
|     |     |     |     |     |        |     | HVC/A0 = V                |  (or V     | ) (Note11)  |
IH IL
Write all 0’s to Volatile Wiper 0
|     |     |     |     |     |       |     | V DD  = 5.5V, F                | SCL  = 100kHz  |        |
| --- | --- | --- | --- | --- | ----- | --- | ------------------------------ | -------------- | ------ |
|     |     |     |     | —   | 2.5 5 | µA  | Serial Interface Inactive,     |                |        |
|     |     |     |     |     |       |     | (Stop condition, SCL = SDA = V |                | IH ),  |
Wiper = 0
|      |                                                                              |     |      |             |             |      | V  = 5.5V, HVC/A0 = V |     |     |
| ---- | ---------------------------------------------------------------------------- | --- | ---- | ----------- | ----------- | ---- | --------------------- | --- | --- |
|      |                                                                              |     |      |             |             |      | DD                    |     | IH  |
| Note | 1: Resistance is defined as the resistance between terminal A to terminal B. |     |      |             |             |      |                       |     |     |
|      | 2: INL and DNL are measured at V                                             |     |      | with V      |  = V  and V |  = V | .                     |     |     |
|      |                                                                              |     |      | W           | A DD        | B    | SS                    |     |     |
|      | 3: MCP4XX1 only.                                                             |     |      |             |             |      |                       |     |     |
|      | 4: MCP4XX2 only, includes V                                                  |     | WZSE |  and V WFSE | .           |      |                       |     |     |
5: Resistor terminals A, W and B’s polarity with respect to each other is not restricted.
|     | 6: This specification by design. |     |     |     |     |     |     |     |     |
| --- | -------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
7: Non-linearity is affected by wiper resistance (R ), which changes significantly overvoltage and
W
temperature.
8: The MCP4XX1 is externally connected to match the configurations of the MCP45X2 and MCP46X2, and
then tested.
|     | 9: POR/BOR is not rate dependent.                                          |     |     |     |     |     |     |     |     |
| --- | -------------------------------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
|     | 10: Supply current is independent of current through the resistor network. |     |     |     |     |     |     |     |     |
11: When HVC/A0 = V , the I  current is less due to current into the HVC/A0 pin. See I  specification.
|                 |     | IHH | DD  |     |     |     |                                       |     | PU  |
| --------------- | --- | --- | --- | --- | --- | --- | ------------------------------------- | --- | --- |
| DS22096B-page 4 |     |     |     |     |     |     |  2008-2013 Microchip Technology Inc. |     |     |

MCP453X/455X/463X/465X
AC/DC CHARACTERISTICS (CONTINUED)
Standard Operating Conditions (unless otherwise specified)
|     |     |     | Operating Temperature |     |     |     |     | –40°C  T |   +125°C (extended)  |     |     |
| --- | --- | --- | --------------------- | --- | --- | --- | --- | --------- | --------------------- | --- | --- |
A
DC Characteristics All parameters apply across the specified operating ranges unless noted.
V  = +2.7V to 5.5V, 5k, 10k, 50k, 100k devices.
DD
|                 |            |       | Typical specifications represent values for V |      |      |       |       |                      | DD               |  = 5.5V, T | A  = +25°C. |
| --------------- | ---------- | ----- | --------------------------------------------- | ---- | ---- | ----- | ----- | -------------------- | ---------------- | ---------- | ----------- |
|                 | Parameters | Sym   |                                               | Min  | Typ  | Max   | Units |                      |                  | Conditions |             |
| Resistance      |            | R AB  |                                               | 4.0  | 5    | 6.0   | k    | -502 devices(Note1) |                  |            |             |
| (± 20%)         |            |       |                                               | 8.0  | 10   | 12.0  | k    | -103 devices(Note1) |                  |            |             |
|                 |            |       |                                               | 40.0 | 50   | 60.0  | k    | -503 devices(Note1) |                  |            |             |
|                 |            |       |                                               | 80.0 | 100  | 120.0 | k    | -104 devices(Note1) |                  |            |             |
| Resolution      |            | N     |                                               |      | 257  |       | Taps  | 8-bit                | No Missing Codes |            |             |
|                 |            |       |                                               |      | 129  |       | Taps  | 7-bit                | No Missing Codes |            |             |
| Step Resistance |            | R S   |                                               | —    | R AB | / —   |      | 8-bit                | Note6            |            |             |
(256)
|     |     |     |     | —   | R AB | / — |    | 7-bit | Note6 |     |     |
| --- | --- | --- | --- | --- | ---- | --- | --- | ----- | ----- | --- | --- |
(128)
| Nominal  |     | |R -R | |   | —   | 0.2 | 1.25 | %   | MCP46X1 devices only  |     |     |     |
| -------- | --- | ----- | --- | --- | --- | ---- | --- | --------------------- | --- | --- | --- |
AB0 AB1
| Resistance Match |     | /R  |     |     |     |     |     |     |     |     |     |
| ---------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
AB
|     |     | |R -R |     | —   | 0.25 | 1.5 | %   | MCP46X2 devices only,  |     |     |     |
| --- | --- | ----- | --- | --- | ---- | --- | --- | ---------------------- | --- | --- | --- |
BW0 BW1
|     |     | | /R |     |     |     |     |     | Code = Full-Scale  |     |     |     |
| --- | --- | ---- | --- | --- | --- | --- | --- | ------------------ | --- | --- | --- |
BW
Wiper Resistance  R — 75 160  V  = 5.5 V, I  = 2.0mA, code = 00h
|     |     | W   |     |     |     |     |     | DD  |     | W   |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
(Note3, Note4)
|             |     |           |     | —   | 75  | 300 |       | V DD                  |  = 2.7 V, I | W  = 2.0mA, code = 00h |     |
| ----------- | --- | --------- | --- | --- | --- | --- | ------ | --------------------- | ----------- | ---------------------- | --- |
| Nominal     |     | R AB /T |     | —   | 50  | —   | ppm/°C | T A  = -20°C to +70°C |             |                        |     |
| Resistance  |     |           |     | —   | 100 | —   | ppm/°C | T  = -40°C to +85°C   |             |                        |     |
A
Tempco
|     |     |     |     | —   | 150 | —   | ppm/°C | T  = -40°C to +125°C |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | ------ | -------------------- | --- | --- | --- |
A
Ratiometeric  V /T — 15 — ppm/°C Code = Midscale (80h or 40h)
WB
Tempco
| Resistor Terminal Input  |     | V V V |     | Vss | —   | V   |     | V Note5, Note6 |     |     |     |
| ------------------------ | --- | ----- | --- | --- | --- | --- | --- | -------------- | --- | --- | --- |
|                          |     | A, W, | B   |     |     | DD  |     |                |     |     |     |
Voltage Range
(Terminals A, B and W)
| Note | 1: Resistance is defined as the resistance between terminal A to terminal B. |     |      |        |      |        |      |     |     |     |     |
| ---- | ---------------------------------------------------------------------------- | --- | ---- | ------ | ---- | ------ | ---- | --- | --- | --- | --- |
|      | 2: INL and DNL are measured at V                                             |     |      | with V |  = V |  and V |  = V | .   |     |     |     |
|      |                                                                              |     |      | W      | A    | DD     | B    | SS  |     |     |     |
|      | 3: MCP4XX1 only.                                                             |     |      |        |      |        |      |     |     |     |     |
|      | 4: MCP4XX2 only, includes V                                                  |     |      |  and V |      | .      |      |     |     |     |     |
|      |                                                                              |     | WZSE |        | WFSE |        |      |     |     |     |     |
5: Resistor terminals A, W and B’s polarity with respect to each other is not restricted.
|     | 6: This specification by design. |     |     |     |     |     |     |     |     |     |     |
| --- | -------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
7: Non-linearity is affected by wiper resistance (R ), which changes significantly overvoltage and
W
temperature.
8: The MCP4XX1 is externally connected to match the configurations of the MCP45X2 and MCP46X2, and
then tested.
|     | 9: POR/BOR is not rate dependent.                                          |     |     |     |     |     |     |     |     |     |     |
| --- | -------------------------------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|     | 10: Supply current is independent of current through the resistor network. |     |     |     |     |     |     |     |     |     |     |
11: When HVC/A0 = V , the I  current is less due to current into the HVC/A0 pin. See I  specification.
|                                       |     | IHH | DD  |     |     |     |     |     |     |     | PU              |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --------------- |
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     |     |     |     | DS22096B-page 5 |

MCP453X/455X/463X/465X
AC/DC CHARACTERISTICS (CONTINUED)
Standard Operating Conditions (unless otherwise specified)
|     |     |     | Operating Temperature |     |     |     | –40°C  T |   +125°C (extended)  |     |     |
| --- | --- | --- | --------------------- | --- | --- | --- | --------- | --------------------- | --- | --- |
A
DC Characteristics All parameters apply across the specified operating ranges unless noted.
|     |     |     | V   |  = +2.7V to 5.5V, 5k, 10k, 50k, 100k devices.  |     |     |     |     |     |     |
| --- | --- | --- | --- | -------------------------------------------------- | --- | --- | --- | --- | --- | --- |
DD
|                         |            |     | Typical specifications represent values for V |         |     |       |            | DD  |  = 5.5V, T | A  = +25°C.         |
| ----------------------- | ---------- | --- | --------------------------------------------- | ------- | --- | ----- | ---------- | --- | ---------- | ------------------- |
|                         | Parameters | Sym |                                               | Min Typ | Max | Units |            |     | Conditions |                     |
| Maximum current         |            | I T |                                               | — —     | 2.5 | mA    | Terminal A |     |            | I AW ,              |
| through Terminal (A, W  |            |     |                                               |         |     |       |            |     |            | W = Full-Scale (FS) |
or B)
|     |     |     |     | — — | 2.5 | mA  | Terminal B |     |     | I BW , |
| --- | --- | --- | --- | --- | --- | --- | ---------- | --- | --- | ------ |
Note6
W = Zero Scale (ZS)
|     |     |     |     | — — | 2.5 | mA  | Terminal W |     |     | I AW  or I BW , |
| --- | --- | --- | --- | --- | --- | --- | ---------- | --- | --- | --------------- |
W = FS or ZS
|     |     |     |     | — — | 1.38 | mA  |     |     |     | I AB , V B  = 0V,  |
| --- | --- | --- | --- | --- | ---- | --- | --- | --- | --- | ------------------ |
V  = 5.5V,
A
|     |     |     |     |     |     |     |     |     |     | R  = 4000 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --------- |
AB(MIN)
|     |     |     |     | — — | 0.688 | mA  |     |     |     | I , V  = 0V,  |
| --- | --- | --- | --- | --- | ----- | --- | --- | --- | --- | ------------- |
|     |     |     |     |     |       |     |     |     |     | AB B          |
V  = 5.5V,
A
|     |     |     |     |     |     |     |     | Terminal A  |     | R  = 8000 |
| --- | --- | --- | --- | --- | --- | --- | --- | ----------- | --- | --------- |
AB(MIN)
and
|     |     |     |     | — — | 0.138 | mA  |     |            |     | I , V  = 0V,  |
| --- | --- | --- | --- | --- | ----- | --- | --- | ---------- | --- | ------------- |
|     |     |     |     |     |       |     |     | Terminal B |     | AB B          |
V  = 5.5V,
A
|     |     |     |     |     |       |     |     |     |     | R AB(MIN)  = 40000 |
| --- | --- | --- | --- | --- | ----- | --- | --- | --- | --- | ------------------ |
|     |     |     |     | — — | 0.069 | mA  |     |     |     | I , V  = 0V,       |
|     |     |     |     |     |       |     |     |     |     | AB B               |
V A  = 5.5V,
|     |     |     |     |     |     |     |     |     |     | R  = 80000 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---------- |
AB(MIN)
Leakage current into A,  I WL — 100 — nA MCP4XX1 PxA = PxW = PxB = V SS
W or B
|     |     |     |     | — 100 | —   | nA  | MCP4XX2 PxB = PxW = V   |     |     | SS   |
| --- | --- | --- | --- | ----- | --- | --- | ----------------------- | --- | --- | ---- |
|     |     |     |     | — 100 | —   | nA  | Terminals Disconnected  |     |     |      |
(R1HW = R0HW = 0)
| Note | 1: Resistance is defined as the resistance between terminal A to terminal B. |     |      |        |             |      |     |     |     |     |
| ---- | ---------------------------------------------------------------------------- | --- | ---- | ------ | ----------- | ---- | --- | --- | --- | --- |
|      | 2: INL and DNL are measured at V                                             |     |      | with V |  = V  and V |  = V | .   |     |     |     |
|      |                                                                              |     |      | W  A   | DD          | B    | SS  |     |     |     |
|      | 3: MCP4XX1 only.                                                             |     |      |        |             |      |     |     |     |     |
|      | 4: MCP4XX2 only, includes V                                                  |     |      |  and V | .           |      |     |     |     |     |
|      |                                                                              |     | WZSE | WFSE   |             |      |     |     |     |     |
5: Resistor terminals A, W and B’s polarity with respect to each other is not restricted.
|     | 6: This specification by design. |     |     |     |     |     |     |     |     |     |
| --- | -------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
7: Non-linearity is affected by wiper resistance (R ), which changes significantly overvoltage and
W
temperature.
8: The MCP4XX1 is externally connected to match the configurations of the MCP45X2 and MCP46X2, and
then tested.
|     | 9: POR/BOR is not rate dependent.                                          |     |     |     |     |     |     |     |     |     |
| --- | -------------------------------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|     | 10: Supply current is independent of current through the resistor network. |     |     |     |     |     |     |     |     |     |
11: When HVC/A0 = V , the I  current is less due to current into the HVC/A0 pin. See I  specification.
|                 |     | IHH | DD  |     |     |     |     |                                       |     | PU  |
| --------------- | --- | --- | --- | --- | --- | --- | --- | ------------------------------------- | --- | --- |
| DS22096B-page 6 |     |     |     |     |     |     |     |  2008-2013 Microchip Technology Inc. |     |     |

MCP453X/455X/463X/465X
AC/DC CHARACTERISTICS (CONTINUED)
Standard Operating Conditions (unless otherwise specified)
|     |     | Operating Temperature |     |     |     | –40°C  T |   +125°C (extended)  |     |     |     |
| --- | --- | --------------------- | --- | --- | --- | --------- | --------------------- | --- | --- | --- |
A
DC Characteristics All parameters apply across the specified operating ranges unless noted.
|     |     | V   |  = +2.7V to 5.5V, 5k, 10k, 50k, 100k devices.  |     |     |     |     |     |     |     |
| --- | --- | --- | -------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- |
DD
|            |     | Typical specifications represent values for V |         |     |       |     | DD  |  = 5.5V, T | A  = +25°C. |     |
| ---------- | --- | --------------------------------------------- | ------- | --- | ----- | --- | --- | ---------- | ----------- | --- |
| Parameters | Sym |                                               | Min Typ | Max | Units |     |     | Conditions |             |     |
Full-Scale Error  V WFSE -6.0 -0.1 — LSb 5k  8-bit  3.0V  V DD   5.5V
| (MCP4XX1 only) |     |     | -4.0 -0.1 | —   | LSb |     | 7-bit  |     | 3.0V  V |   5.5V |
| -------------- | --- | --- | --------- | --- | --- | --- | ------ | --- | -------- | ------- |
DD
(8-bit code = 100h,
|                   |     |     | -3.5 -0.1 | —   | LSb | 10k  | 8-bit  |     | 3.0V  V |   5.5V |
| ----------------- | --- | --- | --------- | --- | --- | ----- | ------ | --- | -------- | ------- |
| 7-bit code = 80h) |     |     |           |     |     |       |        |     |          | DD      |
|                   |     |     | -2.0 -0.1 | —   | LSb |       | 7-bit  |     | 3.0V  V |   5.5V |
DD
|     |     |     | -0.8 -0.1 | —   | LSb | 50k  | 8-bit  |     | 3.0V  V |   5.5V |
| --- | --- | --- | --------- | --- | --- | ----- | ------ | --- | -------- | ------- |
DD
|     |     |     | -0.5 -0.1 | —   | LSb |     | 7-bit  |     | 3.0V  V |   5.5V |
| --- | --- | --- | --------- | --- | --- | --- | ------ | --- | -------- | ------- |
DD
|     |     |     | -0.5 -0.1 | —   | LSb | 100k  | 8-bit  |     | 3.0V  V | DD   5.5V |
| --- | --- | --- | --------- | --- | --- | ------ | ------ | --- | -------- | ---------- |
|     |     |     | -0.5 -0.1 | —   | LSb |        | 7-bit  |     | 3.0V  V | DD   5.5V |
Zero-Scale Error  V — +0.1 +6.0 LSb 5k  8-bit  3.0V  V   5.5V
|                | WZSE |     |        |      |     |     |        |     |          | DD      |
| -------------- | ---- | --- | ------ | ---- | --- | --- | ------ | --- | -------- | ------- |
| (MCP4XX1 only) |      |     | — +0.1 | +3.0 | LSb |     | 7-bit  |     | 3.0V  V |   5.5V |
DD
(8-bit code = 00h,
|                   |     |     | — +0.1 | +3.5 | LSb | 10k  | 8-bit  |     | 3.0V  V |   5.5V |
| ----------------- | --- | --- | ------ | ---- | --- | ----- | ------ | --- | -------- | ------- |
| 7-bit code = 00h) |     |     |        |      |     |       |        |     |          | DD      |
|                   |     |     | — +0.1 | +2.0 | LSb |       | 7-bit  |     | 3.0V  V |   5.5V |
DD
|     |     |     | — +0.1 | +0.8 | LSb | 50k  | 8-bit  |     | 3.0V  V |   5.5V |
| --- | --- | --- | ------ | ---- | --- | ----- | ------ | --- | -------- | ------- |
DD
|     |     |     | — +0.1 | +0.5 | LSb |        | 7-bit  |     | 3.0V  V | DD   5.5V |
| --- | --- | --- | ------ | ---- | --- | ------ | ------ | --- | -------- | ---------- |
|     |     |     | — +0.1 | +0.5 | LSb | 100k  | 8-bit  |     | 3.0V  V |   5.5V    |
DD
|     |     |     | — +0.1 | +0.5 | LSb |     | 7-bit  |     | 3.0V  V |   5.5V |
| --- | --- | --- | ------ | ---- | --- | --- | ------ | --- | -------- | ------- |
DD
Potentiometer Integral  INL -1 ±0.5 +1 LSb 8-bit  3.0V  V   5.5V
DD
| Non-linearity |     |     |            |      |     |        | MCP4XX1 devices only (Note2) |     |     |     |
| ------------- | --- | --- | ---------- | ---- | --- | ------ | ---------------------------- | --- | --- | --- |
|               |     |     | -0.5 ±0.25 | +0.5 | LSb | 7-bit  |                              |     |     |     |
Potentiometer  DNL -0.5 ±0.25 +0.5 LSb 8-bit  3.0V  V   5.5V
DD
| Differential Non-linearity |     |     |              |       |     |        | MCP4XX1 devices only (Note2) |     |     |     |
| -------------------------- | --- | --- | ------------ | ----- | --- | ------ | ---------------------------- | --- | --- | --- |
|                            |     |     | -0.25 ±0.125 | +0.25 | LSb | 7-bit  |                              |     |     |     |
Note 1: Resistance is defined as the resistance between terminal A to terminal B.
| 2: INL and DNL are measured at V |     |     | with V |  = V  and V |  = V | .   |     |     |     |     |
| -------------------------------- | --- | --- | ------ | ----------- | ---- | --- | --- | --- | --- | --- |
|                                  |     |     | W  A   | DD          | B    | SS  |     |     |     |     |
3: MCP4XX1 only.
| 4: MCP4XX2 only, includes V |     |      |  and V | .   |     |     |     |     |     |     |
| --------------------------- | --- | ---- | ------ | --- | --- | --- | --- | --- | --- | --- |
|                             |     | WZSE | WFSE   |     |     |     |     |     |     |     |
5: Resistor terminals A, W and B’s polarity with respect to each other is not restricted.
6: This specification by design.
7: Non-linearity is affected by wiper resistance (R ), which changes significantly overvoltage and
W
temperature.
8: The MCP4XX1 is externally connected to match the configurations of the MCP45X2 and MCP46X2, and
then tested.
9: POR/BOR is not rate dependent.
10: Supply current is independent of current through the resistor network.
11: When HVC/A0 = V , the I  current is less due to current into the HVC/A0 pin. See I  specification.
|                                       | IHH | DD  |     |     |     |     |     |     | PU  |                 |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --------------- |
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     |     |     | DS22096B-page 7 |

MCP453X/455X/463X/465X
AC/DC CHARACTERISTICS (CONTINUED)
Standard Operating Conditions (unless otherwise specified)
|     |     | Operating Temperature |     |     |     | –40°C  T |   +125°C (extended)  |     |     |
| --- | --- | --------------------- | --- | --- | --- | --------- | --------------------- | --- | --- |
A
DC Characteristics All parameters apply across the specified operating ranges unless noted.
|     |     | V   |  = +2.7V to 5.5V, 5k, 10k, 50k, 100k devices.  |     |     |     |     |     |     |
| --- | --- | --- | -------------------------------------------------- | --- | --- | --- | --- | --- | --- |
DD
|                   |     | Typical specifications represent values for V |         |     |       |     | DD    |  = 5.5V, T | A  = +25°C. |
| ----------------- | --- | --------------------------------------------- | ------- | --- | ----- | --- | ----- | ---------- | ----------- |
| Parameters        | Sym |                                               | Min Typ | Max | Units |     |       | Conditions |             |
| Bandwidth -3dB    | BW  |                                               | —       | 2 — | MHz   | 5k | 8-bit |            | Code = 80h  |
| (See Figure2-65,  |     |                                               | —       | 2 — | MHz   |     | 7-bit |            | Code = 40h  |
load = 30pF)
|     |     |     | —     | 1 — | MHz | 10k  | 8-bit |     | Code = 80h  |
| --- | --- | --- | ----- | --- | --- | ----- | ----- | --- | ----------- |
|     |     |     | —     | 1 — | MHz |       | 7-bit |     | Code = 40h  |
|     |     |     | — 200 | —   | kHz | 50k  | 8-bit |     | Code = 80h  |
|     |     |     | — 200 | —   | kHz |       | 7-bit |     | Code = 40h  |
|     |     |     | — 100 | —   | kHz | 100k | 8-bit |     | Code = 80h  |
|     |     |     | — 100 | —   | kHz |       | 7-bit |     | Code = 40h  |
Note 1: Resistance is defined as the resistance between terminal A to terminal B.
| 2: INL and DNL are measured at V |     |     | with V |  = V  and V |  = V | .   |     |     |     |
| -------------------------------- | --- | --- | ------ | ----------- | ---- | --- | --- | --- | --- |
|                                  |     |     | W  A   | DD          | B    | SS  |     |     |     |
3: MCP4XX1 only.
| 4: MCP4XX2 only, includes V |     |      |  and V | .   |     |     |     |     |     |
| --------------------------- | --- | ---- | ------ | --- | --- | --- | --- | --- | --- |
|                             |     | WZSE | WFSE   |     |     |     |     |     |     |
5: Resistor terminals A, W and B’s polarity with respect to each other is not restricted.
6: This specification by design.
7: Non-linearity is affected by wiper resistance (R ), which changes significantly overvoltage and
W
temperature.
8: The MCP4XX1 is externally connected to match the configurations of the MCP45X2 and MCP46X2, and
then tested.
9: POR/BOR is not rate dependent.
10: Supply current is independent of current through the resistor network.
11: When HVC/A0 = V , the I  current is less due to current into the HVC/A0 pin. See I  specification.
|                 | IHH | DD  |     |     |     |     |                                       |     | PU  |
| --------------- | --- | --- | --- | --- | --- | --- | ------------------------------------- | --- | --- |
| DS22096B-page 8 |     |     |     |     |     |     |  2008-2013 Microchip Technology Inc. |     |     |

MCP453X/455X/463X/465X
AC/DC CHARACTERISTICS (CONTINUED)
Standard Operating Conditions (unless otherwise specified)
|     |     |     | Operating Temperature |     |     |     | –40°C  T |   +125°C (extended)  |     |     |
| --- | --- | --- | --------------------- | --- | --- | --- | --------- | --------------------- | --- | --- |
A
DC Characteristics All parameters apply across the specified operating ranges unless noted.
|     |     |     | V   |  = +2.7V to 5.5V, 5k, 10k, 50k, 100k devices.  |     |     |     |     |     |     |
| --- | --- | --- | --- | -------------------------------------------------- | --- | --- | --- | --- | --- | --- |
DD
|     |            |     | Typical specifications represent values for V |     |         |       |     | DD  |  = 5.5V, T | A  = +25°C. |
| --- | ---------- | --- | --------------------------------------------- | --- | ------- | ----- | --- | --- | ---------- | ----------- |
|     | Parameters | Sym |                                               | Min | Typ Max | Units |     |     | Conditions |             |
Rheostat Integral  R-INL -1.5 ±0.5 +1.5 LSb 5k 8-bit 5.5V, I W  = 900µA
| Non-linearity  |     |     |     | -8.25 | +4.5 +8.25 | LSb |     |     |     | 3.0V, I  = 480µA  |
| -------------- | --- | --- | --- | ----- | ---------- | --- | --- | --- | --- | ----------------- |
W
MCP45X1
(Note7)
(Note4, Note8)
|                       |     |     |     | -1.125 | ±0.5 +1.125 | LSb |     | 7-bit |     | 5.5V, I  = 900µA  |
| --------------------- | --- | --- | --- | ------ | ----------- | --- | --- | ----- | --- | ----------------- |
| MCP4XX2 devices only  |     |     |     |        |             |     |     |       |     | W                 |
|                       |     |     |     | -6.0   | +4.5 +6.0   | LSb |     |       |     | 3.0V, I  = 480µA  |
| (Note4)               |     |     |     |        |             |     |     |       |     | W                 |
(Note7)
|     |     |     |     | -1.5 | ±0.5 +1.5 | LSb | 10k | 8-bit |     | 5.5V, I  = 450µA |
| --- | --- | --- | --- | ---- | --------- | --- | ---- | ----- | --- | ---------------- |
W
|     |     |     |     | -5.5 | +2.5 +5.5 | LSb |     |     |     | 3.0V, I  = 240µA  |
| --- | --- | --- | --- | ---- | --------- | --- | --- | --- | --- | ----------------- |
W
(Note7)
|     |     |     |     | -1.125 | ±0.5 +1.125 | LSb |     | 7-bit |     | 5.5V, I  = 450µA |
| --- | --- | --- | --- | ------ | ----------- | --- | --- | ----- | --- | ---------------- |
W
|     |     |     |     | -4.0 | +2.5 +4.0 | LSb |     |     |     | 3.0V, I  = 240µA  |
| --- | --- | --- | --- | ---- | --------- | --- | --- | --- | --- | ----------------- |
W
(Note7)
|     |     |     |     | -1.5 | ±0.5 +1.5 | LSb | 50k | 8-bit |     | 5.5V, I  = 90µA |
| --- | --- | --- | --- | ---- | --------- | --- | ---- | ----- | --- | --------------- |
W
|     |     |     |     | -2.0 | +1 +2.0 | LSb |     |     |     | 3.0V, I  = 48µA  |
| --- | --- | --- | --- | ---- | ------- | --- | --- | --- | --- | ---------------- |
W
(Note7)
|     |     |     |     | -1.125 | ±0.5 +1.125 | LSb |     | 7-bit |     | 5.5V, I  = 90µA |
| --- | --- | --- | --- | ------ | ----------- | --- | --- | ----- | --- | --------------- |
W
|     |     |     |     | -1.5 | +1 +1.5 | LSb |     |     |     | 3.0V, I  = 48µA  |
| --- | --- | --- | --- | ---- | ------- | --- | --- | --- | --- | ---------------- |
W
(Note7)
|     |     |     |     | -1.0 | ±0.5 +1.0 | LSb | 100k | 8-bit |     | 5.5V, I  = 45µA |
| --- | --- | --- | --- | ---- | --------- | --- | ----- | ----- | --- | --------------- |
W
|     |     |     |     | -1.5 | +0.25 +1.5 | LSb |     |     |     | 3.0V, I  = 24µA  |
| --- | --- | --- | --- | ---- | ---------- | --- | --- | --- | --- | ---------------- |
W
(Note7)
|     |     |     |     | -0.8 | ±0.5 +0.8 | LSb |     | 7-bit |     | 5.5V, I  = 45µA |
| --- | --- | --- | --- | ---- | --------- | --- | --- | ----- | --- | --------------- |
W
|     |     |     |     | -1.125 | +0.25 +1.125 | LSb |     |     |     | 3.0V, I W  = 24µA  |
| --- | --- | --- | --- | ------ | ------------ | --- | --- | --- | --- | ------------------ |
(Note7)
| Note | 1: Resistance is defined as the resistance between terminal A to terminal B. |     |      |             |             |      |     |     |     |     |
| ---- | ---------------------------------------------------------------------------- | --- | ---- | ----------- | ----------- | ---- | --- | --- | --- | --- |
|      | 2: INL and DNL are measured at V                                             |     |      | with V      |  = V  and V |  = V | .   |     |     |     |
|      |                                                                              |     |      | W           | A DD        | B    | SS  |     |     |     |
|      | 3: MCP4XX1 only.                                                             |     |      |             |             |      |     |     |     |     |
|      | 4: MCP4XX2 only, includes V                                                  |     | WZSE |  and V WFSE | .           |      |     |     |     |     |
5: Resistor terminals A, W and B’s polarity with respect to each other is not restricted.
|     | 6: This specification by design. |     |     |     |     |     |     |     |     |     |
| --- | -------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
7: Non-linearity is affected by wiper resistance (R ), which changes significantly overvoltage and
W
temperature.
8: The MCP4XX1 is externally connected to match the configurations of the MCP45X2 and MCP46X2, and
then tested.
|     | 9: POR/BOR is not rate dependent.                                          |     |     |     |     |     |     |     |     |     |
| --- | -------------------------------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|     | 10: Supply current is independent of current through the resistor network. |     |     |     |     |     |     |     |     |     |
11: When HVC/A0 = V , the I  current is less due to current into the HVC/A0 pin. See I  specification.
|                                       |     | IHH | DD  |     |     |     |     |     |     | PU              |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --------------- |
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     |     |     | DS22096B-page 9 |

MCP453X/455X/463X/465X
AC/DC CHARACTERISTICS (CONTINUED)
Standard Operating Conditions (unless otherwise specified)
|     |     |     | Operating Temperature |     |     |     | –40°C  T |   +125°C (extended)  |     |     |
| --- | --- | --- | --------------------- | --- | --- | --- | --------- | --------------------- | --- | --- |
A
DC Characteristics All parameters apply across the specified operating ranges unless noted.
|     |     |     | V  = +2.7V to 5.5V, 5k, 10k, 50k, 100k devices.  |     |     |     |     |     |     |     |
| --- | --- | --- | ---------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- |
DD
|            |     |     | Typical specifications represent values for V |     |     |       |     | DD  = 5.5V, T | A  = +25°C. |     |
| ---------- | --- | --- | --------------------------------------------- | --- | --- | ----- | --- | ------------- | ----------- | --- |
| Parameters |     | Sym | Min                                           | Typ | Max | Units |     |               | Conditions  |     |
Rheostat  R-DNL -0.5 ±0.25 +0.5 LSb 5k 8-bit 5.5V, I W  = 900µA
Differential Non-linearity  -1.0 +0.5 +1.0 LSb 3.0V, I  = 480µA
W
MCP45X1
(Note7)
(Note4, Note8)
|                       |     |     | -0.375 | ±0.25 | +0.375 | LSb |     | 7-bit | 5.5V, I |  = 900µA  |
| --------------------- | --- | --- | ------ | ----- | ------ | --- | --- | ----- | ------- | --------- |
| MCP4XX2 devices only  |     |     |        |       |        |     |     |       |         | W         |
|                       |     |     | -0.75  | +0.5  | +0.75  | LSb |     |       | 3.0V, I |  = 480µA  |
| (Note4)               |     |     |        |       |        |     |     |       |         | W         |
(Note7)
|     |     |     | -0.5 | ±0.25 | +0.5 | LSb | 10k | 8-bit | 5.5V, I |  = 450µA |
| --- | --- | --- | ---- | ----- | ---- | --- | ---- | ----- | ------- | -------- |
W
|     |     |     | -1.0 | +0.25 | +1.0 | LSb |     |     | 3.0V, I |  = 240µA  |
| --- | --- | --- | ---- | ----- | ---- | --- | --- | --- | ------- | --------- |
W
(Note7)
|     |     |     | -0.375 | ±0.25 | +0.375 | LSb |     | 7-bit | 5.5V, I |  = 450µA |
| --- | --- | --- | ------ | ----- | ------ | --- | --- | ----- | ------- | -------- |
W
|     |     |     | -0.75 | +0.5 | +0.75 | LSb |     |     | 3.0V, I |  = 240µA  |
| --- | --- | --- | ----- | ---- | ----- | --- | --- | --- | ------- | --------- |
W
(Note7)
|     |     |     | -0.5 | ±0.25 | +0.5 | LSb | 50k | 8-bit | 5.5V, I |  = 90µA |
| --- | --- | --- | ---- | ----- | ---- | --- | ---- | ----- | ------- | ------- |
W
|     |     |     | -0.5 | ±0.25 | +0.5 | LSb |     |     | 3.0V, I |  = 48µA  |
| --- | --- | --- | ---- | ----- | ---- | --- | --- | --- | ------- | -------- |
W
(Note7)
|     |     |     | -0.375 | ±0.25 | +0.375 | LSb |     | 7-bit | 5.5V, I |  = 90µA |
| --- | --- | --- | ------ | ----- | ------ | --- | --- | ----- | ------- | ------- |
W
|     |     |     | -0.375 | ±0.25 | +0.375 | LSb |     |     | 3.0V, I |  = 48µA  |
| --- | --- | --- | ------ | ----- | ------ | --- | --- | --- | ------- | -------- |
W
(Note7)
|     |     |     | -0.5 | ±0.25 | +0.5 | LSb | 100k | 8-bit | 5.5V, I |  = 45µA |
| --- | --- | --- | ---- | ----- | ---- | --- | ----- | ----- | ------- | ------- |
W
|     |     |     | -0.5 | ±0.25 | +0.5 | LSb |     |     | 3.0V, I |  = 24µA  |
| --- | --- | --- | ---- | ----- | ---- | --- | --- | --- | ------- | -------- |
W
(Note7)
|     |     |     | -0.375 | ±0.25 | +0.375 | LSb |     | 7-bit | 5.5V, I |  = 45µA |
| --- | --- | --- | ------ | ----- | ------ | --- | --- | ----- | ------- | ------- |
W
|     |     |     | -0.375 | ±0.25 | +0.375 | LSb |     |     | 3.0V, I | W  = 24µA  |
| --- | --- | --- | ------ | ----- | ------ | --- | --- | --- | ------- | ---------- |
(Note7)
| Capacitance (P | )   | C   | —   | 75  | —   | pF  | f =1MHz, Code = Full-Scale  |     |     |     |
| -------------- | --- | --- | --- | --- | --- | --- | --------------------------- | --- | --- | --- |
|                | A   | AW  |     |     |     |     |                             |     |     |     |
Capacitance (P w ) C W — 120 — pF f =1MHz, Code = Full-Scale
| Capacitance (P                                                                    | )   | C   | —      | 75   | —      | pF   | f =1MHz, Code = Full-Scale  |     |     |     |
| --------------------------------------------------------------------------------- | --- | --- | ------ | ---- | ------ | ---- | --------------------------- | --- | --- | --- |
|                                                                                   | B   | BW  |        |      |        |      |                             |     |     |     |
| Note 1: Resistance is defined as the resistance between terminal A to terminal B. |     |     |        |      |        |      |                             |     |     |     |
| 2: INL and DNL are measured at V                                                  |     |     | with V |  = V |  and V |  = V | .                           |     |     |     |
|                                                                                   |     |     | W      | A    | DD     | B    | SS                          |     |     |     |
| 3: MCP4XX1 only.                                                                  |     |     |        |      |        |      |                             |     |     |     |
| 4: MCP4XX2 only, includes V                                                       |     |     |  and V |      | .      |      |                             |     |     |     |
|                                                                                   |     |     | WZSE   | WFSE |        |      |                             |     |     |     |
5: Resistor terminals A, W and B’s polarity with respect to each other is not restricted.
| 6: This specification by design. |     |     |     |     |     |     |     |     |     |     |
| -------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
7: Non-linearity is affected by wiper resistance (R ), which changes significantly overvoltage and
W
temperature.
8: The MCP4XX1 is externally connected to match the configurations of the MCP45X2 and MCP46X2, and
then tested.
| 9: POR/BOR is not rate dependent.                                          |     |     |     |     |     |     |     |     |     |     |
| -------------------------------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 10: Supply current is independent of current through the resistor network. |     |     |     |     |     |     |     |     |     |     |
11: When HVC/A0 = V IHH , the I DD  current is less due to current into the HVC/A0 pin. See I PU  specification.
| DS22096B-page 10 |     |     |     |     |     |     |     |  2008-2013 Microchip Technology Inc. |     |     |
| ---------------- | --- | --- | --- | --- | --- | --- | --- | ------------------------------------- | --- | --- |

MCP453X/455X/463X/465X
AC/DC CHARACTERISTICS (CONTINUED)
Standard Operating Conditions (unless otherwise specified)
|     |     | Operating Temperature |     |     | –40°C  T |     |   +125°C (extended)  |     |     |     |
| --- | --- | --------------------- | --- | --- | --------- | --- | --------------------- | --- | --- | --- |
A
DC Characteristics All parameters apply across the specified operating ranges unless noted.
|     |     | V  = +2.7V to 5.5V, 5k, 10k, 50k, 100k devices.  |     |     |     |     |     |     |     |     |
| --- | --- | ---------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
DD
|            |     | Typical specifications represent values for V |     |     |       |     | DD  |  = 5.5V, T | A  = +25°C. |     |
| ---------- | --- | --------------------------------------------- | --- | --- | ----- | --- | --- | ---------- | ----------- | --- |
| Parameters | Sym | Min                                           | Typ | Max | Units |     |     | Conditions |             |     |
Digital Inputs/Outputs (SDA, SCK, HVC/A0, A1, A2, WP)
Schmitt Trigger High  V IH 0.45V DD — — V All  2.7V  V DD   5.5V
| Input Threshold |     |     |     |     |     | Inputs  | (Allows 2.7V Digital V |     |     |  with  |
| --------------- | --- | --- | --- | --- | --- | ------- | ---------------------- | --- | --- | ------ |
DD
|     |     |     |     |     |     | except  | 5V Analog V |     | )   |     |
| --- | --- | --- | --- | --- | --- | ------- | ----------- | --- | --- | --- |
DD
SDA
|     |     | 0.5V | —   | —   | V   |      | 1.8V  V |     |   2.7V |     |
| --- | --- | ---- | --- | --- | --- | ---- | -------- | --- | ------- | --- |
|     |     | DD   |     |     |     | and  |          |     | DD      |     |
SCL
|     |     | 0.7V | —   | V   | V   |      | 100kHz |     |     |     |
| --- | --- | ---- | --- | --- | --- | ---- | ------ | --- | --- | --- |
|     |     | DD   |     | MAX |     |      |        |     |     |     |
|     |     | 0.7V | —   | V   | V   | SDA  | 400kHz |     |     |     |
|     |     | DD   |     | MAX |     |      |        |     |     |     |
and
|     |     | 0.7V | —   | V   | V   |     | 1.7MHz |     |     |     |
| --- | --- | ---- | --- | --- | --- | --- | ------ | --- | --- | --- |
|     |     | DD   |     | MAX |     | SCL |        |     |     |     |
|     |     | 0.7V | —   | V   | V   |     | 3.4Mhz |     |     |     |
|     |     | DD   |     | MAX |     |     |        |     |     |     |
Schmitt Trigger Low  V — — 0.2V V All inputs except SDA and SCL
|     | IL  |     |     |     | DD  |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
Input Threshold
|     |     | -0.5 | —   | 0.3V | DD V |     | 100kHz |     |     |     |
| --- | --- | ---- | --- | ---- | ---- | --- | ------ | --- | --- | --- |
SDA
|     |     | -0.5 | —   | 0.3V | DD V |     | 400kHz |     |     |     |
| --- | --- | ---- | --- | ---- | ---- | --- | ------ | --- | --- | --- |
and
|     |     | -0.5 | —   | 0.3V | V   |     | 1.7MHz |     |     |     |
| --- | --- | ---- | --- | ---- | --- | --- | ------ | --- | --- | --- |
|     |     |      |     |      | DD  | SCL |        |     |     |     |
|     |     | -0.5 | —   | 0.3V | V   |     | 3.4Mhz |     |     |     |
DD
Hysteresis of Schmitt  V — 0.1V — V All inputs except SDA and SCL
|     | HYS |     |     | D   |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
Trigger Inputs   (Note6)
D
|     |     | N.A. | —   | —   | V   |     |     |     | V  < 2.0V |     |
| --- | --- | ---- | --- | --- | --- | --- | --- | --- | --------- | --- |
DD
100kHz
|     |     | N.A. | —   | —   | V   |     |     |     | V   2.0V |     |
| --- | --- | ---- | --- | --- | --- | --- | --- | --- | --------- | --- |
DD
SDA
|     |     | 0.1V     | —   | —   | V   |      |        |     | V  < 2.0V    |     |
| --- | --- | -------- | --- | --- | --- | ---- | ------ | --- | ------------ | --- |
|     |     | DD       |     |     |     | and  | 400kHz |     | DD           |     |
|     |     | 0.05V DD | —   | —   | V   |      |        |     | V DD   2.0V |     |
SCL
|     |     | 0.1V DD | —   | —   | V   |     | 1.7MHz |     |     |     |
| --- | --- | ------- | --- | --- | --- | --- | ------ | --- | --- | --- |
|     |     | 0.1V    | —   | —   | V   |     | 3.4Mhz |     |     |     |
DD
High Voltage Limit V — — 12.5 (6)  V Pin can tolerate V  or less.
|     | MAX |     |     |     |     |     |     |     | MAX |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
Note 1: Resistance is defined as the resistance between terminal A to terminal B.
| 2: INL and DNL are measured at V |     | W  with V | A  = V | DD  and V | B  = V | SS  . |     |     |     |     |
| -------------------------------- | --- | --------- | ------ | --------- | ------ | ----- | --- | --- | --- | --- |
3: MCP4XX1 only.
| 4: MCP4XX2 only, includes V |     |  and V |      | .   |     |     |     |     |     |     |
| --------------------------- | --- | ------ | ---- | --- | --- | --- | --- | --- | --- | --- |
|                             |     | WZSE   | WFSE |     |     |     |     |     |     |     |
5: Resistor terminals A, W and B’s polarity with respect to each other is not restricted.
6: This specification by design.
7: Non-linearity is affected by wiper resistance (R W ), which changes significantly overvoltage and
temperature.
8: The MCP4XX1 is externally connected to match the configurations of the MCP45X2 and MCP46X2, and
then tested.
9: POR/BOR is not rate dependent.
10: Supply current is independent of current through the resistor network.
11: When HVC/A0 = V IHH , the I DD  current is less due to current into the HVC/A0 pin. See I PU  specification.
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     |     | DS22096B-page 11 |     |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | ---------------- | --- |

MCP453X/455X/463X/465X
AC/DC CHARACTERISTICS (CONTINUED)
Standard Operating Conditions (unless otherwise specified)
|     |     |     | Operating Temperature |     |     |     | –40°C  T |   +125°C (extended)  |     |     |
| --- | --- | --- | --------------------- | --- | --- | --- | --------- | --------------------- | --- | --- |
A
DC Characteristics All parameters apply across the specified operating ranges unless noted.
V  = +2.7V to 5.5V, 5k, 10k, 50k, 100k devices.
DD
|     |            |     | Typical specifications represent values for V |         |     |       |     | DD  |  = 5.5V, T | A  = +25°C. |
| --- | ---------- | --- | --------------------------------------------- | ------- | --- | ----- | --- | --- | ---------- | ----------- |
|     | Parameters | Sym |                                               | Min Typ | Max | Units |     |     | Conditions |             |
Output Low  V OL   V SS   — 0.2V DD   V V DD  < 2.0V, I OL  = 1mA
| Voltage (SDA)  |     |     |     | V   — | 0.4 |     | V V |   2.0V, I |  = 3mA  |     |
| -------------- | --- | --- | --- | ----- | --- | --- | --- | ---------- | ------- | --- |
|                |     |     |     | SS    |     |     | DD  |            | OL      |     |
Weak Pull-up /  I — — 1.75 mA Internal V  pull-up, V  pull-down
|                   |     | PU  |     |       |     |     |            | DD         |           | IHH    |
| ----------------- | --- | --- | --- | ----- | --- | --- | ---------- | ---------- | --------- | ------ |
| Pull-down Current |     |     |     |       |     |     | V          |  = 5.5V, V |  = 12.5V  |        |
|                   |     |     |     |       |     |     | DD         |            | IHH       |        |
|                   |     |     |     | — 170 | —   | µA  | HVC pin, V |            | = 5.5V, V | = 3V   |
|                   |     |     |     |       |     |     |            |            | DD        | HVC    |
| HVC Pull-up /     |     | R   |     | — 16  | —   | k  | V          | = 5.5V, V  |           |  = 3V  |
|                   |     | HVC |     |       |     |     | DD         |            | HVC       |        |
Pull-down
Resistance
| Input Leakage Current |     | I      |     | -1 — | 1   | µA  | V  = V     |  and V |     |  = V   |
| --------------------- | --- | ------ | --- | ---- | --- | --- | ---------- | ------ | --- | ------ |
|                       |     | IL     |     |      |     |     | IN         | DD     | IN  | SS     |
| Pin Capacitance       |     | C , C  |     | — 10 | —   | pF  | f = 3.4MHz |        |     |        |
|                       |     | IN OUT |     |      |     |     | C          |        |     |        |
RAM (Wiper) Value
| Value Range        |     | N      |     | 0h — | 1FFh | hex | 8-bit device            |     |     |     |
| ------------------ | --- | ------ | --- | ---- | ---- | --- | ----------------------- | --- | --- | --- |
|                    |     |        |     | 0h — | 1FFh | hex | 7-bit device            |     |     |     |
| TCON POR/BOR Value |     | N TCON |     | 1FFh |      | hex | All Terminals connected |     |     |     |
Power Requirements
Power Supply  PSS — 0.0015 0.0035 %/% 8-bit V  = 2.7V to 5.5V,
DD
| Sensitivity  |     |     |     |     |     |     |     | V   |  = 2.7V, Code = 80h |     |
| ------------ | --- | --- | --- | --- | --- | --- | --- | --- | ------------------- | --- |
A
| (MCP45X2 and  |     |     |     | — 0.0015 | 0.0035 | %/% | 7-bit | V   |  = 2.7V to 5.5V,  |     |
| ------------- | --- | --- | --- | -------- | ------ | --- | ----- | --- | ----------------- | --- |
DD
| MCP46X2 only) |     |     |     |     |     |     |     | V   |  = 2.7V, Code = 40h |     |
| ------------- | --- | --- | --- | --- | --- | --- | --- | --- | ------------------- | --- |
A
| Note | 1: Resistance is defined as the resistance between terminal A to terminal B. |     |      |        |             |      |     |     |     |     |
| ---- | ---------------------------------------------------------------------------- | --- | ---- | ------ | ----------- | ---- | --- | --- | --- | --- |
|      | 2: INL and DNL are measured at V                                             |     |      | with V |  = V  and V |  = V | .   |     |     |     |
|      |                                                                              |     |      | W  A   | DD          | B    | SS  |     |     |     |
|      | 3: MCP4XX1 only.                                                             |     |      |        |             |      |     |     |     |     |
|      | 4: MCP4XX2 only, includes V                                                  |     |      |  and V | .           |      |     |     |     |     |
|      |                                                                              |     | WZSE | WFSE   |             |      |     |     |     |     |
5: Resistor terminals A, W and B’s polarity with respect to each other is not restricted.
|     | 6: This specification by design. |     |     |     |     |     |     |     |     |     |
| --- | -------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
7: Non-linearity is affected by wiper resistance (R ), which changes significantly overvoltage and
W
temperature.
8: The MCP4XX1 is externally connected to match the configurations of the MCP45X2 and MCP46X2, and
then tested.
|     | 9: POR/BOR is not rate dependent.                                          |     |     |     |     |     |     |     |     |     |
| --- | -------------------------------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|     | 10: Supply current is independent of current through the resistor network. |     |     |     |     |     |     |     |     |     |
11: When HVC/A0 = V IHH , the I DD  current is less due to current into the HVC/A0 pin. See I PU  specification.

SCL
93
91
|     |     | 90  |     |     |     |     |     | 92  |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
SDA
|     |     | START     |     |     |     |     |     |           | STOP |     |
| --- | --- | --------- | --- | --- | --- | --- | --- | --------- | ---- | --- |
|     |     | Condition |     |     |     |     |     | Condition |      |     |
I2C Bus Start/Stop Bits Timing Waveforms.
FIGURE 1-1:
| DS22096B-page 12 |     |     |     |     |     |     |     |  2008-2013 Microchip Technology Inc. |     |     |
| ---------------- | --- | --- | --- | --- | --- | --- | --- | ------------------------------------- | --- | --- |

MCP453X/455X/463X/465X
| TABLE 1-1: |     | I2C BUS START/STOP BITS REQUIREMENTS       |     |     |     |     |     |     |     |
| ---------- | --- | ------------------------------------------ | --- | --- | --- | --- | --- | --- | --- |
I2C AC Characteristics
Standard Operating Conditions (unless otherwise specified)
|     |     |     |     | Operating Temperature  |     | –40C  TA  +125C (Extended)  |     |     |     |
| --- | --- | --- | --- | ---------------------- | --- | ------------------------------- | --- | --- | --- |
Operating Voltage VDD range is described in AC/DC Characteristics
Param.
|     | Symbol |     | Characteristic |     |     | Min Max | Units |     | Conditions |
| --- | ------ | --- | -------------- | --- | --- | ------- | ----- | --- | ---------- |
No.
|     | F SCL |     |     | Standard Mode |     | 0 100 | kHz | C b  = 400pF, 1.8V - 5.5V |     |
| --- | ----- | --- | --- | ------------- | --- | ----- | --- | ------------------------- | --- |
|     |       |     |     | Fast Mode     |     | 0 400 | kHz | C  = 400pF, 2.7V - 5.5V   |     |
b
|     |     |     |     | High-Speed 1.7 |     | 0 1.7 | MHz | C  = 400pF, 4.5V - 5.5V |     |
| --- | --- | --- | --- | -------------- | --- | ----- | --- | ----------------------- | --- |
b
|     |     |     |     | High-Speed 3.4 |     | 0 3.4 | MHz | C  = 100pF, 4.5V - 5.5V |     |
| --- | --- | --- | --- | -------------- | --- | ----- | --- | ----------------------- | --- |
b
| D102 | C   | Bus capacitive  |     | 100kHz mode |     | —  400 | pF  |     |     |
| ---- | --- | --------------- | --- | ----------- | --- | ------ | --- | --- | --- |
b
loading
|     |     |     |     | 400kHz mode |     | —  400 | pF  |     |     |
| --- | --- | --- | --- | ----------- | --- | ------ | --- | --- | --- |
|     |     |     |     | 1.7MHz mode |     | —  400 | pF  |     |     |
|     |     |     |     | 3.4MHz mode |     | — 100  | pF  |     |     |
90 T START condition  100kHz mode 4700 — ns Only relevant for repeated
SU:STA
|     |     | Setup time |     | 400kHz mode |     | 600 — | ns  | START condition |     |
| --- | --- | ---------- | --- | ----------- | --- | ----- | --- | --------------- | --- |
|     |     |            |     | 1.7MHz mode |     | 160 — | ns  |                 |     |
|     |     |            |     | 3.4MHz mode |     | 160 — | ns  |                 |     |
91 T START condition  100kHz mode 4000 — ns After this period the first
HD:STA
|     |     | Hold time      |     | 400kHz mode |     | 600 —  | ns  | clock pulse is generated |     |
| --- | --- | -------------- | --- | ----------- | --- | ------ | --- | ------------------------ | --- |
|     |     |                |     | 1.7MHz mode |     | 160 —  | ns  |                          |     |
|     |     |                |     | 3.4MHz mode |     | 160 —  | ns  |                          |     |
| 92  | T   | STOP condition |     | 100kHz mode |     | 4000 — | ns  |                          |     |
SU:STO
|     |          | Setup time     |     | 400kHz mode |     | 600 —  | ns  |     |     |
| --- | -------- | -------------- | --- | ----------- | --- | ------ | --- | --- | --- |
|     |          |                |     | 1.7MHz mode |     | 160 —  | ns  |     |     |
|     |          |                |     | 3.4MHz mode |     | 160 —  | ns  |     |     |
| 93  | T HD:STO | STOP condition |     | 100kHz mode |     | 4000 — | ns  |     |     |
|     |          | Hold time      |     | 400kHz mode |     | 600 —  | ns  |     |     |
|     |          |                |     | 1.7MHz mode |     | 160 —  | ns  |     |     |
|     |          |                |     | 3.4MHz mode |     | 160 —  | ns  |     |     |

|     |     |     | 103 | 100 |     |     |     |     | 102 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
101
SCL
|     |     | 90  |     | 106 |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|     |     |     | 91  |     |     | 107 |     | 92  |     |
SDA
In
|     |     |     | 109 |     | 109 |     |     |     | 110 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
SDA
Out
| FIGURE 1-2: |     | I2C Bus Data Timing. |     |     |     |     |     |     |     |
| ----------- | --- | -------------------- | --- | --- | --- | --- | --- | --- | --- |

|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     |     | DS22096B-page 13 |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | ---------------- |

MCP453X/455X/463X/465X
| TABLE 1-2: | I2C BUS DATA REQUIREMENTS (SLAVE MODE)  |     |     |     |     |
| ---------- | --------------------------------------- | --- | --- | --- | --- |
I2C AC Characteristics
Standard Operating Conditions (unless otherwise specified)
|     |     | Operating Temperature  | –40C  T |   +125C (Extended)  |     |
| --- | --- | ---------------------- | --------- | --------------------- | --- |
A
|     |     | Operating Voltage V |  range is described in AC/DC Characteristics |     |     |
| --- | --- | ------------------- | -------------------------------------------- | --- | --- |
DD
| Param.  Symbol | Characteristic |     | Min | Max Units | Conditions |
| -------------- | -------------- | --- | --- | --------- | ---------- |
No.
100 T HIGH Clock high time   100kHz mode 4000 — ns 1.8V-5.5V
|       |                | 400kHz mode | 600  | — ns | 2.7V-5.5V  |
| ----- | -------------- | ----------- | ---- | ---- | ---------- |
|       |                | 1.7MHz mode | 120  | ns   | 4.5V-5.5V  |
|       |                | 3.4MHz mode | 60   | — ns | 4.5V-5.5V  |
| 101 T | Clock low time | 100kHz mode | 4700 | — ns | 1.8V-5.5V  |
LOW
|     |     | 400kHz mode | 1300 | — ns | 2.7V-5.5V |
| --- | --- | ----------- | ---- | ---- | --------- |
|     |     | 1.7MHz mode | 320  | ns   | 4.5V-5.5V |
|     |     | 3.4MHz mode | 160  | — ns | 4.5V-5.5V |
102A  T RSCL   SCL rise time 100kHz mode  — 1000 ns Cb is specified to be from
| (Note5)  |     | 400kHz mode | 20 + 0.1Cb | 300 ns | 10 to 400pF (100pF  |
| -------- | --- | ----------- | ---------- | ------ | ------------------- |
maximum for 3.4MHz
|     |     | 1.7MHz mode | 20  | 80 ns |     |
| --- | --- | ----------- | --- | ----- | --- |
mode)
|     |     | 1.7MHz mode | 20  | 160 ns | After a Repeated Start  |
| --- | --- | ----------- | --- | ------ | ----------------------- |
condition or an
Acknowledge bit
|     |     | 3.4MHz mode | 10  | 40 ns |                         |
| --- | --- | ----------- | --- | ----- | ----------------------- |
|     |     | 3.4MHz mode | 10  | 80 ns | After a Repeated Start  |
condition or an
Acknowledge bit
102B  T   SDA rise time 100kHz mode  — 1000 ns Cb is specified to be from
RSDA
(Note5)  400kHz mode 20 + 0.1Cb 300 ns 10 to 400pF (100pF max
for 3.4MHz mode)
|     |     | 1.7MHz mode | 20  | 160 ns |     |
| --- | --- | ----------- | --- | ------ | --- |
|     |     | 3.4MHz mode | 10  | 80 ns  |     |
103A  T FSCL   SCL fall time 100kHz mode  — 300 ns Cb is specified to be from
| (Note5)  |     |             |            |        | 10 to 400pF (100pF max  |
| -------- | --- | ----------- | ---------- | ------ | ----------------------- |
|          |     | 400kHz mode | 20 + 0.1Cb | 300 ns |                         |
for 3.4MHz mode)
|     |     | 1.7MHz mode | 20  | 80 ns |     |
| --- | --- | ----------- | --- | ----- | --- |
|     |     | 3.4MHz mode | 10  | 40 ns |     |
Note 1: As a transmitter, the device must provide this internal minimum delay time to bridge the undefined region
(minimum 300ns) of the falling edge of SCL to avoid unintended generation of START or STOP conditions.
A fast-mode (400kHz) I2C-bus device can be used in a standard-mode (100kHz) I2C-bus system, but the
2:
requirement t 250ns must then be met. This will automatically be the case if the device does not
SU;DAT
stretch the LOW period of the SCL signal. If such a device does stretch the LOW period of the SCL signal,
it must output the next data bit to the SDA line.
=1000+250=1250ns (according to the standard-mode I2C bus specification) before
| T R  max.+t | SU;DAT |     |     |     |     |
| ----------- | ------ | --- | --- | --- | --- |
the SCL line is released.
| 3: Use C b |  in pF for the calculations. |     |     |     |     |
| ---------- | ---------------------------- | --- | --- | --- | --- |
4: Not tested.
5: A Master Transmitter must provide a delay to ensure that difference between SDA and SCL fall times do
not unintentionally create a Start or Stop condition.
| 6: Ensured by the T | AA  3.4MHz specification test. |     |     |                                       |     |
| ------------------- | ------------------------------ | --- | --- | ------------------------------------- | --- |
| DS22096B-page 14    |                                |     |     |  2008-2013 Microchip Technology Inc. |     |

MCP453X/455X/463X/465X
TABLE 1-2: I2C BUS DATA REQUIREMENTS (SLAVE MODE) (CONTINUED)
I2C AC Characteristics
Standard Operating Conditions (unless otherwise specified)
|     |     | Operating Temperature  | –40C  T |   +125C (Extended)  |     |
| --- | --- | ---------------------- | --------- | --------------------- | --- |
A
|     |     | Operating Voltage V |  range is described in AC/DC Characteristics |     |     |
| --- | --- | ------------------- | -------------------------------------------- | --- | --- |
DD
| Param.  Symbol | Characteristic |     | Min | Max Units | Conditions |
| -------------- | -------------- | --- | --- | --------- | ---------- |
No.
103B  T FSDA   SDA fall time 100kHz mode  — 300 ns Cb is specified to be from
| (Note5) |     |             |             | 10 to 400pF (100pF max  |     |
| ------- | --- | ----------- | ----------- | ----------------------- | --- |
|         |     | 400kHz mode | 20 + 0.1Cb  | 300 ns                  |     |
|         |     |             | (Note 3)    | for 3.4MHz mode)        |     |
|         |     | 1.7MHz mode | 20          | 160 ns                  |     |
|         |     | 3.4MHz mode | 10          | 80 ns                   |     |
106 T HD:DAT Data input hold  100kHz mode  0 — ns 1.8V-5.5V, Note5
time
|       |                   | 400kHz mode  | 0   | — ns 2.7V-5.5V, Note5 |     |
| ----- | ----------------- | ------------ | --- | --------------------- | --- |
|       |                   | 1.7MHz mode  | 0   | — ns 4.5V-5.5V, Note5 |     |
|       |                   | 3.4MHz mode  | 0   | — ns 4.5V-5.5V, Note5 |     |
| 107 T | Data input setup  | 100kHz mode  | 250 | — ns Note2            |     |
SU:DAT
time
|          |               | 400kHz mode  | 100 | — ns               |     |
| -------- | ------------- | ------------ | --- | ------------------ | --- |
|          |               | 1.7MHz mode  | 10  | — ns               |     |
|          |               | 3.4MHz mode  | 10  | — ns               |     |
| 109 T AA | Output valid  | 100kHz mode  | —   | 3450 ns Note1      |     |
|          | from clock    | 400kHz mode  | —   | 900 ns             |     |
|          |               | 1.7MHz mode  | —   | 150 ns Cb = 100pF, |     |
Note1, Note6
|     |     |     | —   | 310 ns Cb = 400pF, |     |
| --- | --- | --- | --- | ------------------ | --- |
Note1, Note4
|     |     | 3.4MHz mode  | —   | 150 ns Cb = 100pF, Note1 |     |
| --- | --- | ------------ | --- | ------------------------ | --- |
110 T Bus free time 100kHz mode  4700 — ns Time the bus must be free
BUF
before a new transmission
|     |     | 400kHz mode | 1300 | — ns |     |
| --- | --- | ----------- | ---- | ---- | --- |
can start
|     |     | 1.7MHz mode | N.A. | — ns |     |
| --- | --- | ----------- | ---- | ---- | --- |
|     |     | 3.4MHz mode | N.A. | — ns |     |
T SP   Input filter spike  100kHz mode  — 50 ns Philips Spec states N.A.
|     | suppression  | 400kHz mode | —   | 50 ns |     |
| --- | ------------ | ----------- | --- | ----- | --- |
(SDA and SCL)
|     |     | 1.7MHz mode | —   | 10 ns Spike suppression  |     |
| --- | --- | ----------- | --- | ------------------------ | --- |
|     |     | 3.4MHz mode | —   | 10 ns Spike suppression  |     |
Note 1: As a transmitter, the device must provide this internal minimum delay time to bridge the undefined region
(minimum 300ns) of the falling edge of SCL to avoid unintended generation of START or STOP conditions.
A fast-mode (400kHz) I2C-bus device can be used in a standard-mode (100kHz) I2C-bus system, but the
2:
requirement t 250ns must then be met. This will automatically be the case if the device does not
SU;DAT
stretch the LOW period of the SCL signal. If such a device does stretch the LOW period of the SCL signal,
it must output the next data bit to the SDA line.
=1000+250=1250ns (according to the standard-mode I2C bus specification) before
| T R  max.+t | SU;DAT |     |     |     |     |
| ----------- | ------ | --- | --- | --- | --- |
the SCL line is released.
| 3: Use C |  in pF for the calculations. |     |     |     |     |
| -------- | ---------------------------- | --- | --- | --- | --- |
b
4: Not tested.
5: A Master Transmitter must provide a delay to ensure that difference between SDA and SCL fall times do
not unintentionally create a Start or Stop condition.
| 6: Ensured by the T |  3.4MHz specification test. |     |     |     |     |
| ------------------- | --------------------------- | --- | --- | --- | --- |
AA
|  2008-2013 Microchip Technology Inc. |     |     |     |     | DS22096B-page 15 |
| ------------------------------------- | --- | --- | --- | --- | ---------------- |

MCP453X/455X/463X/465X
| TEMPERATURE CHARACTERISTICS |     |     |     |     |
| --------------------------- | --- | --- | --- | --- |
Electrical Specifications: Unless otherwise indicated, V =+2.7V to +5.5V, V =GND.
|            |         | DD      | SS    |            |
| ---------- | ------- | ------- | ----- | ---------- |
| Parameters | Sym Min | Typ Max | Units | Conditions |
Temperature Ranges
| Specified Temperature Range | T -40 | — +125 | °C  |     |
| --------------------------- | ----- | ------ | --- | --- |
A
| Operating Temperature Range | T -40 | — +125 | °C  |     |
| --------------------------- | ----- | ------ | --- | --- |
A
| Storage Temperature Range | T -65 | — +150 | °C  |     |
| ------------------------- | ----- | ------ | --- | --- |
A
Thermal Package Resistances
| Thermal Resistance, 8L-DFN (3x3) |  — | 56.7 — | °C/W |     |
| -------------------------------- | --- | ------ | ---- | --- |
JA
| Thermal Resistance, 8L-MSOP |  — | 211 — | °C/W |     |
| --------------------------- | --- | ----- | ---- | --- |
JA
| Thermal Resistance, 8L-SOIC |  — | 149.5 — | °C/W |     |
| --------------------------- | --- | ------- | ---- | --- |
JA
| Thermal Resistance, 10L-DFN (3x3) |  — | 57 — | °C/W |     |
| --------------------------------- | --- | ---- | ---- | --- |
JA
| Thermal Resistance, 10L-MSOP |  JA — | 202 — | °C/W |     |
| ---------------------------- | ------ | ----- | ---- | --- |
| Thermal Resistance, 14L-MSOP |  —    | N/A — | °C/W |     |
JA
| Thermal Resistance, 14L-SOIC |  — | 95.3 — | °C/W |     |
| ---------------------------- | --- | ------ | ---- | --- |
JA
| Thermal Resistance, 16L-QFN |  — | 45.7 — | °C/W |     |
| --------------------------- | --- | ------ | ---- | --- |
JA
| DS22096B-page 16 |     |     |  2008-2013 Microchip Technology Inc. |     |
| ---------------- | --- | --- | ------------------------------------- | --- |

MCP453X/455X/463X/465X
2.0 TYPICAL PERFORMANCE CURVES
Note: The graphs and tables provided following this note are a statistical summary based on a limited number of
samples and are provided for informational purposes only. The performance characteristics listed herein
are not tested or guaranteed. In some graphs or tables, the data presented may be outside the specified
operating range (e.g., outside specified power supply range) and therefore outside the warranted range.
| Note: Unless otherwise indicated, T |     |     |     |  = +25°C, V |  = 5V, V |  = 0V. |     |     |     |     |     |     |
| ----------------------------------- | --- | --- | --- | ----------- | -------- | ------ | --- | --- | --- | --- | --- | --- |
|                                     |     |     |     | A           | DD       | SS     |     |     |     |     |     |     |

|     |     |     |     |     |     |     | 250 |     |     |     |     | 1000 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---- |
800
|     |     |     |     | 1.7 MHz, 5.5V |     |     |     |     |     |     |     | 800 |
| --- | --- | --- | --- | ------------- | --- | --- | --- | --- | --- | --- | --- | --- |
700
3.4 MHz, 5.5V
|     |     |     |     |     |     |     | 200 |     |     |     |     | 600 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
600
|     |     |     |     |     |     |     | )smhOk(  |     |     |     |     | 400 |
| --- | --- | --- | --- | --- | --- | --- | -------- | --- | --- | --- | --- | --- |
500
| )Aµ(  |     |               |               |               |     |     | 150     |     |     | IHVC  |     | 200 )Aµ(  |
| ----- | --- | ------------- | ------------- | ------------- | --- | --- | ------- | --- | --- | ----- | --- | --------- |
|       | 400 |               |               |               |     |     |         |     |     |       |     | 0         |
|       | DD  |               |               |               |     |     |         |     |     |       |     | CVH       |
| I     | 300 | 400 kHz, 5.5V |               |               |     |     | CVH 100 |     |     |       |     | -200      |
|       |     | 100 kHz, 5.5V |               | 3.4 MHz, 4.5V |     |     |         |     |     |       |     | I         |
|       |     |               |               |               |     |     | R       |     |     |       |     | -400      |
|       | 200 |               | 1.7 MHz, 4.5V |               |     |     |         |     |     |       |     |           |
|       |     |               |               |               |     |     | 50      |     |     |       |     | -600      |
100
|     |     | 100 kHz, 2.7V |     |     |     |     |     |     | RHVC  |     |     | -800 |
| --- | --- | ------------- | --- | --- | --- | --- | --- | --- | ----- | --- | --- | ---- |
400 kHz, 2.7V
|     | 0   |     |                  |     |     |     | 0   |     |            |     |      | -1000 |
| --- | --- | --- | ---------------- | --- | --- | --- | --- | --- | ---------- | --- | ---- | ----- |
|     | -40 | 0   | 40               | 80  | 120 |     | 2   | 3 4 | 5 6 7      | 8   | 9 10 |       |
|     |     |     | Temperature (°C) |     |     |     |     |     | V HVC  (V) |     |      |       |
FIGURE 2-1: Device Current (I ) vs. I2C  FIGURE 2-4: HVC Pull-up/Pull-down
DD
|              |     |                            |     |     |     | Resistance (R |     |     | ) and Current (I |     | ) vs. HVC  |     |
| ------------ | --- | -------------------------- | --- | --- | --- | ------------- | --- | --- | ---------------- | --- | ---------- | --- |
| Frequency (f |     | ) and Ambient Temperature  |     |     |     |               |     | HVC |                  | HVC |            |     |
SCL
| (V  | = 2.7V and 5.5V). |     |     |     |     | Input Voltage (V |     | HVC | ) (V DD  = 5.5V). |     |     |     |
| --- | ----------------- | --- | --- | --- | --- | ---------------- | --- | --- | ----------------- | --- | --- | --- |
DD
12
3
)V( dlohserhT  10
|     | 2.5           |     |     |     |     |     |     | 5.5V Entry | 2.7V Entry |     |     |     |
| --- | ------------- | --- | --- | --- | --- | --- | --- | ---------- | ---------- | --- | --- | --- |
|     | )Aµ( ybdnatsI |     |     |     |     |     | 8   |            |            |     |     |     |
5.5V
2
5.5V Exit
6
1.5
PP 4
V CVH
2.7V Exit
|     | 1   |     |     |     |     |     | 2   |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
2.7V
|             | 0.5       |                            |     |     |             |                                         | 0   |     |                            |     |        |     |
| ----------- | --------- | -------------------------- | --- | --- | ----------- | --------------------------------------- | --- | --- | -------------------------- | --- | ------ | --- |
|             | -40       | 0                          | 40  | 80  | 120         |                                         | -40 | -20 | 0 20 40                    | 60  | 80 100 | 120 |
|             |           | Temperature (°C)           |     |     |             |                                         |     |     | Ambient Temperature (°C)   |     |        |     |
|             |           |                            |     |     |             | FIGURE 2-5:                             |     |     | HVC High Input Entry/Exit  |     |        |     |
| FIGURE 2-2: |           | Device Current (I          |     |     | SHDN ) and  |                                         |     |     |                            |     |        |     |
|             |           |                            |     |     |             | Threshold vs. Ambient Temperature and V |     |     |                            |     |        | .   |
| V           |  (HVC = V | ) vs. Ambient Temperature. |     |     |             |                                         |     |     |                            |     |        | DD  |
| DD          |           | DD                         |     |     |             |                                         |     |     |                            |     |        |     |
420
400
)Aµ(  380
360
ETIRW
5.5V
I 340
320
300
|     | -40 | 0   | 40  | 80  | 120 |     |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
Temperature (°C)
| FIGURE 2-3: |     | Write Current (I |     |     | ) vs.  |     |     |     |     |     |     |     |
| ----------- | --- | ---------------- | --- | --- | ------ | --- | --- | --- | --- | --- | --- | --- |
WRITE
Ambient Temperature.
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     |     |     | DS22096B-page 17 |     |     |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---------------- | --- | --- |

MCP453X/455X/463X/465X
Note: Unless otherwise indicated, T = +25°C, V = 5V, V = 0V.
A DD SS
120
100
80
60
40
20
0 32 64 96 128 160 192 224 256
Wiper Setting (decimal)
FIGURE 2-6: 5k Pot Mode – R (), FIGURE 2-9: 5k Rheo Mode – R (),
W W
INL (LSb), DNL (LSb) vs. Wiper Setting and INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V = 5.5V). Ambient Temperature (V = 5.5V).
DD DD
FIGURE 2-7: 5k Pot Mode – R (), FIGURE 2-10: 5k Rheo Mode – R (),
W W
INL (LSb), DNL (LSb) vs. Wiper Setting and INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V = 3.0V). Ambient Temperature (V = 3.0V).
DD DD
FIGURE 2-8: 5k Pot Mode – R (), FIGURE 2-11: 5k Rheo Mode – R (),
W W
INL (LSb), DNL (LSb) vs. Wiper Setting and INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V = 1.8V). Ambient Temperature (V = 1.8V).
DD DD
DS22096B-page 18  2008-2013 Microchip Technology Inc.
) R(
ecnatsiseR
repiW
W
)smho(
0.3
0.2
0.1
0
-0.1
-0.2
-0.3
)bSL(
rorrE
-40C Rw 25C Rw 85C Rw 125C Rw
-40C INL 25C INL 85C INL 125C INL
-40C DNL 25C DNL 85C DNL 125C DNL
DNL INL
85°C -40°C 25°C RW 125°C
300
260
220
180
140
100
60
20
0 32 64 96 128 160 192 224 256
Wiper Setting (decimal)
)
R( ecnatsiseR
repiW
W
)smho(
0.3
0.2
0.1
0
-0.1
-0.2
-0.3
)bSL(
rorrE
-40C Rw 25C Rw 85C Rw 125C Rw
-40C INL 25C INL 85C INL 125C INL -40C DNL 25C DNL 85C DNL 125C DNL
INL DNL
RW
125°C
85°C
25°C -40°C
2500
2000
1500
1000
500
0
0 64 128 192 256
Wiper Setting (decimal)
) R( ecnatsiseR
repiW
W
)smho(
0.5
0.4 0.3
0.2
0.1
0
-0.1
-0.2
-0.3
)bSL(
rorrE
120
100
80
60
40
20
0 32 64 96 128 160 192 224 256
Wiper Setting (decimal)
-40C Rw 25C Rw 85C Rw 125C Rw
-40C INL 25C INL 85C INL 125C INL -40C DNL 25C DNL 85C DNL 125C DNL INL
DNL
RW
Note: Refer to Appendix B: “Characteriza-
tion Data Analysis” for additional infor-
mation on the characteristics of the
wiper resistance (R ) with respect to
W
device voltage and wiper setting value.
) R(
ecnatsiseR
repiW
W
)smho(
1.25
0.75
0.25
-0.25
-0.75
-1.25
)bSL(
rorrE
-40C Rw 25C Rw 85C Rw 125C Rw
-40C INL 25C INL 85C INL 125C INL
-40C DNL 25C DNL 85C DNL 125C DNL
INL
DNL
-40°C 125°C 85°C 25°C RW
300
260
220
180
140
100
60
20
0 32 64 96 128 160 192 224 256
Wiper Setting (decimal)
)
R( ecnatsiseR
repiW
W
)smho(
6
4
2
0
-2
)bSL(
rorrE
-40C Rw 25C Rw 85C Rw 125C Rw
-40C INL 25C INL 85C INL 125C INL
-40C DNL 25C DNL 85C DNL 125C DNL
INL
RW
-40°C
125°C 85°C 25°C DNL
2500
2000
1500
1000
500
0
0 64 128 192 256
Wiper Setting (decimal)
) R( ecnatsiseR
repiW
W
)smho(
118
98 78
58
38
18
-2
)bSL(
rorrE
-40C Rw 25C Rw 85C Rw 125C Rw
-40C INL 25C INL 85C INL 125C INL
-40C DNL 25C DNL 85C DNL 125C DNL INL
RW DNL
Note: Refer to Appendix B: “Characteriza-
tion Data Analysis” for additional infor-
mation on the characteristics of the
wiper resistance (R ) with respect to
W
device voltage and wiper setting value.

MCP453X/455X/463X/465X
| Note: Unless otherwise indicated, T |  = +25°C, V |  = 5V, V |  = 0V. |     |     |
| ----------------------------------- | ----------- | -------- | ------ | --- | --- |
|                                     | A           | DD SS    |        |     |     |
| 5300                                |             |          | 6000   |     |     |
 )
| BA  |     |     | 5000 |     |     |
| --- | --- | --- | ---- | --- | --- |
R( ecnatsiseR lanimoN 5250
|     | 2.7V |     | )smhO(  4000 |     |     |
| --- | ---- | --- | ------------ | --- | --- |
)smhO( 5200
3000
| 5150 |     |     | BW  |     |     |
| ---- | --- | --- | --- | --- | --- |
2000
|           | 5.5V |     | R    |     | -40°C |
| --------- | ---- | --- | ---- | --- | ----- |
| 5100 1.8V |      |     |      |     | 25°C  |
|           |      |     | 1000 |     | 85°C  |
125°C
| 5050                      |       |     | 0    |                         |                 |
| ------------------------- | ----- | --- | ---- | ----------------------- | --------------- |
| -40 0                     | 40 80 | 120 | 0 32 | 64 96 128               | 160 192 224 256 |
| Ambient Temperature  (°C) |       |     |      | Wiper Setting (decimal) |                 |
FIGURE 2-12: 5k – Nominal Resistance  FIGURE 2-13: 5k – R  () vs. Wiper
WB
() vs. Ambient Temperature and V DD . Setting and Ambient Temperature.
|  2008-2013 Microchip Technology Inc. |     |     |     |     | DS22096B-page 19 |
| ------------------------------------- | --- | --- | --- | --- | ---------------- |

MCP453X/455X/463X/465X
Note: Unless otherwise indicated, T = +25°C, V = 5V, V = 0V.
A DD SS
FIGURE 2-14: 5k – Low-Voltage FIGURE 2-17: 5k – Low-Voltage
Decrement Wiper Settling Time (V = 5.5V) Increment Wiper Settling Time (V = 5.5V)
DD DD
(1µs/Div). (1µs/Div).
FIGURE 2-15: 5k – Low-Voltage FIGURE 2-18: 5k – Low-Voltage
Decrement Wiper Settling Time (V = 2.7V) Increment Wiper Settling Time (V = 2.7V)
DD DD
(1µs/Div). (1µs/Div).
FIGURE 2-16: 5k – Power-Up Wiper
Response Time (20ms/Div).
DS22096B-page 20  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
| Note: Unless otherwise indicated, T |     |         |        |        |  = +25°C, V |     |  = 5V, V |  = 0V. |         |        |        |         |     |
| ----------------------------------- | --- | ------- | ------ | ------ | ----------- | --- | -------- | ------ | ------- | ------ | ------ | ------- | --- |
|                                     |     |         |        |        | A           |     | DD SS    |        |         |        |        |         |     |
|                                     | 120 |         |        |        |             |     | 0.3      | 120    |         |        |        |         | 1   |
|                                     |     | -40C Rw | 25C Rw | 85C Rw | 125C Rw     |     |          |        | -40C Rw | 25C Rw | 85C Rw | 125C Rw |     |
-40C INL 25C INL 85C INL 125C INL -40C INL 25C INL 85C INL 125C INL
 ) -40C DNL 25C DNL 85C DNL 125C DNL 0.2  ) -40C DNL 25C DNL 85C DNL 125C DNL
|     | W 100               |     |     |     |     |     |     | W 100               |     |     |     |     |     |
| --- | ------------------- | --- | --- | --- | --- | --- | --- | ------------------- | --- | --- | --- | --- | --- |
|     | R( ecnatsiseR repiW |     |     |     |     |     |     | R( ecnatsiseR repiW |     |     |     |     | 0.5 |
INL
|     |        |     | DNL |     |     |     | 0.1 )bSL( rorrE |        |     |     | INL |     | )bSL( rorrE |
| --- | ------ | --- | --- | --- | --- | --- | --------------- | ------ | --- | --- | --- | --- | ----------- |
|     | 80     |     |     |     |     |     |                 |        | 80  |     |     |     |             |
|     | )smho( |     |     |     |     |     |                 | )smho( |     |     |     |     |             |
|     |        |     |     |     |     |     | 0               |        |     |     |     |     | 0           |
|     | 60     |     |     |     |     |     |                 |        | 60  |     |     |     |             |
-0.1
-0.5
|     | 40  |            |            |     |     |     |      |     | 40    |      |       | DNL |     |
| --- | --- | ---------- | ---------- | --- | --- | --- | ---- | --- | ----- | ---- | ----- | --- | --- |
|     |     |            | 25°C -40°C |     |     |     | -0.2 |     | 85°C  | 25°C | -40°C | RW  |     |
|     |     | 125°C 85°C |            |     | RW  |     |      |     | 125°C |      |       |     |     |
|     | 20  |            |            |     |     |     | -0.3 |     | 20    |      |       |     | -1  |
0 25 50 75 100125150175200225250 0 32 64 96 128 160 192 224 256
|     |     |     | Wiper Setting (decimal) |     |     |     |     |     |     | Wiper Setting (decimal) |     |     |     |
| --- | --- | --- | ----------------------- | --- | --- | --- | --- | --- | --- | ----------------------- | --- | --- | --- |
FIGURE 2-19: 10k Pot Mode – R  (),  FIGURE 2-22: 10k Rheo Mode – R  (),
|     |     |     |     |     |     | W   |     |     |     |     |     |     | W   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
INL (LSb), DNL (LSb) vs. Wiper Setting and  INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V  = 5.5V). Ambient Temperature (V  = 5.5V).
|     |     |     |     | DD  |     |     |     |     |         |        | DD     |         |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | ------- | ------ | ------ | ------- | --- |
|     |     |     |     |     |     |     |     |     | 300     |        |        |         | 4   |
|     | 300 |     |     |     |     |     | 0.3 |     | -40C Rw | 25C Rw | 85C Rw | 125C Rw |     |
-40C Rw 25C Rw 85C Rw 125C Rw -40C INL 25C INL 85C INL 125C INL
 ) -40C INL 25C INL 85C INL 125C INL  ) 260 -40C DNL 25C DNL 85C DNL 125C DNL
|     | W 260               | -40C DNL | 25C DNL | 85C DNL | 125C DNL |     | 0.2 | W                   |     |     |     |     | 3             |
| --- | ------------------- | -------- | ------- | ------- | -------- | --- | --- | ------------------- | --- | --- | --- | --- | ------------- |
|     | R( ecnatsiseR repiW |          |         |         |          |     |     | R( ecnatsiseR repiW |     |     |     | INL |               |
|     | 220                 |          |         |         |          |     |     |                     | 220 |     |     |     |               |
|     |                     |          | DNL     | INL     |          |     | 0.1 |                     |     |     |     |     | 2 )bSL( rorrE |
)bSL( rorrE
|     | )smho( 180 |     |     |     |     |     |     | )smho( | 180 |     |     |     |     |
| --- | ---------- | --- | --- | --- | --- | --- | --- | ------ | --- | --- | --- | --- | --- |
1
0
|     | 140 |            |      |       |     |     |      |     | 140   |           |       |        |     |
| --- | --- | ---------- | ---- | ----- | --- | --- | ---- | --- | ----- | --------- | ----- | ------ | --- |
|     |     |            |      |       |     |     | -0.1 |     |       |           |       |        | 0   |
|     | 100 |            |      | RW    |     |     |      |     | 100   |           |       |        |     |
|     |     |            |      |       |     |     | -0.2 |     |       |           | -40°C | DNL RW | -1  |
|     | 60  |            |      | -40°C |     |     |      |     | 60    |           |       |        |     |
|     |     | 125°C 85°C | 25°C |       |     |     |      |     |       | 85°C 25°C |       |        |     |
|     | 20  |            |      |       |     |     | -0.3 |     | 125°C |           |       |        |     |
|     |     |            |      |       |     |     |      |     | 20    |           |       |        | -2  |
0 32 64 96 128 160 192 224 256 0 25 50 75 100125150175200225250
|     |     |     | Wiper Setting (decimal) |     |     |     |     |     |     | Wiper Setting (decimal) |     |     |     |
| --- | --- | --- | ----------------------- | --- | --- | --- | --- | --- | --- | ----------------------- | --- | --- | --- |
FIGURE 2-20: 10k Pot Mode – R  (),  FIGURE 2-23: 10k Rheo Mode – R  (),
|     |     |     |     |     |     | W   |     |     |     |     |     |     | W   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
INL (LSb), DNL (LSb) vs. Wiper Setting and  INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V  = 3.0V). Ambient Temperature (V  = 3.0V).
|     |     |     |     | DD  |     |     |     |     |         |        | DD     |         |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | ------- | ------ | ------ | ------- | --- |
|     |     |     |     |     |     |     | 0.6 |     | -40C Rw | 25C Rw | 85C Rw | 125C Rw | 98  |
4000 -40C Rw 25C Rw 85C Rw 125C Rw 4000 -40C INL 25C INL 85C INL 125C INL
|     |      | -40C INL | 25C INL | 85C INL | 125C INL |     | 0.5 |  )  |               |         |         |          | 88  |
| --- | ---- | -------- | ------- | ------- | -------- | --- | --- | --- | ------------- | ------- | ------- | -------- | --- |
|     | 3500 |          |         |         |          |     |     | W   | 3500 -40C DNL | 25C DNL | 85C DNL | 125C DNL |     |
 ecnatsiseR repiW -40C DNL 25C DNL 85C DNL 125C DNL 0.4 R( ecnatsiseR repiW 78
3000
|     | )smho() 3000 |     |     |     |     |     | 0.3 )bSL( rorrE |     |     |     |     | INL | 68 )bSL( rorrE |
| --- | ------------ | --- | --- | --- | --- | --- | --------------- | --- | --- | --- | --- | --- | -------------- |
INL
|     | 2500 |     |     |     |     |     |     | )smho( | 2500 |     |     |     | 58  |
| --- | ---- | --- | --- | --- | --- | --- | --- | ------ | ---- | --- | --- | --- | --- |
0.2
|     | 2000    |     |     |     |     |     |     |     | 2000 |     |     |     | 48  |
| --- | ------- | --- | --- | --- | --- | --- | --- | --- | ---- | --- | --- | --- | --- |
|     |         |     | DNL |     |     |     | 0.1 |     |      |     |     |     |     |
|     | W       |     |     |     |     |     |     |     |      |     |     |     | 38  |
|     | R( 1500 |     |     |     |     |     | 0   |     | 1500 |     |     |     |     |
28
|     | 1000 |     |     |     |     |     | -0.1 |     | 1000 |     |     |     |     |
| --- | ---- | --- | --- | --- | --- | --- | ---- | --- | ---- | --- | --- | --- | --- |
18
|     | 500 |     |                         |     |     |     | -0.2 |     | 500 | RW                      |     |     |     |
| --- | --- | --- | ----------------------- | --- | --- | --- | ---- | --- | --- | ----------------------- | --- | --- | --- |
|     |     |     |                         |     | RW  |     |      |     |     |                         |     | DNL | 8   |
|     |     | 0   |                         |     |     |     | -0.3 |     |     |                         |     |     |     |
|     |     |     |                         |     |     |     |      |     | 0   |                         |     |     | -2  |
|     |     | 0   | 64                      | 128 | 192 | 256 |      |     |     |                         |     |     |     |
|     |     |     |                         |     |     |     |      |     | 0   | 64                      | 128 | 192 | 256 |
|     |     |     | Wiper Setting (decimal) |     |     |     |      |     |     | Wiper Setting (decimal) |     |     |     |
Note: Refer to Appendix B: “Characteriza- Note: Refer to Appendix B: “Characteriza-
tion Data Analysis” for additional infor- tion Data Analysis” for additional infor-
mation  on  the  characteristics  of  the mation  on  the  characteristics  of  the
wiper resistance (R ) with respect to wiper resistance (R ) with respect to
|     |     |     |     |     | W   |     |     |     |     |     |     | W   |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
device voltage and wiper setting value. device voltage and wiper setting value.
FIGURE 2-21: 10k Pot Mode – R  (),  FIGURE 2-24: 10k Rheo Mode – R  (),
|     |     |     |     |     |     | W   |     |     |     |     |     |     | W   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
INL (LSb), DNL (LSb) vs. Wiper Setting and  INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V  = 1.8V). Ambient Temperature (V  = 1.8V).
|                                       |     |     |     | DD  |     |     |     |     |     |     | DD  |                  |     |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---------------- | --- |
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     |     |     |     |     | DS22096B-page 21 |     |

MCP453X/455X/463X/465X
| Note: Unless otherwise indicated, T |       |  = +25°C, V |  = 5V, V |  = 0V. |     |     |
| ----------------------------------- | ----- | ----------- | -------- | ------ | --- | --- |
|                                     |       | A           | DD SS    |        |     |     |
|                                     | 10300 |             |          | 12000  |     |     |
 ) BA 10250
10000
R( ecnatsiseR lanimoN 10200
|     | 10150 |     |     | )smhO(  8000 |     |     |
| --- | ----- | --- | --- | ------------ | --- | --- |
)smhO(
10100
2.7V 6000
10050
BW
|     | 10000 |      |     | 4000 |     |       |
| --- | ----- | ---- | --- | ---- | --- | ----- |
|     |       | 5.5V |     | R    |     | -40°C |
|     | 9950  | 1.8V |     |      |     | 25°C  |
|     |       |      |     | 2000 |     | 85°C  |
9900
125°C
|     | 9850                      |         |     | 0    |                         |                 |
| --- | ------------------------- | ------- | --- | ---- | ----------------------- | --------------- |
|     | -40                       | 0 40 80 | 120 | 0 32 | 64 96 128               | 160 192 224 256 |
|     | Ambient Temperature  (°C) |         |     |      | Wiper Setting (decimal) |                 |
FIGURE 2-25: 10k – Nominal Resistance  FIGURE 2-26: 10k – R  () vs. Wiper
WB
() vs. Ambient Temperature and V DD . Setting and Ambient Temperature.
| DS22096B-page 22 |     |     |     |  2008-2013 Microchip Technology Inc. |     |     |
| ---------------- | --- | --- | --- | ------------------------------------- | --- | --- |

MCP453X/455X/463X/465X
Note: Unless otherwise indicated, T = +25°C, V = 5V, V = 0V.
A DD SS
FIGURE 2-27: 10k – Low-Voltage FIGURE 2-30: 10k – Low-Voltage
Decrement Wiper Settling Time (V = 5.5V) Increment Wiper Settling Time (V = 5.5V)
DD DD
(1µs/Div). (1µs/Div).
FIGURE 2-28: 10k – Low-Voltage FIGURE 2-31: 10k – Low-Voltage
Decrement Wiper Settling Time (V = 2.7V) Increment Wiper Settling Time (V = 2.7V)
DD DD
(1µs/Div). (1µs/Div).
FIGURE 2-29: 10k – Power-Up Wiper
Response Time (1µs/Div).
 2008-2013 Microchip Technology Inc. DS22096B-page 23

MCP453X/455X/463X/465X
Note: Unless otherwise indicated, T = +25°C, V = 5V, V = 0V.
A DD SS
120
100
80
60
40
20
0 32 64 96 128 160 192 224 256
Wiper Setting (decimal)
FIGURE 2-32: 50k Pot Mode – R (), FIGURE 2-35: 50k Rheo Mode – R (),
W W
INL (LSb), DNL (LSb) vs. Wiper Setting and INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V = 5.5V). Ambient Temperature (V = 5.5V).
DD DD
FIGURE 2-33: 50k Pot Mode – R (), FIGURE 2-36: 50k Rheo Mode – R (),
W W
INL (LSb), DNL (LSb) vs. Wiper Setting and INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V = 3.0V). Ambient Temperature (V = 3.0V).
DD DD
FIGURE 2-34: 50k Pot Mode – R (), FIGURE 2-37: 50k Rheo Mode – R (),
W W
INL (LSb), DNL (LSb) vs. Wiper Setting and INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V = 1.8V). Ambient Temperature (V = 1.8V).
DD DD
DS22096B-page 24  2008-2013 Microchip Technology Inc.
)
R(
ecnatsiseR
repiW
W
)smho(
0.3
0.2
0.1
0
-0.1
-0.2
-0.3
)bSL(
rorrE
-40C Rw 25C Rw 85C Rw 125C Rw
-40C INL 25C INL 85C INL 125C INL
-40C DNL 25C DNL 85C DNL 125C DNL
INL DNL
-40°C 25°C RW
125°C 85°C
300
260
220
180
140
100
60
20
0 32 64 96 128 160 192 224 256
Wiper Setting (decimal)
) R(
ecnatsiseR
repiW
W
)smho(
0.3
0.2
0.1
0
-0.1
-0.2
-0.3
)bSL(
rorrE
-40C Rw 25C Rw 85C Rw 125C Rw -40C INL 25C INL 85C INL 125C INL -40C DNL 25C DNL 85C DNL 125C DNL
INL
DNL
RW
-40°C
125°C 85°C 25°C
15000 14000
13000 12000 11000
10000
9000 8000
7000 6000
5000 4000
3000
2000
1000
0
0 64 128 192 256
Wiper Setting (decimal)
) R(
ecnatsiseR
repiW
W
)smho(
0.5
0.4 0.3
0.2
0.1
0 -0.1
-0.2
-0.3
-0.4
-0.5
)bSL(
rorrE
120
100
80
60
40
20
0 32 64 96 128 160 192 224 256
Wiper Setting (decimal)
-40C Rw 25C Rw 85C Rw 125C Rw
-40C INL 25C INL 85C INL 125C INL -40C DNL 25C DNL 85C DNL 125C DNL
DNL
INL
RW
Note: Refer to Appendix B: “Characteriza-
tion Data Analysis” for additional infor-
mation on the characteristics of the
wiper resistance (R ) with respect to
W
device voltage and wiper setting value.
)
R(
ecnatsiseR
repiW
W
)smho(
0.3
0.2
0.1
0
-0.1
-0.2
-0.3
)bSL(
rorrE
-40C Rw 25C Rw 85C Rw 125C Rw
-40C INL 25C INL 85C INL 125C INL
-40C DNL 25C DNL 85C DNL 125C DNL
INL
DNL
85°C 25°C -40°C RW 125°C
300
260
220
180
140
100
60
20
0 32 64 96 128 160 192 224 256
Wiper Setting (decimal)
) R(
ecnatsiseR
repiW
W
)smho(
1
0.75 0.5
0.25
0
-0.25
-0.5
-0.75
-1
)bSL(
rorrE
-40C Rw 25C Rw 85C Rw 125C Rw
-40C INL 25C INL 85C INL 125C INL -40C DNL 25C DNL 85C DNL 125C DNL INL
DNL
RW
-40°C
125°C 85°C 25°C
15000 14000
13000 12000 11000
10000
9000 8000
7000 6000
5000 4000
3000
2000
1000
0
0 25 50 75100125150175200225250
Wiper Setting (decimal)
)wR(
ecnatsiseR
repiW
)smho(
78.5 73.5
68.5 63.5 58.5
53.5
48.5 43.5
38.5 33.5 28.5
23.5 18.5
13.5
8.5
3.5
-1.5
)bSL(
rorrE
-40C Rw 25C Rw 85C Rw 125C Rw -40C INL 25C INL 85C INL 125C INL
-40C DNL 25C DNL 85C DNL 125C DNL RW
INL
DNL
Note: Refer to Appendix B: “Characteriza-
tion Data Analysis” for additional infor-
mation on the characteristics of the
wiper resistance (R ) with respect to
W
device voltage and wiper setting value.

MCP453X/455X/463X/465X
| Note: Unless otherwise indicated, T |     |  = +25°C, V |  = 5V, V |  = 0V. |     |     |
| ----------------------------------- | --- | ----------- | -------- | ------ | --- | --- |
|                                     |     | A           | DD SS    |        |     |     |
| 52500                               |     |             |          | 60000  |     |     |
 ) BA
| 52000 |     |     |     | 50000 |     |     |
| ----- | --- | --- | --- | ----- | --- | --- |
R( ecnatsiseR lanimoN
| 51500 |     | 1.8V |     |     |     |     |
| ----- | --- | ---- | --- | --- | --- | --- |
)smhO(  40000
)smhO(
51000
30000
50500
BW
20000
| 50000 |     |      |     | R     |     | -40°C |
| ----- | --- | ---- | --- | ----- | --- | ----- |
|       |     | 2.7V |     |       |     | 25°C  |
| 49500 |     |      |     | 10000 |     | 85°C  |
5.5V
125°C
| 49000 |                           |       |     | 0    |                         |                 |
| ----- | ------------------------- | ----- | --- | ---- | ----------------------- | --------------- |
|       | -40 0                     | 40 80 | 120 | 0 32 | 64 96 128               | 160 192 224 256 |
|       | Ambient Temperature  (°C) |       |     |      | Wiper Setting (decimal) |                 |
FIGURE 2-38: 50k – Nominal Resistance  FIGURE 2-39: 50k – R  () vs. Wiper
WB
() vs. Ambient Temperature and V DD . Setting and Ambient Temperature.
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     | DS22096B-page 25 |
| ------------------------------------- | --- | --- | --- | --- | --- | ---------------- |

MCP453X/455X/463X/465X
Note: Unless otherwise indicated, T = +25°C, V = 5V, V = 0V.
A DD SS
FIGURE 2-40: 50k – Low-Voltage FIGURE 2-43: 50k – Low-Voltage
Decrement Wiper Settling Time (V = 5.5V) Increment Wiper Settling Time (V = 5.5V)
DD DD
(1µs/Div). (1µs/Div).
FIGURE 2-41: 50k – Low-Voltage FIGURE 2-44: 50k – Low-Voltage
Decrement Wiper Settling Time (V = 2.7V) Increment Wiper Settling Time (V = 2.7V)
DD DD
(1µs/Div). (1µs/Div).
FIGURE 2-42: 50k – Power-Up Wiper
Response Time (1µs/Div).
DS22096B-page 26  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
| Note: Unless otherwise indicated, T |     |         |        |        |  = +25°C, V |     |  = 5V, V |  = 0V. |         |        |        |         |
| ----------------------------------- | --- | ------- | ------ | ------ | ----------- | --- | -------- | ------ | ------- | ------ | ------ | ------- |
|                                     |     |         |        |        | A           |     | DD SS    |        |         |        |        |         |
|                                     | 120 |         |        |        |             |     | 0.2      |        | 120     |        |        | 0.3     |
|                                     |     | -40C Rw | 25C Rw | 85C Rw | 125C Rw     |     |          |        | -40C Rw | 25C Rw | 85C Rw | 125C Rw |
-40C INL 25C INL 85C INL 125C INL -40C INL 25C INL 85C INL 125C INL
 ) -40C DNL 25C DNL 85C DNL 125C DNL  ) -40C DNL 25C DNL 85C DNL 125C DNL 0.2
|     | W 100               |     |     |     |     |     |     | W                   | 100 |     |     |     |
| --- | ------------------- | --- | --- | --- | --- | --- | --- | ------------------- | --- | --- | --- | --- |
|     | R( ecnatsiseR repiW |     |     |     |     |     | 0.1 | R( ecnatsiseR repiW |     | INL |     |     |
INL
|     |        |     | DNL |     |     |     | )bSL( rorrE |        | DNL |     |     | 0.1 )bSL( rorrE |
| --- | ------ | --- | --- | --- | --- | --- | ----------- | ------ | --- | --- | --- | --------------- |
|     | 80     |     |     |     |     |     |             |        | 80  |     |     |                 |
|     | )smho( |     |     |     |     |     |             | )smho( |     |     |     |                 |
|     |        |     |     |     |     |     | 0           |        |     |     |     | 0               |
|     | 60     |     |     |     |     |     |             |        | 60  |     |     |                 |
-0.1
-0.1
|     | 40  |     |            |     |     |     |     |     | 40         |       |     |         |
| --- | --- | --- | ---------- | --- | --- | --- | --- | --- | ---------- | ----- | --- | ------- |
|     |     |     | 25°C -40°C |     |     |     |     |     |            | -40°C |     | RW -0.2 |
|     |     |     |            | RW  |     |     |     |     | 125°C 85°C | 25°C  |     |         |
125°C 85°C
|     | 20  |     |     |     |     |     | -0.2 |     | 20  |     |     | -0.3 |
| --- | --- | --- | --- | --- | --- | --- | ---- | --- | --- | --- | --- | ---- |
0 32 64 96 128 160 192 224 256 0 32 64 96 128 160 192 224 256
|     |     |     | Wiper Setting (decimal) |     |     |     |     |     | Wiper Setting (decimal) |     |     |     |
| --- | --- | --- | ----------------------- | --- | --- | --- | --- | --- | ----------------------- | --- | --- | --- |
FIGURE 2-45: 100k Pot Mode – R  (),  FIGURE 2-48: 100k Rheo Mode – R
|     |     |     |     |     |     |     | W   |     |     |     |     | W   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
INL (LSb), DNL (LSb) vs. Wiper Setting and  (), INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V  = 5.5V). Ambient Temperature (V  = 5.5V).
|     |     |     |     | DD  |     |     |     |     |         |        | DD     |         |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | ------- | ------ | ------ | ------- |
|     |     |     |     |     |     |     |     |     | 300     |        |        | 0.6     |
|     | 300 |     |     |     |     |     | 0.2 |     | -40C Rw | 25C Rw | 85C Rw | 125C Rw |
-40C Rw 25C Rw 85C Rw 125C Rw -40C INL 25C INL 85C INL 125C INL
 ) -40C INL 25C INL 85C INL 125C INL 0.15  )wR( ecnatsiseR repiW 260 -40C DNL 25C DNL 85C DNL 125C DNL
|     | W 260               | -40C DNL | 25C DNL | 85C DNL | 125C DNL |     |                  |        |     |     |     | 0.4             |
| --- | ------------------- | -------- | ------- | ------- | -------- | --- | ---------------- | ------ | --- | --- | --- | --------------- |
|     | R( ecnatsiseR repiW |          |         |         |          |     |                  |        |     | INL |     |                 |
|     | 220                 |          |         | INL     |          |     | 0.1              |        | 220 |     |     |                 |
|     |                     |          | DNL     |         |          |     |                  |        | DNL |     |     | 0.2 )bSL( rorrE |
|     |                     |          |         |         |          |     | 0.05 )bSL( rorrE |        |     |     |     |                 |
|     | )smho( 180          |          |         |         |          |     |                  | )smho( | 180 |     |     |                 |
0
0
|     | 140 |     |     |     |     |     |     |     | 140 |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
-0.05
|     |     |     |     |     |     |     |     |     |     |     | RW  | -0.2 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---- |
|     | 100 |     |     | RW  |     |     |     |     | 100 |     |     |      |
-0.1
-0.4
|     |     | 60        |      | -40°C |     |     | -0.15 |     | 60    | -40°C |     |      |
| --- | --- | --------- | ---- | ----- | --- | --- | ----- | --- | ----- | ----- | --- | ---- |
|     |     | 125°C85°C | 25°C |       |     |     |       |     | 85°C  | 25°C  |     |      |
|     |     | 20        |      |       |     |     | -0.2  |     | 125°C |       |     |      |
|     |     |           |      |       |     |     |       |     | 20    |       |     | -0.6 |
0 32 64 96 128 160 192 224 256 0 32 64 96 128 160 192 224 256
|     |     |     | Wiper Setting (decimal) |     |     |     |     |     | Wiper Setting (decimal) |     |     |     |
| --- | --- | --- | ----------------------- | --- | --- | --- | --- | --- | ----------------------- | --- | --- | --- |
FIGURE 2-46: 100k Pot Mode – R  (),  FIGURE 2-49: 100k Rheo Mode – R
|     |     |     |     |     |     |     | W   |     |     |     |     | W   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
INL (LSb), DNL (LSb) vs. Wiper Setting and  (), INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V  = 3.0V). Ambient Temperature (V  = 3.0V).
|     |     |     |     | DD  |     |     |      |     |         |        | DD     |            |
| --- | --- | --- | --- | --- | --- | --- | ---- | --- | ------- | ------ | ------ | ---------- |
|     |     |     |     |     |     |     | 0.35 |     | -40C Rw | 25C Rw | 85C Rw | 125C Rw 59 |
-40C Rw 25C Rw 85C Rw 125C Rw -40C INL 25C INL 85C INL 125C INL 54
|     |  )                  |     | -40C INL | 25C INL 85C INL |     | 125C INL |             |  )                  | 25000    |         |         |             |
| --- | ------------------- | --- | -------- | --------------- | --- | -------- | ----------- | ------------------- | -------- | ------- | ------- | ----------- |
|     | W 25000             |     |          |                 |     |          | 0.25        | W                   | -40C DNL | 25C DNL | 85C DNL | 125C DNL 49 |
|     | R( ecnatsiseR repiW |     | -40C DNL | 25C DNL 85C DNL |     | 125C DNL |             | R( ecnatsiseR repiW |          |         |         |             |
|     |                     |     |          |                 |     |          |             |                     |          |         |         | RW 44       |
|     | 20000               |     | DNL      |                 |     |          | 0.15        |                     | 20000    |         |         | 39          |
|     |                     |     |          |                 |     |          | )bSL( rorrE |                     |          |         |         | )bSL( rorrE |
|     | )smho(              |     |          |                 |     |          | 0.05        | )smho(              |          |         |         | INL 34      |
15000
|     | 15000 |     |     |     |     |     |       |     |       |     |     | 29  |
| --- | ----- | --- | --- | --- | --- | --- | ----- | --- | ----- | --- | --- | --- |
|     |       |     |     |     |     |     | -0.05 |     |       |     |     | 24  |
|     | 10000 |     |     |     |     |     |       |     | 10000 |     |     | 19  |
-0.15
14
|     |     | 5000 |                         |     |     |     |       |     | 5000 |                         |         | 9   |
| --- | --- | ---- | ----------------------- | --- | --- | --- | ----- | --- | ---- | ----------------------- | ------- | --- |
|     |     |      |                         |     | INL |     | -0.25 |     |      |                         |         |     |
|     |     |      |                         | RW  |     |     |       |     |      | DNL                     |         | 4   |
|     |     | 0    |                         |     |     |     | -0.35 |     | 0    |                         |         | -1  |
|     |     | 0    | 64                      | 128 | 192 | 256 |       |     | 0    | 64                      | 128 192 | 256 |
|     |     |      | Wiper Setting (decimal) |     |     |     |       |     |      | Wiper Setting (decimal) |         |     |
Note: Refer to Appendix B: “Characteriza- Note: Refer to Appendix B: “Characteriza-
tion Data Analysis” for additional infor- tion Data Analysis” for additional infor-
mation  on  the  characteristics  of  the mation  on  the  characteristics  of  the
wiper resistance (R ) with respect to wiper resistance (R ) with respect to
|     |     |     |     |     | W   |     |     |     |     |     | W   |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
device voltage and wiper setting value. device voltage and wiper setting value.
FIGURE 2-47: 100k Pot Mode – R  (),  FIGURE 2-50: 100k Rheo Mode – R
|     |     |     |     |     |     |     | W   |     |     |     |     | W   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
INL (LSb), DNL (LSb) vs. Wiper Setting and  (), INL (LSb), DNL (LSb) vs. Wiper Setting and
Ambient Temperature (V  = 1.8V). Ambient Temperature (V  = 1.8V).
|                                       |     |     |     | DD  |     |     |     |     |     |     | DD               |     |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---------------- | --- |
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     |     |     |     | DS22096B-page 27 |     |

MCP453X/455X/463X/465X
| Note: Unless otherwise indicated, T |     |  = +25°C, V |  = 5V, V  = 0V. |     |     |     |
| ----------------------------------- | --- | ----------- | --------------- | --- | --- | --- |
|                                     |     | A           | DD SS           |     |     |     |
| 103500                              |     |             | 120000          |     |     |     |
 ) BA 103000
100000
R( ecnatsiseR lanimoN 102500
102000
)smhO( bwR 80000
)smhO( 101500
1.8V
| 101000 |     |     | 60000 |     |     |     |
| ------ | --- | --- | ----- | --- | --- | --- |
100500
40000
| 100000 |     |     |     |     |     | -40°C |
| ------ | --- | --- | --- | --- | --- | ----- |
2.7V
| 99500 |     |      |       |     |     | 25°C |
| ----- | --- | ---- | ----- | --- | --- | ---- |
|       |     |      | 20000 |     |     | 85°C |
| 99000 |     | 5.5V |       |     |     |      |
125°C
| 98500 |                           |       |     | 0    |                         |                 |
| ----- | ------------------------- | ----- | --- | ---- | ----------------------- | --------------- |
|       | -40 0                     | 40 80 | 120 | 0 32 | 64 96 128               | 160 192 224 256 |
|       | Ambient Temperature  (°C) |       |     |      | Wiper Setting (decimal) |                 |
FIGURE 2-51: 100k – Nominal  FIGURE 2-52: 100k – R  () vs. Wiper
WB
Resistance () vs. Ambient Temperature and  Setting and Ambient Temperature.
V .
DD
| DS22096B-page 28 |     |     |     |  2008-2013 Microchip Technology Inc. |     |     |
| ---------------- | --- | --- | --- | ------------------------------------- | --- | --- |

MCP453X/455X/463X/465X
| Note: Unless otherwise indicated, T |  = +25°C, V |  = 5V, V  = 0V. |
| ----------------------------------- | ----------- | --------------- |
|                                     | A           | DD SS           |
FIGURE 2-53: 100k – Low-Voltage  FIGURE 2-56: 100k – Low-Voltage
Decrement Wiper Settling Time (V DD  = 5.5V)  Increment Wiper Settling Time (V DD  = 2.7V)
(1µs/Div). (1µs/Div).
FIGURE 2-54: 100k – Low-Voltage
| Decrement Wiper Settling Time (V | = 2.7V)  |     |
| -------------------------------- | -------- | --- |
DD
(1µs/Div).
FIGURE 2-55: 100k – Low-Voltage
| Increment Wiper Settling Time (V | =5.5V)  |     |
| -------------------------------- | ------- | --- |
DD
(1µs/Div).
 2008-2013 Microchip Technology Inc. DS22096B-page 29

MCP453X/455X/463X/465X
| Note: Unless otherwise indicated, T |  = +25°C, V |  = 5V, V  = 0V. |     |     |     |
| ----------------------------------- | ----------- | --------------- | --- | --- | --- |
|                                     | A           | DD SS           |     |     |     |
0.12
0.1
0.09
0.1
0.08
| 0.07 |     |     | 0.08 | 5.5V |     |
| ---- | --- | --- | ---- | ---- | --- |
5.5V
0.06
% 0.06
% 0.05
0.04
| 0.03 3.0V |     |     | 0.04 |     |     |
| --------- | --- | --- | ---- | --- | --- |
0.02
0.02
| 0.01             |       |     |                  | 3.0V  |     |
| ---------------- | ----- | --- | ---------------- | ----- | --- |
| 0                |       |     | 0                |       |     |
| -40 0            | 40 80 | 120 |                  |       |     |
|                  |       |     | -40 0            | 40 80 | 120 |
| Temperature (°C) |       |     | Temperature (°C) |       |     |
FIGURE 2-57: Resistor Network 0 to  FIGURE 2-59: Resistor Network 0 to
Resistor Network 1 R AB  (5k) Mismatch vs. V DD   Resistor Network 1 R AB  (50k) Mismatch vs.
| and Temperature. |     | V   |  and Temperature. |     |     |
| ---------------- | --- | --- | ----------------- | --- | --- |
DD
0.04
0.05
| 0.03 |      |     | 0.04 |      |     |
| ---- | ---- | --- | ---- | ---- | --- |
| 0.02 |      |     | 0.03 |      |     |
|      | 5.5V |     |      | 5.5V |     |
0.01
0.02
| % 0   |     |     | % 0.01 |     |     |
| ----- | --- | --- | ------ | --- | --- |
| -0.01 |     |     | 3.0V   |     |     |
| 3.0V  |     |     | 0      |     |     |
-0.02
-0.01
| -0.03 |     |     | -0.02 |     |     |
| ----- | --- | --- | ----- | --- | --- |
-0.04
-0.03
| -40 0            | 40 80 | 120 |                  |     |     |
| ---------------- | ----- | --- | ---------------- | --- | --- |
|                  |       |     | -40 10           | 60  | 110 |
| Temperature (°C) |       |     | Temperature (°C) |     |     |
FIGURE 2-58: Resistor Network 0 to  FIGURE 2-60: Resistor Network 0 to
Resistor Network 1 R  (10k) Mismatch vs.  Resistor Network 1 R  (100k) Mismatch vs.
|                     | AB  |     |                                       | AB  |     |
| ------------------- | --- | --- | ------------------------------------- | --- | --- |
| V  and Temperature. |     | V   |  and Temperature.                     |     |     |
| DD                  |     |     | DD                                    |     |     |
| DS22096B-page 30    |     |     |  2008-2013 Microchip Technology Inc. |     |     |

MCP453X/455X/463X/465X
| Note: Unless otherwise indicated, T |     |     |  = +25°C, V |  = 5V, V |  = 0V. |     |     |     |     |
| ----------------------------------- | --- | --- | ----------- | -------- | ------ | --- | --- | --- | --- |
|                                     |     |     | A           | DD       | SS     |     |     |     |     |
|                                     | 4   |     |             |          |        | 230 |     |     |     |
210
|     | 3.5 |      |     |     |     |     |     | 2.7V |     |
| --- | --- | ---- | --- | --- | --- | --- | --- | ---- | --- |
|     |     | 5.5V |     |     |     | 190 |     |      |     |
3
)Vm(  170
)V(
150
2.5
|     | HI  |     |     |     | LO  | 130 |     | 5.5V |     |
| --- | --- | --- | --- | --- | --- | --- | --- | ---- | --- |
| V   |     |     |     |     | V   |     |     |      |     |
|     | 2   |     |     |     |     | 110 |     |      |     |
2.7V
90
1.5
70
|     | 1   |                  |     |     |     | 50    |                  |     |     |
| --- | --- | ---------------- | --- | --- | --- | ----- | ---------------- | --- | --- |
|     | -40 | 0 40             | 80  | 120 |     | -40 0 | 40               | 80  | 120 |
|     |     | Temperature (°C) |     |     |     |       | Temperature (°C) |     |     |
FIGURE 2-61: V  (SDA, SCL) vs. V  and  FIGURE 2-63: V  (SDA) vs. V  and
|              |     | IH  |     | DD  |                |             | OL  | DD  |     |
| ------------ | --- | --- | --- | --- | -------------- | ----------- | --- | --- | --- |
| Temperature. |     |     |     |     | Temperature (I | OL  = 3mA). |     |     |     |
2
5.5V
)V(
1.5
V LI
2.7V
1
|     | -40 | 0 40 | 80  | 120 |     |     |     |     |     |
| --- | --- | ---- | --- | --- | --- | --- | --- | --- | --- |
Temperature (°C)
| FIGURE 2-62: |     | V  (SDA, SCL) vs. V |     |  and  |     |     |     |     |     |
| ------------ | --- | ------------------- | --- | ----- | --- | --- | --- | --- | --- |
|              |     | IL                  |     | DD    |     |     |     |     |     |
Temperature.
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     | DS22096B-page 31 |     |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | ---------------- | --- |

MCP453X/455X/463X/465X
Note: Unless otherwise indicated, T  = +25°C, 2.1 Test Circuits
A
V  = 5V, V  = 0V.
DD SS
1.2
+5V
1
|     |     | 5.5V |     |     | A   |     |     |
| --- | --- | ---- | --- | --- | --- | --- | --- |
V IN
| 0.8 |     |     |     |     | W   | +   | V   |
| --- | --- | --- | --- | --- | --- | --- | --- |
OUT
)V(
| 0.6 |     | 2.7V |        |     | B   |     |     |
| --- | --- | ---- | ------ | --- | --- | --- | --- |
| DD  |     |      |        |     |     | -   |     |
| V   |     |      | Offset |     |     |     |     |
0.4
GND
0.2
2.5V DC
0
| -40 0 | 40  | 80 120 |     |     |     |     |     |
| ----- | --- | ------ | --- | --- | --- | --- | --- |
Temperature (°C)
FIGURE 2-64: POR/BOR Trip point vs. V   FIGURE 2-65: -3db Gain vs. Frequency
DD
Test.
and Temperature.
floating
V
A
A
|     |     |     |     |     | V   |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- |
W
W
I
|     |     |     |     |     | W   | R  = V  | /I       |
| --- | --- | --- | --- | --- | --- | ------- | -------- |
|     |     |     |     |     |     | BW      | W W      |
|     |     |     |     | B   |     | R  = (V | -V )/I   |
|     |     |     |     | V   |     | W       | W A W    |
B
|                  |     |     | FIGURE 2-66: |     | R BW                                  |  and R W  Measurement. |     |
| ---------------- | --- | --- | ------------ | --- | ------------------------------------- | ---------------------- | --- |
| DS22096B-page 32 |     |     |              |     |  2008-2013 Microchip Technology Inc. |                        |     |

MCP453X/455X/463X/465X
3.0 PIN DESCRIPTIONS
The descriptions of the pins are listed in Table3-1.
Additional descriptions of the device pins follows.
| TABLE 3-1: | PINOUT DESCRIPTION FOR THE MCP453X/455X/463X/465X |     |     |     |     |     |     |
| ---------- | ------------------------------------------------- | --- | --- | --- | --- | --- | --- |
Pin
Weak
| Single |     | Dual  |     |     |          |             |                   |
| ------ | --- | ----- | --- | --- | -------- | ----------- | ----------------- |
|        |     |       |     |     | B u f fe | r  Pull-up/ | Standard Function |
(1)
| Rheo Pot | Rheo | Pot     | Symbol | I/O |         | down    | (1)                     |
| -------- | ---- | ------- | ------ | --- | ------- | ------- | ----------------------- |
|          |      |         |        |     | T y p e |         |                         |
| 8L 8L    | 10L  | 14L 16L |        |     |         |         |                         |
| 1 1      | 1    | 1 16    | HVC/A0 | I   | HV w/ST | “smart” | High Voltage Command /  |
Address 0
| 2 2 | 2   | 2 1 | SCL | I   | HV w/ST | No  | I2C clock input  |
| --- | --- | --- | --- | --- | ------- | --- | ---------------- |
3 3 3 3 2 SDA I/O HV w/ST No I2C serial data I/O. Open Drain
output
| 4 4 | 4   | 4 3, 4 | V   | —   | P   | —   | Ground |
| --- | --- | ------ | --- | --- | --- | --- | ------ |
SS
| — — | 5   | 5 5       | P1B | A   | Analog  | No      | Potentiometer 1 Terminal B      |
| --- | --- | --------- | --- | --- | ------- | ------- | ------------------------------- |
| — — | 6   | 6 6       | P1W | A   | Analog  | No      | Potentiometer 1 Wiper Terminal  |
| — — | —   | 7 7       | P1A | A   | Analog  | No      | Potentiometer 1 Terminal A      |
| — 5 | —   | 8 8       | P0A | A   | Analog  | No      | Potentiometer 0 Terminal A      |
| 5 6 | 7   | 9 9       | P0W | A   | Analog  | No      | Potentiometer 0 Wiper Terminal  |
| 6 7 | 8   | 10 10     | P0B | A   | Analog  | No      | Potentiometer 0 Terminal B      |
| — — | —   | 11 11, 12 | NC  | —   | —       | —       | No Connection                   |
| — — | —   | 12 13     | A2  | I   | HV w/ST | “smart” | Address 2                       |
| 7 — | 9   | 13 14     | A1  | I   | HV w/ST | “smart” | Address 1                       |
| 8 8 | 10  | 14 15     | V   | —   | P       | —       | Positive Power Supply Input     |
DD
| 9 9                                                                          | 11  | — 17 | EP  | —   | —   | —   | Exposed Pad (Note2)  |
| ---------------------------------------------------------------------------- | --- | ---- | --- | --- | --- | --- | -------------------- |
| Legend: HV w/ST = High Voltage tolerant input (with Schmidtt trigger input)  |     |      |     |     |     |     |                      |
A = Analog pins (Potentiometer terminals)  I = digital input (high Z)
O = digital output      I/O = Input / Output
P = Power
Note 1: The pin’s “smart” pull-up shuts off while the pin is forced low. This is done to reduce the standby and shut-
down current.
2: The DFN and QFN packages have a contact on the bottom of the package. This contact is conductively
connected to the die substrate, and therefore should be unconnected or connected to the same ground as
| the device’s V |     |  pin.  |     |     |     |     |     |
| -------------- | --- | ------ | --- | --- | --- | --- | --- |
SS
 2008-2013 Microchip Technology Inc. DS22096B-page 33

MCP453X/455X/463X/465X
3.1 High Voltage Command / Address 0 3.7 Potentiometer Terminal A
(HVC/A0)
The terminal A pin is available on the MCP4XX1
The HVC/A0 pin is the Address 0 input for the I2C devices, and is connected to the internal potentiome-
interface as well as the High Voltage command pin. At ter’s terminal A.
the device’s POR/BOR the value of the A0 address bit The potentiometer’s terminal A is the fixed connection
is latched. This input, along with the A2 and A1 pins, to the Full-Scale wiper value of the digital potentiome-
completes the device address. This allows up to eight ter. This corresponds to a wiper value of 0x100 for 8-bit
MCP45XX/46XX devices on a single I2C bus. devices or 0x80 for 7-bit devices.
During normal operation the voltage on this pin deter- The terminal A pin does not have a polarity relative to
mines if the I2C command is a normal command or a the terminal W or B pins. The terminal A pin can
High Voltage command (when HVC/A0 = V IHH ). support both positive and negative current. The voltage
on terminal A must be between V and V .
SS DD
3.2 Serial Clock (SCL)
The terminal A pin is not available on the MCP4XX2
The SCL pin is the serial interfaces Serial Clock pin. devices, and the internally terminal A signal is floating.
This pin is connected to the Host Controllers SCL pin. MCP46X1 devices have two terminal A pins, one for
The MCP45XX/46XX is a slave device, so its SCL pin each resistor network.
accepts only external clock signals.
3.8 Address 2 (A2)
3.3 Serial Data (SDA)
The A2 pin is the I2C interface’s Address 2 pin. Along
The SDA pin is the serial interfaces Serial Data pin. with the A1 and A0 pins, up to eight MCP45XX/46XX
This pin is connected to the Host Controllers SDA pin. devices can be used on a single I2C bus.
The SDA pin is an open-drain N-channel driver.
3.9 Address 1 (A1)
3.4 Ground (V )
SS
The A2 pin is the I2C interface’s Address 1 pin. Along
The V pin is the device ground reference.
SS with the A2 and A0 pins, up to eight MCP45XX/46XX
devices can be used on a single I2C bus.
3.5 Potentiometer Terminal B
The terminal B pin is connected to the internal 3.10 Positive Power Supply Input (V )
DD
potentiometer’s terminal B.
The V pin is the device’s positive power supply input.
DD
The potentiometer’s terminal B is the fixed connection The input power supply is relative to V .
SS
to the Zero Scale wiper value of the digital potentiome-
While the device V < V (2.7V), the electrical
ter. This corresponds to a wiper value of 0x00 for both DD min
performance of the device may not meet the data sheet
7-bit and 8-bit devices.
specifications.
The terminal B pin does not have a polarity relative to
the terminal W or A pins. The terminal B pin can
3.11 No Connect (NC)
support both positive and negative current. The voltage
on terminal B must be between V SS and V DD . These pins should be either connected to V DD or V SS .
MCP46XX devices have two terminal B pins, one for
each resistor network. 3.12 Exposed Pad (EP)
This pad is conductively connected to the device’s
3.6 Potentiometer Wiper (W) Terminal
substrate. This pad should be tied to the same potential
The terminal W pin is connected to the internal potenti- as the V SS pin (or left unconnected). This pad could be
ometer’s terminal W (the wiper). The wiper terminal is used to assist as a heat sink for the device when
the adjustable terminal of the digital potentiometer. The connected to a PCB heat sink.
terminal W pin does not have a polarity relative to
terminals A or B pins. The terminal W pin can support
both positive and negative current. The voltage on
terminal W must be between V and V .
SS DD
MCP46XX devices have two terminal W pins, one for
each resistor network.
DS22096B-page 34  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
| 4.0 FUNCTIONAL OVERVIEW |     |     | 4.1.2 BROWN-OUT RESET  |     |     |
| ----------------------- | --- | --- | ---------------------- | --- | --- |
When the device powers down, the device V  will
| This data sheet covers a family of thirty-two digital |     |     |     |     | DD  |
| ----------------------------------------------------- | --- | --- | --- | --- | --- |
Potentiometer  and  Rheostat  devices  that  will  be cross the V POR /V BOR  voltage.
referred to as MCP4XXX. The MCP4XX1 devices are Once the V DD  voltage decreases below the V POR /V BOR
the Potentiometer configuration, while the MCP4XX2 voltage, the Serial Interface is disabled.
devices are the Rheostat configuration.
|     |     |     | If the V  voltage decreases below the V |     |  voltage, |
| --- | --- | --- | --------------------------------------- | --- | --------- |
|     |     |     | DD                                      |     | RAM       |
As the Device Block Diagram shows, there are four the following may happen:
main functional blocks. These are:
• Volatile wiper registers become corrupt
• POR/BOR Operation
• TCON register becomes corrupt
• Memory Map
|     |     |     | As the voltage recovers above the V |     | POR /V BOR  voltage |
| --- | --- | --- | ----------------------------------- | --- | ------------------- |
• Resistor Network
see Section4.1.1 “Power-on Reset”.
• Serial Interface (I2C)
Serial commands not completed due to a brown-out
The POR/BOR operation and the memory map are condition may cause the volatile memory location to
| discussed in this section and the Resistor Network and |     |     | become corrupted. |     |     |
| ------------------------------------------------------ | --- | --- | ----------------- | --- | --- |
I2C operation are described in their own sections. The
Device  Commands  commands  are  discussed  in 4.2 Memory Map
Section7.0 “Device Commands”.
The device memory map supports 16 locations, of
4.1 POR/BOR Operation  which three locations are used. Each location is 9-bits
wide (16x9 bits). This memory space is shown in
| The Power-on Reset is the case where the device has |     |             | Table4-1.  |     |     |
| --------------------------------------------------- | --- | ----------- | ---------- | --- | --- |
| power applied to it, starting from the V            |     |  level. The |            |     |     |
SS
Brown-out Reset occurs when power is applied to the TABLE 4-1: MEMORY MAP
device, and that power (voltage) drops below the spec-
|     |     |     | Address | Function | Memory Type |
| --- | --- | --- | ------- | -------- | ----------- |
ified range.
|                                       |     |            | 00h Volatile Wiper 0  |     | RAM |
| ------------------------------------- | --- | ---------- | --------------------- | --- | --- |
| The device’s RAM retention voltage (V |     | ) is lower |                       |     |     |
RAM
than the POR/BOR voltage trip point (V /V ). The 01h Volatile Wiper 1  RAM
POR BOR
| maximum V | /V  voltage is less than 1.8V.      |     |              |     |     |
| --------- | ----------------------------------- | --- | ------------ | --- | --- |
|           | POR BOR                             |     | 02h Reserved |     | —   |
| When V    | /V <V <2.7V, the electrical perfor- |     |              |     |     |
| POR       | BOR DD                              |     | 03h Reserved |     | —   |
mance may not meet the data sheet specifications. In
|     |     |     | 04h Volatile TCON register |     | RAM |
| --- | --- | --- | -------------------------- | --- | --- |
this region, the device is capable of incrementing, dec-
|     |     |     | 05h Reserved |     | RAM |
| --- | --- | --- | ------------ | --- | --- |
rementing, reading and writing to its volatile memory if
|     |     |     | 06h - 0Fh Reserved |     | —   |
| --- | --- | --- | ------------------ | --- | --- |
the proper serial command is executed.
| 4.1.1                                   | POWER-ON RESET  |             |                             |     |     |
| --------------------------------------- | --------------- | ----------- | --------------------------- | --- | --- |
|                                         |                 |             | 4.2.1 VOLATILE MEMORY (RAM) |     |     |
| When the device powers up, the device V |                 |  will cross |                             |     |     |
DD
There are four volatile memory locations. These are:
| the V POR /V                                    | BOR  voltage. Once the V        | DD  voltage crosses |                                       |     |     |
| ----------------------------------------------- | ------------------------------- | ------------------- | ------------------------------------- | --- | --- |
| the V /V                                        |  voltage the following happens: |                     | • Volatile Wiper 0                    |     |     |
| POR                                             | BOR                             |                     |                                       |     |     |
| • Volatile wiper register is loaded with value  |                                 |                     | • Volatile Wiper 1                    |     |     |
| (mid-scale)                                     |                                 |                     | (Dual Resistor Network devices only)  |     |     |
• The TCON register is loaded with the default  • Terminal Control (TCON) register
| value |     |     | • Reserved  |     |     |
| ----- | --- | --- | ----------- | --- | --- |
• The device is capable of digital operation
The volatile memory starts functioning at the RAM
|     |     |     | retention voltage (V            | RAM ).  |     |
| --- | --- | --- | ------------------------------- | ------- | --- |
|     |     |     | 4.2.1.1 Address 05h (Reserved)  |         |     |
This memory location is Reserved and is mapped to
the Status Register of the nonvolatile MCP45XX/46XX
devices. Since the nonvolatile device’s bits are not
used by the volatile device, this location is reserved.
Reading this address will result in a value of 1F7h.
|  2008-2013 Microchip Technology Inc. |     |     |     |     | DS22096B-page 35 |
| ------------------------------------- | --- | --- | --- | --- | ---------------- |

MCP453X/455X/463X/465X
4.2.1.2 Terminal Control (TCON) Register When the WL1 bit is enabled, writes to the TCON
register bits R1HW, R1A, R1W, and R1B are inhibited.
This register contains 8 control bits. Four bits are for
Wiper 0, and four bits are for Wiper 1. Register4-1 When the WL0 bit is enabled, writes to the TCON
describes each bit of the TCON register. register bits R0HW, R0A, R0W, and R0B are inhibited.
The state of each resistor network terminal connection On a POR/BOR this register is loaded with 1FFh
is individually controlled. That is, each terminal (9-bits), for all terminals connected. The Host
connection (A, B and W) can be individually connected/ Controller needs to detect the POR/BOR event and
disconnected from the resistor network. This allows the then update the volatile TCON register value.
system to minimize the currents through the digital
Additionally, there is a bit which enables the operation
potentiometer.
of General Call commands.
The value that is written to this register will appear on
the resistor network terminals when the serial
command has completed.
DS22096B-page 36  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
|      | TCON BITS  (ADDRESS = 0x04) (1) |     |     |     |     |     |     |
| ---- | ------------------------------- | --- | --- | --- | --- | --- | --- |
REGISTER 4-1:
| R/W-1 | R/W-1 | R/W-1 | R/W-1 | R/W-1 R/W-1 | R/W-1 | R/W-1 | R/W-1  |
| ----- | ----- | ----- | ----- | ----------- | ----- | ----- | ------ |
| GCEN  | R1HW  | R1A   | R1W   | R1B R0HW    | R0A   | R0W   | R0B    |
| bit 8 |       |       |       |             |       |       | bit  0 |
Legend:
R = Readable bit W = Writable bit U = Unimplemented bit, read as ‘0’
-n = Value at POR ‘1’ = Bit is set ‘0’ = Bit is cleared x = Bit is unknown
| bit 8 | GCEN: General Call Enable bit  |     |     |     |     |     |     |
| ----- | ------------------------------ | --- | --- | --- | --- | --- | --- |
This bit specifies if I2C General Call commands are accepted
1 = Enable Device to “Accept” the General Call Address (0000h)
0 = The General Call Address is disabled
| bit 7 | R1HW: Resistor 1 Hardware Configuration Control bit |     |     |     |     |     |     |
| ----- | --------------------------------------------------- | --- | --- | --- | --- | --- | --- |
This bit forces Resistor 1 into the “shutdown” configuration of the Hardware pin
1 = Resistor 1 is NOT forced to the hardware pin “shutdown” configuration
0 = Resistor 1 is forced to the hardware pin “shutdown” configuration
| bit 6 | R1A: Resistor 1 Terminal A (P1A pin) Connect Control bit  |     |     |     |     |     |     |
| ----- | --------------------------------------------------------- | --- | --- | --- | --- | --- | --- |
This bit connects/disconnects the Resistor 1 Terminal A to the Resistor 1 Network
1 = P1A pin is connected to the Resistor 1 Network
0 = P1A pin is disconnected from the Resistor 1 Network
| bit 5 | R1W: Resistor 1 Wiper (P1W pin) Connect Control bit |     |     |     |     |     |     |
| ----- | --------------------------------------------------- | --- | --- | --- | --- | --- | --- |
This bit connects/disconnects the Resistor 1 Wiper to the Resistor 1 Network
1 = P1W pin is connected to the Resistor 1 Network
0 = P1W pin is disconnected from the Resistor 1 Network
| bit 4 | R1B: Resistor 1 Terminal B (P1B pin) Connect Control bit |     |     |     |     |     |     |
| ----- | -------------------------------------------------------- | --- | --- | --- | --- | --- | --- |
This bit connects/disconnects the Resistor 1 Terminal B to the Resistor 1 Network
1 = P1B pin is connected to the Resistor 1 Network
0 = P1B pin is disconnected from the Resistor 1 Network
| bit 3 | R0HW: Resistor 0 Hardware Configuration Control bit  |     |     |     |     |     |     |
| ----- | ---------------------------------------------------- | --- | --- | --- | --- | --- | --- |
This bit forces Resistor 0 into the “shutdown” configuration of the Hardware pin
1 = Resistor 0 is NOT forced to the hardware pin “shutdown” configuration
0 = Resistor 0 is forced to the hardware pin “shutdown” configuration
| bit 2 | R0A: Resistor 0 Terminal A (P0A pin) Connect Control bit |     |     |     |     |     |     |
| ----- | -------------------------------------------------------- | --- | --- | --- | --- | --- | --- |
This bit connects/disconnects the Resistor 0 Terminal A to the Resistor 0 Network
1 = P0A pin is connected to the Resistor 0 Network
0 = P0A pin is disconnected from the Resistor 0 Network
| bit 1 | R0W: Resistor 0 Wiper (P0W pin) Connect Control bit |     |     |     |     |     |     |
| ----- | --------------------------------------------------- | --- | --- | --- | --- | --- | --- |
This bit connects/disconnects the Resistor 0 Wiper to the Resistor 0 Network
1 = P0W pin is connected to the Resistor 0 Network
0 = P0W pin is disconnected from the Resistor 0 Network
| bit 0 | R0B: Resistor 0 Terminal B (P0B pin) Connect Control bit |     |     |     |     |     |     |
| ----- | -------------------------------------------------------- | --- | --- | --- | --- | --- | --- |
This bit connects/disconnects the Resistor 0 Terminal B to the Resistor 0 Network
1 = P0B pin is connected to the Resistor 0 Network
0 = P0B pin is disconnected from the Resistor 0 Network
Note 1: These bits do not affect the wiper register values.
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     | DS22096B-page 37 |     |
| ------------------------------------- | --- | --- | --- | --- | --- | ---------------- | --- |

MCP453X/455X/463X/465X
NOTES:
DS22096B-page 38  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
| 5.0 | RESISTOR NETWORK |     |     |     | 5.1 | Resistor Ladder Module |     |     |     |
| --- | ---------------- | --- | --- | --- | --- | ---------------------- | --- | --- | --- |
The  Resistor  Network  has  either  7-bit  or  8-bit The resistor ladder is a series of equal value resistors
resolution. Each Resistor Network allows zero scale to (R ) with a connection point (tap) between the two
S
resistors. The total number of resistors in the series
| full-scale  | connections.  | Figure5-1  | shows  | a  block |     |     |     |     |     |
| ----------- | ------------- | ---------- | ------ | -------- | --- | --- | --- | --- | --- |
diagram for the resistive network of a device.  (ladder)  determines  the  R AB   resistance  (see
Figure5-1). The end points of the resistor ladder are
The Resistor Network is made up of several parts.
connected to analog switches, which are connected to
These include:
the device Terminal A and Terminal B pins. The R
AB
• Resistor Ladder (and R ) resistance has small variations over voltage
S
• Wiper
and temperature.
• Shutdown (Terminal Connections)
For an 8-bit device, there are 256 resistors in a string
Devices have either one or two resistor networks,
between terminal A and terminal B. The wiper can be
These are referred to as Pot 0 and Pot 1.  set to tap onto any of these 256 resistors, thus provid-
ing 257 possible settings (including terminal A and ter-

|     | A   |     |     |     | minal B).  |     |     |     |     |
| --- | --- | --- | --- | --- | ---------- | --- | --- | --- | --- |
For a 7-bit device, there are 128 resistors in a string
8-Bit 7-Bit
N =  N =  between terminal A and terminal B. The wiper can be
256  128  set to tap onto any of these 128 resistors, thus provid-
(100h)  (80h)  ing 129 possible settings (including terminal A and ter-
R  (1)
| R   |   W |     |     |     | minal B).  |     |     |     |     |
| --- | --- | --- | --- | --- | ---------- | --- | --- | --- | --- |
S
|     |     |     |     |     | Equation5-1  | shows  | the  | calculation  | for  the  step |
| --- | --- | --- | --- | --- | ------------ | ------ | ---- | ------------ | -------------- |
|     |     | 255 | 127 |     |              |        |      |              |                |
resistance.
(FFh)  (7Fh)
R  (1)
| R   | S   W |     |     |     |               |     |                |     |     |
| --- | ----- | --- | --- | --- | ------------- | --- | -------------- | --- | --- |
|     |       | 254 |     |     | EQUATION 5-1: |     | R  CALCULATION |     |     |
|     |       |     | 126 |     |               |     | S              |     |     |
(FEh)  (7Eh)
 (1)
|     | R W |     |     |     |     |         | R                 |              |     |
| --- | --- | --- | --- | --- | --- | ------- | ----------------- | ------------ | --- |
| R   | S   |     |     |     |     | R = --- | --- A --- - B --- | 8-bit Device |     |
| R   |     |     |     |     |     | S      | 2 5 6            |              |     |
AB
W
R
R = -------A---B----
|     |     |     |     |     |     | S     |     | 7-bit Device |     |
| --- | --- | --- | --- | --- | --- | ----- | --- | ------------ | --- |
|     |     | 1   | 1   |     |     | 128 |     |              |     |
(01h)
|     |  (1)  |     | (01h)  |     |     |     |     |     |     |
| --- | ----- | --- | ------ | --- | --- | --- | --- | --- | --- |
| R   |   R W |     |        |     |     |     |     |     |     |
S
|     |     | 0   | 0   |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
(00h)  (00h)
R  (1)
W
Analog Mux
B
| Note1:The  | wiper    | resistance                    | is  dependent  | on    |     |     |     |     |     |
| ---------- | -------- | ----------------------------- | -------------- | ----- | --- | --- | --- | --- | --- |
|            | several  | factors  including,           | wiper          | code, |     |     |     |     |     |
|            | device V | , Terminal voltages (on A, B, |                |       |     |     |     |     |     |
DD
and W), and temperature.
Also for the same conditions, each tap
selection resistance has a small variation.
This R W  variation has greater effects on
some specifications (such as INL) for the
|     | smaller   | resistance  | devices     | (5.0k) |     |     |     |     |     |
| --- | --------- | ----------- | ----------- | ------- | --- | --- | --- | --- | --- |
|     | compared  | to  larger  | resistance  | devices |     |     |     |     |     |
(100.0k).
| FIGURE 5-1:                           |     | Resistor Block Diagram. |     |     |     |     |     |                  |     |
| ------------------------------------- | --- | ----------------------- | --- | --- | --- | --- | --- | ---------------- | --- |
|  2008-2013 Microchip Technology Inc. |     |                         |     |     |     |     |     | DS22096B-page 39 |     |

MCP453X/455X/463X/465X
| 5.2 Wiper |     |     |     | TABLE 5-1: | VOLATILE WIPER VALUE VS.  |     |
| --------- | --- | --- | --- | ---------- | ------------------------- | --- |
WIPER POSITION MAP
| Each  tap  | point  (between  | the  R   resistors)  | is  a |     |     |     |
| ---------- | ---------------- | -------------------- | ----- | --- | --- | --- |
S
| connection point for an analog switch. The opposite |     |     |     | Wiper Setting |     |     |
| --------------------------------------------------- | --- | --- | --- | ------------- | --- | --- |
side of the analog switch is connected to a common Properties
|     |     |     |     | 7-bit Pot | 8-bit Pot |     |
| --- | --- | --- | --- | --------- | --------- | --- |
signal, which is connected to the Terminal W (Wiper)
| pin.  |     |     |     | 3FFh | 3FFh Reserved (Full-Scale (W = A)), |     |
| ----- | --- | --- | --- | ---- | ----------------------------------- | --- |
|       |     |     |     | 081h | 101h Increment and Decrement        |     |
A value in the Volatile Wiper register selects which
commands ignored
analog switch to close, connecting the W terminal to
the selected node of the resistor ladder.  080h 100h Full-Scale (W = A),
Increment commands ignored
The wiper can connect directly to Terminal B or to
Terminal A. A zero-scale connection, connects the Ter- 07Fh 0FFh W = N
|     |     |     |     | 041h | 081 |     |
| --- | --- | --- | --- | ---- | --- | --- |
minal W (wiper) to Terminal B (wiper setting of 000h). A
full-scale connection, connects the Terminal W (wiper) 040h 080h W = N (Mid-Scale)
to Terminal A (wiper setting of 100h or 80h). In these
|     |     |     |     | 03Fh | 07Fh W = N |     |
| --- | --- | --- | --- | ---- | ---------- | --- |
configurations, the only resistance between Terminal W
|     |     |     |     | 001h | 001 |     |
| --- | --- | --- | --- | ---- | --- | --- |
and the other Terminal (A or B) is that of the analog
|     |     |     |     | 000h | 000h Zero Scale (W = B) |     |
| --- | --- | --- | --- | ---- | ----------------------- | --- |
switches.
Decrement command ignored
A wiper setting value greater than full-scale (wiper

setting of 100h for 8-bit device or 80h for 7-bit devices)
will also be a Full-Scale setting (Terminal W (wiper) A POR/BOR event will load the Volatile Wiper register
connected to Terminal A). Table5-1 illustrates the full value  with  the  default  value.  Table5-2  shows  the
wiper setting map. default values offered. Custom POR/BOR options are
Equation5-2 illustrates the calculation used to deter- available. Contact the local Microchip Sales Office.
mine the resistance between the wiper and terminal B. TABLE 5-2: DEFAULT FACTORY
SETTINGS SELECTION
| EQUATION 5-2: | R  CALCULATION |     |     |            |                            |            |
| ------------- | -------------- | --- | --- | ---------- | -------------------------- | ---------- |
|               | WB             |     |     |            |  ROP tluafeD gnitteS repiW |            |
|               |                |     |     | ecnatsiseR | eulaV                      | Wiper Code |
 lacipyT
|     | R AB N             |              |     | edoC |     |             |
| --- | ------------------ | ------------ | --- | ---- | --- | ----------- |
| R   | = --------------+R | 8-bit Device |     |      |     |             |
| WB  | 256 W            |              |     |      |     |             |
|     |                    |              |     |      | BA  | 8-bit 7-bit |
N = 0 to 256 (decimal)
R
|                        | R N                      |              |     | -502 | 5.0 k Mid-scale                      | 80h 40h |
| ---------------------- | ------------------------ | ------------ | --- | ---- | ------------------------------------- | ------- |
| R                      | = ----- A --- B ------+R | 7-bit Device |     |      |                                       |         |
| WB                     | 128 W                  |              |     |      |                                       |         |
|                        |                          |              |     | -103 | 10.0 k Mid-scale                     | 80h 40h |
| N = 0 to 128 (decimal) |                          |              |     | -503 | 50.0 k Mid-scale                     | 80h 40h |
|                        |                          |              |     | -104 | 100.0 k Mid-scale                    | 80h 40h |
| DS22096B-page 40       |                          |              |     |      |  2008-2013 Microchip Technology Inc. |         |

MCP453X/455X/463X/465X
5.3 Shutdown 5.3.2 INTERACTION OF RxHW BIT AND
RxA, RxW, AND RxB BITS (TCON
Shutdown is used to minimize the device’s current
REGISTER)
consumption. The MCP4XXX achieves this through the
Terminal Control Register (TCON). Using the TCON bits allows each resistor network
(Pot0 and Pot1) to be individually “shutdown”.
5.3.1 TERMINAL CONTROL REGISTER
The state of the RxHW bit does NOT corrupt the other
(TCON)
bit values in the TCON register, nor the value of the
The Terminal Control (TCON) register is a volatile Volatile Wiper registers. When the Shutdown mode is
register used to configure the connection of each exited (RxHW changes state from “0” to “1”):
resistor network terminal pin (A, B, and W) to the
• The device returns to the Wiper setting specified
Resistor Network. This bits are described in
by the Volatile Wiper value
Register4-1.
• The RxA, RxB, and RxW bits return to controlling
When the RxHW bit is a “0”, the selected resistor net- the terminal connection state of that resistor net-
work is forced into the following state: work
• The PxA terminal is disconnected
• The PxW terminal is simultaneously connected to
the PxB terminal (see Figure5-2)
• The Serial Interface is NOT disabled, and all
Serial Interface activity is executed
Alternate low power configurations may be achieved
with the RxA, RxW, and RxB bits.
Note1: The RxHW bits are identical to the RxHW
bits of the MCP41XX/42XX devices. The
MCP42XX devices also have a SHDN pin
which forces the resistor network into the
same state as that resistor networks
RxHW bit.
2: When RxHW = “0”, the state of the TCON
register RxA, RxW, and RxB bits is over-
ridden (ignored). When the state of the
RxHW bit returns to “1”, the TCON
register RxA, RxW, and RxB bits return to
controlling the terminal connection state.
In other words, the RxHW bit does not
corrupt the state of the RxA, RxW, and
RxB bits.
A
W
B
FIGURE 5-2: Resistor Network Shutdown
Configuration.
 2008-2013 Microchip Technology Inc. DS22096B-page 41
krowteN
rotsiseR

MCP453X/455X/463X/465X
NOTES:
DS22096B-page 42  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
| 6.0 SERIAL INTERFACE (I2C)  |     |     | 6.1 | Signal Descriptions |     |     |
| --------------------------- | --- | --- | --- | ------------------- | --- | --- |
The MCP45XX/46XX devices support the I2C serial The I2C interface uses up to five pins (signals). These
| protocol. The MCP45XX/46XX I2C’s module operates        |     |     | are:                 |     |     |     |
| ------------------------------------------------------- | --- | --- | -------------------- | --- | --- | --- |
| in Slave mode (does not generate the serial clock).     |     |     | • SDA (Serial Data)  |     |     |     |
| Figure6-1 shows a typical I2C Interface connection. All |     |     | • SCL (Serial Clock) |     |     |     |
I2C interface signals are high-voltage tolerant.
• A0 (Address 0 bit)
| The MCP45XX/46XX devices use the two-wire I2C |     |     | • A1 (Address 1 bit) |     |     |     |
| --------------------------------------------- | --- | --- | -------------------- | --- | --- | --- |
• A2 (Address 2 bit)
serial interface. This interface can operate in standard,
fast or High-Speed mode. A device that sends data
|     |     |     | 6.1.1 | SERIAL DATA  (SDA) |     |     |
| --- | --- | --- | ----- | ------------------ | --- | --- |
onto the bus is defined as transmitter, and a device
The Serial Data (SDA) signal is the data signal of the
receiving data, as receiver. The bus has to be con-
device. The value on this pin is latched on the rising
trolled by a master device which generates the serial
clock (SCL), controls the bus access and generates the edge of the SCL signal when the signal is an input.
START and STOP conditions. The MCP45XX/46XX
With the exception of the START and STOP conditions,
device works as slave. Both master and slave can
the High or Low state of the SDA pin can only change
operate  as  transmitter  or  receiver,  but  the  master when the clock signal on the SCL pin is LOW. During
device determines which mode is activated. Communi- the high period of the clock the SDA pin’s value (high or
cation is initiated by the master (microcontroller) which low) must be stable. Changes in the SDA pin’s value
sends the START bit, followed by the slave address
while the SCL pin is HIGH will be interpreted as a
byte. The first byte transmitted is always the slave
START or a STOP condition.
address byte, which contains the device code, the
| address bits, and the R/W bit.  |     |     | 6.1.2 | SERIAL CLOCK (SCL)  |     |     |
| ------------------------------- | --- | --- | ----- | ------------------- | --- | --- |
Refer to the Phillips I2C document for more details of
The Serial Clock (SCL) signal is the clock signal of the
the I2C specifications. device. The rising edge of the SCL signal latches the
value on the SDA pin. The MCP45XX/46XX supports

three I2C interface clock modes:
Typical I2C Interface Connections
• Standard mode: clock rates up to 100kHz
| Host |     | MCP4XXX |     |     |     |     |
| ---- | --- | ------- | --- | --- | --- | --- |
• Fast mode: clock rates up to 400kHz
Controller
• High-Speed mode (HS mode): clock rates up to
| SCL |     | SCL  |     |     |     |     |
| --- | --- | ---- | --- | --- | --- | --- |
3.4MHz
| SDA |     | SDA  | The MCP4XXX will not stretch the clock signal (SCL) |     |     |     |
| --- | --- | ---- | --------------------------------------------------- | --- | --- | --- |
since memory read accesses occur fast enough.
| I/O (1)  |     | HVC/A0 (2)  |     |     |     |     |
| -------- | --- | ----------- | --- | --- | --- | --- |
Depending on the clock rate mode, the interface will
A1 (2, 3)
display different characteristics.
A2 (2, 3)
|     |     |     | 6.1.3 | THE ADDRESS BITS (A2:A1:A0) |     |     |
| --- | --- | --- | ----- | --------------------------- | --- | --- |
There are up to three hardware pins used to specify the
Note1: If High voltage commands are desired,
|     |     |     | device  | address.  The  number  | of  address  | pins  is |
| --- | --- | --- | ------- | ---------------------- | ------------ | -------- |
some type of external circuitry needs to
determined by the part number.
be implemented.
|           |                       |               | Address  | 0  is  multiplexed  | with  the  High  | Voltage |
| --------- | --------------------- | ------------- | -------- | ------------------- | ---------------- | ------- |
| 2: These  | pins  have  internal  | pull-ups.  If |          |                     |                  |         |
Command (HVC) function. So the state of A0 is latched
| faster  | rise  times  are  | required,  then |     |     |     |     |
| ------- | ----------------- | --------------- | --- | --- | --- | --- |
on the MCP4XXX’s POR/BOR event.
external pull-ups should be added.
The state of the A2 and A1 pins should be static, that is
| 3: This  | pin  could  be  tied  | high,  low,  or |     |     |     |     |
| -------- | --------------------- | --------------- | --- | --- | --- | --- |
they should be tied high or tied low.
| connected  | to  an  I/O  | pin  of  the  Host |     |     |     |     |
| ---------- | ------------ | ------------------ | --- | --- | --- | --- |
Controller.
|     |                              |     | 6.1.3.1 | The High Voltage Command (HVC)  |     |     |
| --- | ---------------------------- | --- | ------- | ------------------------------- | --- | --- |
|     | Typical I2C Interface Block  |     |         | Signal                          |     |     |
FIGURE 6-1:
| Diagram. |     |     | The High Voltage Command (HVC) signal is multi- |     |     |     |
| -------- | --- | --- | ----------------------------------------------- | --- | --- | --- |
plexed with Address 0 (A0) and is used to indicate that
the command, or sequence of commands, are in the
High Voltage mode. High Voltage commands are sup-
ported for compatibility with the nonvolatile devices.
The HVC pin has an internal resistor connection to the
|     |     |     | MCP45XX/46XXs internal V |     |  signal. |     |
| --- | --- | --- | ------------------------ | --- | -------- | --- |
DD
|  2008-2013 Microchip Technology Inc. |     |     |     |     | DS22096B-page 43 |     |
| ------------------------------------- | --- | --- | --- | --- | ---------------- | --- |

MCP453X/455X/463X/465X
| 6.2 I2C Operation |     |     | 6.2.1.3 | Acknowledge (A) Bit |     |
| ----------------- | --- | --- | ------- | ------------------- | --- |
The A bit (see Figure6-4) is typically a response from
The MCP45XX/46XX’s  I2C module is compatible with
the Philips I2C specification. The following lists some of the  receiving  device  to  the  transmitting  device.
the module’s features: Depending on the context of the transfer sequence, the
A bit may indicate different things. Typically, the Slave
• 7-bit slave addressing
device will supply an A response after the Start bit and
• Supports three clock rate modes: 8 “data” bits have been received. The A bit has the SDA
- Standard mode, clock rates up to 100kHz
signal low.
- Fast mode, clock rates up to 400kHz
| - High-speed mode (HS mode), clock rates up  |     |     |        |     |     |
| -------------------------------------------- | --- | --- | ------ | --- | --- |
to 3.4MHz
|     |     |     | SDA | D0  | A   |
| --- | --- | --- | --- | --- | --- |
• Support Multi-Master Applications
| • General call addressing  |     |     | SCL |     |     |
| -------------------------- | --- | --- | --- | --- | --- |
|                            |     |     |     | 8   | 9   |
• Internal weak pull-ups on interface signals
The I2C 10-bit addressing mode is not supported.
|     |     |     | FIGURE 6-4: | Acknowledge Waveform. |     |
| --- | --- | --- | ----------- | --------------------- | --- |
The Philips I2C specification only defines the field
types, field lengths, timings, etc. of a frame. The frame
Not A (A) Response
content defines the behavior of the device. The frame
content for the MCP4XXX is defined in Section7.0. The A bit has the SDA signal HIGH. Table6-1 shows
some of the conditions where the Slave Device will
I2C BIT STATES AND SEQUENCE
| 6.2.1 |     |     | issue a Not A (A).  |     |     |
| ----- | --- | --- | ------------------- | --- | --- |
Figure6-8 shows the I2C transfer sequence. The serial
If an error condition occurs (such as an A instead of A),
clock  is  generated  by  the  master.  The  following then  an  START  bit  must  be  issued  to  reset  the
definitions are used for the bit states: command state machine.
• Start bit (S)
| • Data bit   |     |     | TABLE 6-1: | MCP45XX/46XX A / A  |     |
| ------------ | --- | --- | ---------- | ------------------- | --- |
RESPONSES
• Acknowledge (A) bit (driven low) /
No Acknowledge (A) bit (not driven low)
Acknowledge
• Repeated Start bit (Sr)
|     |     |     | Event | Bit  | Comment |
| --- | --- | --- | ----- | ---- | ------- |
• Stop bit (P)
Response
| 6.2.1.1 Start Bit                                        |     |     |              |     |                      |
| -------------------------------------------------------- | --- | --- | ------------ | --- | -------------------- |
|                                                          |     |     | General Call | A   | Only if GCEN bit is  |
| The Start bit (see Figure6-2) indicates the beginning of |     |     |              |     | set                  |
a data transfer sequence. The Start bit is defined as the Slave Address  A
| SDA signal falling when the SCL signal is HIGH. |     |     | valid          |     |     |
| ----------------------------------------------- | --- | --- | -------------- | --- | --- |
|                                                 |     |     | Slave Address  | A   |     |
not valid
| SDA | 1st Bit | 2nd Bit |              |     |                   |
| --- | ------- | ------- | ------------ | --- | ----------------- |
|     |         |         | Device mem-  | A   | After device has  |
|     |         |         | ory address  |     | received address  |
SCL
|     |     |     | and specified  |     | and command  |
| --- | --- | --- | -------------- | --- | ------------ |
S
command
| FIGURE 6-2: | Start Bit. |     | (AD3:AD0 and  |     |     |
| ----------- | ---------- | --- | ------------- | --- | --- |
C1:C0)  are an
| 6.2.1.2 Data Bit |     |     |     |     |     |
| ---------------- | --- | --- | --- | --- | --- |
invalid combi-
| The SDA signal may change state while the SCL signal |     |     | nation |     |     |
| ---------------------------------------------------- | --- | --- | ------ | --- | --- |
is LOW. While the SCL signal is HIGH, the SDA signal I2C Module
|                                 |     |     | Bus Collision | N.A. |                      |
| ------------------------------- | --- | --- | ------------- | ---- | -------------------- |
| MUST be stable (see Figure6-5). |     |     |               |      | Resets, or a “Don’t  |
Care” if the colli-

sion occurs on the
|     | 1st Bit | 2nd Bit |     |     |                      |
| --- | ------- | ------- | --- | --- | -------------------- |
| SDA |         |         |     |     | Masters “Start bit”. |
SCL
Data Bit
| FIGURE 6-3:      | Data Bit. |     |     |                                       |     |
| ---------------- | --------- | --- | --- | ------------------------------------- | --- |
| DS22096B-page 44 |           |     |     |  2008-2013 Microchip Technology Inc. |     |

MCP453X/455X/463X/465X
| 6.2.1.4 | Repeated Start Bit |     |     | 6.2.1.5 | Stop Bit |     |
| ------- | ------------------ | --- | --- | ------- | -------- | --- |
The Repeated Start bit (see Figure6-5) indicates the The Stop bit (see Figure6-6) Indicates the end of the
I2C Data Transfer Sequence. The Stop bit is defined as
current Master Device wishes to continue communicat-
ing with the current Slave Device without releasing the the SDA signal rising when the SCL signal is HIGH.
I2C bus. The Repeated Start condition is the same as A Stop bit resets the I2C interface of all MCP4XXX
the Start condition, except that the Repeated Start bit
devices.
follows a Start bit (with the Data bits + A bit) and not a

Stop bit.
| The  Start  | bit  is  | the  beginning  | of  a  data  transfer | SDA A / A |     |     |
| ----------- | -------- | --------------- | --------------------- | --------- | --- | --- |
sequence and is defined as the SDA signal falling when
| the SCL signal is HIGH. |     |     |     | SCL |     |     |
| ----------------------- | --- | --- | --- | --- | --- | --- |

P
| Note1: | A bus collision during the Repeated Start |     |     |                |     |                            |
| ------ | ----------------------------------------- | --- | --- | -------------- | --- | -------------------------- |
|        | condition occurs if:                      |     |     | FIGURE 6-6:    |     | Stop Condition Receive or  |
|        | •SDA is sampled low when SCL goes         |     |     | Transmit Mode. |     |                            |
from low to high.
|     |     |     |     | 6.2.2 | CLOCK STRETCHING |     |
| --- | --- | --- | --- | ----- | ---------------- | --- |
•SCL goes low before SDA is asserted
|     |     |     |     | “Clock  Stretching”  |     | is  something  that  the  receiving |
| --- | --- | --- | --- | -------------------- | --- | ----------------------------------- |
low. This may indicate that another
device can do, to allow additional time to “respond” to
master is attempting to transmit a
the “data” that has been received.
data"1".
The MCP4XXX will not stretch the clock signal (SCL)

since memory read accesses occur fast enough.
| SDA |     |     | 1st Bit | 6.2.3 | ABORTING A TRANSMISSION |     |
| --- | --- | --- | ------- | ----- | ----------------------- | --- |
If any part of the I2C transmission does not meet the
command format, it is aborted. This can be intentionally
accomplished with a START or STOP condition. This is
SCL
done so that noisy transmissions (usually an extra
START or STOP condition) are aborted before they
Sr = Repeated Start
corrupt the device.
| FIGURE 6-5: |     | Repeat Start Condition  |     |     |     |     |
| ----------- | --- | ----------------------- | --- | --- | --- | --- |
Waveform.

SDA
SCL
S 1st Bit 2nd Bit 3rd Bit 4th Bit 5th Bit 6th Bit 7th Bit 8th Bit A / A P
Typical 8-Bit I2C Waveform Format.
FIGURE 6-7:

SDA
SCL
|     |     | START     | Data allowed | Data or |     | STOP      |
| --- | --- | --------- | ------------ | ------- | --- | --------- |
|     |     | Condition | to change    | A valid |     | Condition |
I2C Data States and Bit Sequence.
FIGURE 6-8:
 2008-2013 Microchip Technology Inc. DS22096B-page 45

MCP453X/455X/463X/465X
6.2.4 ADDRESSING
Slave Address
The address byte is the first byte received following the
START condition from the master device. The address S A6 A5 A4 A3 A2 A1 A0 R/W A/A
contains four (or more) fixed bits and (up to) three user “0”“1” “0”“1”
defined hardware address bits (pins A2, A1, and A0). See Table6-2
These 7-bits address the desired I2C device. The
Start R/W bit
A7:A4 address bits are fixed to “0101” and the device bit R/W = 0 = write
appends the value of following three address pins (A2,
R/W = 1 = read
A1, A0). Address pins that are not present on the
A bit (controlled by slave device)
device are pulled up (a bit value of ‘1’).
A = 0 = Slave Device Acknowledges byte
Since there are up to three address bits controlled by
A = 1 = Slave Device does not Acknowledge byte
hardware pins, there may be up to eight MCP4XXX
devices on the same I2C bus. FIGURE 6-9: Slave Address Bits in the
I2C Control Byte.
Figure6-9 shows the slave address byte format, which
contains the seven address bits. There is also a read/ TABLE 6-2: DEVICE SLAVE ADDRESSES
write bit. Table6-2 shows the fixed address for each
Device Address Comment
device.
MCP45X1 ‘0101 11’b + A0 Supports up to 2
devices. (Note1)
Hardware Address Pins
MCP45X2 ‘0101 1’b + A1:A0 Supports up to 4
The hardware address bits (A2, A1, and A0) devices. (Note1)
correspond to the logic level on the associated address MCP46X1 ‘0101’b + A2:A1:A0 Supports up to 8
pins. This allows up to eight devices on the bus. devices. (Note1)
These pins have a weak pull-up enabled when the MCP46X2 ‘0101 1’b + A1:A0 Supports up to 4
V <V . The weak pull-up utilizes the “smart” devices. (Note1)
DD BOR
pull-up technology and exhibits the same characteris- Note 1: A0 is used for High-Voltage commands,
tics as the High-voltage tolerant I/O structure. and the value is latched at POR.
The state of the A0 address pin is latch on POR/BOR.
6.2.5 SLOPE CONTROL
This is required since High-Voltage commands force
this pin (HVC/A0) to the V level. The MCP45XX/46XX implements slope control on the
IHH
SDA output.
As the device transitions from HS mode to FS mode,
the slope control parameter will change from the HS
specification to the FS specification.
For Fast (FS) and High-Speed (HS) modes, the device
has a spike suppression and a Schmidt trigger at SDA
and SCL inputs.
DS22096B-page 46  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
6.2.6 HS MODE After  switching  to  the  High-Speed  mode,  the  next
transferred byte is the I2C control byte, which specifies
The I2C specification requires that a high-speed mode
the device to communicate with, and any number of
device must be ‘activated’ to operate in High-Speed
|     |     | data  bytes  | plus  acknowledgements.  | The  Master |
| --- | --- | ------------ | ------------------------ | ----------- |
(3.4Mbit/s) mode. This is done by the Master sending
Device can then either issue a Repeated Start bit to
a special address byte following the START bit. This
address a different device (at High-Speed), or a Stop bit
byte is referred to as the high-speed Master Mode
to return to Fast/Standard bus speed. After the Stop bit,
Code (HSMMC).
any other Master Device (in a Multi-Master system) can
The MCP45XX/46XX device does not acknowledge arbitrate for the I2C bus.
this byte. However, upon receiving this command, the
See Figure6-10 for illustration of HS mode command
device switches to HS mode. The device can now com-
sequence.
municate at up to 3.4Mbit/s on SDA and SCL lines.
The device will switch out of the HS mode on the next For more information on the HS mode, or other I2C
STOP condition. modes, please refer to the Phillips I2C specification.
The master code is sent as follows:
|     |     | 6.2.6.1 | Slope Control |     |
| --- | --- | ------- | ------------- | --- |
1. START condition (S)
|     |     | The  slope  | control  on  the  SDA  | output  is  different |
| --- | --- | ----------- | ---------------------- | --------------------- |
2. High-Speed Master Mode Code (0000 1XXX),
between the Fast/Standard Speed and the High-Speed
The XXX bits are unique to the high-speed (HS)
clock modes of the interface.
mode Master.
| 3. No Acknowledge (A) |     | 6.2.6.2 | Pulse Gobbler |     |
| --------------------- | --- | ------- | ------------- | --- |
The pulse gobbler on the SCL pin is automatically
adjusted to suppress spikes < 10ns during HS mode.

| F/S-mode | HS-mode |     |     |     |
| -------- | ------- | --- | --- | --- |
P
F/S-mode
| S                   | Sr‘Slave Address’R/W |          |     |     |
| ------------------- | -------------------- | -------- | --- | --- |
| ‘0 0 0 0  1 X X X’b | A                    | A “Data” | A/A |     |
HS-mode continues
|                |              |                      | Sr‘Slave Address’R/W | A   |
| -------------- | ------------ | -------------------- | -------------------- | --- |
| HS Select Byte | Control Byte | Command/Data Byte(s) |                      |     |
| S = Start bit  |              |                      | Control Byte         |     |
Sr = Repeated Start bit
A = Acknowledge bit
A = Not Acknowledge bit
R/W = Read/Write bit
P = Stop bit (Stop condition terminates HS Mode)
| FIGURE 6-10: HS Mode Sequence.        |     |     |     |                  |
| ------------------------------------- | --- | --- | --- | ---------------- |
|  2008-2013 Microchip Technology Inc. |     |     |     | DS22096B-page 47 |

MCP453X/455X/463X/465X
| 6.2.7 | GENERAL CALL  |     | TABLE 6-3: | GENERAL CALL COMMANDS     |
| ----- | ------------- | --- | ---------- | ------------------------- |
The General Call is a method that the “Master” device
7-bit
(1, 2, 3)  Comment
| can communicate with all other “Slave” devices. In a |     |     | Command  |     |
| ---------------------------------------------------- | --- | --- | -------- | --- |
Multi-Master application, the other Master devices are
|     |     |     | ‘1000 00d’b  | Write Next Byte (Third Byte) to  |
| --- | --- | --- | ------------ | -------------------------------- |
operating in Slave mode. The General Call address
has two documented formats. These are shown in Volatile Wiper 0 Register
Figure6-11. We have added a MCP45XX/46XX format
|                         |     |     | ‘1001 00d’b  | Write Next Byte (Third Byte) to  |
| ----------------------- | --- | --- | ------------ | -------------------------------- |
| in this figure as well. |     |     |              | Volatile Wiper 1 Register        |
This will allow customers to have multiple I2C Digital
|     |     |     | ‘1100 00d’b  | Write Next Byte (Third Byte) to  |
| --- | --- | --- | ------------ | -------------------------------- |
Potentiometers on the bus and have them operate in a TCON Register
synchronous fashion (analogous to the DAC Sync pin
|                  |                          |             | ‘1000 010’b  | Increment Wiper 0 Register |
| ---------------- | ------------------------ | ----------- | ------------ | -------------------------- |
| functionality).  | If  these  MCP45XX/46XX  | 7-bit  com- |              |                            |
or
mands conflict with other I2C devices on the bus, then
‘1000 011’b
the customer will need two I2C busses and ensure that
|     |     |     | ‘1001 010’b  | Increment Wiper 1 Register |
| --- | --- | --- | ------------ | -------------------------- |
the devices are on the correct bus for their desired
| application functionality. |     |     | or  |     |
| -------------------------- | --- | --- | --- | --- |
‘1001 011’b
Dual Pot devices cannot update both Pot0 and Pot1
from a single command. To address this, there are ‘1000 100’b  Decrement Wiper 0 Register
| General Call commands for the Wiper 0, Wiper 1, and |     |     | or  |     |
| --------------------------------------------------- | --- | --- | --- | --- |
‘1000 101’b
the TCON registers.
|     |     |     | ‘1001 100’b  | Decrement Wiper 1 Register |
| --- | --- | --- | ------------ | -------------------------- |
Table6-3 shows the General Call commands. Three
| commands are specified by the I2C specification and |                     |                   | or                                           |     |
| --------------------------------------------------- | ------------------- | ----------------- | -------------------------------------------- | --- |
| are not applicable to the MCP45XX/46XX (so com-     |                     |                   | ‘1001 101’b                                  |     |
| mand  is                                            | Not  Acknowledged)  | The  MCP45XX/46XX |                                              |     |
|                                                     |                     |                   | Note 1: Any other code is Not Acknowledged.  |     |
General Call commands are Acknowledge. Any other
These codes may be used by other
| command is Not Acknowledged. |                                        |     | devices on the I2C bus.                    |     |
| ---------------------------- | -------------------------------------- | --- | ------------------------------------------ | --- |
|                              |                                        |     | 2: The 7-bit command always appends a “0”  |     |
| Note:                        | There is only one General Call command |     |                                            |     |
to form 8-bits. .
per General Call control byte (address).
|     |     |     | 3: “d” is the D8 bit for the 9-bit write value. |     |
| --- | --- | --- | ----------------------------------------------- | --- |
Any additional General Call commands
are ignored and Not Acknowledged.
| DS22096B-page 48 |     |     |     |  2008-2013 Microchip Technology Inc. |
| ---------------- | --- | --- | --- | ------------------------------------- |

MCP453X/455X/463X/465X

Second Byte
| S 0 0                | 0 0 0 0 | 0 0 A X          | X X X X | X X 0 A | P   |     |     |
| -------------------- | ------- | ---------------- | ------- | ------- | --- | --- | --- |
| General Call Address |         | “7-bit Command”  |         |         |     |     |     |
Reserved 7-bit Commands (By I2C Specification - Philips # 9398 393 40011, Ver. 2.1 January 2000)
‘0000 011’b - Reset and write programmable part of slave address by hardware.
‘0000 010’b - Write programmable part of slave address by hardware.
‘0000 000’b - NOT Allowed
MCP45XX/MCP46XX 7-bit Commands
‘1000 01x’b - Increment Wiper 0 Register.
‘1001 01x’b - Increment Wiper 1 Register.
‘1000 10x’b - Decrement Wiper 0 Register.
‘1001 10x’b - Decrement Wiper 1 Register.
The Following is a Microchip Extension to this General Call Format
|       |         |         | Second Byte |         | Third Byte |         |     |
| ----- | ------- | ------- | ----------- | ------- | ---------- | ------- | --- |
| S 0 0 | 0 0 0 0 | 0 0 A X | X X X X     | X d 0 A | d d d d    | d d d d | A P |
General Call Address “7-bit Command”   “0” for General Call Command
MCP45XX/MCP46XX 7-bit Commands
‘1000 00d’b - Write Next Byte (Third Byte) to Volatile Wiper 0 Register.
‘1001 00d’b - Write Next Byte (Third Byte) to Volatile Wiper 1 Register.
‘1100 00d’b - Write Next Byte (Third Byte) to TCON Register.
The Following is a “Hardware General Call” Format
|                      |         |                  | Second Byte |         | n occurrences of (Data + A) |         |     |
| -------------------- | ------- | ---------------- | ----------- | ------- | --------------------------- | ------- | --- |
| S 0 0                | 0 0 0 0 | 0 0 A X          | X X X X     | X X 1 A | X X X X                     | X X X X | A P |
| General Call Address |         | “7-bit Command”  |             |         |                             |         |     |
This indicates a “Hardware General Call”
MCP45XX/MCP46XX will ignore this byte and
all following bytes (and A), until
a Stop bit (P) is encountered.
| FIGURE 6-11:                          | General Call Formats. |     |     |     |     |                  |     |
| ------------------------------------- | --------------------- | --- | --- | --- | --- | ---------------- | --- |
|  2008-2013 Microchip Technology Inc. |                       |     |     |     |     | DS22096B-page 49 |     |

MCP453X/455X/463X/465X
NOTES:
DS22096B-page 50  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
| 7.0 DEVICE COMMANDS |     |     | 7.1 Command Byte |     |     |
| ------------------- | --- | --- | ---------------- | --- | --- |
The MCP4XXX’s I2C command formats are specified in The MCP4XXX’s Command Byte has three fields: the
this section. The I2C protocol does not specify how Address, the Command Operation, and two data bits,
(see Figure7-1). Currently only one of the data bits is
commands are formatted.
defined (D8).
| The  MCP4XXX  | supports  | four  basic  commands. |     |     |     |
| ------------- | --------- | ---------------------- | --- | --- | --- |
Depending on the location accessed determines the The device memory is accessed when the Master
commands that are supported.  sends a proper Command Byte to select the desired
operation. The memory location getting accessed is
For the Volatile Wiper registers, these commands are:
contained in the Command Byte’s AD3:AD0 bits. The
• Write Data action desired is contained in the Command Byte’s
• Read Data C1:C0 bits (see Table7-1). C1:C0 determines if the
• Increment Data desired  memory  location  will  be  read,  written,
Incremented (wiper setting +1) or Decremented (wiper
• Decrement Data
setting -1). The Increment and Decrement commands
For the TCON Register, these commands are: are only valid on the volatile wiper registers.
• Write Data If the Address bits and Command bits are not a valid
• Read Data
combination, then the MCP4XXX will generate a Not
These  commands  have  formats  for  both  a  single Acknowledge pulse to indicate the invalid combination.
The I2C Master device must then force a Start Condi-
command or continuous commands. These commands
tion to reset the MCP4XXX’s 2C module.
are shown in Table7-1.
D9 and D8 are the most significant bits for the digital
Each command has two operational states. These
potentiometer’s wiper setting. The 8-bit devices utilize
operational states are referred to as:
D8 as their MSb while the 7-bit devices utilize D7 (from
• Normal Serial Commands
the data byte) as it’s MSb.
• High-Voltage Serial Commands

| Note: | High Voltage commands are supported |     |     | COMMAND BYTE |     |
| ----- | ----------------------------------- | --- | --- | ------------ | --- |
for compatibility with nonvolatile devices
in the family.
|     |     |     | A A A | A A C C | D D A |
| --- | --- | --- | ----- | ------- | ----- |
|     |     |     | D D   | D D 1 0 | 9 8   |
I2C COMMANDS
| TABLE 7-1: |     |     | 3 2 | 1 0 |     |
| ---------- | --- | --- | --- | --- | --- |
Command Operates on
|     |     |     | MCP4XXX  |     | MSbits (Data) |
| --- | --- | --- | -------- | --- | ------------- |
# of Bit  Volatile/
Memory Address
Clocks  (1)  Nonvolatile
| Operation | Mode |     |     |     |     |
| --------- | ---- | --- | --- | --- | --- |
Command Operation bits
Memory
00 = Write Data
| Write Data | Single     | 29 Both                |     | 01 = Increment  |     |
| ---------- | ---------- | ---------------------- | --- | --------------- | --- |
|            | Continuous | 18n + 11 Volatile Only |     | 10 = Decrement  |     |
11 = Read Data
| Read Data  | Single                                 | 29 Both               |             |                      |     |
| ---------- | -------------------------------------- | --------------------- | ----------- | -------------------- | --- |
|            | Random                                 | 48 Both               | FIGURE 7-1: | Command Byte Format. |     |
|            | Continuous                             | 18n + 11 Both         |             |                      |     |
| Increment  | Single                                 | 20 Volatile Only      |             |                      |     |
|            | Continuous                             | 9n + 11 Volatile Only |             |                      |     |
| Decrement  | Single                                 | 20 Volatile Only      |             |                      |     |
|            | Continuous                             | 9n + 11 Volatile Only |             |                      |     |
| Note 1:    | “n” indicates the number of times the  |                       |             |                      |     |
command operation is to be repeated.
Normal serial commands are those where the HVC pin
| is driven to V                    | IH  or V IL . With High-Voltage Serial Com- |                 |     |     |     |
| --------------------------------- | ------------------------------------------- | --------------- | --- | --- | --- |
| mands, the HVC pin is driven to V |                                             | . In each mode, |     |     |     |
IHH
there are four possible commands.
Table7-2 shows the supported commands for each
memory location.
Table7-3 shows an overview of all the device com-
mands and their interaction with other device features.
|  2008-2013 Microchip Technology Inc. |     |     |     |     | DS22096B-page 51 |
| ------------------------------------- | --- | --- | --- | --- | ---------------- |

MCP453X/455X/463X/465X
| TABLE 7-2: | MEMORY MAP AND THE SUPPORTED COMMANDS     |     |      |
| ---------- | ----------------------------------------- | --- | ---- |
|            | Address                                   |     | Data |
Command Operation (1) Comment
(10-bits)
| Value | Function          |            |              |
| ----- | ----------------- | ---------- | ------------ |
| 00h   | Volatile Wiper 0  | Write Data | nn nnnn nnnn |
(3)
|     |                   | Read Data       | nn nnnn nnnn |
| --- | ----------------- | --------------- | ------------ |
|     |                   | Increment Wiper | —            |
|     |                   | Decrement Wiper | —            |
| 01h | Volatile Wiper 1  | Write Data      | nn nnnn nnnn |
(3)
|     |           | Read Data       | nn nnnn nnnn |
| --- | --------- | --------------- | ------------ |
|     |           | Increment Wiper | —            |
|     |           | Decrement Wiper | —            |
| 02h | Reserved  | —               | —            |
| 03h | Reserved  | —               | —            |
(2)
| 04h  | Volatile TCON Register | Write  Data | nn nnnn nnnn |
| ---- | ---------------------- | ----------- | ------------ |
(3)
|     |     | Read Data  | nn nnnn nnnn |
| --- | --- | ---------- | ------------ |
(2)  (3)
05h  Reserved  Read Data    nn nnnn nnnn Maps to nonvolatile
MCP45XX/46XX device’s
STATUS Register
| 06h - 0Fh  | (2)  Reserved                                                              | —   | —   |
| ---------- | -------------------------------------------------------------------------- | --- | --- |
| Note 1:    | The Data memory is only 9-bits wide, so the MSb is ignored by the device.  |     |     |
| 2:         | Increment or Decrement commands are invalid for these addresses.           |     |     |
I2C read operation will read 2 bytes, of which the 10-bits of data are contained within.
3:
DS22096B-page 52  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
7.2 Data Byte 7.3 Error Condition
Only the Read Command and the Write Command If the four address bits received (AD3:AD0) and the two
have Data Byte(s).  command bits received (C1:C0) are a valid combina-
tion, the MCP4XXX will Acknowledge the I2C bus.
The Write command concatenates the 8-bits of the
Data Byte with the one data bit (D8) contained in the If the address bits and command bits are an invalid
Command Byte to form 9-bits of data (D8:D0). The combination, then the MCP4XXX will Not Acknowledge
the I2C bus.
Command Byte format supports up to 9-bits of data so
that the 8-bit resistor network can be set to Full-Scale
Once an error condition has occurred, any following
(100h or greater). This allows wiper connections to
commands are ignored until the I2C bus is reset with a
Terminal A and to TerminalB. The D9 bit is currently
Start Condition.
unused.
7.3.1 ABORTING A TRANSMISSION
A Restart or Stop condition in the expected data bit
position will abort the current command sequence and
data will not be written to the MCP4XXX.
TABLE 7-3: COMMANDS
High
Voltage
Command Name # of Bits
|     |     | (V ) on  |
| --- | --- | -------- |
IHH
HVC pin?
| Write Data                            | 29               | —   |
| ------------------------------------- | ---------------- | --- |
| Read Data                             | 29               | —   |
| Increment Wiper                       | 20               | —   |
| Decrement Wiper                       | 20               | —   |
| High Voltage Write Data               | 29               | Yes |
| High Voltage Read Data                | 29               | Yes |
| High Voltage Increment Wiper          | 20               | Yes |
| High Voltage Decrement Wiper          | 20               | Yes |
|  2008-2013 Microchip Technology Inc. | DS22096B-page 53 |     |

MCP453X/455X/463X/465X
| 7.4 | Write Data              |     |     | 7.4.2 | CONTINUOUS WRITES TO  |     |     |
| --- | ----------------------- | --- | --- | ----- | --------------------- | --- | --- |
|     | Normal and High Voltage |     |     |       | VOLATILE MEMORY       |     |     |
A continuous write mode of operation is possible when
The Write command can be issued to both the volatile
writing to the volatile memory registers (address 00h,
and nonvolatile memory locations. The format of the
01h, and 04h). This continuous write mode allows
command (see Figure7-2), includes the I2C Control
writes without a Stop or Restart condition or repeated
Byte, an A bit, the MCP4XXX Command Byte, an A bit,
I2C
the MCP4XXX Data Byte, an A bit, and a Stop (or transmissions  of  the  Control  Byte.  Figure7-3
shows the sequence for three continuous writes. The
Restart) condition. The MCP4XXX generates the A/A
writes do not need to be to the same volatile memory
bits.
address. The sequence ends with the master sending
A  Write  command  to  a  volatile  memory  location a STOP or RESTART condition.
changes that location after a properly formatted Write
Command and the A/A clock have been received. 7.4.3 THE HIGH VOLTAGE COMMAND
(HVC) SIGNAL
| 7.4.1 | SINGLE WRITE TO VOLATILE  |     |     |            |                   |        |            |
| ----- | ------------------------- | --- | --- | ---------- | ----------------- | ------ | ---------- |
|       |                           |     |     | The  High  | Voltage  Command  | (HVC)  | signal  is |
MEMORY
multiplexed with Address 0 (A0) and is used to indicate
For volatile memory locations, data is written to the that the command, or sequence of commands, are in
| MCP4XXX  | after  every  | byte  transfer  | (during  the |            |                       |               |         |
| -------- | ------------- | --------------- | ------------ | ---------- | --------------------- | ------------- | ------- |
|          |               |                 |              | the  High  | Voltage  operational  | state.  High  | Voltage |
Acknowledge). If a Stop or Restart condition is gener-
commands allow the device’s WiperLock Technology
ated during a data transfer (before the A), the data will
and write protect features to be enabled and disabled.
not be written to the MCP4XXX. After the A bit, the
The HVC pin has an internal resistor connection to the
master can initiate the next sequence with a Stop or
|                     |     |     |     | MCP45XX/46XXs internal V |     |  signal. |     |
| ------------------- | --- | --- | --- | ------------------------ | --- | -------- | --- |
| Restart condition.  |     |     |     |                          | DD  |          |     |
Refer to Figure7-2 for the byte write sequence.
| DS22096B-page 54 |     |     |     |     |  2008-2013 Microchip Technology Inc. |     |     |
| ---------------- | --- | --- | --- | --- | ------------------------------------- | --- | --- |

MCP453X/455X/463X/465X

|     |         |           | Write bit | Device |         |     |                   |     |     |
| --- | ------- | --------- | --------- | ------ | ------- | --- | ----------------- | --- | --- |
|     | Fixed   | Variable  |           | Memory |         |     |                   |     |     |
|     | Address | Address   |           |        | Command |     | Write “Data” bits |     |     |
Address
ADADADAD
| S 0         | 1 0          | 1 A2 A1             | A0 0 A |               | 0 0 x | D8 A | D7 D6D5         | D4 D3 D2 D1D0 | A P |
| ----------- | ------------ | ------------------- | ------ | ------------- | ----- | ---- | --------------- | ------------- | --- |
|             |              |                     |        | 3 2 1         | 0     |      |                 |               |     |
|             | Control Byte |                     |        | WRITE Command |       |      | Write Data bits |               |     |
| FIGURE 7-2: |              | I2C Write Sequence. |        |               |       |      |                 |               |     |

|     |         |           | Write bit | Device   |         |     |                   |     |     |
| --- | ------- | --------- | --------- | -------- | ------- | --- | ----------------- | --- | --- |
|     | Fixed   | Variable  |           | Memory   |         |     |                   |     |     |
|     | Address | Address   |           | Address  | Command |     | Write “Data” bits |     |     |
ADADADAD
| S 0 | 1 0          | 1 A2 | A1 A0 0 | A             | 0 0 x | D8 AD7 | D6D5            | D4 D3 D2 D1D0 | A   |
| --- | ------------ | ---- | ------- | ------------- | ----- | ------ | --------------- | ------------- | --- |
|     |              |      |         | 3 2 1         | 0     |        |                 |               |     |
|     | Control Byte |      |         | WRITE Command |       |        | Write Data bits |               |     |
ADADADAD
|     | 3   | 2 1           | 0 0 0 | x D8 A D7D6 | D5 D4 D3        | D2D1D0 | A   |     |     |
| --- | --- | ------------- | ----- | ----------- | --------------- | ------ | --- | --- | --- |
|     |     | WRITE Command |       |             | Write Data bits |        |     |     |     |
STOP bit
ADADADAD
|     |     |     |               | 0 0 | x D8 A D7 D6D5 | D4              | D3 D2 | D1D0 A P |     |
| --- | --- | --- | ------------- | --- | -------------- | --------------- | ----- | -------- | --- |
|     |     |     | 3 2 1         | 0   |                |                 |       |          |     |
|     |     |     | WRITE Command |     |                | Write Data bits |       |          |     |
Note: Only functions when writing the volatile wiper registers (AD3:AD0 = 00h, 01h, and 04h)
or the TCON register.
I2C Continuous Volatile Wiper Write.
FIGURE 7-3:
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     | DS22096B-page 55 |     |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | ---------------- | --- |

MCP453X/455X/463X/465X
7.5 Read Data 7.5.1 SINGLE READ
Normal and High Voltage
Figure7-4 shows the waveforms for a single read.
The Read command can be issued to both the volatile For single reads, the master sends a STOP or
and nonvolatile memory locations. The format of the RESTART condition after the data byte is sent from the
command (see Figure7-4) includes the Start condi- slave.
tion, I2C Control Byte (with R/W bit set to “0”), A bit,
7.5.1.1 Random Read
MCP4XXX Command Byte, A bit, followed by a
Repeated Start bit, I2C Control Byte (with R/W bit set to Figure7-5 shows the sequence for a Random Reads.
“1”), and the MCP4XXX transmitting the requested
Refer to Figure7-5 for the random byte read
Data High Byte, A bit, the Data Low Byte, the Master
sequence.
generating the A, and Stop condition.
The I2C Control Byte requires the R/W bit equal to a 7.5.2 CONTINUOUS READS
logic one (R/W = 1) to generate a read sequence. The
Continuous reads allow the device’s memory to be
memory location read will be the last address
read quickly. Continuous reads are possible to all mem-
contained in a valid write MCP4XXX Command Byte or
ory locations. If a nonvolatile memory write cycle is
address 00h, if no write operations have occurred since
occurring, then Read commands may only access the
the device was reset (Power-on Reset or Brown-out
volatile memory locations.
Reset).
Figure7-6 shows the sequence for three continuous
Read operations initially include the same address byte
reads.
sequence as the write sequence (shown in Figure6-9).
This sequence is followed by another control byte For continuous reads, instead of transmitting a STOP
(including the Start condition and Acknowledge) with or RESTART condition after the data transfer, the mas-
the R/W bit equal to a logic one (R/W = 1) to indicate a ter reads the next data byte. The sequence ends with
read. The MCP4XXX will then transmit the data con- the master Not Acknowledging and then sending a
tained in the addressed register. This is followed by the STOP or RESTART.
master generating an A bit in preparation for more data,
7.5.3 THE HIGH VOLTAGE COMMAND
or an A bit followed by a Stop. The sequence is ended
(HVC) SIGNAL
with the master generating a Stop or Restart condition.
The internal address pointer is maintained. The High Voltage Command (HVC) signal is
multiplexed with Address 0 (A0) and is used to indicate
that the command, or sequence of commands, are in
the High Voltage mode. High Voltage commands allow
the device’s WiperLock Technology, and write protect
features to be enabled and disabled.
The HVC pin has an internal resistor connection to the
MCP4XXXs internal V signal.
DD
7.5.4 IGNORING AN I2C TRANSMISSION AND
“FALLING OFF” THE BUS
The MCP4XXX expects to receive entire, valid I2C
commands, and will assume any command not
defined as a valid command is due to a bus corruption,
and will enter a passive high condition on the SDA sig-
nal. All signals will be ignored until the next valid Start
condition and Control Byte are received.
DS22096B-page 56  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X

Read bit
STOP bit
| Fixed   | Variable  |     |     |                |
| ------- | --------- | --- | --- | -------------- |
| Address | Address   |     |     | Read Data bits |
S 0 1 0 1 A2 A1 A0 1 A 0 0 0 0 0 0 0 D8 A1D7 D6 D5 D4D3 D2 D1D0 A2 P
| Control Byte |     |     |     | Read bits |
| ------------ | --- | --- | --- | --------- |
Note1: Master Device is responsible for A/A signal. If an A signal occurs, the MCP45XX/46XX will
abort this transfer and release the bus.
2: The Master Device will Not Acknowledge, and the MCP45XX/46XX will release the bus so the
Master Device can generate a Stop or Repeated Start condition.
3: The MCP45XX/46XX retains the last “Device Memory Address” that it has received. This is
the MCP45XX/46XX does not “corrupt” the “Device Memory Address” after Repeated Start or
Stop conditions.
4: The Device Memory Address pointer defaults to 00h on POR and BOR conditions.
I2C Read (Last Memory Address Accessed).
FIGURE 7-4:

|     |     | Write bit |     | Repeated Start bit |
| --- | --- | --------- | --- | ------------------ |
Device
| Fixed  | Variable  |     |     |     |
| ------ | --------- | --- | --- | --- |
Memory
| Address | Address | Address  | Command |     |
| ------- | ------- | -------- | ------- | --- |
ADADADAD
| S 0 1 | 0 1 A2 A1    | A0 0 A 3 | 2 1 0 1      | 1 x X A Sr |
| ----- | ------------ | -------- | ------------ | ---------- |
|       | Control Byte |          | READ Command |            |
STOP bit
|     |     | Read bit |     | Read Data bits |
| --- | --- | -------- | --- | -------------- |
0 1 0 1 A2 A1 A0 1 A 0 0 0 0 0 0 0 D8 A1 D7 D6D5 D4 D3 D2 D1D0 A2 P
| Control Byte |     |     |     | Read bits |
| ------------ | --- | --- | --- | --------- |
Note1: Master Device is responsible for A / A signal. If a A signal occurs, the MCP45XX/46XX will
abort this transfer and release the bus.
2: The Master Device will Not Acknowledge, and the MCP45XX/46XX will release the bus so the
Master Device can generate a Stop or Repeated Start condition.
3: The MCP45XX/46XX retains the last “Device Memory Address” that it has received. This is
the MCP45XX/46XX does not “corrupt” the “Device Memory Address” after Repeated Start or
Stop conditions.
I2C Random Read.
FIGURE 7-5:
 2008-2013 Microchip Technology Inc. DS22096B-page 57

MCP453X/455X/463X/465X

Read bit
| Fixed   | Variable     |         |     |       |       |                |       |           |     |
| ------- | ------------ | ------- | --- | ----- | ----- | -------------- | ----- | --------- | --- |
| Address | Address      |         |     |       |       | Read Data bits |       |           |     |
|         |              |         |     |       |       | A1D7D6         |       |           | A1  |
| S 0 1   | 0 1 A2       | A1 A0 1 | A 0 | 0 0 0 | 0 0 0 | D8             | D5 D4 | D3 D2D1D0 |     |
|         | Control Byte |         |     |       |       | Read bits      |       |           |     |
Read Data bits
|     |     | 0 0 | 0 0 | 0 0 0 | D8 A1D7D6 | D5 D4 | D3 D2D1D0 | A1  |     |
| --- | --- | --- | --- | ----- | --------- | ----- | --------- | --- | --- |
STOP bit
Read Data bits
|     |     |     | 0   | 0 0 0 0 | 0 0 | D8 A1 D7 | D6 D5 D4D3 | D2 D1D0 | A2 P |
| --- | --- | --- | --- | ------- | --- | -------- | ---------- | ------- | ---- |
Note1: Master Device is responsible for A / A signal. If a A signal occurs, the MCP45XX/46XX will
abort this transfer and release the bus.
2: The Master Device will Not Acknowledge, and the MCP45XX/46XX will release the bus so the
Master Device can generate a Stop or Repeated Start condition.
I2C Continuous Reads.
FIGURE 7-6:
| DS22096B-page 58 |     |     |     |     |     |     |  2008-2013 Microchip Technology Inc. |     |     |
| ---------------- | --- | --- | --- | --- | --- | --- | ------------------------------------- | --- | --- |

MCP453X/455X/463X/465X
| 7.6                                             | Increment Wiper         |     |     |     | TABLE 7-4:     |         | INCREMENT OPERATION VS.  |            |
| ----------------------------------------------- | ----------------------- | --- | --- | --- | -------------- | ------- | ------------------------ | ---------- |
|                                                 | Normal and High Voltage |     |     |     |                |         | VOLATILE WIPER VALUE     |            |
| The Increment Command provides a quick and easy |                         |     |     |     | Current Wiper  |         |                          |            |
|                                                 |                         |     |     |     |                | Setting |                          | Increment  |
method to modify the potentiometer’s wiper by +1 with Wiper (W)
Command
| minimal overhead. The Increment Command will only |     |     |     |     |        |        | Properties |           |
| ------------------------------------------------- | --- | --- | --- | --- | ------ | ------ | ---------- | --------- |
|                                                   |     |     |     |     | 7-bit  | 8-bit  |            | Operates? |
function on the volatile wiper setting memory locations
|     |     |     |     |     |     | Pot  Pot  |     |     |
| --- | --- | --- | --- | --- | --- | --------- | --- | --- |
00h and 01h.
|     |     |     |     |     | 3FFh | 3FFh | Reserved  | No  |
| --- | --- | --- | --- | --- | ---- | ---- | --------- | --- |

|       |                                        |     |     |     | 081h | 101h | (Full-Scale (W = A))  |     |
| ----- | -------------------------------------- | --- | --- | --- | ---- | ---- | --------------------- | --- |
| Note: | Table7-2 shows the valid addresses for |     |     |     |      |      |                       |     |
the  Increment  Wiper  command.  Other 080h 100h Full-Scale (W = A) No
addresses are invalid.
|                                                   |     |     |     |     | 07Fh | 0FFh | W = N |     |
| ------------------------------------------------- | --- | --- | --- | --- | ---- | ---- | ----- | --- |
| When executing an Increment Command, the volatile |     |     |     |     | 041h | 081  |       |     |
wiper setting will be altered from n to n+1 for each
|     |     |     |     |     | 040h | 080h | W = N (Mid-Scale) | Yes |
| --- | --- | --- | --- | --- | ---- | ---- | ----------------- | --- |
Increment Command received. The value will incre-
|     |     |     |     |     | 03Fh | 07Fh | W = N |     |
| --- | --- | --- | --- | --- | ---- | ---- | ----- | --- |
ment up to 100h maximum on 8-bit devices, and 80h on
|     |     |     |     |     | 001h | 001 |     |     |
| --- | --- | --- | --- | --- | ---- | --- | --- | --- |
7-bit devices. If multiple Increment Commands are
received after the value has reached 100h (or 80h), the 000h 000h Zero Scale (W = B) Yes
value will not be incremented further. Table7-4 shows
the Increment Command versus the current volatile
| wiper value. |     |     |     |     | 7.6.1 | THE HIGH VOLTAGE COMMAND  |     |     |
| ------------ | --- | --- | --- | --- | ----- | ------------------------- | --- | --- |
(HVC) SIGNAL
| Refer  | to  Figure7-7  | for  the  | Increment  | Command |     |     |     |     |
| ------ | -------------- | --------- | ---------- | ------- | --- | --- | --- | --- |
sequence. The sequence is terminated by the Stop The High Voltage Command (HVC) signal is multi-
condition. So when executing a continuous command
plexed with Address 0 (A0) and is used to indicate that
string, the Increment command can be followed by any
the command, or sequence of commands, are in the
other valid command. This means that writes do not
High Voltage mode. An HVC/A0 pin voltage > V
IHH
need to be to the same volatile memory address. (~8.5V) puts the MCP45XX/46XX device into the High
Voltage mode.

| Note: | The command sequence can go from an |     |     |     |     |     |     |     |
| ----- | ----------------------------------- | --- | --- | --- | --- | --- | --- | --- |

increment to any other valid command for
|     |     |     |     |     | Note: | There is a required delay after the HVC pin |     |     |
| --- | --- | --- | --- | --- | ----- | ------------------------------------------- | --- | --- |
the specified address.
|     |     |     |     |     |     | is driven to the V |  level to the 1st edge |     |
| --- | --- | --- | --- | --- | --- | ------------------ | ---------------------- | --- |
IHH
The  advantage  of  using  an  Increment  Command of the SCL pin.
instead of a read-modify-write series of commands is
The HVC pin has an internal resistor connection to the
speed and simplicity. The wiper will transition after MCP45XX/46XXs internal V  signal.
DD
each Command Acknowledge when accessing the vol-
atile wiper registers.

|     |        |           | Write bit | Device |     |     |     |     |
| --- | ------ | --------- | --------- | ------ | --- | --- | --- | --- |
|     | Fixed  | Variable  |           |        |     |     |     |     |
Memory
|     | Address | Address |        | Address            | Command |          |                    |             |
| --- | ------- | ------- | ------ | ------------------ | ------- | -------- | ------------------ | ----------- |
|     |         |         |        | ADADADAD           |         | ADADADAD |                    |             |
|     | S 0 1 0 | 1 A2 A1 | A0 0 A |                    | 0 1 x   | X A      | 0 1 x              | X A P  (2)  |
|     |         |         |        | 3 2 1              | 0       | 4        | 3 2 1              |             |
|     |         |         |        | INCR Command (n+1) |         |          | INCR Command (n+2) |             |
Control Byte
Note1: Increment Command (INCR) only functions when accessing the volatile wiper
registers (AD3:AD0 = 0h and 1h).
2: This command sequence does not need to terminate (using the Stop bit) and can
change to any other desired command sequence (Increment, Read or Write).
| FIGURE 7-7:                           |     | I2C Increment Command Sequence. |     |     |     |     |     |                  |
| ------------------------------------- | --- | ------------------------------- | --- | --- | --- | --- | --- | ---------------- |
|  2008-2013 Microchip Technology Inc. |     |                                 |     |     |     |     |     | DS22096B-page 59 |

MCP453X/455X/463X/465X
| 7.7                                             | Decrement Wiper         |     |     |     |     | TABLE 7-5:     | DECREMENT OPERATION VS.  |     |            |
| ----------------------------------------------- | ----------------------- | --- | --- | --- | --- | -------------- | ------------------------ | --- | ---------- |
|                                                 | Normal and High Voltage |     |     |     |     |                | VOLATILE WIPER VALUE     |     |            |
| The Decrement Command provides a quick and easy |                         |     |     |     |     | Current Wiper  |                          |     |            |
|                                                 |                         |     |     |     |     | Setting        |                          |     | Decrement  |
method to modify the potentiometer’s wiper by -1, with Wiper (W)
Command
| minimal overhead. The Decrement Command will only |     |     |     |     |     |        |        | Properties |           |
| ------------------------------------------------- | --- | --- | --- | --- | --- | ------ | ------ | ---------- | --------- |
|                                                   |     |     |     |     |     | 7-bit  | 8-bit  |            | Operates? |
function on the volatile wiper setting memory locations
|     |     |     |     |     |     | Pot  | Pot  |     |     |
| --- | --- | --- | --- | --- | --- | ---- | ---- | --- | --- |
00h and 01h.
|       |                                        |     |     |     |     | 3FFh | 3FFh Reserved              |     | No  |
| ----- | -------------------------------------- | --- | --- | --- | --- | ---- | -------------------------- | --- | --- |
|       |                                        |     |     |     |     | 081h | 101h (Full-Scale (W = A))  |     |     |
| Note: | Table7-2 shows the valid addresses for |     |     |     |     |      |                            |     |     |
the Decrement Wiper command.  Other 080h 100h Full-Scale (W = A) Yes
addresses are invalid.
|                                                  |     |     |     |     |     | 07Fh | 0FFh W = N |     |     |
| ------------------------------------------------ | --- | --- | --- | --- | --- | ---- | ---------- | --- | --- |
| When executing a Decrement Command, the volatile |     |     |     |     |     | 041h | 081        |     |     |
wiper setting will be altered from n to n-1 for each
|            |          |            |      |             |     | 040h | 080h W = N (Mid-Scale) |     | Yes |
| ---------- | -------- | ---------- | ---- | ----------- | --- | ---- | ---------------------- | --- | --- |
| Decrement  | Command  | received.  | The  | value  will |     |      |                        |     |     |
|            |          |            |      |             |     | 03Fh | 07Fh W = N             |     |     |
decrement down to a minimum of 000h. If multiple Dec-
|     |     |     |     |     |     | 001h | 001 |     |     |
| --- | --- | --- | --- | --- | --- | ---- | --- | --- | --- |
rement Commands are received after the value has
reached 000h, the value will not be decremented fur- 000h 000h Zero Scale (W = B) No
ther. Table7-5 shows the Increment Command versus
the current volatile wiper value.
Refer  to  Figure7-8  for  the  Decrement  Command 7.7.1 THE HIGH VOLTAGE COMMAND
(HVC) SIGNAL
sequence. The sequence is terminated by the Stop
condition. So when executing a continuous command The  High  Voltage  Command  (HVC)  signal  is
string, The Increment command can be followed by any
multiplexed with Address 0 (A0) and is used to indicate
other valid command. this means that writes do not
that the command, or sequence of commands, are in
need to be to the same volatile memory address.
the High Voltage mode. An HVC/A0 pin voltage > V
IHH
(~8.5V) puts the MCP45XX/46XX device into the High

| Note: | The command sequence can go from an |     |     |     |     | Voltage mode.  |     |     |     |
| ----- | ----------------------------------- | --- | --- | --- | --- | -------------- | --- | --- | --- |
increment to any other valid command for

the specified address.
|     |     |     |     |     |     | Note: | There is a required delay after the HVC pin |     |     |
| --- | --- | --- | --- | --- | --- | ----- | ------------------------------------------- | --- | --- |
The  advantage  of  using  a  Decrement  Command is driven to the V  level to the 1st edge
IHH
instead of a read-modify-write series of commands is of the SCL pin.
speed and simplicity. The wiper will transition after each
The HVC pin has an internal resistor connection to the
Command Acknowledge when accessing the volatile MCP45XX/46XXs internal V  signal.
DD
wiper registers.

Write bit Device
|     | Fixed   | Variable     |        | Memory             |         |         |                    |       |             |
| --- | ------- | ------------ | ------ | ------------------ | ------- | ------- | ------------------ | ----- | ----------- |
|     | Address | Address      |        | Address            | Command |         |                    |       |             |
|     |         |              |        | ADADADAD           |         |         | ADADADAD           |       |             |
|     | S 0 1   | 0 1 A2 A1    | A0 0 A |                    | 1       | 0 X X A |                    | 1 0 X | X A P  (2)  |
|     |         |              |        | 3 2 1              | 0       |         | 4 3 2              | 1     |             |
|     |         | Control Byte |        | DECR Command (n-1) |         |         | DECR Command (n-2) |       |             |
Note1: Decrement Command (DECR) only functions when accessing the volatile wiper
registers (AD3:AD0 = 0h and 1h).
2: This command sequence does not need to terminate (using the Stop bit) and can
change to any other desired command sequence (INCR, Read, or Write).
I2C Decrement Command Sequence.
FIGURE 7-8:
| DS22096B-page 60 |     |     |     |     |     |     |  2008-2013 Microchip Technology Inc. |     |     |
| ---------------- | --- | --- | --- | --- | --- | --- | ------------------------------------- | --- | --- |

MCP453X/455X/463X/465X
8.0 APPLICATIONS EXAMPLES The circuit in Figure8-2 shows the method used on the
MCP402X nonvolatile Digital Potentiometer Evaluation
Nonvolatile digital potentiometers have a multitude of
|     |     |     | Board  (Part  | Number:  MCP402XEV).  | This  method |
| --- | --- | --- | ------------- | --------------------- | ------------ |
practical uses in modern electronic circuits. The most
requires that the system voltage be approximately 5V.
popular uses include precision calibration of set point This  ensures  that  when  the  PIC10F206  enters  a
thresholds, sensor trimming, LCD bias trimming, audio brown-out condition, there is an insufficient voltage
attenuation, adjustable power supplies, motor control level on the HVC pin to change the stored value of the
overcurrent trip setting, adjustable gain amplifiers and
wiper. The MCP402X nonvolatile Digital Potentiometer
| offset  trimming.  | The  MCP453X/455X/463X/465X |     |     |     |     |
| ------------------ | --------------------------- | --- | --- | --- | --- |
Evaluation Board User’s Guide (DS51546) contains a
| devices can be used to replace the common mechani- |     |     | complete schematic. |     |     |
| -------------------------------------------------- | --- | --- | ------------------- | --- | --- |
cal trim pot in applications where the operating and
GP0 is a general purpose I/O pin, while GP2 can either
terminal voltages are within CMOS process limitations
be a general purpose I/O pin or it can output the internal
(V = 2.7V to 5.5V).
| DD  |     |     | clock. |     |     |
| --- | --- | --- | ------ | --- | --- |
For the serial commands, configure the GP2 pin as an
8.1 Techniques to force the HVC pin
to V   input (high impedance). The output state of the GP0 pin
IHH
|     |     |     | will determine the voltage on the HVC pin (V |     |  or V ).  |
| --- | --- | --- | -------------------------------------------- | --- | --------- |
IL IH
The circuit in Figure8-1 shows a method using the
|     |     |     | For  high-voltage  | serial  commands,  | force  the  GP0 |
| --- | --- | --- | ------------------ | ------------------ | --------------- |
TC1240A doubling charge pump. When the SHDN pin
|     |     |     | output pin to output a high level (V |     | ), and configure |
| --- | --- | --- | ------------------------------------ | --- | ---------------- |
OH
is HIGH, the TC1240A is off, and the level on the HVC the GP2 pin to output the internal clock. This will form
pin is controlled by the PIC® microcontrollers (MCUs)
a charge pump and increase the voltage on the HVC
IO2 pin.
pin (when the system voltage is approximately 5V).
When the SHDN pin is low, the TC1240A is on and the

| V  voltage is 2*V | . The resistor R |  allows the |     |     |     |
| ----------------- | ---------------- | ----------- | --- | --- | --- |
| OUT               | DD               | 1           |     |     |     |
HVC pin to go higher than the voltage such that the PIC PIC10F206 R
1
GP0
| MCU’s IO2 pin “clamps” at approximately V |     | DD . |     |     |          |
| ----------------------------------------- | --- | ---- | --- | --- | -------- |
|                                           |     |      |     |     | MCP4XXX  |
TC1240A
C+
| PIC MCU | V IN   | C   |     | GP2  | HVC  |
| ------- | ------ | --- | --- | ---- | ---- |
1
|     | SHDN C- |     |     |       |     |
| --- | ------- | --- | --- | ----- | --- |
|     |         |     |     | C 1   | C   |
2
|     | V OUT   |     |     |     |     |
| --- | ------- | --- | --- | --- | --- |
IO1
|                |                       | MCP45XX  | FIGURE 8-2:                                 | MCP4XXX Nonvolatile  |     |
| -------------- | --------------------- | -------- | ------------------------------------------- | -------------------- | --- |
|                | R                     | MCP46XX  | Digital Potentiometer Evaluation Board      |                      |     |
|                | 1 HVC                 |          |                                             |                      |     |
| IO2            |                       |          | (MCP402XEV) Implementation to Generate the  |                      |     |
|                | C                     |          | V  Voltage.                                 |                      |     |
|                | 2                     |          | IHH                                         |                      |     |
| FIGURE 8-1:    | Using the TC1240A to  |          |                                             |                      |     |
| Generate the V |  Voltage.             |          |                                             |                      |     |
IHH
|  2008-2013 Microchip Technology Inc. |     |     |     |     | DS22096B-page 61 |
| ------------------------------------- | --- | --- | --- | --- | ---------------- |

MCP453X/455X/463X/465X
8.2 Using Shutdown
S ‘1’ ‘1’ ‘1’ ‘1’ ‘1’ ‘1’ ‘1’ ‘1’ S P
Figure8-3 shows a possible application circuit where
the independent terminals could be used. Disconnect-
ing the wiper allows the transistor input to be taken to
Nine bits of ‘1’
the Bias voltage level (disconnecting A and or B may be
desired to reduce system current). Disconnecting Ter- Start bit
Start
minal A modifies the transistor input by the R
BW bit Stop bit
rheostat value to the Common B. Disconnecting
FIGURE 8-4: Software Reset Sequence
Terminal B modifies the transistor input by the R
AW
Format.
rheostat value to the Common A. The Common A and
Common B connections could be connected to V
DD The 1st Start bit will cause the device to reset from a
and V .
SS state in which it is expecting to receive data from the
Master Device. This occurs since the device is monitor-
ing the data bus in Receive mode and can detect the
Start bit which forces an internal Reset.
Common A
The nine bits of ‘1’ are used to force a Reset of those
devices that could not be reset by the previous Start bit.
This occurs only if the MCP45XX/46XX is driving an A
Input bit on the I2C bus, or is in output mode (from a Read
A command) and is driving a data bit of ‘0’ onto the I2C
bus. In both of these cases, the previous Start bit could
not be generated due to the MCP45XX/46XX holding
the bus low. By sending out nine ‘1’ bits, it is ensured
that the device will see an A bit (the Master Device
To base does not drive the I2C bus low to acknowledge the data
W
of Transistor
sent by the MCP45XX/46XX), which also forces the
(or Amplifier)
MCP45XX/46XX to reset.
The 2nd Start bit is sent to address the rare possibility
of an erroneous write. This could occur if the Master
Device was reset while sending a Write command to
B the MCP45XX/46XX, AND then as the Master Device
returns to normal operation and issues a Start condi-
Input
tion, while the MCP45XX/46XX is issuing an Acknowl-
edge. In this case, if the 2nd Start bit is not sent (and
the Stop bit was sent) the MCP45XX/46XX could initi-
Common B ate a write cycle.
Balance Bias Note: The potential for this erroneous write
ONLY occurs if the Master Device is reset
FIGURE 8-3: Example Application Circuit
while sending a Write command to the
using Terminal Disconnects.
MCP45XX/46XX.
The Stop bit terminates the current I2C bus activity. The
8.3 Software Reset Sequence
MCP45XX/46XX wait to detect the next Start condition.
Note: This technique is documented in AN1028. This sequence does not effect any other I2C devices
which may be on the bus, as they should disregard this
At times it may become necessary to perform a Soft-
as an invalid command.
ware Reset Sequence to ensure the MCP45XX/46XX
device is in a correct and known I2C Interface state.
This technique only resets the I2C state machine.
This is useful if the MCP45XX/46XX device powers up
in an incorrect state (due to excessive bus noise, ...), or
if the Master Device is reset during communication.
Figure8-4 shows the communication sequence to soft-
ware reset the device.
DS22096B-page 62  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
8.4 Using the General Call Command   Figure8-5 shows two I2C bus configurations. In many
|     |     |     |     |     |     |     |     | cases,  | the  | single  | I2C  | bus  configuration  | will  be |
| --- | --- | --- | --- | --- | --- | --- | --- | ------- | ---- | ------- | ---- | ------------------- | -------- |
The use of the General Call Address Increment, Decre-
adequate. For applications that do not want all the
ment, or Write commands is analogous to the “Load”
MCP45XX/46XX devices to do General Call support or
| feature  | (LDAC  | pin)  on  | some  | DACs  | (such  | as  the |     |       |              |       |          |                  |     |
| -------- | ------ | --------- | ----- | ----- | ------ | ------- | --- | ----- | ------------ | ----- | -------- | ---------------- | --- |
|          |        |           |       |       |        |         |     | have  | a  conflict  | with  | General  | Call  commands,  | the |
MCP4921). This allows all the devices to “Update” the multiple I2C bus configuration would be used.
output level “at the same time”.
For some applications, the ability to update the wiper
Single I2C Bus Configuration
values at the same time may be a requirement, since
they delay from writing to one wiper value and then the
next may cause application issues. A possible example Device 1 Device 3 Device n
| would be a “tuned” circuit that uses several MCP45XX/   |     |     |     |     |     |     |     |            | Host |     |     |     |     |
| ------------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | ---------- | ---- | --- | --- | --- | --- |
| 46XX in rheostat configuration. As the system condition |     |     |     |     |     |     |     | Controller |      |     |     |     |     |
changes (temperature, load, ...) these devices need to
Device 4
| be changed (incremented/decremented) to adjust for |     |     |     |     |     |     |     |     |     |     | Device 2 |     |     |
| -------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | -------- | --- | --- |
the system change. These changes will either be in the
Multiple I2C Bus Configuration
| same  | direction  | or  in  opposite  |     | directions.  |     | With  the |     |     |     |     |     |     |     |
| ----- | ---------- | ----------------- | --- | ------------ | --- | --------- | --- | --- | --- | --- | --- | --- | --- |
Potentiometer device, the customer can either select
the  PxB  terminals  (same  direction)  or  the  PxA Device 1a Device 3a Device na
terminal(s) (opposite direction).
|                                                      |         |               |     |             |      |      |     |            | Host | Bus a |     |     |     |
| ---------------------------------------------------- | ------- | ------------- | --- | ----------- | ---- | ---- | --- | ---------- | ---- | ----- | --- | --- | --- |
| Figure8-6 shows that the update of six devices takes |         |               |     |             |      |      |     | Controller |      |       |     |     |     |
| 6*T                                                  |   time  | in  “normal”  |     | operation,  | but  | only |     |            |      |       |     |     |     |
I2CDLY
|     |     |     |     |     |     |     |     |     |     | Device 2a |     | Device 4a |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --------- | --- | --------- | --- |
1*T I2CDLY  time in “General Call” operation.

| Note: | The  | application  | system  |     | may  need  | to  |     |     |     | Device 1b |     |                     |     |
| ----- | ---- | ------------ | ------- | --- | ---------- | --- | --- | --- | --- | --------- | --- | ------------------- | --- |
|       |      |              |         |     |            |     |     |     |     |           |     | Device 3b Device nb |     |
partition the I2C bus into multiple busses to
|     | ensure that the MCP45XX/46XX General |     |     |     |     |     |     |     | Bus b |     |     |     |     |
| --- | ------------------------------------ | --- | --- | --- | --- | --- | --- | --- | ----- | --- | --- | --- | --- |
Call commands do not conflict with the
General Call commands that the other I2C
|     |     |     |     |     |     |     |     |     |     | Device 2b |     | Device 4b |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --------- | --- | --------- | --- |
devices may have defined. Also if only a
portion of the MCP45XX/46XX devices are
|     |     |          |                    |     |            |     |     |     |     | Device 1n |     | Device 3n Device nn |     |
| --- | --- | -------- | ------------------ | --- | ---------- | --- | --- | --- | --- | --------- | --- | ------------------- | --- |
|     | to  | require  | this  synchronous  |     | operation, |     |     |     |     |           |     |                     |     |
Bus n
then the devices that should not receive
these commands should be on the second
|     | I2C bus. |     |     |     |     |     |     |     |     | Device 2n |     | Device 4n |     |
| --- | -------- | --- | --- | --- | --- | --- | --- | --- | --- | --------- | --- | --------- | --- |
Typical Application I2C Bus
FIGURE 8-5:
Configurations.
Normal Operation
|     |     | INC    |        | INC   |     | INC    |        | INC   |        | INC   |        | INC   |     |
| --- | --- | ------ | ------ | ----- | --- | ------ | ------ | ----- | ------ | ----- | ------ | ----- | --- |
|     |     | POT01  |        | POT02 |     | POT03  |        | POT04 |        | POT05 |        | POT06 |     |
|     |     | T      | T      |       | T   |        | T      |       | T      |       | T      |       |     |
|     |     | I2CDLY | I2CDLY |       |     | I2CDLY | I2CDLY |       | I2CDLY |       | I2CDLY |       |     |
General Call Operation
|     |     | INC        |        | INC        |     | INC        |        | INC        |        | INC        |        | INC        |     |
| --- | --- | ---------- | ------ | ---------- | --- | ---------- | ------ | ---------- | ------ | ---------- | ------ | ---------- | --- |
|     |     | POTs 01-06 |        | POTs 01-06 |     | POTs 01-06 |        | POTs 01-06 |        | POTs 01-06 |        | POTs 01-06 |     |
|     |     | T          | T      |            | T   |            | T      |            | T      |            | T      |            |     |
|     |     | I2CDLY     | I2CDLY |            |     | I2CDLY     | I2CDLY |            | I2CDLY |            | I2CDLY |            |     |
 = Time from one I2C command completed to completing the next I2C command.
T
I2CDLY
FIGURE 8-6: Example Comparison of “Normal Operation” vs. “General Call Operation” Wiper
Updates.
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     |     |     |     |     | DS22096B-page 63 |     |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---------------- | --- |

MCP453X/455X/463X/465X
8.5 Implementing Log Steps with a  EQUATION 8-1: dB CALCULATIONS
| Linear Digital Potentiometer  |     |     |     |     |     |     | (VOLTAGE)    |     |
| ----------------------------- | --- | --- | --- | --- | --- | --- | ------------ | --- |
V
In  audio  volume  control  applications,  the  use  of L = 20log  ------------- OUT
|                                                    |     |     |     |     |     |     | 10  | V  |
| -------------------------------------------------- | --- | --- | --- | --- | --- | --- | ---- | --- |
| logarithmic steps is desirable since the human ear |     |     |     |     |     |     |      | IN  |
hears in a logarithmic manner. The use of a linear
potentiometer can approximate a log potentiometer, dB V  / V  Ratio
OUT IN
| but  with  | fewer  steps.  | An  8-bit  | potentiometer  | can |     |     |         |     |
| ---------- | -------------- | ---------- | -------------- | --- | --- | --- | ------- | --- |
|            |                |            |                |     |     | -3  | 0.70795 |     |
achieve fourteen 3dB log steps plus a 100% (0dB)
|     |     |     |     |     |     | -2  | 0.79433 |     |
| --- | --- | --- | --- | --- | --- | --- | ------- | --- |
and a mute setting.
|            |           |                 |     |                  |     | -1  | 0.89125 |     |
| ---------- | --------- | --------------- | --- | ---------------- | --- | --- | ------- | --- |
| Figure8-7  | shows  a  | block  diagram  |     | of  one  of  the |     |     |         |     |
MCP45X1 resistor networks being used to attenuate an
input signal. In this case, the attenuation will be ground
|     |     |     |     |     | EQUATION 8-2: |     | dB CALCULATIONS  |     |
| --- | --- | --- | --- | --- | ------------- | --- | ---------------- | --- |
referenced. Terminal B can be connected to a common
(RESISTANCE) - CASE 1
mode voltage, but the voltages on the A, B and Wiper
Terminal B connected to Ground (see Figure8-7)
| terminals must not exceed the MCP45X1’s V |     |     |     | /V  |     |     |     |     |
| ----------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
DD SS
voltage limits.
R
|         |     |     |     |     |     | L   | = 20log |  ----B----W---  |
| ------- | --- | --- | --- | --- | --- | --- | -------- | ----------------- |
|         |     |     |     |     |     |     | 10R     |                  |
AB
MCP45X1
|     | P0A |     |     |     | EQUATION 8-3: |     | dB CALCULATIONS  |     |
| --- | --- | --- | --- | --- | ------------- | --- | ---------------- | --- |
(RESISTANCE) - CASE 2
|     |     | P0W |     |     |     | Terminal B through R |     |  to Ground |
| --- | --- | --- | --- | --- | --- | -------------------- | --- | ---------- |
B2GND
|     |     |      |     |     |     |            |  R                                           | +R  |
| --- | --- | ---- | --- | --- | --- | ---------- | --------------------------------------------- | ---- |
|     |     | P0B  |     |     |     | L = 20log | ----B----W--------------B----2--G----N----D-- |      |
|     |     |      |     |     |     |            | 10                                           | R   |
AB
Table8-1 shows the codes that can be used for 8-bit
| FIGURE 8-7: |     | Signal Attenuation Block  |     |     |     |     |     |     |
| ----------- | --- | ------------------------- | --- | --- | --- | --- | --- | --- |
Diagram - Ground Referenced. digital potentiometers to implement the log attenuation.
The table shows the wiper codes for -3dB, -2dB and
Equation8-1 shows the equation to calculate voltage -1dB attenuation steps. This table also shows the
dB  gain  ratios  for  the  digital  potentiometer,  while calculated attenuation based on the wiper code’s linear
Equation8-2  shows  the  equation  to  calculate step.  Calculated  attenuation  values  less  than  the
resistance dB gain ratios. These two equations assume
desired attenuation are shown with red text. At lower
that the B terminal is connected to ground.
wiper code values, the attenuation may skip a step; if
If terminal B is not directly resistively connected to this  occurs  the  next  attenuation  value  is  colored
magenta to highlight that a skip occurred. For example,
| ground,  then  | this  terminal  | B   | to  ground  | resistance |     |     |     |     |
| -------------- | --------------- | --- | ----------- | ---------- | --- | --- | --- | --- |
in the -3dB column the -48dB value is highlighted
| (R )  | must  be  | included  | into  the  | calculation. |     |     |     |     |
| ----- | --------- | --------- | ---------- | ------------ | --- | --- | --- | --- |
B2GND
Equation8-3 shows this equation. since the -45dB step could not be implemented (there
are no wiper codes between 2 and 1).
| DS22096B-page 64 |     |     |     |     |     |     |  2008-2013 Microchip Technology Inc. |     |
| ---------------- | --- | --- | --- | --- | --- | --- | ------------------------------------- | --- |

MCP453X/455X/463X/465X
TABLE 8-1: LINEAR TO LOG ATTENUATION FOR 8-BIT DIGITAL POTENTIOMETERS
|     |     | -3dB Steps |     |     |     | -2dB Steps  |     |     |     | -1dB Steps  |     |     |
| --- | --- | ---------- | --- | --- | --- | ----------- | --- | --- | --- | ----------- | --- | --- |
# of
|       |             |     |              | Calculated  |             |     |              | Calculated  | Desired    |     |              | Calculated  |
| ----- | ----------- | --- | ------------ | ----------- | ----------- | --- | ------------ | ----------- | ---------- | --- | ------------ | ----------- |
| Steps | Desired     |     | Wiper        |             | Desired     |     | Wiper        |             |            |     | Wiper        |             |
|       |             |     | Attenuation  |             |             |     | Attenuation  |             | Attenuatio |     | Attenuation  |             |
|       | Attenuation |     | Code         |             | Attenuation |     | Code         |             |            |     | Code         |             |
|       |             |     |              | (1)         |             |     |              | (1)         | n          |     |              | (1)         |
| 0     | 0dB         |     | 256          | 0dB         | 0dB         |     | 256          | 0dB         | 0dB        |     | 256          | 0dB         |
| 1     | -3dB        |     | 181          | -3.011dB    | -2dB        |     | 203          | -2.015dB    | -1dB       |     | 228          | -1.006dB    |
| 2     | -6dB        |     | 128          | -6.021dB    | -4dB        |     | 162          | -3.975dB    | -2dB       |     | 203          | -2.015dB    |
| 3     | -9dB        |     | 91           | -8.984dB    | -6dB        |     | 128          | -6.021dB    | -3dB       |     | 181          | -3.011dB    |
| 4     | -12dB       |     | 64           | -12.041dB   | -8dB        |     | 102          | -7.993dB    | -4dB       |     | 162          | -3.975dB    |
| 5     | -15dB       |     | 46           | -14.910dB   | -10dB       |     | 81           | -9.995dB    | -5dB       |     | 144          | -4.998dB    |
| 6     | -18dB       |     | 32           | -18.062dB   | -12dB       |     | 64           | -12.041dB   | -6dB       |     | 128          | -6.021dB    |
| 7     | -21dB       |     | 23           | -20.930dB   | -14dB       |     | 51           | -14.013dB   | -7dB       |     | 114          | -7.027dB    |
| 8     | -24dB       |     | 16           | -24.082dB   | -16dB       |     | 41           | -15.909dB   | -8dB       |     | 102          | -7.993dB    |
| 9     | -27dB       |     | 11           | -27.337dB   | -18dB       |     | 32           | -18.062dB   | -9dB       |     | 91           | -8.984dB    |
| 10    | -30dB       |     | 8            | -30.103dB   | -20dB       |     | 26           | -19.865dB   | -10dB      |     | 81           | -9.995dB    |
| 11    | -33dB       |     | 6            | -32.602dB   | -22dB       |     | 20           | -22.144dB   | -11dB      |     | 72           | -11.018dB   |
| 12    | -36dB       |     | 4            | -36.124dB   | -24dB       |     | 16           | -24.082dB   | -12dB      |     | 64           | -12.041dB   |
| 13    | -39dB       |     | 3            | -38.622dB   | -26dB       |     | 13           | -25.886dB   | -13dB      |     | 57           | -13.047dB   |
| 14    | -42dB       |     | 2            | -42.144dB   | -28dB       |     | 10           | -28.165dB   | -14dB      |     | 51           | -14.013dB   |
| 15    | -48dB       |     | 1            | -48.165dB   | -30dB       |     | 8            | -30.103dB   | -15dB      |     | 46           | - 14.910dB  |
| 16    | Mute        |     | 0            | Mute        | -32dB       |     | 6            | -32.602dB   | -16dB      |     | 41           | -15.909dB   |
| 17    |             |     |              |             | -34dB       |     | 5            | -34.185dB   | -17dB      |     | 36           | -17.039dB   |
| 18    |             |     |              |             | -36dB       |     | 4            | -36.124dB   | -18dB      |     | 32           | -18.062dB   |
| 19    |             |     |              |             | -38dB       |     | 3            | -38.622dB   | -19dB      |     | 29           | -18.917dB   |
| 20    |             |     |              |             | -42dB       |     | 2            | -42.144dB   | -20dB      |     | 26           | -19.865dB   |
| 21    |             |     |              |             | -48dB       |     | 1            | -48.165dB   | -21dB      |     | 23           | - 20.930dB  |
| 22    |             |     |              |             | Mute        |     | 0            | Mute        | -22dB      |     | 20           | -22.144dB   |
| 23    |             |     |              |             |             |     |              |             | -23dB      |     | 18           | -23.059dB   |
| 24    |             |     |              |             |             |     |              |             | -24dB      |     | 16           | -24.082dB   |
| 25    |             |     |              |             |             |     |              |             | -25dB      |     | 14           | -25.242dB   |
| 26    |             |     |              |             |             |     |              |             | -26dB      |     | 13           | -25.886dB   |
| 27    |             |     |              |             |             |     |              |             | -27dB      |     | 11           | -27.337dB   |
| 28    |             |     |              |             |             |     |              |             | -28dB      |     | 10           | -28.165dB   |
| 29    |             |     |              |             |             |     |              |             | -29dB      |     | 9            | -29.080dB   |
| 30    |             |     |              |             |             |     |              |             | -30dB      |     | 8            | -30.103dB   |
| 31    |             |     |              |             |             |     |              |             | -31dB      |     | 7            | -31.263dB   |
| 32    |             |     |              |             |             |     |              |             | -33dB      |     | 6            | -32.602dB   |
| 33    |             |     |              |             |             |     |              |             | -34dB      |     | 5            | -34.185dB   |
| 34    |             |     |              |             |             |     |              |             | -36dB      |     | 4            | -36.124dB   |
| 35    |             |     |              |             |             |     |              |             | -39dB      |     | 3            | -38.622dB   |
| 36    |             |     |              |             |             |     |              |             | -42dB      |     | 2            | -42.144dB   |
| 37    |             |     |              |             |             |     |              |             | -48dB      |     | 1            | -48.165dB   |
| 38    |             |     |              |             |             |     |              |             | Mute       |     | 0            | Mute        |
Note 1: Attenuation values do not include errors from Digital Potentiometer errors, such as Full Scale Error or Zero
Scale Error.
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     |     |     |     | DS22096B-page 65 |     |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---------------- | --- |

MCP453X/455X/463X/465X
8.6 Design Considerations 8.6.2 LAYOUT CONSIDERATIONS
In the design of a system with the MCP4XXX devices, Inductively-coupled AC transients and digital switching
the following considerations should be taken into noise can degrade the input and output signal integrity,
account: potentially masking the MCP4XXX’s performance.
Careful board layout minimizes these effects and
• Power Supply Considerations
increases the Signal-to-Noise Ratio (SNR). Multi-layer
• Layout Considerations boards utilizing a low-inductance ground plane,
isolated inputs, isolated outputs and proper decoupling
8.6.1 POWER SUPPLY
are critical to achieving the performance that the silicon
CONSIDERATIONS
is capable of providing. Particularly harsh environ-
The typical application will require a bypass capacitor ments may require shielding of critical signals.
in order to filter high-frequency noise, which can be If low noise is desired, breadboards and wire-wrapped
induced onto the power supply's traces. The bypass boards are not recommended.
capacitor helps to minimize the effect of these noise
sources on signal integrity. Figure8-8 illustrates an 8.6.3 RESISTOR TEMPCO
appropriate bypass strategy.
Characterization curves of the resistor temperature
In this example, the recommended bypass capacitor coefficient (Tempco) are shown in Figure2-12,
value is 0.1µF. This capacitor should be placed as Figure2-25, Figure2-38, and Figure2-51.
close (within 4mm) to the device power pin (V ) as
DD These curves show that the resistor network is
possible.
designed to correct for the change in resistance as
The power source supplying these devices should be temperature increases. This technique reduces the
as clean as possible. If the application circuit has end-to-end change in R resistance.
AB
separate digital and analog power supplies, V and
DD
V should reside on the analog plane. 8.6.4 HIGH VOLTAGE TOLERANT PINS
SS
High Voltage support (V ) on the Serial Interface pins
IHH
is for compatibility with the nonvolatile devices.
V
DD
V
DD
V V
SS SS
FIGURE 8-8: Typical Microcontroller
Connections.
DS22096B-page 66  2008-2013 Microchip Technology Inc.
/X554/X354PCM
X564/X364
0.1µF
rellortnocorciM
®CIP
0.1µF
A
SCL
W
B SDA

MCP453X/455X/463X/465X
9.0 DEVICE OPTIONS
Additional, custom devices are available. These
devices have weak pull-up resistors on the SDA and
SCL pins. This is useful for applications where the
wiper value is programmed during manufacture and not
modified by the system during normal operation.
Please contact your local sales office for current infor-
mation and minimum volume requirements.
9.1 Custom Options
The custom device will have a “P” (for Pull-up) after the
resistance version in the Product Identification System.
These devices will not be available through Microchip’s
online Microchip Direct, nor Microchip’s Sample sys-
tems.
Example part number:
MCP4631-103PE/ST
 2008-2013 Microchip Technology Inc. DS22096B-page 67

MCP453X/455X/463X/465X
NOTES:
DS22096B-page 68  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
| 10.0 DEVELOPMENT SUPPORT |     | 10.2 Technical Documentation |     |     |
| ------------------------ | --- | ---------------------------- | --- | --- |
Several additional technical documents are available to
10.1 Development Tools
assist you in your design and development. These
|     |     | technical  documents  | include  Application  | Notes, |
| --- | --- | --------------------- | --------------------- | ------ |
Several development tools are available to assist in
your design and evaluation of the MCP45XX/46XX Technical  Briefs,  and  Design  Guides.  Table10-2
shows some of these documents.
devices. The currently available tools are shown in
Table10-1.
These boards may be purchased directly from the
Microchip web site at www.microchip.com.
| TABLE 10-1: | DEVELOPMENT TOOLS       |         |                   |     |
| ----------- | ----------------------- | ------- | ----------------- | --- |
| Board Name  |                         | Part #  | Supported Devices |     |
(2)
MCP46XX PICTail Plus Daughter Board  MCP46XXDM-PTPLS MCP46XX
MCP4XXX Digital Potentiometer Daughter Board  (1) MCP4XXXDM-DB MCP42XXX, MCP42XX, MCP46XX,
MCP4021, and MCP4011
MCP46XXEV Evaluation Board MCP46XXEV MCP4631, MCP4641, MCP4651,
MCP4661
TSSOP-20 and SSOP-20 Evaluation Board TSSOP20EV MCP4631, MCP4641, MCP4651,
MCP4661
8-pin SOIC/MSOP/TSSOP/DIP Evaluation Board SOIC8EV Any 8-pin device in DIP, SOIC,
MSOP, or TSSOP package
14-pin SOIC/MSOP/DIP Evaluation Board SOIC14EV Any 14-pin device in DIP, SOIC, or
MSOP package
Note1: Requires the use of a PICDEM Demo Board (see User’s Guide for details) and the SOIC14EV board to
convert an MCP46XX device in TSSOP package to the DIP footprint.
2: Requires the use of the PIC24 Explorer 16 Demo Board (see User’s Guide for details)
| TABLE 10-2: | TECHNICAL DOCUMENTATION       |     |     |              |
| ----------- | ----------------------------- | --- | --- | ------------ |
| Application | Title                         |     |     | Literature # |
Note Number
AN1316 Using Digital Potentiometers for Programmable Amplifier Gain DS01316
AN1080 Understanding Digital Potentiometers Resistor Variations DS01080
AN737 Using Digital Potentiometers to Design Low Pass Adjustable Filters DS00737
AN692 Using a Digital Potentiometer to Optimize a Precision Single Supply Photo Detect DS00692
AN691 Optimizing the Digital Potentiometer in Precision Circuits DS00691
AN219 Comparing Digital Potentiometers to Mechanical Potentiometers DS00219
| —                                     | Digital Potentiometer Design Guide |     |     | DS22017          |
| ------------------------------------- | ---------------------------------- | --- | --- | ---------------- |
| —                                     | Signal Chain Design Guide          |     |     | DS21825          |
|  2008-2013 Microchip Technology Inc. |                                    |     |     | DS22096B-page 69 |

MCP453X/455X/463X/465X
NOTES:
DS22096B-page 70  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
11.0 PACKAGING INFORMATION
11.1 Package Marking Information
| 8-Lead DFN (3x3) |                 |        |                 |        | Example: |      |
| ---------------- | --------------- | ------ | --------------- | ------ | -------- | ---- |
|                  | Part Number     | Code   | Part Number     | Code   |          |      |
| XXXX             | MCP4531-502E/MF | DACA   | MCP4532-502E/MF | DACE   |          | DACA |
|                  | MCP4531-103E/MF | DACB   | MCP4532-103E/MF | DACF   |          |      |
| XYWW             |                 |        |                 |        |          | 1028 |
| NNN              | MCP4531-104E/MF | DACD   | MCP4532-104E/MF | DACH   |          | 256  |
|                  | MCP4531-503E/MF | DACC   | MCP4532-503E/MF | DACG   |          |      |
|                  | MCP4551-502E/MF | DACT   | MCP4552-502E/MF | DACX   |          |      |
|                  | MCP4551-103E/MF | DACU   | MCP4552-103E/MF | DACY   |          |      |
|                  | MCP4551-104E/MF | DACW   | MCP4552-104E/MF | DADA   |          |      |
|                  | MCP4551-503E/MF | DACV   | MCP4552-503E/MF | DACZ   |          |      |
| 8-Lead MSOP      |                 |        |                 |        | Example  |      |
|                  | Part Number     | Code   | Part Number     | Code   |          |      |
| XXXXXX           | MCP4531-103E/MS | 453113 | MCP4532-103E/MS | 453213 |          |      |
453113
|         | MCP4531-104E/MS                               | 453114 | MCP4532-104E/MS | 453214 |     |        |
| ------- | --------------------------------------------- | ------ | --------------- | ------ | --- | ------ |
| YWWNNN  |                                               |        |                 |        |     | 028256 |
|         | MCP4531-502E/MS                               | 453152 | MCP4532-502E/MS | 453252 |     |        |
|         | MCP4531-503E/MS                               | 453153 | MCP4532-503E/MS | 453253 |     |        |
|         | MCP4551-103E/MS                               | 455113 | MCP4552-103E/MS | 455213 |     |        |
|         | MCP4551-104E/MS                               | 455114 | MCP4552-104E/MS | 455214 |     |        |
|         | MCP4551-502E/MS                               | 455152 | MCP4552-502E/MS | 455252 |     |        |
|         | MCP4551-503E/MS                               | 455153 | MCP4552-503E/MS | 455253 |     |        |
| Legend: | XX...X Customer-specific information          |        |                 |        |     |        |
|         | Y Year code (last digit of calendar year)     |        |                 |        |     |        |
|         | YY Year code (last 2 digits of calendar year) |        |                 |        |     |        |
|         | WW Week code (week of January 1 is week ‘01’) |        |                 |        |     |        |
|         | NNN Alphanumeric traceability code            |        |                 |        |     |        |
e3
|     |    Pb-free JEDEC designator for Matte Tin (Sn)                    |     |     |     |     |     |
| --- | ----------------------------------------------------------------- | --- | --- | --- | --- | --- |
|     | * This package is Pb-free. The Pb-free JEDEC designator ( e  3  ) |     |     |     |     |     |
can be found on the outer packaging for this package.
Note: In the event the full Microchip part number cannot be marked on one line, it will
|     | be  carried  over  | to  the  next  | line,  thus  limiting  | the  number  | of  available |     |
| --- | ------------------ | -------------- | ---------------------- | ------------ | ------------- | --- |
characters for customer-specific information.
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     | DS22096B-page 71 |
| ------------------------------------- | --- | --- | --- | --- | --- | ---------------- |

MCP453X/455X/463X/465X
Package Marking Information (Continued)
10-Lead DFN (3x3) Example:
| Part Number | Code | Part Number | Code |
| ----------- | ---- | ----------- | ---- |
XXXX AAFA
| MCP4632-502E/MF | AABA | MCP4652-502E/MF | AAKA |
| --------------- | ---- | --------------- | ---- |
YYWW 1028
| MCP4632-103E/MF | AACA | MCP4652-103E/MF | AALA |
| --------------- | ---- | --------------- | ---- |
NNN 256
| MCP4632-104E/MF | AAEA | MCP4652-104E/MF | AAPA |
| --------------- | ---- | --------------- | ---- |
| MCP4632-503E/MF | AADA | MCP4652-503E/MF | AAMA |
10-Lead MSOP Example
| Part Number | Code | Part Number | Code |
| ----------- | ---- | ----------- | ---- |
XXXXXX 463252
| MCP4632-502E/UN | 463252 | MCP4652-502E/UN | 465252 |
| --------------- | ------ | --------------- | ------ |
YWWNNN 028256
| MCP4632-103E/UN                  | 463213 | MCP4652-103E/UN | 465213   |
| -------------------------------- | ------ | --------------- | -------- |
| MCP4632-104E/UN                  | 463214 | MCP4652-104E/UN | 465214   |
| MCP4632-503E/UN                  | 463253 | MCP4652-503E/UN | 465253   |
| 14-Lead TSSOP (MCP4631, MCP4651) |        |                 | Example  |
| XXXXXXXX                         |        |                 | 4631502E |
| YYWW                             |        |                 | 1028     |
| NNN                              |        |                 | 256      |
| 16-Lead QFN (MCP4631, MCP4651)   |        | Example         |          |
| XXXXX                            |        |                 | 4631     |
| XXXXXX                           |        |                 | 502      |
| XXXXXX                           |        |                 | E/ML^e^3 |
| YYWWNNN                          |        |                 | 028256   |
DS22096B-page 72  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
 2008-2013 Microchip Technology Inc. DS22096B-page 73

MCP453X/455X/463X/465X
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
DS22096B-page 74  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
 2008-2013 Microchip Technology Inc. DS22096B-page 75

MCP453X/455X/463X/465X
Note: For the mostcurrent package drawings,please seetheMicrochip Packaging Specification located at
http://www.microchip.com/packaging
DS22096B-page 76  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
Note: For the mostcurrent package drawings,please seetheMicrochip Packaging Specification located at
http://www.microchip.com/packaging
 2008-2013 Microchip Technology Inc. DS22096B-page 77

MCP453X/455X/463X/465X
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
DS22096B-page 78  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
 2008-2013 Microchip Technology Inc. DS22096B-page 79

MCP453X/455X/463X/465X
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
DS22096B-page 80  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
 2008-2013 Microchip Technology Inc. DS22096B-page 81

MCP453X/455X/463X/465X
UN
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
DS22096B-page 82  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
UN
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
 2008-2013 Microchip Technology Inc. DS22096B-page 83

MCP453X/455X/463X/465X
10-Lead Plastic Micro Small Outline Package (UN) [MSOP]
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
DS22096B-page 84  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
 2008-2013 Microchip Technology Inc. DS22096B-page 85

MCP453X/455X/463X/465X
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
DS22096B-page 86  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
 2008-2013 Microchip Technology Inc. DS22096B-page 87

MCP453X/455X/463X/465X
(cid:2)(cid:3)(cid:4)(cid:5)(cid:6)(cid:7)(cid:8)(cid:9)(cid:10)(cid:11)(cid:7)(cid:12)(cid:13)(cid:14)(cid:15)(cid:9)(cid:16)(cid:17)(cid:7)(cid:8)(cid:9)(cid:18)(cid:11)(cid:7)(cid:13)(cid:19)(cid:9)(cid:20)(cid:21)(cid:9)(cid:5)(cid:6)(cid:7)(cid:8)(cid:9)(cid:10)(cid:7)(cid:15)(cid:22)(cid:7)(cid:23)(cid:6)(cid:9)(cid:24)(cid:25)(cid:5)(cid:26)(cid:9)(cid:27)(cid:9)(cid:28)(cid:29)(cid:28)(cid:29)(cid:30)(cid:31) (cid:9)!!(cid:9)"(cid:21)(cid:8)#(cid:9)$(cid:16)(cid:18)(cid:20)%
(cid:20)(cid:21)(cid:13)(cid:6)& ?(cid:22)(cid:21)(cid:14)’(cid:23)(cid:13)(cid:14)((cid:22)"’(cid:14)(cid:20)#(cid:21)(cid:21)(cid:13)(cid:25)’(cid:14)(cid:10)(cid:11)(cid:20)5(cid:11)(cid:12)(cid:13)(cid:14)$(cid:21)(cid:11)+(cid:19)(cid:25)(cid:12)")(cid:14)(cid:10)(cid:26)(cid:13)(cid:11)"(cid:13)(cid:14)"(cid:13)(cid:13)(cid:14)’(cid:23)(cid:13)(cid:14)(cid:18)(cid:19)(cid:20)(cid:21)(cid:22)(cid:20)(cid:23)(cid:19)(cid:10)(cid:14)(cid:31)(cid:11)(cid:20)5(cid:11)(cid:12)(cid:19)(cid:25)(cid:12)(cid:14)(cid:3)(cid:10)(cid:13)(cid:20)(cid:19)&(cid:19)(cid:20)(cid:11)’(cid:19)(cid:22)(cid:25)(cid:14)(cid:26)(cid:22)(cid:20)(cid:11)’(cid:13)$(cid:14)(cid:11)’(cid:14)
(cid:23)’’(cid:10)>@@+++(cid:29)((cid:19)(cid:20)(cid:21)(cid:22)(cid:20)(cid:23)(cid:19)(cid:10)(cid:29)(cid:20)(cid:22)(@(cid:10)(cid:11)(cid:20)5(cid:11)(cid:12)(cid:19)(cid:25)(cid:12)
D D2
EXPOSED
PAD
e
E E2
|     | 2   | 2   |     |     |
| --- | --- | --- | --- | --- |
b
|     | 1   | 1   |     |     |
| --- | --- | --- | --- | --- |
K
| N       |     |       | N          |     |
| ------- | --- | ----- | ---------- | --- |
|         |     | NOTE1 |            | L   |
| TOPVIEW |     |       | BOTTOMVIEW |     |
A A3
A1
|                                                                                                                 |                                                                                       | A(cid:25)(cid:19)’"                           | (cid:18)(cid:28)GG(cid:28)(cid:18)7(cid:24)7(cid:8)(cid:3) |                                 |
| --------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------- | --------------------------------------------- | ---------------------------------------------------------- | ------------------------------- |
|                                                                                                                 | (cid:2)(cid:19)((cid:13)(cid:25)"(cid:19)(cid:22)(cid:25)(cid:14)G(cid:19)((cid:19)’" | (cid:18)(cid:28)H                             | HJ(cid:18)                                                 | (cid:18)(cid:7)K                |
| H#(*(cid:13)(cid:21)(cid:14)(cid:22)&(cid:14)(cid:31)(cid:19)(cid:25)"                                          |                                                                                       | H                                             | (cid:30)L                                                  |                                 |
| (cid:31)(cid:19)’(cid:20)(cid:23)                                                                               |                                                                                       | (cid:13)                                      | (cid:4)(cid:29)L;(cid:14)<(cid:3)=                         |                                 |
| J!(cid:13)(cid:21)(cid:11)(cid:26)(cid:26)(cid:14)N(cid:13)(cid:19)(cid:12)(cid:23)’                            |                                                                                       | (cid:7) (cid:4)(cid:29)(cid:15)(cid:4)        | (cid:4)(cid:29)(cid:6)(cid:4)                              | (cid:30)(cid:29)(cid:4)(cid:4)  |
| (cid:3)’(cid:11)(cid:25)$(cid:22)&&(cid:14)                                                                     |                                                                                       | (cid:7)(cid:30) (cid:4)(cid:29)(cid:4)(cid:4) | (cid:4)(cid:29)(cid:4)(cid:16)                             | (cid:4)(cid:29)(cid:4);         |
| =(cid:22)(cid:25)’(cid:11)(cid:20)’(cid:14)(cid:24)(cid:23)(cid:19)(cid:20)5(cid:25)(cid:13)""                  |                                                                                       | (cid:7)6                                      | (cid:4)(cid:29)(cid:16)(cid:4)(cid:14)(cid:8)7?            |                                 |
| J!(cid:13)(cid:21)(cid:11)(cid:26)(cid:26)(cid:14)O(cid:19)$’(cid:23)                                           |                                                                                       | 7                                             | (cid:5)(cid:29)(cid:4)(cid:4)(cid:14)<(cid:3)=             |                                 |
| 7%(cid:10)(cid:22)"(cid:13)$(cid:14)(cid:31)(cid:11)$(cid:14)O(cid:19)$’(cid:23)                                |                                                                                       | 7(cid:16) (cid:16)(cid:29);(cid:4)            | (cid:16)(cid:29)L;                                         | (cid:16)(cid:29)(cid:15)(cid:4) |
| J!(cid:13)(cid:21)(cid:11)(cid:26)(cid:26)(cid:14)G(cid:13)(cid:25)(cid:12)’(cid:23)                            |                                                                                       | (cid:2)                                       | (cid:5)(cid:29)(cid:4)(cid:4)(cid:14)<(cid:3)=             |                                 |
| 7%(cid:10)(cid:22)"(cid:13)$(cid:14)(cid:31)(cid:11)$(cid:14)G(cid:13)(cid:25)(cid:12)’(cid:23)                 |                                                                                       | (cid:2)(cid:16) (cid:16)(cid:29);(cid:4)      | (cid:16)(cid:29)L;                                         | (cid:16)(cid:29)(cid:15)(cid:4) |
| =(cid:22)(cid:25)’(cid:11)(cid:20)’(cid:14)O(cid:19)$’(cid:23)                                                  |                                                                                       | * (cid:4)(cid:29)(cid:16);                    | (cid:4)(cid:29)6(cid:4)                                    | (cid:4)(cid:29)6;               |
| =(cid:22)(cid:25)’(cid:11)(cid:20)’(cid:14)G(cid:13)(cid:25)(cid:12)’(cid:23)                                   |                                                                                       | G (cid:4)(cid:29)6(cid:4)                     | (cid:4)(cid:29)(cid:5)(cid:4)                              | (cid:4)(cid:29);(cid:4)         |
| =(cid:22)(cid:25)’(cid:11)(cid:20)’(cid:9)’(cid:22)(cid:9)7%(cid:10)(cid:22)"(cid:13)$(cid:14)(cid:31)(cid:11)$ |                                                                                       | Q (cid:4)(cid:29)(cid:16)(cid:4)              | R                                                          | R                               |
(cid:20)(cid:21)(cid:13)(cid:6)(cid:12)&
(cid:30)(cid:29) (cid:31)(cid:19)(cid:25)(cid:14)(cid:30)(cid:14)!(cid:19)"#(cid:11)(cid:26)(cid:14)(cid:19)(cid:25)$(cid:13)%(cid:14)&(cid:13)(cid:11)’#(cid:21)(cid:13)(cid:14)((cid:11)(cid:27)(cid:14)!(cid:11)(cid:21)(cid:27))(cid:14)*#’(cid:14)(#"’(cid:14)*(cid:13)(cid:14)(cid:26)(cid:22)(cid:20)(cid:11)’(cid:13)$(cid:14)+(cid:19)’(cid:23)(cid:19)(cid:25)(cid:14)’(cid:23)(cid:13)(cid:14)(cid:23)(cid:11)’(cid:20)(cid:23)(cid:13)$(cid:14)(cid:11)(cid:21)(cid:13)(cid:11)(cid:29)
(cid:16)(cid:29) (cid:31)(cid:11)(cid:20)5(cid:11)(cid:12)(cid:13)(cid:14)(cid:19)"(cid:14)"(cid:11)+(cid:14)"(cid:19)(cid:25)(cid:12)#(cid:26)(cid:11)’(cid:13)$(cid:29)
6(cid:29) (cid:2)(cid:19)((cid:13)(cid:25)"(cid:19)(cid:22)(cid:25)(cid:19)(cid:25)(cid:12)(cid:14)(cid:11)(cid:25)$(cid:14)’(cid:22)(cid:26)(cid:13)(cid:21)(cid:11)(cid:25)(cid:20)(cid:19)(cid:25)(cid:12)(cid:14)(cid:10)(cid:13)(cid:21)(cid:14)(cid:7)(cid:3)(cid:18)7(cid:14)8(cid:30)(cid:5)(cid:29);(cid:18)(cid:29)
<(cid:3)=> <(cid:11)"(cid:19)(cid:20)(cid:14)(cid:2)(cid:19)((cid:13)(cid:25)"(cid:19)(cid:22)(cid:25)(cid:29)(cid:14)(cid:24)(cid:23)(cid:13)(cid:22)(cid:21)(cid:13)’(cid:19)(cid:20)(cid:11)(cid:26)(cid:26)(cid:27)(cid:14)(cid:13)%(cid:11)(cid:20)’(cid:14)!(cid:11)(cid:26)#(cid:13)(cid:14)"(cid:23)(cid:22)+(cid:25)(cid:14)+(cid:19)’(cid:23)(cid:22)#’(cid:14)’(cid:22)(cid:26)(cid:13)(cid:21)(cid:11)(cid:25)(cid:20)(cid:13)"(cid:29)
(cid:8)7?> (cid:8)(cid:13)&(cid:13)(cid:21)(cid:13)(cid:25)(cid:20)(cid:13)(cid:14)(cid:2)(cid:19)((cid:13)(cid:25)"(cid:19)(cid:22)(cid:25))(cid:14)#"#(cid:11)(cid:26)(cid:26)(cid:27)(cid:14)+(cid:19)’(cid:23)(cid:22)#’(cid:14)’(cid:22)(cid:26)(cid:13)(cid:21)(cid:11)(cid:25)(cid:20)(cid:13))(cid:14)&(cid:22)(cid:21)(cid:14)(cid:19)(cid:25)&(cid:22)(cid:21)((cid:11)’(cid:19)(cid:22)(cid:25)(cid:14)(cid:10)#(cid:21)(cid:10)(cid:22)"(cid:13)"(cid:14)(cid:22)(cid:25)(cid:26)(cid:27)(cid:29)
(cid:18)(cid:19)(cid:20)(cid:21)(cid:22)(cid:20)(cid:23)(cid:19)(cid:10)(cid:24)(cid:13)(cid:20)(cid:23)(cid:25)(cid:22)(cid:26)(cid:22)(cid:12)(cid:27)(cid:2)(cid:21)(cid:11)+(cid:19)(cid:25)(cid:12)=(cid:4)(cid:5)(cid:9)(cid:30)(cid:16)(cid:17)<
DS22096B-page 88  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
Note: For the most current package drawings, please see the Microchip Packaging Specification located at
http://www.microchip.com/packaging
 2008-2013 Microchip Technology Inc. DS22096B-page 89

MCP453X/455X/463X/465X
NOTES:
DS22096B-page 90  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
APPENDIX A: REVISION HISTORY
Revision B (February 2013)
The following is the list of modifications:
1. Corrected MCP45x1 DFN package pinout.
2. Corrected Device Block Diagram.
3. Updated the Absolute Maximum Ratings †
with Total Power Dissipation values for each
package type.
4. Updated typical thermal values in Temperature
Characteristics table.
5. Corrected labeling in Figure2-1, from
Section2.0 “Typical Performance Curves”.
Also corrected Figure2-4.
6. Appropriate 1.8V Graphs in Section2.0 “Typi-
cal Performance Curves” now reference
Appendix B: “Characterization Data Analy-
sis”.
7. Added new Figure2-66.
8. Corrected values in Figure5-1.
9. Added description of wiper value on POR/BOR
(Section5.2 “Wiper”).
10. Added new section Section8.5 “Implementing
Log Steps with a Linear Digital
Potentiometer”.
11. Added information in the Development Tools
Section (Section10.0 “Development
support”).
12. Updated packaging section with package
available landing pattern diagrams.
13. Added Appendix B: “Characterization Data
Analysis”.
14. Updated the format of the Absolute Maximum
Ratings † page in Section1.0 “Electrical
Characteristics”.
15. Clarified actions of the POR in Section4.1.1
“Power-on Reset”.
16. Removed Note 3 from Table10-1.
Revision A (November 2008)
• Original Release of this Document.
 2008-2013 Microchip Technology Inc. DS22096B-page 91

MCP453X/455X/463X/465X
NOTES:
DS22096B-page 92  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
| APPENDIX B: |     | CHARACTERIZATION  |     |     |     |     | B.1 | Low-Voltage Operation |     |     |     |     |     |
| ----------- | --- | ----------------- | --- | --- | --- | --- | --- | --------------------- | --- | --- | --- | --- | --- |
DATA ANALYSIS
|     |     |     |     |     |     |     | This  | appendix  | gives  |     | an  overview  |     | of  CMOS |
| --- | --- | --- | --- | --- | --- | --- | ----- | --------- | ------ | --- | ------------- | --- | -------- |
semiconductor characteristics at lower voltages. This is
Some designers may desire to understand the device
|              |                  |     |          |     |                |     | important  |     | so  that  | the  | 1.8V  | resistor  | network |
| ------------ | ---------------- | --- | -------- | --- | -------------- | --- | ---------- | --- | --------- | ---- | ----- | --------- | ------- |
| operational  | characteristics  |     | outside  | of  | the  specified |     |            |     |           |      |       |           |         |
operating conditions of the device.  characterization graphs of the MCP453X/455X/463X/
465X devices can be better understood.
| Applications  | where  | the  | knowledge  | of  | the  resistor |     |     |     |     |     |     |     |     |
| ------------- | ------ | ---- | ---------- | --- | ------------- | --- | --- | --- | --- | --- | --- | --- | --- |
For this discussion, we will use the 5k device data.
network characteristics could be useful include battery
This data was chosen since the variations of wiper
| powered  | devices  | and  | applications  | that  | experience |     |     |     |     |     |     |     |     |
| -------- | -------- | ---- | ------------- | ----- | ---------- | --- | --- | --- | --- | --- | --- | --- | --- |
resistance has much greater implications for devices
brown-out conditions.
|     |     |     |     |     |     |     | with smaller R |     |  resistances.  |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | -------------- | --- | -------------- | --- | --- | --- | --- |
AB
In battery applications, the application voltage decays
|                                                     |     |     |     |     |     |     | FigureB-1 shows the worst case R |     |     |     |     |  error from the |     |
| --------------------------------------------------- | --- | --- | --- | --- | --- | --- | -------------------------------- | --- | --- | --- | --- | --------------- | --- |
| over time until new batteries are installed. As the |     |     |     |     |     |     |                                  |     |     |     |     | BW              |     |
voltage decays, the system will continue to operate. At average R BW  as a percentage, while FigureB-2 shows
the R  resistance versus wiper code graph. Nonlinear
| some voltage level, the application will be below its |     |     |     |     |     |     |     | BW  |     |     |     |     |     |
| ----------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
behavior occurs at approximately wiper code 160. This
specified operating voltage range. This is dependent
|                                                        |     |     |     |     |     |     | is  better  | shown  |     | in  FigureB-2,  |     | where  | the  R |
| ------------------------------------------------------ | --- | --- | --- | --- | --- | --- | ----------- | ------ | --- | --------------- | --- | ------ | ------ |
| on the individual components used in the design. It is |     |     |     |     |     |     |             |        |     |                 |     |        | BW     |
resistance changes from a linear slope. This change is
still useful to understand the device characteristics to
expect when this low-voltage range is encountered. due to the change in the wiper resistance.
| Unlike a microcontroller, which can use an external      |     |     |     |     |     |     |        |       |     |     |     |     |     |
| -------------------------------------------------------- | --- | --- | --- | --- | --- | --- | ------ | ----- | --- | --- | --- | --- | --- |
| supervisor device to force the controller into the Reset |     |     |     |     |     |     |        | 2.00% |     |     |     |     |     |
state, a digital potentiometer’s resistance characteristic
1.00%
is not specified. But understanding the operational
0.00%
characteristics can be important in the design of the
-1.00%
| application’s circuit for this low-voltage condition.    |     |         |             |        |        |     | % rorrE | -2.00% |     |     |     |     |     |
| -------------------------------------------------------- | --- | ------- | ----------- | ------ | ------ | --- | ------- | ------ | --- | --- | --- | --- | --- |
| Other  application                                       |     | system  | scenarios,  | where  | under- |     |         | -3.00% |     |     |     |     |     |
| standing the low-voltage characteristics of the resistor |     |         |             |        |        |     |         | -4.00% |     |     |     |     |     |
-40C
network could be important, is for system brown-out -5.00% +25C
| conditions. |     |     |     |     |     |     |     | -6.00% |     |     |     |     | +85C |
| ----------- | --- | --- | --- | --- | --- | --- | --- | ------ | --- | --- | --- | --- | ---- |
+125C
| For the MCP453X/455X/463X/465X devices, the ana- |     |     |     |     |     |     |     | -7.00% |     |       |     |         |         |
| ------------------------------------------------ | --- | --- | --- | --- | --- | --- | --- | ------ | --- | ----- | --- | ------- | ------- |
|                                                  |     |     |     |     |     |     |     | 0      | 32  | 64 96 | 128 | 160 192 | 224 256 |
log operation is specified at a minimum of 2.7V. Device
Wiper Code
| testing has Terminal A connected to the device V |     |                |        |      |           | DD  (for |                    |     |     |                   |     |                   |         |
| ------------------------------------------------ | --- | -------------- | ------ | ---- | --------- | -------- | ------------------ | --- | --- | ----------------- | --- | ----------------- | ------- |
|                                                  |     |                |        |      |           |          | FIGURE B-1:        |     |     | 1.8V Worst Case R |     |                   |  Error  |
| potentiometer                                    |     | configuration  | only)  | and  | Terminal  | B        |                    |     |     |                   |     |                   | BW      |
| connected to V                                   |     | .              |        |      |           |          | from Average R     |     |     |  (R               | -R  | ) vs. Wiper Code  |         |
|                                                  |     | SS             |        |      |           |          |                    |     | BW  | BW0               | BW3 |                   |         |
|                                                  |     |                |        |      |           |          | and Temperature (V |     |     |  = 1.8V, I        |     |  = 190 µA).       |         |
|                                                  |     |                |        |      |           |          |                    |     |     | DD                |     | W                 |         |

7000
6000
5000
)(cid:2)( ecnatsiseR
4000
3000
|     |     |     |     |     |     |     |     | 2000 |     |     |     |     | -40C |
| --- | --- | --- | --- | --- | --- | --- | --- | ---- | --- | --- | --- | --- | ---- |
+25C
|     |     |     |     |     |     |     |     | 1000 |     |     |     |     | +85C |
| --- | --- | --- | --- | --- | --- | --- | --- | ---- | --- | --- | --- | --- | ---- |
+125C
0
|     |     |     |     |     |     |     |     | 0   | 32  | 64 96 | 128 | 160 192 | 224 256 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ----- | --- | ------- | ------- |
Wiper Code
|     |     |     |     |     |     |     | FIGURE B-2: |     |     | R   |  vs. Wiper Code And  |     |     |
| --- | --- | --- | --- | --- | --- | --- | ----------- | --- | --- | --- | -------------------- | --- | --- |
BW
|                                       |     |     |     |     |     |     | Temperature (V |     | DD  |  = 1.8V, I | W  = 190µA). |                  |     |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | -------------- | --- | --- | ---------- | ------------ | ---------------- | --- |
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |                |     |     |            |              | DS22096B-page 93 |     |

MCP453X/455X/463X/465X
FigureB-3 and FigureB-4 show the wiper resistance The  method  in  which  the  data  was  collected  is
for V  voltages of 5.5, 3.0, 1.8 volts. These graphs important  to  understand.  FigureB-5  shows  the
DD
show that as the resistor ladder wiper node voltage technique that was used to measure the R BW  and R W
(V )  approaches  the  V /2  voltage,  the  wiper resistance. In this technique, Terminal A is floating and
|     | WCn |     |     | DD  |     |     |     |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
resistance increases. These graphs also show the Terminal B is connected to ground. A fixed current is
different resistance characteristics of the NMOS and then forced into the wiper (I ), and the corresponding
W
PMOS transistors that make up the wiper switch. This wiper voltage (V ) is measured. Forcing a known
W
is demonstrated by the wiper code resistance curve, current through R BW  (I W ) and then measuring the
which does not mirror itself around the mid-scale code voltage  difference  between  the  wiper  (V )  and
W
(wiper code = 128). Terminal A (V ), the wiper resistance (R ) can be
|                                                      |     |     |                             |     |     |     |                                                 |     | A   |     |                    | W   |       |
| ---------------------------------------------------- | --- | --- | --------------------------- | --- | --- | --- | ----------------------------------------------- | --- | --- | --- | ------------------ | --- | ----- |
|                                                      |     |     |                             |     |     |     | calculated, as shown in FigureB-5. Changes in I |     |     |     |                    |     |  cur- |
| So why are the R                                     |     |     |  graphs showing the maximum |     |     |     |                                                 |     |     |     |                    |     | W     |
|                                                      |     |     | W                           |     |     |     | rent will change the wiper voltage (V           |     |     |     | ). This may effect |     |       |
| resistance at about mid-scale (wiper code = 128) and |     |     |                             |     |     |     |                                                 |     |     |     | W                  |     |       |
the R  graphs showing the issue at code 160? the device’s wiper resistance (R W ).
BW
| This  | requires  | understanding  |     | low-voltage  |     | transistor |     |     |     |     |     |     |     |
| ----- | --------- | -------------- | --- | ------------ | --- | ---------- | --- | --- | --- | --- | --- | --- | --- |
floating
characteristics as well as how the data was measured.
V
A
|        |                          |             |             |             |              |     |     | A   |       |     |      |      |     |
| ------ | ------------------------ | ----------- | ----------- | ----------- | ------------ | --- | --- | --- | ----- | --- | ---- | ---- | --- |
|        |                          |             |             |             |              |     |     |     | V W   |     |      |      |     |
|        | 220                      |             |             |             |              |     |     |     | W     |     |      |      |     |
|        |                          | -40C @ 3.0V | +25C @ 3.0V | +85C @ 3.0V | +125C @ 3.0V |     |     |     |       |     |      |      |     |
|        | 200                      | -40C @5.5V  | +25C @ 5.5V | +85C @ 5.5V | +125C @ 5.5V |     |     |     |       |     |      |      |     |
|        | 180                      |             |             |             |              |     |     |     | I W   |     |      |      |     |
|        |                          |             |             |             |              |     |     |     |       | R   |  = V | /I   |     |
|        | )(cid:2)( ecnatsiseR 160 |             |             |             |              |     |     |     |       |     | BW   | W W  |     |
B
|     | 140 |     |     |     |     |     |     |       |     | R   |  = (V | -V )/I |     |
| --- | --- | --- | --- | --- | --- | --- | --- | ----- | --- | --- | ----- | ------ | --- |
|     |     |     |     |     |     |     |     | V B   |     |     | W     | W A    | W   |
120
100
|     | 80  |     |     |     |     |     | FIGURE B-5: |     | R BW |  and R | W  Measurement. |     |     |
| --- | --- | --- | --- | --- | --- | --- | ----------- | --- | ---- | ------ | --------------- | --- | --- |
60
|     |     |     |     |     |     |     | FigureB-6  | shows  | a  block  | diagram  |     | of  the  | resistor |
| --- | --- | --- | --- | --- | --- | --- | ---------- | ------ | --------- | -------- | --- | -------- | -------- |
40
|     |     |     |     |     |     |     | network where the R |     |  resistor is a series of 256 R |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | ------------------- | --- | ------------------------------ | --- | --- | --- | --- |
|     | 20  |     |     |     |     |     |                     |     | AB                             |     |     |     | S   |
0 64 128 192 256 resistors. These resistors are polysilicon devices. Each
Wiper Code
wiper switch is an analog switch made up of an NMOS
and PMOS transistor. A more detailed figure of the
| FIGURE B-3: |     |     | Wiper Resistance (R |     |     | ) vs.  |        |         |            |                 |     |      |       |
| ----------- | --- | --- | ------------------- | --- | --- | ------ | ------ | ------- | ---------- | --------------- | --- | ---- | ----- |
|             |     |     |                     |     |     | W      | wiper  | switch  | is  shown  | in  FigureB-7.  |     | The  | wiper |
Wiper Code and Temperature
resistance is influenced by the voltage on the wiper
(V DD  = 5.5V, I W  = 900 UA; V DD  = 3.0V, switches’ nodes (V , V  and V ). Temperature also
|     |     |     |     |     |     |     |     |     | G W | WCn |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
I  = 480 µA).
| W   |     |     |     |     |     |     | influences the characteristics of the wiper switch, as |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | ------------------------------------------------------ | --- | --- | --- | --- | --- | --- |
shown in FigureB-4.

|     |     |     |     |     |     |     | The  | NMOS  | transistor  and  | PMOS  |     | transistor  | have |
| --- | --- | --- | --- | --- | --- | --- | ---- | ----- | ---------------- | ----- | --- | ----------- | ---- |
2020 -40C @ 1.8V different characteristics. These characteristics, as well
+25C @ 1.8V as the wiper switch node voltages, determine the R
|     |     | +85C @ 1.8V |     |     |     |     |     |     |     |     |     |     | W   |
| --- | --- | ----------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
)(cid:2)( ecnatsiseR 1520 +125C @ 1.8V resistance at each wiper code. The variation of each
wiper switch’s characteristics in the resistor network is
|     | 1020 |     |     |     |     |     | greater then the variation of the R |     |     |     |  resistors.  |     |     |
| --- | ---- | --- | --- | --- | --- | --- | ----------------------------------- | --- | --- | --- | ------------ | --- | --- |
S
|     |     |     |     |     |     |     | The voltage on the resistor network node (V |     |     |     |     |     | ) is |
| --- | --- | --- | --- | --- | --- | --- | ------------------------------------------- | --- | --- | --- | --- | --- | ---- |
WCn
|     | 520 |     |     |     |     |     | dependent             | upon  | the  wiper                       | code   | selected             | and  | the |
| --- | --- | --- | --- | --- | --- | --- | --------------------- | ----- | -------------------------------- | ------ | -------------------- | ---- | --- |
|     |     |     |     |     |     |     | voltages applied to V |       | , V                              |  and V | . The wiper switch V |      |     |
|     |     |     |     |     |     |     |                       |       | A B                              | W      |                      |      | G   |
|     | 20  |     |     |     |     |     | voltage to V          |  or V |  voltage determines how strongly |        |                      |      |     |
W WCn
|     | 0   |     | 64  | 128 | 192 | 256 |     |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
the transistor is turned on. When the transistor is
Wiper Code
|     |     |     |     |     |     |     | weakly turned on the wiper resistance, R |     |     |     |     |  will be high. |     |
| --- | --- | --- | --- | --- | --- | --- | ---------------------------------------- | --- | --- | --- | --- | -------------- | --- |
W
When the transistor is strongly turned on, the wiper
| FIGURE B-4:                 |            |              | Wiper Resistance (R |     |     | ) vs.  |               |     |                                       |     |     |     |     |
| --------------------------- | ---------- | ------------ | ------------------- | --- | --- | ------ | ------------- | --- | ------------------------------------- | --- | --- | --- | --- |
|                             |            |              |                     |     |     | W      | resistance (R |     | ) will be in the typical range.       |     |     |     |     |
| Wiper Code and Temperature  |            |              |                     |     |     |        |               | W   |                                       |     |     |     |     |
| (V                          |  = 1.8V, I |  = 260 µA).  |                     |     |     |        |               |     |                                       |     |     |     |     |
|                             | DD         | W            |                     |     |     |        |               |     |                                       |     |     |     |     |
| DS22096B-page 94            |            |              |                     |     |     |        |               |     |  2008-2013 Microchip Technology Inc. |     |     |     |     |

MCP453X/455X/463X/465X
|     |     |     |     |     |     |     | So,  | looking  | at  | the  wiper  | voltage  | (V )  for  the |
| --- | --- | --- | --- | --- | --- | --- | ---- | -------- | --- | ----------- | -------- | -------------- |
W
|     | A   |     |     |     |     |     | 3.0Vand1.8V data gives the graphs in FigureB-8 and |     |     |     |     |               |
| --- | --- | --- | --- | --- | --- | --- | -------------------------------------------------- | --- | --- | --- | --- | ------------- |
|     |     | V   |     |     |     |     | FigureB-9. In the 1.8V graph, as the V             |     |     |     |     | W  approaches |
A
0.8V, the voltage increases nonlinearly. Since V=I*R,
|     |     |     |     |     |     |     | and the current (I |     |     | ) is constant, it means that the |     |     |
| --- | --- | --- | --- | --- | --- | --- | ------------------ | --- | --- | -------------------------------- | --- | --- |
W
|     | N n   |     |     |     |     |     | device  | resistance  |     | increased  | nonlinearly  | at  around |
| --- | ----- | --- | --- | --- | --- | --- | ------- | ----------- | --- | ---------- | ------------ | ---------- |
 (1)
|     |     | R   |     |     |     |     | wiper code 160. |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --------------- | --- | --- | --- | --- | --- |
|     | R   | W   |     |     |     |     |                 |     |     |     |     |     |
S

N
|     | n -1 |     |       |     |     | DV   |     |     |     |     |     |     |
| --- | ---- | --- | ----- | --- | --- | ---- | --- | --- | --- | --- | --- | --- |
|     |      |     |  (1)  |     |     | G    |     | 1.2 |     |     |     |     |
|     | R    | R W |       |     |     |      |     |     |     |     |     |     |
S
1.0
NMOS
|     | N n-2   |     |     |      |     |     |     | )V( egatloV repiW |     |     |     |     |
| --- | ------- | --- | --- | ---- | --- | --- | --- | ----------------- | --- | --- | --- | --- |
|     |         | V   |     | PMOS |     |     |     | 0.8               |     |     |     |     |
WC(n-2)
R
R S
|     | AB  |     |     |     |     |     |     | 0.6 |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
 (1)
|     | N n-3   |     |     | R W |     |     |     |     |     |     |     |      |
| --- | ------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---- |
|     |         |     |     |     |     |     |     | 0.4 |     |     |     | -40C |
W
+25C
|     |     |     |     |     |     | V   |     | 0.2 |     |     |     |      |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---- |
|     |     |     |     |     |     | W   |     |     |     |     |     | +85C |
+125C
|     | N   |     |     |     |     |     |     | 0.0 |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
1
|     |     | R   |  (1)  |     |     |     |     |     | 0 32 | 64 96 | 128        | 160 192 224 256 |
| --- | --- | --- | ----- | --- | --- | --- | --- | --- | ---- | ----- | ---------- | --------------- |
|     | R   | W   |       |     |     |     |     |     |      |       | Wiper Code |                 |
S
|     | N   |     |     |     |     |     | FIGURE B-8: |     |     | Wiper Voltage (V |     | W ) vs.  |
| --- | --- | --- | --- | --- | --- | --- | ----------- | --- | --- | ---------------- | --- | -------- |
0
|     |     |     |  (1)  |     |     |     | Wiper Code (V |     |     |  = 3.0V, I |  = 190 µA). |     |
| --- | --- | --- | ----- | --- | --- | --- | ------------- | --- | --- | ---------- | ----------- | --- |
|     |     | R   |       |     |     |     |               |     | DD  |            | W           |     |
W

|     |     | V   |     |     |     |     |     | 1.4 |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|     | B   | B   |     |     |     |     |     |     |     |     |     |     |
1.2
| Note1:The  |     | wiper  | resistance  | is  | dependent  | on  |     |     |     |     |     |     |
| ---------- | --- | ------ | ----------- | --- | ---------- | --- | --- | --- | --- | --- | --- | --- |
)V( egatloV repiW 1.0
|     |     | several  | factors  | including,  | wiper  | code, |     |     |     |     |     |     |
| --- | --- | -------- | -------- | ----------- | ------ | ----- | --- | --- | --- | --- | --- | --- |
0.8
|     |     | device V                  | DD , Terminal voltages (on A, B |     |     |     |     |     |     |     |     |     |
| --- | --- | ------------------------- | ------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|     |     | and W), and temperature.  |                                 |     |     |     |     | 0.6 |     |     |     |     |
-40C
| FIGURE B-6: |     |     | Resistor Network Block  |     |     |     |     | 0.4 |     |     |     |     |
| ----------- | --- | --- | ----------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
+25C
| Diagram. |     |     |     |     |     |     |     | 0.2 |     |     |     | +85C |
| -------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---- |
+125C
| The characteristics of the wiper are determined by the |     |     |     |     |     |     |     | 0.0 |     |     |     |     |
| ------------------------------------------------------ | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
characteristics  of  the  wiper  switch  at  each  of  the 0 32 64 96 128 160 192 224 256
Wiper Code
| resistor  | networks  |     | tap  points.  | FigureB-7  |     | shows  an |     |     |     |     |     |     |
| --------- | --------- | --- | ------------- | ---------- | --- | --------- | --- | --- | --- | --- | --- | --- |
example of a wiper switch. As the device operational FIGURE B-9: Wiper Voltage (V ) vs.
W
voltage becomes lower, the characteristics of the wiper Wiper Code (V  = 1.8V, I  = 190 µA).
|                                               |     |     |     |     |     |           |     |     | DD  |     | W   |     |
| --------------------------------------------- | --- | --- | --- | --- | --- | --------- | --- | --- | --- | --- | --- | --- |
| switch change due to a lower voltage on the V |     |     |     |     |     |  signal.  |     |     |     |     |     |     |
G
FigureB-7  shows an implementation of a wiper switch.
When the transistor is turned off, the switch resistance
is in the Giga s. When the  transistor is turned on, the
| switch resistance is dependent on the V |     |     |     |     |     | , V  and |     |     |     |     |     |     |
| --------------------------------------- | --- | --- | --- | --- | --- | -------- | --- | --- | --- | --- | --- | --- |
G W
| V   |  voltages. This resistance is referred to as R |     |     |     |     | .   |     |     |     |     |     |     |
| --- | ---------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| WCn |                                                |     |     |     |     | W   |     |     |     |     |     |     |

R  (1)
W
|     |     |     |     | V   |  (V  | /V )  |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | ---- | ----- | --- | --- | --- | --- | --- | --- |
|     |     |     |     |     | G DD | SS    |     |     |     |     |     |     |
“gate”
NMOS
|     | N WC    |     |      |     | Wiper |     |     |     |     |     |     |     |
| --- | ------- | --- | ---- | --- | ----- | --- | --- | --- | --- | --- | --- | --- |
|     | V WCn   |     | PMOS |     | V     |     |     |     |     |     |     |     |
W
“gate”
|     | Note1: | Wiper Resistance (R |     |     | ) depends on the |     |     |     |     |     |     |     |
| --- | ------ | ------------------- | --- | --- | ---------------- | --- | --- | --- | --- | --- | --- | --- |
W
voltages at the wiper switch nodes
|                                       |     | (V , V |  and V        | ).  |     |     |     |     |     |     |     |                  |
| ------------------------------------- | --- | ------ | ------------- | --- | --- | --- | --- | --- | --- | --- | --- | ---------------- |
|                                       |     | G      | W             | WCn |     |     |     |     |     |     |     |                  |
| FIGURE B-7:                           |     |        | Wiper Switch. |     |     |     |     |     |     |     |     |                  |
|  2008-2013 Microchip Technology Inc. |     |        |               |     |     |     |     |     |     |     |     | DS22096B-page 95 |

MCP453X/455X/463X/465X
Using the simulation models of the NMOS and PMOS
devices for the MCP4XXX analog switch (FigureB-10),
|     |     |     |     |     |     |     |     | 7.00E+09 |     |     |     |     | 160 |
| --- | --- | --- | --- | --- | --- | --- | --- | -------- | --- | --- | --- | --- | --- |
RNMOS
we plot the device resistance when the devices are
|     |     |     |     |     |     |     |     |  ecnatsiseR SOMP dna SOMN 6.00E+09 |     |     |     |     | 140 |
| --- | --- | --- | --- | --- | --- | --- | --- | ---------------------------------- | --- | --- | --- | --- | --- |
turned  on.  FigureB-11  and  FigureB-12  show  the RPMOS  RW
)(cid:2)( ecnatsiseR repiW
| resistances of the NMOS and PMOS devices as the |                                                |     |     |     |     |       |     | 5.00E+09 |     |     |     |     | 120 |
| ----------------------------------------------- | ---------------------------------------------- | --- | --- | --- | --- | ----- | --- | -------- | --- | --- | --- | --- | --- |
| V                                               |  voltage is increased. The wiper resistance (R |     |     |     |     | )  is |     |          |     |     |     |     | 100 |
| IN                                              |                                                |     |     |     |     | W     |     | 4.00E+09 |     |     |     |     |     |
simply the parallel resistance on the NMOS and PMOS
|     |     |     |     |     |     |     |     | )(cid:2)( |     |     |       |     | 80  |
| --- | --- | --- | --- | --- | --- | --- | --- | --------- | --- | --- | ----- | --- | --- |
|     |     |     |     |     |     |     |     | 3.00E+09  |     |     | NMOS  |     |     |
devices (R W  = R NMOS  || R PMOS ). Below the threshold PMOS Theshold 60
voltage  for  the  NMOS  and  PMOS  devices,  the 2.00E+09 Theshold
40
| resistance  |     | becomes  | very  large  | (Giga  | s).  | In  the |     |     |     |     |     |     |     |
| ----------- | --- | -------- | ------------ | ------ | ----- | ------- | --- | --- | --- | --- | --- | --- | --- |
1.00E+09
| transistor’s active region, the resistance is much lower. |     |     |     |     |     |     |     |     |     |     |     |     | 20  |
| --------------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
For these graphs, the resistances are on different 0.00E+00 0
|     |     |     |     |     |     |     |     |     | 0.0 | 0.6 1.2 | 1.8 | 2.4 | 3.0 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ------- | --- | --- | --- |
scales.  FigureB-13  and  FigureB-14  only  plot  the VIN Voltage
NMOS and PMOS device resistance for their active
|     |     |     |     |     |     |     | FIGURE B-12: |     |     | NMOS and PMOS  |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | ------------ | --- | --- | -------------- | --- | --- | --- |
region and the resulting wiper resistance. For these
graphs, all resistances are on the same scale.  Transistor Resistance (R , R ) and
|     |     |     |     |     |     |     |                     |     |     | NMOS    |     | PMOS |     |
| --- | --- | --- | --- | --- | --- | --- | ------------------- | --- | --- | ------- | --- | ---- | --- |
|     |     |     |     |     |     |     | Wiper Resistance (R |     |     | ) VS. V |     |      |     |
|     |     |     |     |     |     |     |                     |     |     | W       | IN  |      |     |
(V DD  = 1.8V).
R W
|     |     |     |     | V G |  (V DD /V | SS )  |     |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --------- | ----- | --- | --- | --- | --- | --- | --- | --- |
“gate”
300
NMOS
|     | V   |     |     |     | V   |     |     | 250 |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|     | IN  |     |     |     |     | OUT |     |     |     |     |     |     |     |
PMOS
200
|     |     |     |     |     |     |     |     | )(cid:2)( ecnatsiseR | RNMOS  |     |     | RPMOS  |     |
| --- | --- | --- | --- | --- | --- | --- | --- | -------------------- | ------ | --- | --- | ------ | --- |
“gate”
150
| FIGURE B-10: |     |     | Analog Switch.  |     |     |     |     |     |     |     |     |     |     |
| ------------ | --- | --- | --------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
100
RW
50
|     | 3.00E+10 |     |     |        |     | 2500 |     |     |     |     |     |     |     |
| --- | -------- | --- | --- | ------ | --- | ---- | --- | --- | --- | --- | --- | --- | --- |
|     |          |     | RW  | RNMOS  |     |      |     | 0   |     |     |     |     |     |
 ecnatsiseR SOMP dna SOMN
|     | 2.50E+10 |        |     |     |     |                                 |     | 0.0 | 0.6 | 1.2         | 1.8 | 2.4 | 3.0 |
| --- | -------- | ------ | --- | --- | --- | ------------------------------- | --- | --- | --- | ----------- | --- | --- | --- |
|     |          | RPMOS  |     |     |     | 2000 )(cid:2)( ecnatsiseR repiW |     |     |     | VIN Voltage |     |     |     |
2.00E+10
|     |     |     |     |     |     |     | FIGURE B-13: |     |     | NMOS and PMOS  |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | ------------ | --- | --- | -------------- | --- | --- | --- |
1500
|     | )(cid:2)( 1.50E+10 |     |     |     |     |      | Transistor Resistance (R |     |     |         | , R |      | ) and  |
| --- | ------------------ | --- | --- | --- | --- | ---- | ------------------------ | --- | --- | ------- | --- | ---- | ------ |
|     |                    |     |     |     |     |      |                          |     |     | NMOS    |     | PMOS |        |
|     |                    |     |     |     |     | 1000 | Wiper Resistance (R      |     |     | ) VS. V |     |      |        |
|     | 1.00E+10           |     |     |     |     |      |                          |     |     | W       | IN  |      |        |
(V  = 3.0V).
|     |          |          |     | NMOS     |     |     |     | DD  |     |     |     |     |     |
| --- | -------- | -------- | --- | -------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|     |          | PMOS     |     |          |     | 500 |     |     |     |     |     |     |     |
|     | 5.00E+09 |          |     | Theshold |     |     |     |     |     |     |     |     |     |
|     |          | Theshold |     |          |     |     |     |     |     |     |     |     |     |
|     | 0.00E+00 |          |     |          |     | 0   |     |     |     |     |     |     |     |
5000
|     |     | 0.0 | 0.3 0.6 0.9 | 1.2 | 1.5 1.8 |     |     |     |     |     |     |     |     |
| --- | --- | --- | ----------- | --- | ------- | --- | --- | --- | --- | --- | --- | --- | --- |
4500
VIN Voltage
4000
| FIGURE B-11: |     |     | NMOS and PMOS  |     |     |     |     | 3500 |     |     |     |     |     |
| ------------ | --- | --- | -------------- | --- | --- | --- | --- | ---- | --- | --- | --- | --- | --- |
)(cid:2)( ecnatsiseR
| Transistor Resistance (R |           |     |         | , R  | ) and  |     |     | 3000 |        |     |        |     |     |
| ------------------------ | --------- | --- | ------- | ---- | ------ | --- | --- | ---- | ------ | --- | ------ | --- | --- |
|                          |           |     | NMOS    | PMOS |        |     |     |      | RNMOS  |     | RPMOS  |     |     |
| Wiper Resistance (R      |           |     | ) VS. V |      |        |     |     | 2500 |        |     |        |     |     |
|                          |           |     | W       | IN   |        |     |     |      |        |     |        |     |     |
| (V                       |  = 3.0V). |     |         |      |        |     |     | 2000 |        |     | RW     |     |     |
DD
1500
1000
500
0
|     |     |     |     |     |     |     |     | 0.0 | 0.3 | 0.6 | 0.9 | 1.2 1.5 | 1.8 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ------- | --- |
VIN Voltage
|     |     |     |     |     |     |     | FIGURE B-14:             |     |     | NMOS and PMOS  |     |      |        |
| --- | --- | --- | --- | --- | --- | --- | ------------------------ | --- | --- | -------------- | --- | ---- | ------ |
|     |     |     |     |     |     |     | Transistor Resistance (R |     |     | NMOS           | , R | PMOS | ) and  |
|     |     |     |     |     |     |     | Wiper Resistance (R      |     |     | ) VS. V        |     |      |        |
|     |     |     |     |     |     |     |                          |     |     | W              | IN  |      |        |
(V  = 1.8V).
DD
| DS22096B-page 96 |     |     |     |     |     |     |     |     |  2008-2013 Microchip Technology Inc. |     |     |     |     |
| ---------------- | --- | --- | --- | --- | --- | --- | --- | --- | ------------------------------------- | --- | --- | --- | --- |

MCP453X/455X/463X/465X
B.2 Optimizing Circuit Design for Low-
Voltage Characteristics
R1
| The  | low-voltage  | nonlinear  | characteristics  |     | can  | be  |     |     | V   |     |     |     |
| ---- | ------------ | ---------- | ---------------- | --- | ---- | --- | --- | --- | --- | --- | --- | --- |
A
| minimized by application design. The section will show |     |     |     |     |     |     |     | A   |     |     |     |     |
| ------------------------------------------------------ | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
V W
two application circuits that can be used to control a
W
| programmable reference voltage (V |     |     |     | ).  |     |     |     |     |     |       |     |     |
| --------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ----- | --- | --- |
|                                   |     |     |     | OUT |     |     |     |     |     | V OUT |     |     |
Minimizing the low-voltage nonlinear characteristics is
done by keeping the voltages on the wiper switch
B
| nodes at a voltage where either the NMOS or PMOS |     |     |     |     |     |     |     | V   | B   |     |     |     |
| ------------------------------------------------ | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| transistor is turned on.                         |     |     |     |     |     |     |     | R2  |     |     |     |     |
An example of this is if we are using a digital potentiom-
| eter for a voltage reference (V |     |     |     | ). Let’s say that we |     |     |     |     |     |     |     |     |
| ------------------------------- | --- | --- | --- | -------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
OUT
want V  to range from 0.5 * V  to 0.6 * V .  FIGURE B-15: Example Implementation #1.
|              | OUT |                 | DD  |                | DD  |     |            |                     |     |     |     |     |
| ------------ | --- | --------------- | --- | -------------- | --- | --- | ---------- | ------------------- | --- | --- | --- | --- |
| In  example  |     | implementation  | #1  | (FigureB-15),  |     | we  |            |                     |     |     |     |     |
|              |     |                 |     |                |     |     | TABLE B-1: | EXAMPLE #1 VOLTAGE  |     |     |     |     |
window the digital potentiometer using resistors R1 and
CALCULATIONS
| R2. When the wiper code is at full scale, the V |     |     |     |     |     | OUT |     |     |     |     |     |     |
| ----------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
voltage will be  0.6 * V  and when the wiper code is Variation
DD,
| at zero scale, the V |     |  voltage will be  0.5 * V |     |     |     | .   |     |     |     |     |     |     |
| -------------------- | --- | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|                      |     | OUT                        |     |     |     | DD  |     |     |     |     |     |     |
Remember that the digital potentiometers R  variation Min Typ Max
AB
| must be included. TableB-1 shows that the V |                                          |     |     |     |     |  volt- |     |        |     |        |        |     |
| ------------------------------------------- | ---------------------------------------- | --- | --- | --- | --- | ------ | --- | ------ | --- | ------ | ------ | --- |
|                                             |                                          |     |     |     | OUT |        | R1  | 12,000 |     | 12,000 | 12,000 |     |
| age can be selected to be between 0.455 * V |                                          |     |     |     | DD  |  and   |     |        |     |        |        |     |
|                                             |                                          |     |     |     |     |        | R2  | 20,000 |     | 20,000 | 20,000 |     |
| 0.727 * V                                   | , which includes the desired range. With |     |     |     |     |        |     |        |     |        |        |     |
DD
respect to the voltages on the resistor network node, at R AB 8,000 10,000 12,000
1.8V the V  voltage would range from 1.29V to 1.31V, V  (@ FS) 0.714 V   0.70 V   0.727 V
|             | A                                         |     |     |     |     |     | OUT       |         | DD  | DD       |           | DD  |
| ----------- | ----------------------------------------- | --- | --- | --- | --- | --- | --------- | ------- | --- | -------- | --------- | --- |
| while the V |  voltage would range from 0.82V to 0.86V. |     |     |     |     |     |           |         |     |          |           |     |
|             | B                                         |     |     |     |     |     | V  (@ ZS) | 0.476 V |     |   0.50 V |   0.455 V |     |
|             |                                           |     |     |     |     |     | OUT       |         | DD  | DD       |           | DD  |
These voltages cause the wiper resistance to be in the
|     |     |     |     |     |     |     | V    | 0.714 V |     |   0.70 V |   0.727 V |     |
| --- | --- | --- | --- | --- | --- | --- | ---- | ------- | --- | -------- | --------- | --- |
nonlinear region (seeFigureB-12). In Potentiometer A DD DD DD
mode, the variation of the wiper resistance is typically V    0.476 V   0.50 V   0.455 V
|          |         |            |          |          |       |     | B       |                                  | DD  | DD  |     | DD  |
| -------- | ------- | ---------- | -------- | -------- | ----- | --- | ------- | -------------------------------- | --- | --- | --- | --- |
| not  an  | issue,  | as  shown  | by  the  | INL/DNL  | graph |     |         |                                  |     |     |     |     |
|          |         |            |          |          |       |     | Legend: | FS – Full Scale, ZS – Zero Scale |     |     |     |     |
(Figure2-7).
In example implementation #2 (FigureB-16), we use
the digital potentiometer in Rheostat mode. The resis-
| tor ladder uses resistors R1 and R2 with R |     |     |     |     |  at the |     |     |     |     |     |     |     |
| ------------------------------------------ | --- | --- | --- | --- | ------- | --- | --- | --- | --- | --- | --- | --- |
BW
bottom of the ladder. When the wiper code is at full
| scale, the V                           |     |  voltage will be  0.6 * V |     |                  | , and when |     |     |     |     |     |     |     |
| -------------------------------------- | --- | -------------------------- | --- | ---------------- | ---------- | --- | --- | --- | --- | --- | --- | --- |
|                                        | OUT |                            |     | DD               |            |     |     |     |     |     |     |     |
| the wiper code is at full scale, the V |     |                            |     |  voltage will be |            |     |     |     |     |     |     |     |
OUT
|  0.5 * V | DD . Remember that the digital potentiometers |     |     |     |     |     |     |     |     |     |     |     |
| --------- | --------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
R  variation must be included. TableB-2 shows that
AB
| the  V |   voltage can  | be  | selected  | to  | be  between |     |     |     |     |     |     |     |
| ------ | -------------- | --- | --------- | --- | ----------- | --- | --- | --- | --- | --- | --- | --- |
OUT
| 0.50*V |  and 0.687 * V |     | , which includes the desired |     |     |     |     |     |     |     |     |     |
| ------ | -------------- | --- | ---------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|        | DD             | DD  |                              |     |     |     |     |     |     |     |     |     |
range. With respect to the voltages on the resistor net-
| work node, at 1.8V the V |             | W      |  voltage would range from |        |      |       |     |     |     |     |     |     |
| ------------------------ | ----------- | ------ | ------------------------- | ------ | ---- | ----- | --- | --- | --- | --- | --- | --- |
| 0.29V                    | to  0.38V.  | These  | voltages                  | cause  | the  | wiper |     |     |     |     |     |     |
resistance to be in the linear region (see FigureB-12).
|  2008-2013 Microchip Technology Inc. |     |     |     |     |     |     |     |     |     | DS22096B-page 97 |     |     |
| ------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---------------- | --- | --- |

MCP453X/455X/463X/465X
R1
V
OUT
R2
V
A A
W
V
W
B
V
B
FIGURE B-16: Example Implementation #2.
TABLE B-2: EXAMPLE #2 VOLTAGE
CALCULATIONS
Variation
Min Typ Max
R1 10,000 10,000 10,000
R2 10,000 10,000 10,000
R (max) 8,000 10,000 12,000
BW
V (@ FS) 0.667 V 0.643 V 0.687 V
OUT DD DD DD
V (@ ZS) 0.50 V 0.50 V 0.50 V
OUT DD DD DD
V (@ FS) 0.333 V 0.286 V 0.375 V
W DD DD DD
V (@ ZS) V V V
W SS SS SS
Legend: FS – Full Scale, ZS – Zero Scale
DS22096B-page 98  2008-2013 Microchip Technology Inc.

MCP453X/455X/463X/465X
PRODUCT IDENTIFICATION SYSTEM
To order or obtain information, e.g., on pricing or delivery, refer to the factory or the listed sales office.
| PART NO. | XXX                    | X /XX   | Examples:           |                   |
| -------- | ---------------------- | ------- | ------------------- | ----------------- |
|          |                        |         | a) MCP4531-502E/XX: | 5k 8LD Device   |
|          |                        |         | b) MCP4531-103E/XX: | 10k, 8-LD Device |
| Device   | Resistance Temperature | Package |                     |                   |
|          |                        |         | c) MCP4531-503E/XX: | 50k, 8LD Device  |
|          | Version                | Range   | d) MCP4531-104E/XX: | 100k, 8LD Device |
e) MCP4531T-104E/XX:T/R,100k,8LD Device

Device: MCP4531: Single Nonvolatile 7-bit Potentiometer a) MCP4532-502E/XX: 5k 8LD Device
MCP4531T: Single Nonvolatile 7-bit Potentiometer b) MCP4532-103E/XX: 10k, 8-LD Device
|     |          | (Tape and Reel)                   | c) MCP4532-503E/XX: | 50k, 8LD Device  |
| --- | -------- | --------------------------------- | ------------------- | ----------------- |
|     | MCP4532: | Single Nonvolatile 7-bit Rheostat |                     |                   |
|     |          |                                   | d) MCP4532-104E/XX: | 100k, 8LD Device |
MCP4532T: Single Nonvolatile 7-bit Rheostat  e) MCP4532T-104E/XX:T/R, 100k, 8LD Device
(Tape and Reel)
MCP4551: Single Nonvolatile 8-bit Potentiometer a) MCP4551-502E/XX: 5k 8LD Device
MCP4551T: Single Nonvolatile 8-bit Potentiometer  b) MCP4551-103E/XX: 10k, 8-LD Device
(Tape and Reel)
|     |     |     | c) MCP4551-503E/XX: | 50k, 8LD Device |
| --- | --- | --- | ------------------- | ---------------- |
MCP4552: Single Nonvolatile 8-bit Rheostat d) MCP4551-104E/XX: 100k, 8LD Device
|     | MCP4552T: | Single Nonvolatile 8-bit Rheostat  |                      |                        |
| --- | --------- | ---------------------------------- | -------------------- | ---------------------- |
|     |           |                                    | e) MCP4551T-104E/XX: | T/R, 100k, 8LD Device |
(Tape and Reel)
MCP4631: Dual Nonvolatile 7-bit Potentiometer a) MCP4552-502E/XX: 5k 8LD Device
|     | MCP4631T: | Dual Nonvolatile 7-bit Potentiometer |                     |                   |
| --- | --------- | ------------------------------------ | ------------------- | ----------------- |
|     |           |                                      | b) MCP4552-103E/XX: | 10k, 8-LD Device |
|     |           | (Tape and Reel)                      | c) MCP4552-503E/XX: | 50k, 8LD Device  |
MCP4632: Dual Nonvolatile 7-bit Rheostat d) MCP4552-104E/XX: 100k, 8LD Device
MCP4632T: Dual Nonvolatile 7-bit Rheostat  e) MCP4552T-104E/XX:T/R, 100k, 8LD Device
(Tape and Reel)
|     | MCP4651: | Dual Nonvolatile 8-bit Potentiometer |                     |                 |
| --- | -------- | ------------------------------------ | ------------------- | --------------- |
|     |          |                                      | a) MCP4631-502E/XX: | 5k 8LD Device |
MCP4651T: Dual Nonvolatile 8-bit Potentiometer  b) MCP4631-103E/XX: 10k, 8-LD Device
(Tape and Reel)
|     |     |     | c) MCP4631-503E/XX: | 50k, 8LD Device |
| --- | --- | --- | ------------------- | ---------------- |
MCP4652: Dual Nonvolatile8-bit Rheostat d) MCP4631-104E/XX: 100k, 8LD Device
MCP4652T: Dual Nonvolatile 8-bit Rheostat  e) MCP4631T-104E/XX:T/R, 100k, 8LD Device
(Tape and Reel)
|                     |            |     | a) MCP4632-502E/XX: | 5k 8LD Device   |
| ------------------- | ---------- | --- | ------------------- | ----------------- |
|                     |            |     | b) MCP4632-103E/XX: | 10k, 8-LD Device |
| Resistance Version: | 502 = 5k  |     |                     |                   |
|                     |            |     | c) MCP4632-503E/XX: | 50k, 8LD Device  |
|                     | 103 = 10k |     | d) MCP4632-104E/XX: | 100k, 8LD Device |
503 = 50k
|     |     |     | e) MCP4632T-104E/XX: | T/R, 100k, 8LD Device |
| --- | --- | --- | -------------------- | ---------------------- |
104 = 100k
|     |     |     | a) MCP4651-502E/XX: | 5k 8LD Device   |
| --- | --- | --- | ------------------- | ----------------- |
|     |     |     | b) MCP4651-103E/XX: | 10k, 8-LD Device |
Temperature Range: E = -40°C to +125°C c) MCP4651-503E/XX: 50k, 8LD Device
|          |      |                                                | d) MCP4651-104E/XX:  | 100k, 8LD Device      |
| -------- | ---- | ---------------------------------------------- | -------------------- | ---------------------- |
|          |      |                                                | e) MCP4651T-104E/XX: | T/R, 100k, 8LD Device |
| Package: | MF = | Plastic Dual Flat No-lead (3x3 DFN), 8/10-lead |                      |                        |
ML = Plastic Quad Flat No-lead (QFN), 16-lead a) MCP4652-502E/XX: 5k 8LD Device
MS = Plastic Micro Small Outline (MSOP), 8-lead b) MCP4652-103E/XX: 10k, 8-LD Device
|     | ST = | Plastic Thin Shrink Small Outline (TSSOP), 14-lead |                     |                  |
| --- | ---- | -------------------------------------------------- | ------------------- | ---------------- |
|     |      |                                                    | c) MCP4652-503E/XX: | 50k, 8LD Device |
UN = Plastic Micro Small Outline (MSOP), 10-lead d) MCP4652-104E/XX: 100k, 8LD Device
|     |     |     | e) MCP4652T-104E/XX: | T/R, 100k, 8LD Device |
| --- | --- | --- | -------------------- | ---------------------- |
XX = MF for 8/10-lead 3x3 DFN
= ML for 16-lead QFN
= MS for 8-lead MSOP
= ST for 14-lead TSSOP
= UN for 10-lead MSOP
|  2008-2013 Microchip Technology Inc. |     |     |     | DS22096B-page 99 |
| ------------------------------------- | --- | --- | --- | ---------------- |

MCP453X/455X/463X/465X
NOTES:
DS22096B-page 100  2008-2013 Microchip Technology Inc.

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
The Microchip name and logo, the Microchip logo, dsPIC,
and may be superseded by updates. It is your responsibility to
FlashFlex, KEELOQ, KEELOQ logo, MPLAB, PIC, PICmicro,
ensure that your application meets with your specifications. PICSTART, PIC32 logo, rfPIC, SST, SST Logo, SuperFlash
MICROCHIP MAKES NO REPRESENTATIONS OR
and UNI/O are registered trademarks of Microchip Technology
WARRANTIES OF ANY KIND WHETHER EXPRESS OR
Incorporated in the U.S.A. and other countries.
IMPLIED, WRITTEN OR ORAL, STATUTORY OR
OTHERWISE, RELATED TO THE INFORMATION, FilterLab, Hampshire, HI-TECH C, Linear Active Thermistor,
INCLUDING BUT NOT LIMITED TO ITS CONDITION, MTP, SEEVAL and The Embedded Control Solutions
QUALITY, PERFORMANCE, MERCHANTABILITY OR Company are registered trademarks of Microchip Technology
FITNESS FOR PURPOSE. Microchip disclaims all liability Incorporated in the U.S.A.
arising from this information and its use. Use of Microchip Silicon Storage Technology is a registered trademark of
devices in life support and/or safety applications is entirely at Microchip Technology Inc. in other countries.
the buyer’s risk, and the buyer agrees to defend, indemnify and
Analog-for-the-Digital Age, Application Maestro, BodyCom,
hold harmless Microchip from any and all damages, claims,
chipKIT, chipKIT logo, CodeGuard, dsPICDEM,
suits, or expenses resulting from such use. No licenses are
dsPICDEM.net, dsPICworks, dsSPEAK, ECAN,
conveyed, implicitly or otherwise, under any Microchip
ECONOMONITOR, FanSense, HI-TIDE, In-Circuit Serial
intellectual property rights.
Programming, ICSP, Mindi, MiWi, MPASM, MPF, MPLAB
Certified logo, MPLIB, MPLINK, mTouch, Omniscient Code
Generation, PICC, PICC-18, PICDEM, PICDEM.net, PICkit,
PICtail, REAL ICE, rfLAB, Select Mode, SQI, Serial Quad I/O,
Total Endurance, TSHARC, UniWinDriver, WiperLock, ZENA
and Z-Scale are trademarks of Microchip Technology
Incorporated in the U.S.A. and other countries.
SQTP is a service mark of Microchip Technology Incorporated
in the U.S.A.
GestIC and ULPP are registered trademarks of Microchip
Technology Germany II GmbH & Co. & KG, a subsidiary of
Microchip Technology Inc., in other countries.
All other trademarks mentioned herein are property of their
respective companies.
© 2008-2013, Microchip Technology Incorporated, Printed in
the U.S.A., All Rights Reserved.
Printed on recycled paper.
ISBN: 978-1-62077-023-8
QUALITY MANAGEMENT SYSTEM
Microchip received ISO/TS-16949:2009 certification for its worldwide
headquarters, design and wafer fabrication facilities in Chandler and
CERTIFIED BY DNV Tempe, Arizona; Gresham, Oregon and design centers in California
and India. The Company’s quality system processes and procedures
== ISO/TS 16949 == are for its PIC® MCUs and dsPIC® DSCs, KEELOQ® code hopping
devices, Serial EEPROMs, microperipherals, nonvolatile memory and
analog products. In addition, Microchip’s quality system for the design
and manufacture of development systems is ISO 9001:2000 certified.
 2008-2013 Microchip Technology Inc. DS22096B-page 101

Worldwide Sales and Service
| AMERICAS | ASIA/PACIFIC | ASIA/PACIFIC | EUROPE |
| -------- | ------------ | ------------ | ------ |
Corporate Office Asia Pacific Office India - Bangalore Austria - Wels
2355 West Chandler Blvd. Suites 3707-14, 37th Floor Tel: 91-80-3090-4444  Tel: 43-7242-2244-39
Chandler, AZ 85224-6199 Tower 6, The Gateway Fax: 91-80-3090-4123 Fax: 43-7242-2244-393
| Tel: 480-792-7200  | Harbour City, Kowloon |                   |                      |
| ------------------ | --------------------- | ----------------- | -------------------- |
|                    |                       | India - New Delhi | Denmark - Copenhagen |
| Fax: 480-792-7277  | Hong Kong             |                   | Tel: 45-4450-2828    |
Tel: 91-11-4160-8631
| Technical Support:  | Tel: 852-2401-1200 |     | Fax: 45-4485-2829 |
| ------------------- | ------------------ | --- | ----------------- |
Fax: 91-11-4160-8632
http://www.microchip.com/
|     | Fax: 852-2401-3431 | India - Pune | France - Paris |
| --- | ------------------ | ------------ | -------------- |
support
|     | Australia - Sydney | Tel: 91-20-2566-1512 | Tel: 33-1-69-53-63-20  |
| --- | ------------------ | -------------------- | ---------------------- |
Web Address:
|     | Tel: 61-2-9868-6733 | Fax: 91-20-2566-1513 | Fax: 33-1-69-30-90-79 |
| --- | ------------------- | -------------------- | --------------------- |
www.microchip.com
|                    | Fax: 61-2-9868-6755   |                      | Germany - Munich      |
| ------------------ | --------------------- | -------------------- | --------------------- |
| Atlanta            |                       | Japan - Osaka        |                       |
|                    | China - Beijing       |                      | Tel: 49-89-627-144-0  |
| Duluth, GA         |                       | Tel: 81-6-6152-7160  |                       |
|                    | Tel: 86-10-8569-7000  |                      | Fax: 49-89-627-144-44 |
| Tel: 678-957-9614  |                       | Fax: 81-6-6152-9310  |                       |
Fax: 86-10-8528-2104
| Fax: 678-957-1455 |     |     | Italy - Milan  |
| ----------------- | --- | --- | -------------- |
Japan - Tokyo
|                    | China - Chengdu      |                       | Tel: 39-0331-742611  |
| ------------------ | -------------------- | --------------------- | -------------------- |
| Boston             |                      | Tel: 81-3-6880- 3770  |                      |
|                    | Tel: 86-28-8665-5511 |                       | Fax: 39-0331-466781  |
| Westborough, MA    |                      | Fax: 81-3-6880-3771   |                      |
|                    | Fax: 86-28-8665-7889 |                       | Netherlands - Drunen |
| Tel: 774-760-0087  |                      | Korea - Daegu         |                      |
|                    | China - Chongqing    |                       | Tel: 31-416-690399   |
| Fax: 774-760-0088  |                      | Tel: 82-53-744-4301   |                      |
|                    | Tel: 86-23-8980-9588 |                       | Fax: 31-416-690340   |
| Chicago            |                      | Fax: 82-53-744-4302   |                      |
Fax: 86-23-8980-9500
| Itasca, IL  |     |     | Spain - Madrid |
| ----------- | --- | --- | -------------- |
Korea - Seoul
Tel: 630-285-0071  China - Hangzhou Tel: 82-2-554-7200 Tel: 34-91-708-08-90
Fax: 630-285-0075 Tel: 86-571-2819-3187  Fax: 82-2-558-5932 or  Fax: 34-91-708-08-91
|     | Fax: 86-571-2819-3189 | 82-2-558-5934 | UK - Wokingham |
| --- | --------------------- | ------------- | -------------- |
Cleveland
| Independence, OH   |                       |                         | Tel: 44-118-921-5869 |
| ------------------ | --------------------- | ----------------------- | -------------------- |
|                    | China - Hong Kong SAR | Malaysia - Kuala Lumpur |                      |
| Tel: 216-447-0464  |                       |                         | Fax: 44-118-921-5820 |
|                    | Tel: 852-2943-5100    | Tel: 60-3-6201-9857     |                      |
Fax: 216-447-0643
|        | Fax: 852-2401-3431 | Fax: 60-3-6201-9859 |     |
| ------ | ------------------ | ------------------- | --- |
| Dallas | China - Nanjing    |                     |     |
Malaysia - Penang
| Addison, TX  | Tel: 86-25-8473-2460 |     |     |
| ------------ | -------------------- | --- | --- |
Tel: 60-4-227-8870
| Tel: 972-818-7423  | Fax: 86-25-8473-2470 |     |     |
| ------------------ | -------------------- | --- | --- |
Fax: 60-4-227-4068
Fax: 972-818-2924
|     | China - Qingdao | Philippines - Manila |     |
| --- | --------------- | -------------------- | --- |
Detroit
|     | Tel: 86-532-8502-7355 | Tel: 63-2-634-9065 |     |
| --- | --------------------- | ------------------ | --- |
Farmington Hills, MI
|     | Fax: 86-532-8502-7205 | Fax: 63-2-634-9069 |     |
| --- | --------------------- | ------------------ | --- |
Tel: 248-538-2250
China - Shanghai
| Fax: 248-538-2260 |     | Singapore |     |
| ----------------- | --- | --------- | --- |
Tel: 86-21-5407-5533
Tel: 65-6334-8870
| Indianapolis      | Fax: 86-21-5407-5066 |                     |     |
| ----------------- | -------------------- | ------------------- | --- |
| Noblesville, IN   |                      | Fax: 65-6334-8850   |     |
| Tel: 317-773-8323 | China - Shenyang     | Taiwan - Hsin Chu   |     |
| Fax: 317-773-5453 | Tel: 86-24-2334-2829 | Tel: 886-3-5778-366 |     |
|                   | Fax: 86-24-2334-2393 | Fax: 886-3-5770-955 |     |
Los Angeles
China - Shenzhen
| Mission Viejo, CA  |     | Taiwan - Kaohsiung |     |
| ------------------ | --- | ------------------ | --- |
Tel: 86-755-8864-2200
| Tel: 949-462-9523  |     | Tel: 886-7-213-7828 |     |
| ------------------ | --- | ------------------- | --- |
Fax: 86-755-8203-1760
| Fax: 949-462-9608 |               | Fax: 886-7-330-9305 |     |
| ----------------- | ------------- | ------------------- | --- |
|                   | China - Wuhan | Taiwan - Taipei     |     |
Santa Clara
|     | Tel: 86-27-5980-5300 | Tel: 886-2-2508-8600  |     |
| --- | -------------------- | --------------------- | --- |
Santa Clara, CA
|     | Fax: 86-27-5980-5118 | Fax: 886-2-2508-0102 |     |
| --- | -------------------- | -------------------- | --- |
Tel: 408-961-6444
| Fax: 408-961-6445      | China - Xian         | Thailand - Bangkok |     |
| ---------------------- | -------------------- | ------------------ | --- |
| Toronto                | Tel: 86-29-8833-7252 | Tel: 66-2-694-1351 |     |
| Mississauga, Ontario,  | Fax: 86-29-8833-7256 | Fax: 66-2-694-1350 |     |
| Canada                 | China - Xiamen       |                    |     |
| Tel: 905-673-0699      | Tel: 86-592-2388138  |                    |     |
| Fax: 905-673-6509      | Fax: 86-592-2388130  |                    |     |
China - Zhuhai
Tel: 86-756-3210040
11/29/12
Fax: 86-756-3210049
| DS22096B-page 102 |     |  2008-2013 Microchip Technology Inc. |     |
| ----------------- | --- | ------------------------------------- | --- |