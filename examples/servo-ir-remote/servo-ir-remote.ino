/**
 * Title: Servo IR Remote
 * Description: Controls a servo's position using commands from an IR remote.
 */

#include <IRremote.h>
#include <Servo.h>

#include "alpha.h"

IRrecv irrecv(AL_IR_RX);
decode_results results;
Servo myServo;
int servoAngle = 90; // Start at center

void setup() {
  irrecv.enableIRIn();
  myServo.attach(AL_SERVO_D5);
  myServo.write(servoAngle);
}

void loop() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case 0xFF18E7: // Example: NEC "2" button - move up
        servoAngle = min(servoAngle + 10, 180);
        break;
      case 0xFF4AB5: // Example: NEC "8" button - move down
        servoAngle = max(servoAngle - 10, 0);
        break;
    }
    myServo.write(servoAngle);
    irrecv.resume();
  }
  delay(100);
}