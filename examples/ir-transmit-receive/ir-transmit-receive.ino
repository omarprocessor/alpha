/**
 * Title: IR Transmit Receive
 * Description: Sends an IR signal and checks if it's received. Lights green LED on success.
 */

#include <IRremote.h>

#include "alpha.h"

IRsend irsend(AL_IR_TX);
IRrecv irrecv(AL_IR_RX);
decode_results results;

void setup() {
  pinMode(AL_LED_GREEN, OUTPUT);
  irrecv.enableIRIn();
}

void loop() {
  irsend.sendNEC(0x20DF10EF, 32); // Send a NEC code (e.g., from a common remote)
  delay(100);

  if (irrecv.decode(&results)) {
    digitalWrite(AL_LED_GREEN, HIGH);
    delay(100);
    digitalWrite(AL_LED_GREEN, LOW);
    irrecv.resume();
  }
  delay(1000);
}