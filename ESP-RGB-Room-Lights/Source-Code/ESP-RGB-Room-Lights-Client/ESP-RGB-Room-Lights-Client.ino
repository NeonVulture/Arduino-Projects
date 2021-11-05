/* The client program to control an LED strip using an IR Remote that triggers different effects and reads the audio data from the master device.*/
#include "LED_Patterns.h"
#include "OTA_Config.h"
#include <IRremote.h>

extern int BRIGHTNESS;
extern int MIN_BRIGHTNESS;
extern int MAX_BRIGHTNESS;
extern long randNumber;
extern long randNumberR;
extern long randNumberG;
extern long randNUmberB;

bool MV = false;

void setup(){
  InitOTA();
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
  
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all strip to 'off'
  strip.setBrightness(BRIGHTNESS); // Initialize brightness set by BRIGHTNESS for strip 
  randomSeed(analogRead(A0));  // Set random number generator seed from analog pin 0
  IrReceiver.begin(13, DISABLE_LED_FEEDBACK);
}

void loop(){
  AsyncElegantOTA.loop();
  if(MV == true) MusicVisualizer();
  if(MV == false) {
  if (IrReceiver.decode()){
 
        //if (results.value == 0XFFFFFFFF) results.value = key_value;
        //Serial.println(IrReceiver.decodedIRData.command, HEX); // For debugging only
        switch(IrReceiver.decodedIRData.command){
          case 0x45: // CH-
          Serial.println("CH-");
          break;
          case 0x46: // CH
          Serial.println("CH");
          break;
          case 0x47: // CH+
          Serial.println("CH+");
          break;
          case 0x44: // |<<
          Serial.println("|<<");
          break;
          case 0x40: // >>|
          Serial.println(">>|");
          break ;  
          case 0x43: // >||
          Serial.println(">||"); // Start the Music visualizer
          MV = true;
          break ;               
          case 0x7: // -
          Serial.println("-");   
          adjustBrightness();  
          break ;  
          case 0x15: // +
          Serial.println("+");
          adjustBrightness(); 
          break ;  
          case 0x09: // EQ
          Serial.println("EQ"); // Turn off the Music visualizer
          colorWipe(strip.Color(0,0,0), 5); 
          MV = false;
          IrReceiver.resume(); 
          break ;  
          case 0x16:
          Serial.println("0"); // Turn off LED strip (Note: pressing any other mode will turn back the strip)
          colorWipe(strip.Color(0,0,0), 5); 
          break ;  
          case 0xFF9867:
          Serial.println("100+");
          break ;
          case 0xFFB04F:
          Serial.println("200+");
          break ;
          case 0x0C:
          Serial.println("1");
          hogwarts();
          break ;
          case 0x18:
          Serial.println("2");
          colorWipe(strip.Color(0, 221, 237), 5);
          break ;
          case 0x5E: 
          Serial.println("3");
          colorWipe(strip.Color(random(0, 128), random(0, 128), random(0, 128)), 5);
          break;
          case 0x08:     
          Serial.println("4");
          rainbow(50);
          break ;
          case 0x1C:
          Serial.println("5");
          meteorRain(0, 221, 237, 10, 64, true, 15);
          break ;
          case 0x5A:
          Serial.println("6");
          TwinkleRandom(PIXEL_COUNT, 30, true);
          break ;
          case 0x42:
          Serial.println("7");
          for(int i = 0; i < 10; i++) {
            theaterChaseRainbow(5);
            delay(1);
          }
          break ;
          case 0x52:
          Serial.println("8");
          flag();
          break ;
          case 0x4A:
          Serial.println("9");
          for(int i = 0; i < 200; i++) {
            Fire(60,200,10);
            delay(10);
          }
          break ;      
        }
        IrReceiver.resume();
  }
  }
}

void adjustBrightness() {
    if(IrReceiver.decodedIRData.command == 0x15) { // +
      BRIGHTNESS += 5;
      if (BRIGHTNESS > MAX_BRIGHTNESS) BRIGHTNESS = MAX_BRIGHTNESS;
    } else if (IrReceiver.decodedIRData.command == 0x07) { // -
      BRIGHTNESS -= 5;
      if (BRIGHTNESS < MIN_BRIGHTNESS) BRIGHTNESS = MIN_BRIGHTNESS;
    }
    strip.setBrightness(BRIGHTNESS);
    strip.show();
}
