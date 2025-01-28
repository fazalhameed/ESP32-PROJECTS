#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
// LED GPIO Pin Definition
#define LED_GPIO 25

// Bluetooth Serial Object (Handle)
BluetoothSerial SerialBT;

// ESP32 Bluetooth (Slave) Device Information
String device_name = "ESP32-BT-Slave";

// Bluetooth Received Byte & Message Buffer Array
String RxBuffer = "";
char RxByte;

void setup() {
  pinMode(LED_GPIO, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());

  // Set the PIN code
  esp_bt_pin_type_t pin_type = ESP_BT_PIN_TYPE_FIXED;
  esp_bt_pin_code_t pin_code;
  strcpy((char *)pin_code, "1234");  // Change this to more secure PIN.
  esp_bt_gap_set_pin(pin_type, 4, pin_code);
}

void loop() {
  // Read The Received Bytes & Add Them To Message (RxBuffer) Array
  if (SerialBT.available()) {
    RxByte = SerialBT.read();
    if (RxByte != '\n') {
      RxBuffer += String(RxByte);
    } else {
      RxBuffer = "";
    }
    Serial.write(RxByte);
  }
  // Check The Received Message & Update Output LED State
  if (RxBuffer == "led_on") {
    digitalWrite(LED_GPIO, HIGH);
  } else if (RxBuffer == "led_off") {
    digitalWrite(LED_GPIO, LOW);
  }
  delay(25);
}
