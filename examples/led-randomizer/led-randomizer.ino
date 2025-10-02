/**
 * Title: led-randomizer
 * Description: Random LED flashes every second with random duration.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_LED_GREEN, OUTPUT);
  pinMode(AL_LED_YELLOW, OUTPUT);
  pinMode(AL_LED_RED, OUTPUT);
  randomSeed(analogRead(AL_LDR));
}

void loop() {
  int r = random(3);
  int d = random(50, 600);
  digitalWrite(AL_LED_GREEN, r == 0);
  digitalWrite(AL_LED_YELLOW, r == 1);
  digitalWrite(AL_LED_RED, r == 2);
  delay(d);
}
