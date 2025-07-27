#include <Arduino.h>
#include "Teste.h"

extern byte text[][7];
extern int lungime;
extern byte textaux[][7];
extern byte textaux2[][7];
extern int lungimeaux;
bool valid=true;

void printMatrix(byte text[][7], int rows) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < 7; j++) {
      Serial.print(text[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void test_shiftareBitiRtoL() {
  SchimbPozitieRtoL(text, lungime, 0);
  byte expected[][7] = {
    {1, 0, 0, 1, 0, 0, 0},  // H
    {0, 1, 1, 0, 0, 0, 0},  // E
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 1},  // L
    {0, 0, 0, 0, 0, 0, 1},  // O
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1}
  };

  /* matricea corecta pentru a nu esua testul
    byte expected[][7] = {
    {1, 0, 0, 1, 0, 0, 0},  // H
    {0, 1, 1, 0, 0, 0, 0},  // E
    {1, 1, 1, 0, 0, 0, 1},  // L
    {0, 0, 0, 0, 0, 0, 1},  // O
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1}
  };
  */

  for (int i = 0; i < lungimeaux; i++) {
    for (int j = 0; j < 7; j++) {
      if(textaux[i][j] != expected[i][j]) {
        valid = false;
      }
    }
  }
  if(valid) {
    Serial.println("A mers testul test_shiftareBitiRtoL");
  } else {
    Serial.println("N-a mers testul test_shiftareBitiRtoL");
    printMatrix(expected, 8);
    Serial.println();
    printMatrix(textaux, 8);
  }
  valid = true;
}

void test_shiftareBitiLtoR() {
  SchimbPozitieLtoR(text, lungime, 1);
  byte expected[][7] = {
    {1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 0},  // H
    {0, 1, 1, 0, 0, 0, 0},  // E
    {1, 1, 1, 0, 0, 0, 1},  // L
    {0, 0, 0, 0, 0, 0, 1},  // O
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1}
  };


  for (int i = 0; i < lungimeaux; i++) {
    for (int j = 0; j < 7; j++) {
      if(textaux[i][j] != expected[i][j]) {
        valid = false;
      }
    }
  }
  if(valid) {
    Serial.println("A mers testul test_shiftareBitiLtoR");
  } else {
    Serial.println("N-a mers testul test_shiftareBitiLtoR");
    printMatrix(expected, 8);
    Serial.println();
    printMatrix(textaux, 8);
  }
  valid = true;
}

void test_shiftareBitiJos() {
  shiftareBitiJos(text, lungime, 1);  

  byte expected[][7] = {
    {1, 1, 0, 0, 0, 1, 1},  
    {1, 1, 1, 0, 0, 1, 0},
    {1, 1, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 0},
  };

  bool valid = true;
  for (int i = 0; i < lungime; i++) {
    for (int j = 0; j < 7; j++) {
      if (textaux2[i][j] != expected[i][j]) {
        valid = false;
      }
    }
  }

  if (valid) {
    Serial.println("A mers testul test_shiftareBitiJos");
  } else {
    Serial.println("N-a mers testul test_shiftareBitiJos:");
    printMatrix(expected, lungime);
    Serial.println();
    printMatrix(textaux2, lungime);
  }
  valid = true;
}

void test_shiftareBitiSus() {
  shiftareBitiSus(text, lungime, 3);  

  byte expected[][7] = {
    {1, 1, 1, 1, 1, 1, 1}, 
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
  };

  bool valid = true;
  for (int i = 0; i < lungime; i++) {
    for (int j = 0; j < 7; j++) {
      if (textaux2[i][j] != expected[i][j]) {
        valid = false;
      }
    }
  }

  if (valid) {
    Serial.println("A mers testul test_shiftareBitiSus");
  } else {
    Serial.println("N-a mers testul test_shiftareBitiSus:");
    printMatrix(expected, lungime);
    Serial.println();
    printMatrix(textaux2, lungime);
  }
  valid = true;
}
