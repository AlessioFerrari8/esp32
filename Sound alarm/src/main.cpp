#include <Arduino.h>

const int buzzerPin = 23;
const int digitalPin = 5;   // KY-037 digital interface
const int analogPin = 32;   // KY-037 analog interface
int digitalVal;       // digital readings
int analogVal;        // analog readings


unsigned long lastPrint = 0;
const unsigned long interval = 500;

void setup() {
  ledcSetup(0, 2000, 8);
  ledcAttachPin(buzzerPin, 0);
  pinMode(digitalPin,INPUT); 
  pinMode(analogPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  analogVal = analogRead(analogPin);
  digitalVal = digitalRead(digitalPin);

  if (millis() - lastPrint >= interval) {
    lastPrint = millis();
    Serial.print("Analog: ");
    Serial.print(analogVal);
    Serial.print("\n");
  }

  if (analogVal > 100) {
    ledcWrite(0, 128); // suona
    delay(1000);
  } else {
    ledcWrite(0, 0);   // silenzio
    delay(1000);
  }
}