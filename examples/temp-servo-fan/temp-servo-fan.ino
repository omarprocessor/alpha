/**
 * Title: temp-servo-fan
 * Description: Move servo to mimic fan speed according to temperature.
 */

#include "alpha.h"
#include <Servo.h>

Servo s;

void setup() {
  s.attach(AL_SERVO_D6);
  Serial.begin(9600);
}

void loop() {
  int t = analogRead(AL_NTC);
  Serial.println(t);
  int angle = map(t, 300, 800, 0, 180);
  angle = constrain(angle, 0, 180);
  s.write(angle);
  delay(200);
}
