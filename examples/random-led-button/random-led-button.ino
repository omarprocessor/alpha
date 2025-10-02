/**
 * Title: random-led-button
 * Description: Press button to light a random one of 3 LEDs.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_BUTTON_A4, INPUT_PULLUP);
  pinMode(AL_LED_GREEN, OUTPUT);
  pinMode(AL_LED_YELLOW, OUTPUT);
  pinMode(AL_LED_RED, OUTPUT);
  randomSeed(analogRead(AL_LDR));
}

void loop() {
  static int last = HIGH;
  int cur = digitalRead(AL_BUTTON_A4);
  if (last == HIGH && cur == LOW) {
    int r = random(3);
    digitalWrite(AL_LED_GREEN, r == 0);
    digitalWrite(AL_LED_YELLOW, r == 1);
    digitalWrite(AL_LED_RED, r == 2);
    delay(200);
  }
  last = cur;
}
