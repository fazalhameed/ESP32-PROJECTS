#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// UUIDs for the BLE service and characteristic
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// DHT11 sensor pin and type
#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BLECharacteristic *pCharacteristic;

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  // Initialize the DHT sensor
  dht.begin();

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  // Initialize the BLE device
  BLEDevice::init("ESP32");
  
  // Create a BLE server
  BLEServer *pServer = BLEDevice::createServer();
  
  // Create a BLE service
  BLEService *pService = pServer->createService(SERVICE_UUID);
  
  // Create a BLE characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  // Set the initial characteristic value
  pCharacteristic->setValue("Waiting for data...");

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connection issues
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  
  Serial.println("Characteristic defined! Now you can read it in your phone!");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BLE Ready");
}

void loop() {
  // Read temperature and humidity from DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0, 0);
    lcd.print("Read error");
    return;
  }

  // Print the data to the serial monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Display the data on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  // Create a string with the sensor data
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "T: %.2f C, H: %.2f %%", temperature, humidity);

  // Update the characteristic value with the formatted string
  pCharacteristic->setValue(buffer);

  // Notify connected clients (optional, if you want to push the data instead of just reading)
  pCharacteristic->notify();

  // Delay for a while before reading again
  delay(2000);
}
