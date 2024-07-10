#define LED_GPIO 2
#define AN_Pot1  35

int AN_Pot1_Result = 0;

void setup() {
  Serial.begin(115200);         // Initialize serial communication for debugging
  pinMode(LED_GPIO, OUTPUT);    // Initialize the LED pin as an output
  Serial.println("Setup complete.");
}

void loop() {
  AN_Pot1_Result = analogRead(AN_Pot1);          // Read the analog value from the potentiometer
  int pwmValue = map(AN_Pot1_Result, 0, 4095, 0, 255); // Map the analog reading to the PWM range (0-255)
  
  analogWrite(LED_GPIO, pwmValue);               // Write the PWM value to the LED pin

  Serial.print("Analog Reading: ");              // Print the analog reading
  Serial.print(AN_Pot1_Result);
  Serial.print(" -> PWM Value: ");               // Print the PWM value
  Serial.println(pwmValue);

  delay(1000);                                   // Small delay to stabilize the reading
}
