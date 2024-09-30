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
        "\nEjercicio 3: Numeros mayores que 0."
        "\nEjercicio 4: Suma de cuadrados del 1 al 10."
        "\nEjercicio 5: Calculo de temperaturas."
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
        case 5:
            {
                ejer5();
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
