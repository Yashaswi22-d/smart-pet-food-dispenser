#include <Arduino.h>
#include "HX711.h"
#include <Wire.h>

// ---------- PIN DEFINITIONS ----------
#define BUZZER_PIN 18
#define MOTOR_PIN  19

#define HX711_DT  4
#define HX711_SCK 5

HX711 scale;

// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);

  scale.begin(HX711_DT, HX711_SCK);
  scale.set_scale();
  scale.tare();

  Serial.println("Smart Pet Food Dispenser - Sensor Module Initialized");
}

// ---------- MAIN LOOP ----------
void loop() {

  // Simulated Heart Rate
  int heartRate = random(60, 100);

  // Simulated Temperature
  float temperature = random(360, 390) / 10.0;

  // Weight from Load Cell
  float weight = scale.get_units(5);

  Serial.print("Heart Rate: ");
  Serial.print(heartRate);
  Serial.println(" BPM");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" g");

  // Health-based decision
  if (heartRate > 90 || temperature > 38.5) {
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("⚠️ Health Alert!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(MOTOR_PIN, HIGH); // dispense food
    delay(2000);
    digitalWrite(MOTOR_PIN, LOW);
  }

  delay(3000);
}
