#include <WiFi.h>
#include <esp_wifi.h>
 
uint8_t New_MAC_Address[] = {0x10, 0xAA, 0xBB, 0xCC, 0x33, 0xF5};
 
void setup(){
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    Serial.print("\nOLD ESP32 MAC Address: ");
    Serial.println(WiFi.macAddress());
    esp_wifi_set_mac(WIFI_IF_STA, New_MAC_Address);
    Serial.print("NEW ESP32 MAC Address: ");
    Serial.println(WiFi.macAddress());
}
 
void loop(){
  // Do Nothing
}