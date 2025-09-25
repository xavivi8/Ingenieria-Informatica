#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "VDinamico.h"

int main(int argc, const char * argv[]) {

    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string id_number = "";
    std::string id_alpha="";
    std::string nombre="";


    is.open("../pa_medicamentos.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, id_number, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, id_alpha,';');
                getline(columnas, nombre,';');


                fila="";
                columnas.clear();

                std::cout << ++contador
                          << " Medicamento: ( Id_number=" << id_number
                          << " id_alpha=" << id_alpha << " Nombre=" << nombre
                          << ")" << std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    /*    Prueba de VDinamico    */
std::cout << "=== Prueba de VDinamico ===" << std::endl;

    // 1. Constructor por defecto
    VDinamico<int> a;
    std::cout << "Vector a creado (tam=" << a.size() << ")" << std::endl;

    // 2. Insertar al final
    a.insert(10);
    a.insert(20);
    a.insert(30);
    std::cout << "a despues de inserts al final: ";
    for (unsigned int i = 0; i < a.size(); i++) std::cout << a[i] << " ";
    std::cout << std::endl;

    // 3. Insertar en posición intermedia
    a.insert(15, 1);
    std::cout << "a despues de insertar 15 en pos 1: ";
    for (unsigned int i = 0; i < a.size(); i++) std::cout << a[i] << " ";
    std::cout << std::endl;

    // 4. Constructor con tamaño inicial
    VDinamico<int> b(3);
    std::cout << "Vector b creado con tam inicial=3 (tam=" << b.size() << ")" << std::endl;

    // 5. Asignar valores a b usando operator[]
    for (unsigned int i = 0; i < b.size(); i++) b[i] = (i+1)*100;
    std::cout << "Contenido de b: ";
    for (unsigned int i = 0; i < b.size(); i++) std::cout << b[i] << " ";
    std::cout << std::endl;

    // 6. Constructor copia
    VDinamico<int> c(b);
    std::cout << "Vector c (copia de b): ";
    for (unsigned int i = 0; i < c.size(); i++) std::cout << c[i] << " ";
    std::cout << std::endl;

    // 7. Constructor de copia parcial
    VDinamico<int> d(b, 1, 2);
    std::cout << "Vector d (copia parcial de b desde pos 1, num=2): ";
    for (unsigned int i = 0; i < d.size(); i++) std::cout << d[i] << " ";
    std::cout << std::endl;

    // 8. Operador asignación
    a = b;
    std::cout << "a despues de asignacion a=b: ";
    for (unsigned int i = 0; i < a.size(); i++) std::cout << a[i] << " ";
    std::cout << std::endl;

    // 9. Eliminar último elemento
    int eliminado = a.remove();
    std::cout << "Eliminado ultimo de a: " << eliminado << std::endl;
    std::cout << "a despues de remove(): ";
    for (unsigned int i = 0; i < a.size(); i++) std::cout << a[i] << " ";
    std::cout << std::endl;

    // 10. Eliminar en posicion concreta
    eliminado = a.remove(0);
    std::cout << "Eliminado en pos 0 de a: " << eliminado << std::endl;
    std::cout << "a despues de remove(0): ";
    for (unsigned int i = 0; i < a.size(); i++) std::cout << a[i] << " ";
    std::cout << std::endl;

    // 11. Probar size
    std::cout << "Tamanyo de a: " << a.size() << std::endl;

    std::cout << "=== Fin de pruebas ===" << std::endl;
    return 0;
}

