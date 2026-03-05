/* Wifi_01.cpp - Scansione per la ricerca di reti Wi-Fi */
#include <Arduino.h>
#include <WiFi.h>

int n;

// dichiarazione della funzione getEncryptionName() che ricava il tipo di protezione
String getEncryptionName(unsigned int);

void setup() {
  Serial.begin(115200);

  // Imposta il WiFi in modalità Station, ma senza effettuare la connessione
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();        // Ci si assicura di non essere connessi a qualche rete
  delay(100);

  Serial.println("Scanner WiFi pronto.");
}

void loop() {
  Serial.println("\nInizio scansione...");

  // WiFi.scanNetworks() restituisce il numero di reti trovate
  // È una funzione "bloccante": il codice aspetta che la scansione finisca
  n = WiFi.scanNetworks();
  
  Serial.println("Scansione completata.");

  if (n == 0)
    Serial.println("Nessuna rete trovata.");
  else {
    Serial.printf("%d reti trovate:\n", n);
    
    for (int i = 0; i < n; ++i) {
      // Stampa: SSID, Potenza Segnale (RSSI), Canale e Crittografia
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));           // Valore in dBm (es. -50 è ottimo, -90 è scarso)
      Serial.print(" dBm) Canale: ");
      Serial.print(WiFi.channel(i));
      
      // Ricava il tipo di protezione
      unsigned int encryptionType = WiFi.encryptionType(i);
      Serial.print(" [Sicurezza: ");
      Serial.print(getEncryptionName(encryptionType));
      Serial.println("]");
      
      delay(10);
    }
  }

  // Aspetta 5 secondi prima della prossima scansione
  delay(5000);
}

// Funzioni di supporto
// Funzione getEncryptionName(): restituisce il tipo di protezione
String getEncryptionName(unsigned int encryptionType) {
  switch (encryptionType) {
    case WIFI_AUTH_OPEN: return "Aperta";
    case WIFI_AUTH_WEP:  return "WEP";
    case WIFI_AUTH_WPA_PSK: return "WPA";
    case WIFI_AUTH_WPA2_PSK: return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA+WPA2";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2 Enterprise";
    default: return "Sconosciuta";
  }
}
