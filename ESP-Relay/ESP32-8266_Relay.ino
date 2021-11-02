#include "OTA_Config.h"
#include <NTPClient.h>     // https://github.com/arduino-libraries/NTPClient

// Set the UTC Time offset in seconds
//const long utcOffsetInSeconds = -18000; // NEW YORK (UTC-05:00)
const long utcOffsetInSeconds = -14400; // NEW YORK (UTC-04:00) (Daylight Savings)

// Define NTP Client to get the time
WiFiUDP ntpUDP;

// Set up the Network Time Protocol Client, update with fresh time every 10 minutes
NTPClient timeClient(ntpUDP, "85.21.78.23", utcOffsetInSeconds, 600000);

// Module connection pins (Digital Pins)
int RelayPin = 4; // Wemos D1 Pin 2
int Relay_Status = LOW;
bool SOS_Status = false;
bool Timer_Mode = false;

void setup() {
  pinMode(RelayPin, OUTPUT);
  InitOTA();
  timeClient.begin();
}

void loop() {
  AsyncElegantOTA.loop();
  timeClient.update();
 
  int hh = timeClient.getHours();
  int mm = timeClient.getMinutes();

  // Turn ON/OFF relay based on a set time interval (Currently: 10:00PM - 5:45AM)
  if (Timer_Mode == true) {
    SOS_Status = false;
    if ((hh >= 22) || (hh == 0) ||(hh <=5 && mm <=45)) {
        delay(1000);  
        digitalWrite(RelayPin, HIGH);
    } else {
        digitalWrite(RelayPin, LOW);
    } 
  }
  
  if (Timer_Mode == false) {
    //Serial.println(Relay_Status);
    if(SOS_Status == true) {
      /*
      for(int i = 0; i < 3; i++) {
         SOS();
      }
      */
      SOS();
      SOS_Status = false; // To prevent endless loop
    }
  }
}
