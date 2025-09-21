/**
 * Title: LDR Buzzer
 * Description: The buzzer beeps faster as the light level decreases.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_BUZZER, OUTPUT);
}

void loop() {
  int lightLevel = analogRead(AL_LDR);
  int delayTime = map(lightLevel, 0, 1023, 50, 1000);

  digitalWrite(AL_BUZZER, HIGH);
  delay(50);
  digitalWrite(AL_BUZZER, LOW);
  delay(delayTime);
}