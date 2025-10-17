#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../include/VDinamico.h"
#include "../include/ListaEnlazada.h"
#include "../include/PaMedicamento.h"
#include "../include/MediExpress.h"

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
        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "----------------------------------------------- " << "Prueba I" << " -----------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;
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

        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "----------------------------------------------- " << "Prueba II" << " -----------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;

        MediExpress mediExpr("../data/pa_medicamentos.csv", "../data/laboratorios.csv");
        VDinamico<PaMedicamento> noLab = mediExpr.getMedicamSinLab();
        std::cout << "Medicamentos sin laboratorio: " << noLab.len() << "\n";

        ListaEnlazada<Laboratorio> granada = mediExpr.buscarLabCiudad("Granada");
        std::cout << "\nLaboratorios en Granada o provincia: " << granada.size() << "\n";
        for (auto it = granada.iterator(); !it.isEnd(); it.next()) {
            std::cout << "- " << it.data() << "\n";
        }

    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    return 0;
}
