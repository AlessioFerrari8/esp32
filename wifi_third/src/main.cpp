/* Wifi_03.cpp - Creazione di una rete Wifi e configurazione dell'ESP32 come Access Point */
#include <Arduino.h>
#include <WiFi.h>

// Definizione del nome della rete e della password (minimo 8 caratteri)
#include "ConfigSSID.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- Avvio Modalità Access Point ---");

  // 1. Configurazione opzionale dell'IP (Default è solitamente 192.168.4.1)
  IPAddress local_IP(172,17,10,1);
  IPAddress gateway(172,17,10,1);
  IPAddress subnet(255,255,255,0);
  WiFi.softAPConfig(local_IP, gateway, subnet);

  // 2. Attivazione dell'Access Point
  // Sintassi: WiFi.softAP(ssid, password, channel, ssid_hidden, max_connection)
  if (WiFi.softAP(ap_ssid, ap_password)) {
    Serial.println("Access Point avviato correttamente!");
  } else {
    Serial.println("Errore durante l'avvio dell'Access Point.");
  }

  // 3. Mostra l'indirizzo IP del dispositivo (il "server")
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Indirizzo IP dell'AP: ");
  Serial.println(myIP);
}

void loop() {
  // Monitoriamo quanti dispositivi sono connessi alla nostra rete
  int numStations = WiFi.softAPgetStationNum();
  
  static int lastNum = -1;
  if (numStations != lastNum) {
    Serial.printf("Dispositivi connessi: %d\n", numStations);
    lastNum = numStations;
  }

  delay(2000); // Controlla ogni 2 secondi
}
