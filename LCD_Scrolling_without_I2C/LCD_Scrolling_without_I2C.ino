#include <LiquidCrystal.h>
 
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal My_LCD(13, 12, 14, 27, 26, 25);
 
void setup()
{
  // Initialize The LCD. Parameters: [ Columns, Rows ]
  My_LCD.begin(16, 2);
  // Clears The LCD Display
  My_LCD.clear();
 
  // Display The First Message In Home Position (0, 0)
  My_LCD.print("Hello");
  // Set The Cursor Position To: [ Col 0, Row 1]
  // The Next Message Will Start From The 1st Char Position in The 2nd Row
  // Note: 1st Row Has An Index of 0, The 2nd Row Has An Index of 1
  My_LCD.setCursor(0, 1);
  // Display The Second Message In Position (0, 1)
  My_LCD.print("CST ");
}
 
void loop()
{
  // Shift The Entire Display To Right 7 Times
  for(int i=0; i<7; i++)
  {
    My_LCD.scrollDisplayRight();
    delay(500);
  }
  // Shift The Entire Display To Left 7 Times
  for(int i=0; i<7; i++)
  {
    My_LCD.scrollDisplayLeft();
    delay(500);
  }
}