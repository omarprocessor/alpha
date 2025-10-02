/**
 * Title: ldr-pulse
 * Description: Green LED pulses faster as light level falls.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_LED_GREEN, OUTPUT);
}

void loop() {
  int val = analogRead(AL_LDR);
  int delayMs = map(val, 0, 1023, 20, 400); // darker -> faster
  analogWrite(AL_LED_GREEN, map(val, 0, 1023, 255, 50));
  delay(delayMs);
}
