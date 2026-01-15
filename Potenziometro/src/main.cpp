#include <Arduino.h>

const int pin_tap = 34;
const int freq = 1000;
const int resolution = 8;
const int pin_led = 27;
const int channel = 0;

void setup() {
  ledcAttachPin(pin_led, channel);
  ledcSetup(channel, freq, resolution);
  ledcWrite(pin_led, 0);   // LED spento all’inizio
  Serial.begin(115200);
}

void loop() {
  // 12 bit
  int val = analogRead(pin_tap); // 0–4095 
  int pwm_val = map(val, 0, 4095, 0, 255); // adattiamo al range 8-bit
  ledcWrite(pin_led, pwm_val);   // LED spenti all’inizio
  if (val != 0){
    // stampo il valore
    Serial.println(val); 
  }

}