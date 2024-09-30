//
// Created by jmart on 30/09/2024.
//
#include <iostream>
#include "functions.h"

using namespace std;

#ifndef EJERCICIOSCICLICAS_H
#define EJERCICIOSCICLICAS_H

int ejer2(){
  int num;

  num = getInt("Inserte un numero: ");

  for(int i=0; i<=10; i++){
    cout << num << " X " << i << " = " << num*i << endl;
  }

  return 0;
}

int ejer3() {
  int num_mayor_0=0;
  double num_actual;

  do {
    num_actual = getDouble("Inserte un numero: ");

    if (num_actual > 0){
      num_mayor_0++;
    }

  }while (num_actual != 0);

  cout << "La cantidad de numeros mayores de " << num_mayor_0 << endl;

  return 0;
}

#endif //EJERCICIOSCICLICAS_H
