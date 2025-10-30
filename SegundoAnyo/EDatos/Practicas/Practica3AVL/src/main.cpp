#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
        clock_t t_bus_ini = clock();

        unsigned int encontradas = 0;
        unsigned int no_encontradas = 0;

        for (unsigned int i = 0; i < cifs500.len(); ++i) {
            Farmacia clave(cifs500[i], "", "", "", "", "", nullptr);
            auto *pf = arbolFarmacias.buscaIt(clave);
            if (pf) ++encontradas;
            else    ++no_encontradas;
        }

        double t_bus_secs = (clock() - t_bus_ini) / (double)CLOCKS_PER_SEC;

        std::cout << "Buscadas " << cifs500.len() << " farmacias por CIF en el AVL.\n";
        std::cout << "Encontradas: " << encontradas << " | No encontradas: " << no_encontradas << "\n";
        std::cout << "Tiempo total de busqueda: " << t_bus_secs << " segs.\n";

        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "----------------------------------------------- " << "Prueba II" << " -----------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;

        

    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    return 0;
}
