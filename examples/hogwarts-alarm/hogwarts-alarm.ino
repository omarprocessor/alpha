/**
 * Title: Hogwarts Sunrise Alarm
 * Description: Plays the Hogwarts theme when sunlight hits the window. Sensitivity adjustable with potentiometer. 
 */

#include "alpha.h"

// Pin Definitions
#define AL_BUZZER      9
#define AL_IR_TX       4
#define AL_SERVO_D5    5
#define AL_SERVO_D6    6
#define AL_IR_RX       7
#define AL_LED_GREEN  11
#define AL_LED_YELLOW 12
#define AL_LED_RED    13

#define AL_LDR        A0
#define AL_POT_A1     A1
#define AL_POT_A2     A2
#define AL_NTC        A3
#define AL_BUTTON_A4  A4
#define AL_BUTTON_A5  A5

// Hogwarts tune durations (us)
int dtc1 = 430, dtc2 = 480, dtc3 = 570, dtc4 = 470, dtc5 = 620;
int dtc6 = 860, dtc7 = 650, dtc8 = 550, dtc9 = 590, dtc10 = 650;
int dtc11 = 700, dtc12 = 570, dtc13 = 850;

// Simple tune: C-D-E-F-G-A-B
int tones[] = {262, 294, 330, 349, 392, 440, 494};
int durations[] = {300, 300, 300, 300, 300, 300, 600};

bool alarmActive = false;

// Function Declarations
void beep(int duration, int delayMicro);
void playHogwartsTune();
void playSimpleTune();

void setup() {
  Serial.begin(9600);
  pinMode(AL_BUZZER, OUTPUT);
  pinMode(AL_LED_GREEN, OUTPUT);
  pinMode(AL_LED_RED, OUTPUT);
  pinMode(AL_BUTTON_A4, INPUT_PULLUP);
  pinMode(AL_BUTTON_A5, INPUT_PULLUP);
}

void loop() {
  int lightVal = analogRead(AL_LDR);
  int potVal = analogRead(AL_POT_A1);
  int threshold = map(potVal, 0, 1023, 50, 800);

  Serial.print("Light: ");
  Serial.print(lightVal);
  Serial.print(" | Threshold: ");
  Serial.println(threshold);

  // Stop everything if either button is pressed
  if (digitalRead(AL_BUTTON_A4) == HIGH || digitalRead(AL_BUTTON_A5) == HIGH) {
    Serial.println("Manual stop triggered");
    digitalWrite(AL_BUZZER, LOW);
    digitalWrite(AL_LED_GREEN, LOW);
    digitalWrite(AL_LED_RED, HIGH);
    delay(30); // debounce
    return;
  }

  // Auto trigger when light exceeds threshold
  if (lightVal > threshold && !alarmActive) {
    Serial.println("Light threshold exceeded: Playing Hogwarts tune");
    digitalWrite(AL_LED_GREEN, HIGH);
    digitalWrite(AL_LED_RED, LOW);
    playHogwartsTune();
    delay(100);
  } else {
    digitalWrite(AL_LED_RED, HIGH);
    digitalWrite(AL_LED_GREEN, LOW);
  }

  // Manual test: play simple C→B tune
  if (digitalRead(AL_BUTTON_A4) == HIGH || digitalRead(AL_BUTTON_A5) == HIGH) {
    playSimpleTune();
  }
}

// Functions
void beep(int duration, int delayMicro) {
  for (int i = 0; i < duration; i++) {
    digitalWrite(AL_BUZZER, HIGH);
    delayMicroseconds(delayMicro);
    digitalWrite(AL_BUZZER, LOW);
    delayMicroseconds(delayMicro);
  }
}

void playSimpleTune() {
  for (int i = 0; i < 7; i++) {
    tone(AL_BUZZER, tones[i]);
    digitalWrite(AL_LED_GREEN, HIGH);
    digitalWrite(AL_LED_RED, LOW);
    delay(durations[i]);
    digitalWrite(AL_LED_GREEN, LOW);
    digitalWrite(AL_LED_RED, HIGH);
    noTone(AL_BUZZER);
    delay(100);
  }
  digitalWrite(AL_LED_RED, LOW);
}

void playHogwartsTune() {
  alarmActive = true;

  beep(220, dtc6);
  delay(30);
  beep(540, dtc7);
  delay(10);
  beep(200, dtc8);
  beep(300, dtc9);
  beep(600, dtc10);
  beep(640, dtc1);
  beep(1100, dtc2);
  beep(890, dtc3);
  beep(500, dtc7);
  beep(200, dtc8);
  beep(200, dtc9);
  beep(550, dtc11);
  beep(400, dtc12);
  beep(550, dtc13);

  delay(1000);
  alarmActive = false;
}
