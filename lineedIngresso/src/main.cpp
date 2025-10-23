// se collego il pin22 a massa, accende il LED esterno e 
// spegne quello interno; in caso contrario, accende il LED interno e 
// spegne quello esterno.
#define pin_pulsante1 22
#define pin_pulsante2 35
#define ledinterno 2
#define led1 12
#define led2 4
#define led3 5
#define led4 19

  int lettura1 = 0;
  int lettura2 = 0;
void setup() {
  Serial.begin(9600);
  pinMode(pin_pulsante1, INPUT_PULLUP);
  pinMode(pin_pulsante2, INPUT_PULLUP);
  pinMode(ledinterno, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

}

void loop() {  
  Serial.println("PREMI il pulsante per accendere il LED esterno");
  lettura1 = digitalRead(pin_pulsante1);
  lettura2 = digitalRead(pin_pulsante2);
  if (lettura1==LOW)
     { Serial.println("tasto premuto, conteggio da 0 a 15");
        digitalWrite(ledinterno, LOW);

        for (int i = 0; i < 16; i++) {      
          // Calcolo ogni bit con divisione intera e resto
          int b0 = i % 2;          // bit meno significativo
          int b1 = (i / 2) % 2;    // secondo bit
          int b2 = (i / 4) % 2;    // terzo bit
          int b3 = (i / 8) % 2;    // quarto bit
      
          digitalWrite(led1, b0);
          digitalWrite(led2, b1);
          digitalWrite(led3, b2);
          digitalWrite(led4, b3);
      
          delay(500);
        }
      }
    else if (lettura1 == HIGH)
        { 
          Serial.println("tasto rilasciato, LED esterno spento");
          digitalWrite(ledinterno, HIGH);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
        }
   else if (lettura2==LOW)
     { Serial.println("tasto premuto, conteggio da 15 a 0");
        digitalWrite(ledinterno, LOW);

        for (int i = 15; i >= 0; i--) {
        
          // Calcolo ogni bit con divisione intera e resto
          int b0 = i % 2;          // bit meno significativo
          int b1 = (i / 2) % 2;    // secondo bit
          int b2 = (i / 4) % 2;    // terzo bit
          int b3 = (i / 8) % 2;    // quarto bit
        
          digitalWrite(led1, b0);
          digitalWrite(led2, b1);
          digitalWrite(led3, b2);
          digitalWrite(led4, b3);
        
          delay(500);
        }

      }
    else if (lettura2 == HIGH)
        { 
          Serial.println("tasto rilasciato, LED esterno spento");
          digitalWrite(ledinterno, HIGH);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
        };
         
  delay(300);
}