#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

#include "../include/VDinamico.h"
#include "../include/ListaEnlazada.h"
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

void loadPharmaciesIntoAvl(const std::string &csvPath, Avl<Farmacia> &tree, MediExpress* medi = nullptr) {
    std::ifstream is(csvPath);
    if (!is.good()){
        std::cout << "Error de apertura en archivo: " << csvPath << "\n";
        return;
    }

    clock_t t_ini = clock();

    std::string row;
    unsigned int count = 0;
    bool firstLine = true;

    while (std::getline(is, row)){
        if (row.empty()) continue;

        if (firstLine && row.size() >= 3 && (unsigned char)row[0]==0xEF && (unsigned char)row[1]==0xBB && (unsigned char)row[2]==0xBF){
            row.erase(0,3);
        }
        firstLine = false;

        std::stringstream columns(row);
        std::string cif, province, city, name, address, postalCode;

        std::getline(columns, cif, ';');
        std::getline(columns, province, ';');
        std::getline(columns, city, ';');
        std::getline(columns, name, ';');
        std::getline(columns, address, ';');
        std::getline(columns, postalCode, ';');

        if (!postalCode.empty() && postalCode.back() == '\r') postalCode.pop_back();

        if (utils::lowerCopy(cif) == "cif") continue;

        if (cif.empty()) continue;

        Farmacia f(cif, province, city, name, address, postalCode, medi);
        tree.inserta(f);
        ++count;
    }
    is.close();

    std::cout << "Cargadas en AVL: " << count << " farmacias. Tiempo: " << ((clock() - t_ini) / (float)CLOCKS_PER_SEC) << " segs.\n";
}

VDinamico<Farmacia> buildVectorFromAvl(Avl<Farmacia> &tree) {
    VDinamico<Farmacia> out;
    VDinamico<Farmacia*> ptrs = tree.recorreInorden();

    for (unsigned int i = 0; i < ptrs.len(); ++i){
        Farmacia* pf = ptrs[i];
        if (pf) out.insert(*pf);
    }
    return out;
}

VDinamico<std::string> loadFirstCifsFromCsv(const std::string &csvPath, unsigned int maxCount = 500) {
    VDinamico<std::string> cifs;

    std::ifstream is(csvPath);
    if (!is.good()){
        std::cout << "Error de apertura en archivo: " << csvPath << "\n";
        return cifs;
    }

    std::string row;
    bool firstLine = true;
    unsigned int count = 0;

    while (count < maxCount && std::getline(is, row)){
        if (row.empty()) continue;

        if (firstLine && row.size() >= 3 && (unsigned char)row[0]==0xEF && (unsigned char)row[1]==0xBB && (unsigned char)row[2]==0xBF){
            row.erase(0,3);
        }
        firstLine = false;

        std::stringstream columns(row);
        std::string cif;
        if (!std::getline(columns, cif, ';')) continue;

        if (utils::lowerCopy(cif) == "cif") continue;

        if (!cif.empty()){
            cifs.insert(cif);
            ++count;
        }
    }
    return cifs;
}

VDinamico<std::string> loadAllCifsFromCsv(const std::string &csvPath) {
    VDinamico<std::string> cifs;
    std::ifstream ifs(csvPath);
    if (!ifs.good()){
        std::cout << "Error de apertura en archivo: " << csvPath << "\n";
        return cifs;
    }
    std::string row;
    bool firstLine = true;

    while (std::getline(ifs, row)){
        if (row.empty()) continue;

        if (firstLine && row.size() >= 3 &&
            (unsigned char)row[0]==0xEF && (unsigned char)row[1]==0xBB && (unsigned char)row[2]==0xBF){
            row.erase(0,3);
        }
        firstLine = false;

        std::stringstream cols(row);
        std::string cif;
        if (!std::getline(cols, cif, ';')) continue;

        if (utils::lowerCopy(cif) == "cif") continue;

        if (!cif.empty()) cifs.insert(cif);
    }
    return cifs;
}

VDinamico<int> loadMedIdsFromCsv(const std::string &csvPath) {
    VDinamico<int> ids;
    std::ifstream ifs(csvPath);
    if (!ifs.good()){
        std::cout << "Error de apertura en archivo: " << csvPath << "\n";
        return ids;
    }
    std::string row;
    bool firstLine = true;

    while (std::getline(ifs, row)){
        if (row.empty()) continue;

        if (firstLine && row.size() >= 3 &&
            (unsigned char)row[0]==0xEF && (unsigned char)row[1]==0xBB && (unsigned char)row[2]==0xBF){
            row.erase(0,3);
        }
        firstLine = false;

        std::stringstream cols(row);
        std::string idNumStr;
        if (!std::getline(cols, idNumStr, ';')) continue;

        if (utils::lowerCopy(idNumStr) == "id_number") continue;

        if (!idNumStr.empty()) ids.insert(std::stoi(idNumStr));
    }
    return ids;
}


/**
 * @author Francisco Javier Martín-Lunas Escobar fjme0008@red.ujaen.es
 */
int main(int argc, const char *argv[]) {
    try {
        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "----------------------------------------------- " << "Prueba I" << " -----------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;
        
        Avl<Farmacia> arbolFarmacias;
        loadPharmaciesIntoAvl("../data/farmacias.csv", arbolFarmacias);

        VDinamico<Farmacia> vFarmacias = buildVectorFromAvl(arbolFarmacias);

        std::cout << "AVL nodos: " << arbolFarmacias.getSize() << "\n";
        std::cout << "Vector elems: " << vFarmacias.len() << "\n";

        separador("CIF vector aux");

        VDinamico<std::string> cifs500 = loadFirstCifsFromCsv("../data/farmacias.csv", 500);
        std::cout << "CIFs guardados en vector auxiliar: " << cifs500.len() << "\n";

        if (cifs500.len() > 0) {
            std::cout << "[ ";
            for (unsigned int i = 0; i < (cifs500.len() - 1); ++i) {
                std::cout << cifs500[i] << " ";
            }
            // imprime el último fuera del bucle para no dejar un separador colgando
            std::cout << cifs500[cifs500.len() - 1] << " ]\n";
        }

        separador("Buscar cif avl y medir tiempo");

        // (opcional) warm-up para estabilizar caché
        for (unsigned int i = 0; i < cifs500.len(); ++i) {
            Farmacia clave(cifs500[i], "", "", "", "", "", nullptr);
            (void)arbolFarmacias.buscaIt(clave);
        }

        auto t0_avl = std::chrono::steady_clock::now();

        unsigned int encontradas = 0;
        unsigned int no_encontradas = 0;

        for (unsigned int i = 0; i < cifs500.len(); ++i) {
            Farmacia clave(cifs500[i], "", "", "", "", "", nullptr);
            auto *pf = arbolFarmacias.buscaIt(clave);
            if (pf) ++encontradas;
            else    ++no_encontradas;
        }

        auto t1_avl = std::chrono::steady_clock::now();
        auto total_us_avl = std::chrono::duration_cast<std::chrono::microseconds>(t1_avl - t0_avl).count();
        double avg_ns_avl = (total_us_avl * 1000.0) / (cifs500.len() ? cifs500.len() : 1);

        std::cout << "Buscadas " << cifs500.len() << " farmacias por CIF en el AVL.\n";
        std::cout << "Encontradas: " << encontradas << " | No encontradas: " << no_encontradas << "\n";
        std::cout << "Tiempo total: " << total_us_avl << " microS (" << (total_us_avl/1000.0) << " ms) | ~" << avg_ns_avl << " ns/busqueda\n";


        separador("Busqueda lineal eb VDinamico");

        auto eq = [](const Farmacia& a, const Farmacia& b){
            return !(a < b) && !(b < a);
        };

        // warm-up opcional para estabilizar caché
        for (unsigned int i = 0; i < cifs500.len(); ++i) {
            Farmacia clave(cifs500[i], "", "", "", "", "", nullptr);
            for (unsigned int j = 0; j < vFarmacias.len(); ++j) {
                if (eq(clave, vFarmacias[j])) break;
            }
        }

        auto t0 = std::chrono::steady_clock::now();

        unsigned int encontradasVec = 0;
        unsigned int noEncontradasVec = 0;

        for (unsigned int i = 0; i < cifs500.len(); ++i) {
            Farmacia clave(cifs500[i], "", "", "", "", "", nullptr);
            bool found = false;

            for (unsigned int j = 0; j < vFarmacias.len(); ++j) {
                if (eq(clave, vFarmacias[j])) { found = true; break; }
            }

            if (found) ++encontradasVec;
            else       ++noEncontradasVec;
        }

        auto t1 = std::chrono::steady_clock::now();
        auto total_us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        double avg_ns = (total_us * 1000.0) / (cifs500.len() ? cifs500.len() : 1);

        std::cout << "Busqueda lineal en vector de " << cifs500.len() << " CIFs\n";
        std::cout << "Encontradas: " << encontradasVec << " | No encontradas: " << noEncontradasVec << "\n";
        std::cout << "Tiempo total: " << total_us << " microS (" << (total_us/1000.0) << " ms) | ~" << avg_ns << " ns/busqueda\n";

        separador("Comparativa AVL vs Vector");

        std::cout.setf(std::ios::fixed);
        std::cout.precision(3);

        std::cout << "AVL:           " << total_us_avl << " microS  (" << avg_ns_avl << " ns/busqueda)\n";
        std::cout << "Vector lineal: " << total_us      << " microS  (" << avg_ns      << " ns/busqueda)\n";

        // Determinar si mejora con AVL
        if (total_us_avl == 0 && total_us == 0) {
            std::cout << "Los tiempos son 0 microS (dataset muy pequenyo o medidas demasiado rapidas). Repite las busquedas varias veces para medir mejor.\n";
        } else if (total_us_avl == 0 && total_us > 0) {
            std::cout << "El AVL ha sido extremadamente rapido (masOmenos0 microS). Mejora clara frente al vector lineal.\n";
        } else if (total_us == 0 && total_us_avl > 0) {
            std::cout << "La busqueda lineal ha sido masOmenos0 µs y el AVL no: en esta medida puntual, no mejora.\n";
        } else {
            const double avl   = static_cast<double>(total_us_avl);
            const double vec   = static_cast<double>(total_us);
            if (avl < vec) {
                double speedup = vec / avl;
                double saving  = (1.0 - avl/vec) * 100.0;
                std::cout << "Mejora: el AVL es " << speedup << " mas rapido (" << saving << "% menos tiempo total).\n";
            } else if (avl > vec) {
                double slowdown = avl / vec;
                double extra    = (avl/vec - 1.0) * 100.0;
                std::cout << "Peor: el AVL es " << slowdown << "× mas lento (" << extra << "% mas tiempo).\n";
            } else {
                std::cout << "= Empate: mismos tiempos totales.\n";
            }
        }

        separador("Altura del AVL");
        std::cout << "Altura del arbol AVL con " << arbolFarmacias.altura() << " farmacias: " << arbolFarmacias.getSize() << "\n";

        separador("Inorden: primeras 100 farmacias");

        VDinamico<Farmacia*> inord = arbolFarmacias.recorreInorden();
        unsigned int toShow = std::min(100u, inord.len());

        for (unsigned int i = 0; i < toShow; ++i) {
            if (inord[i]) {
                std::cout << (i + 1) << ") " << *inord[i] << "\n"; 
            }
        }

        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "----------------------------------------------- " << "Prueba II" << " -----------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;

        MediExpress me("../data/pa_medicamentos.csv", "../data/laboratorios.csv", "../data/farmacias.csv");

        // Releer farmacias -> vector de CIF (sin crear copias de Farmacia: solo strings)
        VDinamico<std::string> allCifs = loadAllCifsFromCsv("../data/farmacias.csv");
        std::cout << "CIFs leidos: " << allCifs.len() << "\n";

        // Leer IDs de medicamentos en el orden del CSV
        VDinamico<int> medIds = loadMedIdsFromCsv("../data/pa_medicamentos.csv");
        std::cout << "IDs de medicamentos cargados: " << medIds.len() << "\n";

        // Enlace: para cada farmacia (encontrada por puntero), asignar 100 meds consecutivos, ciclando
        unsigned int pharmaciesLinked = 0;
        unsigned long long totalLinks = 0;

        for (unsigned int p = 0; p < allCifs.len(); ++p) {
            // Buscar puntero a Farmacia dentro del AVL de MediExpress (NO crea copias)
            Farmacia* pf = me.buscarFarmacia(allCifs[p]);
            if (!pf) continue;

            if (medIds.len() == 0) break; // nada que asignar

            // Bloque de 100 medicamentos por farmacia, con wrap-around
            for (unsigned int k = 0; k < 100; ++k) {
                unsigned int midx = (p * 100u + k) % medIds.len(); // cíclico
                int idNum = medIds[midx];

                // Suministra por ID (internamente busca el puntero real al medicamento y lo dispensa a la Farmacia)
                me.suministrarFarmacia(pf, idNum);
                ++totalLinks;
            }
            ++pharmaciesLinked;
        }

        std::cout << "Farmacias enlazadas: " << pharmaciesLinked
                << " | Enlaces farmacia-medicamento realizados: " << totalLinks << "\n";
        std::cout << "Cada farmacia recibio 100 medicamentos consecutivos; se ciclaron cuando fue necesario.\n";

        separador("Parte 1 del 5");
        
        VDinamico<std::string> cifBuffer;
        const char* cifList[] = {
            "37656422V","46316032N","77092934Q","33961602D","B62351861","B62351861",
            "B65828113","46138599R","35069965W","37579913Y","37682300C","37643742X",
            "46112335A","47980171D","38116138D","46315600V","37640233C","37931842N",
            "33964303L","35022080A","B66046640","E66748344","47640201W","B66621954",
            "46121385Z","X6806622W","46046390E"
        };
        for (const char* s : cifList) cifBuffer.insert(std::string(s));

        std::cout << "Buffer CIFs creado. Tamanyo: " << cifBuffer.len() << "\n";

        separador("Parte 2 del 5");

        
        const int MAGNESIO_ID = 3640;
        unsigned int foundPharm = 0, notFoundPharm = 0, alreadyHad = 0, ordered = 0;

        for (unsigned int i = 0; i < cifBuffer.len(); ++i) {
            const std::string &cif = cifBuffer[i];

            Farmacia* pf = me.buscarFarmacia(cif);
            if (!pf) {
                ++notFoundPharm;
                std::cout << "No encontrada farmacia con CIF: " << cif << "\n";
                continue;
            }
            ++foundPharm;

            if (pf->buscaMedicam(MAGNESIO_ID) != nullptr) {
                ++alreadyHad;
                std::cout << "Farmacia " << cif << " ya dispensa ID " << MAGNESIO_ID << ".\n";
                continue;
            }

            try {
                me.suministrarFarmacia(pf, MAGNESIO_ID);
                ++ordered;
                std::cout << "Pedido realizado a farmacia " << cif << " para ID " << MAGNESIO_ID << ".\n";
            } catch (const std::exception &ex) {
                std::cout << "[ERROR] No se pudo suministrar a " << cif << ": " << ex.what() << "\n";
            }
        }

        std::cout << "Resumen buffer: encontradas=" << foundPharm
                << " no_encontradas=" << notFoundPharm
                << " ya_lo_tenian=" << alreadyHad
                << " pedidos_realizados=" << ordered << "\n";

        separador("Parte 3 del 5");


        VDinamico<Laboratorio*> labsMag = me.buscarLabs("magnesio");
        std::cout << "Laboratorios que trabajan algun \"MAGNESIO\": " << labsMag.len() << "\n";

        unsigned int showLabs = std::min(15u, labsMag.len());
        for (unsigned int i = 0; i < showLabs; ++i) {
            if (labsMag[i]) {
                std::cout << " - " << *labsMag[i] << "\n";
            }
        }

    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    return 0;
}
