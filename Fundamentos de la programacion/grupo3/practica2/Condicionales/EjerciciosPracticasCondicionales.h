//
// Created by jmart on 29/09/2024.
//
#include <iostream>
#include "functions.h"

int ejer2(){
  double num1, num2;

  num1 = getDouble("Inserte un numero: ");
  num2 = getDouble("Inserte otro numero: ");

  if (num1 > num2) {
    cout << "El número mayor es: " << num1 << endl;
  } else if (num2 > num1) {
    cout << "El número mayor es: " << num2 << endl;
  } else {
    cout << "Ambos números son iguales." << endl;
  }

  return 0;
}

int ejer3(){
  double num1, num2, num3;

  num1 = getDouble("Inserte el primer numero: ");
  num2 = getDouble("Inserte el segundo numero: ");
  num3 = getDouble("Inserte el tercer numero: ");

  if (num1 > num2 && num1 > num3){
    cout << "El numero mayor es: " << num1 << endl;
  } else if(num2 > num1 && num2 > num3){
    cout << "El numero mayor es: " << num2 << endl;
  } else if(num3 > num1 && num3 > num2){
    cout << "El numero mayor es: " << num3 << endl;
  } else {
    cout << "Ambos numeros son iguales." << endl;
  }

  return 0;
}

int ejer4(){
  int num;

  num = getInt("Inserte un numero: ");

  (num % 2 == 0) ? cout << "El numero es par" : cout << "El numero es impar";

  return 0;
}

int ejer5() {
  int n, m;

  n = getInt("Inserte un numero n: ");
  m = getInt("Inserte un numero m: ");

  (m % n == 0) ? cout << n << " divide a " << m << endl : cout << n << " no divide a " << m << endl;

  return 0;
}

int ejer6() {
  char caracte;

  caracte = getChar("Inserte un caracter: ");

  if (caracte >= 'A' && caracte<='Z') {
    cout << "Es mayuscula" << endl;
  } else{
    cout << "Es minuscula" << endl;
  }


  return 0;
}

int ejer7() {
  char caracte;

  caracte = getChar("Inserte un caracter: ");

  if(isVocal(caracte)) {
    if (caracte >= 'A' && caracte<='Z') {
      cout << "Es mayuscula" << endl;
    } else{
      cout << "Es minuscula" << endl;
    }
  } else {
    cout << "No es una vocal" << endl;
  }

  return 0;
}