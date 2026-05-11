#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// 8 variables
float v1 = 25.6;
float v2 = 60.2;
float v3 = 1012;
float v4 = 300;

float v5 = 28.4;
float v6 = 55.1;
float v7 = 980;
float v8 = 450;

void setup() {
  Wire.begin(21,22);
  lcd.init();
  lcd.backlight();
}

void loop() {

  // 🔹 FRONT SCREEN (First 4 values)
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("1:");
  lcd.print(v1);
  lcd.setCursor(0,1);
  lcd.print(" 2:");
  lcd.print(v2);

  lcd.setCursor(0,0);
  lcd.print("3:");
  lcd.print(v3);
  lcd.setCursor(0,1);
  lcd.print(" 4:");
  lcd.print(v4);

  delay(3000);

  // 🔹 BACK SCREEN (Next 4 values)
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("5:");
  lcd.print(v5);
   lcd.setCursor(0,1);
  lcd.print(" 6:");
  lcd.print(v6);

  lcd.setCursor(0,0);
  lcd.print("7:");
  lcd.print(v7);
   lcd.setCursor(0,1);
  lcd.print(" 8:");
  lcd.print(v8);

  delay(3000);
}