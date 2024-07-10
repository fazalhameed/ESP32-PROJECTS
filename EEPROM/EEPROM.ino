// Include The EEPROM.h Library To Read & Write To The FLASH Memory
#include <EEPROM.h>
 
// Define The Number of Bytes You Need
#define EEPROM_SIZE 1
// Define The LED Output GPIO Pin & Button Input GPIO Pin
#define LED_GPIO 25
#define BTN_GPIO 35
 
// Global Variables For Button Reading & Debouncing
int ledState = LOW;
int btnState = LOW;
int lastBtnState = LOW;
int lastDebounceTime = 0;
int debounceDelay = 50;
int eeprom_address = 0;
 
void setup() {
  Serial.begin(115200);
  pinMode(LED_GPIO, OUTPUT);
  pinMode(BTN_GPIO, INPUT);
  EEPROM.begin(EEPROM_SIZE);
  ledState = EEPROM.read(eeprom_address);
  digitalWrite(LED_GPIO, ledState);
}
 
void loop() {
  int reading = digitalRead(BTN_GPIO);
  if (reading != lastBtnState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != btnState) {
      btnState = reading;
      if (btnState == HIGH) {
        ledState = !ledState;
        digitalWrite(LED_GPIO, ledState);
        EEPROM.write(eeprom_address, ledState);
        EEPROM.commit();
        Serial.println("State Changed & Saved To FLASH!");
      }
    }
  }
  lastBtnState = reading;
}
