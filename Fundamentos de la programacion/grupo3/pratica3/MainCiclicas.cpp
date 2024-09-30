//
// Created by jmart on 30/09/2024.
//
#include <iostream>
#include "EjerciciosCiclicas.h"

using namespace std;

std::string textoMenu()
{
    return "Seleccione el ejercicio que desea probar de secuenciales: "
        "\nEjercicio 2: Tabla de multiplicar de un numero."
        "\nEjercicio 3: Mayor de tres numeros."
        "\nFin del programa: 0";
}

int menu()
{
    int opcion = 1;

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
        case 2:
            {
                ejer2();
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
