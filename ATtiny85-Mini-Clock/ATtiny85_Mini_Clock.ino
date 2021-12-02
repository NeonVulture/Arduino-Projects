#include <EEPROM.h>
#include "RTClib.h"
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 4 // ATTINY Pin 3
#define DIO 3 // ATTINY Pin 2

// Set up the TM1637 Display
TM1637Display display(CLK, DIO);
RTC_DS1307 rtc;
int DST;

void setup() {
  Serial.begin(57600);
  // Set the brightness of the display (0xff is brightest)
  display.setBrightness(0xff);
  
  DST = EEPROM.get(0, DST);
  if (DST != 0 && DST != 1) {
    DST = 1;
    EEPROM.put(0,DST); 
  }
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    //Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time
  // Format: YY, MTH, DD, HH, MM, SS
  //rtc.adjust(DateTime(2021, 11, 27, 21, 5, 20));
}

void loop() {
  DateTime now = rtc.now();

  int hh = now.hour(); int mm = now.minute(); int ss = now.second();
  int mth = now.month(); int dd = now.day(); int yr = now.year();
  int weekDay = now.dayOfTheWeek();
  
  if (weekDay == 0 && mth == 3 && dd >= 8 && dd <= 14 && hh == 2 && mm == 0 && ss == 0 && DST == 0){
    rtc.adjust(DateTime(yr, mth, dd, hh+1, mm, ss));       
    DST = 1;       
    EEPROM.put(0, DST);     
  } else if(weekDay == 0 && mth == 11 && dd >= 1 && dd <= 8 && hh == 2 && mm == 0 && ss == 0 && DST == 1){       
     rtc.adjust(DateTime(yr, mth, dd, hh-1, mm, ss));       
     DST = 0;       
     EEPROM.put(0, DST);     
  }
    
  // Set time format to AM/PM
  if (hh > 12) {
    hh = hh - 12;
  } 
    
  if (hh == 0) {
    hh = 12;
  }

  // Define the time format
  int clocktime = (hh * 100) + mm;

  // Display the time
  display.showNumberDecEx(clocktime, 0b11100000, false);
  //display.showNumberDec(clocktime);
  
  // Uncomment the following lines if you want the center colon to be static instead of blinking
  delay(900);
  display.showNumberDec(clocktime, false); // Prints displaytime without center colon.
  delay(900);
}
