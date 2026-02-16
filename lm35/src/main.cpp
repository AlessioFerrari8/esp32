/*
 nome file: 260206_Ferrari_sensore_di_temperatura_lm35
 data: 2026-02-06
 autore: Alessio Ferrari
 testo del problema: Realizzare un circuito che misura in tempo reale la temperatura in un determinato ambiente
 e mostra il suo valore a intervalli regolari sul display LCD. Al raggiungimento della soglia
 dei 25° si accende un led per monitorare il superamento della soglia e la "virtuale" accensione
 di un condizionatore.
*/

#include <Arduino.h>
#include <LiquidCrystal.h>



// Dichiarazione costanti
const int pin_lm = 34;
const int freq = 1000;
const int freq_lcd = 5000;
const int resolution = 8;
const int pin_led = 5;
LiquidCrystal lcd(14, 27, 26, 25, 33, 32);

unsigned long previousMillis = 0;  // ultimo aggiornamenot
const long interval = 1000;   

void setup() {
  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, LOW);
  analogSetAttenuation(ADC_0db); // attenuazione lm
  // Configurazione di monitor seriale e schermo LCD
  Serial.begin(115200);
  lcd.begin(16, 2);        // LCD 16x2
  lcd.print("Ciao ESP32!"); // Mostra subito qualcosa sulla prima riga
}

void loop() {
  // tempo attuale
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int val = analogRead(pin_lm); 
    
    // ADC_0db --> 1.1 V circa
    float millivolt = val * (1100.0 / 4095.0); // val : millivolt = 1100.0 : 4095.0
    float temperatura = millivolt / 10.0; // 10mV circa per grado

    if (temperatura >= 25.0) {
      digitalWrite(pin_led, HIGH); // Accendo LED
      
      // Aggiorno LCD
      lcd.setCursor(0, 0);
      lcd.print("Condiz. ON        "); // spazio serve per pulire la riga
    } else {
      digitalWrite(pin_led, LOW); // Spengo LED
      
      // Aggiorno LCD
      lcd.setCursor(0, 0);
      lcd.print("Temp. ambiente: ");
    }

    lcd.setCursor(0, 1);
    lcd.print(temperatura, 1); 
    lcd.print((char)223); // simbolo gradi
    lcd.print("C    ");

  }
}
