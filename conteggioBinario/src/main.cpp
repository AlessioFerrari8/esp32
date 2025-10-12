#define LED1 2
#define LED2 4
#define LED3 5
#define LED4 0

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

}

void loop() {
    
// metodo 1
    //for(int i = 0; i < 16; i++) {
    //	digitalWrite(LED1, bitRead(i, 0));
    //   digitalWrite(LED2, bitRead(i, 1));
    //	digitalWrite(LED3, bitRead(i, 2));
    //	digitalWrite(LED4, bitRead(i, 3));
    //  delay(500);
    //}

// metodo 2
  int numero = 0;
  for (int i = 0; i < 16; i++) {
    numero = i;

    // Calcolo ogni bit con divisione intera e resto
    int b0 = numero % 2;          // bit meno significativo
    int b1 = (numero / 2) % 2;    // secondo bit
    int b2 = (numero / 4) % 2;    // terzo bit
    int b3 = (numero / 8) % 2;    // quarto bit

    digitalWrite(LED1, b0);
    digitalWrite(LED2, b1);
    digitalWrite(LED3, b2);
    digitalWrite(LED4, b3);

    delay(500);
  }
}