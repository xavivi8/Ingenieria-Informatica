#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../include/VDinamico.h"
#include "../include/ListaEnlazada.h"
#include "../include/PaMedicamento.h"
// Preguntar si se pueden usar "#include <vector>"

VDinamico<PaMedicamento> loadMedicinesFromCsv(const std::string &csvPath){

    std::ifstream is;
    std::stringstream columns;
    std::string row;
    int count = 0;
    std::string idNum = "";
    std::string idAlpha = "";
    std::string name = "";

    VDinamico<PaMedicamento> aux;

    is.open(csvPath); // carpeta de proyecto
    if (is.good()){

        clock_t t_ini = clock();

        while (getline(is, row)){

            // ¿Se ha leído una nueva fila?
            if (row != ""){

                columns.str(row);

                // formato de fila: id_number;id_alpha;nombre;

                getline(columns, idNum, ';'); // leemos caracteres hasta encontrar y omitir ';'
                getline(columns, idAlpha, ';');
                getline(columns, name, ';');

                row = "";
                columns.clear();

                /*std::cout << ++count
                          << " Medicamento: ( Id_number=" << idNum
                          << " id_alpha=" << idAlpha << " Nombre=" << name
                          << ")" << std::endl;*/

                PaMedicamento med(std::stoi(idNum), idAlpha, name);
                aux.insert(med);
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float)CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    return aux;
};

void mostrarLista(const ListaEnlazada<int> &lista) {
    auto it = lista.iterator();
    std::cout << "[ ";
    while (!it.isEnd()) {
        std::cout << it.data() << " ";
        it.next();
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief Muestra un separador visual con un título
 */
void separador(const std::string &titulo) {
    std::cout << "=======================================================================================================================" << std::endl;
    std::cout << "----------------------------------------------- " << titulo << " -----------------------------------------------" << std::endl;
    std::cout << "=======================================================================================================================" << std::endl;
}

/**
 * @author Francisco Javier Martín-Lunas Escobar fjme0008@red.ujaen.es
 */
int main(int argc, const char *argv[]) {
    try {
      ListaEnlazada<int> lista;

        separador("Lista creada vacia");
        mostrarLista(lista);

        // Insertar al final valores de 101 a 200
        for (int i = 101; i <= 200; ++i) {
            lista.insertAtEnd(i);
        }
        separador("Insertados valores 101 a 200 al final");
        mostrarLista(lista);

        // Insertar al comienzo valores de 98 a 1 (decrecientes)
        for (int i = 98; i >= 1; --i) {
            lista.insertAtBiginning(i);
        }
        separador("Insertados valores 98 a 1 al comienzo");
        mostrarLista(lista);

        // Insertar 100 delante del 101
        auto it = lista.iterator();
        while(!it.isEnd() && it.data() != 101) {
            it.next();
        }
        if(!it.isEnd()) {
            lista.InsertBefore(it, 100);
        }
        separador("Insertado 100 delante de 101");
        mostrarLista(lista);

        // Insertar 99 detrás del 98
        it = lista.iterator();
        while(!it.isEnd() && it.data() != 98) {
            it.next();
        }
        if(!it.isEnd()) {
            lista.insertAfter(it, 99);
        }
        separador("Insertado 99 detras de 98");
        mostrarLista(lista);

        // Borrar los 10 primeros elementos
        for (int i = 0; i < 10; ++i) {
            lista.removeFirst();
        }
        // Borrar los 10 últimos elementos
        for (int i = 0; i < 10; ++i) {
            lista.removeLast();
        }
        separador("Borrados los 10 primeros y 10 ultimos elementos");
        mostrarLista(lista);

        // Borrar todos los múltiplos de 10
        it = lista.iterator();
        while(!it.isEnd()) {
            if(it.data() % 10 == 0) {
                lista.remove(it);
            } else {
                it.next();
            }
        }
        separador("Borrados los multiplos de 10");
        mostrarLista(lista);

        separador("Fin de la prueba de ListaEnlazada<int>");
        std::cout << "Todos los pasos se ejecutaron correctamente." << std::endl;
    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    return 0;
}
