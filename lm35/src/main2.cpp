/*
  nome file: 260212_Ferrari_sensore_di_temperatura_lm35_e_display_LCD.ino
  data: 2026-02-12
  autore: Alessio Ferrari 
  descrizione: 
    Rilevazione temperatura ambiente con LM35 e visualizzazione su LCD
    Prima riga: "A222bL.R (Aula 222b lab. Reti) - temperatura °C"
    Seconda riga: tempo passato in formato hh:mm:ss
*/

#include <Arduino.h>
#include <LiquidCrystal.h>

// costanti
LiquidCrystal lcd(14, 27, 26, 25, 33, 32);
const int pin_lm = 34;        
unsigned long previousMillis = 0;
const long interval = 1000;    

void setup() {
  Serial.begin(115200);
  
  // attenuazione lm 1,1V
  analogSetAttenuation(ADC_0db);
  
  lcd.begin(16, 2); // LCD 16x2
  lcd.print("Starting...");
  delay(2000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis(); // tempo attuale
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // mi salvo il tempo
    
    // lettura temperatura
    int val = analogRead(pin_lm);
    float millivolt = val * (1100.0 / 4095.0);   // conversione in mV
    float temperatura = millivolt / 10.0;        // 10 mV circa per grado
    
    // calcolo tempo
    unsigned long secondiTotali = millis() / 1000;
    int ore = secondiTotali / 3600;
    int minuti = (secondiTotali % 3600) / 60;
    int secondi = secondiTotali % 60;

    // riga 1
    lcd.setCursor(0, 0);
    // ho dovuto restringere la stringa per farcela stare
    lcd.print("A222bL.R ");    
   
    // parte intera + decimale
    int intPart = (int)temperatura; // estraggo parte intera
    // faccio questo passaggio per
    // 24,42 --> casto a intero diventa 24
    // temp - intPart = 0,42 --> lo sposto a unità 4,2
    // 4,7 --> si casta a intero e diventa 5
    int decPart = (int)((temperatura - intPart) * 10 + 0.5); // +0,5 per arrotondarlo e non troncarlo
    
    if (intPart < 10) lcd.print('0'); // zero iniziale

    // stampo la temperatura
    lcd.print(intPart);
    lcd.print('.');
    lcd.print(decPart);
    lcd.print((char)223); // simbolo °
    lcd.print('C');
        
    // RIGA 2
    lcd.setCursor(0, 1);
    
    // due cifre
    if (ore < 10) lcd.print('0'); // zeri
    // format ore:minuti:secondi
    lcd.print(ore);
    lcd.print(':');
    
    if (minuti < 10) lcd.print('0');
    lcd.print(minuti);
    lcd.print(':');
    
    if (secondi < 10) lcd.print('0');
    lcd.print(secondi);
    
    // pulisce
    lcd.print("        "); 
  }
}