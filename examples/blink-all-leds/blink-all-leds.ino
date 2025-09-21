/**
 * Title: Blink All LEDs
 * Description: Blinks the red, yellow, and green LEDs on and off together.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_LED_RED, OUTPUT);
  pinMode(AL_LED_YELLOW, OUTPUT);
  pinMode(AL_LED_GREEN, OUTPUT);
}

void loop() {
  digitalWrite(AL_LED_RED, HIGH);
  digitalWrite(AL_LED_YELLOW, HIGH);
  digitalWrite(AL_LED_GREEN, HIGH);
  delay(500);

  digitalWrite(AL_LED_RED, LOW);
  digitalWrite(AL_LED_YELLOW, LOW);
  digitalWrite(AL_LED_GREEN, LOW);
  delay(500);
}