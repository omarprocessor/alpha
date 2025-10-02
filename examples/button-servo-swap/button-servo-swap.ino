/**
 * Title: button-servo-swap
 * Description: Button toggles servo between two preset angles.
 */

#include "alpha.h"
#include <Servo.h>

Servo s;

void setup() {
  pinMode(AL_BUTTON_A4, INPUT_PULLUP);
  s.attach(AL_SERVO_D6);
}

void loop() {
  static bool pos = false;
  static int last = HIGH;
  int cur = digitalRead(AL_BUTTON_A4);
  if (last == HIGH && cur == LOW) {
    pos = !pos;
    s.write(pos ? 120 : 60);
    delay(200);
  }
  last = cur;
}
