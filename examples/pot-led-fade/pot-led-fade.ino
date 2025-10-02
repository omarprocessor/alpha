/**
 * Title: pot-led-fade
 * Description: Use potentiometer A1 to fade green LED smoothly.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_LED_GREEN, OUTPUT);
}

void loop() {
  int p = analogRead(AL_POT_A1);
  int duty = map(p, 0, 1023, 0, 255);
  analogWrite(AL_LED_GREEN, duty);
  delay(10);
}
