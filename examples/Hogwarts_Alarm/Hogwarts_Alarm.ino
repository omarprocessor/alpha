//The hogwarts Alarm, place it on your window pane every night and once the sun rises, the hogwarts theme will play as an alarm
//To switch it off, you either unplug it or turn the potentiometer to reduce sensitivity
//sensitivity of the light sensor can be tuned using the potentiometer
//HARDOCDED THE TUNES MYSELF 
#include <Arduino.h>

// Pins
const int lightSensorPin = A0;
const int potPin = A1;
const int buzzPin = 9;
const int greenPin = 11;
const int redPin = 13;
const int button1Pin = A4;
const int button2Pin = A5;

// Normal tune: C-D-E-F-G-A-B
int tones[] = {262, 294, 330, 349, 392, 440, 494};
int durations[] = {300, 300, 300, 300, 300, 300, 600};

// Hogwarts tune duration constants (us)
int dtc1 = 430, dtc2 = 480, dtc3 = 570, dtc4 = 470, dtc5 = 620;
int dtc6 = 860, dtc7 = 650, dtc8 = 550, dtc9 = 590, dtc10 = 650;
int dtc11 = 700, dtc12 = 570, dtc13 = 850;

bool alarmActive = false;

// Sound generator for Hogwarts-style tone
void beep(int duration, int delayMicro) {
  for (int i = 0; i < duration; i++) {
    digitalWrite(buzzPin, HIGH);
    delayMicroseconds(delayMicro);
    digitalWrite(buzzPin, LOW);
    delayMicroseconds(delayMicro);
  }
}

void playSimpleTune() {
  for (int i = 0; i < 7; i++) {
    tone(buzzPin, tones[i]);
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
    delay(durations[i]);
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    noTone(buzzPin);
    delay(100);
  }
  digitalWrite(redPin, LOW);
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

void setup() {
  Serial.begin(9600);
  pinMode(buzzPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
}

void loop() {
  int lightVal = analogRead(lightSensorPin);
  int potVal = analogRead(potPin);
  int threshold = map(potVal, 0, 1023, 50, 800);

  Serial.print("Light: ");
  Serial.print(lightVal);
  Serial.print(" | Threshold: ");
  Serial.println(threshold);

  // Button cancel (both buttons stop alarm)
  if (digitalRead(button1Pin) == HIGH || digitalRead(button2Pin) == HIGH) {
    Serial.println("Everything off");
    digitalWrite(buzzPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    delay(30); // debounce
    return;
  }

  if (lightVal > threshold) {
    Serial.println("Threshold things should be playing");
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
    playHogwartsTune();
    delay(100);
  } else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }

  // Manual Hogwarts Alarm
  if (digitalRead(button1Pin) == HIGH || digitalRead(button2Pin) == HIGH) {
    playSimpleTune();
  }
}
