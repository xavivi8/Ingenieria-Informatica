#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

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

        MediExpress sistema(FICH_MEDICAMENTOS, FICH_LABORATORIOS, FICH_FARMACIAS);

        /**
         * ===========================================================
         * 1) Magnesio en farmacias de la provincia de Sevilla
         * ===========================================================
         */
        separador("1) Compras de magnesio en farmacias de la provincia de Sevilla");

        const int ID_OXIDO     = 3640; // ÓXIDO DE MAGNESIO
        const int ID_CARBONATO = 3632; // CARBONATO DE MAGNESIO
        const int ID_CLORURO   = 3633; // CLORURO DE MAGNESIO
        const int NUM_CLIENTES = 12;

        std::vector<Farmacia*> farSevilla = sistema.buscarFarmacias("Sevilla");

        if (farSevilla.empty()) {
            std::cout << "No se han encontrado farmacias en la provincia de Sevilla.\n";
        }

        int count = 1;
        for (std::size_t i = 0; i < farSevilla.size(); ++i) {
            Farmacia* f = farSevilla[i];

            std::cout << " - " << count << " - Farmacia " << f->getCif()
                      << " - " << f->getName()
                      << " (" << f->getCity() << ", " << f->getProvince() << ")\n";
            ++count;

            int vendidosOxido     = 0;
            int vendidosCarbonato = 0;
            int vendidosCloruro   = 0;

            // 0 = Óxido, 1 = Carbonato, 2 = Cloruro, 3 = ninguno
            int etapa = 0;

            for (int cli = 0; cli < NUM_CLIENTES; ++cli) {
                PaMedicamento* dummy = 0;

                int idActual = 0;
                std::string nombreCorto;

                if (etapa == 0) {
                    idActual    = ID_OXIDO;
                    nombreCorto = "OXIDO de magnesio";
                } else if (etapa == 1) {
                    idActual    = ID_CARBONATO;
                    nombreCorto = "CARBONATO de magnesio";
                } else if (etapa == 2) {
                    idActual    = ID_CLORURO;
                    nombreCorto = "CLORURO de magnesio";
                } else {
                    std::cout << "  Cliente " << (cli + 1)
                              << ": ya no quedan tipos de magnesio disponibles.\n";
                    continue;
                }

                try {
                    // El cliente compra 1 unidad del medicamento "actual"
                    f->comprarMedicam(idActual, 1, dummy);

                    if (etapa == 0)      ++vendidosOxido;
                    else if (etapa == 1) ++vendidosCarbonato;
                    else                 ++vendidosCloruro;

                    std::cout << "  Cliente " << (cli + 1)
                              << " compro " << nombreCorto
                              << " (ID " << idActual << ")\n";

                    // ¿Este cliente ha dejado el stock a 0?
                    int stockDespues = f->getStock(idActual);
                    if (stockDespues == 0) {
                        std::cout << "    [INFO] El cliente " << (cli + 1)
                                  << " ha agotado el stock de " << nombreCorto
                                  << ". Se reponen 10 unidades.\n";

                        // Reponer 10 unidades del mismo medicamento
                        sistema.suministrarFarmacia(*f, idActual, 10);

                        // A partir de ahora, pasar al siguiente tipo
                        if (etapa < 2) {
                            ++etapa;
                            std::cout << "    [INFO] A partir de ahora los siguientes "
                                      << "clientes compraran el siguiente tipo de magnesio.\n";
                        }
                    }

                } catch (const std::exception& e) {
                    std::cout << "  Cliente " << (cli + 1)
                              << ": no pudo comprar " << nombreCorto
                              << " (" << e.what() << ")\n";

                    // Si falla (por ejemplo, sin stock), avanzamos al siguiente tipo
                    if (etapa < 2) {
                        ++etapa;
                        std::cout << "    [INFO] Se pasa al siguiente tipo de magnesio "
                                  << "para los siguientes clientes.\n";
                    }
                }
            }

            int stockOxido     = f->getStock(ID_OXIDO);
            int stockCarbonato = f->getStock(ID_CARBONATO);
            int stockCloruro   = f->getStock(ID_CLORURO);

            std::cout << "  Ventas realizadas: "
                      << "Oxido("      << ID_OXIDO     << ")=" << vendidosOxido
                      << ", Carbonato(" << ID_CARBONATO << ")=" << vendidosCarbonato
                      << ", Cloruro("   << ID_CLORURO   << ")=" << vendidosCloruro << '\n';

            std::cout << "  Stock actual: "
                      << "Oxido="      << stockOxido
                      << ", Carbonato=" << stockCarbonato
                      << ", Cloruro="   << stockCloruro << "\n";
            std::cout << "===================================================================================" << std::endl;
        }

        /**
         * ===========================================================
         * 2) Farmacias de Madrid con medicamentos que contienen "VIRUS"
         * ===========================================================
         */
        separador("2) Farmacias de la provincia de Madrid con medicamentos que contienen \"VIRUS\"");

        std::vector<Farmacia*> farMadrid = sistema.buscarFarmacias("Madrid");
        std::vector<Farmacia*> farMadridConVirus;

        for (std::size_t i = 0; i < farMadrid.size(); ++i) {
            Farmacia* f = farMadrid[i];
            std::vector<PaMedicamento*> conVirus = f->buscaMedicamNombre("VIRUS");
            if (!conVirus.empty()) {
                farMadridConVirus.push_back(f);
            }
        }

        std::cout << "Total de farmacias de la provincia de Madrid con algun medicamento que contiene \"VIRUS\" en su nombre: " << farMadridConVirus.size() << "\n";

        for (std::size_t i = 0; i < farMadridConVirus.size(); ++i) {
            Farmacia* f = farMadridConVirus[i];
            std::cout << "  - " << f->getCif() << " | " << f->getName() << " | " << f->getCity() << " (" << f->getProvince() << ")\n";
        }

        /**
         * ===========================================================
         * 3) Eliminar medicamento con cianuro y comprobar
         * ===========================================================
         */
        separador("3) Eliminacion de medicamentos con cianuro");

        const int ID_CIANURO = 9355;
        const int ID_OTRO    = 3244;

        std::cout << "Eliminando medicamento " << ID_CIANURO << "...\n";
        bool borradoCianuro = sistema.eliminarMedicamento(ID_CIANURO);
        std::cout << "  Resultado eliminar(" << ID_CIANURO << "): " << (borradoCianuro ? "Eliminado" : "No se encontraba") << '\n';

        PaMedicamento* comprobacion = sistema.buscarCompuesto(ID_CIANURO);
        std::cout << "  Comprobacion de busqueda del " << ID_CIANURO << ": " << (comprobacion ? "AUN EXISTE (ERROR)" : "No se encuentra en el sistema") << "\n\n";

        std::cout << "Probando a eliminar el medicamento " << ID_OTRO << "...\n";
        bool borradoOtro = sistema.eliminarMedicamento(ID_OTRO);
        std::cout << "  Resultado eliminar(" << ID_OTRO << "): " << (borradoOtro ? "Eliminado" : "No se encontraba") << '\n';

    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    return 0;
}
