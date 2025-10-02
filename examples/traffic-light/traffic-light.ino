/**
 * Title: Traffic Light
 * Description: Simulates a traffic light sequence using all three LEDs.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_LED_RED, OUTPUT);
  pinMode(AL_LED_YELLOW, OUTPUT);
  pinMode(AL_LED_GREEN, OUTPUT);
}

void loop() {
  // Red
  digitalWrite(AL_LED_RED, HIGH);
  delay(3000);
  // Red + Yellow
  digitalWrite(AL_LED_YELLOW, HIGH);
  delay(1000);
  // Green
  digitalWrite(AL_LED_RED, LOW);
  digitalWrite(AL_LED_YELLOW, LOW);
  digitalWrite(AL_LED_GREEN, HIGH);
  delay(3000);
  // Yellow
  digitalWrite(AL_LED_GREEN, LOW);
  digitalWrite(AL_LED_YELLOW, HIGH);
  delay(1000);
  digitalWrite(AL_LED_YELLOW, LOW);
}