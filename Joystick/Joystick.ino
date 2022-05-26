#include <LiquidCrystal.h>

// LCD
#define LCD_PIN_RS          8
#define LCD_PIN_EN          9
#define LCD_PIN_D0          4
#define LCD_PIN_D1          5
#define LCD_PIN_D2          6
#define LCD_PIN_D3          7
#define LCD_BACK_LIGHT_PIN  10

// Joystick
#define JS_PIN_X            0
#define JS_PIN_Y            1
#define JS_PIN_SW           11

LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_EN,
                  LCD_PIN_D0, LCD_PIN_D1, LCD_PIN_D2, LCD_PIN_D3);

void setup(void) {
  // Initialize backlight pin
  pinMode(LCD_BACK_LIGHT_PIN, OUTPUT);
  
  // Turn backlight on
  digitalWrite(LCD_BACK_LIGHT_PIN, HIGH);
  
  // Initialize LCD
  lcd.begin(16, 2);
  
  // Initialize joystick sw pin
  pinMode(JS_PIN_SW, INPUT);
  digitalWrite(JS_PIN_SW, HIGH);
}

void loop(void) {
  int raw_x = analogRead(JS_PIN_X) / 8;
  int raw_y = analogRead(JS_PIN_Y) / 8;
  int raw_sw = digitalRead(JS_PIN_SW);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(F("X"));

  lcd.setCursor(8, 0);
  lcd.print(F("Y"));

  lcd.setCursor(15, 0);
  if (raw_sw == LOW)
    lcd.print(F("L"));
  else
    lcd.print(F("H"));

  lcd.setCursor(0, 1);
  lcd.print(raw_x);

  lcd.setCursor(8, 1);
  lcd.print(raw_y);
}
