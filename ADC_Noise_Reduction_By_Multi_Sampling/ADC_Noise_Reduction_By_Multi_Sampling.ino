#include "esp_adc_cal.h"
 
#define AN_Pot1     35
#define FILTER_LEN  15
 
uint32_t AN_Pot1_Buffer[FILTER_LEN] = {0};
int AN_Pot1_i = 0;
int AN_Pot1_Raw = 0;
int AN_Pot1_Filtered = 0;
 
void setup()
{
  Serial.begin(115200);
}
void loop()
{
  AN_Pot1_Raw = analogRead(AN_Pot1);
  AN_Pot1_Filtered = readADC_Avg(AN_Pot1_Raw);
  Serial.print(AN_Pot1_Raw);        // Print Raw Reading
  Serial.print(',');                // Comma Separator
  Serial.println(AN_Pot1_Filtered); // Print Filtered Output
  delay(1000);
}
 
uint32_t readADC_Avg(int ADC_Raw)
{
  int i = 0;
  uint32_t Sum = 0;
  
  AN_Pot1_Buffer[AN_Pot1_i++] = ADC_Raw;
  if(AN_Pot1_i == FILTER_LEN)
  {
    AN_Pot1_i = 0;
  }
  for(i=0; i<FILTER_LEN; i++)
  {
    Sum += AN_Pot1_Buffer[i];
  }
  return (Sum/FILTER_LEN);
  
}
