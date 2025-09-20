//
// Created by jmart on 26/11/2024.
//
#include <iostream>

#include "functions.h"

#ifndef EJERCICIOSPUNTEROS_H
#define EJERCICIOSPUNTEROS_H

void intercambiar(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int ejer1(){
  int x=0,y=0;

  x = getInt("Inserte un numero x.");
  y = getInt("Inserte un numero y.");

  std::cout << "Antes del intercambio: " << std::endl;
  std::cout << "x = " << x << ", y = " << y << std::endl;

  intercambiar(&x,&y);

  std::cout << "Despues del intercambio: " << std::endl;
  std::cout << "x = " << x << ", y = " << y << std::endl;

  return 0;
};

/**
* cont int* hace que no se pueda modificar el valor al que apunta*/
void calcularMaxMin(const int* vector, int tamanyo, int* maximo, int* minimo){
  if (tamanyo <= 0) {
    cout << "El vector está vacío o el tamaño es inválido." << endl;
    return;
  }
  *maximo = vector[0];
  *minimo = vector[0];

  for (int i = 1; i < tamanyo; i++) {
    if (vector[i] > *maximo) {
      *maximo = vector[i];
    }
    if (vector[i] < *minimo) {
      *minimo = vector[i];
    }
  }
}

int ejer2(){
  int vector[] = {2,3,7,6,12,43,1,4};
  /*
   *  sizeof(vector) devuelve el tamaño en bytes del arreglo completo.
   *  sizeof(vector[0]) devuelve el tamaño en bytes del primer elemento del
   *         arreglo (ya que todos los elementos tienen el mismo tamaño).
   *  La división calcula cuántos elementos hay en el arreglo.
   * */
  int tamanyo = sizeof(vector) / sizeof(vector[0]);
  int maximo, minimo;

  std::cout << "Elementos del vector: ";
  for(int i=0; i< tamanyo;i++) {
    std::cout << vector[i] << " ";
  }
  std::cout << std::endl;

  calcularMaxMin(vector, tamanyo, &maximo, &minimo);

  cout << "Maximo: " << maximo << endl;
  cout << "Minimo: " << minimo << endl;

  return 0;
};

struct FECHA {
  int dia;
  int mes;
  int anyo;
};

void cogerFecha(FECHA* ptr, string message){
  int dia=0,mes=0,anyo=0;

  std::cout << message << std::endl;

  ptr->dia = getInt("Inserte el dia de la fecha.");
  ptr->mes = getInt("Inserte el mes de la fecha.");
  ptr->anyo = getInt("Inserte el anyo de la fecha.");
}

void pipeFecha(const FECHA* ptr) {
  std::cout << ptr->dia << "/" << ptr->mes << "/" << ptr->anyo << std::endl;
}

bool esAnterior (const FECHA* fecha1, const FECHA* fecha2) {
  if (fecha1->anyo < fecha2->anyo) {
    return true;
  } else if (fecha1->anyo == fecha2->anyo) {
    if (fecha1->mes < fecha2->mes) {
      return true;
    } else if (fecha1->mes == fecha2->mes) {
      return fecha1->dia < fecha2->dia;
    }
  }
  return false;
}

void incrementarAnyo(FECHA* fecha) {
  // Verificar si es 29 de febrero y el año es bisiesto
  if (fecha->mes == 2 && fecha->dia == 29) {
    // Comprobar si el siguiente año es bisiesto
    int siguienteAnio = fecha->anyo + 1;
    if ((siguienteAnio % 4 == 0 && siguienteAnio % 100 != 0) || (siguienteAnio % 400 == 0)) {
      fecha->anyo = siguienteAnio;
    } else {
      // Si no es bisiesto, pasar al 28 de febrero
      fecha->dia = 28;
      fecha->anyo = siguienteAnio;
    }
  } else {
    // Incrementar normalmente
    fecha->anyo++;
  }
}

int ejer3(){
  FECHA fecha1, fecha2;
  cogerFecha(&fecha1,"Fecha 1: ");
  cogerFecha(&fecha2,"Fecha 2: ");

  if (esAnterior(&fecha1, &fecha2)) {
    cout << "La primera fecha es anterior a la segunda.\n" << std::endl;
  } else {
    cout << "La primera fecha no es anterior a la segunda.\n" << std::endl;
  }

  std::cout << "\nIncrementando un anyo a la primera fecha...\n" << std::endl;
  incrementarAnyo(&fecha1);
  pipeFecha(&fecha1);
  return 0;
};

#endif //EJERCICIOSPUNTEROS_H
