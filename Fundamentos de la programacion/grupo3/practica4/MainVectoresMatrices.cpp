//
// Created by jmart on 07/10/2024.
//
#include <iostream>
#include <string>
#include "functions.h"
#include "EjerciciosVectores.h"

using namespace std;

std::string textoMenu()
{
    return "Seleccione el ejercicio que desea probar de secuenciales: "
        "\nEjercicio 1: Almacenar y mostrar numeros con su indice."
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
                ejercicio1();
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
