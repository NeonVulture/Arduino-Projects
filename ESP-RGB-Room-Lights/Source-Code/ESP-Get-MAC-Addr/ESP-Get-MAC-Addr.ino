// Program to retrieve MAC address of ESP board
// Remember to open the serial montior and press the RESET button on your ESP device to get the MAC address
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}
 
void loop() {

}
