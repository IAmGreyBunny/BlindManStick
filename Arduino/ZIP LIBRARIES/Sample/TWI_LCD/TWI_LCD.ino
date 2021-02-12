// TWI LCD sample code

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
                   // addr,en,rw,rs,d4,d5,d6,d7,bl,blpol
                   // addr can be 0x3F or 0x27
void setup()
{ 
  lcd.begin(16, 2); // 16 characters, 2 lines

  lcd.noBacklight(); // turn backlight off
  delay(250);
  lcd.backlight(); // turn backlight on
  delay(250);

  lcd.setCursor(0, 0); // position cursor at character 0, line 0
  lcd.print("Enter password:");
  delay(500);
  
  lcd.setCursor(0, 1); // position cursor at character 0, line 1
  for (int i=0; i<5; i++){
    // read a character in the password
    lcd.print("*"); // display as asterisk
    delay(500);
  }

  delay(5000);
  lcd.clear(); // clear display

  // continue...
}

void loop()
{
  // left blank
}

