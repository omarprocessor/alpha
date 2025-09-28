/**
 * Title: Melody Composer
 * Description: Use the potentiometer to select notes and the button to record/play a melody.
 */

#include "alpha.h"

#define MAX_NOTES 20
int melody[MAX_NOTES];
int currentNote = 0;
bool recording = false;

int notes[] = {262, 294, 330, 349, 392, 440, 494, 523}; // C Major Scale

void setup() {
  pinMode(AL_BUTTON_A4, INPUT_PULLUP);
  pinMode(AL_LED_RED, OUTPUT);
}

void loop() {
  int potValue = analogRead(AL_POT_A1);
  int noteIndex = map(potValue, 0, 1023, 0, 7);
  tone(AL_BUZZER, notes[noteIndex], 100); // Preview the note

  if (digitalRead(AL_BUTTON_A4) == LOW) {
    delay(250); // Debounce
    if (!recording) {
      // Start recording
      recording = true;
      currentNote = 0;
      digitalWrite(AL_LED_RED, HIGH);
    } else {
      // Stop recording and play back
      recording = false;
      digitalWrite(AL_LED_RED, LOW);
      for (int i = 0; i < currentNote; i++) {
        tone(AL_BUZZER, melody[i], 300);
        delay(350);
      }
    }
  }

  if (recording && currentNote < MAX_NOTES) {
    melody[currentNote] = notes[noteIndex];
    currentNote++;
    delay(300); // Time to record each note
  }
  delay(100);
}