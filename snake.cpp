#include <LiquidCrystal.h>


// Inizializza la libreria con i pin: RS, E, D4, D5, D6, D7
// Usiamo i pin mappati precedentemente
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);
const int VRx = 34;
const int VRy = 35;
const int SW = 4;

const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;


/*
1 --> up
2 --> down
3 --> left
4 --> right
*/
int direzione = 0;

byte snake[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte mela[8] = {
  B00000,
  B00000,
  B01110,
  B01110,
  B01110,
  B01110,
  B00000,
  B00000
};

void setup() {
  lcd.createChar(0, snake);
  lcd.createChar(1, mela);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
  pinMode(SW, INPUT_PULLUP);
  randomSeed(analogRead(0));
}
 
void loop() {
  // random riga
  int riga = random(0, 1);
  // random colonna
  int col = random(0, 15);

  // if per vedere che non sia sul snake

  lcd.setCursor(0, 1);
  lcd.write(byte(0));
  int x = analogRead(VRx);
  int y = analogRead(VRy);
  Serial.println(x);
  Serial.println(y);
  lcd.setCursor(0,0);
  lcd.write(byte(1));
}

