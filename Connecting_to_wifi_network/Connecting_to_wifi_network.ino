#include <WiFi.h>
 
// Replace with your own network credentials
const char* ssid = "Use Your WIFI Name";
const char* password = "Wifi Password";
 
int WiFiStatus;
 
String Get_WiFiStatus(int Status){
    switch(Status){
        case WL_IDLE_STATUS:
        return "WL_IDLE_STATUS";
        case WL_SCAN_COMPLETED:
        return "WL_SCAN_COMPLETED";
        case WL_NO_SSID_AVAIL:
        return "WL_NO_SSID_AVAIL";
        case WL_CONNECT_FAILED:
        return "WL_CONNECT_FAILED";
        case WL_CONNECTION_LOST:
        return "WL_CONNECTION_LOST";
        case WL_CONNECTED:
        return "WL_CONNECTED";
        case WL_DISCONNECTED:
        return "WL_DISCONNECTED";
    }
}
 
void setup(){
    Serial.begin(115200);
    Serial.println("Connecting..");
    WiFi.begin(ssid, password);
    WiFiStatus = WiFi.status();
    while(WiFiStatus != WL_CONNECTED){
        delay(250);
        WiFiStatus = WiFi.status();
        Serial.println(Get_WiFiStatus(WiFiStatus));
    }
    Serial.println("\nConnected To The WiFi Network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}
void loop(){
  // Do Nothing
}
