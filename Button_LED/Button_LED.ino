

#define LED_GPIO 2
#define BTN_GPIO 23
 
int BTN_State = 0; // Variable To Store Button State
 
void setup()
{
  pinMode(LED_GPIO, OUTPUT);
  pinMode(BTN_GPIO, INPUT);
    // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
}
 
void loop()
{
  // Read The Button State
  BTN_State = digitalRead(BTN_GPIO);
  // Assign The BTN State To The LED Pin
  digitalWrite(LED_GPIO, BTN_State);

   // Display the LED state on the serial monitor
  if (BTN_State == HIGH) {
    Serial.println("LED is ON");
  } else {
    Serial.println("LED is OFF");
  }
  
  // Add a small delay to avoid flooding the serial monitor
  delay(100);
}