//
// Created by jmart on 13/11/2024.
//
#include "functions.h"

using namespace std;

#ifndef EJERCICIOSMODULAR1_H
#define EJERCICIOSMODULAR1_H

/*
* Ejercicio 1
* */
int numeroRealAbsoluto(){
  double real;
  int absoluto=0;

  real = getDouble("Inserte el numero real: ");
  absoluto = real;

  return absoluto;
}

int ejer1() {
  int absoluto=0;
  absoluto = numeroRealAbsoluto();
  return 0;
}

/*
* Ejercicio 2
* */

string mayorCadena() {
  string cad1="", cad2="";

  cad1 = getString("Inserte la cadena 1: ");
  cad2 = getString("Inserte la cadena 2: ");

  if(cad1.length() <= cad2.length() ){
    cad1 = cad2;
  }

  return cad1;
}

int ejer2(){
  string cadMasLarga="";

  

  return 0;
}

#endif //EJERCICIOSMODULAR1_H
