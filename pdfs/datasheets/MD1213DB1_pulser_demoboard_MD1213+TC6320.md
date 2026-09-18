Supertex inc.
MD1213DB1
MD1213 + TC6320 Demoboard
High Speed ±100V 2A Pulser
General Description Demoboard Features
The MD1213DB1 can drive a transducer as a single chan- ► Demonstrates one channel ultrasound transmitter
nel transmitter for ultrasound and other applications. The ► MD1213 driving a TC6320 power MOSFET
demoboard consists of one MD1213 in a 12-Lead 4x4x0.9mm
► ±2.0 A source and sink current capability
QFN (K6) package, combined with Supertex’s TC6320, an
► Logic control signal input connector
IC containing high voltage P- and N- channel FETs in a 8-
► SMA connectors for cable to a transducer
Lead SOIC package.
► 1.8 to 3.3V CMOS logic interface
Logic control inputs INA, INB and OE of the MD1213 are Designing a Pulser with the MD1213
controlled via the six-pin head connector on the board. Due Low input capacitance and fast switching speed are the
to the fast signal rise and fall time requirement, every ground important features of the MD1213’s input stage. Its logic inputs
wire of the ribbon cable must be used to connect from the have an input impedance of about 20kΩ in parallel with 5pF,
logic signal source. When OE is enabled, it should recieve and an internal speed of around 100MHz. The output enable
the same voltage as the logic source circuit’s power supply. pin, OE, determines the threshold voltage for the input-channel
level translators. The input stage logic is fully compatible with
The MD1213DB1 output waveforms can be displayed direct- 1.8V, 2.0V, 2.5V, 3.3V, or 5.0V CMOS logic. The level translators
ly using an oscilloscope by connecting the scope probe to are also compatible with these logic voltage levels, up to the
the test point TP10-1 and TP10-2 (GND). The J5 jumper can MOSFET’s gate-driver voltage level, which is typically 5.0 to
select whether or not to connect the on-board equivalent- 12V. When OE is low, the chip disables its’ outputs, setting
load, a 220pF 200V capacitor paralleled with a 1.0kΩ, 1W OUTA high and OUTB low. This condition helps to properly pre-
resistor. Also, a coaxial cable can be used to easily connect charge the AC coupling capacitors that the user can optionally
to the user’s transducer. add in series with the gate-driver circuit of the external P/N-
channel FET pair.
Block Diagram
V V V
CC DD H
V DD 1 V DD 2 VH
OE
0 to 100V
OUTA
INA
VCC
1.0µF
OE
XDCF
HV
Level V 2 V OUT
SS L
INA Shifter
V
V 2 H
DD
INB
0 to 100V
C R
L L
OUTB 1.0µF
INB TC6320
MD1213
GND V 1 V 2 VL
SS SS
V V
SS L
Supertex inc.
Doc.# DSDB-MD1213DB1
B032114 www.supertex.com

MD1213DB1
The MD1213’s output stage has separate power pins that  voltage, 2.0A peak current output capabilities, and low input
enable users to select the output signal’s high and low levels  capacitance (110pF maximum). The TC6320 integrates the
independently from the supply voltages used by the main the  gate-source resistors and Zener diodes that a high voltage
circuit. For example, the input logic levels could be 0V and 3.3V,  pulse-driver requires. The high output current capability of the
and the output levels may lie anywhere in the range of ±5.0V.  TC6320 MOSFET speeds output waveform rise and fall time,
while their low input capacitance minimizes propagation de-
Typically, the MD1213’s output has rise and fall times of about  lays. During power up/down conditions, the high voltage sup-
6.0ns when driving a 1000pF load. The output stage is capable  plies V  and V  can inject transient voltages greater than 20V
|     |     |     | PP  | NN  |     |     |
| --- | --- | --- | --- | --- | --- | --- |
of peak currents of up to ±2.0A, depending on the system’s  via the output transistor’s parasitic gate-to-source capacitanc-
supply voltages and load capacitance. Such high currents  es. The maximum permissible gate-to-source voltage (V ) is
GS
are necessary to drive the input capacitances of the output  ±20V. The TC6320’s integral 15 - 18V Zener diodes across its’
MOSFETs for fast switching speeds. gate and source terminals protect against such transient volt-
ages. But even if it is possible to slowly ramp the high voltage
The bottom of the MD1213 12-Lead QFN package has a ther- supplies, these Zener diodes are still crucial, as they also serve
mal pad for power dissipation enhancement. It must externally  as the DC voltage restoration stage for the gates.
connect to the VSS pin on the PCB. This pad is connected
internally to the substrate of the IC circuit. It must have the low- Note that it is possible to vary the V  and V  voltages with-
PP NN
est potential voltage of the circuit at all times, including during  out making significant changes to the circuit configuration. For
the power up or down periods, or it could cause circuit latch-up  example, V  can be 0V and V  +200V for positive unipolar
|     |     |     |     | NN  | PP  |     |
| --- | --- | --- | --- | --- | --- | --- |
or damage. pulses. Or V  can be -200V and V  0V for a negative unipolar
|     |     |     |     | NN  |     | PP  |
| --- | --- | --- | --- | --- | --- | --- |
pulser. If the user plans to operate the demoboard above 100V,
The Supertex TC6320 is comprised of an N- and P-channel  he must adjust the bypass capacitors (C8 or C16) to a voltage
MOSFET pair with low threshold voltages (2.0V maximum).  rating of 200V. Due to the BV limitation of the TC6320, the dif-
This 8-Lead SO packaged device features 200V breakdown  ferential voltage (V -V ) must not be greater then 200V.
|     |     |     |     | PP  | NN  |     |
| --- | --- | --- | --- | --- | --- | --- |
Operating Supply Voltages
| Symbol | Parameter | Min  | Typ | Max | Units | Conditions |
| ------ | --------- | ---- | --- | --- | ----- | ---------- |
| V      |           | -5.5 | 0   | 0   |       |            |
SS
|     | Negative drive supply |     |     |        | V   | (V  - V ) ≤ 13 |
| --- | --------------------- | --- | --- | ------ | --- | -------------- |
| V   |                       | V   | -   | V -2.0 |     | DD SS          |
| L   |                       | SS  |     | DD     |     |                |
| V   |                       | 4.5 | 10  | 12     |     |                |
DD
|     | Positive drive supply |     |     |     | V   | (V  - V ) ≤ 13 |
| --- | --------------------- | --- | --- | --- | --- | -------------- |
DD SS
| V   |              | V +2.0 | 10  | V   |     |     |
| --- | ------------ | ------ | --- | --- | --- | --- |
| H   |              | SS     |     | DD  |     |     |
| V   | Logic supply | 1.8    | 3.3 | 5.5 | V   | --- |
CC
| V   | TC6320 HV positive supply | 0   | -   | 100 | V   | --- |
| --- | ------------------------- | --- | --- | --- | --- | --- |
PP
| V   | TC6320 HV negative supply | -100 | -   | 0   | V   | --- |
| --- | ------------------------- | ---- | --- | --- | --- | --- |
NN
Board Layout
| Doc.# DSDB-MD1213DB1 |     |     |     |     |     | Supertex inc.     |
| -------------------- | --- | --- | --- | --- | --- | ----------------- |
| B032114              |     |     | 2   |     |     |  www.supertex.com |

MD1213DB1
Current Consumption
|                                | Symbol |                            | Typ |     | Units |     | Conditions |     |
| ------------------------------ | ------ | -------------------------- | --- | --- | ----- | --- | ---------- | --- |
|                                | I      |                            | 0.7 |     | mA    |     | V  = 12V   |     |
|                                |        | DD                         |     |     |       |     | DD         |     |
|                                | I      |                            | 0.7 |     | mA    |     | V  = 12V   |     |
|                                |        | H                          |     |     |       |     | H          |     |
|                                | I      |                            | 58  |     | mA    |     | V  = 3.3V  |     |
|                                |        | CC                         |     |     |       |     | CC         |     |
|                                | I      |                            | 2.4 |     | mA    |     | V  = 100V  |     |
|                                |        | PP                         |     |     |       |     | PP         |     |
|                                | I      |                            | 2.5 |     | mA    |     | V  = -100V |     |
|                                |        | NN                         |     |     |       |     | NN         |     |
| Waveform C, 20MHz, 8 cycles, V |        |  = V = 0 Load: 220pF//1.0k |     |     |       |     |            |     |
SS L
Voltage Supply Power-Up Sequence
|     | 1   | V Logic voltage supply, and all OE = INA = INB = Low |     |     |     |     |     |     |
| --- | --- | ---------------------------------------------------- | --- | --- | --- | --- | --- | --- |
CC
|     | 2   | V Positive drive voltage for V |     |     | 1,2 |     |     |     |
| --- | --- | ------------------------------ | --- | --- | --- | --- | --- | --- |
|     |     | DD                             |     |     | DD  |     |     |     |
3 V 0 or -5.0V negative bias voltage for V 1,2 and IC substrate voltage
|     |     | SS                                              |     |                                |     | SS  |     |     |
| --- | --- | ----------------------------------------------- | --- | ------------------------------ | --- | --- | --- | --- |
|     | 4   | V 0 to -5.0V or V                               |     |  negative driver voltage for V |     |     |     |     |
|     |     | L                                               |     | SS                             |     |     | L   |     |
|     | 5   | V 0 to +10 or V                                 |     |  positive driver voltage for V |     |     |     |     |
|     |     | H                                               |     | DD                             |     |     | H   |     |
|     | 6   | V /V +/-HV supply, slew rate not exceed 2.0V/ms |     |                                |     |     |     |     |
|     |     | PP NN                                           |     |                                |     |     |     |     |
Note:
The power-down sequence should be the reverse of the power-up sequence above
Board Connector and Test Pin Description
Logic Control Signal Input Connector
|      | Pin | Name Description                 |     |     |     |     |     |     |
| ---- | --- | -------------------------------- | --- | --- | --- | --- | --- | --- |
| J3-1 |     | VCC Logic voltage supply for VCC |     |     |     |     |     |     |
J3-2 OE MD1213 OE signal for pulser output enable, when OE=0, TC6320 P and N MOSFET both off.
| J3-3 |     | GND Logic ground |     |     |     |     |     |     |
| ---- | --- | ---------------- | --- | --- | --- | --- | --- | --- |
| J3-4 |     | INA ---          |     |     |     |     |     |     |
| J3-5 |     | GND Logic ground |     |     |     |     |     |     |
| J3-6 |     | INB ---          |     |     |     |     |     |     |
Power Supply Connector
|      | Pin | Name Description                    |     |     |     |     |     |     |
| ---- | --- | ----------------------------------- | --- | --- | --- | --- | --- | --- |
| J1-1 |     | VCC +3.3 logic voltage supply for V |     |     |     |     |     |     |
CC
J1-2 VSS 0 or -5.0V negative bias supply for V 1, V 2 and SUB
|     |     |     |     |     |     | SS  | SS  |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
J1-3 VL 0 or -5.0V negative voltage supply for driver output stage
| J1-4 |     | GND Power supply ground                       |     |     |     |     |           |     |
| ---- | --- | --------------------------------------------- | --- | --- | --- | --- | --------- | --- |
| J1-5 |     | VDD +10V positive driver voltage supply for V |     |     |     |     | 1 and V 2 |     |
|      |     |                                               |     |     |     |     | DD DD     |     |
J1-6 VH +10 or +5.0V positive voltage supply for driver output stage
J2-1 VPP 0 to +100V positive high voltage supply with current limiting maximum to 2.0A
| J2-2 |     | GND High voltage power supply return, 0V |     |     |     |     |     |     |
| ---- | --- | ---------------------------------------- | --- | --- | --- | --- | --- | --- |
J2-3 VNN 0 to -100V Negative high voltage supply with current limiting maximum to -2.0A
| Doc.# DSDB-MD1213DB1 |     |     |     |     |     |     |     | Supertex inc.     |
| -------------------- | --- | --- | --- | --- | --- | --- | --- | ----------------- |
| B032114              |     |     |     |     |     | 3   |     |  www.supertex.com |

MD1213DB1
Schematic Diagram
 RCDX
 31-001
 6J
 5
D 1 B
 NNV
|     |     |     |     |     |            |     |  Ωk0.1 |  W0.1 |     |  1  |  2  |     |
| --- | --- | --- | --- | --- | ---------- | --- | ------ | ----- | --- | --- | --- | --- |
|     |     |     |     |     |  11R  Ω002 |     |  51R   |       |     |     |     |     |
 V001
 µ
  6 0
C . 1
|     |     |     |     |     |     |  2  4 |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | ----- | --- | --- | --- | --- | --- | --- |
8PT
5J
 Ω
|     |     |     |  2   |  0  |     |  1  3 |     |     |     |     |     |             |
| --- | --- | --- | ---- | --- | --- | ----- | --- | --- | --- | --- | --- | ----------- |
|     |     |     | 01PT | 1   | 0 0 |       |     |     |     |     |     |             |
|     |     |     |      | R   | 2   |       |     |     |     |     |     | 3    2    1 |
2J
|     |     |     |          |     |     |     |  21C  022 |       |     |     |       |     |
| --- | --- | --- | -------- | --- | --- | --- | --------- | ----- | --- | --- | ----- | --- |
|     |     |     |  1       |     |     |  3  |           |       |     |     |       |     |
|     |     |     | V001     |     |     |     |           |  V    |     |     |       |     |
|     |     |     | 11C µ0.1 |     |     |     |           |  µ    |     |     | V001  |     |
|     |     |     |          |     |     |     |  8C       | 0 0 0 |     |     | µ0    |     |
|     |     |     |          |     |  9  |     |           | .1 1  |     |     | 5 C . |     |
|     |     |     |          |   1 | 9   |     |           |       |     |     | 1     |     |
|     |     |     |          | 1D  | V   |     |           |       |     |     |       |     |
AB
|     |     | PPV |     |     |  1  |  2  |     | NNV |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
 PPV
|     |     |     |     |  3  6 |  5  |  7  8 | 1   |     |     |  1  |  2  |     |
| --- | --- | --- | --- | ----- | --- | ----- | --- | --- | --- | --- | --- | --- |
4 3
|     |     |     |     |     |     |  0236CT |     |     |     |     | D 1-0011B |     |
| --- | --- | --- | --- | --- | --- | ------- | --- | --- | --- | --- | --------- | --- |
|     |     |     |     |     | P   | N       |     |     |     |     |           |     |
 3U
|     |     |     |     |            |  4  |           |  2  |     |     |     |     |     |
| --- | --- | --- | --- | ---------- | --- | --------- | --- | --- | --- | --- | --- | --- |
|     |     |     |     |  n01  V002 |     |  V002     |     |     |     |  HV |     |  LV |
|     |     |     |  9C |            |     |  01C  n01 |     |     |     |     |     |     |
 6  1
 A3D
|     |     |     |  2  |       |     |     | 2   |      |     |  3   |  3  |      |
| --- | --- | --- | --- | ----- | --- | --- | --- | ---- | --- | ---- | --- | ---- |
|     |     |     |     |       |     |     |     |      |     |  B3D |     |  B2D |
|     |     |     | 9PT |       |     |     | 5PT |      |     |      |     |      |
|     |     |     |  1  |       |     |     |     |      |     |  4   |  4  |      |
|     |     |     |     |  Ω002 |     |     | 1   | Ω002 |     |      |     |  SSV |
|     |     |     |     |  9R   |     |     |     | 41R  |     |      |     |      |
 1
 A2
 A
|     |     |     |     | 9   |     | 7   |     |     |     |  6 D | 1D  |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---- | --- | --- |
 52C  0.1
|     |     |     |     |      |     |      |     |     |     |  DDV |       |  CCV |
| --- | --- | --- | --- | ---- | --- | ---- | --- | --- | --- | ---- | ----- | ---- |
|     |     |     |     | ATUO |     | BTUO |  2  |     |     |      |       |      |
|     |     |     |  8  |      |     |      | LV  |     |     |      |  6  1 |      |
|     | H   |     | HV  |      |     |      |     |     |     |      |       |      |
V
V L
|     |     |  42C  0.1 |     |     |     |     |  72C |  1.0 |     |     |     |     |
| --- | --- | --------- | --- | --- | --- | --- | ---- | ---- | --- | --- | --- | --- |
2SSV  6
4PT
|     |     |     |  01 2DDV |     |     |     |     |     |     |  V61      |     |     |
| --- | --- | --- | -------- | --- | --- | --- | --- | --- | --- | --------- | --- | --- |
|     | DD  |     |          |     |     |     |     |     | SS  |  4C +  01 |     |     |
|     |     |     |          |     |     |     | 31  |     | V   |           |     |     |
|     | V   |     |          |     |     |     | BUS |     |     |           |     |     |
 2  02C  1.0
|     |  1BF |     |     |     |     |     |      |      | H   |     |     |     |
| --- | ---- | --- | --- | --- | --- | --- | ---- | ---- | --- | --- | --- | --- |
|     |      |     |     |     |     |     |  82C |  1.0 | V   |     |     |     |
1SSV
|     |  1  |     |     |     |     |     | 5   |     | 3PT |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
 11
|     |     |     | 1DDV |     |     |     |     |     |     |  V61 |     |     |
| --- | --- | --- | ---- | --- | --- | --- | --- | --- | --- | ---- | --- | --- |
 3C +  01
DNG 4
 12C
|     |     |  1.0 |             |     | ANI     | BNI |      |     | DD  |           |     |     |
| --- | --- | ---- | ----------- | --- | ------- | --- | ---- | --- | --- | --------- | --- | --- |
|     |     |      |             | EO  |         |     |      |     | V   |           |     |     |
|     |     |      |  2U  3121DM | 21  | 1  21PT | 3   |      |     |     |  V61      |     |     |
|     |     |      |             |     |         |     |  7PT |     |     |  2C  01+  |     |     |
 11PT
|     |     |     |     |  31PT |     |     |     |     |     |     |     |  6    5    4    3    2   1 |
| --- | --- | --- | --- | ----- | --- | --- | --- | --- | --- | --- | --- | -------------------------- |
2PT
 1J
V L
|     |     |     |     | 2   | 4 6 |     |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
 V61
 1C  01+
 3J
|     |     |     |     |     |     |     |     |     |  1PT |     |  CCV |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | ---- | --- | ---- | --- |
|     |     |     |     | 1   | 3 5 |     |     |     |      |     |      |     |
|     |     |     |     |     |     |     |     |     | SS   |     |  6PT |     |
|     |     |     | CC  |     |     |     |     |     | V    |     |      |     |
|     |     |     | V   |     |     |     |     |     |      |     |  3   |  4  |
 B1D
 22C  1.0
| Doc.# DSDB-MD1213DB1 |     |     |     |     |     |     |     |     |     |     |     | Supertex inc.     |
| -------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ----------------- |
| B032114              |     |     |     |     |     |     | 4   |     |     |     |     |  www.supertex.com |

MD1213DB1
Waveforms
Fig 1: INA, INB, OUTA, OUTB and HV  with 220pF//1K Load, V = V =+12V, V = V = 0V, V /V = +/-100V, 10MHz
|     | OUT | DD H | SS L | PP NN |
| --- | --- | ---- | ---- | ----- |
Fig 2: INA, INB, OUTA, OUTB and HV  with 220pF//1K Load, V = V = +12V, V = V = 0V, V /V = +/-100V, 20MHz
|     | OUT | DD H | SS L | PP NN |
| --- | --- | ---- | ---- | ----- |
Fig 3 :INA, INB, OUTA, OUTB and HV  with 220pF//1K Load, V = V =+12V, V = V = 0V, V /V = +/-100V, 312.5kHz
|     | OUT | DD H | SS L | PP NN |
| --- | --- | ---- | ---- | ----- |
Supertex inc. does not recommend the use of its products in life support applications, and will not knowingly sell them for use in such applications unless it receives
an adequate “product liability indemnification insurance agreement.” Supertex inc. does not assume responsibility for use of devices described, and limits its liability
to the replacement of the devices determined defective due to workmanship. No responsibility is assumed for possible omissions and inaccuracies. Circuitry and
specifications are subject to change without notice. For the latest product specifications refer to the Supertex inc. (website: http//www.supertex.com)
©2014 Supertex inc. All rights reserved. Unauthorized use or reproduction is prohibited. Supertex inc.
1235 Bordeaux Drive, Sunnyvale, CA 94089
Tel: 408-222-8888
Doc.# DSDB-MD1213DB1
| B032114 |     | 5   |     | www.supertex.com |
| ------- | --- | --- | --- | ---------------- |