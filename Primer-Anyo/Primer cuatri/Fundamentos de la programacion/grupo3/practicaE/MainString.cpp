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
        "\nEjercicio 2: Acabar el programa al introducir: FIN y dar el mayor y menor lexicográfico."
        "\nEjercicio 3: Igual pero el mayor y menor seran por caracter."
        "\nEjercicio 4: Comprovar si el nombre introducido se encuentra en el vector."
        "\nEjercicio 5: Palindromo de palabras."
        "\nEjercicio 6: Palindromo de frases."
        "\nFin del programa: 0";
}

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
        case 5:
            {
                ejer5();
                break;
            }
        case 6:
            {
                ejer5();
                break;
            }
        case 7:
            {
                ejer7();
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