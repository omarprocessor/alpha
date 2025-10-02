/**
 * Title: pot-balance
 * Description: Turns on buzzer with tone when two potentiometers are unbalanced.
 */

#include "alpha.h"

#define DIFF_THRESHOLD 100  // Minimum difference to trigger buzzer
#define BUZZER_FREQ 1000    // Frequency of buzzer tone in Hz

void setup() {
 pinMode(AL_BUZZER, OUTPUT); // Set buzzer pin as output
}

void loop() {
 int a = analogRead(AL_POT_A1); // Read first potentiometer
 int b = analogRead(AL_POT_A2); // Read second potentiometer

 // If the absolute difference exceeds the threshold, turn on tone
 if (abs(a - b) > DIFF_THRESHOLD) {
  tone(AL_BUZZER, BUZZER_FREQ); // Play buzzer tone
 } else {
  noTone(AL_BUZZER); // Stop buzzer
 }
}
