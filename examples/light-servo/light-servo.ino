/**
 * Title: light-servo
 * Description: Servo seeks brighter area using LDR changes.
 */

#include "alpha.h"
#include <Servo.h>

Servo s;

void setup() {
  s.attach(AL_SERVO_D5);
}

void loop() {
  int v = analogRead(AL_LDR);
  int angle = map(v, 0, 1023, 0, 180);
  s.write(angle);
  delay(100);
}
