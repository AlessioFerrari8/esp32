#include <Arduino.h>

/*
nome file: codiceMorse2
data: 02-10-2025
autore: alessio ferrari
testo del problema: Codificare in Morse una lettera dell'alfabeto a scelta e visualizzare la 
                    codifica sul led built-in e sul Monitor Seriale
ipotesi aggiuntive/analisi del problema: Viene codificata la lettera A.
                    La durata del punto è di 200 ms, la linea 600 ms.
                    Lo spazio tra lettere è di 600 ms (equivalente a 3 punti)
                    Utilizzo funzioni per punto, linea e spazio
*/


void setup() {
  Serial.begin(9600);
  Serial.println("Codice Morse");
  pinMode(2, OUTPUT); // led builtin
}

  /***
   * funzione per punto
   */
  void punto() {
    digitalWrite(2, HIGH);
    Serial.print(".");    
    delay(200); // durata
    digitalWrite(2, LOW); // spengo il led
    delay(200); 
  }

  /***
   * funzione per linea (equiv. di 3 punti)
   */
  void linea() {
    digitalWrite(2, HIGH);
    Serial.print("-");    
    delay(600); // durata
    digitalWrite(2, LOW);
    delay(200);
  }

  /***
   * funzione per spazio
   * param: durata in ms
   */
  void spazio(int durata) {
    Serial.print(" ");    
    delay(durata);
  }

void loop() {
  Serial.println("\nLettera A:");
  punto();
  linea();
  spazio(600); // spazio tra lettere
  Serial.println("\nLettera A:");
  punto();
  linea();

}


