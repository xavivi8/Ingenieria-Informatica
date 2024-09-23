//
// Created by jmart on 23/09/2024.
//
#include <iostream>
#include "functions.h"

using namespace std;

int ejer1(){
  double num1, num2;

  num1 = getInt("De un primer numero");
  num2 = getInt("De un segundo numero");

  cout << "Suma " + to_string(num1+num2)
              + "\n Resta: " + to_string(num1-num2)
              + "\n Producto: " + to_string(num1*num2)
              + "\n Division: " + to_string(num1/num2)
       << endl;

  return 0;
}

int ejer2(){
  double precio;

  precio = getInt("Inserte el precio de un producto sin iva.");

  double iva = precio * 0.21;
  double precioConIva = precio + iva;

  cout << "" + to_string(precio +(precio*0.21)) << endl;
  cout << precioConIva;

  return 0;
}