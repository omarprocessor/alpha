/**
 * Title: Debate Timer Auto
 * Description: Timed speaking turns for two speakers with automatic switch-over, OLED countdown, LEDs, and buzzer alerts.
 */

#include "alpha.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// === OLED Settings ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// === Timer Settings ===
unsigned long SPEAK_TIME = 40000;  // default speaking time (ms)
unsigned long SWITCH_TIME = 3000;  // 3-second switch-over (ms)

// === State Variables ===
bool speakerATurn = true;
bool switchOver = false;
unsigned long turnStart = 0;
unsigned long switchStart = 0;
bool warningGiven = false;
bool timeExpired = false;
int lastSeconds = -1;

// === Red LED flash control ===
unsigned long lastRedBlink = 0;
bool redState = false;

void setup() {
  Serial.begin(9600);

  pinMode(AL_LED_GREEN, OUTPUT);
  pinMode(AL_LED_YELLOW, OUTPUT);
  pinMode(AL_LED_RED, OUTPUT);
  pinMode(AL_BUZZER, OUTPUT);

  clearAll();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("🕒 Debate Timer Auto");
  display.display();

  // Prompt for custom time
  promptTime();

  // Start first speaker automatically
  startTurn();
}

void loop() {
  if (switchOver) {
    unsigned long elapsed = millis() - switchStart;
    int remaining = (SWITCH_TIME > elapsed) ? (SWITCH_TIME - elapsed) / 1000 + 1 : 0;

    displaySwitchCountdown(remaining);
    digitalWrite(AL_LED_YELLOW, HIGH);
    digitalWrite(AL_LED_GREEN, LOW);

    if (elapsed >= SWITCH_TIME) {
      switchOver = false;
      speakerATurn = !speakerATurn;  // switch speaker
      startTurn();
    }
  } else {
    manageTimer();
  }
}

// Prompt for speaking time
void promptTime() {
  Serial.println("⏱️ Enter debate time in seconds (or default 40s): ");
  while (!Serial.available()) delay(10);
  int sec = Serial.parseInt();
  if (sec > 0) SPEAK_TIME = sec * 1000UL;

  Serial.print("✅ Speaking time set: ");
  Serial.print(SPEAK_TIME / 1000);
  Serial.println(" s");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speaking time: ");
  display.print(SPEAK_TIME / 1000);
  display.println(" s");
  display.display();
}

// Start a turn
void startTurn() {
  tone(AL_BUZZER, 1500, 200);  // single beep
  turnStart = millis();
  warningGiven = false;
  timeExpired = false;
  lastSeconds = -1;
  clearAll();
  digitalWrite(AL_LED_GREEN, HIGH);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speaker ");
  display.print(speakerATurn ? "A" : "B");
  display.println(" speaking");
  display.display();

  Serial.print("🎙️ Speaker ");
  Serial.print(speakerATurn ? "A" : "B");
  Serial.println(" speaking...");
}

// End turn automatically
void endTurn() {
  clearAll();
  timeExpired = false;
  switchOver = true;
  switchStart = millis();

  tone(AL_BUZZER, 1500, 200);
  delay(250);
  tone(AL_BUZZER, 1500, 200);  // double beep

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speaker ");
  display.print(speakerATurn ? "A" : "B");
  display.println(" ended");
  display.display();

  Serial.print("✅ Speaker ");
  Serial.print(speakerATurn ? "A" : "B");
  Serial.println(" ended turn.");
}

// Timer management
void manageTimer() {
  unsigned long elapsed = millis() - turnStart;
  unsigned long remaining = (SPEAK_TIME > elapsed) ? SPEAK_TIME - elapsed : 0;
  int secondsLeft = remaining / 1000;

  // Countdown beeps last 3 seconds
  if (secondsLeft <= 3 && secondsLeft > 0 && secondsLeft != lastSeconds) {
    tone(AL_BUZZER, 2000 - (3 - secondsLeft) * 400, 150);
    lastSeconds = secondsLeft;
  }

  // 80% warning - flash red LED
  if (!warningGiven && elapsed >= SPEAK_TIME * 0.8) {
    warningGiven = true;
    Serial.println("⚠️ 80% time used");
  }

  if (warningGiven) {
    if (millis() - lastRedBlink > 400) {
      lastRedBlink = millis();
      redState = !redState;
      digitalWrite(AL_LED_RED, redState ? HIGH : LOW);
    }
  } else {
    digitalWrite(AL_LED_RED, LOW);
  }

  // Time expired
  if (elapsed >= SPEAK_TIME && !timeExpired) {
    timeExpired = true;
    digitalWrite(AL_LED_GREEN, LOW);
    digitalWrite(AL_LED_YELLOW, HIGH);
    endTurn();
  }

  // Update OLED countdown
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speaker ");
  display.print(speakerATurn ? "A" : "B");
  display.println(" speaking");
  display.setCursor(0, 20);
  display.print("Time left: ");
  display.print(secondsLeft);
  display.println(" s");

  if (warningGiven) {
    display.setCursor(0, 40);
    display.println("⚠️ 80% time used");
  }

  display.display();
}

// Display switch-over countdown
void displaySwitchCountdown(int seconds) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("🔄 Switch-over");
  display.setCursor(0, 20);
  display.print("Next speaker in: ");
  display.print(seconds);
  display.println(" s");
  display.display();
}

// Reset LEDs & buzzer
void clearAll() {
  digitalWrite(AL_LED_GREEN, LOW);
  digitalWrite(AL_LED_YELLOW, LOW);
  digitalWrite(AL_LED_RED, LOW);
  noTone(AL_BUZZER);
}
