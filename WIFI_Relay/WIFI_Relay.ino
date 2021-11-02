#include "OTA_Config.h"
#include <NTPClient.h>     // https://github.com/arduino-libraries/NTPClient
//#include <ESP8266WiFi.h>
//#include <ESP8266mDNS.h>
//#include <WiFiUdp.h>
//#include <ArduinoOTA.h>

/*
#ifndef STASSID
#define STASSID "RAMOS"
#define STAPSK  "87BL504KPC"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
*/
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

  /*
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  */
  timeClient.begin();
}

void loop() {
  AsyncElegantOTA.loop();
  //ArduinoOTA.handle();
  // Update the time client to get the current time
  timeClient.update();
 
  int hh = timeClient.getHours();
  int mm = timeClient.getMinutes();

  // Turn ON/OFF relay based on a set time interval
  // Currently: 10:00PM - 5:45AM
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
      for(int i = 0; i < 3; i++) {
         SOS();
      }
      SOS_Status = false; // To prevent endless loop
    }
  }
}
