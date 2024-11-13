//
// Created by jmart on 13/11/2024.
//
#include <iostream>
#include <string>
#include "functions.h"
#include "EJERCICIOSMODULAR1.h"

using namespace std;

std::string textoMenu()
{
    return "Seleccione el ejercicio que desea probar de modular 1: "
        "\nEjercicio 1: Tiempo toal que tarda un ciclista en correr las etapas."
        "\nFin del programa: 0";
};

int menu()
{
    int opcion;

    do {
        cout << "\n -----------------------------------------------------------------------------------" << endl;
        cout << textoMenu() << endl;
        opcion = getInt("Inserte la opcion: ");
        cin.ignore();

        switch (opcion)
        {
        case 0:
            {
                cout << "Fin" << endl;
                break;
            }
        case 1:
            {

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