/**
 * Title: button-led-cycle
 * Description: Button cycles through green -> yellow -> red.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_BUTTON_A4, INPUT_PULLUP);
  pinMode(AL_LED_GREEN, OUTPUT);
  pinMode(AL_LED_YELLOW, OUTPUT);
  pinMode(AL_LED_RED, OUTPUT);
}

void loop() {
  static int idx = 0;
  static int last = HIGH;
  int cur = digitalRead(AL_BUTTON_A4);
  if (last == HIGH && cur == LOW) {
    idx = (idx + 1) % 3;
    digitalWrite(AL_LED_GREEN, idx == 0);
    digitalWrite(AL_LED_YELLOW, idx == 1);
    digitalWrite(AL_LED_RED, idx == 2);
    delay(150);
  }
  last = cur;
}
