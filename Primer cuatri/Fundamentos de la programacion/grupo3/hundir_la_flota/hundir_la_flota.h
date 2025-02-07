//
// Created by jmart on 16/12/2024.
//
#include <iostream>
#include "mis_datos.h"
using namespace std;

#ifndef HUNDIR_LA_FLOTA_H
#define HUNDIR_LA_FLOTA_H


int posicion_fila(char letra){
  return letra-'A';
}

void colocar_barcos(int m, Coordenadas vector[], int numBarcos, char matriz[MAX_FILAS][MAX_COLUMNAS]) {
  int numFilas=m;
  int numColumnas=m;
   for(int i=0; i<numFilas; ++i) {
     for (int j=0; j<numColumnas; ++j) {
       matriz[i][j]=' ';
     }
   }

  for(int k=0; k<numBarcos; ++k) {
    int filaBarco=posicion_fila(vector[k].fila);
    int columnaBarco=vector[k].columna;
    matriz[filaBarco][columnaBarco-1]='X';
  }
}

string jugada(char matriz[MAX_FILAS][MAX_COLUMNAS], int dimension, Coordenadas jugadaCoordenadas) {
  int fila_barco=posicion_fila(jugadaCoordenadas.fila);
  int columna_barco=jugadaCoordenadas.columna-1;
  string resultado;

  if (fila_barco < 0 || fila_barco >= dimension || columna_barco < 0 || columna_barco >= dimension) {
    return "jugada fuera de rango";
  }

  if(matriz[fila_barco][columna_barco]==' ') {
    matriz[fila_barco][columna_barco]='A';
    resultado="agua";
  }

  if(matriz[fila_barco][columna_barco]=='X') {
    if(matriz[fila_barco][columna_barco+1]=='X' || matriz[fila_barco][columna_barco-1]=='X' || matriz[fila_barco+1][columna_barco]=='X'||matriz[fila_barco-1][columna_barco]=='X') {
      matriz[fila_barco][columna_barco]='T';
      resultado="tocado";
    }

    if(matriz[fila_barco][columna_barco+1]=='T'){
      int columna_buscar=columna_barco+1;
      while(matriz[fila_barco][columna_buscar]!='A'&&matriz[fila_barco][columna_buscar]!=' ' && columna_buscar<dimension) {
        if(matriz[fila_barco][columna_buscar]=='X') resultado="tocado";
        else {
          resultado="hundido";
          matriz[fila_barco][columna_barco]='T';
        }
        ++columna_buscar;
      }
    }

    if(matriz[fila_barco][columna_barco-1]=='T'){
      int columna_buscar=columna_barco-1;
      while(matriz[fila_barco][columna_buscar]!='A'&& matriz[fila_barco][columna_buscar]!=' ' && 0<=columna_buscar) {
        if(matriz[fila_barco][columna_buscar]=='X') resultado="tocado";
        else {
          resultado="hundido";
          matriz[fila_barco][columna_barco]='T';
        }
        --columna_buscar;
      }
    }

    if(matriz[fila_barco-1][columna_barco]=='T'){
      int fila_buscar=fila_barco-1;
      while(matriz[fila_buscar][columna_barco]!='A'&&matriz[fila_buscar][columna_barco]!=' '&&fila_buscar>=0) {
        if(matriz[fila_buscar][columna_barco]=='X') resultado="tocado";
        else {
          resultado="hundido";
          matriz[fila_barco][columna_barco]='T';
        }
        --fila_buscar;
      }
    }

    if(matriz[fila_barco+1][columna_barco]=='T'){
      int fila_buscar=fila_barco+1;
      while(matriz[fila_buscar][columna_barco]!='A'&&matriz[fila_buscar][columna_barco]!=' ' && fila_buscar<dimension) {
        if(matriz[fila_buscar][columna_barco]=='X') resultado="tocado";
        else {
          resultado="hundido";
          matriz[fila_barco][columna_barco]='T';
        }
        ++fila_buscar;
      }
    }
  }

  return resultado;
}

#endif //HUNDIR_LA_FLOTA_H
