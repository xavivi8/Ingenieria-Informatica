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
         "\nEjercicio 2: iva de in producto.";
}

int menu(){
  int opcion = 1;

  do{
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
      default: {
        cout << "Opcion invalida \n\n" << endl;
        opcion = 1;
        break;
      }

    }

  }while(opcion != 0);

  return 0;
}

int main(){
  menu();
  return 0;
}