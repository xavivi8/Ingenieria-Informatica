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

        separador("Prueba II");

    } catch (const std::exception &e) {
        std::cerr << "[ERROR] " << e.what() << '\n';
        return 1;
    }

    return 0;
}