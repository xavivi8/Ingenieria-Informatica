//
// Created by jmart on 23/09/2024.
//
#include <iostream>
#include <string>
#include "functions.h"
#include "EjerciciosPracticasSecuenciales.h"

using namespace std;

std::string textoMenu(){
  return "Seleccione el ejercicio que desea probar de secuenciales: "
         "\nEjercicio 1: sumas, restas, divisiones y productos."
         "\nEjercicio 2: iva de in producto."
         "\nEjercicio 3: Datos de una persona"
         "\nEjercicio 4: Nota media"
         "\nEjercicio 5: Media de alumnos"
         "\nEjercicio 6: Raiz cuadrada"
         "\nEjercicio 11: Factura de luz"
         "\nFin del programa: 0";
}

int menu(){
  int opcion = 1;

  do {
    cout << "---------------------------------------------------------" << endl;
    cout << textoMenu() << endl;
    opcion = getInt("Inserte la opcion: ");

    switch (opcion) {
      case 0: {
        cout << "Fin" << endl;
        break;
      }
      case 1: {
        ejer1();
        break;
      }
      case 2: {
        ejer2();
        break;
      }
      case 3:{
          ejer3();
          break;
      }
      case 4:{
          ejer4();
          break;
      }
      case 5:{
          ejer5();
          break;
      }
      case 6:{
          ejer6();
          break;
      }
      case 11:{
          ejer11();
          break;
      }
      default: {
        cout << "Opcion invalida \n\n" << endl;
        opcion = 1;
        break;
      }

    }

  } while(opcion != 0);

  return 0;
}

int main(){
  menu();
  return 0;
}