# ATtiny85 Mini Clock
#### A very basic clock in a small form factor 
#### Features
+ 
+ Accounts for Daylight Savings Time (DST)
## Component List
+ Attiny85
+ Breadboard
+ A display
+ RTC (Module or bare-bones)
+ Attiny85 Programmer or Arduino Uno
+ 10uF Capacitor (if not using programmer)

## Choosing a display
This project utilized a 0.56" TM1637 display. It requires just two pins (aside from VCC and GND) to control and thus makes it easy to use with an ATtiny85. However, you need not to use a TM1637 display. It is also possible to use a 7-Segment display that is controlled by MAX7219 IC.
## Choosing an RTC
This project utilized a bare-bones (i.e. non-module) version of a DS1307 RTC. However, you could use any other RTC module such as the DS3231 RTC (tested) or DS1302 RTC (not-tested).
## Required libraries
The necessary libraries are going to depend on what display you chose. 
## Wiring
Below show how to wire up the components via a schematic and physically on a breadboard.

## Code & Uploading to Attiny85
The sketch can be uploaded either using an attiny85 programmer or using an Arduino UNO. If you are unfamiliar with programming the Attiny85 with an Arduino UNO, I recommend following this [tutorial](https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829).

## PCB Design
