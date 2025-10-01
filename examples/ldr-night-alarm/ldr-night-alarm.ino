/**
 * Title: ldr-night-alarm
 * Description: Turns buzzer on in sustained darkness.
 */

#include "alpha.h"

#define DARK_THRESHOLD 200
#define DARK_COUNT_REQ 5

void setup() {
  pinMode(AL_BUZZER, OUTPUT);
}

void loop() {
  static int count = 0;
  int v = analogRead(AL_LDR);
  if (v < DARK_THRESHOLD) {
    count++;
    if (count >= DARK_COUNT_REQ) tone(AL_BUZZER, 1000);
  } else {
    count = 0;
    noTone(AL_BUZZER);
  }
  delay(300);
}
