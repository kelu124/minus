Supertex inc.
AN-H53
Application Note
High Voltage Pulser Circuits
By Ching Chu, Sr. Applications Engineer
Introduction
The high voltage pulser circuit shown in Figure 1 utilizes  circuit. The MD1213 only needs a single V  supply voltage
DD
Supertex’s complementary P- and N-channel  transistors  of 5.0 to 12V, and does not need any logic supply voltage.
| (TC6320)  driven  | by  an  MD1213  | to  achieve  | excellent  |     |     |
| ----------------- | --------------- | ------------ | ---------- | --- | --- |
performance and efficiency with minimal components. The  High voltage, high speed, and high current pulses at low
output voltage swings are -100 to +100V. Rise and fall times  duty cycles are usually required in applications such as
are less than 15ns while sourcing and sinking over ±2.0  medical  ultrasound  imaging,  B-scan ultrasound, material
amps respectively. The output is conveniently controlled by  flaw detection in NDT ultrasound, sonar transmitters and
input logic signals with 1.2 to 5.0V over any CMOS logic  signal generation in test instruments.
Figure 1: ±100V Bipolar Pulser Using the MD1213 and TC6320
+12V
0.47µF
|     | VDD1 |     | VDD2 | VH  |     |
| --- | ---- | --- | ---- | --- | --- |
OE Level
Shifter
|     |     |     |     | OUTA +100V |     |
| --- | --- | --- | --- | ---------- | --- |
INA Level
|     | Shifter |     |     |     | 1µF |
| --- | ------- | --- | --- | --- | --- |
10nF
|     |     |     | VSS2 | VL  | To Piezoelectric |
| --- | --- | --- | ---- | --- | ---------------- |
3.3V CMOS
| Logic Inputs |     |     |     |     | Transducer |
| ------------ | --- | --- | --- | --- | ---------- |
VH
VDD2
10nF
-100V
INB Level
|     |     |     |     | OUTB | 1µF |
| --- | --- | --- | --- | ---- | --- |
Shifter Supertex
Supertex
TC6320
MD1213
|     | GND | VSS1 | VSS2 | VL  |     |
| --- | --- | ---- | ---- | --- | --- |
Circuit Description
The high voltage pulser in Figure 1 consists of 3 basic  or 5.0V CMOS logic IC, FPGA, CPLD and CPU families.
stages; the input signal interface, the high current buffer and  Second, when OE is low, the outputs are disabled, with the
level translation, and the high voltage and current output  A output high and the B output low. This assists in properly
drivers. The first stage has been designed and integrated  pre-charging the AC coupling capacitors that may be used
into the MD1213. Low input capacitance and fast switching  in series in the gate drive circuit of a pair of external P- and
speed are the most important considerations in the MD1213  N-channel FETs.
| input stage. The logic inputs operate at more than 20kΩ with  |     |     |     |     |     |
| ------------------------------------------------------------- | --- | --- | --- | --- | --- |
less than 5.0pF input impendence, and an internal speed  The  output  stage  of  the  MD1213  has  separate  power
of 100MHz. The OE pin serves a dual purpose. First, its  connections enabling the output signal L and H levels to be
logic H level is used to compute the threshold voltage level  chosen independently from the supply voltages used for the
for the channel input level translators. The MD1213 input  majority of the circuit. As an example, the input logic levels
logic is fully compatible and will work with1.8, 2.0, 2.5, 3.3  may be 0 and 1.8V, and the control logic may be powered
| Doc.# DSAN-AN-H53 |     |     |     | Supertex inc. |                   |
| ----------------- | --- | --- | --- | ------------- | ----------------- |
| A040413           |     |     |     |               |  www.supertex.com |

AN-H53
by +5.0 to 12V. Typically, the MD1213 output has about a V and V voltages can be varied without additional
PP NN
6ns rise and fall time with a 1000pF load. The output stage changes within the circuitry. For example, V can be 0V and
NN
is capable of peak currents of up to ±2.0A, depending on the V +200V for positive unipolar pulses. Or V can be –200V
PP NN
supply voltages used and load capacitance present. Such and V 0V for a negative unipolar pulser. See Figure 2 and
PP
high currents are required to adequately drive the input Figure 4.
capacitances, including Miller effect of the output MOSFETs,
to accomplish fast switching speeds. For a single supply to MD1213, connect VDD1, VDD2, and
VH pins to a V of +5.0, +10 or +12V and connect VSS1,
DD
The Supertex TC6320TG consists of a high voltage, low VSS2 and VL, to ground.
threshold, P-channel and N-channel MOSFET in an 8-Lead
SO package. Both MOSFETs have integrated gate-source For all the unipolar cases, if V is 200V, the high voltage
DD
resistors and gate-source Zener diode clamps which are supply bypass capacitors need to have a working voltage
desired for high voltage pulser applications. The TC6320TG higher than 200V. And the high voltage side gate coupling
offers 200V breakdown voltage and 2.0A output peak current capacitor(s) need to have a similar working voltage as well.
and low input capacitance. The 2.0A output current capability In the case of a positive unipolar and single driver supply, the
will minimize the high voltage pulser output rise and fall OUTB to N-FET gate can be DC coupled without a coupling
times. The low input capacitance will minimize propagation capacitor. See Figure 5.
delay times and also make the rise and fall times faster.
A bipolar return-to-zero high voltage pulser circuitry powered
The TC6320 P- and N-channel FETs have integrated gate- by +10 and ±100V is shown in Figure 6.
source resistors and gate-source Zener diode clamps that
are desired for high voltage pulser applications to save board Note the outputs of the two drain MOSFETs may or may
space and improve performance. Output voltage swings can not be connected. The output condition in each application
switch from -100 to +100V. Input capacitance is increased will determine the connections. When one uses the pulser
due to the Miller effect, C = C + C (GFS* RL). Low C alone as shown, then connecting the two drains is fine and
IN ISS RSS RSS
& C capacitance, high output current, low on-resistance even delivers some speed advantages. But if the circuit is
ISS
and high breakdown voltage are required parameters for only part of multi-level pulser and it is not the highest voltage
the output transistors. The Supertex TC6320 is ideally one, then the drains must not be connected. In these cases
suited for the high voltage pulser. Also, complementary P- the diodes need to direct the voltage and current separately
and N-channel DMOS transistors array TC7320 or discreet when positive or negative pulses are generated.
TN5325/TP5322, TN0104/TP0102, TP0620/TN0620 or
TP2640/TN2640, may be used for their low threshold PCB Layout Design Considerations
voltages, low input capacitances and high output current
For proper operation of the MD1213, low inductance (ESL)
capabilities. These are essential features to generate high
bypass capacitors should be used on the various supply
voltage pulses with high speeds and currents. All these high
pins. The GND input pin should be connected to the digital
voltage MOSFETs are cost-effective, and in 8-Lead SO,
ground. The INA, INB, and OE pins should be connected
32-Lead LQFP, SOT-89 or SOT-23 etc. packages, which
to their logic source with a swing of GND to logic level high
have low package inductance, they have excellent thermal
which is 1.2 to 5.0V. Good trace practices should be followed
performance and save board space.
corresponding to the desired operating speed.
During power up and power down conditions, it is possible
The internal circuitry of the MD1213 is capable of operating
for transient voltages greater than 20V to appear across the
up to 100MHz, with the primary speed limitation being the
gate-to-source on the output transistors. Maximum gate-to-
loading effects of the load capacitance. Because of this speed
source voltage, V , is rated at ±20V. The built-in 15 - 18V
GS and the high transient currents that result with capacitive
Zener diodes are connected across the gate and source
loads, the bypass capacitors should be as close to the chip
of the output transistors to protect against such transient
pins as possible. The VSS1, VSS2, and VL pins should have
voltages. These diodes will not have Zener current during
low inductance feed-through connections directly to a ground
normal operation. But even if the high voltage V and V
PP NN plane. The power connections VDD1 and VDD2 should have
can be ramped slowly, the Zener diodes can’t be omitted,
a ceramic bypass capacitor to the ground plane with short
because these diodes also serve as the gate DC voltage
leads and decoupling components to prevent resonance in
restoring functions.
the power leads. A common capacitor and voltage source
may be used for these two pins, which should always have
Supertex inc.
Doc.# DSAN-AN-H53
A040413 2 www.supertex.com

AN-H53
the same DC voltage applied. For applications sensitive to it may be desirable to add a small series resistor in series
jitter and noise, a separate decoupling ferrite bead may be with the output signal to obtain better waveform integrity at
used for VDD1 from VDD2. The supplied voltages of VH and the load terminals. This will, of course, reduce the output
VL determine the output logic levels. These two pins can voltage slew rate at the terminals of a capacitive load. Pay
draw fast transient currents of up to 2.0A, so they should be particular attention to the parasitic coupling from the driver
provided with an appropriate bypass capacitor located next output to the input signal terminals. This feedback may cause
to the chip pins. A ceramic capacitor of up to 1.0µF may be oscillations or spurious waveform shapes on the edges
appropriate, with a series ferrite bead to prevent resonance of signal transitions. Since the input operates with signals
in the power supply lead coming to the capacitor. down to 1.2V, even small coupled voltages may cause
problems. Use of a solid ground plane and good power and
Pay particular attention to minimizing trace lengths and signal layout practices will prevent this problem. Be careful
using sufficient trace width to reduce inductance. Surface that the circulating ground return current from a capacitive
mount components are highly recommended. Since the load cannot react with common inductance to cause noise
output impedance of this driver is very low, in some cases voltages in the input logic circuitry.
Figure 2: +200V Unipolar Pulser Using the MD1213 and TC6320
+10V
0.47µF
VDD1 VDD2 VH
OE Level
Shifter
+200V
OUTA
INA Level
Shifter 1µF +200V
0V
10nF
Unipolar
VSS2 VL
1.2 ~ 3.3V CMOS Pulser
Logic Inputs VH Output
VDD2
10nF
INB Level
Shifter OUTB Supertex
Supertex
TC6320
MD1213
GND VSS1 VSS2 VL
Supertex inc.
Doc.# DSAN-AN-H53
A040413 3 www.supertex.com

AN-H53
Figure 3: +200V Unipolar Pulser with MD1213 Power Supply
+10V
0.47µF
|     | VDD1 | VDD2 | VH  |     |     |
| --- | ---- | ---- | --- | --- | --- |
OE Level
Shifter
|     |     |     | OUTA |     | +200V |
| --- | --- | --- | ---- | --- | ----- |
INA Level
Shifter
1µF +200V
0V
10nF
Unipolar
|                 |     | VSS2 | VL  |     |        |
| --------------- | --- | ---- | --- | --- | ------ |
| 1.2 ~ 3.3V CMOS |     |      |     |     | Pulser |
| Logic Inputs    |     |      | VH  |     | Output |
VDD2
10nF
INB Level
|     | Shifter |     | OUTB | Supertex |     |
| --- | ------- | --- | ---- | -------- | --- |
Supertex
TC6320
MD1213
|     | GND VSS1 | VSS2 | VL  |     |     |
| --- | -------- | ---- | --- | --- | --- |
Figure 4: -200V Unipolar Pulser Using the MD1213, TC6320
+10V
0.47µF
|     | VDD1 | VDD2 |     |     |     |
| --- | ---- | ---- | --- | --- | --- |
VH
OE Level
Shifter
OUTA
INA Level
Shifter
10nF
Unipolar
|     |     | VSS2 | VL  |     | Pulser |
| --- | --- | ---- | --- | --- | ------ |
1.2 ~ 3.3V CMOS
| Logic Inputs |     |     |     |     | Output |
| ------------ | --- | --- | --- | --- | ------ |
VH
VDD2
0V
10nF
-200V
-200V
INB
|     | Level   |     |      |     | 1µF |
| --- | ------- | --- | ---- | --- | --- |
|     | Shifter |     | OUTB |     |     |
Supertex
Supertex
TC6320
MD1213
|                   | GND VSS1 | VSS2 | VL  |     |                   |
| ----------------- | -------- | ---- | --- | --- | ----------------- |
| Doc.# DSAN-AN-H53 |          |      |     |     | Supertex inc.     |
| A040413           |          |      | 4   |     |  www.supertex.com |

AN-H53
Figure 5: +200V Unipolar Pulser Using the MD1213, TP2640, and the TN2640
+10V
0.47µF
|     | VDD1 |     |     | VDD2 |     | VH  |     |     |
| --- | ---- | --- | --- | ---- | --- | --- | --- | --- |
OE Level
Shifter
0 to +200V
VPP
OUTA
INA Level
|     |     | Shifter |     |     |     |     |     | 1µF VPP |
| --- | --- | ------- | --- | --- | --- | --- | --- | ------- |
M1
0V
TP2640
10nF
Unipolar
|                 |     |     |     | VSS2 |     | VL  |     |        |
| --------------- | --- | --- | --- | ---- | --- | --- | --- | ------ |
| 1.2 ~ 3.3V CMOS |     |     |     |      |     |     |     | Pulser |
Output
| Logic Inputs |     |     |     |      |     | VH  |     |     |
| ------------ | --- | --- | --- | ---- | --- | --- | --- | --- |
|              |     |     |     | VDD2 |     |     | M2  |     |
TP2640
INB Level
OUTB
Shifter
Supertex
MD1213
|     |     | GND | VSS1 | VSS2 |     | VL  |     |     |
| --- | --- | --- | ---- | ---- | --- | --- | --- | --- |
Figure 6: ±100V Bipolar 3-Level Pulser Using the MD1213, and the TC6320
+10V
0.1µF
|     |      |      | FB   |     | 0.47µF |     | +100V |     |
| --- | ---- | ---- | ---- | --- | ------ | --- | ----- | --- |
|     |      | VDD1 | VDD2 | VH  |        |     | 1µF   |     |
|     | ENAB | OE   |      |     |        |     |       |     |
OUTA
INA
|     | +PULSE |     |     |     |     | 10nF |     |     |
| --- | ------ | --- | --- | --- | --- | ---- | --- | --- |
OUTB
|     | -PULSE | INB |     |     |     |     |     |     |
| --- | ------ | --- | --- | --- | --- | --- | --- | --- |
10nF
|              |     | GND | VSS1 VSS2 | VL  |      |          | -100V |     |
| ------------ | --- | --- | --------- | --- | ---- | -------- | ----- | --- |
|              |     |     | Supertex  |     |      |          | 1µF   |     |
| 3.3V CMOS    |     |     |           |     |      | Supertex |       |     |
|              |     |     | MD1213    |     | +10V |          |       |     |
| Logic Inputs |     |     |           |     |      | TC6320   |       |     |
0.1µF
|     |      |      | FB   |     | 0.47µF |     |     |     |
| --- | ---- | ---- | ---- | --- | ------ | --- | --- | --- |
|     |      | VDD1 | VDD2 | VH  |        |     |     |     |
|     | ENAB | OE   |      |     |        |     |     |     |
OUTA
INA
|     | DAMP |     |     |     |     | 10nF |     |     |
| --- | ---- | --- | --- | --- | --- | ---- | --- | --- |
OUTB
|     | DAMP | INB |     |     |     |     |     |     |
| --- | ---- | --- | --- | --- | --- | --- | --- | --- |
GND
|     |     |     | VSS1 VSS2 | VL  |     |          |     |     |
| --- | --- | --- | --------- | --- | --- | -------- | --- | --- |
|     |     |     | Supertex  |     |     | Supertex |     |     |
MD1213
TC6320
| Doc.# DSAN-AN-H53 |     |     |     |     |     |     |     | Supertex inc.     |
| ----------------- | --- | --- | --- | --- | --- | --- | --- | ----------------- |
| A040413           |     |     |     |     | 5   |     |     |  www.supertex.com |

AN-H53
Figure 7: MD1213DB1 Waveform
|     | CH1:  | INA   | 5.0V/div   |     |
| --- | ----- | ----- | ---------- | --- |
|     | CH2:  | INB   | 5.0V/div   |     |
|     | CH3:  | UOA   | 10.0V/div  |     |
|     | REF1: | OUB   | 10.0V/div  |     |
|     | CH4:  | HVOUT | 100.0V/div |     |
Recorded by TEK TDS5104B 2.5GS/sec
P6243 1GHz Probes
1K//120pF load, at 200ns/div Horizontal.
Supertex inc. does not recommend the use of its products in life support applications, and will not knowingly sell them for use in such applications unless it receives
an adequate “product liability indemnification insurance agreement.” Supertex inc. does not assume responsibility for use of devices described, and limits its liability
to the replacement of the devices determined defective due to workmanship. No responsibility is assumed for possible omissions and inaccuracies. Circuitry and
specifications are subject to change without notice. For the latest product specifications refer to the Supertex inc. (website: http//www.supertex.com)
©2013 Supertex inc. All rights reserved. Unauthorized use or reproduction is prohibited. Supertex inc.
1235 Bordeaux Drive, Sunnyvale, CA 94089
Tel: 408-222-8888
Doc.# DSAN-AN-H53
| A040413 |     | 6   |     | www.supertex.com |
| ------- | --- | --- | --- | ---------------- |