/**
 * Title: Temperature Alert
 * Description: The red LED turns on if the temperature (from NTC) is above a threshold.
 */

#include "alpha.h"

void setup() {
  pinMode(AL_LED_RED, OUTPUT);
}

void loop() {
  int ntcValue = analogRead(AL_NTC);

  if (ntcValue > 700) { // Adjust this threshold based on your NTC's calibration
    digitalWrite(AL_LED_RED, HIGH);
  } else {
    digitalWrite(AL_LED_RED, LOW);
  }
  delay(100);
}