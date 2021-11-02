#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncWebServer.h>
# else
  #include <ESP8266WiFi.h> // Change to WiFi.h if using ESP32  
  #include <ESPAsyncTCP.h> // Change to AsyncTCP if using ESP32  
#endif
#include <WiFiUdp.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

const char *ssid = "RAMOS";
const char *password = "87BL504KPC";

extern int RelayPin;
extern int Relay_Status;
extern bool SOS_Status;
extern bool Timer_Mode;

const char* PARAM_INPUT_1 = "Relay";  
const char* PARAM_INPUT_2 = "SOS";
const char* PARAM_INPUT_3 = "Timer";

AsyncWebServer server(80);

String projectTitle = "WiFi-Controlled Outdoor Lamp";
String projectDesc = 
  "<ul><li>Control an Relay remotely via WiFi"
  "<li>Timed intervals for relay operation."
  "<li>Manually toggle the relay on and off."
  "<li>Send an S.O.S distress signal.</ul>";

void dot() {
  digitalWrite(RelayPin, HIGH);
  delay(250);
  digitalWrite(RelayPin, LOW);
  delay(250);
}

void dash() {
  digitalWrite(RelayPin, HIGH);
  delay(1000);
  digitalWrite(RelayPin, LOW);
  delay(250);
}

void SOS() {
  dot(); dot(); dot();
  dash(); dash(); dash();
  dot(); dot(); dot();
  delay(3000);
}

String RelayOutputState() {
  if(digitalRead(RelayPin)) {
    return "checked";
  } else {
    return "";
  }
  return "";
}

String TimerOutputState() {
  if(Timer_Mode == true) {
    return "checked";
  } else {
    return "";
  }
  return "";
}

String SOSOutputState() {
  if(SOS_Status == true) {
    return "checked";
  } else {
    return "";
  }
  return "";
}

// Replaces placeholder with button section in your web page
String processor(const String& var) {
  //Serial.println(var);
  if(var == "RELAYBUTTONPLACEHOLDER") {
    String Relay_Button = "";
    String RelayOutputStateValue = RelayOutputState();
    Relay_Button += "<h4>Relay: <span id=\"outputState\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"output\" " + RelayOutputStateValue + "><span class=\"slider\"></span></label>";
    return Relay_Button;
  }

  if(var == "TIMERBUTTONPLACEHOLDER") {
    String Timer_Button = "";
    String TimerOutputStateValue = RelayOutputState();
    Timer_Button += "<h4>Timer: <span id=\"outputState3\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"output3\" " + TimerOutputStateValue + "><span class=\"slider\"></span></label>";
    return Timer_Button;
  }
 
  if(var == "SOSBUTTONPLACEHOLDER") {
    String SOS_Button =  "";
    String SOSOutputStateValue = RelayOutputState();
    SOS_Button += "<h4>SOS: <span id=\"outputState2\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox2(this)\" id=\"output2\" " + SOSOutputStateValue + "><span class=\"slider\"></span></label>";
    return SOS_Button;
  }
  return String();
}

// Main Page HTML Definiton
const char index_html[] PROGMEM = R"rawliteral(
      <!DOCTYPE HTML><html>
      <head>
      <title> WiFi Relay Control </title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
      html {font-family: Arial; display: inline-block; text-align: center;}
      h2 {font-size: 3.0rem;}
      p {font-size: 3.0rem;}
      body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
      .switch {position: relative; display: inline-block; width: 120px; height: 68px}
      .switch input {display: none}
      .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #F63E36; border-radius: 34px}
      .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
      input:checked+.slider {background-color: #3CC33C}
      input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
      </style>
      </head>
      <body>
      <h3>Relay Control Page</h3>
      %RELAYBUTTONPLACEHOLDER%
      %TIMERBUTTONPLACEHOLDER%
      %SOSBUTTONPLACEHOLDER%
      <script>
      function toggleCheckbox(element) {
        var xhr = new XMLHttpRequest();
        if(element.checked) {
          xhr.open("GET", "/getData?Relay=1", true);
        } else {
            xhr.open("GET", "/getData?Relay=0", true);
        }
        xhr.send();
      }
       
      function toggleCheckbox2(element) {
        var xhr2 = new XMLHttpRequest();
        if(element.checked) {
          xhr2.open("GET", "/getData?SOS=1", true);
        } else {
            xhr2.open("GET", "/getData?SOS=0", true);
        }
        xhr2.send();
      }

      function toggleCheckbox3(element) {
        var xhr3 = new XMLHttpRequest();
        if(element.checked) {
          xhr3.open("GET", "/getData?Timer=1", true);
        } else {
          xhr3.open("GET", "/getData?Timer=0", true);
        }
        xhr3.send();
      }
       
      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function()
        {
        if (this.readyState == 4 && this.status == 200) {
          var inputChecked;
          var outputStateM;
       
          if(this.responseText == 1) {
            inputChecked = true;
            outputStateM = "ON";
          } else {
              inputChecked = false;
              outputStateM = "OFF";
          }
          document.getElementById("output").checked = inputChecked;
          document.getElementById("outputState").innerHTML = outputStateM;
       }
       }
       xhttp.open("GET", "/Relay", true);
       xhttp.send();
       
       var xhttp2 = new XMLHttpRequest();
       xhttp2.onreadystatechange = function()
       {
       if (this.readyState == 4 && this.status == 200) {
         var inputChecked2;
         var outputStateM2;
       
         if(this.responseText == 1) {
           inputChecked2 = true;
           outputStateM2 = "ON";
         } else {
             inputChecked2 = false;
             outputStateM2 = "OFF";
         }
         document.getElementById("output2").checked = inputChecked2;
         document.getElementById("outputState2").innerHTML = outputStateM2;
       }
       };
       xhttp2.open("GET", "/SOS", true);
       xhttp2.send();

       var xhttp3 = new XMLHttpRequest();
       xhttp3.onreadystatechange = function()
       {
       if (this.readyState == 4 && this.status == 200) {
         var inputChecked3;
         var outputStateM3;
       
         if(this.responseText == 1) {
           inputChecked3 = true;
           outputStateM3 = "ON";
         } else {
             inputChecked3 = false;
             outputStateM3 = "OFF";
         }
         document.getElementById("output3").checked = inputChecked3;
         document.getElementById("outputState3").innerHTML = outputStateM3;
       }
       };
       xhttp3.open("GET", "/Timer", true);
       xhttp3.send();
       
       }, 1000 ) ;
       </script>
       </body>
       </html>
       )rawliteral";

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
  Serial.print("Successfully connected to SSID: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Project Home Page
  server.on("/aboutme", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  printf("Sending response started\n");
                  request->send(200, "text/html", R"(
        <!DOCTYPE HTML>
        <head><title>)" +
                          String(projectTitle) +
                          R"(</title></head>
        <body style='font-size:1.1em;'>
          <h3>ESP32/8266 RGB Room LEDS Home Page</h3>

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

      // Route for Main page
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", index_html, processor);
      }); 
          
      // Data Extraction Page
      server.on("/getData", HTTP_GET, [] (AsyncWebServerRequest *request){
        
        String RelayMessage; String SOSMessage; String TimerMessage;      
        String RelayParam; String SOSParam; String TimerParam;
       
        // GET Relay Status on <ESP_IP>/update?state=<inputMessage>
        if (request->hasParam(PARAM_INPUT_1)){
          RelayMessage = request->getParam(PARAM_INPUT_1)->value();
          RelayParam = PARAM_INPUT_1;
          digitalWrite(RelayPin, RelayMessage.toInt()); 
          Relay_Status = !Relay_Status; 
        } 
        Serial.print("Relay Status: ");
        Serial.println(RelayMessage.toInt());
        request->send(200, "text/plain", "OK");
        
        // GET SOS Status on <ESP_IP>/update?state=<inputMessage>
       
        if (request->hasParam(PARAM_INPUT_2)) {
          SOSMessage = request->getParam(PARAM_INPUT_2)->value();
          SOSParam = PARAM_INPUT_2;
          SOS_Status = true;
        } 
        Serial.print("SOS Status: ");
        Serial.println(SOSMessage.toInt());
        request->send(200, "text/plain", "OK");

        // GET Timer Status on <ESP_IP>/update?state=<inputMessage>
       
        if (request->hasParam(PARAM_INPUT_3)) {
          TimerMessage = request->getParam(PARAM_INPUT_3)->value();
          TimerParam = PARAM_INPUT_3;
          //Timer_Mode = true;
          //Timer_Mode = !Timer_Mode;
        } 
        Serial.print("Timer Mode: ");
        Serial.println(TimerMessage.toInt());
        Serial.println();
        request->send(200, "text/plain", "OK");
        
      });
       
      // Send a GET request to <ESP_IP>/Relay
      server.on("/Relay", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(digitalRead(RelayPin)).c_str());
      });

      // Send a GET request to <ESP_IP>/Timer 
      server.on("/Timer", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(Timer_Mode).c_str());
      });
      
      // Send a GET request to <ESP_IP>/SOS 
      server.on("/SOS", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(SOS_Status).c_str());
      });
       
      AsyncElegantOTA.begin(&server); // Start ElegantOTA
      server.begin();
}
