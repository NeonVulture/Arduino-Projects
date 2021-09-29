# Pocket Simon
#### The famous Simon game on the go!
#### Features
+ Switch to "mute" piezo/buzzer speaker
## Component List
+ Attiny85
+ Breadboard
+ 4 push buttons (preferably colored)
+ 4 LEDs (Red, Green, Blue, Yellow)
+ Piezo Speaker/Buzzer
+ 4 220 Ohm resistors
+ 1 100 ohm resistor
+ 3V (CR2032) battery & holder (or any power source 5V or less)
+ 2 Slide switches (optional for PCB desgin) 
+ Attiny85 Programmer or Arduino Uno
+ 10uF Capacitor (if not using programmer)
## Wiring
Below show how to wire up the components on a breadboard and
![Schematic](https://github.com/NeonVulture/Arduino-Projects/blob/main/Pocket-Simon/Assets/Schematic.PNG "Schematic")
![Breadboard Wiring](https://github.com/NeonVulture/Arduino-Projects/blob/main/Pocket-Simon/Assets/Wiring_Diagram.PNG "Breadboard Wiring")
## Code & Uploading to Attiny85
The sketch can be uploaded either using an attiny85 programmer or using an Arduino UNO. If you are unfamiliar with programming the Attiny85 with an Arduino UNO, I recommed following this [tutorial](https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829).
## PCB Design
If you wish to make your build more permanent, I have provided a PCB version that is the about the size of a credit card (70mm x 45mm). In addition to the build on the breadboard, the PCB utilizes two slide switches SW5 and SW6. Switch SW5 is used to power on and off the game while switch SW6 "mutes" the piezo/buzzer speaker as to not disturb anyone in a public setting.
<p align="center">
  <img src="https://github.com/NeonVulture/Arduino-Projects/blob/main/Pocket-Simon/Assets/PCB_FullView.PNG?raw=true" alt="PCB View"/>
</p>

![PCB 3D View](https://github.com/NeonVulture/Arduino-Projects/blob/main/Pocket-Simon/Assets/PCB_FullView_3D.PNG "PCB 3D View")
This PCB was designed using EasyEDA. If you would like your own, you can download the gerber files and order it on any pcb manufacture such as [JLCPCB](https://jlcpcb.com/VBS?utm_source=bing_ads&utm_medium=cpc&utm_campaign=JP_ALL_20200709&msclkid=9ef340d94811193b322f218aa54c1cd9). Alternatively, You can download the template here which can be edited in KiCad as well.
