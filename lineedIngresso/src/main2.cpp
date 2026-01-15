#define pin_pulsante1 22
#define pin_pulsante2 35
#define ledinterno 2
#define led1 12
#define led2 4
#define led3 34

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
  
  digitalWrite(ledinterno, HIGH); // LED interno acceso all'avvio
}

void loop() {
  lettura1 = digitalRead(pin_pulsante1);
  lettura2 = digitalRead(pin_pulsante2);

  // ---- Pulsante 1: conteggio crescente ----
  if (lettura1 == LOW) {
    Serial.println("Pulsante 1 premuto: conteggio da 0 a 15");
    digitalWrite(ledinterno, LOW);

    for (int i = 0; i < 16; i++) {
      mostraNumero(i);
      delay(500);
    }

    spegniLED();
    digitalWrite(ledinterno, HIGH);
  }

  // ---- Pulsante 2: conteggio decrescente ----
  if (lettura2 == LOW) {
    Serial.println("Pulsante 2 premuto: conteggio da 15 a 0");
    digitalWrite(ledinterno, LOW);

    for (int i = 15; i >= 0; i--) {
      mostraNumero(i);
      delay(500);
    }

    spegniLED();
    digitalWrite(ledinterno, HIGH);
  }

  delay(200);
}

void mostraNumero(int n) {
  digitalWrite(led1, n % 2);
  digitalWrite(led2, (n / 2) % 2);
  digitalWrite(led3, (n / 4) % 2);
  digitalWrite(led4, (n / 8) % 2);
}

void spegniLED() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}
