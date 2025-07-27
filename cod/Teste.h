#ifndef TESTE_H
#define TESTE_H

#include <Arduino.h>

void test_shiftareBitiRtoL();
void test_shiftareBitiLtoR();
void test_shiftareBitiJos();
void test_shiftareBitiSus();
void printMatrix(byte text[][7], int rows);

void shiftareBitiJos(byte text[][7], int lungime, int repetari);
void shiftareBitiSus(byte text[][7], int lungime, int repetari);
void SchimbPozitieRtoL(byte text[][7], int lungime, int pozitie);
void SchimbPozitieLtoR(byte text[][7], int lungime, int pozitie);

#endif
