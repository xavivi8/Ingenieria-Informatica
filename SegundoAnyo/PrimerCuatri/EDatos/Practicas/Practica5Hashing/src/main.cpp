#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <unordered_set>

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

    struct HashResult  {
        std::string  functionName;
        unsigned int tableSize;
        float loadFactor;
        unsigned int maxCollisions;
        float avgCollisions;
        unsigned int numOver10Collisions;
    };

    HashResult results[2][3];

    // Creamos 6 objetos MediExpress: 3 funciones hash x 2 lambdas
    for (int l = 0; l < 2; ++l) {
        for (int h = 0; h < 3; ++h) {
            MediExpress tmp(fichMed,
                            fichLab,
                            fichFar,
                            LAMBDAS[l],
                            TIPOS[h]);

            results[l][h].functionName = NOMBRES_HASH[h];
            results[l][h].tableSize = tmp.getTamTabla();
            results[l][h].loadFactor = tmp.getFactorCarga();
            results[l][h].maxCollisions = tmp.getMaxColisiones();
            results[l][h].avgCollisions = tmp.getPromedioColisiones();
            results[l][h].numOver10Collisions = tmp.getNumMax10();
        }
    }

    // Elegimos automáticamente la mejor configuración (menor promedio de colisiones)
    int bestL = 0;
    int bestH = 0;
    float bestProm = results[0][0].avgCollisions;
    for (int l = 0; l < 2; ++l) {
        for (int h = 0; h < 3; ++h) {
            if (results[l][h].avgCollisions < bestProm) {
                bestProm = results[l][h].avgCollisions;
                bestL    = l;
                bestH    = h;
            }
        }
    }

    // Construir el sistema (carga CSV + construcción tabla hash) con la mejor config
    std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();
    MediExpress system(fichMed, fichLab, fichFar, LAMBDAS[bestL], TIPOS[bestH]);
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> durCarga = t1 - t0;

    // Mostrar por pantalla el estado interno de la tabla elegida
    system.mostrarEstadoTabla();

    // Lanzar la prueba de rendimiento (rellena m_tiempoHash / m_tiempoLista)
    system.pruebaRendimiento();

    // Tiempos de búsqueda hash vs lista
    double hashTime = system.getTiempoHash();
    double listTime = system.getTiempoLista();

    std::ofstream md("../analisis_Thash.md");
    if (!md.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir ../analisis_Thash.md para escritura\n";
    } else {
        md << "# Análisis de tablas de dispersión\n\n";
        md << "* *Francisco Javier Martín-Lunas Escobar*\n\n";

        // ---- Tablas de ajuste para λ=0.65 y λ=0.68 ----
        for (int l = 0; l < 2; ++l) {
            unsigned int tamTabla = results[l][0].tableSize;

            md << "## Tamaño de tabla: " << tamTabla << "\n";
            md << "| función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |\n";
            md << "|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|\n";

            for (int h = 0; h < 3; ++h) {
                const HashResult &r = results[l][h];
                md << "| " << r.functionName << "   |  "
                   << r.maxCollisions << "          |      "
                   << r.numOver10Collisions << "       |        "
                   << r.loadFactor << "       |        "
                   << r.avgCollisions << "         |\n";
            }
            md << "\n";

            md << "Número de inserciones con más de 10 colisiones para este tamaño de tabla:\n\n";
            for (int h = 0; h < 3; ++h) {
                const HashResult &r = results[l][h];
                md << "- " << r.functionName << ": " << r.numOver10Collisions << "\n";
            }
            md << "\n";
        }

        const HashResult &best = results[bestL][bestH];

        md << "## Justificación de la configuración elegida\n\n";
        md << "Hemos optado por la configuración de tabla con tamaño "
           << best.tableSize << ", aplicando la función "
           << best.functionName << " con λ objetivo "
           << LAMBDA_TEXT[bestL] << ".\n";
        md << "Es la que ofrece el menor promedio de colisiones ("
           << best.avgCollisions << ") y un máximo de "
           << best.maxCollisions << " colisiones en la inserción más costosa,\n";
        md << "además de un número de inserciones con más de 10 colisiones igual a "
           << best.numOver10Collisions << ", inferior al de otras alternativas.\n\n";

        md << "## Comparación de tiempos dados en milisegundos\n\n";
        md << "Tiempo en realizar las búsquedas en la Tabla Hash: " << hashTime  << " ms\n";
        md << "Tiempo en realizar las búsquedas en la Lista: "      << listTime  << " ms\n";
        md << "Tiempo aproximado de carga de datos y construcción de la tabla: "
           << durCarga.count() << " ms\n";

        md.close();
    }

    std::cout << "Informe generado en ../analisis_Thash.md\n";

    return system;
}

/**
 * @brief Lógica de la Prueba II Parte II (farmacias de Sevilla y MAGNESIO)
 */
void pruebaII_ParteII(MediExpress &system) {
    const int NUM_CLIENTES = 12;
    const int ID_OXIDO = 3640;   // ÓXIDO DE MAGNESIO

    std::vector<Farmacia*> sevillaPharmacies = system.buscarFarmacias("Sevilla");
    if (sevillaPharmacies.empty()) {
        std::cout << "\nNo se han encontrado farmacias en la provincia de Sevilla.\n";
    } else {
        for (std::size_t i = 0; i < sevillaPharmacies.size(); ++i) {
            Farmacia* f = sevillaPharmacies[i];
            if (f == 0) {
                continue;
            }

            std::cout << "\nFarmacia " << f->getCif() << " - " << f->getName() << " (" << f->getCity() << ", " << f->getProvince() << ")\n";

            // Estado inicial: mostrar medicamentos con "MAGNESIO" y su stock
            std::vector<PaMedicamento*> magIni = f->buscaMedicamNombre("MAGNESIO");
            std::cout << "  Estado inicial (medicamentos con 'MAGNESIO'):\n";
            if (magIni.empty()) {
                std::cout << "    (ninguno)\n";
            } else {
                for (std::size_t j = 0; j < magIni.size(); ++j) {
                    PaMedicamento* pm = magIni[j];
                    if (pm == 0) {
                        continue;
                    }
                    int stock = f->getStock(pm->getIdNum());
                    std::cout << "    - ID " << pm->getIdNum() << " | " << pm->getName() << " | stock = " << stock << "\n";
                }
            }

            // 12 clientes
            for (int cli = 0; cli < NUM_CLIENTES; ++cli) {
                std::cout << "  Cliente " << (cli + 1) << ": ";

                // Buscar un tipo de magnesio en stock
                std::vector<PaMedicamento*> mag = f->buscaMedicamNombre("MAGNESIO");
                PaMedicamento* chosen = 0;

                for (std::size_t j = 0; j < mag.size(); ++j) {
                    PaMedicamento* pm = mag[j];
                    if (pm == 0) {
                        continue;
                    }
                    int stock = f->getStock(pm->getIdNum());
                    if (stock > 0) {
                        chosen = pm;
                        break;
                    }
                }

                PaMedicamento* dummy = 0;

                if (chosen != 0) {
                    try {
                        f->comprarMedicam(chosen->getIdNum(), 1, dummy);
                        std::cout << "compra " << chosen->getName() << " (ID " << chosen->getIdNum() << ")\n";
                    } catch (const std::exception &e) {
                        std::cout << "no pudo comprar " << chosen->getName() << " (" << e.what() << ")\n";
                    }
                } else {
                    std::cout << "no encuentra ningun 'MAGNESIO' en stock. " << "Se pide OXIDO DE MAGNESIO (ID " << ID_OXIDO << ") al laboratorio.\n";

                    // Reponer 10 unidades de ÓXIDO DE MAGNESIO a la farmacia
                    system.suministrarFarmacia(*f, ID_OXIDO, 10);
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
                    if (pm == 0) {
                        continue;
                    }
                    int stock = f->getStock(pm->getIdNum());
                    std::cout << "    - ID " << pm->getIdNum() << " | " << pm->getName() << " | stock = " << stock << "\n";
                }
            }
        }
    }
}

/**
 * @brief Lógica de la Prueba II Parte III (farmacia de Jaén / Úbeda y ANTÍGENO OLIGOSACÁRIDO)
 */
void pruebaII_ParteIII(MediExpress &system) {
    std::vector<Farmacia*> jaenPharmacies = system.buscarFarmacias("Jaen");
    if (jaenPharmacies.empty()) {
        std::cout << "No se ha encontrado farmacia en la provincia de Jaen.\n";
    } else {
        Farmacia* ubedaPharmacy = jaenPharmacies[0];
        if (ubedaPharmacy == 0) {
            std::cout << "No se ha podido obtener la farmacia de Jaen.\n";
            return;
        }

        std::cout << "Farmacia de Jaen (Ubeda): " << ubedaPharmacy->getCif() << " - " << ubedaPharmacy->getName() << " (" << ubedaPharmacy->getCity() << ", " << ubedaPharmacy->getProvince() << ")\n";

        std::vector<PaMedicamento*> antigenos = system.buscarCompuesto("ANTIGENO OLIGOSACARIDO");

        std::cout << "\nSe han encontrado " << antigenos.size() << " medicamento(s) que contienen \"ANTIGENO OLIGOSACARIDO\" en su nombre.\n";

        std::cout << "\nStock inicial de 'ANTIGENO OLIGOSACARIDO' (todas las formas) en la farmacia de Ubeda:\n";
        if (antigenos.empty()) {
            std::cout << "  No se han encontrado medicamentos con ese nombre en el sistema.\n";
        } else {
            for (std::size_t i = 0; i < antigenos.size(); ++i) {
                PaMedicamento* pm = antigenos[i];
                if (pm == 0) {
                    continue;
                }
                int stock = ubedaPharmacy->getStock(pm->getIdNum());
                std::cout << "  - ID " << pm->getIdNum() << " | " << pm->getName() << " | stock = " << stock << "\n";
            }

            std::cout << "\nSe piden 10 unidades de todas las formas de 'ANTIGENO OLIGOSACARIDO'.\n";
            for (std::size_t i = 0; i < antigenos.size(); ++i) {
                PaMedicamento* pm = antigenos[i];
                if (pm == 0) {
                    continue;
                }
                system.suministrarFarmacia(*ubedaPharmacy, pm->getIdNum(), 10);
            }

            std::cout << "\nStock final tras el pedido en la farmacia de Ubeda:\n";
            for (std::size_t i = 0; i < antigenos.size(); ++i) {
                PaMedicamento* pm = antigenos[i];
                if (pm == 0) {
                    continue;
                }
                int stock = ubedaPharmacy->getStock(pm->getIdNum());
                std::cout << "  - ID " << pm->getIdNum() << " | " << pm->getName() << " | stock = " << stock << "\n";
            }
        }
    }
}

/**
 * @brief Lógica de la Prueba II Parte IV (prohibición de CIANURO y BISMUTO como palabra completa)
 */
void pruebaII_ParteIV(MediExpress &system) {
    const std::string forbidden_names[] = { "CIANURO", "BISMUTO" };
    const int NUM_FORBBIDEN = 2;

    // 1) Buscar, mostrar y eliminar
    for (int i = 0; i < NUM_FORBBIDEN; ++i) {
        const std::string &baseName = forbidden_names[i];

        // Queremos que sea "palabra": patrones con espacios alrededor
        const std::string patterns[3] = {
            baseName + " ",        // ...CIANURO + espacio
            " " + baseName,        // espacio + CIANURO...
            " " + baseName + " "   // espacio + CIANURO + espacio
        };

        std::vector<PaMedicamento*> encontrados;
        std::unordered_set<PaMedicamento*> seen;

        // Unimos resultados de las tres búsquedas evitando duplicados
        for (int p = 0; p < 3; ++p) {
            std::vector<PaMedicamento*> parciales = system.buscarCompuesto(patterns[p]);
            for (std::size_t j = 0; j < parciales.size(); ++j) {
                PaMedicamento* pm = parciales[j];
                if (pm == 0) {
                    continue;
                }
                if (!seen.count(pm)) {
                    seen.insert(pm);
                    encontrados.push_back(pm);
                }
            }
        }

        std::cout << "\nMedicamentos que contienen la palabra \"" << baseName
                  << "\" en su nombre: " << encontrados.size() << "\n";

        if (encontrados.empty()) {
            std::cout << "  (ninguno)\n";
            continue;
        }

        // Mostrar y eliminar
        for (std::size_t j = 0; j < encontrados.size(); ++j) {
            PaMedicamento* pm = encontrados[j];
            if (pm == 0) {
                continue;
            }

            int id = pm->getIdNum();
            std::cout << "  - Eliminando ID " << id << " | " << pm->getName() << " ... ";

            bool ok = system.eliminarMedicamento(id);
            if (ok) {
                std::cout << "OK\n";
            } else {
                std::cout << "ya estaba eliminado o no se encontraba.\n";
            }
        }
    }

    // 2) Comprobación: intentar buscarlos de nuevo con la misma lógica de "palabra"
    for (int i = 0; i < NUM_FORBBIDEN; ++i) {
        const std::string &baseName = forbidden_names[i];

        const std::string patterns[3] = {
            baseName + " ",
            " " + baseName,
            " " + baseName + " "
        };

        std::vector<PaMedicamento*> comprobacion;
        std::unordered_set<PaMedicamento*> seenCheck;

        for (int p = 0; p < 3; ++p) {
            std::vector<PaMedicamento*> parciales = system.buscarCompuesto(patterns[p]);
            for (std::size_t j = 0; j < parciales.size(); ++j) {
                PaMedicamento* pm = parciales[j];
                if (pm == 0) {
                    continue;
                }
                if (!seenCheck.count(pm)) {
                    seenCheck.insert(pm);
                    comprobacion.push_back(pm);
                }
            }
        }

        std::cout << "\nTras la prohibicion, medicamentos con la palabra \"" << baseName
                  << "\" en el nombre: " << comprobacion.size() << "\n";
    }
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
        MediExpress system  = ejecutarPruebaI(FICH_MEDICAMENTOS, FICH_LABORATORIOS, FICH_FARMACIAS);

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
            std::vector<PaMedicamento*> meds = system.buscarCompuesto(q);

            std::cout << "\nBusqueda por nombre: \"" << q << "\"\n";
            std::cout << "  Se han encontrado " << meds.size() << " medicamento(s).\n";
            if (meds.empty()) {
                std::cout << "  (sin resultados)\n";
            } else {
                for (std::size_t j = 0; j < meds.size(); ++j) {
                    PaMedicamento* pm = meds[j];
                    if (pm == 0) {
                        continue;
                    }
                    std::cout << "  - ID " << pm->getIdNum() << " | "   << pm->getName() << "\n";
                }
            }
        }

        separador("Prueba II Parte II");
        pruebaII_ParteII(system);

        separador("Prueba II Parte III");
        pruebaII_ParteIII(system);

        separador("Prueba II Parte IV");
        pruebaII_ParteIV(system);

    } catch (const std::exception &e) {
        std::cerr << "[ERROR] " << e.what() << '\n';
        return 1;
    }

    return 0;
}