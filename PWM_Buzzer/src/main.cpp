#include <Arduino.h>

/*
 * Controllo intensità LED con PULSANTE (versione corretta con fronte di salita)
 */

#define LED1 5
#define LED2 14
#define LED3 15
#define LED4 23
#define BUZZER 33

#define FREQ 1000
#define PULSANTE 22
#define RESOLUTION 8

int led[] = {LED1, LED2, LED3, LED4};
int melodia[] = {330, 330, 330, 330, 330, 330, 330, 392, 262, 294, 330};
int pausa[] = {300, 300, 600, 300, 300, 600, 300, 300, 300, 300, 600};
int pausaNote[] = {50, 50, 80, 50, 50, 80, 30, 30, 30, 30, 60};
int LUNGHEZZA_MELODIA = 11;
int numLed = 4;
int iLed[] = {0, 0, 0, 0};
bool luci = false;

void IRAM_ATTR interrompi() {
  luci = !luci; // cambia stato
}

bool statoVecchio = LOW;  // Per rilevare il fronte

void setup() {
  Serial.begin(9600);
  pinMode (BUZZER, OUTPUT);
  pinMode(PULSANTE, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PULSANTE), interrompi, RISING);
  for (int i = 0; i < numLed; i++) {
    ledcAttach(led[i], FREQ, RESOLUTION);
    ledcWrite(led[i], 0);   // LED spenti all’inizio
  }
}

void loop() {
  noTone(BUZZER);

  // Riconosco il FRONTE DI SALITA (click)
  if(luci) {
    int maxPWM = (1 << RESOLUTION) - 1;
    noTone(BUZZER);
    // Imposta valori casuali
    for (int i = 0; i < numLed; i++) {
      int valore;
      for(int i = 0; i < 4; i++) {
        valore = random(0, maxPWM + 1);
        if (iLed[i] != valore) {
           iLed[i] = valore;
        } else {
          valore = random(0, maxPWM + 1);
        }
      }
      ledcWrite(led[i], valore);
    }
    delay(150);
    
  } else {
    for (int i = 0; i < LUNGHEZZA_MELODIA; i++){
      tone(BUZZER, melodia[i]); delay(pausa[i]); noTone(BUZZER);
    }
    tone(BUZZER, 330); delay(300); noTone(BUZZER); delay(50); // Mi
    tone(BUZZER, 330); delay(300); noTone(BUZZER); delay(50); // Mi
    tone(BUZZER, 330); delay(600); noTone(BUZZER); delay(80); // Mi lunga
  
    tone(BUZZER, 330); delay(300); noTone(BUZZER); delay(50); // Mi
    tone(BUZZER, 330); delay(300); noTone(BUZZER); delay(50); // Mi
    tone(BUZZER, 330); delay(600); noTone(BUZZER); delay(80); // Mi lunga
  
    tone(BUZZER, 330); delay(300); noTone(BUZZER); delay(30); // Mi
    tone(BUZZER, 392); delay(300); noTone(BUZZER); delay(30); // Sol
    tone(BUZZER, 262); delay(300); noTone(BUZZER); delay(30); // Do
    tone(BUZZER, 294); delay(300); noTone(BUZZER); delay(30); // Re
    tone(BUZZER, 330); delay(600); noTone(BUZZER); delay(60); // Mi
  
    delay(500); // pausa prima del loop
  }
  
}