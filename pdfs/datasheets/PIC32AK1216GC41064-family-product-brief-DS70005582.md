High-Performance 32-bit MCUs with Floating-Point Unit
and High-Speed ADCs
PIC32AK1216GC41064 Family
Operating Conditions
• 3.0V to 3.6V: -40°C to +125°C, DC to 200 MHz
High-Performance 32-bit CPU
• 32-bit Comprehensive Instruction Set for Optimized Speed and Program Code Size:
– Non-paged linear data/Flash 24-bit addressing space
– 16-bit/32-bit instructions for optimized code size and performance
• 32-Bit Wide Data Paths
• Single and Double Precision Floating-Point Unit (FPU) Coprocessor
• 2-Kbyte Instruction Cache
• 16-Bit/32-Bit Working Registers
• Dual 72-Bit Accumulators Supporting Fixed-Point DSP Operations
• Eight Level Deep Working Register Sets
• Eight Level Deep Accumulator Register Sets
• Eight Level Deep Floating-Point Register Sets
Controller Features
• High-Current Sink/Source Capable I/Os
• Programmable Weak Pull-Up and Pull-Down Resistors
• Programmable Open-Drain Outputs
• Edge or Level Change Notification Interrupt on I/O pins
• Peripheral Pin Select (PPS) Remappable Pins to Reduce Board Layout Complexity
• Multiple Interrupt Vectors with Individual Programmable Priority
• Five External Interrupt Pins
• Selectable Oscillator Options Including:
– 8 MHz, 1% at 0ºC-85ºC Internal Fast RC (FRC) oscillator
– 8 MHz, 2% Internal Backup Fast RC (BFRC) oscillator with 32 kHz divided output
– High-speed crystal resonator oscillator or external clock
• Two 1.6 GHz PLLs for Peripherals which can be clocked from the FRC or a Crystal Oscillator
• Reference Clock Output (REFO)
• Low-Power Modes (Sleep and Idle)
• Power-On Reset and Brown-Out Reset
Product Brief DS70005582A - 1
© 2024 Microchip Technology Inc. and its subsidiaries

PIC32AK1216GC41064 Family
Two High-Speed Analog-to-Digital Converters
• 12-bit Resolution
• Up to 40 Msps Conversion Rate
• Up to 22 Analog Input Pins
• 20 Settings Channels. Each Channel:
– Supports discrete configuration
– Can be assigned to any analog input (I/O pin or internal signal)
– Can be set to a different sampling time
– Can be configured as single-ended or differential
– Conversion result can be formatted as unsigned or signed
– Conversion result can be left-aligned (fraction format)
– Has a separate 32-bit conversion result register
• Supports Four Sampling Modes:
– Oversampling of multiple samples
– Integration of multiple samples
– Window (multiple samples accumulated when the gate signal is active)
– Single conversion
– All channels have a digital comparator to detect when the conversion result is less than, greater than, in
bounds or out of bounds for the configurable thresholds
– Three channels support second result accumulator to implement second order filters
• Band Gap Reference and Temperature Sensor Diode Inputs
Analog Features
• Three 5 nS Analog Comparators with 12-Bit PDM DACs:
– Input multiplexing
– Slope compensation
– One DAC output buffer
• Three Rail-to-Rail 100 MHz Operational Amplifiers with:
– 100 V/µS slew rate
– 1 mV offset (typical)
• Four 10 μA Constant Sources and Four Programmable Sources
High-Speed PWM
• Four PWM Generators (Four Pairs with Eight Outputs)
• Up to 2.5 nS PWM Resolution
• Dead Time for Rising and Falling Edges
• Dead-Time Compensation Supports Lower Speed Operation
• Clock Chopping for High-Frequency Operation
• Fault and Current Limit Inputs
• Flexible Trigger Configuration for ADC Triggering
Product Brief DS70005582A - 2
© 2024 Microchip Technology Inc. and its subsidiaries

PIC32AK1216GC41064 Family
Peripheral Features
• 3 Four-Wire SPI Modules (up to 40 Mbps):
– 16-byte FIFO
– Variable data width
– I2S mode
• Two I2C Modules w/Address Masking and IPMI Support
• Three Protocol UARTs with 8-Character RX/TX FIFOs and Automated Handling Support for:
– LIN 2.2
– DMX
– Smart card (ISO 7816)
®
– IrDA
• Two SENT Modules
• One Dedicated 32-Bit Timer/Counter
• Four Single Output Capture/Compare/PWM/Timer (SCCP) Modules:
– Flexible configuration as PWM, input capture, output compare or timers
– Two 16-bit timers or one 32-bit timer in each module
– Single PWM output pin
• One Quadrature Encoder Interface (QEI):
– Four inputs: Phase A, Phase B, Home and Index
• Four Configurable Logic Cells (CLC) with Internal Connections to Select Peripherals and PPS
• Serial Encoder Interface BiSS with up to Four Client Encoders Support
• Peripheral Trigger Generator (PTG):
– Ten input trigger sources from other peripheral modules
– Five output triggers to other peripheral modules
– Four individual interrupt request signals
– CPU independent state machine-based instruction sequencer
Safety Features
• Windowed Watchdog Timer (WDT)
• Deadman Timer (DMT)
• Four I/O Integrity Monitors (IOIM)
• Fail-Safe Clock Monitor (FSCM) with Automatic Switchover to Backup Clock Source with:
– Programmable over-frequency/under-frequency thresholds
• Flash Error Correcting Code (ECC)
• RAM Error Correcting Code (ECC)
• RAM Memory Built-In Self-Test (MBIST)
• 32-Bit Cyclic Redundancy Check (CRC) Module
• Entire Flash OTP by ICSP™ Write Inhibit
• Capless Internal Voltage Regulator
• Virtual PPS Pins for Redundancy and Monitoring
Product Brief DS70005582A - 3
© 2024 Microchip Technology Inc. and its subsidiaries

PIC32AK1216GC41064 Family
• Temperature Sensor Diode
Security Module
• Secure Boot
• Secure Debug
• Immutable Root of Trust (IRT)
• Code Protect
• ICSP Program/Erase Disable (Entire Flash OTP by ICSP Write Inhibit)
• Firmware IP Protection
• Flash Write Protection
Qualification
AEC-Q100 REV H:
• Grade 1: -40°C to +125°C
Debug Features
• Three Programming and Debugging Interfaces:
– Two-wire ICSP interface with non-intrusive access and real-time data exchange with application
• Five Complex and Five Simple Breakpoints
• IEEE Standard 1149.2 Compatible (JTAG) Boundary Scan
Product Brief DS70005582A - 4
© 2024 Microchip Technology Inc. and its subsidiaries

PIC32AK1216GC41064 Family
PIC32AK1216GC41064 Product Family
PIC32AK1216GC41064 Product Family
The PIC32AK family names, pin counts, memory sizes and peripheral availability of each device are
listed in Table 1, and their pinout diagrams are included as well.
Product Brief DS70005582A - 5
© 2024 Microchip Technology Inc. and its subsidiaries

©
2024
Microchip
Technology
Inc.
and
its
subsidiaries
Product
Brief
DS70005582A
-
6
PIC32AK1216GC41064
Product
Family
PIC32AK1216GC41064
Family
Table 1. PIC32AK1216GC41064 Family
Product
rotatethispage90
sniP
)setybK(
yromeM
margorP
)setybK(
yromeM
ataD
SPP/O/I
esopruP
lareneG
)sriaP
rotareneG(
MWP
noituloseR-hgiH
)stupnI
golanA
lanretxE(
sCDA
tib-21
owT
Remappable Peripherals
sremiT
tib-23
detacideD
TRAU SSIB
)1(PCCS
CLC
S2I/IPS
TNES IEQ
srefiilpmA
pO
srotarapmoC
sCAD
tib-21 C2I
CRC
tib-23
)slennahC(
AMD
segakcaP
PIC32AK3208GC41036 36 32 8 27/27 4*2 15 1 3 1 4 4 3 2 1 3 3 3 2 1 6 VQFN
PIC32AK3208GC41048 48 32 8 35/35 4*2 18 1 3 1 4 4 3 2 1 3 3 3 2 1 6 VQFN/TQFP
PIC32AK3208GC41064 64 32 8 49/49 4*2 22 1 3 1 4 4 3 2 1 3 3 3 2 1 6 VQFN/TQFP
PIC32AK6416GC41036 36 64 16 27/27 4*2 15 1 3 1 4 4 3 2 1 3 3 3 2 1 6 VQFN
PIC32AK6416GC41048 48 64 16 35/35 4*2 18 1 3 1 4 4 3 2 1 3 3 3 2 1 6 VQFN/TQFP
PIC32AK6416GC41064 64 64 16 49/49 4*2 22 1 3 1 4 4 3 2 1 3 3 3 2 1 6 VQFN/TQFP
PIC32AK1216GC41036 36 128 16 27/27 4*2 15 1 3 1 4 4 3 2 1 3 3 3 2 1 6 VQFN
PIC32AK1216GC41048 48 128 16 35/35 4*2 18 1 3 1 4 4 3 2 1 3 3 3 2 1 6 VQFN/TQFP
PIC32AK1216GC41064 64 128 16 49/49 4*2 22 1 3 1 4 4 3 2 1 3 3 3 2 1 6 VQFN/TQFP
Note:
rotatethispage90
1. SCCP can be configured as a PWM with one output, input capture, output compare, 2 x 16-bit timers or 1 x 32-bit timer.

 PIC32AK1216GC41064 Family
Pin Diagrams
Pin Diagrams
Figure 1. 36-Pin VQFN
5V Tolerant
RLCM
11DR
|     | 4DR | DD SS 3DR | 2DR 1DR 0DR |     |
| --- | --- | --------- | ----------- | --- |
V V
|     | 36 35 34 | 33 32 31 | 30 29 28 |     |
| --- | -------- | -------- | -------- | --- |
|     | RA0 1    |          | 27 RC4   |     |
|     | RA1 2    |          | 26 RC3   |     |
|     | AV 3     |          | 25 RC5   |     |
SS
|     | AV DD 4 |     | 24 RC2 |     |
| --- | ------- | --- | ------ | --- |
PIC32AKXXXXGC41036
|     | RA2 5 |     | 23 V |     |
| --- | ----- | --- | ---- | --- |
DD
|     | RA3 6 |     | 22 V |     |
| --- | ----- | --- | ---- | --- |
SS
|     | RA4 7 |     | 21 RC1 |     |
| --- | ----- | --- | ------ | --- |

RC0(2)
|     | RA5 8     |                 | 20          |     |
| --- | --------- | --------------- | ----------- | --- |
|     | RA6 9     |                 | 19 RB7      |     |
|     | 10 11 12  | 13 14 15        | 16 17 18    |     |
|     | 5BR SS DD | 0BR )4( 1BR 2BR | 3BR 4BR 6BR |     |
1BR
V V
Table 2. 36-Pin VQFN Complete Pin Function Descriptions(1,3)
| Pin | Function | Pin |     | Function |
| --- | -------- | --- | --- | -------- |
1 PGD2/AD2AN6/CMP3C/ISRC2/IBIAS2/RP1/SDA2/ 19 AD2ANN2/AD2AN8/RP24/IOMF0/RB7
IOMF2/RA0
2 PGC2/DACOUT1/AD1AN7/AD2AN3/CMP1D/CMP2D/ 20 OSCO/CLKO/RP33/IOMF5/RC0(2)
CMP3D/RP2/SCL2/RA1
| 3 AV SS                       |     | 21  | OSCI/CLKI/RP34/IOMF6/RC1 |     |
| ----------------------------- | --- | --- | ------------------------ | --- |
| 4 AV                          |     | 22  | V                        |     |
| DD                            |     |     | SS                       |     |
| 5 OA1OUT/AD1AN0/CMP1A/RP3/RA2 |     | 23  | V                        |     |
DD
| 6 OA1IN-/AD1ANN1/AD2AN0/RP4/RA3 |     | 24  | PGC3/RP35/PWM4H/RC2       |     |
| ------------------------------- | --- | --- | ------------------------- | --- |
| 7 OA1IN+/AD1AN1/CMP1B/RP5/RA4   |     | 25  | RP38/PWM4L/RC5            |     |
| 8 OA3OUT/AD1AN3/CMP3A/RP6/RA5   |     | 26  | PGD3/RP36/PWM3H/IOMD0/RC3 |     |
| 9 OA3IN-/AD1AN2/RP7/RA6         |     | 27  | RP37/PWM3L/IOMD1/RC4      |     |
| 10 OA3IN+/AD2AN2/CMP3B/RP22/RB5 |     | 28  | RP49/PWM2H/IOMD2/RD0      |     |
| 11 V                            |     | 29  | TCK/RP50/PWM2L/IOMD3/RD1  |     |
SS
| 12 V |     | 30  | TDO/RP51/PWM1H/IOMD4/RD2 |     |
| ---- | --- | --- | ------------------------ | --- |
DD
13 OA2OUT/AD2AN1/CMP2A/RP17/INT0/RB0 31 TDI/RP52/PWM1L/IOMD5/RD3
| 14 TMS/OA2IN-/AD1AN4/AD2ANN1/RP18/RB1(4) |     | 32  | V   |     |
| ---------------------------------------- | --- | --- | --- | --- |
SS
| 15 OA2IN+/AD2AN4/CMP2B/RP19/RB2 |     | 33  | V   |     |
| ------------------------------- | --- | --- | --- | --- |
DD
| 16 PGD1/AD1AN5/CMP1C/ISRC0/IBIAS0/RP20/SDA1/RB3 |     | 34  | RP53/PCI22/RD4 |     |
| ----------------------------------------------- | --- | --- | -------------- | --- |
| 17 PGC1/AD2AN5/CMP2C/ISRC1/IBIAS1/RP21/SCL1/RB4 |     | 35  | RP60/RD11      |     |
| 18 AD1ANN2/AD1AN8/RP23/RB6                      |     | 36  | MCLR           |     |
 Product Brief DS70005582A - 7
© 2024 Microchip Technology Inc. and its subsidiaries

PIC32AK1216GC41064 Family
Pin Diagrams
...........continued
Pin Function Pin Function
Notes:
1. RPn represents remappable peripheral functions.
2. This pin has 8x drive strength.
3. Unless otherwise stated, pins are 4x drive strength. Refer to the Electrical Specifications section of the device data sheet
for current drive strength details.
4. A pull-up resistor is connected to this pin when the device is erased (JTAG enabled) and during programming.
Product Brief DS70005582A - 8
© 2024 Microchip Technology Inc. and its subsidiaries

 PIC32AK1216GC41064 Family
Pin Diagrams
Pin Diagrams
Figure 2. 48-Pin VQFN, TQFP
5V Tolerant
RLCM
|     |     | 4DR DD | SS 8DR 7DR | 6DR 5DR 3DR 2DR 1DR 0DR |     |
| --- | --- | ------ | ---------- | ----------------------- | --- |
V V
|     |       | 48 47 46 | 45 44 43 | 42 41 40 39 38 37 |     |
| --- | ----- | -------- | -------- | ----------------- | --- |
|     | RA0 1 |          |          | 36 V              |     |
DD
|     | RA7 2 |     |     | 35 V   | SS  |
| --- | ----- | --- | --- | ------ | --- |
|     | RA1 3 |     |     | 34 RC4 |     |
|     | RA8 4 |     |     | 33 RC3 |     |
|     | RA9   |     |     | RC5    |     |
5 32
|     | AV 6 |     |     | 31 RC2 |     |
| --- | ---- | --- | --- | ------ | --- |
SS
PIC32AKXXXXGC41048
|     | AV DD 7 |     |     | 30 V | DD  |
| --- | ------- | --- | --- | ---- | --- |
|     | RA2 8   |     |     | 29 V |     |
SS
|     | RA3 9  |     |     | 28 RC1    |     |
| --- | ------ | --- | --- | --------- | --- |
|     | RA4 10 |     |     | 27 RC0(2) |     |
|     | RA5 11 |     |     | 26 RC7    |     |
|     | RA6    |     |     | RC6       |     |
12 25
|     |     | 13 14 15 | 16 17 18 | 19 20 21 22 23 24 |     |
| --- | --- | -------- | -------- | ----------------- | --- |
)4(
|     |     | 5BR SS DD | 0BR 1BR 1BR 2BR | SS DD 3BR 4BR 6BR 7BR |     |
| --- | --- | --------- | --------------- | --------------------- | --- |
|     |     | V V       |                 | V V                   |     |
Table 3. 48-Pin VQFN, TQFP Complete Pin Function Descriptions(1,3)
| Pin                                        | Function |     |     | Pin         | Function |
| ------------------------------------------ | -------- | --- | --- | ----------- | -------- |
| 1 PGD2/AD2AN6/CMP3C/ISRC2/IBIAS2/RP1/SDA2/ |          |     |     | 25 RP39/RC6 |          |
IOMF2/RA0
| 2 AD1AN6/RP8/IOMF1/RA7 |     |     |     | 26 RP40/RC7 |     |
| ---------------------- | --- | --- | --- | ----------- | --- |
3 PGC2/DACOUT1/AD1AN7/AD2AN3/CMP1D/CMP2D/ 27 OSCO/CLKO/RP33/IOMF5/RC0(2)
CMP3D/RP2/SCL2/RA1
| 4 AD2AN9/ISRC3/IBIAS3/RP9/RA8 |     |     |     | 28 OSCI/CLKI/RP34/IOMF6/RC1 |     |
| ----------------------------- | --- | --- | --- | --------------------------- | --- |
| 5 AD1ANN3/AD1AN9/RP10/RA9     |     |     |     | 29 V SS                     |     |
| 6 AV                          |     |     |     | 30 V                        |     |
| SS                            |     |     |     | DD                          |     |
| 7 AV                          |     |     |     | 31 PGC3/RP35/PWM4H/RC2      |     |
DD
| 8 OA1OUT/AD1AN0/CMP1A/RP3/RA2   |     |     |     | 32 RP38/PWM4L/RC5            |     |
| ------------------------------- | --- | --- | --- | ---------------------------- | --- |
| 9 OA1IN-/AD1ANN1/AD2AN0/RP4/RA3 |     |     |     | 33 PGD3/RP36/PWM3H/IOMD0/RC3 |     |
| 10 OA1IN+/AD1AN1/CMP1B/RP5/RA4  |     |     |     | 34 RP37/PWM3L/IOMD1/RC4      |     |
| 11 OA3OUT/AD1AN3/CMP3A/RP6/RA5  |     |     |     | 35 V SS                      |     |
| 12 OA3IN-/AD1AN2/RP7/RA6        |     |     |     | 36 V                         |     |
DD
| 13 OA3IN+/AD2AN2/CMP3B/RP22/RB5 |     |     |     | 37 RP49/PWM2H/IOMD2/RD0     |     |
| ------------------------------- | --- | --- | --- | --------------------------- | --- |
| 14 V SS                         |     |     |     | 38 TCK/RP50/PWM2L/IOMD3/RD1 |     |
| 15 V DD                         |     |     |     | 39 TDO/RP51/PWM1H/IOMD4/RD2 |     |
16 OA2OUT/AD2AN1/CMP2A/RP17/INT0/RB0 40 TDI/RP52/PWM1L/IOMD5/RD3
| 17 TMS/OA2IN-/AD1AN4/AD2ANN1/RP18/RB1(4) |     |     |     | 41 RP54/ASCL1/RD5             |     |
| ---------------------------------------- | --- | --- | --- | ----------------------------- | --- |
| 18 OA2IN+/AD2AN4/CMP2B/RP19/RB2          |     |     |     | 42 RP55/ASDA1/RD6             |     |
| 19 V                                     |     |     |     | 43 RP56/ASCL2/IOMD7/IOMF4/RD7 |     |
SS
| 20 V |     |     |     | 44 RP57/ASDA2/IOMD6/IOMF3/RD8 |     |
| ---- | --- | --- | --- | ----------------------------- | --- |
DD
| 21 PGD1/AN1P5/CMP1C/ISRC0/IBIAS0/RP20/SDA1/RB3 |     |     |     | 45 V |     |
| ---------------------------------------------- | --- | --- | --- | ---- | --- |
SS
| 22 PGC1/AD2AN5/CMP2C/ISRC1/IBIAS1/RP21/SCL1/RB4 |     |     |     | 46 V |     |
| ----------------------------------------------- | --- | --- | --- | ---- | --- |
DD
| 23 AD1ANN2/AD1AN8/RP23/RB6 |     |     |     | 47 RP53/PCI22/RD4 |     |
| -------------------------- | --- | --- | --- | ----------------- | --- |
 Product Brief DS70005582A - 9
© 2024 Microchip Technology Inc. and its subsidiaries

PIC32AK1216GC41064 Family
Pin Diagrams
...........continued
Pin Function Pin Function
24 AD2ANN2/AD2AN8/RP24/IOMF0/RB7 48 MCLR
Note:
1. RPn represents remappable peripheral functions.
2. This pin has 8x drive strength.
3. Unless otherwise stated, pins are 4x drive strength. Refer to the Electrical Specifications section of the device data sheet
for current drive strength details.
4. A pull-up resistor is connected to this pin when the device is erased (JTAG enabled) and during programming.
Product Brief DS70005582A - 10
© 2024 Microchip Technology Inc. and its subsidiaries

 PIC32AK1216GC41064 Family
Pin Diagrams
Pin Diagrams
Figure 3. 64-Pin VQFN, TQFP
5V Tolerant
|     |     | RLCM | 21DR     |         |             |             | 01DR |     |
| --- | --- | ---- | -------- | ------- | ----------- | ----------- | ---- | --- |
|     |     |      | 11DR 4DR | 8DR 7DR | 6DR 5DR 3DR | 2DR 1DR 0DR | 9DR  |     |
DD SS
V V
|     |     | 46  | 36 26 16 | 06 95 85 75 | 65 55 45 | 35 25 15 | 05 94 |     |
| --- | --- | --- | -------- | ----------- | -------- | -------- | ----- | --- |
|     | RA0 | 1   |          |             |          |          | 48    | V   |
DD
|     | RA7 | 2   |     |     |     |     | 47  | V SS |
| --- | --- | --- | --- | --- | --- | --- | --- | ---- |
|     | RA1 | 3   |     |     |     |     | 46  | RC11 |
|     | V   | 4   |     |     |     |     | 45  | RC10 |
SS
|     | V    | DD 5 |     |                    |     |     | 44  | RC4 |
| --- | ---- | ---- | --- | ------------------ | --- | --- | --- | --- |
|     | RA11 | 6    |     |                    |     |     | 43  | RC3 |
|     | RA8  | 7    |     |                    |     |     | 42  | RC5 |
|     | RA9  | 8    |     |                    |     |     | 41  | RC2 |
|     | RA10 | 9    |     | PIC32AKXXXXGC41064 |     |     | 40  | V   |
DD
|     | AV  | 10    |           |                        |           |             | 39       | V      |
| --- | --- | ----- | --------- | ---------------------- | --------- | ----------- | -------- | ------ |
|     |     | SS    |           |                        |           |             |          | SS     |
|     | AV  | DD 11 |           |                        |           |             | 38       | RC1    |
|     | RA2 | 12    |           |                        |           |             | 37       | RC0(2) |
|     | RA3 | 13    |           |                        |           |             | 36       | RC7    |
|     | RA4 | 14    |           |                        |           |             | 35       | RC6    |
|     | RA5 | 15    |           |                        |           |             | 34       | RC9(2) |
|     | RA6 | 16    |           |                        |           |             | 33       | RC8(2) |
|     |     | 71    | 81 91 02  | 12 22 32 42            | 52 62 72  | 82 92 03    | 13 23    |        |
|     |     | 5BR   | SS DD 0BR | )4(1BR 1BR 2BR 8BR 9BR | SS DD 3BR | 4BR 6BR 7BR | )2( 11BR |        |
01BR
|     |     |     | V V |     | V V |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
Table 4. 64-Pin VQFN, TQFP Complete Pin Function Descriptions(1,3)
| Pin |     | Function |     |     | Pin |     |     | Function |
| --- | --- | -------- | --- | --- | --- | --- | --- | -------- |
1 PGD2/AD2AN6/CMP3C/ISRC2/IBIAS2/RP1/SDA2/ 33 RP41/IOMD11/IOMF11/PCI20/RC8(2)
IOMF2/RA0
2 AD1AN6/RP8/IOMF1/RA7 34 RP42/IOMD10/SDO2/IOMF10/PCI19/RC9(2)
| 3 PGC2/DACOUT1/AD1AN7/AD2AN3/CMP1D/CMP2D/ |     |     |     |     | 35  | RP39/RC6 |     |     |
| ----------------------------------------- | --- | --- | --- | --- | --- | -------- | --- | --- |
CMP3D/RP2/SCL2/RA1
| 4 V SS |     |     |     |     | 36  | RP40/RC7                    |     |     |
| ------ | --- | --- | --- | --- | --- | --------------------------- | --- | --- |
| 5 V    |     |     |     |     | 37  | OSCO/CLKO/RP33/IOMF5/RC0(2) |     |     |
DD
| 6 AD1AN10/RP12/RA11           |     |     |     |     | 38  | OSCI/CLKI/RP34/IOMF6/RC1 |     |     |
| ----------------------------- | --- | --- | --- | --- | --- | ------------------------ | --- | --- |
| 7 AD2AN9/ISRC3/IBIAS3/RP9/RA8 |     |     |     |     | 39  | V SS                     |     |     |
| 8 AD1ANN3/AD1AN9/RP10/RA9     |     |     |     |     | 40  | V                        |     |     |
DD
| 9 AD2ANN3/AD2AN7/RP11/RA10       |     |     |     |     | 41  | PGC3/RP35/PWM4H/RC2       |     |     |
| -------------------------------- | --- | --- | --- | --- | --- | ------------------------- | --- | --- |
| 10 AV SS                         |     |     |     |     | 42  | RP38/PWM4L/RC5            |     |     |
| 11 AV DD                         |     |     |     |     | 43  | PGD3/RP36/PWM3H/IOMD0/RC3 |     |     |
| 12 OA1OUT/AD1AN0/CMP1A/RP3/RA2   |     |     |     |     | 44  | RP37/PWM3L/IOMD1/RC4      |     |     |
| 13 OA1IN-/AD1ANN1/AD2AN0/RP4/RA3 |     |     |     |     | 45  | RP43/IOMD9/IOMF9/RC10     |     |     |
| 14 OA1IN+/AD1AN1/CMP1B/RP5/RA4   |     |     |     |     | 46  | RP44/IOMD8/IOMF8/RC11     |     |     |
| 15 OA3OUT/AD1AN3/CMP3A/RP6/RA5   |     |     |     |     | 47  | V                         |     |     |
SS
| 16 OA3IN-/AD1AN2/RP7/RA6 |     |     |     |     | 48  | V   |     |     |
| ------------------------ | --- | --- | --- | --- | --- | --- | --- | --- |
DD
| 17 OA3IN+/AD2AN2/CMP3B/RP22/RB5 |     |     |     |     | 49  | RP58/IOMF7/RD9 |     |     |
| ------------------------------- | --- | --- | --- | --- | --- | -------------- | --- | --- |
| 18 V                            |     |     |     |     | 50  | RP59/RD10      |     |     |
SS
| 19 V |     |     |     |     | 51  | RP49/PWM2H/IOMD2/RD0 |     |     |
| ---- | --- | --- | --- | --- | --- | -------------------- | --- | --- |
DD
 Product Brief DS70005582A - 11
© 2024 Microchip Technology Inc. and its subsidiaries

 PIC32AK1216GC41064 Family
Pin Diagrams
...........continued
| Pin | Function | Pin | Function |
| --- | -------- | --- | -------- |
20 OA2OUT/AD2AN1/CMP2A/RP17/INT0/RB0 52 TCK/RP50/PWM2L/IOMD3/RD1
TMS/OA2IN-/AD1AN4/AD2ANN1/RP18/RB1(4)
| 21                              |     | 53 TDO/RP51/PWM1H/IOMD4/RD2   |     |
| ------------------------------- | --- | ----------------------------- | --- |
| 22 OA2IN+/AD2AN4/CMP2B/RP19/RB2 |     | 54 TDI/RP52/PWM1L/IOMD5/RD3   |     |
| 23 AD1AN11/RP25/RB8             |     | 55 RP54/ASCL1/RD5             |     |
| 24 AD2AN10/RP26/RB9             |     | 56 RP55/ASDA1/RD6             |     |
| 25 V                            |     | 57 RP56/ASCL2/IOMD7/IOMF4/RD7 |     |
SS
| 26 V DD                                         |     | 58 RP57/ASDA2/IOMD6/IOMF3/RD8 |     |
| ----------------------------------------------- | --- | ----------------------------- | --- |
| 27 PGD1/AD1AN5/CMP1C/ISRC0/IBIAS0/RP20/SDA1/RB3 |     | 59 V SS                       |     |
| 28 PGC1/AD2AN5/CMP2C/ISRC1/IBIAS1/RP21/SCL1/RB4 |     | 60 V DD                       |     |
| 29 AD1ANN2/AD1AN8/RP23/RB6                      |     | 61 RP53/PCI22/RD4             |     |
| 30 AD2ANN2/AD2AN8/RP24/IOMF0/RB7                |     | 62 RP60/RD11                  |     |
RP27/SCK2/RB10(2)
| 31                |     | 63 RP61/PCI21/RD12 |     |
| ----------------- | --- | ------------------ | --- |
| 32 RP28/SDI2/RB11 |     | 64 MCLR            |     |
Note:
1. RPn represents remappable peripheral functions.
2. This pin has 8x drive strength.
3. Unless otherwise stated, pins are 4x drive strength. Refer to the Electrical Specifications section of the device data sheet
for current drive strength details.
4. A pull-up resistor is connected to this pin when the device is erased (JTAG enabled) and during programming.
 Product Brief DS70005582A - 12
© 2024 Microchip Technology Inc. and its subsidiaries

PIC32AK1216GC41064 Family
Microchip Information
Trademarks
The “Microchip” name and logo, the “M” logo, and other names, logos, and brands are registered
and unregistered trademarks of Microchip Technology Incorporated or its affiliates and/or
subsidiaries in the United States and/or other countries (“Microchip Trademarks”). Information
regarding Microchip Trademarks can be found at https://www.microchip.com/en-us/about/legal-
information/microchip-trademarks.
ISBN: 978-1-6683-0430-3
Legal Notice
This publication and the information herein may be used only with Microchip products, including
to design, test, and integrate Microchip products with your application. Use of this information
in any other manner violates these terms. Information regarding device applications is provided
only for your convenience and may be superseded by updates. It is your responsibility to ensure
that your application meets with your specifications. Contact your local Microchip sales office for
additional support or, obtain additional support at www.microchip.com/en-us/support/design-help/
client-support-services.
THIS INFORMATION IS PROVIDED BY MICROCHIP “AS IS”. MICROCHIP MAKES NO REPRESENTATIONS
OR WARRANTIES OF ANY KIND WHETHER EXPRESS OR IMPLIED, WRITTEN OR ORAL, STATUTORY
OR OTHERWISE, RELATED TO THE INFORMATION INCLUDING BUT NOT LIMITED TO ANY IMPLIED
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
PURPOSE, OR WARRANTIES RELATED TO ITS CONDITION, QUALITY, OR PERFORMANCE.
IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL, OR
CONSEQUENTIAL LOSS, DAMAGE, COST, OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
INFORMATION OR ITS USE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW,
MICROCHIP’S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THE INFORMATION OR
ITS USE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO
MICROCHIP FOR THE INFORMATION.
Use of Microchip devices in life support and/or safety applications is entirely at the buyer’s risk,
and the buyer agrees to defend, indemnify and hold harmless Microchip from any and all damages,
claims, suits, or expenses resulting from such use. No licenses are conveyed, implicitly or otherwise,
under any Microchip intellectual property rights unless otherwise stated.
Microchip Devices Code Protection Feature
Note the following details of the code protection feature on Microchip products:
• Microchip products meet the specifications contained in their particular Microchip Data Sheet.
• Microchip believes that its family of products is secure when used in the intended manner, within
operating specifications, and under normal conditions.
• Microchip values and aggressively protects its intellectual property rights. Attempts to breach the
code protection features of Microchip products are strictly prohibited and may violate the Digital
Millennium Copyright Act.
• Neither Microchip nor any other semiconductor manufacturer can guarantee the security of its
code. Code protection does not mean that we are guaranteeing the product is “unbreakable”.
Code protection is constantly evolving. Microchip is committed to continuously improving the
code protection features of our products.
Product Brief DS70005582A - 13
© 2024 Microchip Technology Inc. and its subsidiaries