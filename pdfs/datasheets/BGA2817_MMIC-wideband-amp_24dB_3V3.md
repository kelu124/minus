BGA2817
MMIC wideband amplifier
| Rev. 7 — 30 March 2017 |     |     | Product data sheet |
| ---------------------- | --- | --- | ------------------ |
1.  Product profile
1.1 General description
Silicon Monolithic Microwave Integrated Circuit (MMIC) wideband amplifier with internal
matching circuit in a 6-pin SOT363 plastic SMD package.
1.2 Features and benefits
 Internally matched to 50 
 A gain of 24.4dB at 2150 MHz
 Output power at 1 dB gain compression = 5 dBm at 2150 MHz
 Supply current = 20.0 mA at a supply voltage of 3.3 V
 Reverse isolation > 39 dB up to 2150 MHz
 Good linearity with low second order and third order products
 Noise figure = 3.9 dB at 950 MHz
 Unconditionally stable (K > 1)
 No output inductor required
1.3 Applications
 LNB IF amplifiers
 General purpose low noise wideband amplifier for frequencies between
DCand2.2GHz
2.  Pinning information
|  Table 1. | Pinning     |                    |                |
| --------- | ----------- | ------------------ | -------------- |
| Pin       | Description | Simplified outline | Graphic symbol |
| 1         | V           |                    |                |
CC
|      |        | (cid:25) (cid:24) (cid:23) | (cid:20)          |
| ---- | ------ | -------------------------- | ----------------- |
| 2, 5 | GND2   |                            |                   |
| 3    | RF_OUT |                            | (cid:25) (cid:22) |
| 4    | GND1   |                            |                   |
(cid:23) (cid:21)(cid:15)(cid:3)(cid:24)
| 6   | RF_IN | (cid:20) (cid:21) (cid:22) |     |
| --- | ----- | -------------------------- | --- |
(cid:86)(cid:92)(cid:80)(cid:19)(cid:24)(cid:21)

BGA2817
NXP Semiconductors
MMIC wideband amplifier
3.  Ordering information
|     |  Table 2.   | Ordering information |                                          |     |     |     |     |         |
| --- | ----------- | -------------------- | ---------------------------------------- | --- | --- | --- | --- | ------- |
|     | Type number | Package              |                                          |     |     |     |     |         |
|     |             | Name                 | Description                              |     |     |     |     | Version |
|     | BGA2817     | -                    | plastic surface-mounted package; 6 leads |     |     |     |     | SOT363  |
4.  Marking
|     |  Table 3.   | Marking |              |     |                           |     |     |     |
| --- | ----------- | ------- | ------------ | --- | ------------------------- | --- | --- | --- |
|     | Type number |         | Marking code |     | Description               |     |     |     |
|     | BGA2817     |         | LS*          |     | * = - : made in Hong Kong |     |     |     |
* = p : made in Hong Kong
* = W : made in China
* = t : made in Malaysia
5.  Limiting values
|     |  Table 4. | Limiting values |     |     |     |     |     |     |
| --- | --------- | --------------- | --- | --- | --- | --- | --- | --- |
In accordance with the Absolute Maximum Rating System (IEC 60134).
|     | Symbol | Parameter      |     | Conditions          |     |     | Min  | Max Unit |
| --- | ------ | -------------- | --- | ------------------- | --- | --- | ---- | -------- |
|     | V      | supply voltage |     | RF input AC coupled |     |     | 0.5 | +5.0 V   |
CC
|     | I   | supply current |     |     |     |     | -   | 55 mA |
| --- | --- | -------------- | --- | --- | --- | --- | --- | ----- |
CC
|     | P   | total power dissipation |     | T   |  = 90 C |     | -   | 200 mW  |
| --- | --- | ----------------------- | --- | --- | -------- | --- | --- | ------- |
|     | tot |                         |     | sp  |          |     |     |         |
|     | T   | storage temperature     |     |     |          |     | 40 | +125 C |
stg
|     | T   | junction temperature |     |     |     |     | -   | 125 C |
| --- | --- | -------------------- | --- | --- | --- | --- | --- | ------ |
j
|     | P   | drive power |     |     |     |     | -   | 10 dBm |
| --- | --- | ----------- | --- | --- | --- | --- | --- | ------ |
drive
6.  Thermal characteristics
|     |  Table 5. | Thermal characteristics |     |     |            |     |     |          |
| --- | --------- | ----------------------- | --- | --- | ---------- | --- | --- | -------- |
|     | Symbol    | Parameter               |     |     | Conditions |     |     | Typ Unit |
R thermal resistance from junction to  P =200mW; T =90C 300 K/W
|     | th(j-sp) |     |     |     | tot | sp  |     |     |
| --- | -------- | --- | --- | --- | --- | --- | --- | --- |
solder point
7.  Characteristics
Table 6. Characterist ics
V CC  = 3.3 V; Z S  = Z L  = 50 ; P = 40 dBm; T i amb  = 25 C; measured on demo board; unless otherwise specified.
| Symbol Parameter    |     |     | Conditions |     |     | Min  | Typ  | Max Unit |
| ------------------- | --- | --- | ---------- | --- | --- | ---- | ---- | -------- |
| V CC supply voltage |     |     |            |     |     | 3.0  | 3.3  | 3.6 V    |
| I CC supply current |     |     |            |     |     | 17.6 | 20.0 | 22.2 mA  |
BGA2817 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2017. All rights reserved.
| Product data sheet |     |     | Rev. 7 — 30 March 2017  |     |     |     |     | 2 of 13 |
| ------------------ | --- | --- | ----------------------- | --- | --- | --- | --- | ------- |

BGA2817
NXP Semiconductors
MMIC wideband amplifier
| Table 6. | Characteristics …continued |     |     |     |     |     |
| -------- | -------------------------- | --- | --- | --- | --- | --- |
V  = 3.3 V; Z  = Z  = 50 ; P = 40 dBm; T  = 25 C; measured on demo board; unless otherwise specified.
| CC     | S L        | i   | amb         |     |           |          |
| ------ | ---------- | --- | ----------- | --- | --------- | -------- |
| Symbol | Parameter  |     | Conditions  |     | Min Typ   | Max Unit |
| G      | power gain |     | f = 250 MHz |     | 23.6 24.2 | 24.8 dB  |
p
|     |                   |     | f = 950 MHz  |     | 23.5 24.3 | 25 dB   |
| --- | ----------------- | --- | ------------ | --- | --------- | ------- |
|     |                   |     | f = 2150 MHz |     | 23 24.4   | 25.9 dB |
| RL  | input return loss |     | f = 250 MHz  |     | 13 15     | - dB    |
in
|     |                    |     | f = 950 MHz  |     | 16 18 | - dB |
| --- | ------------------ | --- | ------------ | --- | ----- | ---- |
|     |                    |     | f = 2150 MHz |     | 13 20 | - dB |
| RL  | output return loss |     | f = 250 MHz  |     | 12 17 | - dB |
out
|     |                 |     | f = 950 MHz             |     | 16 17   | - dB    |
| --- | --------------- | --- | ----------------------- | --- | ------- | ------- |
|     |                 |     | f = 2150 MHz            |     | 17 20   | - dB    |
| ISL | isolation       |     | f = 250 MHz             |     | 36 57   | - dB    |
|     |                 |     | f = 950 MHz             |     | 47 49   | - dB    |
|     |                 |     | f = 2150 MHz            |     | 37 39   | - dB    |
| NF  | noise figure    |     | f = 250 MHz             |     | - 3.9   | 4.4 dB  |
|     |                 |     | f = 950 MHz             |     | - 3.9   | 4.3 dB  |
|     |                 |     | f = 2150 MHz            |     | - 3.8   | 4.2 dB  |
| B   | 3 dB bandwidth |     | 3 dB below gain at 1GHz |     | 3.3 3.5 | 3.7 GHz |
3dB
| K   | Rollett stability factor |     | f = 250 MHz  |     | 10 21   | -     |
| --- | ------------------------ | --- | ------------ | --- | ------- | ----- |
|     |                          |     | f = 950 MHz  |     | 7 9     | -     |
|     |                          |     | f = 2150 MHz |     | 1.5 2.7 | -     |
| P   | saturated output power   |     | f = 250 MHz  |     | 8 8     | - dBm |
L(sat)
|     |     |     | f = 950 MHz  |     | 5 7 | - dBm |
| --- | --- | --- | ------------ | --- | --- | ----- |
|     |     |     | f = 2150 MHz |     | 5 6 | - dBm |
P output power at 1 dB gain compression f = 250 MHz 6 6 - dBm
L(1dB)
|     |     |     | f = 950 MHz  |     | 5 6 | - dBm |
| --- | --- | --- | ------------ | --- | --- | ----- |
|     |     |     | f = 2150 MHz |     | 4 5 | - dBm |
IP3 input third-order intercept point P =40dBm (for each tone)
| I   |     |     | drive         |          |         |       |
| --- | --- | --- | ------------- | -------- | ------- | ----- |
|     |     |     | f =250MHz; f  | =251MHz  | 9 7   | - dBm |
|     |     |     | 1             | 2        |         |       |
|     |     |     | f =950MHz; f  | =951MHz  | 9 7   | - dBm |
|     |     |     | 1             | 2        |         |       |
|     |     |     | f =2150MHz; f | =2151MHz | 13 10 | - dBm |
|     |     |     | 1             | 2        |         |       |
IP3 output third-order intercept point P =40dBm (for each tone)
| O     |                              |     | drive         |          |           |         |
| ----- | ---------------------------- | --- | ------------- | -------- | --------- | ------- |
|       |                              |     | f =250MHz; f  | =251MHz  | 16 18     | - dBm   |
|       |                              |     | 1             | 2        |           |         |
|       |                              |     | f =950MHz; f  | =951MHz  | 16 18     | - dBm   |
|       |                              |     | 1             | 2        |           |         |
|       |                              |     | f =2150MHz; f | =2151MHz | 12.5 15.5 | - dBm   |
|       |                              |     | 1             | 2        |           |         |
| P     | second harmonic output power |     | P =28dBm     |          |           |         |
| L(2H) |                              |     | drive         |          |           |         |
|       |                              |     | f =250MHz; f  | =500MHz  | - 53     | 51 dBm |
|       |                              |     | 1H            | 2H       |           |         |
|       |                              |     | f =950MHz; f  | =1900MHz | - 45     | 41 dBm |
|       |                              |     | 1H            | 2H       |           |         |
IM2 second-order intermodulation distance P =31dBm (for each tone)
drive
|     |     |     | f =250MHz; f | =251MHz | 34 36 | - dBc |
| --- | --- | --- | ------------ | ------- | ----- | ----- |
|     |     |     | 1            | 2       |       |       |
|     |     |     | f =950MHz; f | =951MHz | 33 39 | - dBc |
|     |     |     | 1            | 2       |       |       |
BGA2817 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2017. All rights reserved.
| Product data sheet |     |     | Rev. 7 — 30 March 2017  |     |     | 3 of 13 |
| ------------------ | --- | --- | ----------------------- | --- | --- | ------- |

BGA2817
NXP Semiconductors
MMIC wideband amplifier
8.  Application information
Figure1 shows a typical application circuit for the BGA2817 MMIC. The device is
internally matched to 50 , and therefore does not need any external matching. The value
of the input and output DC blocking capacitors C2 and C3 should not be more than 100 pF
for applications above 100 MHz. However, when the device is operated below 100 MHz,
the capacitor value should be increased.
The location of the 470 pF supply decoupling capacitor (C ) can be precisely chosen for
dec
optimum performance.
The PCB top ground plane, connected to pins 2, 4 and 5 must be as close as possible to
the MMIC, preferably also below the MMIC. When using via holes, use multiple via holes
as close as possible to the MMIC.

(cid:57)(cid:54)
(cid:38)(cid:71)(cid:72)(cid:70)
(cid:57)(cid:54)
|     |     |     | (cid:38)(cid:20)                                                | (cid:53)(cid:41)(cid:66)(cid:44)(cid:49) | (cid:53)(cid:41)(cid:66)(cid:50)(cid:56)(cid:55) (cid:38)(cid:21) |                                                                         |     |     |
| --- | --- | --- | --------------------------------------------------------------- | ---------------------------------------- | ----------------------------------------------------------------- | ----------------------------------------------------------------------- | --- | --- |
|     |     |     | (cid:53)(cid:41)(cid:3)(cid:76)(cid:81)(cid:83)(cid:88)(cid:87) |                                          |                                                                   | (cid:53)(cid:41)(cid:3)(cid:82)(cid:88)(cid:87)(cid:83)(cid:88)(cid:87) |     |     |
|     |     |     |                                                                 | (cid:42)(cid:49)(cid:39)(cid:20)         | (cid:42)(cid:49)(cid:39)(cid:21)                                  |                                                                         |     |     |
(cid:68)(cid:68)(cid:68)(cid:16)(cid:19)(cid:19)(cid:22)(cid:26)(cid:24)(cid:26)
|     | Fig 1. | Typical application circuit |     |     |     |     |     |     |
| --- | ------ | --------------------------- | --- | --- | --- | --- | --- | --- |
8.1 Application examples

|     | (cid:90)(cid:76)(cid:71)(cid:72)(cid:69)(cid:68)(cid:81)(cid:71)(cid:3) |     |     |     | (cid:90)(cid:76)(cid:71)(cid:72)(cid:69)(cid:68)(cid:81)(cid:71)(cid:3) |     |     |     |
| --- | ----------------------------------------------------------------------- | --- | --- | --- | ----------------------------------------------------------------------- | --- | --- | --- |
(cid:68)(cid:80)(cid:83)(cid:79)(cid:76)(cid:73)(cid:76)(cid:72)(cid:85)
|     | (cid:80)(cid:76)(cid:91)(cid:72)(cid:85) (cid:68)(cid:80)(cid:83)(cid:79)(cid:76)(cid:73)(cid:76)(cid:72)(cid:85) |     |     |     | (cid:47)(cid:49)(cid:36) | (cid:80)(cid:76)(cid:91)(cid:72)(cid:85) |     |     |
| --- | ----------------------------------------------------------------------------------------------------------------- | --- | --- | --- | ------------------------ | ---------------------------------------- | --- | --- |
(cid:87)(cid:82)(cid:3)(cid:44)(cid:41)(cid:3)(cid:70)(cid:76)(cid:85)(cid:70)(cid:88)(cid:76)(cid:87)(cid:3)
| (cid:73)(cid:85)(cid:82)(cid:80)(cid:3)(cid:53)(cid:41)(cid:3) |     | (cid:87)(cid:82)(cid:3)(cid:44)(cid:41)(cid:3)(cid:70)(cid:76)(cid:85)(cid:70)(cid:88)(cid:76)(cid:87)(cid:3) |     | (cid:68)(cid:81)(cid:87)(cid:72)(cid:81)(cid:81)(cid:68) |     |     |     |     |
| -------------------------------------------------------------- | --- | ------------------------------------------------------------------------------------------------------------- | --- | -------------------------------------------------------- | --- | --- | --- | --- |
(cid:82)(cid:85)(cid:3)(cid:71)(cid:72)(cid:80)(cid:82)(cid:71)(cid:88)(cid:79)(cid:68)(cid:87)(cid:82)(cid:85)
(cid:70)(cid:76)(cid:85)(cid:70)(cid:88)(cid:76)(cid:87) (cid:82)(cid:85)(cid:3)(cid:71)(cid:72)(cid:80)(cid:82)(cid:71)(cid:88)(cid:79)(cid:68)(cid:87)(cid:82)(cid:85)
|     | (cid:82)(cid:86)(cid:70)(cid:76)(cid:79)(cid:79)(cid:68)(cid:87)(cid:82)(cid:85) |                                                                          |     |     |     | (cid:82)(cid:86)(cid:70)(cid:76)(cid:79)(cid:79)(cid:68)(cid:87)(cid:82)(cid:85) |                                                                          |     |
| --- | -------------------------------------------------------------------------------- | ------------------------------------------------------------------------ | --- | --- | --- | -------------------------------------------------------------------------------- | ------------------------------------------------------------------------ | --- |
|     |                                                                                  | (cid:19)(cid:19)(cid:20)(cid:68)(cid:68)(cid:73)(cid:26)(cid:25)(cid:21) |     |     |     |                                                                                  | (cid:19)(cid:19)(cid:20)(cid:68)(cid:68)(cid:73)(cid:26)(cid:25)(cid:22) |     |
The MMIC is very suitable as IF amplifier in e.g. LNB’s.  As second amplifier after an LNA, the MMIC offers an
The excellent wideband characteristics make it an easy  easy matching, low noise solution.
building block.
Fig 2. Application as IF amplifier Fig 3. Application as RF amplifier
8.2 Tables
|     |  Table 7. | Supply current over temperature and supply voltages |     |     |     |     |     |     |
| --- | --------- | --------------------------------------------------- | --- | --- | --- | --- | --- | --- |
Typical values.
|     | Symbol | Parameter |     | Conditions | T  (C) |     |     | Unit |
| --- | ------ | --------- | --- | ---------- | ------- | --- | --- | ---- |
amb
|     |     |                |     |         | 40  | +25  | +85  |     |
| --- | --- | -------------- | --- | ------- | ---- | ---- | ---- | --- |
|     | I   | supply current |     | V =3.0V | 18.0 | 17.6 | 17.3 | mA  |
|     | CC  |                |     | CC      |      |      |      |     |
|     |     |                |     | V =3.3V | 20.4 | 20.0 | 19.6 | mA  |
CC
|     |     |     |     | V =3.6V | 22.7 | 22.2 | 21.7 | mA  |
| --- | --- | --- | --- | ------- | ---- | ---- | ---- | --- |
CC
BGA2817 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2017. All rights reserved.
| Product data sheet |     |     | Rev. 7 — 30 March 2017  |     |     |     |     | 4 of 13 |
| ------------------ | --- | --- | ----------------------- | --- | --- | --- | --- | ------- |

BGA2817
NXP Semiconductors
MMIC wideband amplifier
 Table 8. Second harmonic output power over temperature and supply voltages
Typical values.
|     | Symbol Parameter |     | Conditions |     |     | T  (C) | Unit |
| --- | ---------------- | --- | ---------- | --- | --- | ------- | ---- |
amb
|     |                                |     |                |       |         | 40 +25 | +85     |
| --- | ------------------------------ | --- | -------------- | ----- | ------- | ------- | ------- |
|     | P second harmonic output power |     | f = 250 MHz; P |       | =28dBm |         |         |
|     | L(2H)                          |     |                |       | drive   |         |         |
|     |                                |     | V              | =3.0V |         | 38 44 | 52 dBm |
CC
|     |     |     | V   | =3.3V |     | 45 53 | 60 dBm |
| --- | --- | --- | --- | ----- | --- | ------- | ------- |
CC
|     |     |     | V   | =3.6V |     | 56 59 | 53 dBm |
| --- | --- | --- | --- | ----- | --- | ------- | ------- |
CC
|     |     |     | f = 950 MHz; P |     | =28dBm |     |     |
| --- | --- | --- | -------------- | --- | ------- | --- | --- |
drive
|     |     |     | V   | =3.0V |     | 43 53 | 45 dBm |
| --- | --- | --- | --- | ----- | --- | ------- | ------- |
CC
|     |     |     | V   | =3.3V |     | 51 45 | 41 dBm |
| --- | --- | --- | --- | ----- | --- | ------- | ------- |
CC
|     |     |     | V   | =3.6V |     | 44 41 | 39 dBm |
| --- | --- | --- | --- | ----- | --- | ------- | ------- |
CC
 Table 9. Input power at 1 dB gain compression over temperature and supply voltages
Typical values.
|     | Symbol Parameter |     |     | Conditions | T   |  (C) | Unit |
| --- | ---------------- | --- | --- | ---------- | --- | ----- | ---- |
amb
|     |                                       |     |     |             | 40 | +25 +85 |     |
| --- | ------------------------------------- | --- | --- | ----------- | --- | ------- | --- |
|     | P input power at 1dB gain compression |     |     | f = 250 MHz |     |         |     |
i(1dB)
|     |     |     |     | V   | =3.0V 19 | 18 18 | dBm |
| --- | --- | --- | --- | --- | --------- | ------- | --- |
CC
|     |     |     |     | V   | =3.3V 17 | 17 17 | dBm |
| --- | --- | --- | --- | --- | --------- | ------- | --- |
CC
|     |     |     |     | V   | =3.6V 16 | 16 16 | dBm |
| --- | --- | --- | --- | --- | --------- | ------- | --- |
CC
f = 950 MHz
|     |     |     |     | V   | =3.0V 19 | 18 18 | dBm |
| --- | --- | --- | --- | --- | --------- | ------- | --- |
CC
|     |     |     |     | V   | =3.3V 18 | 17 17 | dBm |
| --- | --- | --- | --- | --- | --------- | ------- | --- |
CC
|     |     |     |     | V   | =3.6V 17 | 17 17 | dBm |
| --- | --- | --- | --- | --- | --------- | ------- | --- |
CC
f = 2150 MHz
|     |     |     |     | V   | =3.0V 20 | 20 20 | dBm |
| --- | --- | --- | --- | --- | --------- | ------- | --- |
CC
|     |     |     |     | V   | =3.3V 19 | 19 20 | dBm |
| --- | --- | --- | --- | --- | --------- | ------- | --- |
CC
|     |     |     |     | V   | =3.6V 18 | 19 20 | dBm |
| --- | --- | --- | --- | --- | --------- | ------- | --- |
CC
BGA2817 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2017. All rights reserved.
| Product data sheet |     | Rev. 7 — 30 March 2017  |     |     |     |     | 5 of 13 |
| ------------------ | --- | ----------------------- | --- | --- | --- | --- | ------- |

BGA2817
NXP Semiconductors
MMIC wideband amplifier
 Table 10. Output power at 1 dB gain compression over temperature and supply voltages
Typical values.
|     | Symbol | Parameter | Conditions | T  (C) | Unit |
| --- | ------ | --------- | ---------- | ------- | ---- |
amb
|     |     |                                      |             | 40 | +25 +85 |
| --- | --- | ------------------------------------ | ----------- | --- | ------- |
|     | P   | output power at 1dB gain compression | f = 250 MHz |     |         |
L(1dB)
|     |     |     | V =3.0V | 4   | 5 5 dBm |
| --- | --- | --- | ------- | --- | ------- |
CC
|     |     |     | V =3.3V | 6   | 6 6 dBm |
| --- | --- | --- | ------- | --- | ------- |
CC
|     |     |     | V =3.6V | 8   | 8 7 dBm |
| --- | --- | --- | ------- | --- | ------- |
CC
f = 950 MHz
|     |     |     | V =3.0V | 4   | 4 4 dBm |
| --- | --- | --- | ------- | --- | ------- |
CC
|     |     |     | V =3.3V | 6   | 6 6 dBm |
| --- | --- | --- | ------- | --- | ------- |
CC
|     |     |     | V =3.6V | 7   | 7 7 dBm |
| --- | --- | --- | ------- | --- | ------- |
CC
f = 2150 MHz
|     |     |     | V =3.0V | 4   | 4 3 dBm |
| --- | --- | --- | ------- | --- | ------- |
CC
|     |     |     | V =3.3V | 6   | 5 4 dBm |
| --- | --- | --- | ------- | --- | ------- |
CC
|     |     |     | V =3.6V | 7   | 6 5 dBm |
| --- | --- | --- | ------- | --- | ------- |
CC
|     |  Table 11. | Saturated output power over temperature and supply voltages |     |     |     |
| --- | ---------- | ----------------------------------------------------------- | --- | --- | --- |
Typical values.
|     | Symbol | Parameter | Conditions | T  (C) | Unit |
| --- | ------ | --------- | ---------- | ------- | ---- |
amb
|     |     |                        |             | 40 +25 | +85 |
| --- | --- | ---------------------- | ----------- | ------- | --- |
|     | P   | saturated output power | f = 250 MHz |         |     |
L(sat)
|     |     |     | V =3.0V | 6 6 | 7 dBm |
| --- | --- | --- | ------- | --- | ----- |
CC
|     |     |     | V =3.3V | 8 8 | 8 dBm |
| --- | --- | --- | ------- | --- | ----- |
CC
|     |     |     | V =3.6V | 9 9 | 9 dBm |
| --- | --- | --- | ------- | --- | ----- |
CC
f = 950 MHz
|     |     |     | V =3.0V | 6 6 | 6 dBm |
| --- | --- | --- | ------- | --- | ----- |
CC
|     |     |     | V =3.3V | 7 7 | 7 dBm |
| --- | --- | --- | ------- | --- | ----- |
CC
|     |     |     | V =3.6V | 7 8 | 8 dBm |
| --- | --- | --- | ------- | --- | ----- |
CC
f = 2150 MHz
|     |     |     | V =3.0V | 5 5 | 4 dBm |
| --- | --- | --- | ------- | --- | ----- |
CC
|     |     |     | V =3.3V | 7 6 | 5 dBm |
| --- | --- | --- | ------- | --- | ----- |
CC
|     |     |     | V =3.6V | 8 7 | 6 dBm |
| --- | --- | --- | ------- | --- | ----- |
CC
BGA2817 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2017. All rights reserved.
| Product data sheet |     | Rev. 7 — 30 March 2017  |     |     | 6 of 13 |
| ------------------ | --- | ----------------------- | --- | --- | ------- |

BGA2817
NXP Semiconductors
MMIC wideband amplifier
 Table 12. Second-order intermodulation distance over temperature and supply voltages
Typical values.
|     | Symbol | Parameter |     | Conditions | T  (C) | Unit |
| --- | ------ | --------- | --- | ---------- | ------- | ---- |
amb
|     |      |                                       |     |             | 40 | +25 +85 |
| --- | ---- | ------------------------------------- | --- | ----------- | --- | ------- |
|     | IM2 | second-order intermodulation distance |     | f =250MHz;  |     |         |
1
f 2 =251MHz;
P drive =31dBm
|     |     |     |     | V CC =3.0V | 28  | 32 36 dBc |
| --- | --- | --- | --- | ---------- | --- | --------- |
|     |     |     |     | V CC =3.3V | 33  | 36 40 dBc |
|     |     |     |     | V CC =3.6V | 38  | 40 44 dBc |
f 1 =950MHz;
f =951MHz;
2
P =31dBm
drive
|     |     |     |     | V =3.0V | 29  | 34 40 dBc |
| --- | --- | --- | --- | ------- | --- | --------- |
CC
|     |     |     |     | V =3.3V | 35  | 39 43 dBc |
| --- | --- | --- | --- | ------- | --- | --------- |
CC
|     |     |     |     | V =3.6V | 40  | 44 42 dBc |
| --- | --- | --- | --- | ------- | --- | --------- |
CC
T
able 13. Output third-order intercept point over temperature and supply voltages
Typical values.
|     | Symbol | Parameter                          |     | Conditions    | T amb  (C) | Unit |
| --- | ------ | ---------------------------------- | --- | ------------- | ----------- | ---- |
|     |        |                                    |     |               | 40 +25     | +85  |
|     | IP3 O  | output third-order intercept point |     | f 1 =250MHz;  |             |      |
f =251MHz;
2
P =40dBm
drive
|     |     |     |     | V =3.0V | 14 15 | 16 dBm |
| --- | --- | --- | --- | ------- | ----- | ------ |
CC
|     |     |     |     | V =3.3V | 18 18 | 17 dBm |
| --- | --- | --- | --- | ------- | ----- | ------ |
CC
|     |     |     |     | V =3.6V | 19 19 | 19 dBm |
| --- | --- | --- | --- | ------- | ----- | ------ |
CC
f =950MHz;
1
f =951MHz;
2
P drive =40dBm
|     |     |     |     | V CC =3.0V | 15 16 | 15 dBm |
| --- | --- | --- | --- | ---------- | ----- | ------ |
|     |     |     |     | V CC =3.3V | 18 18 | 17 dBm |
|     |     |     |     | V CC =3.6V | 20 20 | 18 dBm |
f 1 =2150MHz;
f 2 =2151MHz;
P =40dBm
drive
|     |     |     |     | V =3.0V | 15.5 14.5 | 12.5 dBm |
| --- | --- | --- | --- | ------- | --------- | -------- |
CC
|     |     |     |     | V =3.3V | 17.5 15.5 | 13.5 dBm |
| --- | --- | --- | --- | ------- | --------- | -------- |
CC
|     |     |     |     | V =3.6V | 18.5 16.5 | 13.5 dBm |
| --- | --- | --- | --- | ------- | --------- | -------- |
CC
|     | T  able 14. | 3 dB bandwidth over temperature and supply voltages |     |     |     |     |
| --- | ----------- | ---------------------------------------------------- | --- | --- | --- | --- |
Typical values.
|     | Symbol | Parameter       | Conditions | T amb  (C) |      | Unit     |
| --- | ------ | --------------- | ---------- | ----------- | ---- | -------- |
|     |        |                 |            | 40         | +25  | +85      |
|     | B 3dB | 3 dB bandwidth | V CC =3.0V | 3.6         | 3.49 | 3.34 GHz |
|     |        |                 | V CC =3.3V | 3.59        | 3.47 | 3.32 GHz |
|     |        |                 | V CC =3.6V | 3.58        | 3.46 | 3.31 GHz |
BGA2817 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2017. All rights reserved.
| Product data sheet |     | Rev. 7 — 30 March 2017  |     |     |     | 7 of 13 |
| ------------------ | --- | ----------------------- | --- | --- | --- | ------- |

BGA2817
NXP Semiconductors
MMIC wideband amplifier
9. Test information
(cid:68)(cid:68)(cid:68)(cid:16)(cid:19)(cid:19)(cid:23)(cid:22)(cid:22)(cid:26)
For decoupling a decoupling capacitor (C ) is used on one of the positions of P5 to P24. The
dec
results mentioned in this data sheet have been obtained using the decoupling capacitor Cdec on
position P22. The distance between the center of pin 1 and the center of position P22 is 7.43 mm.
Fig 4. PCB layout and demo board with components
[1] For decoupling a decoupling capacitor (C ) is used on one of the positions of P5 to P24. The results mentioned in this data sheet have
dec
been obtained using the decoupling capacitor Cdec on position P22.
BGA2817 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2017. All rights reserved.
Product data sheet Rev. 7 — 30 March 2017 8 of 13
(cid:55)(cid:56)(cid:50)(cid:41)(cid:53)
(cid:49)(cid:44)(cid:41)(cid:53)
(cid:23)(cid:20)(cid:51) (cid:24)(cid:20)(cid:51)
(cid:24)(cid:51)
(cid:25)(cid:20)(cid:51)
(cid:25)(cid:51)
(cid:26)(cid:20)(cid:51)
(cid:26)(cid:51)
(cid:27)(cid:20)(cid:51)
(cid:27)(cid:51)
(cid:28)(cid:20)(cid:51)
(cid:28)(cid:51)
(cid:19)(cid:21)(cid:51)
(cid:19)(cid:20)(cid:51)
(cid:20)(cid:21)(cid:51)
(cid:20)(cid:20)(cid:51)
(cid:21)(cid:21)(cid:51)
(cid:21)(cid:20)(cid:51)
(cid:22)(cid:21)(cid:51)
(cid:22)(cid:20)(cid:51)
(cid:23)(cid:21)(cid:51)
(cid:42)(cid:49)(cid:39)
(cid:38)(cid:21)
(cid:20) (cid:57)(cid:38)(cid:38)
(cid:42)(cid:49)(cid:39)
(cid:38)(cid:20)
(cid:54)(cid:53)(cid:50)(cid:55)(cid:38)(cid:56)(cid:39)(cid:49)(cid:50)(cid:38)(cid:44)(cid:48)(cid:40)(cid:54)
(cid:37)(cid:42)(cid:36)(cid:21)(cid:91)(cid:91)(cid:91)(cid:3)(cid:54)(cid:50)(cid:55)(cid:22)(cid:25)(cid:22)(cid:3)(cid:40)(cid:57)(cid:37)
Table 15. List of components used for the typical application
Component Description Value Dimensions Remarks
C1, C2 multilayer ceramic chip capacitor 470 pF 0603 X7R RF coupling capacitor
P5 to P24 [1] position for multilayer ceramic chip 470 pF 0603 X7R RF decoupling capacitor
capacitor C
dec
IC1 BGA2817 MMIC - SOT363

BGA2817
NXP Semiconductors
MMIC wideband amplifier
10. Package outline

(cid:51)(cid:79)(cid:68)(cid:86)(cid:87)(cid:76)(cid:70)(cid:3)(cid:86)(cid:88)(cid:85)(cid:73)(cid:68)(cid:70)(cid:72)(cid:16)(cid:80)(cid:82)(cid:88)(cid:81)(cid:87)(cid:72)(cid:71)(cid:3)(cid:83)(cid:68)(cid:70)(cid:78)(cid:68)(cid:74)(cid:72)(cid:30)(cid:3)(cid:25)(cid:3)(cid:79)(cid:72)(cid:68)(cid:71)(cid:86) (cid:54)(cid:50)(cid:55)(cid:22)(cid:25)(cid:22)
(cid:39)
|     |     |     |     | (cid:37) |     | (cid:40) | (cid:36) (cid:59) |     |
| --- | --- | --- | --- | -------- | --- | -------- | ----------------- | --- |
(cid:92)
|     |     |          |          |          |     | (cid:43)(cid:40) | (cid:89) (cid:48) (cid:36) |     |
| --- | --- | -------- | -------- | -------- | --- | ---------------- | -------------------------- | --- |
|     |     | (cid:25) | (cid:24) | (cid:23) |     |                  |                            |     |
(cid:52)
(cid:83)(cid:76)(cid:81)(cid:3)(cid:20)(cid:3)
|     |     | (cid:76)(cid:81)(cid:71)(cid:72)(cid:91) |     |     | (cid:36) |     |     |     |
| --- | --- | ---------------------------------------- | --- | --- | -------- | --- | --- | --- |
(cid:36)(cid:20)
|     |     | (cid:20) | (cid:21) | (cid:22) |     |     |     |     |
| --- | --- | -------- | -------- | -------- | --- | --- | --- | --- |
(cid:70)
|     |     | (cid:72)(cid:20) | (cid:69)(cid:83) | (cid:90) | (cid:48) (cid:37) |     | (cid:47)(cid:83) |     |
| --- | --- | ---------------- | ---------------- | -------- | ----------------- | --- | ---------------- | --- |
(cid:72)
(cid:71)(cid:72)(cid:87)(cid:68)(cid:76)(cid:79)(cid:3)(cid:59)
|     |     |     |     | (cid:19) | (cid:20) | (cid:21)(cid:3)(cid:80)(cid:80) |     |     |
| --- | --- | --- | --- | -------- | -------- | ------------------------------- | --- | --- |
(cid:86)(cid:70)(cid:68)(cid:79)(cid:72)
(cid:39)(cid:44)(cid:48)(cid:40)(cid:49)(cid:54)(cid:44)(cid:50)(cid:49)(cid:54)(cid:3)(cid:11)(cid:80)(cid:80)(cid:3)(cid:68)(cid:85)(cid:72)(cid:3)(cid:87)(cid:75)(cid:72)(cid:3)(cid:82)(cid:85)(cid:76)(cid:74)(cid:76)(cid:81)(cid:68)(cid:79)(cid:3)(cid:71)(cid:76)(cid:80)(cid:72)(cid:81)(cid:86)(cid:76)(cid:82)(cid:81)(cid:86)(cid:12)
(cid:36)(cid:20)(cid:3)
(cid:56)(cid:49)(cid:44)(cid:55) (cid:36) (cid:69)(cid:83) (cid:70) (cid:39) (cid:40) (cid:72) (cid:72) (cid:20) (cid:43)(cid:40) (cid:47)(cid:83) (cid:52) (cid:89) (cid:90) (cid:92)
(cid:80)(cid:68)(cid:91)
|     | (cid:20)(cid:17)(cid:20)(cid:3) | (cid:19)(cid:17)(cid:22)(cid:19)(cid:3) (cid:19)(cid:17)(cid:21)(cid:24)(cid:3) | (cid:21)(cid:17)(cid:21)(cid:3) (cid:20)(cid:17)(cid:22)(cid:24)(cid:3) |     | (cid:21)(cid:17)(cid:21)(cid:3) (cid:19)(cid:17)(cid:23)(cid:24)(cid:3) | (cid:19)(cid:17)(cid:21)(cid:24)(cid:3) |     |     |
| --- | ------------------------------- | ------------------------------------------------------------------------------- | ----------------------------------------------------------------------- | --- | ----------------------------------------------------------------------- | --------------------------------------- | --- | --- |
(cid:80)(cid:80) (cid:19)(cid:17)(cid:20) (cid:20)(cid:17)(cid:22) (cid:19)(cid:17)(cid:25)(cid:24) (cid:19)(cid:17)(cid:21) (cid:19)(cid:17)(cid:21) (cid:19)(cid:17)(cid:20)
|     | (cid:19)(cid:17)(cid:27) | (cid:19)(cid:17)(cid:21)(cid:19) (cid:19)(cid:17)(cid:20)(cid:19) | (cid:20)(cid:17)(cid:27) (cid:20)(cid:17)(cid:20)(cid:24) |     | (cid:21)(cid:17)(cid:19) (cid:19)(cid:17)(cid:20)(cid:24) | (cid:19)(cid:17)(cid:20)(cid:24) |     |     |
| --- | ------------------------ | ----------------------------------------------------------------- | --------------------------------------------------------- | --- | --------------------------------------------------------- | -------------------------------- | --- | --- |
(cid:3)(cid:53)(cid:40)(cid:41)(cid:40)(cid:53)(cid:40)(cid:49)(cid:38)(cid:40)(cid:54)
(cid:50)(cid:56)(cid:55)(cid:47)(cid:44)(cid:49)(cid:40)(cid:3) (cid:40)(cid:56)(cid:53)(cid:50)(cid:51)(cid:40)(cid:36)(cid:49)(cid:3)
(cid:51)(cid:53)(cid:50)(cid:45)(cid:40)(cid:38)(cid:55)(cid:44)(cid:50)(cid:49) (cid:44)(cid:54)(cid:54)(cid:56)(cid:40)(cid:3)(cid:39)(cid:36)(cid:55)(cid:40)
|     | (cid:57)(cid:40)(cid:53)(cid:54)(cid:44)(cid:50)(cid:49) | (cid:3)(cid:44)(cid:40)(cid:38) | (cid:3)(cid:45)(cid:40)(cid:39)(cid:40)(cid:38) |     | (cid:3)(cid:45)(cid:40)(cid:44)(cid:55)(cid:36) |     |     |     |
| --- | -------------------------------------------------------- | ------------------------------- | ----------------------------------------------- | --- | ----------------------------------------------- | --- | --- | --- |
(cid:19)(cid:23)(cid:16)(cid:20)(cid:20)(cid:16)(cid:19)(cid:27)(cid:3)
|     | (cid:3)(cid:54)(cid:50)(cid:55)(cid:22)(cid:25)(cid:22) |     | (cid:3) |     | (cid:54)(cid:38)(cid:16)(cid:27)(cid:27) |     |     |     |
| --- | ------------------------------------------------------- | --- | ------- | --- | ---------------------------------------- | --- | --- | --- |
(cid:19)(cid:25)(cid:16)(cid:19)(cid:22)(cid:16)(cid:20)(cid:25)
Fig 5. Package outline SOT363
BGA2817 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2017. All rights reserved.
| Product data sheet |     |     |     | Rev. 7 — 30 March 2017  |     |     |     | 9 of 13 |
| ------------------ | --- | --- | --- | ----------------------- | --- | --- | --- | ------- |

BGA2817
NXP Semiconductors
MMIC wideband amplifier
11. Abbreviations
 Table 16. Abbreviations
|     | Acronym Description        |                           |     |     |     |
| --- | -------------------------- | ------------------------- | --- | --- | --- |
|     | IF Intermediate Frequency  |                           |     |     |     |
|     | LNA Low-Noise Amplifier    |                           |     |     |     |
|     | LNB                        | Low-Noise Block converter |     |     |     |
|     | PCB                        | Printed-Circuit Board     |     |     |     |
|     | SMD Surface Mounted Device |                           |     |     |     |
12. Revision history
 Table 17. Revision history
Document ID Release date Data sheet status Change notice Supersedes
| BGA2817 v.7 | 20170330 | Product data sheet | -   | BGA2817 v.6 |     |
| ----------- | -------- | ------------------ | --- | ----------- | --- |
•
Modifications: Table6 on page2: the maximum value for f1H=950MHz; f2H=1900MHz has been changed
to 41 dBm
•
Table6 on page2: the minimum value for IM2 (f1=950MHz; f2=951MHz) has been
changed to 33 dBc
•
Table6 on page2: the maximum value removed from RL , RL , ISL, K, P , P , IP3,
|     |     |     | in out | L(sat) L(1dB) | I   |
| --- | --- | --- | ------ | ------------- | --- |
IP3 , IM2
O
•
Table6 on page2: the minimum value removed from NF, P
L(2H)
| BGA2817 v.6 | 20161003 | Product data sheet | -   | BGA2817 v.5 |     |
| ----------- | -------- | ------------------ | --- | ----------- | --- |
•
Modifications: Table6 on page2: the min/max value for P  (f =950MHz; f =1900MHz) removed
|     |     |     | L(2H) 1H 2H |     |     |
| --- | --- | --- | ----------- | --- | --- |
•
Table6 on page2: the min/max value for IM2 (f 1 =950MHz; f 2 =951MHz) removed
| BGA2817 v.5 | 20150330 | Product data sheet | -   | BGA2817 v.4 |     |
| ----------- | -------- | ------------------ | --- | ----------- | --- |
•
Modifications: Table4 on page2: the maximum value for P drive  has been changed to 10 dBm
| BGA2817 v.4 | 20141203 | Product data sheet | -   | BGA2817 v.3 |     |
| ----------- | -------- | ------------------ | --- | ----------- | --- |
| BGA2817 v.3 | 20130826 | Product data sheet | -   | BGA2817 v.2 |     |
| BGA2817 v.2 | 20120419 | Product data sheet | -   | BGA2817 v.1 |     |
| BGA2817 v.1 | 20111117 | Product data sheet | -   | -           |     |
BGA2817 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2017. All rights reserved.
| Product data sheet |     | Rev. 7 — 30 March 2017  |     |     | 10 of 13 |
| ------------------ | --- | ----------------------- | --- | --- | -------- |

BGA2817
NXP Semiconductors
MMIC wideband amplifier
13. Legal information
13.1 Data sheet status
Document status[1][2] Product status[3] Definition
Objective [short] data sheet Development This document contains data from the objective specification for product development.
Preliminary [short] data sheet Qualification This document contains data from the preliminary specification.
Product [short] data sheet Production This document contains the product specification.
[1] Please consult the most recently issued document before initiating or completing a design.
[2] The term ‘short data sheet’ is explained in section “Definitions”.
[3] The product status of device(s) described in this document may have changed since this document was published and may differ in case of multiple devices. The latest product status
information is available on the Internet at URLhttp://www.nxp.com.
13.2 Definitions Suitability for use — NXP Semiconductors products are not designed,
authorized or warranted to be suitable for use in life support, life-critical or
safety-critical systems or equipment, nor in applications where failure or
Draft — The document is a draft version only. The content is still under
malfunction of an NXP Semiconductors product can reasonably be expected
internal review and subject to formal approval, which may result in
to result in personal injury, death or severe property or environmental
modifications or additions. NXP Semiconductors does not give any
damage. NXP Semiconductors and its suppliers accept no liability for
representations or warranties as to the accuracy or completeness of
inclusion and/or use of NXP Semiconductors products in such equipment or
information included herein and shall have no liability for the consequences of
applications and therefore such inclusion and/or use is at the customer’s own
use of such information.
risk.
Short data sheet — A short data sheet is an extract from a full data sheet
Applications — Applications that are described herein for any of these
with the same product type number(s) and title. A short data sheet is intended
products are for illustrative purposes only. NXP Semiconductors makes no
for quick reference only and should not be relied upon to contain detailed and
representation or warranty that such applications will be suitable for the
full information. For detailed and full information see the relevant full data
specified use without further testing or modification.
sheet, which is available on request via the local NXP Semiconductors sales
office. In case of any inconsistency or conflict with the short data sheet, the Customers are responsible for the design and operation of their applications
full data sheet shall prevail. and products using NXP Semiconductors products, and NXP Semiconductors
accepts no liability for any assistance with applications or customer product
Product specification — The information and data provided in a Product design. It is customer’s sole responsibility to determine whether the NXP
data sheet shall define the specification of the product as agreed between Semiconductors product is suitable and fit for the customer’s applications and
NXP Semiconductors and its customer, unless NXP Semiconductors and products planned, as well as for the planned application and use of
customer have explicitly agreed otherwise in writing. In no event however, customer’s third party customer(s). Customers should provide appropriate
shall an agreement be valid in which the NXP Semiconductors product is design and operating safeguards to minimize the risks associated with their
deemed to offer functions and qualities beyond those described in the applications and products.
Product data sheet.
NXP Semiconductors does not accept any liability related to any default,
damage, costs or problem which is based on any weakness or default in the
13.3 Disclaimers customer’s applications or products, or the application or use by customer’s
third party customer(s). Customer is responsible for doing all necessary
testing for the customer’s applications and products using NXP
Limited warranty and liability — Information in this document is believed to
Semiconductors products in order to avoid a default of the applications and
be accurate and reliable. However, NXP Semiconductors does not give any
the products or of the application or use by customer’s third party
representations or warranties, expressed or implied, as to the accuracy or
customer(s). NXP does not accept any liability in this respect.
completeness of such information and shall have no liability for the
consequences of use of such information. NXP Semiconductors takes no Limiting values — Stress above one or more limiting values (as defined in
responsibility for the content in this document if provided by an information the Absolute Maximum Ratings System of IEC60134) will cause permanent
source outside of NXP Semiconductors. damage to the device. Limiting values are stress ratings only and (proper)
operation of the device at these or any other conditions above those given in
In no event shall NXP Semiconductors be liable for any indirect, incidental,
the Recommended operating conditions section (if present) or the
punitive, special or consequential damages (including - without limitation - lost
Characteristics sections of this document is not warranted. Constant or
profits, lost savings, business interruption, costs related to the removal or
repeated exposure to limiting values will permanently and irreversibly affect
replacement of any products or rework charges) whether or not such
the quality and reliability of the device.
damages are based on tort (including negligence), warranty, breach of
contract or any other legal theory. Terms and conditions of commercial sale — NXP Semiconductors
products are sold subject to the general terms and conditions of commercial
Notwithstanding any damages that customer might incur for any reason
whatsoever, NXP Semiconductors’ aggregate and cumulative liability towards sale, as published at http://www.nxp.com/profile/terms, unless otherwise
customer for the products described herein shall be limited in accordance agreed in a valid written individual agreement. In case an individual
with the Terms and conditions of commercial sale of NXP Semiconductors. agreement is concluded only the terms and conditions of the respective
agreement shall apply. NXP Semiconductors hereby expressly objects to
Right to make changes — NXP Semiconductors reserves the right to make applying the customer’s general terms and conditions with regard to the
changes to information published in this document, including without purchase of NXP Semiconductors products by customer.
limitation specifications and product descriptions, at any time and without
notice. This document supersedes and replaces all information supplied prior No offer to sell or license — Nothing in this document may be interpreted or
to the publication hereof. construed as an offer to sell products that is open for acceptance or the grant,
conveyance or implication of any license under any copyrights, patents or
other industrial or intellectual property rights.
BGA2817 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2017. All rights reserved.
Product data sheet Rev. 7 — 30 March 2017 11 of 13

BGA2817
NXP Semiconductors
MMIC wideband amplifier
Export control — This document as well as the item(s) described herein NXP Semiconductors’ specifications such use shall be solely at customer’s
may be subject to export control regulations. Export might require a prior own risk, and (c) customer fully indemnifies NXP Semiconductors for any
authorization from competent authorities. liability, damages or failed product claims resulting from customer design and
use of the product for automotive applications beyond NXP Semiconductors’
Non-automotive qualified products — Unless this data sheet expressly
standard warranty and NXP Semiconductors’ product specifications.
states that this specific NXP Semiconductors product is automotive qualified,
the product is not suitable for automotive use. It is neither qualified nor tested Translations — A non-English (translated) version of a document is for
in accordance with automotive testing or application requirements. NXP reference only. The English version shall prevail in case of any discrepancy
Semiconductors accepts no liability for inclusion and/or use of between the translated and English versions.
non-automotive qualified products in automotive equipment or applications.
In the event that customer uses the product for design-in and use in 13.4 Trademarks
automotive applications to automotive specifications and standards, customer
(a) shall use the product without NXP Semiconductors’ warranty of the
Notice: All referenced brands, product names, service names and trademarks
product for such automotive applications, use and specifications, and (b)
are the property of their respective owners.
whenever customer uses the product for automotive applications beyond
14. Contact information
For more information, please visit: http://www.nxp.com
For sales office addresses, please send an email to: salesaddresses@nxp.com
BGA2817 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2017. All rights reserved.
Product data sheet Rev. 7 — 30 March 2017 12 of 13

BGA2817
NXP Semiconductors
MMIC wideband amplifier
15. Contents
1 Product profile. . . . . . . . . . . . . . . . . . . . . . . . . . 1
1.1 General description . . . . . . . . . . . . . . . . . . . . . 1
1.2 Features and benefits. . . . . . . . . . . . . . . . . . . . 1
1.3 Applications . . . . . . . . . . . . . . . . . . . . . . . . . . . 1
2 Pinning information. . . . . . . . . . . . . . . . . . . . . . 1
3 Ordering information. . . . . . . . . . . . . . . . . . . . . 2
4 Marking. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 2
5 Limiting values. . . . . . . . . . . . . . . . . . . . . . . . . . 2
6 Thermal characteristics . . . . . . . . . . . . . . . . . . 2
7 Characteristics. . . . . . . . . . . . . . . . . . . . . . . . . . 2
8 Application information. . . . . . . . . . . . . . . . . . . 4
8.1 Application examples . . . . . . . . . . . . . . . . . . . . 4
8.2 Tables. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 4
9 Test information. . . . . . . . . . . . . . . . . . . . . . . . . 8
10 Package outline. . . . . . . . . . . . . . . . . . . . . . . . . 9
11 Abbreviations. . . . . . . . . . . . . . . . . . . . . . . . . . 10
12 Revision history. . . . . . . . . . . . . . . . . . . . . . . . 10
13 Legal information. . . . . . . . . . . . . . . . . . . . . . . 11
13.1 Data sheet status . . . . . . . . . . . . . . . . . . . . . . 11
13.2 Definitions. . . . . . . . . . . . . . . . . . . . . . . . . . . . 11
13.3 Disclaimers. . . . . . . . . . . . . . . . . . . . . . . . . . . 11
13.4 Trademarks. . . . . . . . . . . . . . . . . . . . . . . . . . . 12
14 Contact information. . . . . . . . . . . . . . . . . . . . . 12
15 Contents. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 13
Please be aware that important notices concerning this document and the product(s)
described herein, have been included in section ‘Legal information’.
© NXP Semiconductors N.V. 2017. All rights reserved.
For more information, please visit: http://www.nxp.com
For sales office addresses, please send an email to: salesaddresses@nxp.com
Date of release: 30 March 2017
Document identifier: BGA2817