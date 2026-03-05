/* Wifi_02.cpp - Connessione alla rete specificata nel file ConfigWifi.h e visualizzazione dell'IPv4 assegnato dal DHCP*/
#include <Arduino.h>
#include <WiFi.h>
#include "ConfigWifi.h"

const int LED_ON_BOARD = 2;

// dichiarazione funzioni di servizio

void setup() {
  Serial.begin(115200);
  pinMode(LED_ON_BOARD, OUTPUT);
  // Imposta l'ESP32 in modalità Station
  WiFi.mode(WIFI_STA); 
  
  Serial.println("\nConnessione in corso...");
  WiFi.begin(ssid, password);

  // Attende finché la connessione non è stabilita
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnesso correttamente!");
  Serial.print("Indirizzo IP locale: ");
  Serial.println(WiFi.localIP());           // Stampa l'IP assegnato dal DHCP
}

void loop() {
  digitalWrite(LED_ON_BOARD, HIGH);
  delay(1000);
  digitalWrite(LED_ON_BOARD, LOW);
  delay(1000);
}

// definizione funzioni di servizio
