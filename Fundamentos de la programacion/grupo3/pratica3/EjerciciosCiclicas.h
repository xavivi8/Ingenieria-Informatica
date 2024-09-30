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

#endif //EJERCICIOSCICLICAS_H
