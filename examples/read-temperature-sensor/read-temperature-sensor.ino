/**
 * Title: read-print-temperature
 * Description: Reads the temperature sensor values, calculates and converts the value to degrees celcius and returns and prints that
 */


#include "alpha.h"

// Constants (adjust to your thermistor/resistor values)
const float SERIES_RESISTOR      = 10000.0;  // Ω
const float NOMINAL_RESISTANCE   = 10000.0;  // Ω at 25 °C
const float NOMINAL_TEMPERATURE  = 25.0;     // °C
const float BETA_COEFFICIENT     = 3950.0;   // K
const int   ADC_MAX              = 1023;     // 10‑bit ADC
const float SUPPLY_VOLTAGE       = 5.0;      // V

/**
 * Reads a 10 kΩ NTC thermistor on the given analog pin and returns the temperature in °C.
 *
 * @param pin  Analog pin number (e.g. A0)
 * @return     Temperature in degrees Celsius
 */
float readNTCTemperature(int pin) {
  int raw = analogRead(pin);
  float voltage = (raw / float(ADC_MAX)) * SUPPLY_VOLTAGE;

  // Correct divider formula:
  float resistance = SERIES_RESISTOR * (voltage / (SUPPLY_VOLTAGE - voltage));

  // Steinhart‑Hart (Beta) equation:
  float steinhart = resistance / NOMINAL_RESISTANCE;     // R/R0
  steinhart = log(steinhart);                            // ln(R/R0)
  steinhart /= BETA_COEFFICIENT;                         // 1/B * ln(R/R0)
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);     // + (1/T0)
  steinhart = 1.0 / steinhart;                           // T in Kelvin

  return steinhart - 273.15;                             // → °C
}



void setup() {
  pinMode(AL_NTC, INPUT);
  Serial.begin(9600);

}

void loop() {
  Serial.println(readNTCTemperature(AL_NTC));

}
