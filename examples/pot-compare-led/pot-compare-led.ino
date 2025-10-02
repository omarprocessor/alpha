/**
 * Title: pot-compare-led
 * Description: Lights green if A1 > A2 else red.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_LED_GREEN, OUTPUT);
  pinMode(AL_LED_RED, OUTPUT);
}

void loop() {
  int a = analogRead(AL_POT_A1);
  int b = analogRead(AL_POT_A2);
  if (a > b) {
    digitalWrite(AL_LED_GREEN, HIGH);
    digitalWrite(AL_LED_RED, LOW);
  } else {
    digitalWrite(AL_LED_GREEN, LOW);
    digitalWrite(AL_LED_RED, HIGH);
  }
  delay(100);
}
