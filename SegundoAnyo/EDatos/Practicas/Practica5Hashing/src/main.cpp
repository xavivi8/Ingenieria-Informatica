#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <vector>
#include "../include/PaMedicamento.h"
#include "../include/MediExpress.h"
#include "../include/utils.h"

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
        const std::string FICH_FARMACIAS    = "../data/farmacias.csv";
        const std::string FICH_LABORATORIOS = "../data/laboratorios.csv";
        const std::string FICH_MEDICAMENTOS = "../data/pa_medicamentos.csv";

        // ===========================================================
        // 1) Carga de datos y construcción de la tabla hash
        // ===========================================================
        separador("CARGA INICIAL DE DATOS Y CONSTRUCCION DE LA TABLA HASH");

        auto t0 = std::chrono::high_resolution_clock::now();
        MediExpress sistema(FICH_MEDICAMENTOS, FICH_LABORATORIOS, FICH_FARMACIAS);
        auto t1 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> durCarga = t1 - t0;
        std::cout << "Tiempo de carga de datos y construccion de la tabla hash: "
                  << durCarga.count() << " ms\n\n";

        // Mostrar el estado interno de la tabla (max colisiones, lambda, promedio, etc.)
        sistema.mostrarEstadoTabla();

        std::cout << "\n";
        std::cout << ">> Con estos datos puedes rellenar la tabla del fichero ../analisis_Thash.md\n";
        std::cout << "   (max colisiones, factor de carga, promedio de colisiones, etc.)\n\n";

        // ===========================================================
        // 2) Prueba de rendimiento: hash vs lista
        // ===========================================================
        separador("PRUEBA DE RENDIMIENTO: TABLA HASH VS LISTA");

        sistema.pruebaRendimiento();

        std::cout << "\n";
        std::cout << ">> Usa los tiempos mostrados para completar el apartado de rendimiento\n";
        std::cout << "   en ../analisis_Thash.md (comparacion hash vs std::list<PaMedicamento>).\n";
    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    return 0;
}
