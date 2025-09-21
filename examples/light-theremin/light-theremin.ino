/**
 * Title: Light Theremin
 * Description: Creates a musical instrument where the pitch is controlled by light and volume by a pot.
 */

#include "alpha.h"

void setup() {}

void loop() {
  int lightPitch = analogRead(AL_LDR);
  int potVolume = analogRead(AL_POT_A1);

  int pitch = map(lightPitch, 0, 1023, 50, 2000); // Map light to pitch
  int volumeDelay = map(potVolume, 0, 1023, 1, 20); // Crude volume control via duty cycle

  tone(AL_BUZZER, pitch);
  delay(volumeDelay);
  noTone(AL_BUZZER);
  delay(volumeDelay);
}