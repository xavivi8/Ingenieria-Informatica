#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "../include/MediExpress.h"

/**
 * @brief Muestra un separador visual con un título
 */
void separador(const std::string &titulo) {
    std::cout << "=======================================================================================================================" << std::endl;
    std::cout << "----------------------------------------------- " << titulo << " -----------------------------------------------" << std::endl;
    std::cout << "=======================================================================================================================" << std::endl;
}

/**
 * @brief Ejecuta la Prueba I: ajuste de la tabla + prueba de rendimiento. Devuelve un MediExpress construido con la mejor configuración encontrada.
 */
MediExpress ejecutarPruebaI(const std::string &fichMed, const std::string &fichLab, const std::string &fichFar) {
    const double   LAMBDAS[2]      = {0.65, 0.68};
    const char*    LAMBDA_TEXT[2]  = {"0.65", "0.68"};
    const TipoHash TIPOS[3]        = {HASH1, HASH2, HASH3};
    const char*    NOMBRES_HASH[3] = {"hash1", "hash2", "hash3"};

    struct ResultadoHash {
        std::string  nombreFuncion;
        unsigned int tamTabla;
        float        factorCarga;
        unsigned int maxCol;
        float        promCol;
        unsigned int numSup10;
    };

    ResultadoHash resultados[2][3];

    // Creamos 6 objetos MediExpress: 3 funciones hash x 2 lambdas
    for (int l = 0; l < 2; ++l) {
        for (int h = 0; h < 3; ++h) {
            MediExpress tmp(fichMed,
                            fichLab,
                            fichFar,
                            LAMBDAS[l],
                            TIPOS[h]);

            resultados[l][h].nombreFuncion = NOMBRES_HASH[h];
            resultados[l][h].tamTabla = tmp.getTamTabla();
            resultados[l][h].factorCarga = tmp.getFactorCarga();
            resultados[l][h].maxCol = tmp.getMaxColisiones();
            resultados[l][h].promCol = tmp.getPromedioColisiones();
            resultados[l][h].numSup10 = tmp.getNumMax10();
        }
    }

    // Elegimos automáticamente la mejor configuración (menor promedio de colisiones)
    int bestL = 0;
    int bestH = 0;
    float bestProm = resultados[0][0].promCol;
    for (int l = 0; l < 2; ++l) {
        for (int h = 0; h < 3; ++h) {
            if (resultados[l][h].promCol < bestProm) {
                bestProm = resultados[l][h].promCol;
                bestL    = l;
                bestH    = h;
            }
        }
    }

    // Construir el sistema (carga CSV + construcción tabla hash) con la mejor config
    std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();
    MediExpress sistema(fichMed, fichLab, fichFar, LAMBDAS[bestL], TIPOS[bestH]);
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> durCarga = t1 - t0;

    // Mostrar por pantalla el estado interno de la tabla elegida
    sistema.mostrarEstadoTabla();

    // Lanzar la prueba de rendimiento (rellena m_tiempoHash / m_tiempoLista)
    sistema.pruebaRendimiento();

    // Tiempos de búsqueda hash vs lista
    double tHash = sistema.getTiempoHash();
    double tList = sistema.getTiempoLista();

    std::ofstream md("../analisis_Thash.md");
    if (!md.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir ../analisis_Thash.md para escritura\n";
    } else {
        md << "# Análisis de tablas de dispersión\n\n";
        md << "* *Francisco Javier Martín-Lunas Escobar*\n\n";

        // ---- Tablas de ajuste para λ=0.65 y λ=0.68 ----
        for (int l = 0; l < 2; ++l) {
            unsigned int tamTabla = resultados[l][0].tamTabla;

            md << "## Tamaño de tabla: " << tamTabla << "\n";
            md << "| función | máximo de colisiones | factor de carga | promedio de colisiones |\n";
            md << "|---------|:--------------------:|:---------------:|:----------------------:|\n";

            for (int h = 0; h < 3; ++h) {
                const ResultadoHash &r = resultados[l][h];
                md << "| " << r.nombreFuncion << "   |  "
                   << r.maxCol << "          |      "
                   << r.factorCarga << "       |        "
                   << r.promCol << "         |\n";
            }
            md << "\n";

            md << "Número de inserciones con más de 10 colisiones para este tamaño de tabla:\n\n";
            for (int h = 0; h < 3; ++h) {
                const ResultadoHash &r = resultados[l][h];
                md << "- " << r.nombreFuncion << ": " << r.numSup10 << "\n";
            }
            md << "\n";
        }

        const ResultadoHash &best = resultados[bestL][bestH];

        md << "## Justificación de la configuración elegida\n\n";
        md << "Hemos optado por la configuración de tabla con tamaño "
           << best.tamTabla << ", aplicando la función "
           << best.nombreFuncion << " con λ objetivo "
           << LAMBDA_TEXT[bestL] << ".\n";
        md << "Es la que ofrece el menor promedio de colisiones ("
           << best.promCol << ") y un máximo de "
           << best.maxCol << " colisiones en la inserción más costosa,\n";
        md << "además de un número de inserciones con más de 10 colisiones igual a "
           << best.numSup10 << ", inferior al de otras alternativas.\n\n";

        md << "## Comparación de tiempos dados en milisegundos\n\n";
        md << "Tiempo en realizar las búsquedas en la Tabla Hash: " << tHash  << " ms\n";
        md << "Tiempo en realizar las búsquedas en la Lista: "      << tList  << " ms\n";
        md << "Tiempo aproximado de carga de datos y construcción de la tabla: "
           << durCarga.count() << " ms\n";

        md.close();
    }

    std::cout << "Informe generado en ../analisis_Thash.md\n";

    return sistema;
}


/**
 * @author Francisco Javier Martín-Lunas Escobar  (fjme0008@red.ujaen.es)
 */
int main(int argc, const char *argv[]) {
    try {
        const std::string FICH_FARMACIAS    = "../data/farmacias.csv";
        const std::string FICH_LABORATORIOS = "../data/laboratorios.csv";
        const std::string FICH_MEDICAMENTOS = "../data/pa_medicamentos.csv";

        separador("Prueba I");
        MediExpress sistema = ejecutarPruebaI(FICH_MEDICAMENTOS, FICH_LABORATORIOS, FICH_FARMACIAS);

        separador("Prueba II Parte I");
        const std::string consultas[] = {
            "MAGNESIO CLORURO HEXAHIDRATO",
            "CLORURO",
            "ANHIDRO CALCIO CLORURO",
            "LIDOCAINA HIDROCLORURO",
            "MENTA PIPERITA",
            "VIRUS GRIPE"
        };
        const int NUM_CONSULTAS = sizeof(consultas) / sizeof(consultas[0]);

        for (int i = 0; i < NUM_CONSULTAS; ++i) {
            const std::string &q = consultas[i];
            std::vector<PaMedicamento*> meds = sistema.buscarCompuesto(q);

            std::cout << "\nBusqueda por nombre: \"" << q << "\"\n";
            std::cout << "  Se han encontrado " << meds.size() << " medicamento(s).\n";
            if (meds.empty()) {
                std::cout << "  (sin resultados)\n";
            } else {
                for (std::size_t j = 0; j < meds.size(); ++j) {
                    PaMedicamento* pm = meds[j];
                    if (!pm) continue;
                    std::cout << "  - ID " << pm->getIdNum()
                              << " | "   << pm->getName() << "\n";
                }
            }
        }

        separador("Prueba II Parte II");
        const int NUM_CLIENTES = 12;
        const int ID_OXIDO     = 3640;   // ÓXIDO DE MAGNESIO

        std::vector<Farmacia*> farSevilla = sistema.buscarFarmacias("Sevilla");
        if (farSevilla.empty()) {
            std::cout << "\nNo se han encontrado farmacias en la provincia de Sevilla.\n";
        } else {
            for (std::size_t i = 0; i < farSevilla.size(); ++i) {
                Farmacia* f = farSevilla[i];
                if (!f) continue;

                std::cout << "\nFarmacia " << f->getCif()
                          << " - " << f->getName()
                          << " (" << f->getCity() << ", " << f->getProvince() << ")\n";

                // Estado inicial: mostrar medicamentos con "MAGNESIO" y su stock
                std::vector<PaMedicamento*> magIni = f->buscaMedicamNombre("MAGNESIO");
                std::cout << "  Estado inicial (medicamentos con 'MAGNESIO'):\n";
                if (magIni.empty()) {
                    std::cout << "    (ninguno)\n";
                } else {
                    for (std::size_t j = 0; j < magIni.size(); ++j) {
                        PaMedicamento* pm = magIni[j];
                        if (!pm) continue;
                        int stock = f->getStock(pm->getIdNum());
                        std::cout << "    - ID " << pm->getIdNum()
                                  << " | " << pm->getName()
                                  << " | stock = " << stock << "\n";
                    }
                }

                // 12 clientes
                for (int cli = 0; cli < NUM_CLIENTES; ++cli) {
                    std::cout << "  Cliente " << (cli + 1) << ": ";

                    // Buscar un tipo de magnesio en stock
                    std::vector<PaMedicamento*> mag = f->buscaMedicamNombre("MAGNESIO");
                    PaMedicamento* elegido = nullptr;

                    for (std::size_t j = 0; j < mag.size(); ++j) {
                        PaMedicamento* pm = mag[j];
                        if (!pm) continue;
                        int stock = f->getStock(pm->getIdNum());
                        if (stock > 0) {
                            elegido = pm;
                            break;
                        }
                    }

                    PaMedicamento* dummy = 0;

                    if (elegido) {
                        try {
                            f->comprarMedicam(elegido->getIdNum(), 1, dummy);
                            std::cout << "compra " << elegido->getName()
                                      << " (ID " << elegido->getIdNum() << ")\n";
                        } catch (const std::exception &e) {
                            std::cout << "no pudo comprar " << elegido->getName()
                                      << " (" << e.what() << ")\n";
                        }
                    } else {
                        std::cout << "no encuentra ningun 'MAGNESIO' en stock. "
                                  << "Se pide OXIDO DE MAGNESIO (ID " << ID_OXIDO << ") al laboratorio.\n";

                        // Reponer 10 unidades de ÓXIDO DE MAGNESIO a la farmacia
                        sistema.suministrarFarmacia(*f, ID_OXIDO, 10);
                    }
                }

                // Estado final: mostrar de nuevo los medicamentos con "MAGNESIO"
                std::vector<PaMedicamento*> magFin = f->buscaMedicamNombre("MAGNESIO");
                std::cout << "  Estado final (medicamentos con 'MAGNESIO'):\n";
                if (magFin.empty()) {
                    std::cout << "    (ninguno)\n";
                } else {
                    for (std::size_t j = 0; j < magFin.size(); ++j) {
                        PaMedicamento* pm = magFin[j];
                        if (!pm) continue;
                        int stock = f->getStock(pm->getIdNum());
                        std::cout << "    - ID " << pm->getIdNum()
                                  << " | " << pm->getName()
                                  << " | stock = " << stock << "\n";
                    }
                }
            }
        }

        separador("Prueba II Parte III");
        std::vector<Farmacia*> farJaen = sistema.buscarFarmacias("Jaen");
        if (farJaen.empty()) {
            std::cout << "No se ha encontrado farmacia en la provincia de Jaen.\n";
        } else {
            Farmacia* fUbeda = farJaen[0];
            std::cout << "Farmacia de Jaen (Ubeda): "
                    << fUbeda->getCif() << " - " << fUbeda->getName()
                    << " (" << fUbeda->getCity() << ", " << fUbeda->getProvince() << ")\n";

            // Buscar todas las formas de "ANTIGENO OLIGOSACARIDO" EN TODO EL SISTEMA
            std::vector<PaMedicamento*> antigenos =
                    sistema.buscarCompuesto("ANTIGENO OLIGOSACARIDO");

            std::cout << "\nSe han encontrado " << antigenos.size()
                    << " medicamento(s) que contienen \"ANTIGENO OLIGOSACARIDO\" en su nombre.\n";

            std::cout << "\nStock inicial de 'ANTIGENO OLIGOSACARIDO' (todas las formas) en la farmacia de Ubeda:\n";
            if (antigenos.empty()) {
                std::cout << "  No se han encontrado medicamentos con ese nombre en el sistema.\n";
            } else {
                // Mostrar stock inicial en la farmacia (aunque sea 0)
                for (std::size_t i = 0; i < antigenos.size(); ++i) {
                    PaMedicamento* pm = antigenos[i];
                    if (!pm) continue;
                    int stock = fUbeda->getStock(pm->getIdNum());   // 0 si no estaba en stock
                    std::cout << "  - ID " << pm->getIdNum()
                            << " | " << pm->getName()
                            << " | stock = " << stock << "\n";
                }

                // Pedir 10 unidades de todos los que haya disponibles (en el sistema)
                std::cout << "\nSe piden 10 unidades de todas las formas de 'ANTIGENO OLIGOSACARIDO'.\n";
                for (std::size_t i = 0; i < antigenos.size(); ++i) {
                    PaMedicamento* pm = antigenos[i];
                    if (!pm) continue;
                    sistema.suministrarFarmacia(*fUbeda, pm->getIdNum(), 10);
                }

                // Mostrar stock final en la farmacia
                std::cout << "\nStock final tras el pedido en la farmacia de Ubeda:\n";
                for (std::size_t i = 0; i < antigenos.size(); ++i) {
                    PaMedicamento* pm = antigenos[i];
                    if (!pm) continue;
                    int stock = fUbeda->getStock(pm->getIdNum());
                    std::cout << "  - ID " << pm->getIdNum()
                            << " | " << pm->getName()
                            << " | stock = " << stock << "\n";
                }
            }
        }

        separador("Prueba II Parte IV");
        // Buscar primero por nombre y luego eliminar en el orden indicado
        const std::string nombresProhibidos[] = { "CIANURO", "BISMUTO" };
        const int NUM_PROHIBIDOS = 2;

        for (int i = 0; i < NUM_PROHIBIDOS; ++i) {
            const std::string &nombre = nombresProhibidos[i];
            std::vector<PaMedicamento*> encontrados = sistema.buscarCompuesto(nombre);

            std::cout << "\nMedicamentos que contienen \"" << nombre
                      << "\" en su nombre: " << encontrados.size() << "\n";

            if (encontrados.empty()) {
                std::cout << "  (ninguno)\n";
                continue;
            }

            // Mostrar y eliminar
            for (std::size_t j = 0; j < encontrados.size(); ++j) {
                PaMedicamento* pm = encontrados[j];
                if (!pm) continue;

                int id = pm->getIdNum();
                std::cout << "  - Eliminando ID " << id
                          << " | " << pm->getName() << " ... ";

                bool ok = sistema.eliminarMedicamento(id);
                if (ok) {
                    std::cout << "OK\n";
                } else {
                    std::cout << "ya estaba eliminado o no se encontraba.\n";
                }
            }
        }

        // Comprobación: intentar buscarlos de nuevo
        for (int i = 0; i < NUM_PROHIBIDOS; ++i) {
            const std::string &nombre = nombresProhibidos[i];
            std::vector<PaMedicamento*> comprobacion = sistema.buscarCompuesto(nombre);

            std::cout << "\nTras la prohibicion, medicamentos con \"" << nombre
                      << "\" en el nombre: " << comprobacion.size() << "\n";
        }

    } catch (const std::exception &e) {
        std::cerr << "[ERROR] " << e.what() << '\n';
        return 1;
    }

    return 0;
}