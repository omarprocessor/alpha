/**
 * Title: Dual Servo Control with Potentiometers
 * Description: Controls two external servo motors using the two on-board potentiometers (AL_POT_A1 and AL_POT_A2).
 */

#include "alpha.h"
#include <Servo.h>

// Defines
#define SERVO1_PIN AL_SERVO_D5
#define SERVO2_PIN AL_SERVO_D6
#define POT1_PIN AL_POT_A1
#define POT2_PIN AL_POT_A2

// Library objects
Servo servo1;  // First servo motor
Servo servo2;  // Second servo motor

// Function declarations (none needed for now)

void setup() {
  servo1.attach(SERVO1_PIN);  // Connect servo1 to defined pin
  servo2.attach(SERVO2_PIN);  // Connect servo2 to defined pin
}

void loop() {
  int pot1Value = analogRead(POT1_PIN);  // Read value from potentiometer 1 (0–1023)
  int pot2Value = analogRead(POT2_PIN);  // Read value from potentiometer 2

  int angle1 = map(pot1Value, 0, 1023, 0, 180); // Map to servo angle
  int angle2 = map(pot2Value, 0, 1023, 0, 180);

  servo1.write(angle1);  // Move servo 1
  servo2.write(angle2);  // Move servo 2

  delay(10); // Short delay for servo stability
}


