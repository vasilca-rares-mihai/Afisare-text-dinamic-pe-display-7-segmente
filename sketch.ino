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

byte charH[] = {1, 0, 0, 1, 0, 0, 0}; //H
byte charE[] = {0, 1, 1, 0, 0, 0, 0}; //E
byte charL[] = {1, 1, 1, 0, 0, 0, 1}; //L
byte charO[] = {0, 0, 0, 0, 0, 0, 1}; //O

void setup() {
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segDP, OUTPUT);

  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  pinMode(dig3, OUTPUT);
  pinMode(dig4, OUTPUT);

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
