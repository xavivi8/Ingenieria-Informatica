#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

#include "../include/PaMedicamento.h"
#include "../include/MediExpress.h"
#include "../include/utils.h"

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
        
        
        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "----------------------------------------------- " << "Prueba II" << " -----------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;

        
    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    return 0;
}
