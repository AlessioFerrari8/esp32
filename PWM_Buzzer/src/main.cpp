/*
 * Controllo intensità LED con PULSANTE (versione corretta con fronte di salita)
 */


//definizione pin
#define LED1 5
#define LED2 14
#define LED3 15
#define LED4 23
#define BUZZER 33
#define PULSANTE 22


//definizione costanti per PWM
#define FREQ 1000
#define RESOLUTION 8


//definizione variabili globali
//array pin LED
int led[] = {LED1, LED2, LED3, LED4};
//Array con melodia e pause per buzzer
int melodia[] = {330, 330, 330, 330, 330, 330, 330, 392, 262, 294, 330};
int pausa[] = {300, 300, 600, 300, 300, 600, 300, 300, 300, 300, 600};
int pausaNote[] = {50, 50, 80, 50, 50, 80, 30, 30, 30, 30, 60};
//Lunghezza array melodia, non esiste funzione length in C++
int LUNGHEZZA_MELODIA = 11;
//Lunghezza array LED
int numLed = 4;
//Array per memorizzare valori di intensità LED per PWM
int iLed[] = {0, 0, 0, 0};
//Valore massimo per PWM
int maxPWM = (1 << RESOLUTION) - 1;
//variabile per stato luci o buzzer
bool luci = false;


//funzione di interrupt per cambio stato luci/buzzer, viene eseguita al fronte di salita del pulsante
void IRAM_ATTR handleInterrupt() {
  luci = !luci; // cambia stato
}


void setup() {
  Serial.begin(9600);
  //configurazione pin
  pinMode (BUZZER, OUTPUT);
  pinMode(PULSANTE, INPUT_PULLUP);
  //configurazione interrupt sul pulsante
  attachInterrupt(digitalPinToInterrupt(PULSANTE), handleInterrupt, RISING);
  //configurazione canali PWM per i LED
  for (int i = 0; i < numLed; i++) {
    ledcAttach(led[i], FREQ, RESOLUTION);
    ledcWrite(led[i], 0);   // LED spenti all’inizio
  }
}


void loop() {
  // Assicuro che il buzzer sia spento
  noTone(BUZZER);


  // Controllo stato luci o buzzer
  if(luci) {
    //Gestione luci
    noTone(BUZZER);
    // Imposta valori casuali per tutti i LED
    for (int i = 0; i < numLed; i++) {
      int valore;
      for(int i = 0; i < 4; i++) {
        // Genera un valore casuale per l'intensità del LED
        valore = random(0, maxPWM + 1);
        // Evita di ripetere lo stesso valore
        if (iLed[i] != valore) {
           iLed[i] = valore;
        } else {
          valore = random(0, maxPWM + 1);
        }
      }
      // Imposta il valore PWM per il LED
      ledcWrite(led[i], valore);
    }
    delay(150);
   
  } else {
    //Gestione buzzer
    //Esegue la melodia nell'array
    for (int i = 0; i < LUNGHEZZA_MELODIA; i++){
      tone(BUZZER, melodia[i]); delay(pausa[i]); noTone(BUZZER); delay(pausaNote[i]);
      //Si ferma se il pulsante viene premuto
      if (luci){
        break;
      }
    }
    delay(500); // pausa prima del loop
  }
 
}
