#include <Arduino.h>

/*
nome file: codiceMorse1
data: 02-10-2025
autore: alessio ferrari
testo del problema: Codificare in Morse una lettera dell'alfabeto a scelta e visualizzare la 
                    codifica sul led built-in e sul Monitor Seriale
ipotesi aggiuntive/analisi del problema: Vengono codificate le lettere A, R, R, A, Y.
                    La durata del punto è di 200 ms, la linea 600 ms.
                    Lo spazio tra lettere è di 600 ms (equivalente a 3 punti)
                    Lo spazio tra parole è di 1400 ms (equivalente a 7 punti)
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

  // array di funzioni 
  // typedef = crea un nuovo tipo di dato
  // * --> puntatore a funzione (non posso puntare direttamente alla funzione, ma punto ad un indirizzo di memoria)
  typedef void (*MorseFunc)();  
  
  // definizione delle lettere
  MorseFunc letterA[] = { punto, linea };
  MorseFunc letterR[] = { punto, linea, punto };
  MorseFunc letterY[] = { linea, punto, linea, linea };

void loop() {
  Serial.println("\nLettera A:");
  for (int i = 0; i < 2; i++) { // scorro l'array
    letterA[i](); // chiamo la funzione
  }
  spazio(600); // spazio tra una parola e un altra (equivalente a 3 punti)
  Serial.println("\nLettera R:");
  for (int i = 0; i < 3; i++) { // scorro l'array
    letterR[i](); // chiamo la funzione
  }
  spazio(600);
  Serial.println("\nLettera R:");
  for (int i = 0; i < 3; i++) { // scorro l'array
    letterR[i](); // chiamo la funzione
  }
  spazio(600);
  Serial.println("\nLettera A:");
  for (int i = 0; i < 2; i++) { // scorro l'array
    letterA[i](); // chiamo la funzione
  }
  spazio(600);
  Serial.println("\nLettera Y:");
  for (int i = 0; i < 4; i++) { // scorro l'array
    letterY[i](); // chiamo la funzione
  }
  spazio(600); 
 
}


