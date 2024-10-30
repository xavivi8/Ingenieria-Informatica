//
// Created by jmart on 28/10/2024.
//
#include <iostream>
#include <string>
#include "functions.h"
#include "EjerciciosPracticasStrings.h"

using namespace std;

std::string textoMenu()
{
    return "Seleccione el ejercicio que desea probar de secuenciales: "
        "\nEjercicio 1: Cantidad de vocales en la cadena."
        "\nFin del programa: 0";
}

int menu()
{
    int opcion;

    do {
        cout << "\n -----------------------------------------------------------------------------------" << endl;
        cout << textoMenu() << endl;
        opcion = getInt("Inserte la opcion: ");

        switch (opcion)
        {
        case 0:
            {
                cout << "Fin" << endl;
                break;
            }
        case 1:
            {
                ejer1();
                break;
            }
        case 2:
            {
                ejer2();
                break;
            }
        case 3:
            {
                ejer3();
                break;
            }
        case 4:
            {
                ejer4();
                break;
            }
        default:
            {
                cout << "Opcion invalida \n\n" << endl;
                break;
            }
        }
    } while (opcion != 0);

    return 0;
}

int main()
{
    menu();
    return 0;
}