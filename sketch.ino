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
  {1, 0, 0, 1, 0, 0, 0},  // H
  {0, 1, 1, 0, 0, 0, 0},  // E
  {1, 1, 1, 0, 0, 0, 1},  // L
  {0, 0, 0, 0, 0, 0, 1},  // O
};
int lungime = sizeof(text) / sizeof(text[0]);


bool start = false;
int scrollLR = 0;
int scrollUD = 0;


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
  DDRC &= ~(1 << 1);   
  PORTC |= (1 << 1);   


}


void loop() {


  if ((PINC & (1 << 0)) == 0) {  
    delay(200);
    Serial.println("Apasat buton L/R");
    start = true;
    if(scrollLR == 0) {
      scrollLR = 1;
      scrollUD = 2;
    } else {
      scrollLR = 0;
      scrollUD = 2;
    }
  }
  if((PINC & (1 << 1)) == 0) {
    delay(200);
    Serial.println("Apasat buton U/D");
    start = true;
    if(scrollUD == 0) {
      scrollUD = 1;
      scrollLR = 2;
    } else {
      scrollUD = 0;
      scrollLR = 2;
    }
  }


  if(start == true) {
    

    if(scrollLR == 0) {
      SchimbPozitieLtoR(text, lungime, 4);
      SchimbPozitieLtoR(text, lungime, 3);
      SchimbPozitieLtoR(text, lungime, 2);
      SchimbPozitieLtoR(text, lungime, 1);
      SchimbPozitieRtoL(text, lungime, 0);
      SchimbPozitieRtoL(text, lungime, 1);
      SchimbPozitieRtoL(text, lungime, 2);
      SchimbPozitieRtoL(text, lungime, 3);
      
    } else if(scrollLR == 1){
      SchimbPozitieRtoL(text, lungime, 4);
      SchimbPozitieRtoL(text, lungime, 3);
      SchimbPozitieRtoL(text, lungime, 2);
      SchimbPozitieRtoL(text, lungime, 1);
      SchimbPozitieRtoL(text, lungime, 0);
      SchimbPozitieLtoR(text, lungime, 1);
      SchimbPozitieLtoR(text, lungime, 2);
      SchimbPozitieLtoR(text, lungime, 3);
    }
    
    if(scrollUD == 0) {
      shiftareBitiJos(text, lungime, 3);
      shiftareBitiJos(text, lungime, 2);
      shiftareBitiJos(text, lungime, 1);
      shiftareBitiJos(text, lungime, 0);
      shiftareBitiSus(text, lungime, 1);
      shiftareBitiSus(text, lungime, 2);
    } 
    if(scrollUD == 1) {
      shiftareBitiSus(text, lungime, 3);
      shiftareBitiSus(text, lungime, 2);
      shiftareBitiSus(text, lungime, 1);
      shiftareBitiSus(text, lungime, 0);
      shiftareBitiJos(text, lungime, 1);
      shiftareBitiJos(text, lungime, 2);
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



void SchimbPozitieRtoL(byte text[][7], int lungime, int pozitie) {
  byte textaux[][7] = {
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1}
  };
  int lungimeaux = sizeof(textaux) / sizeof(textaux[0]);

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
  afiseaza(textaux);
}


void SchimbPozitieLtoR(byte text[][7], int lungime, int pozitie) {
  byte textaux[][7] = {
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1},  
    {1, 1, 1, 1, 1, 1, 1}
  };
  int lungimeaux = sizeof(textaux) / sizeof(textaux[0]);

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
  afiseaza(textaux);
}

void shiftareBitiJos(byte text[][7], int lungime, int repetari) {
  byte textaux[lungime][7];
  
  for (int i = 0; i < lungime; i++) {
    for (int j = 0; j < 7; j++) {
      textaux[i][j] = text[i][j];
    }
  }
  
  for(int j=0; j<repetari; j++) {
    for(int i=0; i<lungime; i++) {
      textaux[i][4] = textaux[i][5];
      textaux[i][5] = 1;
      textaux[i][2] = textaux[i][1];
      textaux[i][1] = 1;
      textaux[i][3] = textaux[i][6];
      textaux[i][6] = textaux[i][0];
      textaux[i][0] = 1;
    }
  }
  afiseaza(textaux);

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
  byte textaux[lungime][7];
  for (int i = 0; i < lungime; i++) {
    for (int j = 0; j < 7; j++) {
      textaux[i][j] = text[i][j];
    }
  }

  for(int j=0; j<repetari; j++) {
    for(int i=0; i<lungime; i++) {
      textaux[i][5] = textaux[i][4];
      textaux[i][4] = 1;
      textaux[i][1] = textaux[i][2];
      textaux[i][2] = 1;
      textaux[i][0] = textaux[i][6];
      textaux[i][6] = textaux[i][3];
      textaux[i][3] = 1;
    }
  }
    afiseaza(textaux);
}
