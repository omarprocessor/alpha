/**
 * Title: Mood Lamp
 * Description: Fades the LEDs through different colors based on potentiometer input.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_LED_RED, OUTPUT);
  pinMode(AL_LED_YELLOW, OUTPUT);
  pinMode(AL_LED_GREEN, OUTPUT);
}

void loop() {
  int potValue = analogRead(AL_POT_A1);
  int stage = map(potValue, 0, 1023, 0, 5);

  switch (stage) {
    case 0: // Red
      analogWrite(AL_LED_RED, 255);
      analogWrite(AL_LED_YELLOW, 0);
      analogWrite(AL_LED_GREEN, 0);
      break;
    case 1: // Orange
      analogWrite(AL_LED_RED, 255);
      analogWrite(AL_LED_YELLOW, 100);
      analogWrite(AL_LED_GREEN, 0);
      break;
    case 2: // Yellow
      analogWrite(AL_LED_RED, 100);
      analogWrite(AL_LED_YELLOW, 255);
      analogWrite(AL_LED_GREEN, 0);
      break;
    case 3: // Green
      analogWrite(AL_LED_RED, 0);
      analogWrite(AL_LED_YELLOW, 0);
      analogWrite(AL_LED_GREEN, 255);
      break;
    case 4: // Cyan
      analogWrite(AL_LED_RED, 0);
      analogWrite(AL_LED_YELLOW, 100);
      analogWrite(AL_LED_GREEN, 255);
      break;
    case 5: // White
      analogWrite(AL_LED_RED, 255);
      analogWrite(AL_LED_YELLOW, 255);
      analogWrite(AL_LED_GREEN, 255);
      break;
  }
  delay(10);
}