#include <Servo.h>

// Joystick
#define JS_PIN_X            0
#define JS_PIN_Y            1
#define JS_PIN_SW           7

// BLDC motor
#define BLDC_MOTOR_PIN      6

Servo ESC;
int init_raw_x;
int init_raw_y;

void setup(void) {
  // Initialize ESC
  ESC.attach(BLDC_MOTOR_PIN, 1000, 2000);
  ESC.write(0);

  // Initialize Joystick SW pin
  pinMode(JS_PIN_SW, INPUT);
  digitalWrite(JS_PIN_SW, HIGH);
  
  // Initialize and wait for port to open
  Serial.begin(9600);
  while (!Serial) {}
  
  // Other
  init_raw_x = analogRead(JS_PIN_X);
  init_raw_y = analogRead(JS_PIN_Y);
  Serial.print("Init X: ");
  Serial.println(init_raw_x);
  Serial.print("Init Y: ");
  Serial.println(init_raw_y);
  Serial.println("----------");
  while (true) {
    if (!digitalRead(JS_PIN_SW))
      break;
  }
}

void loop(void) {
  if (!Serial)
    return;
  delay(200);
  
  int raw_x = analogRead(JS_PIN_X);
  int raw_y = analogRead(JS_PIN_Y);
  int raw_sw = digitalRead(JS_PIN_SW);
  
  Serial.print("X: ");
  Serial.println(raw_x);
  Serial.print("Y: ");
  Serial.println(raw_y);
  Serial.print("SW: ");
  Serial.println(raw_sw);
  
  if (raw_x < init_raw_x)
    raw_x = init_raw_x;
  int esc_val = map(raw_x, init_raw_x, 1023, 0, 180);
  ESC.write(esc_val);

  Serial.print("ESC: ");
  Serial.println(esc_val);
  Serial.println("----------");
}
