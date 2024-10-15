//
// Created by jmart on 12/10/2024.
//
#include <iostream>
#include <vector>

#include "functions.h"

using namespace std;

#ifndef EJERCICIOSVECTORES_H
#define EJERCICIOSVECTORES_H

const int MAX_NUMEROS = 100;

int ejer1(){
  int numeros[MAX_NUMEROS];
  int cantidad = 0;
  int num = 0;

  cout << "Inserte numeros hasta "<< MAX_NUMEROS <<" para almacenarlos (para salir inserte -1): " << endl;
  do{
    cin >> num;
    if(num != -1) {
      numeros[cantidad] = num;
      cantidad++;
    }

  }while(num != -1 && cantidad < MAX_NUMEROS);

  cout << "\nIndice\tValor\n";
  for (int i = 0; i < cantidad; ++i) {
    cout << (i+1) << "\t" << numeros[i] << "\n";
  }

  return 0;
}

#endif //EJERCICIOSVECTORES_H
