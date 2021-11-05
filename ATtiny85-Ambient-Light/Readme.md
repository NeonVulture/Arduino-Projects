# ATtiny85 Ambient Light
#### Create ambient lighting effects using an Attiny85 and RGB Strip
#### Features
+ Cycle through LED effects using a pushbutton.
+ Utilize an LDR to ensure that the RGB strip operates only in a dark environment.
## Component List
+ Attiny85
+ RGB Strip (preferably 5V)
+ Breadboard 
+ 1 push button
+ 1 470 ohm resistor
+ 1 Photoresistor
+ Attiny85 Programmer or Arduino Uno
+ 10uF Capacitor (if not using a programmer)
## Wiring
Below show how to wire up the components via a schematic and the physical layout on a breadboard.
![Breadboard Wiring](https://github.com/NeonVulture/Arduino-Projects/blob/main/ATtiny85-Ambient-Light/Assets/Breadboard_Wiring.PNG "Breadboard Wiring")

## Code & Uploading to Attiny85
The sketch can be uploaded either using an attiny85 programmer or using an Arduino UNO. If you are unfamiliar with programming the Attiny85 with an Arduino UNO, I recommend following this [tutorial](https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829).
