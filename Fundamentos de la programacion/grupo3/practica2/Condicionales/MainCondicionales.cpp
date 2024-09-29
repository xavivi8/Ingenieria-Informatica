//
// Created by jmart on 28/09/2024.
//
#include <iostream>
#include <string>
#include "functions.h"
#include "EjerciciosPracticasCondicionales.h"

using namespace std;

std::string textoMenu(){
    return "Seleccione el ejercicio que desea probar de secuenciales: "
           "\nEjercicio 2: Mayor de dos numeros."
           "\nEjercicio 3: Mayor de tres numeros."
           "\nEjercicio 4: Comprobar si es par o impar.";
}

int menu(){
    int opcion = 1;

    do{
        cout << "\n ---------------------------------------------------------" << endl;
        cout << textoMenu() << endl;
        opcion = getInt("Inserte la opcion: ");

        switch (opcion) {
        case 0: {
          cout << "Fin" << endl;
          break;
        }
        case 2: {
          ejer2();
          break;
        }
        case 3: {
          ejer3();
          break;
        }
        case 4: {
          ejer4();
          break;
        }
        default: {
          cout << "Opcion invalida \n\n" << endl;
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
