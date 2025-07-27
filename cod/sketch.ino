const int segA = A5;
const int segB = A4;
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
  {1, 0, 0, 1, 0, 0, 0},  // H
  {0, 1, 1, 0, 0, 0, 0},  // E
  {1, 1, 1, 0, 0, 0, 1},  // L
  {0, 0, 0, 0, 0, 0, 1},  // O
};
byte textaux2[4][7]; //am facut variabila auxiliara pt animatia sus-jos-sus
byte textaux[][7] = { //am facut variabila auxiliara pt animatia dreapta-stanga-dr
  {1, 1, 1, 1, 1, 1, 1},  
  {1, 1, 1, 1, 1, 1, 1},  
  {1, 1, 1, 1, 1, 1, 1},  
  {1, 1, 1, 1, 1, 1, 1},  
  {1, 1, 1, 1, 1, 1, 1},  
  {1, 1, 1, 1, 1, 1, 1},  
  {1, 1, 1, 1, 1, 1, 1},  
  {1, 1, 1, 1, 1, 1, 1}
};
int lungime = sizeof(text) / sizeof(text[0]);
int lungimeaux = sizeof(textaux) / sizeof(textaux[0]);

volatile bool interruptTriggered = false;
bool start = false;
int scrollLR = 0;
int scrollUD = 0;


void setup() {
  Serial.begin(9600);
  //am setat pinii 2-7 de pe D si pinii de la 0 la 5 de pe B  pe output 
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
  DDRC |= (1<<4);
  DDRC |= (1<<5);
  allSegmentsOff();
  allDigitsOff();

  DDRD &= ~(1 << 2);   
  PORTD |= (1 << 2);  
  DDRD &= ~(1 << 3);   
  PORTD |= (1 << 3);   

  attachInterrupt(digitalPinToInterrupt(2), handleLR, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), handleUD, FALLING);
}

volatile unsigned long lastInterruptTimeLR = 0;
volatile unsigned long lastInterruptTimeUD = 0;
const unsigned long debounceDelay = 200;

void handleLR() {
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTimeLR > debounceDelay) {
    scrollLR = !scrollLR;
    scrollUD = 2;
    interruptTriggered = true;
    lastInterruptTimeLR = currentTime;
    Serial.println("apel al handleLR");
  }
}

void handleUD() {
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTimeUD > debounceDelay) {
    scrollUD = !scrollUD;
    scrollLR = 2;
    interruptTriggered = true;
    lastInterruptTimeUD = currentTime;
    Serial.println("apel al handleUD");
  }
}

void animatie() {
  int rotatie = 4;
  int rotatie2 = 3;
  if(scrollLR == 0) {
    while(rotatie > 0) {
      if (interruptTriggered) return;
        SchimbPozitieLtoR(text, lungime, rotatie);
        afiseaza(textaux);
        rotatie--;
      }
    while(rotatie <= 3){
        if (interruptTriggered) return;
        SchimbPozitieRtoL(text, lungime, rotatie);
        afiseaza(textaux);
        rotatie++;
      } 
  } else if(scrollLR == 1){
    while(rotatie > 0) {
      if (interruptTriggered) return;
      SchimbPozitieRtoL(text, lungime, rotatie);
      afiseaza(textaux);
      rotatie--;
    }
    while(rotatie <= 3){
      if (interruptTriggered) return;
      SchimbPozitieLtoR(text, lungime, rotatie);
      afiseaza(textaux);
      rotatie++;
    }
  } else if(scrollUD == 0) {
    while(rotatie2 > 0) {
      if (interruptTriggered) return;
      shiftareBitiJos(text, lungime, rotatie2);
      afiseaza(textaux2);
      rotatie2--;
    }
    while(rotatie2 <= 2){
      if (interruptTriggered) return;
        shiftareBitiSus(text, lungime, rotatie2);
        afiseaza(textaux2);
        rotatie2++;
      }
  } else if(scrollUD == 1) {
    while(rotatie2 > 0) {
      if (interruptTriggered) return;
      shiftareBitiSus(text, lungime, rotatie2);
      afiseaza(textaux2);
      rotatie2--;
    }
    while(rotatie2 <= 2){
      if (interruptTriggered) return;
      shiftareBitiJos(text, lungime, rotatie2);
      afiseaza(textaux2);
      rotatie2++;
    }
  }
}

void loop() {
  if (interruptTriggered) {
    interruptTriggered = false;
    start = true;
    allSegmentsOff();
    allDigitsOff();
    Serial.println("Intrerupere detectata");
  }
  if ((PIND & (1 << 2)) == 0) {  
    delay(200);
    Serial.println("Apasat buton L/R");
    start = true;
  }
  if((PIND & (1 << 3)) == 0) {
    delay(200);
    Serial.println("Apasat buton U/D");
    start = true;
  }
  if (start) {
    animatie();
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


void printTextaux(byte textaux[][7], int lungime) {
  Serial.println("Continutul textaux:");
  for (int i = 0; i < lungime; i++) {
    for (int j = 0; j < 7; j++) {
      Serial.print(textaux[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println();
} 


void SchimbPozitieRtoL(byte text[][7], int lungime, int pozitie) {
  for(int i=0; i<lungimeaux; i++) {
    for(int j=0; j<7; j++) {
      textaux[i][j] = 1;
    }
  }
  for(int i=0; i<lungime; i++) {
    for(int j=0; j<7; j++) {
      textaux[i][j] = text[i][j];
    }
  }

  byte temp[7];
  for(int z=0; z<pozitie; z++) {
    for (int i = 0; i < 7; i++) {
      temp[i] = textaux[0][i];
    }

    for (int i = 0; i < lungimeaux - 1; i++) {
      for (int j = 0; j < 7; j++) {
        textaux[i][j] = textaux[i + 1][j];
      }
    }

    for (int j = 0; j < 7; j++) {
      textaux[lungimeaux - 1][j] = temp[j];
    }
  }
  
}


void SchimbPozitieLtoR(byte text[][7], int lungime, int pozitie) {
  for(int i=0; i<lungimeaux; i++) {
    for(int j=0; j<7; j++) {
      textaux[i][j] = 1;
    }
  }
  
  for(int i=0; i<lungime; i++) {
    for(int j=0; j<7; j++) {
      textaux[i][j] = text[i][j];
    }
  }

  byte temp[7];
  for(int z=0; z<pozitie; z++) {
    for (int i = 0; i < 7; i++) {
      temp[i] = textaux[lungimeaux - 1][i];
    }

    for (int i = lungimeaux - 1; i > 0; i--) {
      for (int j = 0; j < 7; j++) {
        textaux[i][j] = textaux[i - 1][j];
      }
    }

    for (int j = 0; j < 7; j++) {
      textaux[0][j] = temp[j];
    }
  }
}

void shiftareBitiJos(byte text[][7], int lungime, int repetari) {
  for (int i = 0; i < lungime; i++) {
    for (int j = 0; j < 7; j++) {
      textaux2[i][j] = text[i][j];
    }
  }
  
  for(int j=0; j<repetari; j++) {
    for(int i=0; i<lungime; i++) {
      textaux2[i][4] = textaux2[i][5];
      textaux2[i][5] = 1;
      textaux2[i][2] = textaux2[i][1];
      textaux2[i][1] = 1;
      textaux2[i][3] = textaux2[i][6];
      textaux2[i][6] = textaux2[i][0];
      textaux2[i][0] = 1;
    }
  }

}

void afiseaza(byte text[][7]) {
  for (int i = 0; i < 50; i++) {
    displayDigit(text[0], dig1);
    delay(5);
    displayDigit(text[1], dig2);
    delay(5);
    displayDigit(text[2], dig3);
    delay(5);
    displayDigit(text[3], dig4);
    delay(5);
  }
}

void shiftareBitiSus(byte text[][7], int lungime, int repetari) {
  for (int i = 0; i < lungime; i++) {
    for (int j = 0; j < 7; j++) {
      textaux2[i][j] = text[i][j];
    }
  }

  for(int j=0; j<repetari; j++) {
    for(int i=0; i<lungime; i++) {
      textaux2[i][5] = textaux2[i][4];
      textaux2[i][4] = 1;
      textaux2[i][1] = textaux2[i][2];
      textaux2[i][2] = 1;
      textaux2[i][0] = textaux2[i][6];
      textaux2[i][6] = textaux2[i][3];
      textaux2[i][3] = 1;
    }
  }
}

