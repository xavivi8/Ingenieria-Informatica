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

// Estructura para almacenar el array y la cantidad de números
struct Resultado {
  int numeros[MAX_NUMEROS];
  int cantidad;
};

Resultado pedirNumeros() {
  Resultado res;
  int num = 0;
  res.cantidad = 0;

  cout << "Inserte numeros hasta " << MAX_NUMEROS << " para almacenarlos (para salir inserte 0): " << endl;
  do {
    cin >> num;
    if (num != 0 && res.cantidad < MAX_NUMEROS) {
      res.numeros[res.cantidad] = num;
      res.cantidad++;
    }
  } while (num != 0 && res.cantidad < MAX_NUMEROS);

  return res;
}

int ejer1(){
  int numeros[MAX_NUMEROS];
  int cantidad = 0;
  Resultado res = pedirNumeros();

  cantidad = res.cantidad;
  for (int i = 0; i < cantidad; ++i) {
    numeros[i] = res.numeros[i];
  }


  cout << "\nIndice\tValor\n";
  for (int i = 0; i < cantidad; ++i) {
    cout << (i+1) << "\t" << numeros[i] << "\n";
  }

  return 0;
}


int ejer2() {
  int numeros[MAX_NUMEROS];
  int cantidad = 0;
  Resultado res = pedirNumeros();

  cantidad = res.cantidad;
  for (int i = 0; i < cantidad; ++i) {
    numeros[i] = res.numeros[i];
  }

  cout << "\nIndice\tValor\n";
  for (int i = cantidad - 1; i >= 0; --i) {
    cout << (i + 1) << "\t" << numeros[i] << "\n";
  }

  return 0;
}

int ejer3() {
  int numeros[MAX_NUMEROS];
  int cantidad = 0;
  int sumatoria = 0;
  Resultado res = pedirNumeros();

  cantidad = res.cantidad;
  for (int i = 0; i < cantidad; ++i) {
    numeros[i] = res.numeros[i];
    sumatoria += res.numeros[i];
  }

  cout << "La suma de todos los numeros es de: " << sumatoria << endl;
}

#endif //EJERCICIOSVECTORES_H
