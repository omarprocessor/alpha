/**
 * Title: Serial Controlled LED
 * Description: Type 'r', 'y', or 'g' in the Serial Monitor to turn the respective LED on or off.
 */

#include "alpha.h"

void setup() {
  Serial.begin(9600);
  pinMode(AL_LED_RED, OUTPUT);
  pinMode(AL_LED_YELLOW, OUTPUT);
  pinMode(AL_LED_GREEN, OUTPUT);
  Serial.println("Send 'r', 'y', or 'g' to toggle LEDs.");
}

void loop() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    toggleLED(incomingByte);
  }
}

void toggleLED(char ledColor) {
  int pin;
  switch (ledColor) {
    case 'r': pin = AL_LED_RED; break;
    case 'y': pin = AL_LED_YELLOW; break;
    case 'g': pin = AL_LED_GREEN; break;
    default: return; // Ignore other characters
  }
  bool currentState = digitalRead(pin);
  digitalWrite(pin, !currentState);
  Serial.print("Toggled LED ");
  Serial.println(ledColor);
}