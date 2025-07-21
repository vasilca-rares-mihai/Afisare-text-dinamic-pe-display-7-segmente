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

byte charH[] = {1, 0, 0, 1, 0, 0, 0}; 
byte charE[] = {0, 1, 1, 0, 0, 0, 0}; 
byte charL[] = {1, 1, 1, 0, 0, 0, 1}; 
byte charO[] = {0, 0, 0, 0, 0, 0, 1}; 



void setup() {
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
}

void loop() {
  for (int i = 0; i < 100; i++) {
    displayDigit(charH, dig1);
    delay(5);
    displayDigit(charE, dig2);
    delay(5);
    displayDigit(charL, dig3);
    delay(5);
    displayDigit(charO, dig4);
    delay(5);
  }

  schimbpozitie(charH, charE, charL, charO);
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

void schimbpozitie(byte ch1[], byte ch2[], byte ch3[], byte ch4[]) {
  byte temp[7];
  
  // copiez ch1 in temp
  for (int i = 0; i < 7; i++) {
    temp[i] = ch1[i];
  }

  // ch2 in ch1
  for (int i = 0; i < 7; i++) {
    ch1[i] = ch2[i];
  }

  // ch3 in ch2
  for (int i = 0; i < 7; i++) {
    ch2[i] = ch3[i];
  }

  // ch4 in ch3
  for (int i = 0; i < 7; i++) {
    ch3[i] = ch4[i];
  }

  // temp in ch4
  for (int i = 0; i < 7; i++) {
    ch4[i] = temp[i];
  }
}

