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
 * @author
 *  Francisco Javier Martín-Lunas Escobar  (fjme0008@red.ujaen.es)
 */
int main(int argc, const char *argv[]) {
    try {
        const std::string FICH_FARMACIAS    = "../data/farmacias.csv";
        const std::string FICH_LABORATORIOS = "../data/laboratorios.csv";
        const std::string FICH_MEDICAMENTOS = "../data/pa_medicamentos.csv";

        separador("Prueba I");
        // 1) Construir el sistema (carga CSV + construcción tabla hash)
        auto t0 = std::chrono::high_resolution_clock::now();
        MediExpress sistema(FICH_MEDICAMENTOS, FICH_LABORATORIOS, FICH_FARMACIAS);
        auto t1 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> durCarga = t1 - t0;

        // Mostrar por pantalla el estado interno de la tabla, tal y como pide el enunciado
        sistema.mostrarEstadoTabla();

        // 2) Lanzar la prueba de rendimiento (rellena m_tiempoHash / m_tiempoLista)
        sistema.pruebaRendimiento();

        // 3) Obtener métricas de la tabla hash mediante getters
        unsigned int tam = sistema.getTamTabla();
        unsigned int nElems = sistema.getNumElementos();  // si quieres usarlo luego
        float lambda  = sistema.getFactorCarga();
        unsigned int maxCol = sistema.getMaxColisiones();
        unsigned int num10 = sistema.getNumMax10();
        float promCol = sistema.getPromedioColisiones();
        double tHash = sistema.getTiempoHash();
        double tList = sistema.getTiempoLista();

        // 4) Escribir el informe en analisis_Thash.md
        std::ofstream md("../analisis_Thash.md");
        if (!md.is_open()) {
            std::cerr << "[ERROR] No se pudo abrir ../analisis_Thash.md para escritura\n";
            return 1;
        }

        md << "# Análisis de tablas de dispersión\n\n";
        md << "* *Francisco Javier Martín-Lunas Escobar*\n\n";

        // ===================== Tabla tamaño actual =====================
        md << "## Tamaño de tabla: " << tam << "\n\n";   // <-- línea en blanco tras el heading
        md << "| función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |\n";
        md << "|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|\n";
        md << "| configuración actual | "
           << maxCol  << " | "
           << num10   << " | "
           << lambda  << " | "
           << promCol << " |\n";
        md << "| texto   | valor | valor | valor | valor |\n\n";  // <-- línea en blanco tras la tabla

        // ===================== Tabla para otra configuración (plantilla) =====================
        md << "## Tamaño de tabla: yy\n\n";  // heading + línea en blanco
        md << "| función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |\n";
        md << "|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|\n";
        md << "| texto   | valor | valor | valor | valor |\n";
        md << "| texto   | valor | valor | valor | valor |\n\n";

        // ===================== Justificación =====================
        md << "## Justificación de la configuración elegida\n\n"; // heading + blanco
        md << "Hemos optado por ... (rellenar manualmente justificando en base a los valores de la tabla).\n\n";

        // ===================== Comparación de tiempos =====================
        md << "## Comparación de tiempos dados en milisegundos\n\n"; // heading + blanco
        md << "Tiempo en realizar las búsquedas en la Tabla Hash: " << tHash  << " ms\n";
        md << "Tiempo en realizar las búsquedas en la Lista: "      << tList  << " ms\n";
        md << "Tiempo aproximado de carga de datos y construcción de la tabla: "
           << durCarga.count() << " ms\n";

        md.close();

        std::cout << "Informe generado en ../analisis_Thash.md\n";

        separador("Prueba II Parte I");
        //TODO: hacer busqueda con intersección para que encuentre exactamente el medicamento, por ejemplo, LIDOCAINA 
        //TODO    HIDROCLORURO y no LIDOCAINA HIDROCLORURO xxxxxxx
        
        //TODO: en todas las busquedas de medicamentos hay que hacer la intersección para por ejemplo que si quiero MAGNESIO me de
        //TODO  todos los medicamentos que contenga MAGNESIO en el nombre 
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

            std::cout << "\nTras la prohibicion, medicamentos con \"" << nombre <<"\" en el nombre: " << comprobacion.size() << "\n";
        }

    } catch (const std::exception &e) {
        std::cerr << "[ERROR] " << e.what() << '\n';
        return 1;
    }

    return 0;
}