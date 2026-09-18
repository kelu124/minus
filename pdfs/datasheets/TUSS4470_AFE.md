TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022
TUSS4470 Transformer Drive Ultrasonic Sensor IC With Logarithmic Amplifier
| 1 Features | 3 Description |     |     |     |     |     |     |
| ---------- | ------------- | --- | --- | --- | --- | --- | --- |
• Integrated driver for directly driving transducers  The  TUSS4470  is  a  highly  integrated  direct  drive
and receiver stage with analog output for  analog front end for industrial ultrasonic applications.
ultrasound applications The transducer drive stage is an internal H-bridge
• 86-dB input dynamic range analog front-end that  can  be  configured  to  drive  the  transducer
– First stage low noise amplifier adjustable to 10,  in  direct-drive  mode  to  achieve  maximum  voltage
12.5, 15 and 20 V/V across  the  transducer.  The  internal  H-bridge  can
– Configurable bandpass filter from 40 KHz to  also be configured as a pre-driver for external FETs,
enabling higher current and voltage drive for larger
500 KHz
| – Wide-band logarithmic amplifier | transducers. |     |     |     |     |     |     |
| --------------------------------- | ------------ | --- | --- | --- | --- | --- | --- |
• Supported transducer frequencies (controlled by
The receive signal path includes a low-noise linear
external clock)
amplifier, a bandpass filter, followed by a logarithmic
– 40 KHz to 1 MHz gain amplifier for input dependent amplification. The
– Pre-driver mode: 40 KHz to 440 KHz
|     | logarithmic  |     | amplifier  | allows  | for  | high  sensitivity  | for  |
| --- | ------------ | --- | ---------- | ------- | ---- | ------------------ | ---- |
• For low-power applications
weak echo signals and offers excellent input dynamic
– Standby mode: 1.7 mA (typical) range over full range of reflected echoes.
– Sleep mode: 220 µA (typical)
|     | The  | drivers  |     | can  be  controlled  |     | directly  through  | the  |
| --- | ---- | -------- | --- | -------------------- | --- | ------------------ | ---- |
• Configurable drive stage:
microcontroller for complete customization of the burst
– Direct drive using internal H-Bridge for
|     | signal,  |     | or  can  | be  programmed  |     | through  SPI  | with  |
| --- | -------- | --- | -------- | --------------- | --- | ------------- | ----- |
transducer excitation
|     | a   | customizable  |     | burst  length.  |     | The  TUSS4470  | can  |
| --- | --- | ------------- | --- | --------------- | --- | -------------- | ---- |
– Pre-driver configuration to use internal H-bridge
support a single transducer to send and receive burst
to drive external Field Effect Transistors (FETs)
signals, or can set up two transducers to split the
for higher current drive
send and receive functions.
– Configurable burst patterns using IO1 and IO2
| pins |     |     |     | Device Information(1)  |     |     |     |
| ---- | --- | --- | --- | ---------------------- | --- | --- | --- |
• Outputs:
|     |     | PART NUMBER |     | PACKAGE |     | BODY SIZE (NOM) |     |
| --- | --- | ----------- | --- | ------- | --- | --------------- | --- |
– Voltage output of the demodulated echo
|     | TUSS4470 |     |     | WQFN (20) |     | 4.00 mm × 4.00 mm |     |
| --- | -------- | --- | --- | --------- | --- | ----------------- | --- |
envelope on VOUT
(1) For all available packages, see the orderable addendum at
– Input signal zero crossing comparator output on
the end of the data sheet.
OUT3 pin
| – Programmable VOUT threshold crossing on  |     | > D1 | RPWR |     |     |     |     |
| ------------------------------------------ | --- | ---- | ---- | --- | --- | --- | --- |
VIN
OUT4 pin
CPWR1
• Serial Peripheral Interface (SPI) for configuration
|                          |     |  MCU |     | IO2 VPWR | OUTA |     |     |
| ------------------------ | --- | ---- | --- | -------- | ---- | --- | --- |
| by microcontroller (MCU) |     | GPIO |     | IO1      | VDRV |     |     |
|                          |     | GPIO |     | OUT3     |      |     |     |
|                          |     | GPIO |     | OUT4     | OUTB |     |     |
| 2 Applications           |     |      |     |          | FLT  |     |     |
NCS
|     |     |     |     | S D O |     | CFLT CPWR2 |     |
| --- | --- | --- | --- | ----- | --- | ---------- | --- |
|     |     | SPI |     | S D I |     |            |     |
• Position sensor
|                     |     |       |     | SSCCLLKK |      | CINP RINP |     |
| ------------------- | --- | ----- | --- | -------- | ---- | --------- | --- |
| • Level transmitter |     |       |     | VOUT     | INP  |           |     |
|                     |     |   ADC |     | DNGD     | DNGS | CINN      |     |
|                     |     | LDO   |     | VDD DNG  | INN  |           |     |
• Proximity sensor
CVDD
TUSS4470 Application Diagram
An IMPORTANT NOTICE at the end of this data sheet addresses availability, warranty, changes, use in safety-critical applications,
intellectual property matters and other important disclaimers. PRODUCTION DATA.

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
Table of Contents
1 Features............................................................................1 7.3 Feature Description...................................................11
2 Applications.....................................................................1 7.4 Device Functional Modes..........................................20
3 Description.......................................................................1 7.5 Programming............................................................21
4 Revision History..............................................................2 7.6 Register Maps...........................................................23
5 Pin Configuration and Functions ..................................3 8 Application and Implementation..................................30
6 Specifications..................................................................4 8.1 Application Information.............................................30
6.1 Absolute Maximum Ratings........................................4 8.2 Typical Application....................................................30
6.2 ESD Ratings...............................................................4 9 Power Supply Recommendations................................36
6.3 Recommended Operating Conditions.........................4 10 Layout...........................................................................37
6.4 Thermal Information ...................................................5 10.1 Layout Guidelines...................................................37
6.5 Power-Up Characteristics...........................................5 10.2 Layout Example......................................................38
6.6 Transducer Drive ........................................................5 11 Device and Documentation Support..........................39
6.7 Receiver Characteristics.............................................6 11.1 Receiving Notification of Documentation Updates..39
6.8 Echo Interrupt Comparator Characteristics.................7 11.2 Support Resources.................................................39
6.9 Digital I/O Characteristics...........................................7 11.3 Trademarks.............................................................39
6.10 Switching Characteristics..........................................8 11.4 Electrostatic Discharge Caution..............................39
6.11 Typical Characteristics..............................................8 11.5 Glossary..................................................................39
7 Detailed Description......................................................11 12 Mechanical, Packaging, and Orderable
7.1 Overview...................................................................11 Information....................................................................39
7.2 Functional Block Diagram.........................................11
4 Revision History
NOTE: Page numbers for previous revisions may differ from page numbers in the current version.
Changes from Revision * (April 2018) to Revision A (May 2022) Page
• Updated the numbering format for tables, figures, and cross-references throughout the document..................1
• Changed all instances of legacy terminology to controller and peripheral where SPI is mentioned...................1
• Changed operating free-air temperature minimum from: –25°C to: –40°C.........................................................4
2 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
| www.ti.com |     |     |     | SLDS251A – DECEMBER 2019 – REVISED MAY 2022 |
| ---------- | --- | --- | --- | ------------------------------------------- |
5 Pin Configuration and Functions
RWPV 4TUO VRDV BTUO
TLF
02 91 81 71 61
|     |     | OUT3 1 | 15         |  OUTA |
| --- | --- | ------ | ---------- | ----- |
|     |     | DGND 2 | 14         |  GND  |
|     |     | NCS 3  | Thermal 13 |  SGND |
Pad
|     |     | SCLK 4 | 12  |  INP |
| --- | --- | ------ | --- | ---- |
|     |     | SDI 5  | 11  |  INN |
6 7 8 9 01
ODS 1OI 2OI TUOV DDV
Not to scale
Figure 5-1. RTJ Package 20-Pin WQFN With Exposed Thermal Pad (Top View)
PIN
|     |      | TYPE(1)                          |     | DESCRIPTION |
| --- | ---- | -------------------------------- | --- | ----------- |
| NO. | NAME |                                  |     |             |
| 1   | OUT3 | O General-purpose digital output |     |             |
| 2   | DGND | G Digital ground                 |     |             |
| 3   | NCS  | I SPI negative chip select       |     |             |
| 4   | SCLK | I SPI CLK                        |     |             |
| 5   | SDI  | I SPI data input                 |     |             |
| 6   | SDO  | O SPI data output                |     |             |
| 7   | IO1  | I General-purpose digital input  |     |             |
| 8   | IO2  | I General-purpose digital input  |     |             |
| 9   | VOUT | O Demodulated echo analog output |     |             |
| 10  | VDD  | P Voltage regulator input        |     |             |
| 11  | INN  | I Negative transducer receive    |     |             |
| 12  | INP  | I Positive transducer receive    |     |             |
| 13  | SGND | G Sensor ground (quiet)          |     |             |
| 14  | GND  | G Ground                         |     |             |
| 15  | OUTA | O Transducer driver output A     |     |             |
| 16  | OUTB | O Transducer driver output B     |     |             |
| 17  | VDRV | P H-bridge driver supply voltage |     |             |
| 18  | FLT  | I/O Filter components            |     |             |
| 19  | OUT4 | O General-purpose digital output |     |             |
| 20  | VPWR | P Input supply voltage           |     |             |
(1) I = input, O = output, I/O = input and output, G = ground, P = power
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 3
Product Folder Links: TUSS4470

TUSS4470
| SLDS251A – DECEMBER 2019 – REVISED MAY 2022 |     |     |     | www.ti.com |
| ------------------------------------------- | --- | --- | --- | ---------- |
6 Specifications
6.1 Absolute Maximum Ratings
over operating free-air temperature range (unless otherwise noted)(1)
|     |                      | MIN  | MAX | UNIT |
| --- | -------------------- | ---- | --- | ---- |
| V   | Supply voltage range | –0.3 | 40  | V    |
VPWR
| V VDD  | Voltage regulator input voltage | –0.3   | 5.5         | V   |
| ------ | ------------------------------- | ------ | ----------- | --- |
| V VDRV | H-bridge drive voltage          | –0.3 V | VPWR  + 0.3 | V   |
| V      | Filter component pin            | –0.3   | V  + 0.3    | V   |
| FLT    |                                 |        | VDD         |     |
| V      | INP, INN pins input voltage     | 0.5    | 1.3         | V   |
INX
| V      | SCLK, SDI, NCS, IOx pin input voltage | –0.3 | V  + 0.3     | V   |
| ------ | ------------------------------------- | ---- | ------------ | --- |
| DIG_IN |                                       |      | VDD          |     |
| V VOUT | Analog output voltage                 | –0.3 | V VDD  + 0.3 | V   |
V DIG_OUT SDO, OUTx, IOx pin output voltage –0.3 V VDD  + 0.3 V
| V      | OUTA, OUTB pins output voltage | –0.3 V |  + 0.3 | V   |
| ------ | ------------------------------ | ------ | ------ | --- |
| OUTA_B |                                |        | VDRV   |     |
| T      | Ambient temperature            | –40    | 105    |     |
A
| T   | Junction temperature | –40 | 125 | °C  |
| --- | -------------------- | --- | --- | --- |
J
| T stg | Storage temperature | –40 | 125 |     |
| ----- | ------------------- | --- | --- | --- |
(1) Stresses beyond those listed under Absolute Maximum Rating may cause permanent damage to the device. These are stress
ratings only, which do not imply functional operation of the device at these or any other conditions beyond those indicated
under Recommended Operating Condition. Exposure to absolute-maximum-rated conditions for extended periods may affect device
reliability.
6.2 ESD Ratings
|     |     |     | VALUE | UNIT |
| --- | --- | --- | ----- | ---- |
Human body model (HBM), per ANSI/ESDA/
±2000
JEDEC JS-001, all pins(1)
| V   | Electrostatic discharge |     |     | V   |
| --- | ----------------------- | --- | --- | --- |
(ESD)
Charged device model (CDM), per JEDEC  ±500
specification JESD22-C101, all pins(2)
(1) JEDEC document JEP155 states that 500-V HBM allows safe manufacturing with a standard ESD control process.
(2) JEDEC document JEP157 states that 250-V CDM allows safe manufacturing with a standard ESD control process.
6.3 Recommended Operating Conditions
over operating free-air temperature range (unless otherwise noted)
|     |                            | MIN NOM | MAX | UNIT |
| --- | -------------------------- | ------- | --- | ---- |
| V   | Supply voltage on VPWR pin | 5       | 36  | V    |
VPWR
Voltage on VDRV pin, internal regulation on VDRV disabled
|     | (VDRV_HI_Z=1)(1) | 5   | 36  | V   |
| --- | ---------------- | --- | --- | --- |
V
| VDRV | VDRV voltage Pre driver mode (PRE_DRIVER_MODE=1), internal  |     |     |     |
| ---- | ----------------------------------------------------------- | --- | --- | --- |
|      |                                                             | 5   | 15  | V   |
regulation on VDRV disabled (VDRV_HI_Z=1)(1)
| V       | Digital I/O pins        | –0.1 | V   | V   |
| ------- | ----------------------- | ---- | --- | --- |
| VDIG_IO |                         |      | VDD |     |
| V       | Regulated voltage Input | 3.1  | 5.5 | V   |
VDD
I VPWR_INDIR Current consumption at VPWR pin during ranging 150 240 340 µA
| I   | Current consumption at VPWR in standby mode | 150 220 | 340 | µA  |
| --- | ------------------------------------------- | ------- | --- | --- |
VPWR_STDBY
| I   | Current consumption at VDD pin during ranging | 7 11.5 | 13  | mA  |
| --- | --------------------------------------------- | ------ | --- | --- |
VDD_INDIR
| I   | Current consumption at VDD in standby mode | 1.2 | 1.5 2.5 | mA  |
| --- | ------------------------------------------ | --- | ------- | --- |
VDD_STDBY
| I VDD_SLEEP | Current consumption in sleep mode |     | 350 | µA  |
| ----------- | --------------------------------- | --- | --- | --- |
| T A         | Operating free-air temperature    | –40 | 105 | °C  |
| T           | Operating junction temperature    | –40 | 125 | °C  |
J
| (1) Always V |  > V  + 0.3 V to prevent reverse current from VDRV pin to VPWR pin |     |     |     |
| ------------ | ------------------------------------------------------------------ | --- | --- | --- |
VPWR VDRV
4 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
| www.ti.com |     |     |     | SLDS251A – DECEMBER 2019 – REVISED MAY 2022 |     |     |
| ---------- | --- | --- | --- | ------------------------------------------- | --- | --- |
6.4 Thermal Information
TUSS4470
|     |     | THERMAL METRIC(1) |     |     | RTJ (WQFN) | UNIT |
| --- | --- | ----------------- | --- | --- | ---------- | ---- |
20 PINS
| R θJA | Junction-to-ambient thermal resistance |     |     |     | 36.3 | °C/W |
| ----- | -------------------------------------- | --- | --- | --- | ---- | ---- |
R θJC(top) Junction-to-case (top) thermal resistance 29.4 °C/W
| R   | Junction-to-board thermal resistance |     |     |     | 14.7 | °C/W |
| --- | ------------------------------------ | --- | --- | --- | ---- | ---- |
θJB
| Ψ   | Junction-to-top characterization parameter |     |     |     | 0.4 | °C/W |
| --- | ------------------------------------------ | --- | --- | --- | --- | ---- |
JT
| Ψ   | Junction-to-board characterization parameter |     |     |     | 14.7 | °C/W |
| --- | -------------------------------------------- | --- | --- | --- | ---- | ---- |
JB
R θJC(bot) Junction-to-case (bottom) thermal resistance 4.7 °C/W
(1) For more information about traditional and new thermal metrics, see the Semiconductor and IC Package Thermal Metrics application
report, SPRA953.
6.5 Power-Up Characteristics
over operating free-air temperature range, V , V  and V  recommended voltage range (unless otherwise noted)
|           |     |     | VPWR VDRV       | VDD |         |          |
| --------- | --- | --- | --------------- | --- | ------- | -------- |
| PARAMETER |     |     | TEST CONDITIONS |     | MIN TYP | MAX UNIT |
Time to power
up when SPI
| t   |     |     |     |     |     | 10 ms |
| --- | --- | --- | --- | --- | --- | ----- |
PWR_ON communication is
possible
VDRV_VOLTAGE_LEVEL = 0x0; V VPWR  > V VDRV  + 100 mV 4.5 5 5.3
VDRV_VOLTAGE_LEVEL = 0x4; V VPWR  > V VDRV  + 100 mV 8.1 9 9.9
|     |     | VDRV_VOLTAGE_LEVEL = 0x7; V |     |  > V  + 100 mV | 11.5 12 | 12.6 |
| --- | --- | --------------------------- | --- | -------------- | ------- | ---- |
VPWR VDRV
|                       |     | VDRV_VOLTAGE_LEVEL = 0x8; V |     |  > V  + 100 mV | 12.09 13 | 13.91 |
| --------------------- | --- | --------------------------- | --- | -------------- | -------- | ----- |
| Regulated voltage     |     |                             |     | VPWR VDRV      |          |       |
| V VDRV on VDRV pin(1) |     |                             |     |                |          | V     |
|                       |     | VDRV_VOLTAGE_LEVEL = 0xC; V |     |  > V  + 100 mV | 15.81 17 | 18.9  |
VPWR VDRV
VDRV_VOLTAGE_LEVEL = 0xD; V VPWR  > V VDRV  + 100 mV 16.74 18 19.26
|     |     | VDRV_VOLTAGE_LEVEL = 0xE; V |     |  > V  + 100 mV | 17.67 19 | 20.33 |
| --- | --- | --------------------------- | --- | -------------- | -------- | ----- |
VPWR VDRV
|     |     | VDRV_VOLTAGE_LEVEL = 0xF; V |     |  > V  + 100 mV | 19.0 20 | 21.4 |
| --- | --- | --------------------------- | --- | -------------- | ------- | ---- |
VPWR VDRV
|                   |     | VDRV_CURRENT_LEVEL = 0x0; V |     |  > V  + 1 V | 8.5 10 | 11.5 |
| ----------------- | --- | --------------------------- | --- | ----------- | ------ | ---- |
| I VDRV capacitor  |     |                             |     | VPWR VDRV   |        | mA   |
VDRV charging current
|     |     | VDRV_CURRENT_LEVEL = 0x1; V |     |  > V  + 1 V | 17 20 | 23  |
| --- | --- | --------------------------- | --- | ----------- | ----- | --- |
VPWR VDRV
(1) Other VDRV voltage levels possible.
6.6 Transducer Drive
over operating free-air temperature range, V , V  and V  recommended voltage range (unless otherwise noted)
|                                  |           |     | VPWR VDRV  | VDD             |         |          |
| -------------------------------- | --------- | --- | ---------- | --------------- | ------- | -------- |
|                                  | PARAMETER |     |            | TEST CONDITIONS | MIN TYP | MAX UNIT |
| R High-side MOSFET on-resistance |           |     | T  =+105°C |                 |         | 30 Ω     |
| HS_FET                           |           |     | A          |                 |         |          |
| R Low-side MOSFET on-resistance  |           |     | T  =+105°C |                 |         | 20 Ω     |
| LS_FET                           |           |     | A          |                 |         |          |
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 5
Product Folder Links: TUSS4470

TUSS4470
| SLDS251A – DECEMBER 2019 – REVISED MAY 2022 |     |     |     |     |     |     |     |     |     | www.ti.com |
| ------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---------- |
6.7 Receiver Characteristics
over operating free-air temperature range, V , V  and V  recommended voltage range (unless otherwise noted)
|       |                  |                    | VPWR            | VDRV     | VDD |     |      |      |      |      |
| ----- | ---------------- | ------------------ | --------------- | -------- | --- | --- | ---- | ---- | ---- | ---- |
|       | PARAMETER        |                    | TEST CONDITIONS |          |     |     | MIN  | TYP  | MAX  | UNIT |
| G     |                  | LNA_GAIN = 0x00; f |                 | = 58 KHz |     |     | 13.7 | 15   | 16.8 |      |
| LNA   |                  |                    | DRV_CLK         |          |     |     |      |      |      |      |
| G     | Low-noise        | LNA_GAIN = 0x01; f |                 | = 58 KHz |     |     | 9.4  | 10   |      | 12   |
| LNA   |                  |                    | DRV_CLK         |          |     |     |      |      |      |      |
|       | amplifier fixed  |                    |                 |          |     |     |      |      |      | V/V  |
| G     |                  | LNA_GAIN = 0x10; f |                 | = 58 KHz |     |     | 17.6 | 20   | 21.8 |      |
| LNA   | gain             |                    | DRV_CLK         |          |     |     |      |      |      |      |
| G LNA |                  | LNA_GAIN = 0x11; f | DRV_CLK         | = 58 KHz |     |     | 11.6 | 12.5 | 14.2 |      |
Minimum
| DR  | VIN_MIN receive input(2) |     |     |     |     |     |     | 2.4 |     | µVrms |
| --- | ------------------------ | --- | --- | --- | --- | --- | --- | --- | --- | ----- |
LOGAMP_DIS_FIRST=0x0;LOGAMP_DIS_LAST=0x0
|     | Maximum                  | LNA_GAIN=0x00; ERR      |     | LOG  < ± 3dB; f | DRV_CLK  |  < 500KHz |     |      |     |       |
| --- | ------------------------ | ----------------------- | --- | --------------- | -------- | --------- | --- | ---- | --- | ----- |
| DR  |                          |                         |     |                 |          |           |     | 48   |     | mVrms |
|     | VIN_MAX receive input(2) |                         |     |                 |          |           |     |      |     |       |
|     | Slope of analog          | VOUT_SCALE_SEL = 0x0; f |     |                 | = 58 KHz |           | 25  | 29.7 |     | 33    |
| SL  |                          |                         |     | DRV_CLK         |          |           |     |      |     | mV/dB |
| AFE | front end(4)             |                         |     |                 |          |           |     |      |     |       |
|     |                          | VOUT_SCALE_SEL = 0x1; f |     | DRV_CLK         | = 58 KHz |           | 38  | 45.1 |     | 46    |
LOGAMP_DIS_FIRST = 0x0; LOGAMP_DIS_LAST = 0x0
|     | Receiver path  | ERR  < ± 3 dB; f |         |  < 500 KHz |     |     | 82  |     |     | 92  |
| --- | -------------- | ---------------- | ------- | ---------- | --- | --- | --- | --- | --- | --- |
|     |                | LOG              | DRV_CLK |            |     |     |     |     |     |     |
dynamic range
LOGAMP_DIS_FIRST = 0x0; LOGAMP_DIS_LAST = 0x1
|     | (minimum to    |                                             |         |            |     |     | 74  |     |     | 86  |
| --- | -------------- | ------------------------------------------- | ------- | ---------- | --- | --- | --- | --- | --- | --- |
|     |                | ERR  < ± 3 dB; f                            |         |  < 500 KHz |     |     |     |     |     |     |
|     | maximum input) | LOG                                         | DRV_CLK |            |     |     |     |     |     |     |
|     | (2)            | LOGAMP_DIS_FIRST = 0x1; LOGAMP_DIS_LAST=0x1 |         |            |     |     |     |     |     |     |
|     |                |                                             |         |            |     |     | 59  |     |     | 70  |
| DR  |                | ERR  < ± 3dB; f                             |         |  < 500 KHz |     |     |     |     |     | dB  |
|     | AFE            | LOG                                         | DRV_CLK |            |     |     |     |     |     |     |
Receiver path
dynamic
|     | Range (noise  | LOGAMP_DIS_FIRST = 0x0; LOGAMP_DIS_LAST = 0x0 |         |            |     |     |     |     |     |     |
| --- | ------------- | --------------------------------------------- | ------- | ---------- | --- | --- | --- | --- | --- | --- |
|     | floor to      | ERR  < ± 3 dB; f                              |         |  < 500 KHz |     |     | 74  |     |     | 84  |
|     |               | LOG                                           | DRV_CLK |            |     |     |     |     |     |     |
maximum input)
(3)
Logamp
| BW  |               | Information only |     |     |     |     | 40  |     | 1000 | KHz |
| --- | ------------- | ---------------- | --- | --- | --- | --- | --- | --- | ---- | --- |
|     | LOG bandwidth |                  |     |     |     |     |     |     |      |     |
LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0;
|     |     |     |     |     |     |     | -108 |     | -97 |     |
| --- | --- | --- | --- | --- | --- | --- | ---- | --- | --- | --- |
f DRV_CLK  = 40 KHz
INT Intercept point  LOGAMP_DIS_FIRST = 0x0; LOGAMP_DIS_LAST=0x1; -94 -86 dBV
|     | LOG in dBV | f = 40 KHz |     |     |     |     |     |     |     |     |
| --- | ---------- | ---------- | --- | --- | --- | --- | --- | --- | --- | --- |
DRV_CLK
LOGAMP_DIS_FIRST = 0x1; LOGAMP_DIS_LAST=0x1;
|     |     |     |     |     |     |     | -80 |     | -70 |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
f = 40 KHz
DRV_CLK
Log
| ERR | LOG conformance  | Information only |     |     |     |     | -3  |     |     | 3 dB |
| --- | ---------------- | ---------------- | --- | --- | --- | --- | --- | --- | --- | ---- |
error
Configurable
|     | range of center  | BPF_BYPASS = 0x0; BPF_FC_TRIM = 0x0;    |     |     |     |     |     |     |     |     |
| --- | ---------------- | --------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
| f   |                  |                                         |     |     |     |     | 40  |     | 500 | KHz |
| BPF | frequency of     | set by different values of BPF_HPF_FREQ |     |     |     |     |     |     |     |     |
BPF
Q of bandpass
| Q   |        | BPF_BYPASS = 0x0; BPF_Q_SEL = 0x0(1) |     |     |     |     | 3   | 4   |     | 5.2 |
| --- | ------ | ------------------------------------ | --- | --- | --- | --- | --- | --- | --- | --- |
| BPF | filter |                                      |     |     |     |     |     |     |     |     |
Internal resistor
| R LPF | on FLT pin to  |     |     |     |     |     |     | 6.25 |     | KΩ  |
| ----- | -------------- | --- | --- | --- | --- | --- | --- | ---- | --- | --- |
ground
|     |     | V = 3.3 V; f |  = 40 KHz;  VOUT_SCALE_SEL = 0x0 |     |     |     |     |     |      |     |
| --- | --- | ------------ | -------------------------------- | --- | --- | --- | --- | --- | ---- | --- |
|     |     | VDD          | DRV_CLK                          |     |     |     | 0.3 |     | 0.45 |     |
Output pedestal LOGAMP_DIS_FIRST = 0x0; LOGAMP_DIS_LAST = 0x0
| V O_PDSTL |          |              |                                  |     |     |     |      |     |       | V   |
| --------- | -------- | ------------ | -------------------------------- | --- | --- | --- | ---- | --- | ----- | --- |
|           | level(2) | V = 5.0 V; f |  = 40 KHz;  VOUT_SCALE_SEL = 0x1 |     |     |     |      |     |       |     |
|           |          | VDD          | DRV_CLK                          |     |     |     | 0.45 |     | 0.675 |     |
LOGAMP_DIS_FIRST = 0x0;LOGAMP_DIS_LAST = 0x0
6 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
| www.ti.com |     |     |     |     | SLDS251A – DECEMBER 2019 – REVISED MAY 2022 |     |     |
| ---------- | --- | --- | --- | --- | ------------------------------------------- | --- | --- |
over operating free-air temperature range, V VPWR , V VDRV  and V VDD  recommended voltage range (unless otherwise noted)
| PARAMETER |                 |                                             | TEST CONDITIONS |            |     | MIN TYP | MAX UNIT |
| --------- | --------------- | ------------------------------------------- | --------------- | ---------- | --- | ------- | -------- |
|           |                 | V =3.3 V; f                                 |  = 40 KHz; C    |  = 15      |     |         |          |
|           |                 | VDD DRV_CLK                                 |                 | FLT        |     |         |          |
|           |                 | nF;  VOUT_SCALE_SEL = 0x0                   |                 |            |     | 50      | 200      |
|           | Output peak-to- | LOGAMP_DIS_FIRST = 0x0; LOGAMP_DIS_LAST=0x0 |                 |            |     |         |          |
| V         |                 |                                             |                 |            |     |         | mVpp     |
| N_pk_pk   | peak noise      |                                             |                 |            |     |         |          |
|           |                 | V VDD =5.0 V; f DRV_CLK                     |  = 40 KHz; C    | FLT  = 15  |     |         |          |
|           |                 | nF;  VOUT_SCALE_SEL = 0x1                   |                 |            |     | 75      | 300      |
LOGAMP_DIS_FIRST = 0x0; LOGAMP_DIS_LAST = 0x0
(1) Other choices of Q possible.
(2) Measured with effectively very large C . Actual minimum signal detectable will depend on V .  Minimum and maximum input
|                           |     | FLT |     |     |     | N_pk_pk |     |
| ------------------------- | --- | --- | --- | --- | --- | ------- | --- |
| levels are defined by ERR |     | .   |     |     |     |         |     |
LOG
(3) Measured with different C  values according to Equation 3. Noise floor is set by V  in addition to V .
|     |     | FLT |     |     | N_PK_PK | O_PDSTL |     |
| --- | --- | --- | --- | --- | ------- | ------- | --- |
(4) Slope measured with factory trim at f = 58 KHz. Slope can be adjusted with LOGAMP_SLOPE_ADJ bits for different f
|     |     | DRV_CLK  |     |     |     |     | DRV_CLK  |
| --- | --- | -------- | --- | --- | --- | --- | -------- |
settings.
6.8 Echo Interrupt Comparator Characteristics
over operating free-air temperature range (unless otherwise noted)
|     | PARAMETER |     |     | TEST CONDITIONS |     | MIN TYP | MAX UNIT |
| --- | --------- | --- | --- | --------------- | --- | ------- | -------- |
VOUT_SCALE_SEL = 0x0
|     |     |     | ECHO_INT_THR_SEL = 0x0 |     |     | 0.37 0.4 | 0.43 |
| --- | --- | --- | ---------------------- | --- | --- | -------- | ---- |
|     |     |     | ECHO_INT_THR_SEL = 0x5 |     |     | 0.56 0.6 | 0.64 |
Echo interrupt comparator
| V ECMP_THR_0 | threshold(1)                         |     |                        |     |     |          | V     |
| ------------ | ------------------------------------ | --- | ---------------------- | --- | --- | -------- | ----- |
|              |                                      |     | ECHO_INT_THR_SEL = 0xA |     |     | 0.75 0.8 | 0.85  |
|              |                                      |     | ECHO_INT_THR_SEL = 0xF |     |     | 0.94 1   | 1.06  |
| V ECMP_HYS_0 | Echo interrupt comparator hysteresis |     |                        |     |     | 7        | 68 mV |
VOUT_SCALE_SEL = 0x1
|     |     |     | ECHO_INT_THR_SEL = 0x0 |     |     | 0.56 0.6 | 0.64 |
| --- | --- | --- | ---------------------- | --- | --- | -------- | ---- |
Echo interrupt comparator  ECHO_INT_THR_SEL = 0x5 0.84 0.9 0.96
| V           |              |     |                        |     |     |          | V    |
| ----------- | ------------ | --- | ---------------------- | --- | --- | -------- | ---- |
| E_CMP_THR_1 | threshold(1) |     |                        |     |     |          |      |
|             |              |     | ECHO_INT_THR_SEL = 0xA |     |     | 1.13 1.2 | 1.27 |
|             |              |     | ECHO_INT_THR_SEL = 0xF |     |     | 1.41 1.5 | 1.59 |
Echo interrupt output threshold level
| V          |            |     |     |     |     | 7   | 68 mV |
| ---------- | ---------- | --- | --- | --- | --- | --- | ----- |
| ECMP_HYS_1 | hysteresis |     |     |     |     |     |       |
(1) Other thresholds possible.
6.9 Digital I/O Characteristics
over operating free-air temperature range, V , V  and V  recommended voltage range (unless otherwise noted)
|            |                          |     | VPWR VDRV | VDD             |     |         |          |
| ---------- | ------------------------ | --- | --------- | --------------- | --- | ------- | -------- |
|            | PARAMETER                |     |           | TEST CONDITIONS |     | MIN TYP | MAX UNIT |
| V IH_DIGIO | Digital input high-level |     |           |                 |     | 0.7     | V VDD    |
V IL_DIGIO Digital input low-level NCS, SDI, SCLK and IOx pins 0.3 V VDD
| V   | Digital input hysteresis |     |     |     |     | 100 | mV  |
| --- | ------------------------ | --- | --- | --- | --- | --- | --- |
HYS_DIGIO
V Digital output high-level(1) SDO, OUTx pins; I  = – 1 mA V – 0.1 V
| OH_DIGIO |     |     |     | DIGIO_OUT |     | VDD  |     |
| -------- | --- | --- | --- | --------- | --- | ---- | --- |
V Digital output low-level(1) SDO, OUTx pins;  I  = 1 mA 0.1 V
| OL_DIGIO |     |     |     | DIGIO_OUT |     |     |     |
| -------- | --- | --- | --- | --------- | --- | --- | --- |
V O_CAP Maximum output load capacitance  SDO pin. Information Only 10 pF
R Digital input pullup resistance to VDD NCS, IO1, IO2 pins 80 100 130 kΩ
PU_DIGIO
Digital Input pulldown resistance to
| R        |     |     | SCLK, SDI pins |     |     | 80 100 | 130 kΩ |
| -------- | --- | --- | -------------- | --- | --- | ------ | ------ |
| PD_DIGIO | GND |     |                |     |     |        |        |
(1) No short-circuit protection on output pins. Damage may occur for currents higher than specified.
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 7
Product Folder Links: TUSS4470

TUSS4470
| SLDS251A – DECEMBER 2019 – REVISED MAY 2022 |     |     |     |     | www.ti.com |
| ------------------------------------------- | --- | --- | --- | --- | ---------- |
6.10 Switching Characteristics
over operating free-air temperature range, V , V  and V  recommended voltage range (unless otherwise noted)
|                                          |     | VPWR VDRV VDD             |     |         |          |
| ---------------------------------------- | --- | ------------------------- | --- | ------- | -------- |
| PARAMETER                                |     | TEST CONDITIONS           |     | MIN TYP | MAX UNIT |
| Frequency of drive clock at IO1 and IO2  |     | Used as burst frequency;  |     |         |          |
|                                          |     |                           |     | 40      | 1000 KHz |
| pin ; depends on the VDRV voltage        |     | PRE_DRIVER_MODE = 0x0     |     |         |          |
| f DRV_CLK                                |     | Used as burst frequency;  |     |         |          |
Frequency of drive clock at IO1 and IO2
|     |     | PRE_DRIVER_MODE = 0x1; Load cap  |     | 40  | 440 KHz |
| --- | --- | -------------------------------- | --- | --- | ------- |
pin
on OUTA/OUTB = 2nF
| SPI RATE SPI bit rate |     |     |     |     | 500 KHz |
| --------------------- | --- | --- | --- | --- | ------- |
6.11 Typical Characteristics
| 3       |     |     | 4.5      |     |     |
| ------- | --- | --- | -------- | --- | --- |
| 40 KHz  |     |     | 4 40 KHz |     |     |
| 256 KHz |     |     | 256 KHz  |     |     |
2.5
| 500 KHz  |     |     | 3.5 500 KHz  |     |     |
| -------- | --- | --- | ------------ | --- | --- |
| 750 KHz  |     |     | 750 KHz      |     |     |
| 2 1MHz   |     |     | 3 1MHz       |     |     |
| )V( tuoV |     |     | )V( tuoV 2.5 |     |     |
1.5
2
| 1   |     |     | 1.5 |     |     |
| --- | --- | --- | --- | --- | --- |
1
0.5
0.5
| 0         |            |           | 0         |            |           |
| --------- | ---------- | --------- | --------- | ---------- | --------- |
| 5E-7 1E-5 | 1E-4 1E-3  | 1E-2 1E-1 | 5E-7 1E-5 | 1E-4 1E-3  | 1E-2 1E-1 |
|           | VinRMS (V) |           |           | VinRMS (V) |           |
| VDD:3.3V  |            |           | VDD:5.0V  |            |           |
| Temp:25qC |            |           | Temp:25qC |            |           |
LNA_GAIN=0x0; VOUT_SCALE_SEL=0x0 LNA_GAIN=0x0; VOUT_SCALE_SEL=0x1
LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0 LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0
Figure 6-1. Receive Signal Path Transfer Function for VDD = 3.3  Figure 6-2. Receive Signal Path Transfer Function for VDD = 5 V
V
| 3   |     |     | 3   |     |     |
| --- | --- | --- | --- | --- | --- |
-40qC LNA_GAIN
25qC
| 2.5 |     |     | 2.5 0x01 |     |     |
| --- | --- | --- | -------- | --- | --- |
125qC 0x11
0x00
| 2                                |            |           | 2 0x10              |            |           |
| -------------------------------- | ---------- | --------- | ------------------- | ---------- | --------- |
| )V( tuoV                         |            |           | )V( tuoV            |            |           |
| 1.5                              |            |           | 1.5                 |            |           |
| 1                                |            |           | 1                   |            |           |
| 0.5                              |            |           | 0.5                 |            |           |
| 0                                |            |           | 0                   |            |           |
| 5E-7 1E-5                        | 1E-4 1E-3  | 1E-2 1E-1 | 5E-7 1E-5           | 1E-4 1E-3  | 1E-2 1E-1 |
|                                  | VinRMS (V) |           |                     | VinRMS (V) |           |
| VDD:3.3V                         |            |           | VDD:3.3V; Temp:25qC |            |           |
| Fc:256KHz                        |            |           | Fc:256KHz           |            |           |
| LNA_GAIN=0x0; VOUT_SCALE_SEL=0x0 |            |           | VOUT_SCALE_SEL=0x0  |            |           |
LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0 LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0
Figure 6-3. Receive Signal Path Transfer Function Across
Figure 6-4. Receive Signal Path Transfer Function Across LNA
Temperature
Gain
8 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
| www.ti.com |     |     |     | SLDS251A – DECEMBER 2019 – REVISED MAY 2022 |     |     |     |
| ---------- | --- | --- | --- | ------------------------------------------- | --- | --- | --- |
6.11 Typical Characteristics (continued)
| 3   |     |     | 10  |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- |
DEV_CTRL_2
| 2.5 0x00 |     |     |     |     |     |     |     |
| -------- | --- | --- | --- | --- | --- | --- | --- |
)Bd( rorrE ecnamrofnoC goL 5
0x40
| 0xC0 |     |     |     |     | 3dB |     |     |
| ---- | --- | --- | --- | --- | --- | --- | --- |
2
| )V( tuoV |     |     | 0   |                  |      |                  |     |
| -------- | --- | --- | --- | ---------------- | ---- | ---------------- | --- |
| 1.5      |     |     |     |                  | -3dB |                  |     |
|          |     |     | -5  | -40.00qC, 40KHz  |      | 25.00qC, 500KHz  |     |
| 1        |     |     |     | -40.00qC, 256KHz |      | 125.00qC, 40KHz  |     |
|          |     |     |     | -40.00qC, 500KHz |      | 125.00qC, 256KHz |     |
|          |     |     |     | 25.00qC, 40KHz   |      | 125.00qC, 500KHz |     |
| 0.5      |     |     | -10 |                  |      |                  |     |
25.00qC, 256KHz
| 0         |            |           | -15  |           |            |      |      |
| --------- | ---------- | --------- | ---- | --------- | ---------- | ---- | ---- |
| 5E-7 1E-5 | 1E-4 1E-3  | 1E-2 1E-1 |      |           |            |      |      |
|           |            |           | 1E-6 | 1E-5 1E-4 | 1E-3       | 1E-2 | 1E-1 |
|           | VinRMS (V) |           |      |           | VinRMS (V) |      |      |
VDD:3.3V
| Fc:256KHz |     |     | LNA_GAIN=0x0                              |     |     |     |     |
| --------- | --- | --- | ----------------------------------------- | --- | --- | --- | --- |
| Temp:25qC |     |     | LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0 |     |     |     |     |
Figure 6-5. Receive Signal Path Transfer Function for Various  Figure 6-6. Receive Signal Path Log Conformance Error With
| Logamp Stages Disabled     |     |     |                            | All Stages Enabled |     |     |     |
| -------------------------- | --- | --- | -------------------------- | ------------------ | --- | --- | --- |
| 10                         |     |     | 10                         |                    |     |     |     |
| 7.5                        |     |     | 7.5                        |                    |     |     |     |
| )Bd( rorrE ecnamrofnoC goL |     |     | )Bd( rorrE ecnamrofnoC goL |                    |     |     |     |
| 5                          |     |     | 5                          |                    |     |     |     |
| 2.5                        |     |     | 2.5                        |                    |     |     |     |
|                            | 1dB |     |                            |                    | 1dB |     |     |
| 0                          |     |     | 0                          |                    |     |     |     |
| -2.5                       |     |     | -2.5                       |                    |     |     |     |
-5 -40.00qC, 40KHz 25.00qC, 500KHz -5 -40.00qC, 40KHz 25.00qC, 500KHz
-40.00qC, 256KHz 125.00qC, 40KHz -40.00qC, 256KHz 125.00qC, 40KHz
-7.5 -40.00qC, 500KHz 125.00qC, 256KHz -7.5 -40.00qC, 500KHz 125.00qC, 256KHz
-10 25.00qC, 40KHz 125.00qC, 500KHz -10 25.00qC, 40KHz 125.00qC, 500KHz
|           | 25.00qC, 256KHz |           |       | 25.00qC, 256KHz |      |      |      |
| --------- | --------------- | --------- | ----- | --------------- | ---- | ---- | ---- |
| -12.5     |                 |           | -12.5 |                 |      |      |      |
| -15       |                 |           | -15   |                 |      |      |      |
| 1E-6 1E-5 | 1E-4 1E-3       | 1E-2 1E-1 | 1E-5  | 1E-4            | 1E-3 | 1E-2 | 1E-1 |
VinRMS (V)
VinRMS (V)
| LNA_GAIN=0x0 |     |     | LNA_GAIN=0x0 |     |     |     |     |
| ------------ | --- | --- | ------------ | --- | --- | --- | --- |
LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x1 LOGAMP_DIS_FIRST=0x1; LOGAMP_DIS_LAST=0x1
Figure 6-7. Receive Signal Path Log Conformance Error With  Figure 6-8. Receive Signal Path Log Conformance Error With
| Last Stage Disabled |              |           |                                            | First and Last Stage Disabled |     |     |     |
| ------------------- | ------------ | --------- | ------------------------------------------ | ----------------------------- | --- | --- | --- |
| 2.15                |              |           | 6E+5                                       |                               |     |     |     |
| 2.1                 | BPF_HPF_FREQ |           | )zH( ycneuqerF retneC retliF ssapdnaB 5E+5 |                               |     |     |     |
| 0x00                | 0x0C 0x18    | 0x24 0x2F |                                            | -40qC                         |     |     |     |
| 2.05                |              |           | 4E+5                                       |                               |     |     |     |
| 0x04                | 0x10 0x1C    | 0x28      |                                            | 25qC                          |     |     |     |
| 2                   |              |           |                                            | 125qC                         |     |     |     |
| 0x08                | 0x14 0x20    | 0x2C      | 3E+5                                       |                               |     |     |     |
1.95
| )V( tuoV 1.9 |     |     | 2E+5 |     |     |     |     |
| ------------ | --- | --- | ---- | --- | --- | --- | --- |
1.85
1.8
| 1.75 |     |     | 1E+5 |     |     |     |     |
| ---- | --- | --- | ---- | --- | --- | --- | --- |
1.7
7E+4
1.65
| 1.6  |     |     | 5E+4     |     |     |     |     |
| ---- | --- | --- | -------- | --- | --- | --- | --- |
| 1.55 |     |     | 44EE++44 |     |     |     |     |
3E+4 5E+4 7E+4 1E+5 2E+5 3E+5 5E+5 77EE++55 0x00 0x06 0x0C 0x12 0x18 0x1E 0x24 0x2A 0x30
|           | Vin Frequency (Hz) |     |                                           | BPF_HPF_FREQ Register Value |     |     |     |
| --------- | ------------------ | --- | ----------------------------------------- | --------------------------- | --- | --- | --- |
| VDD:3.3V  |                    |     | LNA_GAIN=0x0;                             |                             |     |     |     |
| Temp:25qC |                    |     | LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0 |                             |     |     |     |
LNA_GAIN=0x0; VOUT_SCALE_SEL=0x0 Figure 6-10. Receive Signal Path Bandpass Filter frequency for
LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0
Various Register Settings
Figure 6-9. Receive Signal Path Bandpass Filter Transfer
Function
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 9
Product Folder Links: TUSS4470

TUSS4470
| SLDS251A – DECEMBER 2019 – REVISED MAY 2022 |     |     |     |     |     |     |     | www.ti.com |
| ------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | ---------- |
6.11 Typical Characteristics (continued)
| 5E+4   |     |     | 9.25E+5 | 1.6E+5 |     |     |     |     |
| ------ | --- | --- | ------- | ------ | --- | --- | --- | --- |
| 4.8E+4 |     |     | 9E+5    |        |     |     |     |     |
)00x0( )zH( ycneuqerF retneC FPB BPF_HPF_FREQ Value )F2x0( )zH( ycneuqerF  retneCFPB -40qC, 3.3V
| 4.6E+4 |     | 0x00 | 8.75E+5 | 1.4E+5                         |             |     |     |     |
| ------ | --- | ---- | ------- | ------------------------------ | ----------- | --- | --- | --- |
| 4.4E+4 |     | 0x2F | 8.5E+5  | )zH( htdiwdnaB retliF ssapdnaB | -40qC, 5.0V |     |     |     |
25qC, 3.3V
| 4.2E+4 |     |     | 8.25E+5 | 1.2E+5 |            |     |     |     |
| ------ | --- | --- | ------- | ------ | ---------- | --- | --- | --- |
| 4E+4   |     |     | 8E+5    |        | 25qC, 5.0V |     |     |     |
125qC, 3.3V
| 3.8E+4    |                |                | 7.75E+5 | 1E+5 |             |     |     |     |
| --------- | -------------- | -------------- | ------- | ---- | ----------- | --- | --- | --- |
| 3.6E+4    |                |                | 7.5E+5  |      | 125qC, 5.0V |     |     |     |
| 3.4E+4    |                |                | 7.25E+5 |      |             |     |     |     |
| 3.2E+4    |                |                | 7E+5    | 8E+4 |             |     |     |     |
| 3E+4      |                |                | 6.75E+5 |      |             |     |     |     |
| 2.8E+4    |                |                | 6.5E+5  | 6E+4 |             |     |     |     |
| 2.6E+4    |                |                | 6.25E+5 |      |             |     |     |     |
| 2.4E+4    |                |                | 6E+5    | 4E+4 |             |     |     |     |
| 2.2E+4    |                |                | 5.75E+5 |      |             |     |     |     |
| 2E+4      |                |                | 5.5E+5  | 2E+4 |             |     |     |     |
| 0x10 0x0E | 0x0C 0x0A 0x08 | 0x06 0x04 0x02 | 0x00    |      |             |     |     |     |
BPF_FC_TRIM Register Value
0
VDD=3.3V
| Temp=25qC |     |     |     | 5E+4 | 1.5E+5 | 2.5E+5 3.5E+5 | 4.5E+5 | 5.5E+5 6.5E+5 |
| --------- | --- | --- | --- | ---- | ------ | ------------- | ------ | ------------- |
LNA_GAIN=0x0; VOUT_SCALE_SEL=0x0
Bandpass Filter Center Frequency (Hz)
| LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0                |     |     |     | LNA_GAIN=0x0  |     |     |     |     |
| -------------------------------------------------------- | --- | --- | --- | ------------- | --- | --- | --- | --- |
| Figure 6-11. Receive Signal Path Bandpass Filter Center  |     |     |     | BPF_Q_SEL=0x0 |     |     |     |     |
LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0
Frequency Trim
Figure 6-12. Receive Signal Path Bandpass Filter Bandwidth for
Various Center Frequency Settings
| 3                |      |     |     | 3   |                |      |      |     |
| ---------------- | ---- | --- | --- | --- | -------------- | ---- | ---- | --- |
| LOGAMP_SLOPE_ADJ |      |     |     |     | LOGAMP_INT_ADJ |      |      |     |
|                  | 0x01 |     |     |     | 0x0F           | 0x00 | 0x07 |     |
| 2.5              |      |     |     | 2.5 |                |      |      |     |
|                  | 0x03 |     |     |     | 0x0C           | 0x03 |      |     |
0x04
| 2                   |            |      |           | 2                   |      |            |      |           |
| ------------------- | ---------- | ---- | --------- | ------------------- | ---- | ---------- | ---- | --------- |
| )V( tuoV            |            |      |           | )V( tuoV            |      |            |      |           |
| 1.5                 |            |      |           | 1.5                 |      |            |      |           |
| 1                   |            |      |           | 1                   |      |            |      |           |
| 0.5                 |            |      |           | 0.5                 |      |            |      |           |
| 0                   |            |      |           | 0                   |      |            |      |           |
| 5E-7                | 1E-5 1E-4  | 1E-3 | 1E-2 1E-1 | 5E-7                | 1E-5 | 1E-4       | 1E-3 | 1E-2 1E-1 |
|                     | VinRMS (V) |      |           |                     |      | VinRMS (V) |      |           |
| VDD:3.3V; Temp:25qC |            |      |           | VDD:3.3V; Temp:25qC |      |            |      |           |
| Fc:256KHz           |            |      |           | Fc:256KHz           |      |            |      |           |
| VOUT_SCALE_SEL=0x0  |            |      |           | VOUT_SCALE_SEL=0x0  |      |            |      |           |
LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0 LOGAMP_DIS_FIRST=0x0; LOGAMP_DIS_LAST=0x0
Figure 6-13. Receive Signal Path Transfer Function for Various  Figure 6-14. Receive Signal Path Transfer Function for Various
|     | Slope Adjustments |     |     |     | Intercept Adjustments |     |     |     |
| --- | ----------------- | --- | --- | --- | --------------------- | --- | --- | --- |
10 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
7 Detailed Description
7.1 Overview
The TUSS4470 is a highly integrated driver and receiver IC designed especially for ultrasonic transducers
operating between the range of 40 KHz to 1 MHz. The TUSS4470 integrates an H-bridge to drive the transducer
directly. This is useful in applications where the receive transducer sensitivity is high and large driving voltage
is not required to create sufficient sound pressure level and where short distance measurements are needed.
The driver stage has flexible and configurable controls set through the SPI interface or through digital input
pins that can be driven by an external MCU. The receive stage consists of a logarithmic amplifier receive
chain. The logamp enables the TUSS4470 to have a wide dynamic input range. This enables applications
where objects with different physical properties must be detected with the same sensor. A key advantage of the
TUSS4470 is that it integrates a bandpass filter that can be tuned to the center frequency of the transducer.
A demodulated analog output representing the receive echo, the zero crossing of the input signal, and a
simple threshold crossing indicator enable a variety of end applications from complex object detection to simple
presence detection.
7.2 Functional Block Diagram
VDD VVPPWWRR VDRV
Control Logic
NCS
SCLK
INTERFACE
SDO
SDI OUTA
OUTB
IO1
IO2 PULSE GENERATOR
Burst Pulses
DGND GND
Output Driver
Echo INT
Threshold
OUT4 Comp
Analog front-end
receiver
VOUT Buffer
Zero Crossing
OUT3 INP
Log
Low Pass Band Pass
Amp & LNA
Filter filter
Demod INN
FLT SGND
7.3 Feature Description
7.3.1 Excitation Power Supply (VDRV)
The TUSS4470 device includes a current source which charges a capacitor connected to the VDRV pin. The
VDRV pin serves as the power supply for the integrated H-Bridge driver circuit The voltage on the VDRV pin
(V ) is controlled by an internal voltage monitor which can be configured by the VDRV_VOLTAGE_LEVEL
VDRV
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 11
Product Folder Links: TUSS4470

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
bits. The current source is switched off after VDRV pin voltage crosses the configured V value. The
VDRV
charging current (I ) can be configured using VDRV_CURRENT_LEVEL bits.
VDRV
In applications where VPWR can vary over a wide range, this allows the transducer drive voltage to be fixed for
every burst for a deterministic sound pressure level created by the transducer. This is possible only when the
minimum supply voltage on the VPWR pin is greater than the configured value of V .
VDRV
The VDRV regulation is disabled at device power up indicated by VDRV_HI_Z bit being set. To enable VDRV
this bit must be cleared. This feature enables applications where the the H-Bridge driver supply is connected to
an external power supply source through the VDRV pin.
Note
• When VDRV pin is supplied from an external power supply, it must be ensured that all times
including during power up, V > V + 0.3 V to prevent any reverse current from VDRV pin
VPWR VDRV
to VPWR pin. Alternatively a reverse current prevention diode can be used on VPWR pin as shown
in Figure 8-1 (D1).
• Very fast ramp-up rate on VPWR pin should be avoided to prevent damage to the device. If fast
ramp rates are possible, a series resistor between power supply and VPWR pin as shown in Figure
8-1 (R ) is recommended.
PWR
After a burst is completed and during the long receive time (listen mode), the capacitor on VDRV pin will
discharge causing the charging current to turn on intermittently. This can inject switching noise which can be
picked by the analog front end as a spurious echo. To eliminate this noise, the DIS_VDRV_REG_LSTN bit can
be set. This disables charging of VDRV automatically after the burst is done. The VDRV charging current can be
turned on again by setting the VDRV_TRIGGER bit. Setting this bit may create a spurious echo which can be
ignored by the echo processing in the MCU. The VDRV_READY bit in DEV_STAT register can be monitored to
know when the required voltage level has been reached and the device is ready to generate a new burst. The
VDRV_TRIGGER bit must be un-set through SPI just before the start of burst and will have to be set again for
next charging cycle. If the VDRV_TRIGGER bit is not un-set before next burst cycle, the VDRV charging current
will not be automatically disabled after the burst even when DIS_VDRV_REG_LSTN is set. This functionality is
ignored when the VDRV_HI_Z bit is set.
7.3.2 Burst Generation
TUSS4470 has multiple modes to excite the transducer through OUTA and OUTB pins. For each of the modes,
the desired frequency of burst is supplied through an external clock on the IOx pins. This enables the user
to supply a highly precise clock calibrated to the center frequency of transducer to enable the highest sound
pressure level generation. These modes can be selected by the IO_MODE bits in the DEV_CTRL_3 register.
The burst mode is enabled first, then the start of burst (OUTA/OUTB changing states) happens at the next falling
edge of IO1 or IO2, depending on the mode selected. These modes are described below.
• IO_MODE = 0: In this mode, the external clock for the transducer is applied at the IO2 pin and the burst
mode is enabled by setting the CMD_TRIGGER in the TOF_CONFIG register through SPI, as shown in
Figure 7-1. The device then expects a clock at IO2 pin to generate pulses on the OUTA/OUTB pins. The
start of burst happens from the first falling edge of IO2. The number of pulses are counted by counting falling
edge to next falling edge transitions on IO2 once the start of burst is triggered. The end of burst sequence is
signaled when the number of pulses defined in BURST_PULSE are sent, or when the CMD_TRIGGER = 0 is
set through SPI, whichever occurs earlier. TI recommends that IO2 is held high before burst enable to count
the number of pulses correctly. After the start of burst, the state of OUTA and OUTB pins are determined by
IO1 and IO2 pins. A transition of CMD_TRIGGER from high to low to high again is required to initiate a new
burst sequence.
12 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
Burst Enable S B ta u r r t s o t f End of Burst Burst Disable
CMD_TRIGGER = 0 CMD_TRIGGER = 1 CMD_TRIGGER = 0
IO2
#1 #2 #3 #4
BURST_PULSE=0x04
Figure 7-1. IO_MODE 0 Description
• IO_MODE = 1: In this mode, the external clock for the transducer is applied at the IO2 pin and the burst
mode is enabled when IO1 pin transitions low (see Figure 7-2). The device then expects a clock at IO2 pin to
generate pulses on the OUTA/OUTB pins. The start of burst happens from the first falling edge of IO2. The
number of pulses are counted by counting falling edge to next falling edge transitions on IO2 once the start of
burst is triggered. End of burst sequence is signaled when the number of pulses defined in BURST_PULSE
are sent or IO1 transitions high, whichever occurs earlier. TI recommends that IO2 is held high before start
of burst to count the number of pulse correctly. After the start of burst, the state of OUTA and OUTB pins are
determined by IO1 and IO2 pins. A transition of IO1 from low to high to low again is required to initiate a new
burst sequence.
Burst Enable S B ta u r r t s o t f End of Burst Burst Disable
IO1
IO2
#1 #2 #3 #4
BURST_PULSE=0x04
Figure 7-2. IO_MODE 1 Description
• IO_MODE = 2: In this mode both IO1 and IO2 are used to control OUTA and OUTB. The burst enable is
triggered when either IO1 or IO2 transitions from high to low. Start of burst (OUTA and OUTB changing state)
happens only at the next falling edge of IO1. Figure 7-3 shows the case where a high-to-low transition on
IO2 is used to enable the burst. A burst is emulated when IO1 and IO2 are toggled in a non-overlapping
sequence. After the start of burst, the state of OUTA and OUTB pins are determined by IO1 and IO2 pins.
During a burst, if there is a condition where both IO1 and IO2 are high for more than half period of the
internal clock f (caused by differential delays due to PCB parasitics or MCU code), an end of burst
INT_CLK
and burst mode disable will be triggered. Any falling edge just after this condition will be ignored to toggle
OUTA and OUTB as it would be considered as a new burst enable signal. A systematic condition of overlap
can cause a continuous end of burst trigger such that OUTA and OUTB do not toggle even though IO1 and
IO2 are toggling. TI recommends no overlap or minimum non-overlap between the IO1 and IO2 signals when
measured at the pins. BURST_PULSE has no effect in this mode.
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 13
Product Folder Links: TUSS4470

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
End of Burst
Burst Enable Start of Non Overlap &
Burst Burst Disable
. . . . . . .
IO1
IO2
Figure 7-3. IO_MODE 2 Description
• IO_MODE = 3: In this mode, burst enable and start of burst are both triggered by the falling edge of IO2. TI
recommends that IO2 pin is kept pulled up to VDD for this mode. The device then expects a clock at IO2 pin
to generate pulses on the OUTA/OUTB pins (see Figure 7-4). The number of pulses are counted by counting
falling edge to next falling edge transitions on IO2 once the start of burst is triggered. End of burst sequence
is signaled when the number of pulses defined in BURST_PULSE are sent. After end of burst, a blank-out
timer interval defined by the DRV_PLS_FLT_DT register is started to prevent triggering of a new start of burst
in the event if the IO2 pin is still toggling. After the start of burst, the state of OUTA and OUTB pins are
determined by IO1 and IO2 pins.
Start of Burst End of Burst
& &
Burst Enable Burst Disable
IO2
#1 #2 #3 #4
BURST_PULSE=0x04 Blank Out Time
Figure 7-4. IO_MODE 3 Description
Note
• For IO_MODE 0 and 1, by setting BURST_PULSE = 0, the device will generate continuous
burst pulses on OUTA and OUTB until the end of burst is signaled through SPI or the IO1 pin,
respectively. Continuous bursting is not available for IO_MODE=3.
• A higher noise floor at the VOUT pin is expected in continuous mode where one transducer is used
to transmit burst signals and another transducer is used to receive, as the switching noise of the
digital IO pins can couple into the highly sensitive analog front end for the receive channel. This
also applies to the single transducer use case where a continuous clock is applied on IO2 pin when
the device is in indirect or listening mode.
• The range for frequency of switching for the output drivers is given by f parameter in the
DRV_CLK
Switching Characteristics table.
• When the device is not in direct sensing or bursting mode, the device is always in indirect sensing
or listening mode.
7.3.2.1 Burst Generation Diagnostics
In IO_MODE 0, 1 and 3, a pulse number diagnostic is active after start of burst (not when the burst is enabled) to
monitor if the correct number of pulses (as set in BURST_PULSE) were generated before the end of burst was
signaled through SPI or the IO1 pin. A fault, if detected, is then reported through the PULSE_NUM_FLT bit.
The pulse duration after start of burst (not when the burst is enabled) is monitored to detect a stuck condition,
which will keep the FETs on OUTA or OUTB turned on. This can happen because of loss of external clock
14 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

or the driving signal on IO1 and IO2 pins being stuck in one state. The device expects to see a toggle on
IOx pins (based on IO_MODE) within the time period as defined in the DRV_PLS_FLT_DT register. If this
diagnostic triggers, it will force an end of burst. The fault is reported by setting the DRV_PULSE_FLT bit. If a
DRV_PULSE_FLT is set in IO_MODE 0, 1 and 3—and the programmed number of pulses were not sent before
end of burst—the PULSE_NUM_FLT will also be set.
Note
• The DRV_PULSE_FLT bit is cleared when a new start of burst is triggered, when
DRV_PLS_FLT_DT = 0x7 is set, or if the device is put into Standby or Sleep mode.
• The PULSE_NUM_FLT bit is cleared when a new start of burst is triggered, or if the device is put
into Standby or Sleep mode.
7.3.3 Direct Transducer Drive
Figure 7-5 shows the internal structure for driving an ultrasonic transducer connected directly to the device
output using an H-bridge output stage. This configuration drives 2 × V as the peak-to-peak voltage across
VDRV
the transducer. The voltage on VDRV pin can be set as described in the Excitation Power Supply (VDRV)
section.
VPWR
OUTA
Burst and Gate
Drive Control
OUTB
ycneuqerF
gnivirD
tnuoC
esluP
gifnoC
evirD
TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
IO2
IVDRV VDRV
+
± VVDRV
Figure 7-5. Direct Drive Configuration Using Internal FETs
Figure 7-5 shows the most common application case for the TUSS4470 device, in which the output driver
pulses the two half-bridges out-of-phase. It is also possible to use the driver in half-bridge mode by setting
the HALF_BRG_MODE bit. In this mode, only V is applied across the transducer. This mode is useful for
VDRV
transducers where one side of the membrane must be always grounded.
The device can also be configured as a pre-driver to drive external FETs or BJTs to drive higher current and
voltage into the primary side of the transformer, as shown in Figure 7-6, by setting the PRE_DRIVER_MODE
bit. The high-side and low-side devices are used to drive the external low-side drivers. The VDRV voltage level
can be configured to ensure that the OUTA and OUTB voltages do not violate the V or V specification for
GS BE
external the FET or BJT, respectively. In the configuration shown in Figure 7-6, it is possible to use a voltage
(VBOOST) which is higher than the supply of the system for generating higher voltage across the transducer.
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 15
Product Folder Links: TUSS4470

Refer to Application and Implementation for an application diagram and information on how the polarity and state
of OUTA and OUTB pins are defined with respect to IO1 and IO2 pin states and other register settings.
VPWR
OUTA
OUTB
Burst and Gate
Drive Control
ycneuqerF
gnivirD
tnuoC
esluP
gifnoC
evirD
IO1/IO2
IVDRV
VDRV VBOOST
+
± VVDRV
Figure 7-6. Center-Tap Transformer Drive Using External FETs
7.3.4 Analog Front End
F. RANGE: BPF_HPF_FREQ
Q: 4; GAIN: 0.9 V/V
INP
GAIN: LNA_GAIN
BPF
VOUT
INN
LNA
DSE
&
SAIB
MC
TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
OUT3
HYS RANGE: ZC_CMP_HYST Thr: ECHO_INT_THR_SEL
OUT4
COMPARATOR COMPARATOR
DYN. RANGE: DRLOG GAIN: LOGAMP_SLOPE_ADJ
F. RANGE: BPF_HPF_FREQ
GAIN: 1V/V LOGAMP BUFFER
FLT
HPF KX: LOGAMP_INT_ADJ
Intercept Correction
Figure 7-7. TUSS4470 Analog Front-End Block Diagram
Figure 7-7 shows the analog front-end block diagram that can receive and condition the signals from the
transducer during listen mode. The received echo is first amplified with a fixed linear low-noise amplifier, followed
16 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
by either a bandpass filter or a high-pass filter to remove noise out of the expected signal band. After filtering the
signal, the signal is fed into a logarithmic amplifier. The output of the logarithmic amplifier is then buffered to the
VOUT pin. In Figure 7-7, every block has the register name associated with it that can be used to configure the
signal path. The final equation for the signal path is given by Equation 2:
) ®) ®8
.0# $2( +0
8
176
=)
8176
®5.
.1)
®20log
10l +06 ®- p
.1) : (1)
where
• G is set by the LOGAMP_SLOPE_ADJ bits.
VOUT
• SL is slope of logarithmic amplifier as specified in the Receiver Characteristics table.
LOG
• G is set by the LNA_GAIN bits.
LNA
• G is typically 0.9V/V.
BPF
• V is the input V
IN INP
• INT is logarithmic amplifier intercept specified in the Receiver Characteristics table.
LOG
• K is the log intercept adjustment set by the LOGAMP_INT_ADJ bits.
X
The bandpass filter is critical for reducing noise to allow utilization of the complete dynamic range of the
logarithmic amplifier. The center frequency of the bandpass filter can be configured to be close the transducer
frequency which is set by the BPF_HPF_FREQ bits. Table 7-1 shows the nominal values for the BPF center
frequency corresponding to the BPF_HPF_FREQ register value. The TUSS4470 supports a wide range of
frequencies, therefore a factory trim is used to remove process variation for a particular pre-determined
frequency. It is possible that all other frequencies listed in Table 7-1 do not correspond exactly to value of
BPF_HPF_FREQ in a factory trim. The user can vary the value of the BPF_HPF_FREQ register around the
desired center frequency while actively bursting and observing the VOUT signal. The value with maximum
voltage at VOUT pin will the desired setting for the BPF_HPF_FREQ register.
Table 7-1. Bandpass Filter Center Frequency Configuration
BPF_HPF_FREQ (HEX)
BPF_F (KHz)
(BPF_FC_TRIM_FRC = 0) c
0x00 40.64
0x01 44.05
0x02 45.6
0x03 48.86
0x04 50.58
0x05 52.96
0x06 56.75
0x07 60.11
0x08 62.95
0x09 66.68
0x0A 71.44
0x0B 74.81
0x0C 79.24
0x0D 82.03
0x0E 86.89
0x0F 92.04
0x10 97.49
0x11 103.27
0x12 109.4
0x13 114.54
0x14 121.33
0x15 128.52
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 17
Product Folder Links: TUSS4470

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
Table 7-1. Bandpass Filter Center Frequency Configuration (continued)
BPF_HPF_FREQ (HEX)
BPF_F (KHz)
(BPF_FC_TRIM_FRC = 0) c
0x16 134.58
0x17 142.55
0x18 151.01
0x19 159.94
0x1A 167.48
0x1B 177.41
0x1C 185.77
0x1D 196.78
0x1E 206.05
0x1F 218.26
0x20 228.54
0x21 244.89
0x22 256.43
0x23 271.63
0x24 284.43
0x25 301.28
0x26 319.13
0x27 338.14
0x28 353.97
0x29 374.95
0x2A 397.16
0x2B 408.17
0x2C 420.7
0x2D 455.63
0x2E 472.03
0x2F 500
The factory trim can be overridden by setting the BPF_FC_TRIM_FRC bit first and varying the BPF_FC_TRIM
bit after. This is useful in two ways:
• If the factory trimmed bandpass filter center frequency is higher than the desired value for BPF_HPF_FREQ
= 0x00, or lower than desired value for BPF_HPF_FREQ = 0x2F, then BPF_FC_TRIM can be used to
recover the range.
• This setting can also be used to extend the frequency range of the bandpass filter center frequency.
The BPF_FC_TRIM acts like an offset on top of the BPF_HPF_FREQ setting. Table 7-2 shows the nominal
value of center frequency when this offset is added to the minimum and maximum BPF_HPF_FREQ code.
Figure 6-11 shows the measured data. For BPF_HPF_FREQ values greater than 0x08 and less than 0x27,
varying BPF_FC_TRIM keeping BPF_HPF_FREQ fixed is the same as setting BPF_FC_TRIM = 0x00 and
varying BPF_HPF_FREQ to find the optimum setting.
Table 7-2. Bandpass Filter Center Frequency Range Extension
BPF_HPF_FREQ (hex) + BPF_FC_TRIM (hex)
BPF_F (KHz)
(BPF_FC_TRIM_FRC = 1) c
0x00 + 0x8 27.48
0x00 + 0x9 29.44
0x00 + 0xA 30.83
0x00 + 0xB 31.19
0x00 + 0xC 32.65
18 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
Table 7-2. Bandpass Filter Center Frequency Range Extension (continued)
BPF_HPF_FREQ (hex) + BPF_FC_TRIM (hex)
BPF_F (KHz)
(BPF_FC_TRIM_FRC = 1) c
0x00 + 0xD 34.19
0x00 + 0xE 35.8
0x00 + 0xF 38.81
0x2F + 0x1 523.56
0x2F + 0x2 554.59
0x2F + 0x3 587.45
0x2F + 0x4 622.23
0x2F + 0x5 651.58
0x2F + 0x6 690.19
0x2F + 0x7 731.09
Note
• The Q factor of the filter is specified in the Receiver Characteristics table, and can be selected by
the BPF_Q_SEL bits.
• The bandpass filter can also be converted into a high-pass filter by setting the BPF_BYPASS bit
for transducer frequencies in the range above what is shown in Table 7-1. The corner frequency for
high-pass filter is also controlled by the BPF_HPF_FREQ bits.
• BPF_Q_SEL and BPF_FC_TRIM have no effect when BPF_BYPASS = 1.
The logamp provides compression for large signal inputs and amplifies linearly small signal inputs. Logamp
simplifies system design to detect varying strengths of echoes that happens because of difference in reflectivity
of different types of objects and objects at different distances. It automatically adjusts its gain based on the input
signal level. The logamp also demodulates the incoming signal.
The logamp consists of multiple gain stages and range extension stages that are combined to give a logarithmic
response. The current consumption of the device can be reduced by turning off the either the first stage, the last
stage of the logamp, or both, by setting the LOGAMP_DIS_FIRST and LOGAMP_DIS_LAST bits. Disabling the
stages will reduce the input dynamic range on the lower side of the range (see Figure 6-4). The pedestal noise
floor will be lower because the gain stages are disabled, but the minimum detectable signal value becomes
higher due to the reduced dynamic range. Depending on the received input signal strength, stages can be
disabled to get optimum object detection. For very small inputs, all stages should be enabled to get maximum
input dynamic range even though the noise floor is higher. Figure 6-6, Figure 6-7, and Figure 6-8 show the effect
on the log conformance error when all stages are enabled, when the last stage is disabled, and when both first
and last stages are disabled. When stages are disabled, a lower error is obtained with a lower noise floor, but the
input dynamic range is reduced.
At the output of the logamp, the user can apply an adjustment to the intercept of the logamp curve. This is
denoted by the K factor in Equation 1. The intercept adjustment is controlled by the LOGAMP_INT_ADJ bits.
X
Table 7-3 shows the nominal values of K factor corresponding to register values, and Figure 6-14 shows its
X
effect on the transfer function.
Table 7-3. Logamp Intercept Adjustment
LOGAMP_INT_ADJ K
X
0x00 1
0x01 1.155
0x02 1.334
0x03 1.54
0x04 1.778
0x05 2.054
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 19
Product Folder Links: TUSS4470

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
Table 7-3. Logamp Intercept Adjustment (continued)
LOGAMP_INT_ADJ K
X
0x06 2.371
0x07 2.738
0x08 1
0x09 0.931
0x0A 0.866
0x0B 0.806
0x0C 0.75
0x0D 0.698
0x0E 0.649
0x0F 0.604
The output of the logamp is filtered using a low-pass filter to remove the high-frequency components and provide
a sufficient peak hold time for the demodulated envelope signal. The cut-off frequency of the low-pass filter is
set by the internal impedance of the FLT pin and the value of an external capacitor connected to the pin. As this
filter capacitance (C ) suppresses the high frequency fluctuations, it also slows down the response time of the
FLT
logamp. Higher C capacitance will result in lower peak-to-peak voltage variations at VOUT, and slower rise
FLT
and fall times for the VOUT voltage to reach its maximum value for a given input signal. A nominal value can be
calculated using Equation 3, and must be optimized depending on the application.
The output of the low-pass filter is buffered to the VOUT pin using an internal buffer. The buffer is designed
to support an ADC input of a MCU. It is possible to change output dynamic range of the VOUT buffer
using the VOUT_SCALE_SEL bit. Once the range is set, the gain of the VOUT buffer can be set by the
LOGAMP_SLOPE_ADJ bits. The slope variation of the receiver analog front end is show in Figure 6-13.
Echo interrupt signal is available on the OUT4 pin that goes high when the signal on the VOUT pin crosses a
threshold as defined by the ECHO_INT_THR_SEL bits. As long as the VOUT signal is higher than this threshold,
the echo interrupt signal is held high. The signal goes low asynchronously when the VOUT signal drops below
the programmed threshold. This signal can be used to interrupt a MCU when an object has been detected. The
threshold value is also dependent on the setting of the VOUT_SCALE_SEL bit.
A zero-crossing signal is output at the OUT3 pin which can be used to validate the frequency of the received
echo signal to provide robustness against interference from other signals. This zero-crossing signal is derived
from the raw amplified input signal from a particular stage as it is being demodulated in the logamp block.
This function is disabled at device power up. but can be enabled by setting the ZC_CMP_EN bit. When
enabled, the ZC_CMP_STG_SEL bits are used to select which logamp gain stage is used to generate the zero
crossing signal while the ZC_CMP_HYST bits control the hysteresis of the zero-crossing comparator. The stage
selection to see the OUT3 pin toggling depends on the strength of signal received by the logamp and has to
be configured depending on the application. For large amplitude of input signal, a lower stage of the logamp
should be selected, whereas for lower amplitude signal, a higher stage should be selected. To avoid switching
noise generated by the toggling of the zero-crossing comparator when the ZC_EN_ECHO_INT bit is set, the
zero-crossing output will be only enabled while the echo interrupt signal is high.
7.4 Device Functional Modes
The device has four functional modes:
Sleep Ultra-low current consumption sleep mode
Mode
In this mode, all major blocks of the device are disabled, including VDRV regulation. The
SPI interface is still active. This transition into and out of this mode is done using the
SLEEP_MODE_EN register bit. Upon issuing a command to exit this mode, the device transitions
to other modes only when the VDRV pin reaches the programmed regulation voltage.
20 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
Standby Low current standby mode
Mode
In this state, the VDRV regulation is active, but other analog blocks are shut down to reduce
quiescent current consumption. The STDBY_MODE_EN bit is used to enter and exit this mode
through SPI. The device can transition very quickly from this state to one of the active states for
bursting and listening.
Listen Default mode of the device
Mode
This is the default mode of the device when it is not in Sleep mode or Standby mode. In this mode,
there is no activity on the transmitter block and the device is actively listening for any ultrasonic
signals.
Burst Mode in which the device is enabled to start a burst to drive the transducer
Mode
In this mode, the transmitter blocks are active and enabled to drive the transducer depending on
when the start of burst occurs. The receiving path is also active at the same time listening for
signals at the input. This mode is entered when a burst enable event occurs and exited when an
end of burst occurs as described in Burst Generation section.
Figure 7-8 shows an example of the transitions between the different modes of the device for IO_MODE = 0,
where the burst is activated through a SPI command and end of burst occurs as the number of programmed
pulses are sent.
CMD_TRIGGER
STDBY_MODE_EN
SLEEP_MODE_EN
DEVICE
MODES
SLEEP STANDBY LISTEN BURST LISTEN BURST
64ms max VDRV in Regulation Burst Enable Burst Disable Burst Enable
Figure 7-8. Device Modes Timing Diagram
Note
• The transition to standby or active mode (listen or burst) from power-up or sleep mode is done only
once the VDRV voltage crosses the programmed VDRV_VOLTAGE_LEVEL bit, or is higher 64 ms,
whichever occurs earlier.
• In the case when VDRV is disabled, the device immediately transitions from power or sleep mode
to standby and active modes.
7.5 Programming
The primary communication between the IC and the external MCU is through an SPI bus that provides full-
duplex communications in a controller-peripheral configuration. The external MCU is always a SPI controller that
sends command requests on the SDI pin and receives device responses on the SDO pin. The device is always
a SPI peripheral device that receives command requests and sends responses to the external MCU over the
SDO line. The following lists the characteristics of the SPI:
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 21
Product Folder Links: TUSS4470

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
• The SPI is a 4-pin interface.
• The frame size is 16 bits and is assigned as follows:
Controller-to-peripheral (MCU to  1 RW bit, 6 bits for the register address, 1 ODD parity bit for entire
| TUSS4470 over the SDI line) |     |     | SPI frame, 8 bits for data |     |     |     |     |     |     |     |     |
| --------------------------- | --- | --- | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
Peripheral-to-controller (TUSS4470  1 bit for Controller Parity error reporting during previous frame
to MCU over the SDO line) reception, 6 bits for the status, 1 bit for ODD parity for entire SPI
frame, 8 bits for data
• SPI commands and data are shifted with the MSB first and the LSB last.
• The SDO line is sampled on the falling edge of the SCLK pin.
• The SDI line is shifted out on the rising edge of the SCLK pin.
The SPI communication begins with the NCS falling edge and ends with the NCS rising edge. The NCS
high-level maintains the SPI peripheral-interface in the RESET state. The SDO output is in the tri-state condition.
The SPI does not support back-to-back SPI frame operation. After each SPI transfer the NCS pin must go from
low to high before the next SPI transfer can begin.
Figure 7-9 shows an overview of a complete 16-bit SPI frame.
15
|     | 14  | 13 12 | 11 10 | 9   | 8   | 7 6 | 5   | 4 3 | 2   | 1   | 0   |
| --- | --- | ----- | ----- | --- | --- | --- | --- | --- | --- | --- | --- |
MSB
NCS
SCLK
SDI ADDR ADDR ADDR ADDR ADDR ADDR C DATA DATA DATA DATA DATA DATA DATA DATA
| R / W | 5   | 4   | 3 2 1 | 0   | PRTY | 7 6 | 5   | 4   | 3 2 | 1   | 0   |
| ----- | --- | --- | ----- | --- | ---- | --- | --- | --- | --- | --- | --- |
SDO
PRTY STAT STAT STAT STAT STAT STAT P DATA DATA DATA DATA DATA DATA DATA DATA
| ERR | 5                                       | 4   | 3 2 1                 | 0   | PRTY                            | 7 6 | 5   | 4   | 3 2 | 1   | 0   |
| --- | --------------------------------------- | --- | --------------------- | --- | ------------------------------- | --- | --- | --- | --- | --- | --- |
|     | Controller/Peripheral SPI Frame Parity  |     | Register Address Bits |     | Controller/Peripheral Data Bits |     |     |     |     |     |     |
Bit
|     | Peripheral Status Bits |     | Read/Write Bit |     |     |     |     |     |     |     |     |
| --- | ---------------------- | --- | -------------- | --- | --- | --- | --- | --- | --- | --- | --- |
Figure 7-9. 16-Bit SPI Frame
Figure 7-10 shows a SPI transfer sequence between the controller and the peripheral TUSS4470 device. When
the controller is writing a SPI frame, the parity error bit indicates if there was a parity error for the previous frame.
When the controller is transmitting the data for the SPI write, the peripheral echoes back register address that
was sent just before in the command.
| SDI |     |     |                  |     |     | C    |     |      |     |     |     |
| --- | --- | --- | ---------------- | --- | --- | ---- | --- | ---- | --- | --- | --- |
|     | W   |     | Register Address |     |     | PRTY |     | DATA |     |     |     |
CONTROLLER WRITE
Peripheral Echo Data
SPI FRAME
SDO
|     | P R T Y |     | Status Bits      |     |     | P W   |     | Register Address |     |     | 0   |
| --- | ------- | --- | ---------------- | --- | --- | ----- | --- | ---------------- | --- | --- | --- |
|     | E R R   |     |                  |     |     | PR TY |     |                  |     |     |     |
| SDI |         |     |                  |     |     | C     |     |                  |     |     |     |
|     | R       |     | Register Address |     |     |       |     | 0x00             |     |     |     |
PRTY
CONTROLLER READ
SPI FRAME
| SDO |         |     |             |     |     | P     |     |      |     |     |     |
| --- | ------- | --- | ----------- | --- | --- | ----- | --- | ---- | --- | --- | --- |
|     | P R T Y |     | Status Bits |     |     |       |     | DATA |     |     |     |
|     | E R R   |     |             |     |     | PR TY |     |      |     |     |     |
Figure 7-10. SPI Transfer Sequence
22 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
The status bits are defined in Table 7-4:
Table 7-4. SPI Interface Status Bits Description
STATUS BIT DESCRIPTION
Set when VDRV power regulator has reached the programmed voltage level. This is also
STAT 5 - VDRV_READY
indicated by VDRV_READY bit.
STAT 4- PULSE_NUM_FLT Set if the burst sequence was terminated before completing the pulse number selected. This
is also indicated by PULSE_NUM_FLT bit.
Set if there is a "stuck" fault detected during pulsing in a burst sequence. This is also
STAT 3 - DRV_PULSE_FLT
indicated by DRV_PULSE_FLT
Set if there is a CRC Error when loading internal EEPROM memory. This is also indicated by
STAT 2 - EE_CRC_FLT
EE_CRC_FLT bit.
Device State:
00 - LISTEN
STAT <1:0> - DEV_STATE 01 - BURST
10 - STANDBY
11 - SLEEP
7.6 Register Maps
This section lists the REG_USER registers that are part of the volatile memory that can be configured by the
MCU at power up or any time during the operation of the device. For register bits that are marked reserved, their
reset value should not be changed.
7.6.1 REG_USER Registers
Table  7-5  lists  the  REG_USER  registers.  All  register  offset  addresses  not  listed  in  Table  7-5  should  be
considered as reserved locations and the register contents should not be modified.
Table 7-5. REG_USER Registers
| Address Acronym      |     | Register Name               |     | Section |
| -------------------- | --- | --------------------------- | --- | ------- |
| 0x10 BPF_CONFIG_1    |     | Bandpass filter settings    |     | Go      |
| 0x11 BPF_CONFIG_2    |     | Bandpass filter settings    |     | Go      |
| 0x12 DEV_CTRL_1      |     | Log-amp configuration       |     | Go      |
| 0x13 DEV_CTRL_2      |     | Log-amp configuration       |     | Go      |
| 0x14 DEV_CTRL_3      |     | Device Configuration        |     | Go      |
| 0x16 VDRV_CTRL       |     | VDRV Regulator Control      |     | Go      |
| 0x17 ECHO_INT_CONFIG |     | Echo Interrupt Control      |     | Go      |
| 0x18 ZC_CONFIG       |     | Zero Crossing configuration |     | Go      |
| 0x1A BURST_PULSE     |     | Burst pulse configuration   |     | Go      |
| 0x1B TOF_CONFIG      |     | Time of Flight Config       |     | Go      |
| 0x1C DEV_STAT        |     | Fault status bits           |     | Go      |
| 0x1D DEVICE_ID       |     | Device ID                   |     | Go      |
| 0x1E REV_ID          |     | Revision ID                 |     | Go      |
Complex bit access types are encoded to fit into small table cells. Table 7-6 shows the codes that are used for
access types in this section.
Table 7-6. REG_USER Access Type Codes
|     | Access Type | Code | Description |     |
| --- | ----------- | ---- | ----------- | --- |
Read Type
|     | R   | R   | Read |     |
| --- | --- | --- | ---- | --- |
Write Type
|     | W   | W   | Write |     |
| --- | --- | --- | ----- | --- |
Reset or Default Value
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 23
Product Folder Links: TUSS4470

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
Table 7-6. REG_USER Access Type Codes
(continued)
Access Type Code Description
-n Value after reset or the default
value
7.6.1.1 BPF_CONFIG_1 Register (Address = 0x10) [reset = 0x0]
BPF_CONFIG_1 is shown in Table 7-7.
Return to the Summary Table.
Table 7-7. BPF_CONFIG_1 Register Field Descriptions
Bit Field Type Reset Description
7 BPF_FC_TRIM_FRC R/W 0x0 Override factor settings for Bandpass filter trim and control via
BPF_FC_TRIM register. Valid only when BPF_BYPASS = 0
0x0 = Factory trim
0x1 = Override Factory trim
6 BPF_BYPASS R/W 0x0 Select between Bandpass filter or high pass filter
0x0 = BPF Enabled
0x1 = HPF Enabled (BPF Bypass)
5:0 BPF_HPF_FREQ R/W 0x0 If BPF_BYPASS = 0:
Band pass filter center frequency. See "Bandpass filter center
frequency configuration" table
If BPF_BYPASS = 1:
High pass filter corner frequency
0x00 - 0x0F - 200kHz
0x10 - 0x1F - 400kHz
0x20 - 0x2F - 50kHz
0x30 - 0x3F - 100kHz
7.6.1.2 BPF_CONFIG_2 Register (Address = 0x11) [reset = 0x0]
BPF_CONFIG_2 is shown in Table 7-8.
Return to the Summary Table.
Table 7-8. BPF_CONFIG_2 Register Field Descriptions
Bit Field Type Reset Description
7:6 RESERVED R 0x0 Reserved
5:4 BPF_Q_SEL R/W 0x0 Bandpass filter Q factor. Valid only when BPF_BYPASS = 0
0x0 = 4
0x1 = 5
0x2 = 2
0x3 = 3
3:0 BPF_FC_TRIM R/W 0x0 Offset BPF_HPF_FREQ when BPF_FC_TRIM_FRC = 1:
BPF_HPF_FREQ = BPF_HPF_FREQ + BPF_FC_TRIM
See "Bandpass filter center frequency range extension" table.
7.6.1.3 DEV_CTRL_1 Register (Address = 0x12) [reset = 0x0]
DEV_CTRL_1 is shown in Table 7-9.
Return to the Summary Table.
24 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
Table 7-9. DEV_CTRL_1 Register Field Descriptions
Bit Field Type Reset Description
7 LOGAMP_FRC R/W 0x0 Override for factory settings for LOGAMP_SLOPE_ADJ and
LOGAMP_INT_ADJ
6:4 LOGAMP_SLOPE_ADJ R/W 0x0 Slope or gain adjustment at the final output on VOUT pin. Slope
adjustment depends on the setting of VOUT_SCALE_SEL.
0x0 = 3.0× VOUT_SCALE_SEL+4.56×VOUT_SCALE_SEL V/V
0x1 = 3.1× VOUT_SCALE_SEL+4.71×VOUT_SCALE_SEL V/V
0x2 = 3.2× VOUT_SCALE_SEL+4.86×VOUT_SCALE_SEL V/V
0x3 = 3.3× VOUT_SCALE_SEL+5.01×VOUT_SCALE_SEL V/V
0x4 = 2.6× VOUT_SCALE_SEL+3.94×VOUT_SCALE_SEL V/V
0x5 = 2.7× VOUT_SCALE_SEL+ 4.10×VOUT_SCALE_SEL V/V
0x6 = 2.8× VOUT_SCALE_SEL+4.25×VOUT_SCALE_SEL V/V
0x7 = 2.9× VOUT_SCALE_SEL+4.4×VOUT_SCALE_SEL V/V
3:0 LOGAMP_INT_ADJ R/W 0x0 Logamp Intercept adjustment. See "Logamp intercept adjustment"
table in specification for values.
7.6.1.4 DEV_CTRL_2 Register (Address = 0x13) [reset = 0x0]
DEV_CTRL_2 is shown in Table 7-10.
Return to the Summary Table.
Table 7-10. DEV_CTRL_2 Register Field Descriptions
Bit Field Type Reset Description
7 LOGAMP_DIS_FIRST R/W 0x0 Disable first logamp stage to reduce quiescent current
6 LOGAMP_DIS_LAST R/W 0x0 Disable last logamp stage quiescent current
3 RESERVED R 0x0 Reserved
2 VOUT_SCALE_SEL R/W 0x0 Select VOUT scaling
0x0 = Select Vout gain to map output to 3.3 V
0x1 = Select Vout gain to map output to 5.0 V
1:0 LNA_GAIN R/W 0x0 Adjust LNA Gain in V/V
0x0 = 15 V/V
0x1 = 10 V/V
0x2 = 20 V/V
0x3 = 12.5 V/V
7.6.1.5 DEV_CTRL_3 Register (Address = 0x14) [reset = 0x0]
DEV_CTRL_3 is shown in Table 7-11.
Return to the Summary Table.
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 25
Product Folder Links: TUSS4470

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
Table 7-11. DEV_CTRL_3 Register Field Descriptions
Bit Field Type Reset Description
4:2 DRV_PLS_FLT_DT R/W 0x0 Driver Pulse Fault Deglitch Time.
In IO_MODE = 0 or IO_MODE = 1, DRV_PULSE_FLT will be set if
start of burst is triggered and IO2 pin has not toggled for greater than
deglitch Time.
In IO_MODE = 2, DRV_PULSE_FLT will be set if start of burst is
triggered and if IO1 or IO2 do not toggle a period longer than the
deglitch time except when both pins are high.
0x0 = 64 µs
0x1 = 48 µs
0x2 = 32 µs
0x3 = 24 µs
0x4 = 16 µs
0x5 = 8 µs
0x6 = 4 µs
0x7 = Check Disabled
1:0 IO_MODE R/W 0x0 Configuration for low voltage IO pins.
0x0 = IOMODE 0
0x1 = IOMODE 1
0x2 = IOMODE 2
0x3 = IOMODE 3
7.6.1.6 VDRV_CTRL Register (Address = 0x16) [reset = 0x20]
VDRV_CTRL is shown in Table 7-12.
Return to the Summary Table.
Table 7-12. VDRV_CTRL Register Field Descriptions
Bit Field Type Reset Description
7 RESERVED R 0x0 Reserved
6 DIS_VDRV_REG_LSTN R/W 0x0 Automatically disable VDRV charging in listen mode every time after
burst mode is exited given VDRV_TRIGGER =0x0.
0x0 = Do not automatically disable VDRV charging
0x1 = Automatically disable VDRV charging
5 VDRV_HI_Z R/W 0x1 Turn off current source between VPWR and VRDV and disable
VDRV regulation.
0x0 = VDRV not Hi-Z
0x1 = VDRV in Hi-Z mode
4 VDRV_CURRENT_LEVEL R/W 0x0 Pull up current at VDRV pin
0x0 = 10 mA
0x1 = 20 mA
3:0 VDRV_VOLTAGE_LEVEL R/W 0x0 Regulated Voltage at VDRV pin Value is calculated as :
VDRV = VDRV_VOLTAGE_LEVEL + 5 [V]
7.6.1.7 ECHO_INT_CONFIG Register (Address = 0x17) [reset = 0x7]
ECHO_INT_CONFIG is shown in Table 7-13.
Return to the Summary Table.
Table 7-13. ECHO_INT_CONFIG Register Field Descriptions
Bit Field Type Reset Description
7:5 RESERVED R 0x0 Reserved
4 ECHO_INT_CMP_EN R/W 0x0 Enable echo interrupt comparator output
26 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
Table 7-13. ECHO_INT_CONFIG Register Field Descriptions (continued)
Bit Field Type Reset Description
3:0 ECHO_INT_THR_SEL R/W 0x7 Threshold level to issue interrupt on OUT4 pin. Applied to Low pass
filter output.
If VOUT_SCALE_SEL=0x0 :
Threshold = 0.04 x ECHO_INT_THR_SEL + 0.4 [V]
If VOUT_SCALE_SEL=0x1:
Threshold = 0.06 x ECHO_INT_THR_SEL + 0.6 [V]
7.6.1.8 ZC_CONFIG Register (Address = 0x18) [reset = 0x14]
ZC_CONFIG is shown in Table 7-14.
Return to the Summary Table.
Table 7-14. ZC_CONFIG Register Field Descriptions
Bit Field Type Reset Description
7 ZC_CMP_EN R/W 0x0 Enable Zero Cross Comparator for Frequency detection
6 ZC_EN_ECHO_INT R/W 0x0 When set, provides ZC information only when object is detected
5 ZC_CMP_IN_SEL R/W 0x0 Zero Comparator Input Select
0x0 = INP - VCM
0x1 = INP - INN
4:3 ZC_CMP_STG_SEL R/W 0x2 Zero Cross Comparator Stage Select
2:0 ZC_CMP_HYST R/W 0x4 Zero Cross Comparator Hysteresis Selection
0x0 = 30 mV
0x1 = 80 mV
0x2 = 130 mV
0x3 = 180 mV
0x4 = 230 mV
0x5 = 280 mV
0x6 = 330 mV
0x7 = 380 mV
7.6.1.9 BURST_PULSE Register (Address = 0x1A) [reset = 0x0]
BURST_PULSE is shown in Table 7-15.
Return to the Summary Table.
Table 7-15. BURST_PULSE Register Field Descriptions
Bit Field Type Reset Description
7 HALF_BRG_MODE R/W 0x0 Use output driver in half-bridge mode.
When enabled, drive both high-side FET together and low-side FETs
together.
0x0 = Disable half-bridge mode
0x1 = Enable half bridge mode
6 PRE_DRIVER_MODE R/W 0x0 Pre-driver mode to drive external FETs
0x0 = Disable pre-driver mode
0x1 = Enable pre-driver mode
5:0 BURST_PULSE R/W 0x0 Number of burst pulses. REG_VALUE=0x00 enables continuous
burst mode
7.6.1.10 TOF_CONFIG Register (Address = 0x1B) [reset = 0x0]
TOF_CONFIG is shown in Table 7-16.
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 27
Product Folder Links: TUSS4470

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
Return to the Summary Table.
Table 7-16. TOF_CONFIG Register Field Descriptions
| Bit Field       | Type Reset | Description                        |
| --------------- | ---------- | ---------------------------------- |
| 7 SLEEP_MODE_EN | R/W 0x0    | For entering or exiting sleep mode |
0x0 = Wake up or exit Sleep Mode
0x1 = Enter sleep mode
| 6 STDBY_MODE_EN | R/W 0x0 | For entering or exiting standby mode |
| --------------- | ------- | ------------------------------------ |
0x0 = Exit Standby Mode
0x1 = Enter Standby mode
| 5:2 RESERVED | R 0x0 | Reserved |
| ------------ | ----- | -------- |
1 VDRV_TRIGGER R/W 0x0 Control charging of VDRV pin when DIS_VDRV_REG_LSTN = 1.
This has no effect when VDRV_HI_Z=0x1.
0x0 = Disable I
VDRV
0x1 = Enable I
VDRV
0 CMD_TRIGGER R/W 0x0 For IO_MODE=0x0, control enabling of burst mode. Ignored for other
IO_MODE values.
0x0 = Disable burst mode
0x1 = Enable burst mode
7.6.1.11 DEV_STAT Register (Address = 0x1C) [reset = 0x0]
DEV_STAT is shown in Table 7-17.
Return to the Summary Table.
Table 7-17. DEV_STAT Register Field Descriptions
| Bit Field    | Type Reset | Description             |
| ------------ | ---------- | ----------------------- |
| 7:4 RESERVED | R 0x0      | Reserved                |
| 3 VDRV_READY | R 0x0      | VDRV pin voltage status |
0x0 = VDRV is below configured voltage
0x1 = VDRV is equal or above configured voltage
2 PULSE_NUM_FLT R 0x0 The Driver has not received the number of pulses defined by
BURST_PULSE
1 DRV_PULSE_FLT R 0x0 The Driver has been stuck in a single state in burst mode for a period
longer than delgitch time set by DRV_PLS_FLT_DT
| 0 EE_CRC_FLT | R 0x0 | CRC error for internal memory |
| ------------ | ----- | ----------------------------- |
7.6.1.12 DEVICE_ID Register (Address = 0x1D) [reset = X]
DEVICE_ID is shown in Table 7-18.
Return to the Summary Table.
Table 7-18. DEVICE_ID Register Field Descriptions
| Bit Field     | Type Reset | Description     |
| ------------- | ---------- | --------------- |
| 7:0 DEVICE_ID | R X        | Device ID: 0xB9 |
7.6.1.13 REV_ID Register (Address = 0x1E) [reset = 0x2]
REV_ID is shown in Table 7-19.
Return to the Summary Table.
28 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
Table 7-19. REV_ID Register Field Descriptions
| Bit Field  | Type Reset | Description |
| ---------- | ---------- | ----------- |
| 7:0 REV_ID | R 0x2      | Revision ID |
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 29
Product Folder Links: TUSS4470

8 Application and Implementation
Note
Information in the following applications sections is not part of the TI component specification,
and TI does not warrant its accuracy or completeness. TI’s customers are responsible for
determining suitability of components for their purposes, as well as validating and testing their design
implementation to confirm system functionality.
8.1 Application Information
The TUSS4470 device must be paired with an external ultrasonic transducer. The TUSS4470 device drives
the transducer to generate an ultrasonic echo and applies logarithmic gain scaling to the received echo signal
in the analog front end. The transducer should be chosen based on the resonant frequency, input voltage
requirements, sensitivity, beam pattern, and decay time. The TUSS4470 device is flexible enough to meet most
transducer requirements by adjusting the driving frequency, driving current limit, and center frequency of the
band-pass filter. The only available interface to configure the device registers is SPI. During the burst-and-listen
cycles, an external ADC or analog receiver should be used to capture the echo envelope from the VOUT pin to
compute time of flight (ToF), distance, amplitude, and/or width of the return echo.
8.2 Typical Application
>
C
PWR1
DNG DNGS
OUTA
OUTB
VDD
VPWR
MCU
VDRV
C INP INP
C INN INN DNGD
TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
D R
1 PWR
VIN
IO2
GPIO IO1
GPIO OUT3
GPIO OUT4
NCS FLT
C
SDO PWR2
C
SPI FLT
SDI
SSCCLLKK R INP
VOUT
ADC
LDO
C
VDD
Figure 8-1. TUSS4470 Application Diagram
30 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
| www.ti.com |     |     | SLDS251A – DECEMBER 2019 – REVISED MAY 2022 |     |
| ---------- | --- | --- | ------------------------------------------- | --- |
Table 8-1. Recommended Component Values for Typical Applications
| DESIGNATOR | VALUE | COMMENT |     |     |
| ---------- | ----- | ------- | --- | --- |
Optional (to limit fast voltage transient on VPWR pin during power
| R   | 10 Ω |     |     |     |
| --- | ---- | --- | --- | --- |
| PWR |      | up) |     |     |
R 200Ω (1/4 Watt) Optional higher value for EMI/ESD robustness
(INP)
| C PWR1 | 50V, 100nF |     |     |     |
| ------ | ---------- | --- | --- | --- |
| C PWR2 | 40V, 2µF   |     |     |     |
| C      | >5V, 10nF  |     |     |     |
VDD
| C   | 40V, 330pF |     |     |     |
| --- | ---------- | --- | --- | --- |
INP
|     |     | Use equation below to estimate value of C |     |  depending on the burst  |
| --- | --- | ----------------------------------------- | --- | ------------------------ |
INN
frequency
1
| C   | >5V, C | % =      |         |     |
| --- | ------ | -------- | ------- | --- |
| INN | INN    | +00      | B       |     |
|     |        | 2®è®150® | &48_%.- |     |
|     |        |          | l 4     | p   |
(2)
|     |     | Use equation below to estimate value of C |     | FLT  depending on the burst  |
| --- | --- | ----------------------------------------- | --- | ---------------------------- |
frequency . Value has to be optimized for application depending on
noise and response time requirements.
| C   | 5V, C |                  | 25  |     |
| --- | ----- | ---------------- | --- | --- |
| FLT | FLT   |                  |     |     |
|     |       | % =              |     |     |
|     |       | (.6 2®è® k6250®B |     |     |
o
&48_%.- (3)
D1 1N4001 or equivalent Optional for reverse supply and reverse current protection.
Example devices for low-frequency range:
Closed top: 40 kHz: PUI Audio UTR-1440K-TT-R
XDCR (transducer) Open top: muRata MA40H1S-R, SensComp 40LPT16, Kobitone
255-400PT160-ROX
Example devices for high-frequency range:
Closed top: 300 kHz: Murata MA300D1-1
8.2.1 Transducer Drive Configuration Options
For different transducer drive configurations, the TUSS4470 supports multiple configurations to accommodate
specific system needs as shown in Figure 8-2. The typical application diagram in Figure 8-1 is considered as
"Case 1".
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 31
Product Folder Links: TUSS4470

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
|     | HALF_BRG_MODE = 0 |     |      | HALF_BRG_MODE = 1 |     |
| --- | ----------------- | --- | ---- | ----------------- | --- |
|     | VPWR              |     | VPWR |                   |     |
|     | VDRV              |     | VDRV |                   |     |
OUTA
OUTA
|     | OUTB |           | OUTB |           |     |
| --- | ---- | --------- | ---- | --------- | --- |
|     |      | 1         |      |           | 2   |
|     | VPWR | VPWR/VEXT | VPWR | VPWR/VEXT |     |
|     | VDRV |           | VDRV |           |     |
|     | OUTA |           | OUTA |           |     |
|     | OUTB |           | OUTB |           |     |
|     |      | 3         |      |           | 4   |
Figure 8-2. TUSS4470 Transducer Drive Options
The behavior of the internal FETs in the TUSS4470 device is different for each configuration in Figure 8-2. Table
8-2 and Table 8-3 shows the relationship between the IOx pins and the state of the OUTA and OUTB pins for
different register settings.
Table 8-2. OUTA / OUTB Pin Behavior for Different Drive Configurations in IO MODE 2
IO MODE 2
PRE_DRI
| START OF  | HALF_BRG_M |         |      |       |                  |
| --------- | ---------- | ------- | ---- | ----- | ---------------- |
|           | VER_MO     | IO1 IO2 | OUTA | OUTB  | APPLICATION CASE |
| BURST     | DE ODE     |         |      |       |                  |
|           | 0 0        | 0 0     | GND  | GND   |                  |
| YES       | 0 0        | 0 1     | GND  | VVDRV |                  |
CASE 1
|     | 0 0 | 1 0 | VVDRV | GND   |     |
| --- | --- | --- | ----- | ----- | --- |
| NO  | 0 0 | 1 1 | Hi-Z  | GND   |     |
|     | 0 1 | 0 0 | Hi-Z  | Hi-Z  |     |
| YES | 0 1 | 0 1 | VVDRV | VVDRV |     |
CASE 2
|     | 0 1 | 1 0 | GND  | GND   |     |
| --- | --- | --- | ---- | ----- | --- |
| NO  | 0 1 | 1 1 | Hi-Z | Hi-Z  |     |
|     | 1 0 | 0 0 | GND  | GND   |     |
| YES | 1 0 | 0 1 | GND  | VVDRV |     |
CASE 3
|     | 1 0 | 1 0 | VVDRV | GND   |     |
| --- | --- | --- | ----- | ----- | --- |
| NO  | 1 0 | 1 1 | GND   | GND   |     |
|     | 1 1 | 0 0 | GND   | GND   |     |
| YES | 1 1 | 0 1 | VVDRV | VVDRV |     |
CASE 4
|     | 1 1 | 1 0 | GND | GND |     |
| --- | --- | --- | --- | --- | --- |
| NO  | 1 1 | 1 1 | GND | GND |     |
32 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
| www.ti.com |     |     |     | SLDS251A – DECEMBER 2019 – REVISED MAY 2022 |     |
| ---------- | --- | --- | --- | ------------------------------------------- | --- |
Table 8-3. OUTA / OUTB Pin Behavior for Different Drive Configurations in IO MODE 0, IO MODE 1 and IO
MODE 3
IO MODE 0, IO MODE 1, IO MODE 3
CMD_TRIG
|           | PRE_DRI    | IO1       |          |      |                  |
| --------- | ---------- | --------- | -------- | ---- | ---------------- |
| START OF  | HALF_BRG_M | GER       |          |      |                  |
|           | VER_MO     | (IO MODE  | IO2 OUTA | OUTB | APPLICATION CASE |
| BURST     | ODE        | (IO MODE  |          |      |                  |
|           | DE         | 0) 1)     |          |      |                  |
|           | 0 0        | 0 1       | 0        |      |                  |
| NO        |            |           | Hi-Z     | GND  |                  |
|           | 0 0        | 0 1       | 1        |      |                  |
CASE 1
|     | 0 0 | 1 0 | 0 GND | VVDRV |     |
| --- | --- | --- | ----- | ----- | --- |
YES
|     | 0 0 | 1 0 | 1 VVDRV | GND  |     |
| --- | --- | --- | ------- | ---- | --- |
|     | 0 1 | 0 1 | 0       |      |     |
| NO  |     |     | Hi-Z    | Hi-Z |     |
|     | 0 1 | 0 1 | 1       |      |     |
CASE 2
|     | 0 1 | 1 0 | 0 GND | GND |     |
| --- | --- | --- | ----- | --- | --- |
YES
|     | 0 1 | 1 0 | 1 VVDRV | VVDRV |     |
| --- | --- | --- | ------- | ----- | --- |
|     | 1 0 | 0 1 | 0       |       |     |
| NO  |     |     | GND     | GND   |     |
|     | 1 0 | 0 1 | 1       |       |     |
CASE 3
|     | 1 0 | 1 0 | 0 GND | VVDRV |     |
| --- | --- | --- | ----- | ----- | --- |
YES
|     | 1 0 | 1 0 | 1 VVDRV | GND |     |
| --- | --- | --- | ------- | --- | --- |
|     | 1 1 | 0 1 | 0       |     |     |
| NO  |     |     | GND     | GND |     |
|     | 1 1 | 0 1 | 1       |     |     |
CASE 4
|     | 1 1 | 1 0 | 0 GND | GND |     |
| --- | --- | --- | ----- | --- | --- |
YES
|     | 1 1 | 1 0 | 1 VVDRV | VVDRV |     |
| --- | --- | --- | ------- | ----- | --- |
8.2.1.1 Design Requirements
For this design example, use the parameters listed in Table 8-4 as the input and operating parameters. All other
device settings can be assumed to be factory default.
Table 8-4. Design Parameters
|     | DESIGN PARAMETER           |     |     | EXAMPLE VALUE      |     |
| --- | -------------------------- | --- | --- | ------------------ | --- |
|     | Input voltage range        |     |     | 5 to 36 V          |     |
|     | Input voltage recommended  |     |     | 5 V or 20 V        |     |
|     | Transducer driving voltage |     |     | 5 V AC  or 20 V AC |     |
|     | Transducer frequency       |     |     | 40 kHz or 400 kHz  |     |
Transducer pulse count 16
8.2.1.2 Detailed Design Procedure
To begin the design process, determine the following:
• Transducer
– Transducer driving voltage
– Transducer resonant frequency
– Transducer pulse count maximum
8.2.1.2.1 Transducer Driving Voltage
When a voltage is applied to piezoelectric ceramics, mechanical distortion is generated according to the voltage
and frequency. The mechanical distortion is measured in units of sound pressure level (SPL) to indicate the
volume of sound, and can be derived from a free-field microphone voltage measurement using Equation 4.
|     | § V | ·   |     |     |     |
| --- | --- | --- | --- | --- | --- |
(MIC)
|     | ¨   | ¸   |     |     |     |
| --- | --- | --- | --- | --- | --- |
©3.4mV¹
SPL(db) 20ulog
P O (4)
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 33
Product Folder Links: TUSS4470

where
• V is the measured sensor sound pressure (mV ).
(MIC) RMS
• P is a referenced sound pressure of 20 μPa.
O
The SPL does not increase indefinitely with the driving voltage. After a particular driving voltage, the amount
of SPL that a transducer can generate becomes saturated. A transducer is given a maximum driving voltage
specification to indicate when the maximum SPL is generated. Driving the transducer beyond the maximum
driving voltage makes the ultrasonic module less power-efficient and can damage or decrease the life
expectancy of the transducer.
8.2.1.2.2 Transducer Driving Frequency
The strength of ultrasonic waves propagated into the air attenuate proportionally with distance. This attenuation
is caused by diffusion, diffraction, and absorption loss as the ultrasonic energy transmits through the medium of
air. As shown in Figure 8-3, the higher the frequency of the ultrasonic wave, the larger the attenuation rate and
the shorter the distance the wave reaches.
Distance (m)
)Bd(
noitaunettA
TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
0
-10
-20
-30
-40
-50
-60
-70
200 kHz
-80
80 kHz
-90 40 kHz
20 kHz
-100
0.1 1 10
D008
Figure 8-3. Attenuation Characteristics of Sound Pressure by Distance
An ultrasonic transducer has a fixed resonant center frequency with a typical tolerance of ±2%. The lower
frequency range of 30 kHz to 100 kHz is the default operating range for common long range applications for a
step resolution of 1 cm and typical range of 30 cm to 5 m. The upper frequency range of 100 kHz to 1000 kHz is
reserved for high-precision applications with a step resolution of 1 mm and a typical range of 5 cm to 1 m.
8.2.1.2.3 Transducer Pulse Count
The pulse count determines how many alternating periods are applied to the transducer by the complementary
low-side drivers and determines the total width of the ultrasonic ping that was transmitted. The larger the width
of the transmitted ping, the larger the width of the returned echo signature of the reflected surface and the more
resolution available to set a stable threshold. A disadvantage of a large pulse count is a large ringing-decay
period, which limits how detectable objects are at short distances.
Select a pulse count based on the minimum object distance requirement. If short-distance object detection is not
a priority, a high pulse count is not a concern. Certain transducers can be driven continuously while others have
a limit to the maximum driving-pulse count. Refer to the specification for the selected transducer to determine if
the pulse count must be limited.
34 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
| www.ti.com |     |     |     | SLDS251A – DECEMBER 2019 – REVISED MAY 2022 |     |     |     |
| ---------- | --- | --- | --- | ------------------------------------------- | --- | --- | --- |
8.2.1.3 Application Curves
Figure 8-4 and Figure 8-5 show the typical ranging performance of a 40-kHz, closed-top transducer under
nominal operating conditions as indicated in Table 8-4. The targeted object is a PVC pole measuring 1000
mm in height and 75 mm in diameter. Notable device settings: LNA_GAIN = 0x0; VOUT_SCALE_SEL = 0x0;
LOGAMP_DIS_FIRST = 0x0; LOGAMP_DIS_LAST = 0x1.
| 3   |     |     |     | 3   |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- |
|     |     |     | 1m  |     |     |     | 1m  |
|     |     |     | 2m  |     |     |     | 2m  |
| 2.5 |     |     |     | 2.5 |     |     |     |
|     |     |     | 3m  |     |     |     | 3m  |
|     |     |     | 4m  |     |     |     | 4m  |
5m
| 2   |     |     |     | 2   |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- |
6m
| )V( TUOV |           |       |     | )V( TUOV |           |       |     |
| -------- | --------- | ----- | --- | -------- | --------- | ----- | --- |
| 1.5      |           |       |     | 1.5      |           |       |     |
| 1        |           |       |     | 1        |           |       |     |
| 0.5      |           |       |     | 0.5      |           |       |     |
| 0        |           |       |     | 0        |           |       |     |
| 0 6      | 12 18     | 24 30 | 36  | 0 6      | 12 18     | 24 30 | 36  |
|          | Time (ms) |       |     |          | Time (ms) |       |     |
Figure 8-4. TUSS4470 40 kHz Ranging at 5-V Driver  Figure 8-5. TUSS4470 40 kHz Ranging at 20-V
With Last Log-Amp Stage Disabled Driver With Last Log-Amp Stage Disabled
Figure 8-6 and Figure 8-7 show the typical ranging performance of a 400-kHz, closed-top transducer under
nominal operating conditions as indicated in Table 8-4. The targeted object is an aluminum pole measuring 100
mm in height and 10 mm in diameter. Notable device settings: LNA_GAIN = 0x0; VOUT_SCALE_SEL = 0x0;
LOGAMP_DIS_FIRST = 0x0; LOGAMP_DIS_LAST = 0x0.
| 3        |           |       |     | 3        |           |       |     |
| -------- | --------- | ----- | --- | -------- | --------- | ----- | --- |
|          |           | 50mm  |     |          |           | 50mm  |     |
|          |           | 100mm |     |          |           | 100mm |     |
| 2.5      |           | 200mm |     | 2.5      |           | 200mm |     |
|          |           | 300mm |     |          |           | 300mm |     |
|          |           | 400mm |     |          |           | 400mm |     |
| 2        |           |       |     | 2        |           |       |     |
| )V( TUOV |           |       |     | )V( TUOV |           |       |     |
| 1.5      |           |       |     | 1.5      |           |       |     |
| 1        |           |       |     | 1        |           |       |     |
| 0.5      |           |       |     | 0.5      |           |       |     |
| 0        |           |       |     | 0        |           |       |     |
| 0 0.5    | 1 1.5     | 2 2.5 | 3   | 0 0.5    | 1 1.5     | 2 2.5 | 3   |
|          | Time (ms) |       |     |          | Time (ms) |       |     |
Figure 8-6. TUSS4470 400 kHz Ranging at 5-V Drive Figure 8-7. TUSS4470 400 kHz Ranging at 20-V
Driver
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 35
Product Folder Links: TUSS4470

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
9 Power Supply Recommendations
The TUSS4470 device is designed to operate from two independent supplies, a driver supply and a regulated
supply.
The driver input voltage supply (VPWR) range can operate from 5 V to 36 V. In applications where the
TUSS4470 device may be exposed to battery transients and reverse battery currents, use external component-
safeguards, such as component D1 or parallel TVS diodes, to help protect the device. If the input supply is
placed more than a few inches from the TUSS4470 device, additional bulk capacitance may be required in
addition to the ceramic bypass capacitors near the VPWR pin. In the event both the VDRV and pre-driver modes
is enabled, limit the VPWR voltage to the maximum rated voltage of the externally driven transistor’s gate-source
or base-emitter rating. The electrolytic capacitor at the VDRV pin is intended to act as a fast discharge capacitor
during the bursting stage of the TUSS4470 device. The H-bridge high-side voltage can be supplied with an
independent voltage at the VDRV pin to isolate the driver from VPWR, but must remain within the specified
maximum voltage rating of the VDRV, OUTA, and OUTB outputs. If the H-bridge high-side voltage is to be
supplied by an independent source, VDRV should be disabled.
The regulated supply (VDD) is used as the supply reference for the analog front end, filtering, and analog
output blocks, so this supply should be stable for maximum performance. TI recommends using an LDO or other
regulated external power source with bypass capacitor placed closely to the VDD pin. As VDD becomes less
stable, the noise floor of the VOUT signal will increase, and result in a loss of long range object detection as a
consequence.
To prevent damage to the device, always avoid hot-plugging or providing instantaneous power at the VPWR
and VDRV pins at start-up, unless these pins are properly protected with an RC filter or TVS diode to minimize
transient effects. VPWR must always be equal to or greater than the value present at VDRV.
36 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
10 Layout
10.1 Layout Guidelines
A minimum of two layers is required to accomplish a small-form factor ultrasonic module design. The layers
should be separated by analog and digital signals. The pin map of the device is routed such that the power
and digital signals are on the opposing side of the analog driver and receiver pins. Consider the following best
practices for TUSS4470 device layout in order of descending priority:
• Separating the grounding types is important to reduce noise at the AFE input of the TUSS4470. In particular,
the transducer sensor ground, supporting driver, and return-path circuitry should have a separate ground
before being connected to the main ground. Separating the sensor and main grounds through a ferrite bead
is best practice, but not require. A copper-trace or 0-Ω short is also acceptable when bridging grounds.
• The analog return path pins, INP and INN, are most susceptible to noise and therefore should be routed as
short and directly to the transducer as possible. Ensure the INN capacitor is close to the pin to reduce the
length of the ground wire.
• The analog output pin trace should be routed as short and directly to an external ADC or microcontroller input
to avoid signal-to-noise losses due to parasitic-effects or noise coupling onto the trace from external radiating
aggressors.
• In applications where protection from an ESD strike on the case of the transducer is important, ground routing
of the capacitor on the INN pin should be separate from the device ground and connected directly with the
shortest possible trace to the connector ground.
• The analog drive pins can be high-current, high-voltage, or both and therefore the design limitation of the
OUTA and OUTB pins is based on the copper trace profile. The driver pins are recommended to be as short
and direct as possible when driving a transducer with a high-voltage.
• The decoupling capacitors for the VDD and VPWR pins should be placed as close to the pins as possible.
• Any digital communication should be routed away from the analog receiver pins. TXD, RXD, SCLK, NCS,
IO1, IO2, OUT3, and OUT4 pins should be routed on the opposite side of the PCB, away from of the analog
signals.
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 37
Product Folder Links: TUSS4470

TUSS4470
SLDS251A – DECEMBER 2019 – REVISED MAY 2022 www.ti.com
10.2 Layout Example
Legend Charging Capacitor
| Copper Trace - Top    |       |     | 2  F     |     |
| --------------------- | ----- | --- | -------- | --- |
|                       | Power |     | (cid:10) |     |
| Copper Trace - Bottom | +     |     |          |     |
|                       | —     |     | +        |     |
Via
To Controller
(cid:9)
|     | RWPV 02 | 4TUO 91 VRDV 71 BTUO 61 |     |     |
| --- | ------- | ----------------------- | --- | --- |
TLF 81
| To Controller | OUT3 1 |     | 15 OUTA |     |
| ------------- | ------ | --- | ------- | --- |
(cid:1)
|               | DGND 2 |             | 14 GND  |     |
| ------------- | ------ | ----------- | ------- | --- |
| To Controller | NCS 3  | Thermal Pad | 13 SGND |     |
(cid:0)
| To Controller | SCLK 4 |     | 12 INP |     |
| ------------- | ------ | --- | ------ | --- |
(cid:2)
| To Controller | SDI 5 |     | 11 INN |     |
| ------------- | ----- | --- | ------ | --- |
(cid:3)
|     | 6 ODS | 7 1OI 8 2OI  01 TUOV 9 DDV |     | Transducer |
| --- | ----- | -------------------------- | --- | ---------- |
To Controller
(cid:4)
To/From Controller
(cid:5)
To/From Controller
(cid:6)
To ADC
(cid:7)
From LDO
(cid:8)
Figure 10-1. TUSS4470 Layout Example
38 Submit Document Feedback Copyright © 2022 Texas Instruments Incorporated
Product Folder Links: TUSS4470

TUSS4470
www.ti.com SLDS251A – DECEMBER 2019 – REVISED MAY 2022
11 Device and Documentation Support
11.1 Receiving Notification of Documentation Updates
To receive notification of documentation updates, navigate to the device product folder on ti.com. Click on
Subscribe to updates to register and receive a weekly digest of any product information that has changed. For
change details, review the revision history included in any revised document.
11.2 Support Resources
TI E2E™ support forums are an engineer's go-to source for fast, verified answers and design help — straight
from the experts. Search existing answers or ask your own question to get the quick design help you need.
Linked content is provided "AS IS" by the respective contributors. They do not constitute TI specifications and do
not necessarily reflect TI's views; see TI's Terms of Use.
11.3 Trademarks
TI E2E™ is a trademark of Texas Instruments.
All trademarks are the property of their respective owners.
11.4 Electrostatic Discharge Caution
This integrated circuit can be damaged by ESD. Texas Instruments recommends that all integrated circuits be handled
with appropriate precautions. Failure to observe proper handling and installation procedures can cause damage.
ESD damage can range from subtle performance degradation to complete device failure. Precision integrated circuits may
be more susceptible to damage because very small parametric changes could cause the device not to meet its published
specifications.
11.5 Glossary
TI Glossary This glossary lists and explains terms, acronyms, and definitions.
12 Mechanical, Packaging, and Orderable Information
The following pages include mechanical, packaging, and orderable information. This information is the most
current data available for the designated devices. This data is subject to change without notice and revision of
this document. For browser-based versions of this data sheet, refer to the left-hand navigation.
Copyright © 2022 Texas Instruments Incorporated Submit Document Feedback 39
Product Folder Links: TUSS4470

PACKAGE OPTION ADDENDUM
www.ti.com 9-Nov-2025
PACKAGING INFORMATION
Orderable part number Status Material type Package | Pins Package qty | Carrier RoHS Lead finish/ MSL rating/ Op temp (°C) Part marking
(1) (2) (3) Ball material Peak reflow (6)
(4) (5)
TUSS4470TRTJR Active Production QFN (RTJ) | 20 3000 | LARGE T&R Yes NIPDAU Level-1-260C-UNLIM -25 to 105 USS4470
TUSS4470TRTJR.A Active Production QFN (RTJ) | 20 3000 | LARGE T&R Yes NIPDAU Level-1-260C-UNLIM -25 to 105 USS4470
TUSS4470TRTJT Obsolete Production QFN (RTJ) | 20 - - Call TI Call TI -25 to 105 USS4470
(1) Status: For more details on status, see our product life cycle.
(2) Material type: When designated, preproduction parts are prototypes/experimental devices, and are not yet approved or released for full production. Testing and final process, including without limitation quality assurance,
reliability performance testing, and/or process qualification, may not yet be complete, and this item is subject to further changes or possible discontinuation. If available for ordering, purchases will be subject to an additional
waiver at checkout, and are intended for early internal evaluation purposes only. These items are sold without warranties of any kind.
(3) RoHS values: Yes, No, RoHS Exempt. See the TI RoHS Statement for additional information and value definition.
(4) Lead finish/Ball material: Parts may have multiple material finish options. Finish options are separated by a vertical ruled line. Lead finish/Ball material values may wrap to two lines if the finish value exceeds the maximum
column width.
(5) MSL rating/Peak reflow: The moisture sensitivity level ratings and peak solder (reflow) temperatures. In the event that a part has multiple moisture sensitivity ratings, only the lowest level per JEDEC standards is shown.
Refer to the shipping label for the actual reflow temperature that will be used to mount the part to the printed circuit board.
(6) Part marking: There may be an additional marking, which relates to the logo, the lot trace code information, or the environmental category of the part.
Multiple part markings will be inside parentheses. Only one part marking contained in parentheses and separated by a "~" will appear on a part. If a line is indented then it is a continuation of the previous line and the two
combined represent the entire part marking for that device.
Important Information and Disclaimer:The information provided on this page represents TI's knowledge and belief as of the date that it is provided. TI bases its knowledge and belief on information provided by third parties, and
makes no representation or warranty as to the accuracy of such information. Efforts are underway to better integrate information from third parties. TI has taken and continues to take reasonable steps to provide representative
and accurate information but may not have conducted destructive testing or chemical analysis on incoming materials and chemicals. TI and TI suppliers consider certain information to be proprietary, and thus CAS numbers
and other limited information may not be available for release.
In no event shall TI's liability arising out of such information exceed the total purchase price of the TI part(s) at issue in this document sold by TI to Customer on an annual basis.
Addendum-Page 1

PACKAGE MATERIALS INFORMATION
|     |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- |
www.ti.com 3-Sep-2026
TAPE AND REEL INFORMATION
| REEL DIMENSIONS |     |     | TAPE DIMENSIONS |     |     |     |
| --------------- | --- | --- | --------------- | --- | --- | --- |
K0  P1
W
B0
Reel
Diameter
|     |     |     | Cavity                                                    | A0  |     |     |
| --- | --- | --- | --------------------------------------------------------- | --- | --- | --- |
|     |     | A0  | Dimension designed to accommodate the component width     |     |     |     |
|     |     | B0  | Dimension designed to accommodate the component length    |     |     |     |
|     |     | K0  | Dimension designed to accommodate the component thickness |     |     |     |
|     |     | W   | Overall width of the carrier tape                         |     |     |     |
|     |     | P1  | Pitch between successive cavity centers                   |     |     |     |
Reel Width (W1)
QUADRANT ASSIGNMENTS FOR PIN 1 ORIENTATION IN TAPE
Sprocket Holes
|     |     | Q1 Q2 | Q1 Q2 |                        |     |     |
| --- | --- | ----- | ----- | ---------------------- | --- | --- |
|     |     | Q3 Q4 | Q3 Q4 | User Direction of Feed |     |     |
Pocket Quadrants

*All dimensions are nominal
| Device | Package Package | Pins | SPQ Reel Reel | A0 B0 | K0 P1 | W Pin1 |
| ------ | --------------- | ---- | ------------- | ----- | ----- | ------ |
Type Drawing Diameter Width (mm) (mm) (mm) (mm) (mm) Quadrant
|     |     |     | (mm) W1 (mm) |     |     |     |
| --- | --- | --- | ------------ | --- | --- | --- |
TUSS4470TRTJR QFN RTJ 20 3000 330.0 12.4 4.25 4.25 1.15 8.0 12.0 Q2
Pack Materials-Page 1

PACKAGE MATERIALS INFORMATION
www.ti.com 3-Sep-2026
TAPE AND REEL BOX DIMENSIONS
Width (mm) H
W L
*All dimensions are nominal
Device Package Type Package Drawing Pins SPQ Length (mm) Width (mm) Height (mm)
TUSS4470TRTJR QFN RTJ 20 3000 360.0 360.0 36.0
Pack Materials-Page 2

GENERIC PACKAGE VIEW
RTJ 20 WQFN - 0.8 mm max height
4 x 4, 0.5 mm pitch PLASTIC QUAD FLATPACK - NO LEAD
This image is a representation of the package family, actual package may vary.
Refer to the product data sheet for package details.
4224842/A
www.ti.com

DATABOOK
PACKAGEOUTLINE
LEADFRAMEEXAMPLE
4222370
| DRAFTSMAN: | DATE:    |     |     |     |     |     |
| ---------- | -------- | --- | --- | --- | --- | --- |
| H.DENG     | 09122016 |     |     |     |     |     |
| DESIGNER:  | DATE:    |     |     |     |     |     |
CODEIDENTITY
| H.DENG | 09122016 |     |     |     |     | NUMBER |
| ------ | -------- | --- | --- | --- | --- | ------ |
01295
| CHECKER:         | DATE:    |            |       | SEMICONDUCTOROPERATIONS |       |          |
| ---------------- | -------- | ---------- | ----- | ----------------------- | ----- | -------- |
| V.PAKU&T.LEQUANG | 09122016 |            |       |                         |       |          |
| ENGINEER:        | DATE:    |            | ePOD, | RTJ0020D                | WQFN, |          |
| T.TANG           | 09122016 |            |       |                         |       |          |
| APPROVED:        | DATE:    |            | 20    | PIN, 0.5MMPITCH         |       |          |
| E.REY&D.CHIN     | 10062016 |            |       |                         |       |          |
| RELEASED:        | DATE:    |            |       |                         |       |          |
| WDM              | 10242016 |            |       |                         |       |          |
|                  |          | SCALE SIZE |       |                         |       | REV PAGE |
| TEMPLATEINFO:    | DATE:    | 15X A      |       | 4219125                 |       | A        |
OF
| EDGE4218519 | 04072016 |     |     |     |     |     |
| ----------- | -------- | --- | --- | --- | --- | --- |

PACKAGEOUTLINE
RTJ0020D WQFN- 0.8mmmaxheight
PLASTICQUADFLATPACK-NOLEAD
A
4.1
B
3.9
PIN1INDEXAREA
4.1
3.9
DIMA
OPT1 OPT2
(0.1) (0.2)
C
0.8MAX
SEATINGPLANE
0.05
0.00 0.08 C
16X0.5
(A)TYP
6 10
EXPOSED
THERMALPAD
5
11
SYMM (cid:21)(cid:17)(cid:26)(cid:147)(cid:19)(cid:17)(cid:20)
4X2
21
15
1
0.5
20X
0.3
PIN1ID
(OPTIONAL)
20 SYMM 16
0.29
20X
0.19
0.1 C A B
0.05 C
4219125 A 102016
NOTES:
1. Alllineardimensionsareinmillimeters.Anydimensionsinparenthesisareforreferenceonly.Dimensioningandtolerancing
perASMEY14.5M.
2. Thisdrawingissubjecttochangewithoutnotice.
3. Thepackagethermalpadmustbesolderedtotheprintedcircuitboardforthermalandmechanicalperformance.
www.ti.com

EXAMPLEBOARDLAYOUT
RTJ0020D WQFN- 0.8mmmaxheight
PLASTICQUADFLATPACK-NOLEAD
2.7)
SYMM
20 16
20X(0.6)
1
20X(0.24) 15
(1.1)
21
TYP
SYMM
(3.8)
(0.5)
(cid:11)(cid:145)(cid:19)(cid:17)(cid:21)(cid:12)(cid:3)(cid:55)(cid:60)(cid:51) TYP
VIA
5
11
(R0.05)
TYP
6 10
(3.8)
LANDPATTERNEXAMPLE
SCALE:20X
0.07MAX 0.07MIN
ALLAROUND ALLAROUND
SOLDERMASK METAL METALUNDER SOLDERMASK
OPENING SOLDERMASK OPENING
NONSOLDERMASK SOLDERMASK
DEFINED DEFINED
(PREFERRED)
SOLDERMASKDETAILS
4219125 A 102016
NOTES:(continued)
4. Thispackageisdesignedtobesolderedtoathermalpadontheboard.Formoreinformation,seeTexasInstruments
literaturenumber SLUA271(www.ti.comlitslua271) .
5. Viasareoptionaldependingonapplication,refertodevicedatasheet.Ifanyviasareimplemented,refertotheir
locationsshownonthisview.Itisrecommendedthatviasunderpastebefilled,pluggedortented.
www.ti.com

EXAMPLESTENCILDESIGN
RTJ0020D WQFN- 0.8mmmaxheight
PLASTICQUADFLATPACK-NOLEAD
SYMM
(0.69)
20 TYP 16
20X(0.6)
1
20X(0.24) 15
(0.69)
TYP
SYMM
(3.8)
(0.5)
TYP
5
11
(R0.05)
TYP 21
6 10
4X( 1.19)
(3.8)
SOLDERPASTEEXAMPLE
BASEDON0.125mmTHICKSTENCIL
EXPOSEDPAD
78PRINTEDCOVERAGEBYAREA
SCALE:20X
4219125 A 102016
NOTES:(continued)
6. Lasercuttingapertureswithtrapezoidalwallsandroundedcornersmayofferbetterpasterelease.IPC-7525mayhavealternate
designrecommendations..
www.ti.com

REVISIONS
| REV                 | DESCRIPTION |               | ECR     | DATE     | ENGINEERDRAFTSMAN |
| ------------------- | ----------- | ------------- | ------- | -------- | ----------------- |
| A RELEASENEWDRAWING |             |               | 2160736 | 10242016 | T.TANGH.DENG      |
|                     |             | SC AL E S IZE |         | 4219125  | R EV PA G E       |
N T S A A
5 O F 5

IMPORTANT NOTICE AND DISCLAIMER
TI PROVIDES TECHNICAL AND RELIABILITY DATA (INCLUDING DATASHEETS), DESIGN RESOURCES (INCLUDING REFERENCE
DESIGNS), APPLICATION OR OTHER DESIGN ADVICE, WEB TOOLS, SAFETY INFORMATION, AND OTHER RESOURCES “AS IS”
AND WITH ALL FAULTS, AND DISCLAIMS ALL WARRANTIES, EXPRESS AND IMPLIED, INCLUDING WITHOUT LIMITATION ANY
IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT OF THIRD
PARTY INTELLECTUAL PROPERTY RIGHTS.
These resources are intended for skilled developers designing with TI products. You are solely responsible for (1) selecting the appropriate
TI products for your application, (2) designing, validating and testing your application, and (3) ensuring your application meets applicable
standards, and any other safety, security, regulatory or other requirements.
These resources are subject to change without notice. TI grants you permission to use these resources only for development of an
application that uses the TI products described in the resource. Other reproduction and display of these resources is prohibited. No license
is granted to any other TI intellectual property right or to any third party intellectual property right. TI disclaims responsibility for, and you fully
indemnify TI and its representatives against any claims, damages, costs, losses, and liabilities arising out of your use of these resources.
TI’s products are provided subject to TI’s Terms of Sale, TI’s General Quality Guidelines, or other applicable terms available either on
ti.com or provided in conjunction with such TI products. TI’s provision of these resources does not expand or otherwise alter TI’s applicable
warranties or warranty disclaimers for TI products. Unless TI explicitly designates a product as custom or customer-specified, TI products
are standard, catalog, general purpose devices.
TI objects to and rejects any additional or different terms you may propose.
IMPORTANT NOTICE
Copyright © 2026, Texas Instruments Incorporated
Last updated 10/2025