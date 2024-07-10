#include <WiFi.h>
#include <WebServer.h>
 
// Replace with your own network credentials
const char* ssid = "CST WIFI";
const char* password = "iotdevs123";
 
WebServer server(80);
 
const int led1Pin = 25;
const int led2Pin = 13;
int ledState = LOW;
int ledBrightness = 0;
 
const char html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Web Server</title>
  <style>
    body {
      font-family: sans-serif;
    }
    .container {
      display: flex;
      flex-direction: column;
      align-items: center;
    }
    button {
      font-size: 1.5em;
      margin: 10px;
      padding: 10px;
      background-color: lightgray; /* Set the initial background color */
    }
    button.on {
      background-color: green; /* Set the background color when the LED is ON */
    }
    input[type=range] {
      width: 50%;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>ESP32 Web Server</h1>
    <br>
    <h3>LED1 State Control</h3>
    <button id="button" onclick="toggleLED()">LED: OFF</button>
    <br>
    <br>
    <h3>LED2 Brightness Control</h3>
    <input type="range" id="trackbar" min="0" max="255" step="1" value="0" oninput="setBrightness()">
  </div>
  <script>
    var ledState = false;
    var ledBrightness = 0;
    var button = document.getElementById('button');
    var trackbar = document.getElementById('trackbar');
    function toggleLED() {
      ledState = !ledState;
      var xhr = new XMLHttpRequest();
      xhr.open('GET', '/led?state=' + (ledState ? '1' : '0'), true);
      xhr.send();
      button.innerHTML = 'LED: ' + (ledState ? 'ON' : 'OFF');
      button.classList.toggle('on', ledState); // Add or remove the 'on' class based on the LED state
    }
    function setBrightness() {
      ledBrightness = trackbar.value;
      var xhr = new XMLHttpRequest();
      xhr.open('GET', '/brightness?value=' + ledBrightness, true);
      xhr.send();
    }
  </script>
</body>
</html>
)rawliteral";
 
void handleRoot() {
  server.send(200, "text/html", html);
}
 
void handleLED() {
  ledState = server.arg("state").toInt();
  digitalWrite(led1Pin, ledState);
  server.send(200, "text/plain", String(ledState));
}
 
void handleBrightness() {
  ledBrightness = server.arg("value").toInt();
  analogWrite(led2Pin, ledBrightness);
  server.send(200, "text/plain", String(ledBrightness));
}
 
void setup() {
  Serial.begin(115200);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  digitalWrite(led1Pin, ledState);
  analogWrite(led2Pin, ledBrightness);
  // WiFi Configuration & Init
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting To WiFi Network .");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  // Connected Successfully
  Serial.println("\nConnected To The WiFi Network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  // Attach Server Handler Functions & Start WebServer
  server.on("/", handleRoot);
  server.on("/led", handleLED);
  server.on("/brightness", handleBrightness);
  server.begin();
}
 
void loop() {
  server.handleClient();
}