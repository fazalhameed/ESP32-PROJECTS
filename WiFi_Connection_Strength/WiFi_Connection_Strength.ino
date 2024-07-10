#include <WiFi.h>
 
// Replace with your own network credentials
const char* ssid = "CST WIFI";
const char* password = "iotdevs123";
 
void setup(){
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");
    // Keep Waiting Until Connection is Established
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }
    // Connected Successfully
    Serial.println("\nConnected To The WiFi Network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    // Print The RSSI (Received Signal Strength Indicator)
    Serial.print("RRSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
}
 
void loop(){
  // Do Nothing
}