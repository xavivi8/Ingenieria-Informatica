//
// Created by jmart on 17/12/2024.
//

#ifndef MIS_DATOS_H
#define MIS_DATOS_H
const int MAX_FILAS=5;
const int MAX_COLUMNAS=5;
const int MAX_DATOS=7;
bool player1 = true;
bool player2 = false;

struct Coordenadas {
  char fila;
  int columna;
};

Coordenadas cord1[MAX_DATOS]={};
Coordenadas cord2[MAX_DATOS]={};

char flota1[MAX_FILAS][MAX_COLUMNAS]={};
char flota2[MAX_FILAS][MAX_COLUMNAS]={};

#endif //MIS_DATOS_H
