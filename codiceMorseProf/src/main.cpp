#include <Arduino.h>

#define LED 2
#define PUNTO 150
#define LINEA 3 * PUNTO
#define INT_SIMBOLO PUNTO
#define INT_LETTERA 3 * PUNTO
#define INT_PAROLA 7 * PUNTO

String alfabeto[] = {"01", "1110", "0101", "100", "0", "0010", "110", "0000", "00",
                     "0111", "101", "0100", "11", "10", "111", "0110", "1101", "101", "000",
                     "1", "001", "0001", "011", "1001", "1011", "1100"},
       parola = "sos";

int indice, i, k;

void simbolo(int s)
{
  digitalWrite(LED, HIGH);
  delay(s);
  digitalWrite(LED, LOW);
  delay(s);
}

void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  delay(10);
  Serial.println("Codifica Morse!");
}

void loop()
{
  i = 0;
  while (i < parola.length())
  {
    indice = parola.charAt(i) - 'a';
    Serial.print("Carattere ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(parola.charAt(i));
    Serial.print("\t");
    Serial.print("Posizione in alfabeto: ");
    Serial.print(indice);
    Serial.print("\t");
    Serial.print("Codifica Morse: ");
    Serial.print(alfabeto[indice]);
    Serial.print("\t");
    k = 0;
    while (k < alfabeto[indice].length())
    {
      if (alfabeto[indice].charAt(k) == '0')
      {
        simbolo(PUNTO);
        Serial.print(".");
      }
      else
      {
        simbolo(LINEA);
        Serial.print("-");
      }
      k++;
    }
    Serial.println();
    Serial.println("Fine LETTERA...");
    delay(INT_LETTERA);

    i++;
  }
  Serial.println("Fine PAROLA...");
  delay(INT_PAROLA);
}
