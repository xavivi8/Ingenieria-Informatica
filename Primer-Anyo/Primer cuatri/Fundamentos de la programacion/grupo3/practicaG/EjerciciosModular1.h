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
int numeroRealAbsoluto(double real){
  int absoluto=0;

  absoluto = real;

  return absoluto;
}

int ejer1() {
  int absoluto=0;
  double real;

  real = getDouble("Inserte el numero real: ");

  absoluto = numeroRealAbsoluto(real);
  cout << "El absoluto es: " << absoluto << endl;

  return 0;
}

/*
* Ejercicio 2
* */

string mayorCadena(string cad1, string cad2) {
  if(cad1.length() <= cad2.length() ){
    cad1 = cad2;
  }

  return cad1;
}

int ejer2(){
  string cad1="", cad2="", cadMasLarga="";

  cad1 = getString("Inserte la cadena 1: ");
  cad2 = getString("Inserte la cadena 2: ");

  cadMasLarga = mayorCadena(cad1, cad2);

  cout << "La cadema mas larga es: "<<cadMasLarga<<endl;

  return 0;
}

#endif //EJERCICIOSMODULAR1_H
