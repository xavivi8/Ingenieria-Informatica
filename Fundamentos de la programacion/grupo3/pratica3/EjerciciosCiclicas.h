//
// Created by jmart on 30/09/2024.
//
#include <iostream>
#include <cmath>
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

int ejer4() {
  double sol=0;
  string solucion="";

  for(int i=1; i<=10; i++) {
    sol += pow(i,2);
    solucion += to_string(i)+"^2";
    if(i!=10) {
      solucion += " + ";
    }
  }

  cout << sol << " = " << solucion;

  return 0;
}

int ejer5() {
  int contador=0;
  double temperatura, sumatorio=0, mayor = 0, menor = 0;

  for(int i=0; i<=24; i+=4) {
    contador++;

    temperatura = getDouble(("Inserte la temperatura " + to_string(i) +": "));

    if(temperatura<menor || i == 0) {
      menor = temperatura;
    }
    if(temperatura>mayor || i==0) {
      mayor = temperatura;
    }

    sumatorio += temperatura;
  }

  cout << "Media: " << (sumatorio/contador) << "\nMayor: " << mayor << "\nMenor: " << menor <<endl;

  return 0;
}

int ejer6() {
  int num;

  cout << "Introduce un numero distinto de 0 y fuera del rango [20,30]" << endl;

  do {
    num = getInt("Inserte un numero: ");
  } while (!(num ==0 ||(num >= 20 && num <=30)));

  return 0;
}

int ejer7() {
  int x, y;
  long long resultado = 1;

  cout << "Inserte numeros para calcular x^y" << endl;

  do {
    x = getInt("Inserte un numero x: ");
    if(x<=0) {
      cout << "x debe ser positivo." << endl;
    }
  } while (x <= 0);

  do {
    y = getInt("Inserte un numero y: ");
    if(y<=0) {
      cout << "y debe ser positivo." << endl;
    }
  } while (y <= 0);

  for(int i = 1; i<=y; i++) {
    resultado *= x;
  }

  cout << "El resiltado de " << x << "^" << y << " da " << resultado << endl;

  return 0;
}

int ejer8() {
  int numero_terminos;
  double pi = 0.0;

  numero_terminos = getInt("Introduce el numero de terminos para aproximar pi:");

  // Calcular la aproximacion de pi usando la serie de Leibniz
  for (int i = 0; i < numero_terminos; i++) {
    // Si el término es par, se suma; si es impar, se resta
    if (i % 2 == 0) {
      pi += 1.0 / (2 * i + 1);
    } else {
      pi -= 1.0 / (2 * i + 1);
    }
  }

  // Multiplicar por 4 para obtener la aproximación de pi
  pi *= 4;

  cout << "Aproximacion de pi con " << numero_terminos << " terminos: " << pi << endl;

  return 0;
}

int ejer9(){
  bool finish = false;
  int origin_x, origin_y, mcd, x, y;

  do {
    x = getInt("Inserte un numero x: ");
    y = getInt("Inserte un numero y: ");

    if(x<=0 || y<=0) {
      cout << "Ambos números deben ser positivos." << endl;
    }
  } while (x <= 0 && y <= 0);

  mcd = x;
  origin_x = x;
  origin_y = y;

  if (x%y==0) {
    mcd = y;
    cout << "mcd(" << origin_x << "," << origin_y << ") = " << y << endl;
  } else {
    while(y != 0 && finish == false) {
      int resto = x % y;
      x=y;
      y=resto;
      int r= x % y;
      if(r==0) {
        mcd = y;
        finish = true;
      } else if(y % r == 0) {
        mcd = y;
        finish = true;
      } else if(r % (y % r) == 0) {
        mcd = y;
        finish = true;
      }
    }

    cout << "mcd(" << origin_x << "," << origin_y << ") = mcd( " << origin_y << "," << mcd << ")" << endl;
  }

  return 0;
}

int ejer10() {
  char caracter;
  string son_vocales;

  cout << "Inserte caracteres, para parar inserte + o - ." << endl;

  do{
    caracter = getChar("Inserte un caracter: ");

    if(!isVocal(caracter) && son_vocales.empty() && caracter != '+' && caracter != '-') {
      son_vocales = "no ";
    }

  } while (caracter != '+' && caracter != '-');

  cout << "En los caracteres insertados " << son_vocales << "hay vocales." << endl;

  return  0;
}

#endif //EJERCICIOSCICLICAS_H
