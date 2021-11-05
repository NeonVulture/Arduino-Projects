#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <espnow.h>

#define AUDIO_PIN 12 // D6
const int SAMPLE_TIME = 10;
unsigned long CurrMillis;
unsigned long LastMillis = 0;
unsigned long ElapsedMillis = 0;
int sampleBufferValue = 0;

uint8_t ClientAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Replace with your board's MAC Address

typedef struct struct_message {
  uint8_t vol;
} struct_message;

// Create a struct_message called myData
struct_message AudioData;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER); // Register Master
  esp_now_add_peer(ClientAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);   // Register Client
  esp_now_register_send_cb(OnDataSent); // Register Callback function
}

void loop() {
  CurrMillis = millis();
  ElapsedMillis = CurrMillis - LastMillis;

  if (digitalRead(AUDIO_PIN) == LOW) sampleBufferValue++;
  if (ElapsedMillis > SAMPLE_TIME) {
    Serial.println(sampleBufferValue);
    AudioData.vol = sampleBufferValue;
    sampleBufferValue = 0;
    LastMillis = CurrMillis;
  }
  // Send message via ESP-NOW
  esp_now_send(ClientAddress, (uint8_t *) &AudioData, sizeof(AudioData));
}

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Data Delivery success");
  } else {
    Serial.println("Data Delivery fail");
  }
}
