#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "lcd_wrapper.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void made_by() {
  char* top_text = "Made by Nikita";
  char* bottom_text = "Kalashnikov";

  lcd_print_at(0, 0, top_text);
  lcd_print_at(0, 1, bottom_text);
  delay(3000);
}

void lcd_init() {
  lcd.init();
  lcd.backlight();
  made_by();
}

void lcd_clear() {
  lcd.clear();
}

void lcd_set_cursor(int y, int x) {
  lcd.setCursor(y, x);
}

void lcd_print(char* text) {
  // Serial.println(text);
  lcd.print(text);
}

void lcd_num(int num) {
  lcd.print(num);
}


void lcd_print_at(int y, int x, char* text) {
  lcd_set_cursor(y, x);
  lcd_print(text);
}