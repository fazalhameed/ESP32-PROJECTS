#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C I2C_LCD1(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Custom character definitions
byte HeartChar[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

byte TickChar[8] = {
  B00000,
  B00001,
  B00011,
  B10110,
  B11100,
  B01000,
  B00000,
  B00000
};

byte BellChar[8] = {
  B00000,
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00100,
  B00000
};

byte BatteryChar[8] = {
  B01110,
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111,
  B01110
};

byte SoundChar[8] = {
  B00001,
  B00011,
  B00111,
  B01111,
  B01111,
  B00111,
  B00011,
  B00001
};

byte SmileChar[8] = {
  B00000,
  B01010,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

void setup()
{
  // Initialize The I2C LCD
  I2C_LCD1.init();
  // Turn ON The Backlight
  I2C_LCD1.backlight();
  
  // Create Custom Characters
  I2C_LCD1.createChar(0, HeartChar);
  I2C_LCD1.createChar(1, TickChar);
  I2C_LCD1.createChar(2, BellChar);
  I2C_LCD1.createChar(3, BatteryChar);
  I2C_LCD1.createChar(4, SoundChar);
  I2C_LCD1.createChar(5, SmileChar);
  
  // Display The First Message In Home Position (0, 0)
  I2C_LCD1.setCursor(0, 1);
 
  // Append The New Chars To The Message with spaces between them
  I2C_LCD1.write(byte(0)); // Heart
  I2C_LCD1.print(" ");      // Space
  I2C_LCD1.write(byte(1)); // Tick
  I2C_LCD1.print(" ");      // Space
  I2C_LCD1.write(byte(2)); // Bell
  I2C_LCD1.print(" ");      // Space
  I2C_LCD1.write(byte(3)); // Battery
  I2C_LCD1.print(" ");      // Space
  I2C_LCD1.write(byte(4)); // Sound
  I2C_LCD1.print(" ");      // Space
  I2C_LCD1.write(byte(5)); // Smile
  
  // Set cursor to second line and print a message
  I2C_LCD1.setCursor(0, 0);
  I2C_LCD1.print("Custom characters");
}

void loop()
{
  // Do Nothing...
}
