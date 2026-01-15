#include <Arduino.h>
/*
 * Controllo intensità LED con pulsante
 * 
 * Descrizione:
 * Questo programma controlla l'intensità di un LED tramite un pulsante.
 * Ad ogni pressione del pulsante, cambia il livello di intensità del LED
 * in 5 step diversi (0%, 25%, 50%, 75%, 100%).
 * 
 * Collegamenti:
 * - LED sul pin 5
 * - Pulsante sul pin 22 (con pull-down interno)
 * 
 * Autore: Alessio Ferrari
 * Data: 2025-11-20
 */

// Definizione dei pin e parametri
#define LEDPIN 5          // Pin a cui è collegato il LED
#define FREQ 1000         // Frequenza PWM in Hz
#define pulsante 22       // Pin a cui è collegato il pulsante
#define resolution 8      // Risoluzione PWM (8 bit = 0-255)

// Variabili globali
int livello = 25;         // Incremento percentuale per ogni livello (25%)
int intensita = 0;        // Livello di intensità corrente (0-4)

bool statoVecchio = LOW;  // Stato precedente del pulsante per rilevamento fronte

void setup() {
  // Inizializzazione comunicazione seriale
  Serial.begin(9600);
  
  // Configurazione pin pulsante con resistore di pull-down interno
  pinMode(pulsante, INPUT_PULLDOWN);
  
  // Configurazione PWM per il LED
  ledcAttach(LEDPIN, FREQ, resolution);
}

void loop() {
  // Lettura stato attuale del pulsante
  bool statoAttuale = digitalRead(pulsante);

  // Rilevamento fronte di salita (pulsante appena premuto)
  if (statoAttuale == HIGH && statoVecchio == LOW) {
    
    // Calcolo intensità attuale in percentuale
    int attuale = intensita * livello;

    // Calcolo valore PWM massimo in base alla risoluzione
    int maxPWM = (1 << resolution) - 1;        // 2^8 - 1 = 255 per 8 bit
    
    // Conversione percentuale in valore PWM
    int valorePwm = attuale * maxPWM / 100;    // 25 * 255 / 100 = 63

    // Scrittura valore PWM sul LED
    ledcWrite(LEDPIN, valorePwm);

    // Incremento livello di intensità
    intensita++;
    
    // Reset del contatore dopo il livello massimo (4 = 100%)
    if (intensita > 4) intensita = 0;
    
    // Debug: stampa valori su seriale
    Serial.print("Livello: ");
    Serial.print(intensita);
    Serial.print(", Intensità: ");
    Serial.print(attuale);
    Serial.print("%, PWM: ");
    Serial.println(valorePwm);
  }

  // Aggiornamento stato precedente del pulsante
  statoVecchio = statoAttuale;
  
  // Piccolo delay per stabilità (opzionale)
  delay(10);
}