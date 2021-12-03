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
*TM1637 Display (Module)*
<p align="center">
  <img src="https://github.com/NeonVulture/Arduino-Projects/blob/main/ATtiny85-Mini-Clock/Assets/Supplemental_Images/TM1637_Display_Module.jpg?raw=true" alt="TM1637 Module"/>
</p>
*TM1637 Display (Barebone)*
<p align="center">
  <img src="https://github.com/NeonVulture/Arduino-Projects/blob/main/ATtiny85-Mini-Clock/Assets/Supplemental_Images/TM1637_IC_Driver.jpg?raw=true" alt="TM1637 Driver"/>
</p>
*MAX7219 Display (Module)*
<p align="center">
  <img src="https://github.com/NeonVulture/Arduino-Projects/blob/main/ATtiny85-Mini-Clock/Assets/Supplemental_Images/MAX7219_7-Seg_Front.jpg?raw=true" alt="MAX7219 Module (Front)"/>
  <img src="https://github.com/NeonVulture/Arduino-Projects/blob/main/ATtiny85-Mini-Clock/Assets/Supplemental_Images/MAX7219_7-Seg_Back.jpg?raw=true" alt="MAX7219 Module (Back)"/>
</p>

*MAX7219 Display (Barebone)*
This project utilized a 0.56" TM1637 display. It requires just two pins (aside from VCC and GND) to control and thus makes it easy to use with an ATtiny85. However, you need not to use a TM1637 display. It is also possible to use a 7-Segment display that is controlled by MAX7219 IC.
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
