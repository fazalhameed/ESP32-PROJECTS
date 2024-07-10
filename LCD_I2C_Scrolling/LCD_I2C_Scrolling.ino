
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C I2C_LCD1(0x27, 16, 2);

void setup()
{
  // Initialize The I2C LCD
  I2C_LCD1.init();
  // Turn ON The Backlight
  I2C_LCD1.backlight();
  // Print A Message To The 1st Line
  I2C_LCD1.print(" Fazal Hameed ");
  // Set Cursor To Line 2
  I2C_LCD1.setCursor(0,1);
  // Print A Message To The 2nd Line
  I2C_LCD1.print(" Chip Soul");
}

void loop()
{
  // The message to scroll
  String message = " Chip Soul  ";
  // Pad the message with spaces to ensure a smooth scrolling effect
  message = "                " + message + "                "; // Add spaces to both ends for scrolling
  
  // Scroll the message to the right
  for (int i = 0; i < 16; i++) {
    I2C_LCD1.setCursor(0, 1); // Set cursor to the second line
    I2C_LCD1.print(message.substring(i, i + 16)); // Print substring of message
    delay(500); // Wait for a while before the next scroll
  }

  // Scroll the message to the left
  for (int i = 16; i > 0; i--) {
    I2C_LCD1.setCursor(0, 1); // Set cursor to the second line
    I2C_LCD1.print(message.substring(i, i + 16)); // Print substring of message
    delay(500); // Wait for a while before the next scroll
  }
}

