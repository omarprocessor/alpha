/**
 * Title: sos-morse
 * Description: Blink LED and buzz Morse code for "SOS".
 */

#include "alpha.h"

void dot() { digitalWrite(AL_LED_RED, HIGH); tone(AL_BUZZER, 800); delay(200); digitalWrite(AL_LED_RED, LOW); noTone(AL_BUZZER); delay(200); }
void dash() { digitalWrite(AL_LED_RED, HIGH); tone(AL_BUZZER, 800); delay(600); digitalWrite(AL_LED_RED, LOW); noTone(AL_BUZZER); delay(200); }

void setup() {
  pinMode(AL_LED_RED, OUTPUT);
  pinMode(AL_BUZZER, OUTPUT);
}

void loop() {
  // S: ...  O: ---  S: ...
  dot(); dot(); dot();
  delay(400);
  dash(); dash(); dash();
  delay(400);
  dot(); dot(); dot();
  delay(2000);
}
