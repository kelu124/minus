MPLAB IPE (Integrated Programming Environment)
User's Guide
MPLAB IPE User's Guide
Notice to Development Tools Customers
Important:
All documentation becomes dated, and Development Tools manuals are no exception. Our tools
and documentation are constantly evolving to meet customer needs, so some actual dialogs
and/or tool descriptions may differ from those in this document. Please refer to our website
(www.microchip.com/) to obtain the latest version of the PDF document.
Documents are identified with a DS number located on the bottom of each page. The DS format is
DS<DocumentNumber><Version>, where <DocumentNumber> is an 8-digit number and <Version>
is an uppercase letter.
For the most up-to-date information, find help for your tool at onlinedocs.microchip.com/.
User Guide DS50002227H - 1
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
Table of Contents
Notice to Development Tools Customers..........................................................................................................................1
1. Introduction...................................................................................................................................................................4
1.1. Conventions Used in This Guide......................................................................................................................4
1.2. Recommended Reading....................................................................................................................................4
2. MPLAB IPE Overview.....................................................................................................................................................6
2.1. IPE Defined..........................................................................................................................................................6
2.2. Software Installation Requirements................................................................................................................6
2.3. Programming Tools Supported........................................................................................................................7
2.4. IPE Modes...........................................................................................................................................................7
3. General Setup................................................................................................................................................................8
3.1. Launching the MPLAB IPE Application.............................................................................................................8
3.2. Setting Up the Programmer..............................................................................................................................8
3.3. Advanced Mode Login.....................................................................................................................................10
3.4. Advanced Mode Settings................................................................................................................................12
4. MPLAB IPE Reference..................................................................................................................................................24
4.1. IPE Main Window.............................................................................................................................................24
4.2. File Menu...........................................................................................................................................................25
4.3. Settings Menu...................................................................................................................................................26
4.4. View Menu........................................................................................................................................................28
4.5. Tools Menu.......................................................................................................................................................30
4.6. Window Menu..................................................................................................................................................36
4.7. Help Menu........................................................................................................................................................38
5. Revision History...........................................................................................................................................................39
5.1. Revision A (December 2013)...........................................................................................................................39
5.2. Revision B (August 2015).................................................................................................................................39
5.3. Revision C (March 2017)..................................................................................................................................39
5.4. Revision D (June 2018)....................................................................................................................................39
5.5. Revision E (April 2020).....................................................................................................................................39
5.6. Revision F (December 2021)...........................................................................................................................40
5.7. Revision G (November 2022)..........................................................................................................................40
5.8. Revision H (April 2023)....................................................................................................................................40
6. Support.........................................................................................................................................................................41
6.1. Warranty Registration......................................................................................................................................41
6.2. Personalized Notification Service..................................................................................................................41
The Microchip Website.......................................................................................................................................................42
Product Change Notification Service................................................................................................................................42
Customer Support..............................................................................................................................................................42
Product Identification System...........................................................................................................................................43
Microchip Devices Code Protection Feature....................................................................................................................43
User Guide DS50002227H - 2
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
Legal Notice.........................................................................................................................................................................43
Trademarks..........................................................................................................................................................................44
Quality Management System............................................................................................................................................45
Worldwide Sales and Service.............................................................................................................................................46
User Guide DS50002227H - 3
© 2023 Microchip Technology Inc. and its subsidiaries

 MPLAB IPE User's Guide
Introduction
1.  Introduction
This chapter contains general information that will be useful to know before using the MPLAB ®
Integrated Programming Environment (IPE) installed. This document is compatible with the version
of the IPE installed with MPLAB X IDE v6.0 or greater.
1.1  Conventions Used in This Guide
This manual uses the following documentation conventions:
Table 1-1. Documentation Conventions
| Description |     | Represents |     | Examples |
| ----------- | --- | ---------- | --- | -------- |
Arial font:
| Italic characters | Referenced books |     | MPLAB® IDE User’s Guide    |     |
| ----------------- | ---------------- | --- | -------------------------- | --- |
|                   | Emphasized text  |     | ...is the only compiler... |     |
| Initial caps      | A window         |     | the Output window          |     |
|                   | A dialog         |     | the Settings dialog        |     |
|                   | A menu selection |     | select Enable Programmer   |     |
Quotes A field name in a window or dialog “Save project before build”
| Underlined, italic text with right | A menu path |     | File>Save |     |
| ---------------------------------- | ----------- | --- | --------- | --- |
angle bracket
| Bold characters | A dialog button |     | Click OK            |     |
| --------------- | --------------- | --- | ------------------- | --- |
|                 | A tab           |     | Click the Power tab |     |
N‘Rnnnn A number in verilog format, where N is the 4‘b0010, 2‘hF1
total number of digits, R is the radix and n
is a digit.
Text in angle brackets < > A key on the keyboard Press <Enter>, <F1>
Courier New font:
| Plain Courier New | Sample source code   |     | #define START         |     |
| ----------------- | -------------------- | --- | --------------------- | --- |
|                   | Filenames            |     | autoexec.bat          |     |
|                   | File paths           |     | c:\mcc18\h            |     |
|                   | Keywords             |     | _asm, _endasm, static |     |
|                   | Command-line options |     | -Opa+, -Opa-          |     |
|                   | Bit values           |     | 0, 1                  |     |
|                   | Constants            |     | 0xFF, ‘A’             |     |
Italic Courier New A variable argument file.o, where file can be any valid
filename
mcc18 [options] file [options]
| Square brackets [ ] | Optional arguments |     |     |     |
| ------------------- | ------------------ | --- | --- | --- |
Curly brackets and pipe Choice of mutually exclusive arguments; errorlevel {0|1}
| character: { | } | an OR selection                  |     |                          |     |
| ---------------- | -------------------------------- | --- | ------------------------ | --- |
| Ellipses...      | Replaces repeated text           |     | var_name [, var_name...] |     |
|                  | Represents code supplied by user |     | void main (void)         |     |
{ ...
}
1.2  Recommended Reading
This user's guide describes how to use Microchip MPLAB IPE. Other useful documents are listed
below. The following Microchip documents are available and recommended as supplemental
reference resources.
Multi-Tool Design Advisory (DS51764)
 User Guide DS50002227H - 4
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
Introduction
Please read this first! This document contains important information about operational issues that
should be considered when using the MPLAB IPE with your target design.
MPLAB X IDE Online Help
This is an essential document to be used with any Microchip hardware tool.
This is an extensive help file for the MPLAB X IDE. It includes an overview of embedded systems,
installation requirements, tutorials, details on creating new projects, setting build properties,
debugging code, setting configuration bits, setting breakpoints, programming a device, etc. This help
file is generally more up-to-date than the printable PDF of the user’s guide (DS50002027) available
as a free download at www.microchip.com/mplabx/.
Release Notes for MPLAB IPE
For the latest information on using the MPLAB IPE, read the notes under “Release Notes and
Support Documentation” on the MPLAB X IDE Start Page. The release notes contain updated
information and known issues that may not be included in this guide.
MPLAB IPE Online Help File
A comprehensive help file for the MPLAB IPE is included with MPLAB X IDE. This help file may be
more up-to-date than the printed documentation.
Processor Extension Pak and Header Specification (DS50001292)
This booklet describes how to install and use headers. Headers are used to better debug selected
devices, without the loss of pins or resources. See also the PEP and Header online Help file.
Transition Socket Specification (DS51194)
Consult this document for information on transition sockets available for use with headers.
SQTP File Format Specification (DS50002539)
This document shows how a Serial Quick Turn Programming (SQTPSM) file is produced and used by
®
MPLAB IPE Integrated Programming Environment. Engineers can use this information to generate
their own SQTP file.
User Guide DS50002227H - 5
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Overview
2. MPLAB IPE Overview
2.1 IPE Defined
®
The MPLAB Integrated Programming Environment (IPE) is a software application that provides a
simple interface to quickly access key programmer features. The IPE provides a production user
interface for use on the manufacturing floor.
The MPLAB IPE uses the MPLAB X IDE v6.0 or greater framework, Microchip Debugger (MDB)
database, hardware tool interfaces and respective drivers to provide programming capabilities for all
Microchip programmers.
The MPLAB IPE is compatible with any of these platforms:
®
• Microsoft Windows 10 or later
®
• Linux
• macOS™
2.2 Software Installation Requirements
The MPLAB IPE application must be installed on your PC. It is available during the MPLAB X IDE
installation process if the check box is selected (see the setup figure below). You do not need to
install the MPLAB X IDE in order to use the IPE application. However, you may want to refer to
the online help for the MPLAB X IDE for additional information. Also select the check boxes for the
device support you want installed.
User Guide DS50002227H - 6
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Overview
Figure 2-1. Select Applications Dialog
Once you’ve installed the software, the IPE application can be accessed through the MPLAB IPE icon
on your desktop or startup menu.
2.3 Programming Tools Supported
Tools supported in MPLAB X IDE are also supported in MPLAB IPE. To find out which tools are
supported for which devices, refer to the Device Support List.
Gen 5 Tools
The following Gen 5 programming tools work with IPE:
• MPLAB® ICD 5 In-Circuit Debugger - recommended for production programming
• MPLAB® PICKit™ 5 In-Circuit Debugger - recommended for production programming
2.4 IPE Modes
The IPE application operates in two modes:
• Production Mode – in which you can perform production programming operations. By default,
the IPE is in Production Mode when it is launched. The Production Mode capabilities are set from
the Advanced Mode menu discussed in 3.4.6. Production of this document.
• Advanced Mode – a feature-rich GUI interface in which you can view and change the settings for
programming operations, and set up a production user interface for use on the manufacturing
floor. To enable Advanced Mode, see 3.2. Setting Up the Programmer.
User Guide DS50002227H - 7
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
3. General Setup
®
Getting started with the MPLAB IPE is discussed in this chapter.
3.1 Launching the MPLAB IPE Application
After installing the software, double-click the MPLAB IPE application icon located on the desktop.
The MPLAB IPE main window opens.
Figure 3-1. MPLAB IPE Main Window
Multiple Instances of IPE
If you need to have multiple instances of the IPE available, refer to the MPLAB X IDE help. Open
MPLAB X IDE, go to Help>Tool Help Contents>MPLAB X IDE Help and navigate to the “Before You Begin”
section, then “Launch Multiple Instances of the IDE.” The instructions also apply to the IPE.
3.2 Setting Up the Programmer
For programming devices, you can use any of the supported tools (see 2.3. Programming Tools
Supported). Refer to the online help of the selected tool (for example, MPLAB ICD 4, PICkit 4, etc.) for
information on programming a device.
1. Using the Family drop-down menu, select the family of the device you wish to program, then use
the Device drop-down menu to select the device. Or use the Device drop-down menu directly to
select the device.
Note: Selecting the Recently Used option from the Family menu lists the latest 10 devices used
in the Device menu.
User Guide DS50002227H - 8
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
Figure 3-2. Recently Used
2. Click Apply to configure the IPE to the current device (for example, Target Memory Views,
checksum).
3. Connect the development tool to the PC and attach the appropriate target board, device and
power. Refer to the tool’s online help for additional instructions and information on connecting
to target boards, etc.
4. Use the Tool drop-down menu to select the tool you want to use. If more than one development
tool is connected to the PC, select the one you wish to use.
Figure 3-3. Select Tool
5. Click the Connect button (next to the Tool name) to establish a connection between the IPE and
the tool.
6. When the tool is connected, any messages or errors related to this tool will be displayed in the
Output window (refer to the following figure).
User Guide DS50002227H - 9
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
Figure 3-4. Output Window
7. After the tool is successfully connected, proceed to the next chapter to program the device with
the IPE.
3.3 Advanced Mode Login
3.3.1 Logging In
Typically, someone has been authorized to establish the settings that production will use for the
device and tool. To input those settings, log in to the Advanced mode.
Select Settings>Advanced Mode to open the Advanced Mode login dialog. The password is case
sensitive. Type in the default password microchip and click Login.
User Guide DS50002227H - 10
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
Figure 3-5. Advanced Mode Login
3.3.2 Changing the Password
To change the password after the initial log on, click Change Password. A Change Password dialog
opens.
If you forget the new password, click on Forgot Password under the Log in button. The Forgot
Password dialog opens where you can answer the security question used when you changed the
default password (microchip) to a new one. Once you enter the answer, click Submit and it
displays your password.
User Guide DS50002227H - 11
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
3.3.3 Staying Logged In
To start up the MPLAB IPE directly in Advanced mode without entering the password again, type the
password, select the “Keep me logged in” check box, then click Log on. A new installation or first
time usage will launch the MPLAB IPE in basic mode. Once the “Keep me logged in” check box is
selected, subsequent launches will open in Advanced mode.
To cancel the automatic Advanced mode login, click Logout (see figure below) on the Advanced
Settings dialog.
Figure 3-6. Cancel Keep Me Logged In
3.4 Advanced Mode Settings
Advanced mode settings must be set by someone authorized to do so. Some settings that are
selected in these dialogs will allow a production specialist to view and control certain commands
from the IPE Menu bar, Settings menu.
3.4.1 Operate
After validating the password to log in to the Advanced Mode, the dialog opens in the Operate view.
This display is similar to the main display, with the addition of option buttons located along the left
side of the window. The dialog shows the device and tool that has been selected (see Section 2.3
“Setting Up the Programmer”).
User Guide DS50002227H - 12
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
Figure 3-7. Advanced Mode, Operate Dialog
3.4.2 Power
The Power option is available only when a tool is connected. From the Advanced Mode dialog, click
Power to display the available settings. Depending on the tool and the device, only the options
available for that combination display.
Power options will vary for different device families and the tool selected. All of the settings and
parameters are similar to MPLAB X IDE.
Table 3-1. Power Settings
Setting Description
Note: The options available will vary depending on the device and too selected. The following may not show every possible
option.
Voltage Options
V Min/Max This voltage is used by the programmer to verify memory. The value should be the
DD
minimum/maximum voltage for the designated circuit. The default is the device's maximum
voltage value.
V Nom The default value depends on the device. For example, PIC32 has 3.3V as default V Nom.
DD DD
V This is the voltage used to bring the device into a programming mode. Although this is
PP
dependent on the device's programming specification, it can be changed.
V App This is the voltage used by the programmer to verify Flash memory. The default is the
DD
device's nominal voltage value.
Power target circuit from (tool) This setting enables the tool to power the target.
Voltage Level Set the level you want to use.
Programming Options
Programming mode entry Select “Use low voltage programming mode entry” or “Use high voltage programming mode
entry.”
User Guide DS50002227H - 13
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
...........continued
Setting Description
Programming Method Select either “Apply Vdd before Vpp” or “Apply Vpp before Vdd.”
Reset to defaults Returns voltages to their default settings.
3.4.3 Memory
From the Advanced Mode dialog, click Memory to display the available settings for the device
and tool you selected. You can control the memory address and other parameters related to a
programming operation. Some of the options in this window are also available on the main screen,
for viewing and to provide easy access to these settings.
Memory options will vary for different device families and the tool selected. All of the settings and
parameters are similar to MPLAB X IDE.
Note: The memory settings for the MPLAB PM3 Programmer may be different in versions of MPLAB
IPE prior to v3.60.
Table 3-2. Memory Settings
Setting Description
Note: The options available will vary depending on the device and too selected. The following may not show every possible
option.
Allow select memories and Select either “Allow (tool) to Select Memories” or “Manually select memories and ranges.”
ranges
Configuration Memory When selected, this setting allows the tool to program the configuration memory.
Auxiliary Memory When selected, this setting allows the tool to program the auxiliary memory.
Flash Data When selected, this setting allows the tool to program the Flash data.
EEPROM When selected, this setting allows the tool to program the EEPROM.
ID When selected, this setting allows the tool to program the User IDs.
Boot Flash When selected, this setting allows the tool to program the Boot Flash.
Program Memory When selected, this setting allows the tool to program the program memory.
Program Memory Range(s) The address range in Hex of the program space that will be programmed.
(hex)
Preserve Program Memory When selected, this setting allows the tool to preserve the program memory.
If you wish to use any of the Preserve Memory options, first ensure that your code is not
code-protected. For memory to be preserved, the programmer reads the section it needs to
save, performs a bulk erase of the device, reprograms the device and then rewrites the area
that is preserved with what was saved. Therefore, this area cannot be code protected.
Note: The MPLAB PM3 programmer does not support the Preserve Memory options in the
environment .pm3 files.
Preserve Program Memory The address range in Hex of the program space that will be preserved.
Range(s)(hex)
Preserve ID Memory When selected, the ID memory will not be programmed with any new data that is present in
the ID memory. Only available if device has user ID memory.
Note: PIC32M devices do not support preserving user ID or Boot memory.
Reset Returns addresses to default settings.
The MPLAB PM3 programmer does not support the Preserve Memory options in the
environment .pm3 files.
If you wish to use any of the Preserve Memory options, first ensure that your code is not code-
protected. For memory to be preserved, the programmer reads the section it needs to save,
performs a bulk erase of the device, reprograms the device and then rewrites the area that is
preserved with what was saved. Therefore, this area cannot be code protected.
PIC32M devices do not support preserving User ID or Boot Memory.
User Guide DS50002227H - 14
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
3.4.4 Environment
Environments allow you to save settings, so that all of the same settings can be reloaded in another
programming session. Environments are supported, under all tools, as either .pen files or .pm3 files.
Note: MPLAB PM3 programmer does not support the Preserve Memory options in the
environment .pm3 files.
From the Advanced Mode dialog, click Environment to display the available settings.
Table 3-3. Environment Settings
Setting Description
Note: The options available will vary depending on the device and too selected. The following may not show every possible
option.
Create Environment Tab
Environment Information
Name Enter a name for the environment.
.pm3 file For MPLAB device programmers, select this type of. file.
.pen file For MPLAB debuggers or emulators, select this type of file.
Description Enter the description for the environment.
Misc Files Add or remove other files used in the environment, for example, data sheets, instructions, etc.
Multiple files can be selected.
SQTP File Browse or enter the SQTP file name used in the environment.
Save to PM3 Card Saves the environment file to a MPLAB PM3 SD card destination. See ADD LINK TO REFERENCE SECTION
Save Firmware into PM3 SD Card for additional information on saving multiple operating system firmware
to the SD card.
Save to PC Saves the environment file to a destination on the PC.
Copy Opens the Copy Environment dialog to select source and destination for copying the environment.
Browse Environments Tab
Browse on: Select either PC or MPLAB PM3 Card.
PC When the PC is selected, it opens the PM3 Environment file selection browser for you to select an
environment to load into the MPLAB PM3.
MPLAB PM3 Card When this option is selected, it opens the PM3 Card browser for you to select an environment from the
files on the PM3 Card. In the browser, you can:
View the properties of the PM3 SD Card.
Format the PM3 SD card.
Select an environment to load into the MPLAB PM3; the information displays in the Environment Settings
window.
Select an environment to delete from the PM3 Card.
Select an environment to view information; information displays in the Environment Settings window.
Environment Displays information related to the selected environment file such as Name, Path and Environment
Information Description. From here, you can select to clear the information or load the environment into the MPLAB
PM3.
3.4.5 SQTP
SQTP (serial quick turn programming) is used to program a unique serial number into each device.
This number can be used as an entry code, password or ID number. From the Advanced Mode
dialog, click SQTP to display the available settings.
Note: The programmers and tools currently do not support SQTP with serial memory devices.
Therefore, the function to import the SQTP file will not be available.
If using SQTP with MPLAB PM3, see “Using SQTP with MPLAB PM3” below for additional information.
If using PIC32 devices, see “Using SQTP with PIC32 Devices” below for information on the import
methods. For information about how the SQTP files are produced, refer to the SQTP File Format
Specification (DS50002539).
User Guide DS50002227H - 15
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
Table 3-4. SQTP SETTINGS
Setting Description
Note: The options available will vary depending on the device and too selected. The following may not show every possible
option.
Generation Method:
Random Select this option to generate unique, random numbers for each part.
Also enter the start address, number of bytes and number of parts in the corresponding
fields.
Pseudo-Random Select this option to generate a pseudo-random set of non-repeating numbers based on
Seed Value (Hex): the Hex value you enter into the Seed Value field.
Also enter the start address, number of bytes and number of parts in the corresponding
fields.
Sequential Select this option to generate sequential numbers based on the starting value specified
Start Value (Hex): and incrementing each number by the amount specified.
Increment (Dec): Also enter the start address, number of bytes and number of parts in the corresponding
fields.
Configuration:
Start Address (Hex) Enter the starting address (in Hex) for the serial number.
Number of Bytes (Dec) Enter the size of the serial number (in decimal).
Make sure a large enough serial number is specified for the number of parts planned to
program using this file.
Number of parts (Dec) Enter the number of parts to be programmed using this file.
Location:
Program Memory Select this option to load the SQTP number in program memory.
EEPROM Select this option to load the SQTP number in EEPROM.
Auxiliary Memory Select this option to load the SQTP number in auxiliary memory.
User OTP Memory Select this option to load the SQTP number in One-Time Program memory.
User ID Memory Select this option to load the SQTP number in user ID memory.
Boot Memory Select this option to load the SQTP number in boot memory.
Flash Data Select this option to load the SQTP number in Flash memory.
Access Method:
RETLW Select this option to use a series of RETLW (Return Literal W) instructions with the serial
number bytes as the literal data.
Raw Data Select this option to use the raw data.
Format for PSV If the Raw Data option is selected, selecting Format for PSV formats SQTP data to make it
compatible with PSV (Program Space Visibility).
Programming Options:
Disable operations of SQTP Select this option to cease programming if there are no more SQTP values available.
values are exhausted
Display the next SQTP sequence Select this option to display the information in the output window.
in the output window
Generate Click Generate to create the SQTP (.num) file.
Using SQTP with MPLAB PM3
SQTP files for Flash Data memory that were generated prior to MPLAB IPE v2.20 will work with
MPLAB PM3 firmware up to v3.00. SQTP file generation for Flash Data memory has been modified to
the 32-bit byte order (12345678) and the firmware is updated accordingly. A new SQTP file must be
regenerated to work with MPLAB IPE v3.00 and higher.
Using SQTP with PIC32 Devices
User Guide DS50002227H - 16
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
For PIC32 devices only, starting with MPLAB IPE v3.15, a dialog box, similar to the one below, is
provided to choose either 32-bit byte order (12345678) or 16-bit byte order (56781234) when loading
an SQTP file.
Figure 3-8. Import SQTP File Dialog
3.4.6 Production
From the Advanced Mode dialog, click Production to display the available settings.
The Production Settings dialog enables authorized personnel to select the options that are available
during production programming. The options that are selected in the Production Settings (see table
below) determine which commands will be available under the main IPE menu bar’s File, View, and
Settings menus when in Production Mode.
Select the appropriate settings for your production programming project by checking or unchecking
the settings. Selecting a check box in the Production Settings dialog causes a check mark to display
in front of that option under the Settings menu on the main IPE menu bar.
A check mark indicates that an option has been set in the Advanced Mode. If the item is available
and has a check mark, then the production specialist can control this item by toggling it on or off.
Table 3-5. Production Settings
Setting Description
Allow Export Hex This setting enables a production specialist to export Hex files.
If checked, this option displays under the File>Export menu.
Allow Import Hex file Enables a production specialist to import Hex files.
If checked, this option displays under the File>Import menu.
Note: If using a Hex file in the IPE and the file is modified using Notepad, MPLAB X IDE, etc.,
outside of the IPE, a message displays: “File modified. The loaded hex file has been modified
externally. Would you like to reload hex file?”
Auto reset program stats Automatically resets the program statistics counter.
counter
Allow Import Multiple Hex This setting enables a production specialist to import multiple Hex files.
files If checked, this option displays under the File>Import menu.
Allow Import Environment This setting enables a production specialist to import environments.
If checked, this option displays under the File>Import menu.
Allow Import SQTP file This setting enables a production specialist to import SQTP files.
If checked, this option displays under the File>Import menu.
Generate Reports This setting enables reports to be generated.
If Generate Reports is checked, click Browse to set the location where the reports will be
placed.
Limit the Program Count to If selected, this option limits the pass, fail, and total counts to the value that is entered into
the associated field.
This actually halts further programming operations from occurring.
To clear the counts on the main window, click Reset Counters.
User Guide DS50002227H - 17
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
...........continued
Setting Description
Allow “Verify Device ID before This setting activates this option in the Settings menu and enables a production specialist to
Program” under Settings control this option.
menu (Applicable only for This setting is valid only for tools that are capable of performing this function, for example,
PM3) MPLAB PM3.
Allow “Auto Download If selected, this option displays in the Settings menu and can be controlled by a production
Firmware” under Settings specialist.
menu If it is not selected, the IPE automatically downloads the latest firmware for the tool, if
needed.
Allow “Erase All before If selected, this option displays in the Settings menu and can be controlled by a production
Program” under Settings specialist.
menu (Applicable only for If it is not selected, the production specialist cannot control this option from the Settings
PM3 and Gen4) menu.
Note: This option will only be enabled under the Settings menu if the PM3 is connected. For
all other tools, this setting is set to true by default and cannot be changed.
Allow “PM3 Communication” If selected, this option is enabled and can be controlled by a production specialist.
under Settings menu If using the MPLAB PM3 programmer COM port (RS-232), you must select this option in
order to set the appropriate COM port.
Remove Read button from If this option is selected, the Read button is removed from the main window.
main window
Audible notification If selected, this option generates a sound when programming completes successfully.
on successful program
completion
Allow memory editing and Enables memory editing and filling of Execution Memory, Configuration Bits, User ID
filling Memory or Device ID Memory.
If enabled, this option is accessed in Production Mode from the
Window>Target Memory Views option.
Display EEPROM checksum in If selected, the EEPROM checksum is displayed in the output window. “EEPROM checksum”
the output window is the checksum of the EEPROM memory in the MCUs (PIC18F1220 for example) and not the
memory from the exclusive memory devices such as 11AA/LCxxx, 24AA/LC/FCxxx.
Display imported hex file If selected, the non-code protected checksum is displayed in the Results area.
checksum with CP=OFF A checksum is a calculated value (see the device programming specification for calculation)
that should match the value of the programmed device when performing a read of the
device. If selected, the CP=OFF checksum setting displays the checksum of the hex file
with the code protection bit disabled. This allows for a meaningful checksum value for hex
images with enabled code protection bits.
Enable programming If selected,
operations only if hex file is If Hex file is not loaded: All the programming buttons (Program, Read, Erase, Verify, Blank
loaded Check) will be disabled.
If Hex file is loaded, all the programming buttons will be enabled.
Allow Memory View
Program Memory If this option is selected, program memory can be displayed in the Windows>Target Memory
Views on the main window.
Auxiliary Memory If this option is selected, auxiliary memory can be displayed in the Windows>Target Memory
Views on the main window.
User IDs If this option is selected, user IDs can be displayed in the Windows>Target Memory Views on
the main window. This is only applicable if user IDs are supported by the tool.
Config Memory If this option is selected, configuration memory can be displayed in the Windows>Target
Memory Views on the main window.
Flash Data If this option is selected, Flash memory can be displayed in the Windows>Target Memory Views
on the main window.
EEPROM If this option is selected, EEPROM memory can be displayed in the Windows>Target Memory
Views on the main window.
OTP Fuses If this option is selected, OTP fuse memory can be displayed in the Windows > Target
Memory Views on the main window.
User Guide DS50002227H - 18
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
3.4.7 Settings
From the Advanced Mode dialog, click Settings to display the available options. If you are connected
to a Microchip tool there are additional options.
Table 3-6. Special Settings
Settings Description
Note: The options displayed are dependent on the device and tool selected. This table may not show every possible option.
JTAG Communications method
JTAG Method Select 2-wire JTAG or 4-wire JTAG.
Auto Select communication speed Select this check box to auto select the communication speed for J32 Debug Probe.
Communication settings for AVR or SAM devices
Interface Select JTAG or ISP.
Speed (MHz) Type in the appropriate speed.
Programming Options
Allow programing of OTP config Select this check box to enable the OTP config memory for programming.
memory
Erase key with validation 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF
Chip erase type All Memories + NVM configuration rows (ChipErase_ALL)
All Memories excluding BOOT region (ChipErase_S)
All Non Secure Memory Regions excluding BOOT region (ChipErase_NS)
Reset device before or after Select this check box to reset the device before or after programming.
programming
Diagnostics
Logging Level Set the message logging level.
OFF: No logging.
SEVERE: Log severe (error) messages only.
WARNING: Log warning messages only.
INFO: Log informational messages only.
CONFIG: Log configuration information only.
FINE: Log some module-to-module communication.
FINER: Log more module-to-module communication.
FINEST: Log all module-to-module communication.
Log File Path and name of log file.
Tool Pack Selection
Tool pack update options Select from the available options:
Use latest installed tool pack (Recommended).
Use specific tool pack - opens a Select Tool Pack dialog showing the available
version(s).
Specifically selected version Displays the available versions.
Device Pack Selection
Device Packs The device pack for the currently selected device. Changing the device pack selection
is enabled only if the tool is disconnected.
Special Memory Regions
Program Calibration Memory Enables programming of registers used to hold calibration values for a device.
Program/Read User OTP Enables programming or reading of a serial user ID that is OTP (one time
programmable). Once programmed, it cannot be changed.
Secure Segments
User Guide DS50002227H - 19
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
...........continued
Settings Description
Segments to Program Available only for devices with CodeGuard, for example, dsPIC33FJ12GP202.
Select the segments to program:
Full Chip Programming
Boot, Secure and General Segments
Secure and General Segments
General Segment Only
SQTP
Disable operations if SQTP values Selecting the check box prohibits further programming if all SQTP values from the
are exhausted specified .num file have been exhausted.
Display the next SQTP sequence in Select this check box to display the next SQTP sequence in the output window.
the output window
Programming Method
This option allows you to choose the Test mode entry method for devices. This feature is supported by the tools which can
power the target (except for PM3).This setting refers to the order in which the Vpp and Vdd voltages will be applied when
programming/reading the target device.
Apply Vpp before Vdd This is the default setting.
(Recommended)
Apply Vdd before Vpp Caution is recommended when using this setting as it may have adverse side effects.
This option is available only when powering the device from the debug tool.
(Tool) Options
PGC Configuration Select either none, pull up or pull down. The default is pull down.
PGD resistor value (Kohms) Type in a resistor value from 0-50.The default value is 4.7 Kohms.
PGC resistor value (Kohms) Type in a resistor value from 0-50.The default value is 4.7 Kohms.
LED Brightness setting Select the level of brightness from 1 (darkest) to 10 (brightest); the default is 5.
PGD Configuration Select either none, pull up or pull down. The default is pull down.
Program Speed Select either Low, Normal or High. The default is Normal.
Program calibration memory Select if you want to program calibration memory.
Program Options
Erase All Before Program Select this check box to erase all before programming.
Programmer-To-Go
Image Name The default is “<your project name>_ptg,” but you can edit the name. This will be
the folder name on the microSDHC card that contains the appropriate files for
Programmer-To-Go.
Send image to tool The check box is selected by default. With the box checked, the PTG image is created
and then sent to the microSDHC card in the connected MPLAB PICkit 4/5.
Program Device The check box is selected by default. When the check box selected, the device
connected to the MPLAB PICkit 4/5 is programmed.
Note: If both the Send image to tool and Program Device check boxes are unchecked,
see the MPLAB PICkit 4 In-Circuit Debugger User’s Guide topic on “Setting Up PTG Mode
Without a Memory Card.”
User Guide DS50002227H - 20
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
...........continued
Settings Description
Browse PTG Image This option will open a window with a set of options listed related to PTG image.
Once the Browse PTG Image option is selected, the follow options will display:
1. Delete Image: User selected PTG images from checkbox are selected for deletion
of image on SDCard.
2. Refresh Image: SDCard PTG images and its stats are refreshed.
3. Set Active Image: Selected image will be set as active.
4. Reset Stats: Selected image stats will be reset to 0.
5. Title Names:
a. Image Name: PTG image name
b. Total Count: Total number of programming count
c. Pass Count: Passed number of programming count
6. Active Image: Displays the current active image name.
7. Checkbox: Multiple PTG images ca be selected for deletion (refer to 1).
8. Selects the image as active (refer to 3).
9. Close: Closes the PTG window.
10. Select All: Check marked as select all for the deletion of images on the SDCard.
User Guide DS50002227H - 21
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
...........continued
Settings Description
Note: Refer to this image for a visual on what selecting all for the deletion of images will look like on the screen.
Python Script Supported Devices - Programmer-To-Go
Python script enabled devices do not support PTG or the Tool options category. Refer to this list for
Python script-enabled devices:
ATSAML10D14A
ATSAML10D15A
ATSAML10D16A
ATSAML10E14A
ATSAML10E15A
ATSAML10E16A
ATSAML11D14A
ATSAML11D15A
ATSAML11D16A
ATSAML11E14A
ATSAML11E15A
ATSAML11E16A
PIC32CM2532LE00048
PIC32CM2532LE00064
PIC32CM2532LE00100
User Guide DS50002227H - 22
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
General Setup
PIC32CM5164LE00048
PIC32CM5164LE00064
PIC32CM5164LE00100
PIC32CM2532LS00048
PIC32CM2532LS00064
PIC32CM2532LS00100
PIC32CM5164LS00048
PIC32CM5164LS00064
PIC32CM5164LS00100
PIC32CM5164LS60048
PIC32CM5164LS60064
PIC32CM5164LS60100
3.4.8 Logout
After the settings are selected, click Logout to save your settings, exit the Advanced Mode, and
return to the main window.
User Guide DS50002227H - 23
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
4. MPLAB IPE Reference
4.1 IPE Main Window
The following figure shows the main window of the IPE. The IPE Menu bar contains the following
menus, with commands:
• File Menu
• Settings Menu
• View Menu
• Tools Menu
• Window Menu
• Help Menu
Commands are available based on several factors, such as the device selected or the settings
selected in Advanced Mode.
Figure 4-1. IPE Main Window
Table 4-1. IPE Main Window Fields
Item Description
Select Device and Tool:
User Guide DS50002227H - 24
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
...........continued
Item Description
Family Filters devices by family or recently used.
Device Specifies the device; click Apply to select.
Tool Specifies the tool; click Connect or Disconnect as appropriate.
Results:
CP=OFF Checksum This field displays only if enabled in Advanced Mode.
Displays the imported hex checksum as if code protect is off for the device with current memory
contents; value can be copied using CTRL+C.
Checksum Checksum value for the device with current memory contents; value can be copied using CTRL+C.
Pass Count Details the number of programming operations that passed.
Fail Count Details the number of programming operations that failed.
Total Count The total number of programming operations.
Command Buttons:
Program Programs the device.
Erase Erases the device.
Read Reads the device.
Verify Performs a verify operation on the device.
Blank Check Checks whether the device is blank.
Other:
Hex File The Hex file location, Browse to locate the file.
SQTP The SQTP file location, Browse to locate the file.
Output Tab Display of output data.
Right-click in the Output window to access additional options.
Tool Tab Display of specific tool data, for example, PM3, ICD 4, PICkit 4.
4.2 File Menu
On the IPE menu bar, the File menu provides three commands:
• Export
• Import
• Exit
4.2.1 File>Export
The Export menu item allows you to export data from IPE to storage media. By default, these
commands are not available in Production Mode. However, in Advanced Mode, an authorized user
can change the default states of this feature for the Production Mode.
®
File>Export>Hex – this command allows you to export all the memory contents into Intel Hex file
format.
4.2.2 File>Import
The Import menu item allows you to import various files into the IPE. By default, these commands
are not available in Production Mode. However, in Advanced Mode, an authorized user can change
the default states of this feature for the Production Mode.
• File>Import>Environment – select to import (load) the environment (*.pen or .pm3 file).
• File>Import>Hex – select to import a hexadecimal file (*.hex).
User Guide DS50002227H - 25
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
Note: If using a Hex file in the IPE and the file is modified using
Notepad, MPLAB X IDE, etc., outside the IPE, the following message displays:
• File>Import>Multiple Hex – select to import multiple hexadecimal files (*.hex).
Note: If Hex files were generated for individual memories for EEPROM, Flash, etc., these Hex files
can be imported in the MPLAB IPE. These files are loaded in a FIFO (first in, first out) manner.
When loaded into the IPE, the contents are loaded into the respective memory regions of the
selected device. If memory regions overlap, a warning message displays in the Output window.
From the Hex File Selection dialog, click the + button to browse and add files, or click the - button
to remove a file. Select Load to import the files.
• File>Import>SQTP – select to load the SQTP file (*.num file).
4.2.3 File>Exit
This command closes the IPE application.
4.3 Settings Menu
4.3.1 Understanding the Settings Menu Commands
The Settings menu on the IPE Menu bar (see table below) contains commands available for
production personnel. Many of these commands are made available through the Advanced Mode,
Production Mode dialog.
Menu commands are shown as active (black) or unavailable (grayed out).
Active commands with a check mark indicate that the production personnel can control these
settings.
Active commands without a check mark indicate that only authorized personnel can access them.
Unavailable commands with or without a check mark indicate that production personnel cannot
control these settings.
Table 4-2. Settings Menu Commands
Setting Description
Advanced Mode This command opens the Advanced Mode login dialog. Once the login is validated, additional
settings can be set by authorized personnel.
Refer to 3.2. Setting Up the Programmer and 3.4. Advanced Mode Settings for more information.
Verify Device ID Before This command is only appropriate when using devices that have device IDs.
Program
Erase All Before Program This command is used to control whether or not the contents of the device will be erased before
it is programmed.
It is not applicable to One-Time-Programmable (OTP). When the “Erase All Before Program”
command is enabled (check box is selected), the device will be erased before it is programmed.
If it is disabled (unchecked), the device will not be erased before it is programmed.
Auto Download This command is available only for legacy tools (MPLAB ICD 3, PICkit 3 and PM3). If this command
Firmware* is selected, the application verifies that the firmware is the latest available; and if needed,
downloads the newer firmware automatically.
Manual Download This command is available only for legacy tools (MPLAB ICD 3, PICkit 3 and PM3) and enables
Firmware* manual download of firmware. The Firmware Browser dialog opens and locates directory
containing the latest PM3.jar firmware file. Click on the Firmware File, then click OK to download
the firmware.
User Guide DS50002227H - 26
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
...........continued
Setting Description
Save Firmware into SD This command downloads the operating system firmware into an SD Card that has been inserted
Card into the connected MPLAB PM3 programmer. See Section 3.3.2 “Save Firmware into PM3 SD
Card”.
Hold in Reset This command prevents the code from running after programming.
Release from Reset This command removes the Reset and allows the code to run.
PM3 Communication This command is only used with the MPLAB PM3 programmer.
This command opens the PM3 Communication Setting dialog. Use this dialog to set
communications for COM or USB ports. See Section 3.3.3 “PM3 Communication Setting Dialog” for
more information.
*The download of firmware will not occur until the connect/disconnect button is clicked or a
programming operation is performed.
4.3.2 Hold in Reset and Release from Reset
If you do not want your code to execute after you build your application and program the image
into a device, you can select Hold in Reset before running. This feature will persist for any run
command until you select Release from Reset (the button changes to Release from Reset after
Hold in Reset is selected). Then the next run command will allow program execution.
By default in MPLAB X IDE, the code will execute after build and program (Release from Reset).
The methods used for these functions depends on whether the tool is providing power to the target
device or the target is externally powered.
Table 4-3. Hold in Reset/Release from Reset Toggle Button
Button Icon Function Target powered by Tool Target powered by External
Supply
Hold in Reset MCLR driven low MCLR driven low.
Release from Reset MCLR driven to Vdd MCLR Tristated. Target
hardware is responsible for
providing a pull-up on MCLR.
4.3.3 Save Firmware into PM3 SD Card
In production houses, there may be a need to program several different device family architectures
without having access to a computer.
Between MPLAB IPE v3.25 and v3.40, the PM3 operating system was split into two parts based on
the device architecture (32-bit vs all other devices). In MPLAB IPE v3.40, the PM3 operating system
and database are split into three parts based on the architectures for 8-, 16- and 32-bit devices.
MPLAB IPE v3.40 or greater enables you to save the three PM3 operating system firmwares
supporting each of the device family architectures into a PM3 SD card.
Once all the PM3 operating system firmwares are downloaded, when a PM3 environment is selected
in Stand-Alone mode, the MPLAB PM3 programmer will load the correct operating system and
database for the device from the PM3 SD card.
This feature is available only in the MPLAB IPE v3.40 or greater, not in the MPLAB X IDE.
To save all three operating systems into the PM3 SD card:
1. Insert any supported SD card into PM3 SD card slot.
2. Open MPLAB IPE v3.40 or greater and connect the MPLAB PM3 programmer to the computer.
User Guide DS50002227H - 27
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
3. Select Settings>Save firmware into SD Card. The output window in the MPLAB IPE displays
messages when the operating systems and databases for the 8-bit, 16-bit and 32-bit MCUs are
successfully saved onto the SD card.
4.3.3.1 Points To Be Considered:
• Please ensure the PM3 operating system firmware version stored on the SD card matches the
operating system firmware version on the MPLAB PM3 programmer. A mismatch may occur if an
upgrade of the PM3 operating system was performed but the SD card firmware was not updated.
Use the MPLAB IPE v3.40 or greater to select the Settings>Save firmware into SD Card option to
load the PM3 SD card with the desired PM3 operating system firmware version.
• Any firmware versions of v3.40 or greater are not compatible with earlier versions of MPLAB
IPE. It is highly recommended that the MPLAB PM3 use the firmware packaged within the same
MPLAB IPE version.
Version Support
Prior to MPLAB IPE v3.25 One operating system supported.
MPLAB IPE v3.25-3.35 Two operating systems supported (32-bit and all other devices).
MPLAB IPE v3.40 or greater Three operating systems supported (8-, 16-, 32-bit devices).
4.3.4 PM3 Communication Setting Dialog
The PM3 Communication Setting dialog is available under the IPE Menu bar, Settings menu only
when the associated check box for Allow “Communication” under Settings menu is selected in the
Advanced Mode, Production Mode dialog.
The MPLAB PM3 must be connected to the PC, using the appropriate cable, prior to using the PM3
Communication Setting dialog.
This dialog enables selecting the communication port for the MPLAB PM3 programmer through the
IPE.
To use the RS-232 port on the MPLAB PM3, select the COM Port option and use the drop list to select
the available port. Click the refresh button if necessary to view available ports. Click the Test button
to check communication between the IPE and the MPLAB PM3.
To use USB for the communication port, select the USB Port option.
Setting up the COM Port Manually
On some systems, you may need to set up the communications port manually.
On Windows, from the Start menu, select Control Panel, then System and Security. Under the
System settings, click Device Manager. Expand the Ports drop-down list and double-click on the port
you are trying to use. Click the Port Settings tab, and select the following:
Bits per second: 57600 (baud rate)
Data bits: 8
Parity: None
Stop bits: 1
Flow control: Hardware
Click Advanced. Uncheck the Use FIFO buffers check box.
Reboot the PC to implement the change.
4.4 View Menu
The viewable memory types are determined by the Production settings that are selected in the
Advanced Mode. The View menu commands are described below:
• Clear All Memory
• 4.4.1. Memory Settings
User Guide DS50002227H - 28
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
• 4.4.2. Power Settings
• 4.4.3. Transfer from PM3
• 4.4.4. Transfer to PM3
• 4.4.5. Read Device ID
• 4.4.6. View PM3 Socket Info
Clear All Memory
Clears all of the memory views.
4.4.1 Memory Settings
Displays the current memory settings (see example below). The Memory Settings are view-only and
cannot be changed from this window.
Figure 4-2. Memory Settings Display
4.4.2 Power Settings
Displays the current power settings (see example below).
User Guide DS50002227H - 29
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
Figure 4-3. Power Settings Display
4.4.3 Transfer from PM3
When selected, this option transfers the image from the connected MPLAB PM3 Programmer. The
status displays in the Output window.
4.4.4 Transfer to PM3
When selected, this option transfers the image to the connected MPLAB PM3 Programmer. The
status displays in the Output window.
4.4.5 Read Device ID
Displays the device ID of the selected device in the Output window.
4.4.6 View PM3 Socket Info
Displays the PM3 socket information in the Output window.
4.5 Tools Menu
The Tools menu provides access to:
• Device Actions - to access specific actions on the chip for SAMLxx family devices.
• Packs - to access the Pack Manager window for installing/uninstalling DFP & Tools Packs.
• Manage Network Tools - to access a target remotely.
• Plugins - to view your current plugins.
• Plugins Download - to download new plugins.
• Hardware Tool Emergency Boot Firmware Recovery - to reset tool to factory settings.
4.5.1 Device Actions
Device Actions are used to activate specific actions on the SAMLxx family devices. These device
actions are based on the device selected and its applicable device actions are updated dynamically
to the submenu. The device actions list will be empty for non-supported device.
User Guide DS50002227H - 30
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
Figure 4-4. Device Actions Menu
After each device actions operation, the respective message is displayed as shown in the following
table.
Device Actions Description
Set DAL 0 DAL is now 0.
Note: Once the DAL 0 is applied,the device is protected and restrict programming and debug access to
Secure and Non-Secure resources in the system.
Chip Erase_S CE1 Chip Erase Done. DAL is now 1.
Note: The DAL is combined with three key-protected ChipErase commands and DAL value is set
accordingly.
Set DAL 1 DAL is now 1.
Note: Once the DAL 1 is applied, the Secure Memory regions are not allowed to be accessed. For
Non-Secure memory regions, access is limited.
Chip Erase_NS CE0 Chip Erase Done. DAL is now 1.
Note: The DAL is combined with three key-protected ChipErase commands and the DAL value is set
accordingly.
User Guide DS50002227H - 31
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
...........continued
Device Actions Description
Chip Erase_All CE2 Chip Erase Done. DAL is now 2.
Note: The DAL is combined with three key-protected ChipErase commands and the DAL value is set
accordingly.
4.5.2 Packs
The Packs feature allows the user to install or uninstall the respective DFP and Tool Packs from the
Pack Manager window.
Figure 4-5. Packs Menu
Pack Manager Window
1. Select Tools > Packs to open the MPLAB Pack Manager.
2. Go to Pack Manager > Show Packs Compatible With MPLAB X IPE vx.xx where x.xx to see
the current version of the IPE.
3. In the Device Family Pack or Tool Pack tabs, click Update, Install or Uninstall versions.
Note: The number on the tab reflects the number of new DFPs or TPs.
4. Go to the bottom pack locations to see System Packs Location and User Packs Location
displayed.
5. On opening, MPLAB X IPE will look for updates and installations of packs. The results are shown
in the upper right corner of the window.
User Guide DS50002227H - 32
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
Figure 4-6. Pack Manager Window
Installed Pack Locations
Packs are placed in a packs directory of the MPLAB X installation.
For example, in Windows OS: C:\Program Files\Microchip\MPLABX\vx.xx\packs.
Packs may be in a user directory if they are placed after an MPLAB X IPE install.
For example, in Windows OS: C:\User\Microchip\UserName\.mchp-packs.
Note: For more information, refer to the MPLAB X IDE User’s Guide.
Work with Packs on the Command Line
A utility is available for working with packs on the command line. For details, see: C:\Program
Files\Microchip\MPLABX\vx.xx\mplab_platform\bin\packmanager where x.xx is the
MPLAB X IDE version.
4.5.3 Manage Network Tools
The Manage Network Tools dialog is available for the MPLAB ICE 4 emulator. Select Tools>Manage
Network Tools to see the options listed below. Refer to the MPLAB ICE 4 In-Circuit Emulator User's
Guide for more information.
User Guide DS50002227H - 33
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
Figure 4-7. Manage Network Tools
Selecting WiFi or Ethernet communication instead of USB has several uses:
- Access a target remotely. The emulator and target can be in one location and a PC in another.
- Isolate the target. Targets that need to be in a controlled environment can be separate from the PC
location.
Table 4-4. Manage Network Tools Dialog
Option Description
Configure Tools For Network Usage
Network Capable Tools Plugged Into USB: Begin with the USB (default) connection. Then switch to
Ethernet or Wifi.
Configure Default Connection Type for Selected Tool
• USB Default. USB 3.0, USB 2.0
• Ethernet (Wired/DHCP/APIAP) Direct or via access point
• WiFi-AP WiFi Access Point (WiFi-AP) mode allows the emulator to
create its own network (like a router) and have other devices
(e.g., a laptop) connect to it. Use this mode to access the
emulator and target via a PC within the range of the WiFi
signal.
Direct or via network
• Ethernet (Wired/StaticIP) Enter address for the appropriate type:
• Static IP Address
• Gateway
• Subnet Mask
• WiFi-STA (2.4 GHz) Enter the appropriate entries:
• Network SSID
• Security Type
• User Name
• Password
User Guide DS50002227H - 34
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
...........continued
Option Description
Update Connection Type Click to update changes.
Selectable Network Tools
Disable All Network Tool Discovery/Access Select the checkbox to disable.
Active Discovered Network Tools Lists the discovered tools. Click Rescan to update the list.
Name - type in the field, then click Update Name.
Use Type and Serial Number for Name checkbox - select to
use instead of entering a name.
Found at IP Address - enter address
User Specified Network Tools Lists the tools. Click New to add or select a tool and click
Remove to delete.
Use Type and Serial Number for Name checkbox - select to
use instead of entering a name.
Found at IP Address - enter address. Click Renew once
entered.
4.5.4 Plugins
The Tools menu provides access to Plugins. Select Plugins to display the Plugins Manager. For
details, see the topic: Manage Plug-ins found in microchipdeveloper.com/mplabx:plugins. If MPLAB X
IDE is installed, see the MPLAB X IDE Help file, Additional Tasks, Add PlugIn Tools.
4.5.5 Plugins Download
Figure 4-8. Download Plugins Dialog
4.5.6 Hardware Tool Emergency Firmware Boot Recovery Utility
Only use this utility to restore hardware tool boot firmware to its factory state. Use
WARNING
only if your hardware tool no longer functions on any machine.
The hardware tool may need to be forced into recovery boot mode (reprogrammed) in rare
situations; for example, if any of the following occurs when the tool is connected to the computer:
• If the tool has no LED lit.
• If the procedure described in 4.5.6. Hardware Tool Emergency Firmware Boot Recovery Utility
was not successful.
YOU MUST USE MPLAB X IDE V4.15 OR GREATER TO USED THE EMERGENCY RECOVERY UTILITY.
User Guide DS50002227H - 35
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
Carefully follow the instructions found in MPLAB X IDE under the main menu options Debug >
Hardware Tool Emergency Boot Firmware Recovery.
If the MPLAB X IDE or MPLAB IPE cannot communicate with the debugger, the debugger may need
to be forced into bootload mode (download new firmware). Some possible reasons could be the
following:
• If steps 1-5 in did not correct the debugger issue.
• If the MPLAB X IDE Output window shows an asterisk (*) next to the Application version number,
the debugger’s firmware is not the newest.
This can occur if the Project Properties Firmware options has the “Use Latest Firmware” box
unchecked and there is a new firmware version available with the MPLAB X IDE version.
In this case, check the “Use Latest Firmware” box and click the Refresh Debug Tool Status Icon
in the MPLAB X IDE dashboard display. If there is still an asterisk next to the Application
version number, or the debugger issue is not resolved, proceed to the following steps for
bootload mode.
Perform the following steps to force the debugger into bootload mode:
1. Disconnect the Micro-B USB cable from the debugger.
2. Press down on the MPLAB PICkit 4 logo and hold while plugging in the Micro-B USB cable.
The light strip flashes purple. Continue pressing the logo until the light strip stops flashing and
changes to steady on purple. You are now in bootload mode.
3. Try to reestablish communication with the MPLAB X IDE or MPLAB IPE. If successful, the latest
firmware is downloaded. When complete, the LED is steady on blue and the debugger is ready
for operation.
4.6 Window Menu
4.6.1 Output
This option opens the Output window at the bottom of the display. Right-click the tab title to display
window options, such as Close, Float, Move, etc. Right-click in the body of the window to display
Output window content options, such as Find, Wrap text, etc. See figure below.
User Guide DS50002227H - 36
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
Figure 4-9. Output Window Right-Click Menus
4.6.2 Target Memory Views
This option is available only if Production Settings are set in Advanced Mode to view the different
types of memory. Some of the possible memory views include Execution Memory, Configuration
Bits, User ID Memory, Device ID Memory, OTP fuse, etc.
Figure 4-10. OTP Fuse Memory Option from Menu
Figure 4-11. OTP Fuse Bit Configuration Window
Configured OTP fuse bits are applied from the imported .hex file and can view the settings from the
window below.
User Guide DS50002227H - 37
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
MPLAB IPE Reference
Enable the fuse bits configuration and set the size from the Option field.
4.6.3 Reset Windows
Selecting this option will reset all the program windows to the default settings.
4.7 Help Menu
The Help menu provides access to the following online information:
• Read Me Docs - MPLAB IPE Readme and Programmer Command-line Readme.
• Help Contents - displays the master set of all installed documentation.
• Tool Help Contents - lists help for several Microchip tools.
• About - displays information specific to the current version of MPLAB IPE.
User Guide DS50002227H - 38
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
Revision History
5. Revision History
5.1 Revision A (December 2013)
Initial release of this document.
5.2 Revision B (August 2015)
Modified “Software Installation Requirements”. The IPE is now a separate installation than the
MPLAB X IDE.
Modified the description of Production Mode.
In the General Setup chapter:
• Added information on new features: Recently Used option in the Family list of devices and
Creating Desktop Shortcuts.
• Added information on Preserve Memory options.
• Added notes regarding MPLAB PM3 programmer environment files.
• Added a note in the description of the Allow Import Hex file option.
• Added information regarding using the MPLAB PM3 programmer with the option Allow
“Communication” under Settings menu.
• Added Special Memory Regions information.
In The MPLAB IPE Reference chapter:
• Added a note regarding the File>Import>Hex option.
5.3 Revision C (March 2017)
• Added Note with location of the Readme file for MPLAB IPE in “Software Installation
Requirements”.
• Added a “Staying Logged In” topic to the Advanced Mode Login section.
• Updated memory range descriptions.
• Updated environment settings options.
• Revised “SQTP” section and added sections for using SQTP with MPLAB PM3 and with PIC32
devices.
• Added new SQTP setting.
• Updated field descriptions to the main IPE window.
• Added new Read Device ID option to the View menu.
• Added new settings menu command for saving firmware into SD card and added a revised
information to “Save Firmware into PM3 SD Card”.
5.4 Revision D (June 2018)
• In the Preface, added compatibility note that this document reflects the changes as of MPLAB X
IDE v4.20 or greater.
• Multiple updates throughout to reflect changes made to the program for the NetBeans platform.
Added Tools and Windows menus, updated graphics, text, and menu options.
5.5 Revision E (April 2020)
• Entire document has been reformatted and renumbered.
• In the Preface, added compatibility note that this document reflects the changes as of MPLAB X
IDE v5.40 or greater.
User Guide DS50002227H - 39
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
Revision History
• Replaced screen for Select Applications Dialog in the “Software Installation Requirements”
section.
• Removed the “Feature Matrix” section.
• Added a new heading for “Multiple Instances of IPE” in Launching the MPLAB IPE Application
section.
• Replaced screen for Advanced Mode Login and added screen for Change Password and Forgot
Password dialogs.
• Updated Production Settings table.
• Updated Special Settings table, added information for tool and device packs and other options
including Programmer-To-Go, JTAG, etc. Also removed PM3 program speed option and screen.
5.6 Revision F (December 2021)
• Updated Tools menu to add options for Manage Network Tools, Download Plugins and Hardware
Tool Emergency Boot Firmware Recovery.
• Added support information for MPLAB ICE 4 Emulator.
5.7 Revision G (November 2022)
• Updated Tools menu to add Packs Manager feature.
• Added screenshots and steps for navigating the Packs menu and Pack manager window.
• Updated Window menu to document OTP fuse support.
• Updated Settings menu to move options from Program to Programming.
5.8 Revision H (April 2023)
Under Advanced Mode Settings:
• Updated Programming Tools Supported to reflect Gen 5 tools.
• Updated Special Settings section to reflect Erase All Before Program option.
• Updated Special Settings section to reflect Browse PTG Image functionality.
• Added section about Python script-enabled devices.
User Guide DS50002227H - 40
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
Support
6. Support
Please refer to the items discussed here for support issues.
• 6.1. Warranty Registration
• 6.2. Personalized Notification Service
6.1 Warranty Registration
If your development tool package includes a Warranty Registration Card, please complete the card
and mail it in promptly. Sending in your Warranty Registration Card entitles you to receive new
product updates. Interim software releases are available at the Microchip web site.
6.2 Personalized Notification Service
Microchip's personal notification service helps keep customers current on their Microchip products
of interest. Subscribers will receive e-mail notification whenever there are changes, updates,
revisions or errata related to a specified product family or development tool.
Please visit http://www.microchip.com/pcn to begin the registration process and select your
preferences to receive personalized notifications. A FAQ and registration details are available on
the page, which can be opened by selecting the link above.
When you are selecting your preferences, choosing “Development Systems” will populate the list
with available development tools. The main categories of tools are listed below:
• Compilers – The latest information on Microchip C compilers, assemblers, linkers and other
language tools. These include all MPLAB C compilers; all MPLAB assemblers (including MPASM™
assembler); all MPLAB linkers (including MPLINK™ object linker); and all MPLAB librarians
(including MPLIB™ object librarian).
• Emulators – The latest information on Microchip in-circuit emulators.These include the MPLAB
REAL ICE in-circuit emulators
• In-Circuit Debuggers – The latest information on Microchip in-circuit debuggers. These include
the MPLAB ICD 3 and MPLAB ICD 4 in-circuit debuggers and PICkit™ 3 and MPLAB PICkit 4
in-circuit debuggers.
• MPLAB® X IDE – The latest information on Microchip MPLAB X IDE, the multi-platform (Windows®,
macOS™, Linux®) Integrated Development Environment for development systems tools.
• Programmers – The latest information on Microchip programmers. These include the device
(production) programmers MPLAB REAL ICE in-circuit emulator, MPLAB ICD 4 in-circuit debugger,
MPLAB PICkit 4 in-circuit debugger, MPLAB PM3 and development (non-production) programmer
and PICkit 3.
• Starter/Demo Boards – These include MPLAB Starter Kit boards, PICDEM demo boards, and
various other evaluation boards.
User Guide DS50002227H - 41
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
The Microchip Website
Microchip provides online support via our website at www.microchip.com/. This website is used to
make files and information easily available to customers. Some of the content available includes:
• Product Support – Data sheets and errata, application notes and sample programs, design
resources, user’s guides and hardware support documents, latest software releases and archived
software
• General Technical Support – Frequently Asked Questions (FAQs), technical support requests,
online discussion groups, Microchip design partner program member listing
• Business of Microchip – Product selector and ordering guides, latest Microchip press releases,
listing of seminars and events, listings of Microchip sales offices, distributors and factory
representatives
Product Change Notification Service
Microchip’s product change notification service helps keep customers current on Microchip
products. Subscribers will receive email notification whenever there are changes, updates, revisions
or errata related to a specified product family or development tool of interest.
To register, go to www.microchip.com/pcn and follow the registration instructions.
Customer Support
Users of Microchip products can receive assistance through several channels:
• Distributor or Representative
• Local Sales Office
• Embedded Solutions Engineer (ESE)
• Technical Support
Customers should contact their distributor, representative or ESE for support. Local sales offices are
also available to help customers. A listing of sales offices and locations is included in this document.
Technical support is available through the website at: www.microchip.com/support
User Guide DS50002227H - 42
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
Product Identification System
To order or obtain information, e.g., on pricing or delivery, refer to the factory or the listed sales
office.
PART NO. [X](1) - X /XX XXX
Device Tape and Reel Temperature Package Pattern
Option Range
Device: PIC16F18313, PIC16LF18313, PIC16F18323, PIC16LF18323
Tape and Reel Option: Blank = Standard packaging (tube or tray)
T = Tape and Reel(1)
Temperature Range: I = -40°C to +85°C (Industrial)
E = -40°C to +125°C (Extended)
Package:(2)   JQ = UQFN
 
P = PDIP
ST = TSSOP
SL = SOIC-14
SN = SOIC-8
RF = UDFN
Pattern: QTP, SQTP, Code or Special Requirements (blank otherwise)
Examples:
• PIC16LF18313- I/P Industrial temperature, PDIP package
• PIC16F18313- E/SS Extended temperature, SSOP package
Notes:
1. Tape and Reel identifier only appears in the catalog part number description. This identifier is
used for ordering purposes and is not printed on the device package. Check with your Microchip
Sales Office for package availability with the Tape and Reel option.
2. Small form-factor packaging options may be available. Please check www.microchip.com/
packaging for small-form factor package availability, or contact your local Sales Office.
Microchip Devices Code Protection Feature
Note the following details of the code protection feature on Microchip products:
• Microchip products meet the specifications contained in their particular Microchip Data Sheet.
• Microchip believes that its family of products is secure when used in the intended manner, within
operating specifications, and under normal conditions.
• Microchip values and aggressively protects its intellectual property rights. Attempts to breach the
code protection features of Microchip product is strictly prohibited and may violate the Digital
Millennium Copyright Act.
• Neither Microchip nor any other semiconductor manufacturer can guarantee the security of its
code. Code protection does not mean that we are guaranteeing the product is “unbreakable”.
Code protection is constantly evolving. Microchip is committed to continuously improving the
code protection features of our products.
Legal Notice
This publication and the information herein may be used only with Microchip products, including
to design, test, and integrate Microchip products with your application. Use of this information

User Guide DS50002227H - 43
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
in any other manner violates these terms. Information regarding device applications is provided
only for your convenience and may be superseded by updates. It is your responsibility to ensure
that your application meets with your specifications. Contact your local Microchip sales office for
additional support or, obtain additional support at www.microchip.com/en-us/support/design-help/
client-support-services.
THIS INFORMATION IS PROVIDED BY MICROCHIP "AS IS". MICROCHIP MAKES NO REPRESENTATIONS
OR WARRANTIES OF ANY KIND WHETHER EXPRESS OR IMPLIED, WRITTEN OR ORAL, STATUTORY
OR OTHERWISE, RELATED TO THE INFORMATION INCLUDING BUT NOT LIMITED TO ANY IMPLIED
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
PURPOSE, OR WARRANTIES RELATED TO ITS CONDITION, QUALITY, OR PERFORMANCE.
IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL, OR
CONSEQUENTIAL LOSS, DAMAGE, COST, OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
INFORMATION OR ITS USE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW,
MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THE INFORMATION OR
ITS USE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO
MICROCHIP FOR THE INFORMATION.
Use of Microchip devices in life support and/or safety applications is entirely at the buyer's risk,
and the buyer agrees to defend, indemnify and hold harmless Microchip from any and all damages,
claims, suits, or expenses resulting from such use. No licenses are conveyed, implicitly or otherwise,
under any Microchip intellectual property rights unless otherwise stated.
Trademarks
The Microchip name and logo, the Microchip logo, Adaptec, AVR, AVR logo, AVR Freaks, BesTime,
BitCloud, CryptoMemory, CryptoRF, dsPIC, flexPWR, HELDO, IGLOO, JukeBlox, KeeLoq, Kleer,
LANCheck, LinkMD, maXStylus, maXTouch, MediaLB, megaAVR, Microsemi, Microsemi logo, MOST,
MOST logo, MPLAB, OptoLyzer, PIC, picoPower, PICSTART, PIC32 logo, PolarFire, Prochip Designer,
QTouch, SAM-BA, SenGenuity, SpyNIC, SST, SST Logo, SuperFlash, Symmetricom, SyncServer,
Tachyon, TimeSource, tinyAVR, UNI/O, Vectron, and XMEGA are registered trademarks of Microchip
Technology Incorporated in the U.S.A. and other countries.
AgileSwitch, APT, ClockWorks, The Embedded Control Solutions Company, EtherSynch, Flashtec,
Hyper Speed Control, HyperLight Load, Libero, motorBench, mTouch, Powermite 3, Precision Edge,
ProASIC, ProASIC Plus, ProASIC Plus logo, Quiet- Wire, SmartFusion, SyncWorld, Temux, TimeCesium,
TimeHub, TimePictra, TimeProvider, TrueTime, and ZL are registered trademarks of Microchip
Technology Incorporated in the U.S.A.
Adjacent Key Suppression, AKS, Analog-for-the-Digital Age, Any Capacitor, AnyIn, AnyOut,
Augmented Switching, BlueSky, BodyCom, Clockstudio, CodeGuard, CryptoAuthentication,
CryptoAutomotive, CryptoCompanion, CryptoController, dsPICDEM, dsPICDEM.net, Dynamic
Average Matching, DAM, ECAN, Espresso T1S, EtherGREEN, GridTime, IdealBridge, In-Circuit Serial
Programming, ICSP, INICnet, Intelligent Paralleling, IntelliMOS, Inter-Chip Connectivity, JitterBlocker,
Knob-on-Display, KoD, maxCrypto, maxView, memBrain, Mindi, MiWi, MPASM, MPF, MPLAB Certified
logo, MPLIB, MPLINK, MultiTRAK, NetDetach, Omniscient Code Generation, PICDEM, PICDEM.net,
PICkit, PICtail, PowerSmart, PureSilicon, QMatrix, REAL ICE, Ripple Blocker, RTAX, RTG4, SAM-
ICE, Serial Quad I/O, simpleMAP, SimpliPHY, SmartBuffer, SmartHLS, SMART-I.S., storClad, SQI,
SuperSwitcher, SuperSwitcher II, Switchtec, SynchroPHY, Total Endurance, Trusted Time, TSHARC,
USBCheck, VariSense, VectorBlox, VeriPHY, ViewSpan, WiperLock, XpressConnect, and ZENA are
trademarks of Microchip Technology Incorporated in the U.S.A. and other countries.
SQTP is a service mark of Microchip Technology Incorporated in the U.S.A.
The Adaptec logo, Frequency on Demand, Silicon Storage Technology, and Symmcom are registered
trademarks of Microchip Technology Inc. in other countries.
User Guide DS50002227H - 44
© 2023 Microchip Technology Inc. and its subsidiaries

MPLAB IPE User's Guide
GestIC is a registered trademark of Microchip Technology Germany II GmbH & Co. KG, a subsidiary
of Microchip Technology Inc., in other countries.
All other trademarks mentioned herein are property of their respective companies.
© 2023, Microchip Technology Incorporated and its subsidiaries. All Rights Reserved.
ISBN: 978-1-6683-2375-5
AMBA, Arm, Arm7, Arm7TDMI, Arm9, Arm11, Artisan, big.LITTLE, Cordio, CoreLink, CoreSight, Cortex,
DesignStart, DynamIQ, Jazelle, Keil, Mali, Mbed, Mbed Enabled, NEON, POP, RealView, SecurCore,
Socrates, Thumb, TrustZone, ULINK, ULINK2, ULINK-ME, ULINK-PLUS, ULINKpro, µVision, Versatile
are trademarks or registered trademarks of Arm Limited (or its subsidiaries) in the US and/or
elsewhere.
Quality Management System
For information regarding Microchip’s Quality Management Systems, please visit
www.microchip.com/quality.
User Guide DS50002227H - 45
© 2023 Microchip Technology Inc. and its subsidiaries

Worldwide Sales and Service
| AMERICAS | ASIA/PACIFIC | ASIA/PACIFIC | EUROPE |
| -------- | ------------ | ------------ | ------ |
Corporate Office Australia - Sydney India - Bangalore Austria - Wels
2355 West Chandler Blvd. Tel: 61-2-9868-6733 Tel: 91-80-3090-4444 Tel: 43-7242-2244-39
Chandler, AZ 85224-6199 China - Beijing India - New Delhi Fax: 43-7242-2244-393
Tel: 480-792-7200 Tel: 86-10-8569-7000 Tel: 91-11-4160-8631 Denmark - Copenhagen
Fax: 480-792-7277 China - Chengdu India - Pune Tel: 45-4485-5910
Technical Support: Tel: 86-28-8665-5511 Tel: 91-20-4121-0141 Fax: 45-4485-2829
www.microchip.com/support China - Chongqing Japan - Osaka Finland - Espoo
Web Address: Tel: 86-23-8980-9588 Tel: 81-6-6152-7160 Tel: 358-9-4520-820
www.microchip.com China - Dongguan Japan - Tokyo France - Paris
Atlanta Tel: 86-769-8702-9880 Tel: 81-3-6880- 3770 Tel: 33-1-69-53-63-20
Duluth, GA China - Guangzhou Korea - Daegu Fax: 33-1-69-30-90-79
Tel: 678-957-9614 Tel: 86-20-8755-8029 Tel: 82-53-744-4301 Germany - Garching
Fax: 678-957-1455 China - Hangzhou Korea - Seoul Tel: 49-8931-9700
Austin, TX Tel: 86-571-8792-8115 Tel: 82-2-554-7200 Germany - Haan
Tel: 512-257-3370 China - Hong Kong SAR Malaysia - Kuala Lumpur Tel: 49-2129-3766400
Boston Tel: 852-2943-5100 Tel: 60-3-7651-7906 Germany - Heilbronn
Westborough, MA China - Nanjing Malaysia - Penang Tel: 49-7131-72400
Tel: 774-760-0087 Tel: 86-25-8473-2460 Tel: 60-4-227-8870 Germany - Karlsruhe
Fax: 774-760-0088 China - Qingdao Philippines - Manila Tel: 49-721-625370
Chicago Tel: 86-532-8502-7355 Tel: 63-2-634-9065 Germany - Munich
| Itasca, IL | China - Shanghai | Singapore | Tel: 49-89-627-144-0 |
| ---------- | ---------------- | --------- | -------------------- |
Tel: 630-285-0071 Tel: 86-21-3326-8000 Tel: 65-6334-8870 Fax: 49-89-627-144-44
Fax: 630-285-0075 China - Shenyang Taiwan - Hsin Chu Germany - Rosenheim
Dallas Tel: 86-24-2334-2829 Tel: 886-3-577-8366 Tel: 49-8031-354-560
Addison, TX China - Shenzhen Taiwan - Kaohsiung Israel - Ra’anana
Tel: 972-818-7423 Tel: 86-755-8864-2200 Tel: 886-7-213-7830 Tel: 972-9-744-7705
Fax: 972-818-2924 China - Suzhou Taiwan - Taipei Italy - Milan
Detroit Tel: 86-186-6233-1526 Tel: 886-2-2508-8600 Tel: 39-0331-742611
Novi, MI China - Wuhan Thailand - Bangkok Fax: 39-0331-466781
Tel: 248-848-4000 Tel: 86-27-5980-5300 Tel: 66-2-694-1351 Italy - Padova
Houston, TX China - Xian Vietnam - Ho Chi Minh Tel: 39-049-7625286
Tel: 281-894-5983 Tel: 86-29-8833-7252 Tel: 84-28-5448-2100 Netherlands - Drunen
| Indianapolis      | China - Xiamen      |     | Tel: 31-416-690399   |
| ----------------- | ------------------- | --- | -------------------- |
| Noblesville, IN   | Tel: 86-592-2388138 |     | Fax: 31-416-690340   |
| Tel: 317-773-8323 | China - Zhuhai      |     | Norway - Trondheim   |
| Fax: 317-773-5453 | Tel: 86-756-3210040 |     | Tel: 47-72884388     |
| Tel: 317-536-2380 |                     |     | Poland - Warsaw      |
| Los Angeles       |                     |     | Tel: 48-22-3325737   |
| Mission Viejo, CA |                     |     | Romania - Bucharest  |
| Tel: 949-462-9523 |                     |     | Tel: 40-21-407-87-50 |
| Fax: 949-462-9608 |                     |     | Spain - Madrid       |
| Tel: 951-273-7800 |                     |     | Tel: 34-91-708-08-90 |
| Raleigh, NC       |                     |     | Fax: 34-91-708-08-91 |
| Tel: 919-844-7510 |                     |     | Sweden - Gothenberg  |
| New York, NY      |                     |     | Tel: 46-31-704-60-40 |
| Tel: 631-435-6000 |                     |     | Sweden - Stockholm   |
| San Jose, CA      |                     |     | Tel: 46-8-5090-4654  |
| Tel: 408-735-9110 |                     |     | UK - Wokingham       |
| Tel: 408-436-4270 |                     |     | Tel: 44-118-921-5800 |
| Canada - Toronto  |                     |     | Fax: 44-118-921-5820 |
Tel: 905-695-1980
Fax: 905-695-2078
 User Guide DS50002227H - 46
© 2023 Microchip Technology Inc. and its subsidiaries