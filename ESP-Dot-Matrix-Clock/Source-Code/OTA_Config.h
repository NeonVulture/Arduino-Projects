#ifdef ESP32 
  #include <WiFi.h> 
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h> 
#endif
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

const char *ssid = "RamosHome";
const char *password = "5fR68gTw201vVq";

// OTA Setup
AsyncWebServer server(80);
String projectTitle = "ESP WIFI Clock";
String projectDesc = 
  "<ul><li>Manual dimmer via potentiometer (optional). "
  "<li>International display options including display languages [En, Es, Fr, Pt, It] and three different date formats [MM:DD:YYY, DD:MM:YYYY, YYYY:MM:DD]."
  "<li>Option to format month and days of the week to shorthand (i.e. Wed)."
  "<li>Over the Air (OTA) progammable for making future updates easier.</ul>";

void InitOTA() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("");
  Serial.print("Successfully connted to SSID: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  printf("Sending response started\n");
                  request->send(
                      200,
                      "text/html",
                      R"(
        <!DOCTYPE HTML>
        <head><title>)" +
                          String(projectTitle) +
                          R"(</title></head>
        <body style='font-size:1.1em;'>
          <h3>ESP32/8266 WIFI Clock Home Page</h3>

          <div>Welcome to the landing page for )" +
                          String(projectTitle) +
                          R"( ESP32/8266 device on IP: )" +
                          String((char *)(WiFi.localIP()).toString().c_str()) +
                          R"(</div>

         <fieldset style="margin:20px 5px 20px 5px;border:1px;border-radius:5px;border:1px solid darkgray;background-color:white">
          <legend style="font-size:0.8em;">Features:</legend>
            <div style="font-size:0.8em;background-color:#EEEEEE;padding:5px;border-radius:10px;">)" +
                          String(projectDesc) +
                          R"(</div>
          </fieldset>

          <p>To update your device within Arduino IDE follow these steps: </p>
          <p>1. Go to <b>Sketch >> Export compiled Binary (Ctrl+Alt+S) </b></p>
          <p>2. Find the sketch folder via <b>Sketch >> Show Sketch Folder (Ctrl+K) </b></p>
          <p>3. Go to <a href='http://)" + String((char *)(WiFi.localIP()).toString().c_str()) + R"(/update' target='_blank'>http://)" + String((char *)(WiFi.localIP()).toString().c_str()) + R"(/update</a> </p>
          <p>4. Click on <b>Choose File </b> and upload your <b>.bin </b> file. </p>
          
        </body>
        </html>
      )");
                  printf("Sending response ends\n");
              });
  
  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();
}
