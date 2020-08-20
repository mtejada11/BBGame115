# BBGame115

BBGame115 is an electronic game based on the "breadboard game" BBGame114. Because [BBGame114](https://github.com/mtejada11/BBGame114/wiki) is built on a breadboard, it's limited to a matrix of 11x4 LEDs. BBGame115 is built on a printed circuit board (PCB), and the size of its matrix is 11x5 LEDs. The extra row of LEDs mainly improves the display of dot-matrix text.

The BBGame115 PCB already has all the electrical connections as traces, so there is no need for wires. However, all 55 LEDs must be soldered on to the PCB. The Arduino Nano microcontroller, 3 pushbuttons, 8 resistors and the piezoelectric speaker also need to be soldered on to the PCB.

<img src="https://github.com/mtejada11/BBGame115/raw/master/PCB/bbgame115_pcb_assembled.png" width="800" alt="BBGame115 assembled on PCB">
*Diagram of BBGame115 assembled on PCB*<br>
<br>
<img src="https://github.com/mtejada11/BBGame115/raw/master/PCB/bbgame115_pcb_schematic.png" width="800" alt="BBGame115 circuit schematic">
*Circuit schematic diagram*<br>

# How to Order a PCB

This repository includes the [BBGame PCB Gerber files .zip archive](https://github.com/mtejada11/BBGame115/raw/master/PCB/bbgame115_pcb_v2_4_gerber.zip) used to manufacture the PCB. Download this file and submit it to an online PCB manufacturing service. See the [How to Order a BBGame115 PCB](https://github.com/mtejada11/BBGame115/wiki/How-to-Order-a-BBGame115-PCB) page for more details. 

The [BBGame115Lib.zip](https://github.com/mtejada11/BBGame115/raw/master/Lib/BBGame114Lib.zip?raw=true) library for Arduino included in this repository is a library that allows the BBGame115 device to be programmed with higher level methods/functions than the Arduino `digitalWrite` and `digitalRead` functions. Refer to the [BBGame114Lib Library Reference](https://github.com/mtejada11/BBGame114/wiki/BBGame114Lib-Library-Reference) page for more information on this library. The interfaces for the BBGame114 and BBGame115 are identical, and there are just a few differences in the libraries' internal code. 

# BBGame115 Arduino Library

The [BBGame115Lib.zip](https://github.com/mtejada11/BBGame115/raw/master/Lib/BBGame114Lib.zip?raw=true) library for Arduino included in this repository is a library that allows the BBGame115 device to be programmed with higher level methods/functions than the Arduino `digitalWrite` and `digitalRead` functions. Refer to the [BBGame114Lib Library Reference](https://github.com/mtejada11/BBGame114/wiki/BBGame114Lib-Library-Reference) page for more information on this library. The interfaces for the BBGame114 and BBGame115 are identical, and there are just a few differences in the libraries' internal code. 
