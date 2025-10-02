/**
 * Title: ir-object-counter
 * Description: Counts objects passing the IR beam and prints on Serial.
 */

#include "alpha.h"

void setup() {
  Serial.begin(9600);
  pinMode(AL_IR_RX, INPUT);
}

void loop() {
  static int last = HIGH;
  static unsigned long count = 0;
  int cur = digitalRead(AL_IR_RX);
  if (last == HIGH && cur == LOW) {
    count++;
    Serial.print("Objects: ");
    Serial.println(count);
    delay(150);
  }
  last = cur;
}
