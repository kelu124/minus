A RP2040-BASED ULTRASOUND PULSE-ECHO ACQUISITION DEVICE

A MODULAR OPEN-SOURCE DEVICE FOR ULTRASOUND RESEARCH

Luc Jonveaux∗
Tinkerer, Milly le Meugon, France
contact@un0rick.cc

April 13, 2024

ABSTRACT

After a couple of iterations for single-element ultrasound pulse-echo devices, the pic0rick choses
simplicity to reach a modular design, allowing for bipolar pulser, fast acquisition and relatively simple,
barebone design. No FPGA, no BGA, plain old raspberry pico.

Keywords arduino · open-source · ultrasound · single element · pulse echo · hardware · rp2040 · lowtech

This PDF is also a ZIP that contains the sources to the hardware and some data too, don’t hesitate to have a look. Just
rename the file from .PDF to .ZIP and you’re ready to go .

1 Overview

The pic0rick is a very central board for an ultrasound pulse-echo system. It is composed of a main board, based on the
famous rp2040 and easy to solder SMD, to which a single, and a double PMOD connector can connect to addons:

• The main board is equipped with a 60Msps, 10bit ADC. Front end is protected against high-voltage pulses, and
features a proven time-gain compensation system consisting in a AD8331(55.5dB) with a controlling (MCP4812)
SPI DAC. PCB is 4 layers, single face - with only large SMD passives, and no BGA.

• The single PMOD connector can plug to the Pulser board, which can be equipped with a simple +-25V high-voltage
(HV) generation board. Together, they generate the pulse on behalf of the pic0rick main board. The setup can
generate three-level pulses ( with a pair of MD1210 + TC6320 ). HV board can be swapped easily.

• The double PMOD connector can be used for virtually anything. The current code allows for a VGA to be
connected, which displays acquisitions from the board. There is also a 8 MB PSRAM module for more RAM.

The current system uses both PIOs (one for the acquisition, the other for the VGA) which leaves the other resources of the
rp2040 relatively free to use for your own priorities.

Figure 1: Setup of the boards (main, pulser, hv) and resulting acquisition. VGA PMOD not connected.

∗More on the website http://un0rick.cc. This paper has its on Zenodo DOI 10.5281/zenodo.10968504

PIC0RICK DOCUMENTATION - APRIL 13, 2024

2 Where to find the latest sources

The latest sources of the hardware as well as software are available at https://github.com/kelu124/pic0rick/.
However, this PDF also doubles as an archive (you can rename the .pdf as a .zip, and you’ll see), and contains, in short:
a set of gerbers and BOM, and some documentation. There may be some other stuff there, but I forgot what I put there.
Published documents include:

• KiCad design files for the main board
• KiCad design files for the pulser + hv boards
• rp2040 firmware for the microcontroller.

3 Next steps

Plenty to do on the next steps. The current shopping list (non-exhaustive) may include:

• Hardware: Slight tweaks on the main board to allow more space for the PMODs, include OSHWA certfication

number, ..

• Firmware: Tie the pulses to the PIO code so that pulses strictly cohappen with the acquisition start

4 Links to go further

• Come and chat : join the Slack channel
• The full GitHub repository for the pic0rick "motherboard".
• The board’s Tindie shop to get it
• Check out my previous work on the topic of ultrasound modules [4] and its dataset on Zenodo. More to come!

License

This work is based on previous projects, the un0rick, lit3rick and the echOmods projects. The pic0rick project and its
boards are open hardware and software, developed with open-source elements.

Copyright Luc Jonveaux / kelu124 (kelu124@gmail.com) 2024

• The hardware is licensed under TAPR Open Hardware License (www.tapr.org/OHL)
• The software components are free software: you can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

• The documentation is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License.

References

[1] Luc Jonveaux 2017. Arduino-like development kit for single-element ultrasound imaging. In Journal of Open Hardware,

1(1), p.3. DOI: 10.5334/joh.2

[2] Luc Jonveaux 2019. un0rick : open-source fpga board for single element ultrasound imaging On Zenodo. DOI:

10.5281/zenodo.3364559

[3] Luc Jonveaux 2021. lit3rick: an up5k ultrasound pulse-echo device On Zenodo. DOI: 10.5281/zenodo.5792245
[4] Luc Jonveaux, Carla Schloh, William Meng, Jorge Arija, Jean Rintoul 2024. Review of Current Simple Ultrasound
Hardware Considerations, Designs, and Processing Opportunities On Journal of Open Hardware (JOH) . DOI:
10.5334/joh.28

[5] Luc Jonveaux 2021. An opensource max14866 development board On Zenodo. DOI: 10.5281/zenodo.5792252

2

