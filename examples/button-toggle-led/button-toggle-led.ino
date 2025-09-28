/**
 * Title: Button Toggle LED
 * Description: Press the button to toggle the red LED on or off.
 */

#include "alpha.h"

bool ledState = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(AL_LED_RED, OUTPUT);
  pinMode(AL_BUTTON_A4, INPUT_PULLUP);
}

void loop() {
  bool currentButtonState = digitalRead(AL_BUTTON_A4);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    ledState = !ledState;
    digitalWrite(AL_LED_RED, ledState);
    delay(50); // Simple debounce
  }
  lastButtonState = currentButtonState;
}