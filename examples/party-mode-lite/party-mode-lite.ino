/**
 * Title: party-mode-lite
 * Description: LEDs flash, buzzer plays pattern, servo wiggles for a short show.
 */

#include "alpha.h"
#include <Servo.h>

Servo s;

void setup() {
  s.attach(AL_SERVO_D6);
  pinMode(AL_LED_GREEN, OUTPUT);
  pinMode(AL_LED_YELLOW, OUTPUT);
  pinMode(AL_LED_RED, OUTPUT);
  pinMode(AL_BUZZER, OUTPUT);
}

void loop() {
  // LED strobe
  for (int i = 0; i < 6; i++) {
    digitalWrite(AL_LED_GREEN, i % 2 == 0);
    digitalWrite(AL_LED_YELLOW, i % 3 == 0);
    digitalWrite(AL_LED_RED, i % 4 == 0);
    tone(AL_BUZZER, 500 + i * 150);
    s.write(30 + i * 20);
    delay(120);
  }
  noTone(AL_BUZZER);
  s.write(90);
  digitalWrite(AL_LED_GREEN, LOW);
  digitalWrite(AL_LED_YELLOW, LOW);
  digitalWrite(AL_LED_RED, LOW);
  delay(1000);
}
