/**
 * Title: Combination Lock
 * Description: Enter a combination using the potentiometer and button.
 */

#include "alpha.h"

int combination[] = {3, 1, 4}; // The secret combination: 3, then 1, then 4
int currentStep = 0;
int potPosition = 0;

void setup() {
  pinMode(AL_LED_RED, OUTPUT);
  pinMode(AL_LED_GREEN, OUTPUT);
  pinMode(AL_BUTTON_A4, INPUT_PULLUP);
  pinMode(AL_BUZZER, OUTPUT);
}

void loop() {
  potPosition = map(analogRead(AL_POT_A1), 0, 1023, 0, 9); // Map pot to 0-9

  if (digitalRead(AL_BUTTON_A4) == LOW) {
    delay(250); // Debounce

    if (potPosition == combination[currentStep]) {
      currentStep++;
      tone(AL_BUZZER, 1000, 100);
      if (currentStep >= 3) { // Correct combination entered!
        digitalWrite(AL_LED_GREEN, HIGH);
        delay(3000);
        digitalWrite(AL_LED_GREEN, LOW);
        currentStep = 0; // Reset lock
      }
    } else {
      // Wrong entry
      currentStep = 0;
      digitalWrite(AL_LED_RED, HIGH);
      tone(AL_BUZZER, 300, 1000);
      delay(1000);
      digitalWrite(AL_LED_RED, LOW);
    }
  }
}