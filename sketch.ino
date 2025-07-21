const int segA = 2;
const int segB = 3;
const int segC = 4;
const int segD = 5;
const int segE = 6;
const int segF = 7;
const int segG = 8;
const int segDP = 9;

const int dig1 = 10;
const int dig2 = 11;
const int dig3 = 12;
const int dig4 = 13;

byte text[][7] = {
  {1, 1, 1, 1, 1, 1, 1}, 
  {1, 1, 1, 1, 1, 1, 1}, 
  {1, 1, 1, 1, 1, 1, 1}, 
  {1, 1, 1, 1, 1, 1, 1}, 
  {1, 0, 0, 1, 0, 0, 0},  // H
  {0, 1, 1, 0, 0, 0, 0},  // E
  {1, 1, 1, 0, 0, 0, 1},  // L
  {0, 0, 0, 0, 0, 0, 1}   // O
};

int lungime = sizeof(text) / sizeof(text[0]);
bool start = false;
bool scrollLR = false;


void setup() {
  
  Serial.begin(9600);
  //am setat pinii 2-7 de pe D si pinii de la 0 la 5 de pe B  pe output 
  DDRD |= (1<<2);
  DDRD |= (1<<3);
  DDRD |= (1<<4);
  DDRD |= (1<<5);
  DDRD |= (1<<6);
  DDRD |= (1<<7);
  DDRB |= (1<<0);
  DDRB |= (1<<1);
  DDRB |= (1<<2);
  DDRB |= (1<<3);
  DDRB |= (1<<4);
  DDRB |= (1<<5);

  allSegmentsOff();
  allDigitsOff();

  //buton
  DDRC &= ~(1 << 0);   
  PORTC |= (1 << 0);   


}

void loop() {
  for (int i = 0; i < 100; i++) {
    displayDigit(text[0], dig1);
    delay(5);
    displayDigit(text[1], dig2);
    delay(5);
    displayDigit(text[2], dig3);
    delay(5);
    displayDigit(text[3], dig4);
    delay(5);
  }

  if ((PINC & (1 << 0)) == 0) {  
    Serial.println("Buton APASAT");
    start = true;
    if(scrollLR == false) {
      scrollLR = true;
    } else {
      scrollLR = false;
    }
  } else {
    Serial.println("Buton NEAPASAT");
  }

  if(start == true) {
    if(scrollLR == false) {
      schimbpozitieRtoL(text, lungime);
    } else {
      schimbpozitieLtoR(text, lungime);
    }
  }

}



void allSegmentsOff() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segDP, HIGH);
}

void allDigitsOff() {
  digitalWrite(dig1, LOW);
  digitalWrite(dig2, LOW);
  digitalWrite(dig3, LOW);
  digitalWrite(dig4, LOW);
}

void displayDigit(byte characterPattern[], int digitPin) {
  allDigitsOff();
  allSegmentsOff();

  digitalWrite(segA, characterPattern[0]);
  digitalWrite(segB, characterPattern[1]);
  digitalWrite(segC, characterPattern[2]);
  digitalWrite(segD, characterPattern[3]);
  digitalWrite(segE, characterPattern[4]);
  digitalWrite(segF, characterPattern[5]);
  digitalWrite(segG, characterPattern[6]);

  digitalWrite(digitPin, HIGH);
}

void schimbpozitieRtoL(byte text[][7], int lungime) {
  byte temp[7];

  for (int i = 0; i < 7; i++) {
    temp[i] = text[0][i];
  }

  for (int i = 0; i < lungime - 1; i++) {
    for (int j = 0; j < 7; j++) {
      text[i][j] = text[i + 1][j];
    }
  }

  for (int j = 0; j < 7; j++) {
    text[lungime - 1][j] = temp[j];
  }
}

void schimbpozitieLtoR(byte text[][7], int lungime) {
  byte temp[7];

  for (int i = 0; i < 7; i++) {
    temp[i] = text[lungime - 1][i];
  }

  for (int i = lungime - 1; i > 0; i--) {
    for (int j = 0; j < 7; j++) {
      text[i][j] = text[i - 1][j];
    }
  }

  for (int j = 0; j < 7; j++) {
    text[0][j] = temp[j];
  }
}

