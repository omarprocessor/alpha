/**
 * Title: Reaction Game
 * Description: Wait for the green light, then see how fast you can press the button!
 */

#include "alpha.h"

unsigned long startTime;
unsigned long reactionTime;
bool waiting = false;

void setup() {
  pinMode(AL_LED_RED, OUTPUT);
  pinMode(AL_LED_GREEN, OUTPUT);
  pinMode(AL_BUTTON_A4, INPUT_PULLUP);
  randomSeed(analogRead(A0));
}

void loop() {
  if (!waiting) {
    digitalWrite(AL_LED_RED, HIGH); // "Don't press yet"
    delay(random(2000, 5000));      // Random wait
    digitalWrite(AL_LED_RED, LOW);
    digitalWrite(AL_LED_GREEN, HIGH); // "Press now!"
    startTime = millis();
    waiting = true;
  }

  if (waiting && digitalRead(AL_BUTTON_A4) == LOW) {
    reactionTime = millis() - startTime;
    waiting = false;
    digitalWrite(AL_LED_GREEN, LOW);
    // Provide feedback via buzzer
    tone(AL_BUZZER, 1000, 200);
    delay(1000);
  }
}