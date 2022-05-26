/*
 * MIT License
 *
 * Copyright (c) 2018-2020 Erriez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \brief LCD Keypad Shield example demo
 * \details
 *      Source:         https://github.com/Erriez/ErriezLCDKeypadShield
 *      Documentation:  https://erriez.github.io/ErriezLCDKeypadShield
 */

#include <ErriezLCDKeypadShield.h>
#include <LiquidCrystal.h>
#include <Servo.h>

LCDKeypadShield shield;
Servo ESC;
long cur_ESC;
long cur_time;

void init_ESC() {
  cur_ESC = 0;
  cur_time = millis();
  ESC.attach(11, 1000, 2000);
  ESC.write(cur_ESC);
  shield.clear();
  shield.print(F("Push the buttons"));
}

void update_ESC(long val) {
  if (millis() - cur_time < 500)
    return;
  cur_ESC += val;
  cur_ESC = (cur_ESC > 180) ? 180 : cur_ESC;
  cur_ESC = (cur_ESC < 0) ? 0 : cur_ESC;
  cur_time = millis();
  ESC.write(cur_ESC);
  shield.clear();
  shield.print(F("Push the buttons"));
}

void setup(void) {
  init_ESC();

  // Backlight control
  for (uint8_t i = 0; i < 3; i++) {
    // Turn backlight off
    shield.backlightOff();
    delay(500);

    // Turn backlight on
    shield.backlightOn();
    delay(500);
  }
}

void loop(void) {
  shield.setCursor(9, 1);
  shield.print(cur_ESC);

  // Display seconds elapsed since power-up
  shield.setCursor(13, 1);
  shield.print(millis() / 1000);

  // Set cursor start second line
  shield.setCursor(0, 1);

  // Read buttons
  switch (shield.getButtons()) {
  case ButtonRight:
    shield.print(F("RIGHT "));
    update_ESC(15);
    break;
  case ButtonLeft:
    shield.print(F("LEFT  "));
    update_ESC(-15);
    break;
  case ButtonUp:
    shield.print(F("UP    "));
    update_ESC(5);
    break;
  case ButtonDown:
    shield.print(F("DOWN  "));
    update_ESC(-5);
    break;
  case ButtonSelect:
    shield.print(F("SELECT"));
    update_ESC(-180);
    break;
  case ButtonNone:
    shield.print(F("NONE  "));
    break;
  default:
    break;
  }
}
