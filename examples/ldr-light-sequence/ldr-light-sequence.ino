/**
 * Title: ldr-light-sequence
 * Description: Uses LDR to control a 3-LED sequence speed.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_LED_GREEN, OUTPUT);
  pinMode(AL_LED_YELLOW, OUTPUT);
  pinMode(AL_LED_RED, OUTPUT);
}

void loop() {
  int v = analogRead(AL_LDR);
  int speed = map(v, 0, 1023, 50, 800);
  digitalWrite(AL_LED_GREEN, HIGH);
  delay(speed);
  digitalWrite(AL_LED_GREEN, LOW);
  digitalWrite(AL_LED_YELLOW, HIGH);
  delay(speed);
  digitalWrite(AL_LED_YELLOW, LOW);
  digitalWrite(AL_LED_RED, HIGH);
  delay(speed);
  digitalWrite(AL_LED_RED, LOW);
}
