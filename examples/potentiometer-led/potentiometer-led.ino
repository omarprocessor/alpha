/**
 * Title: Potentiometer LED
 * Description: Controls the brightness of the green LED using a potentiometer.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_LED_GREEN, OUTPUT);
}

void loop() {
  int potValue = analogRead(AL_POT_A1);
  int brightness = map(potValue, 0, 1023, 0, 255);
  analogWrite(AL_LED_GREEN, brightness);
  delay(10);
}