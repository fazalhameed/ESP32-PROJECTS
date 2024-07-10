#include "esp_adc_cal.h"
 
#define AN_Pot1    35
 
int AN_Pot1_Result = 0;
float Voltage = 0.0;
 
void setup()
{
  Serial.begin(115200);
}
 
void loop()
{
  AN_Pot1_Result = analogRead(AN_Pot1);
  Voltage = readADC_Cal(AN_Pot1_Result);
  Serial.println(Voltage/1000.0); // Print Voltage (in V)
  //Serial.println(Voltage);      // Print Voltage (in mV)
  delay(100);
}
 
uint32_t readADC_Cal(int ADC_Raw)
{
  esp_adc_cal_characteristics_t adc_chars;
  
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  return(esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars));
}