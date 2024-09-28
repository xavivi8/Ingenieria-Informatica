//
// Created by jmart on 28/09/2024.
//
#include <iostream>
#include <string>
#include "functions.h"

using namespace std;

std::string textoMenu(){
    return "Seleccione el ejercicio que desea probar de secuenciales: "
           "\nEjercicio 2: Mayor de dos números.";
}

int menu(){
    int opcion = 1;

    do{
        cout << "---------------------------------------------------------" << endl;
        cout << textoMenu() << endl;
        opcion = getInt("Inserte la opcion: ");

        switch (opcion) {
        case 0: {
                cout << "Fin" << endl;
                break;
        }
        case 1: {
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
