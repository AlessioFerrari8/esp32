/*
  nome file: 260129_Ferrari_sensore_di_luminosità_LDR
  data: 2026-01-29
  autore: Alessio Ferrari
  testo del problema: Realizzare un circuito con un led che modifica la propria intensità in base
  al valore della tensione misurata dall'LDR e quindi in base alla luce presente.
  ipotesi aggiuntive/analisi del problema: Abbiamo utilizzato anche uno schermo LCD per mostrare il valore della tensione
  in tempo reale, e non essere costretti ad utilizzare il monitor seriale.
*/

#include <LiquidCrystal.h>


// Dichiarazione costanti
const int pin_ldr = 34;
const int freq = 1000;
const int freq_lcd = 5000;
const int resolution = 8;
const int pin_led = 5;
const int pin_lcd_led = 18;
LiquidCrystal lcd(14, 27, 26, 25, 33, 32);


void setup() {
 // Impostazione canali PWM per i pin del LED e della retroilluminazione dello schermo
 ledcAttach(pin_led, freq, resolution);
 ledcAttach(pin_lcd_led, freq_lcd, resolution);
 ledcWrite(pin_led, 0);   // LED spento all’inizio
 ledcWrite(pin_lcd_led, 0);   // LED spento all’inizio
 // Configurazione di monitor seriale e schermo LCD
 Serial.begin(115200);
 lcd.begin(16, 2);        // LCD 16x2
 lcd.print("Ciao ESP32!"); // Mostra subito qualcosa sulla prima riga
}


void loop() {
 // Lettura del valore analogico
 int val = analogRead(pin_ldr); // 0–4095, 12 bit
 //Serial.println(tensione);
 int pwm_val = map(val, 0, 4095, 255, 0); // adattiamo al range 8-bit, valori inversi
 int pwm_val_lcd = map(val, 0, 4095, 40, 255); // adattiamo al range 8-bit
 ledcWrite(pin_led, pwm_val);   // Impostazione del nuovo valore di luminosità tramite canale PWM
 ledcWrite(pin_lcd_led, pwm_val_lcd);   // Impostazione del nuovo valore di luminosità tramite canale PWM
 // Visualizzo il valore sul monitor seriale
 Serial.println(val);
 // Imposto il cursore dello schermo nella seconda riga
 lcd.setCursor(0, 1);
 lcd.print("      "); // cancella riga
 lcd.setCursor(0, 1);
 lcd.print(val);      // scrivi nuovo valore
 delay(200);
}
