/* Wifi_02.cpp - Connessione alla rete specificata nel file ConfigWifi.h e visualizzazione dell'IPv4 assegnato dal DHCP*/
#include <Arduino.h>
#include <WiFi.h>
#include "ConfigWifi.h"
#include <ESP32Ping.h>


const int LED_ON_BOARD = 2;
IPAddress remoteESP32(192, 168, 5, 254); 

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
  Serial.println(WiFi.subnetMask());
  Serial.println(WiFi.gatewayIP());

  Serial.print("Ping");
  Serial.print(remoteESP32);
  Serial.print("...");

  // ping con 5 pacchetti
  bool success = Ping.ping(remoteESP32, 5);

  if (success) {
  Serial.println("Ping a buon fine");
  } else {
  Serial.println("Nope. L’altro esp non risponde");
  }

}

void loop() {
  digitalWrite(LED_ON_BOARD, HIGH);
  delay(1000);
  digitalWrite(LED_ON_BOARD, LOW);
  delay(1000);
}

// definizione funzioni di servizio
