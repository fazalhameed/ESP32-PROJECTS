#define HALL_SENSOR_PIN 23  // Pin connected to D0 of the Hall sensor

volatile int rotationCount = 0;  // Counter for magnet detections
volatile unsigned long lastDebounceTime = 0;  // Timestamp of the last valid detection
const unsigned long debounceDelay = 10;  // 10 ms debounce delay

void IRAM_ATTR handleRotation() {
  unsigned long currentTime = millis();
  
  // Check if the debounce time has passed since the last detection
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    rotationCount++;  // Increment the counter
    lastDebounceTime = currentTime;  // Update the last debounce time
  }
}  
void setup() {
  Serial.begin(115200);  // Initialize Serial Monitor
  pinMode(HALL_SENSOR_PIN, INPUT);  // Set Hall sensor pin as input

  // Attach interrupt to the Hall sensor pin
  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), handleRotation, FALLING);
}
void loop() {
  // Print the total number of detections
  Serial.print("Total detections: ");
  Serial.println(rotationCount);
  delay(500);  // Delay to reduce serial output clutter
}
