# ATtiny85 Mini Clock
#### A very basic clock in a small form factor 
#### Features
+ 
+ Accounts for Daylight Savings Time (DST)
## Introduction
There are hundreds if not thousands of online of digital clock builds. They usually multifunctional with [].
This project will aim to show not only how to build a very minimalistic clock using an ATtiny, but how display drivers actually work along with how to build your own 'barebone' versions of common drivers. With that being said, there will be multiple options in how to build a digital.
## Component List
+ Attiny85
+ Breadboard
+ A display (module or barbone)
+ RTC (module or barebone)
+ Attiny85 Programmer or Arduino Uno
+ 10uF Capacitor (if not using programmer)

## Choosing a display
If you are unfamiliar with 7-Segment displays, they are simply a cluster of LEDS organized in such a way that each represents a segment that can then be manipulated to display alpha-numeric data. Each LED can be individually triggered by setting its corresponding pin to logic HIGH (i.e. VCC) or logic LOW (i.e. GND) depending on the type of display. When working with 7-Segment displays alongside microcontrollers, we typically utilize display modules which provide a 'brain' for the display. You may be wondering why do we even require modules to control a 7-Segment display. In essence, it makes interfacing with them much easier and thus makes our lives much easier. Namely, it reduces the number of pins required to control a 7-Segment display. These displays typically contain anywhere from () to () pins and thus require many I/0 pins on a microcontroller whereas a module reduces the number of required I/O pins down to just 3 or 2! Also, for the purposes of this project, it is necessary to use a module because there is not enough pins on the ATtiny to connect each pin of a 7-Segment display. The modules that we will explore today are the TM1637 and MAX7219 display drivers. We will also explore how to build our own barebone versions of each driver.

*TM1637 Display (Module)*
Perhaps the most common module to drive a 7-Segment display is the TM1637 display driver. It requires just two pins (aside from VCC and GND) to control and thus makes it easy to use with an ATtiny85.
<p align="center">
  <img src="https://github.com/NeonVulture/Arduino-Projects/blob/main/ATtiny85-Mini-Clock/Assets/Supplemental_Images/TM1637_Display_Module.jpg?raw=true" alt="TM1637 Module"/>
</p>
This module is usually available in 0.38" or 0.56" display packages which are great for mini-sized clocks.
*TM1637 Display (Barebone)*
It is totally possible to create your own TM1637 display driver if you have the parts available according to the following schematic.
<p align="center">
  <img src="https://github.com/NeonVulture/Arduino-Projects/blob/main/ATtiny85-Mini-Clock/Assets/Supplemental_Images/TM1637_IC_Driver.jpg?raw=true" alt="TM1637 Driver"/>
</p>
The question is however, why bother? Well, perhaps other than saving a couple of dollars, this gives you a bit more freedom
*MAX7219 Display (Module)*
The MAX7219 display module is most commonly found as an 8-digit display package which is a good choice if you want to display alpha-numeric data that is larger than 4-digits. In terms of digital clock design, this module would be most useful
<p align="center">
  <img src="https://github.com/NeonVulture/Arduino-Projects/blob/main/ATtiny85-Mini-Clock/Assets/Supplemental_Images/MAX7219_7-Seg_Front.jpg?raw=true" alt="MAX7219 Module (Front)"/>
  <img src="https://github.com/NeonVulture/Arduino-Projects/blob/main/ATtiny85-Mini-Clock/Assets/Supplemental_Images/MAX7219_7-Seg_Back.jpg?raw=true" alt="MAX7219 Module (Back)"/>
</p>

*MAX7219 Display (Barebone)*
While a MAX7219 IC can drive up [] it can also be used to drive an ordinary 4-digit display.
## Choosing an RTC
This project utilized a bare-bones (i.e. non-module) version of a DS1307 RTC. However, you could use any other RTC module such as the DS3231 RTC (tested) or DS1302 RTC (not-tested).
## Wiring
Regardless of what RTC and Display you decide to use 
*Option 1: (DS1307 or DS3231) + TM1637*
*Option 2:* 
## Required libraries
The necessary libraries are going to depend on what display you chose. 
## Code & Uploading to Attiny85
The sketch can be uploaded either using an attiny85 programmer or using an Arduino UNO. If you are unfamiliar with programming the Attiny85 with an Arduino UNO, I recommend following this [tutorial](https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829).

## PCB Design
