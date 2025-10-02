/**
 * Title: button-long-short
 * Description: Short press toggles green, long press sounds buzzer.
 */

#include "alpha.h"

#define LONG_MS 800

void setup() {
  pinMode(AL_BUTTON_A4, INPUT_PULLUP);
  pinMode(AL_LED_GREEN, OUTPUT);
  pinMode(AL_BUZZER, OUTPUT);
}

void loop() {
  if (digitalRead(AL_BUTTON_A4) == LOW) {
    unsigned long start = millis();
    while (digitalRead(AL_BUTTON_A4) == LOW) delay(10);
    unsigned long dur = millis() - start;
    if (dur > LONG_MS) {
      tone(AL_BUZZER, 1000);
      delay(400);
      noTone(AL_BUZZER);
    } else {
      digitalWrite(AL_LED_GREEN, !digitalRead(AL_LED_GREEN));
    }
    delay(100);
  }
}
