//
// Created by Claudia on 05/12/2024.
//
#include <iostream>
#include "hundir_la_flota.h"
#include "functions.h"
#include "control_jugadas.h"
#include "mis_datos.h"

using namespace std;


int main(){


  char matriz[MAX_FILAS][MAX_COLUMNAS]={};
  int m=5;

  insertarDatos(cord1);
  insertarDatos(cord2);

  int tam=10;

  colocar_barcos(m,cord1,tam,matriz);

  for(int i=0; i<m; ++i) {
    for(int j=0; j<m; ++j) {
      cout<<matriz[i][j]<<'\t';
    }
    cout<<endl;
  }
  cout<<endl;
  cout<<"JUGADA1: "<<jugada(matriz,m,{'A',4})<<endl;

  cout<<"JUGADA2: "<<jugada(matriz,m,{'C',1})<<endl;

  cout<<"JUGADA3: "<<jugada(matriz,m,{'B',1})<<endl;

  cout<<"JUGADA4: "<<jugada(matriz,m,{'A',5})<<endl;

  cout<<"JUGADA5: "<<jugada(matriz,m,{'A',3})<<endl;
  for(int i=0; i<m; ++i) {
    for(int j=0; j<m; ++j) {
      cout<<matriz[i][j]<<'\t';
    }
    cout<<endl;
  }
  return 0;
}