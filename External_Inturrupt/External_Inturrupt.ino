#define Btn1_GPIO   35
#define LED1_GPIO   2
 
void IRAM_ATTR Ext_INT1_ISR()
{
  // Toggle The LED
  digitalWrite(LED1_GPIO, !digitalRead(LED1_GPIO));
}
 
void setup()
{
  pinMode(LED1_GPIO, OUTPUT);
  pinMode(Btn1_GPIO, INPUT);
  attachInterrupt(Btn1_GPIO, Ext_INT1_ISR, RISING);
}
 
void loop()
{
  // Do Nothing...
}