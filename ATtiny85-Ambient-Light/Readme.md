# ATtiny85 Ambient Light
#### Create ambient lighting effects using an Attiny85 and RGB Strip
#### Features
+ Cycle through LED effects using a pushbutton.
+ Utilize an LDR to ensure that the RGB strip operates only in a dark environment.
## Component List
+ Attiny85
+ 1 16MHz Crystal (Optional)
+ RGB Strip (preferably 5V)
+ Breadboard 
+ 1 push button
+ 1 470 ohm resistor (Optional)
+ 1 Photoresistor
+ 1 10k resistor
+ 1 1000uF Capactior (Optional)
+ Attiny85 Programmer or Arduino Uno
+ 10uF Capacitor (if not using a programmer)
## Wiring
Below show how to wire up the components via a schematic and the physical layout on a breadboard.
![Breadboard Wiring](https://github.com/NeonVulture/Arduino-Projects/blob/main/ATtiny85-Ambient-Light/Assets/Breadboard_Wiring.jpg "Breadboard Wiring")
The RGB strip used in this project is a 5V WS2812B because it elminates the need for a voltage regulator or additional power supply if a 12V RGB strip were used instead. Note that a resistor value of 330 to 560 Ohms is optional but recommended. Also, a 1000uF capacitor across the VCC and GND terminals of the RGB strip can help smooth (i.e. filter out) any noise that may arise

## Code & Uploading to Attiny85
The sketch can be uploaded either using an attiny85 programmer or using an Arduino UNO. If you are unfamiliar with programming the Attiny85 with an Arduino UNO, I recommend following this [tutorial](https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829).
