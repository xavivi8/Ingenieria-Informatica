//
// Created by jmart on 23/09/2024.
//
#include <iostream>
#include "functions.h"

using namespace std;

int ejer1(){
  double num1, num2;

  num1 = getInt("De un primer número");
  num2 = getInt("De un segundo número");

  cout << "Suma " + to_string(num1+num2) << endl;

  return 0;
}