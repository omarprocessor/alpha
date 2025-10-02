/**
 * Title: button-press-counter
 * Description: Counts presses and prints count over Serial.
 */

#include "alpha.h"

void setup() {
  Serial.begin(9600);
  pinMode(AL_BUTTON_A4, INPUT_PULLUP);
}

void loop() {
  static int last = HIGH;
  static unsigned long count = 0;
  int cur = digitalRead(AL_BUTTON_A4);
  if (last == HIGH && cur == LOW) {
    count++;
    Serial.print("Press count: ");
    Serial.println(count);
    delay(150);
  }
  last = cur;
}
