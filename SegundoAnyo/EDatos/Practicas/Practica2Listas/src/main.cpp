#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../include/VDinamico.h"
#include "../include/PaMedicamento.h"
// Preguntar si se pueden usar "#include <vector>"

/**
 * @brief Carga los medicamentos desde un archivo CSV
 * @param csvPath Ruta del archivo CSV
 * @return Devuelve un vector dinamico con los medicamentos cargados desde el archivo CSV
 */
VDinamico<PaMedicamento> loadMedicinesFromCsv(const std::string &csvPath){

    std::ifstream is;
    std::stringstream columns;
    std::string row;
    int count = 0;
    std::string idNum = "";
    std::string idAlpha = "";
    std::string name = "";

    VDinamico<PaMedicamento> aux;

    is.open(csvPath); // carpeta de proyecto
    if (is.good()){

        clock_t t_ini = clock();

        while (getline(is, row)){

            // ¿Se ha leído una nueva fila?
            if (row != ""){

                columns.str(row);

                // formato de fila: id_number;id_alpha;nombre;

                getline(columns, idNum, ';'); // leemos caracteres hasta encontrar y omitir ';'
                getline(columns, idAlpha, ';');
                getline(columns, name, ';');

                row = "";
                columns.clear();

                /*std::cout << ++count
                          << " Medicamento: ( Id_number=" << idNum
                          << " id_alpha=" << idAlpha << " Nombre=" << name
                          << ")" << std::endl;*/

                PaMedicamento med(std::stoi(idNum), idAlpha, name);
                aux.insert(med);
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float)CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    return aux;
};

/**
 * @brief Muestra los primeros 50 elementos del vector de medicamentos
 * @param medicines Vector dinamico de medicamentos
 */
void showFirst50(VDinamico<PaMedicamento> &medicines){
    unsigned int limit = 50;

    if (limit > medicines.size()){
        limit = medicines.size();
        std::cout << "Primeros " << limit << " elementos: " << std::endl;
    } else {
        std::cout << "Primeros 50 elementos: " << std::endl;
    }

    for (unsigned int i = 0; i < limit; ++i){
        std::cout << "Medicamento: Id Num: " << medicines[i].getIdNum() << " - Id Alpha: " << medicines[i].getIdAlpha()
                  << " - Nombre: " << medicines[i].getName() << std::endl;
    }
};

/**
 * @brief Busca un grupo de medicamentos por sus ids
 * @param medicines Vector dinamico de medicamentos
 * @param ids Vector dinamico de ids a buscar
 * @post Muestra por pantalla la posicion y los datos de los medicamentos encontrados
 */
void searchGroupOfMedicinesByIds(VDinamico<PaMedicamento> &medicines, VDinamico<int> &ids){
    for (unsigned int i = 0; i < ids.size(); ++i){
        int id = ids[i];
        PaMedicamento medicineAux(id, "", "");

        unsigned int pos = medicines.binarySearch(medicineAux);

        if (pos != UINT_MAX){
            std::cout << "Posicion en el vector: " << pos << "\n"
                      << " Medicamento: ( IdNum=" << medicines[pos].getIdNum()
                      << " IdAlpha=" << medicines[pos].getIdAlpha()
                      << " Nombre=" << medicines[pos].getName()
                      << ")" << std::endl;
        } else{
            std::cout << "No se encontro medicamento cuyo id es: " << id << std::endl;
        }
    }
};

/**
 * @brief Busca medicamentos que contengan un compuesto en su nombre
 * @param comp Compuesto a buscar
 * @param vMedicamentos Vector dinamico de medicamentos
 * @return Devuelve un vector dinamico de punteros a los medicamentos que contienen el compuesto en su nombre
 */
VDinamico<PaMedicamento *> buscarCompuesto(const std::string &comp, VDinamico<PaMedicamento> &vMedicamentos){
    VDinamico<PaMedicamento *> result;

    for (unsigned int i = 0; i < vMedicamentos.size(); ++i){
        if (vMedicamentos[i].getName().find(comp) != std::string::npos){
            result.insert(&vMedicamentos[i]);
        }
    }

    return result;
};

/**
 * @author Francisco Javier Martín-Lunas Escobar fjme0008@red.ujaen.es
 */
int main(int argc, const char *argv[]) {

    try {
        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "-------------------------------------------------- Inserto los datos --------------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;

        VDinamico<PaMedicamento> medicines = loadMedicinesFromCsv("../pa_medicamentos.csv");

        for (unsigned int i = 0; i < medicines.size(); i++){
            std::cout << i + 1 << " Medicamento: ( IdNum=" << medicines[i].getIdNum()
                      << " IdAlpha=" << medicines[i].getIdAlpha()
                      << " Nombre=" << medicines[i].getName()
                      << ")" << std::endl;
        }

        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "----------------------------------------------- Muestro los 50 primeros -----------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;

        showFirst50(medicines);

        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "------------------------------------------------------- Ordeno --------------------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;

        medicines.sort();

        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "----------------------------------------------- Muestro los 50 primeros -----------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;

        showFirst50(medicines);

        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "---------------------------------------------------- Buscar los ids ---------------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;

        VDinamico<int> ids;
        ids.insert(350);
        ids.insert(409);
        ids.insert(820);
        ids.insert(9009);
        ids.insert(12370);
        searchGroupOfMedicinesByIds(medicines, ids);

        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "---------------------------------------------------- Buscar aceites ---------------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;

        VDinamico<PaMedicamento *> oil = buscarCompuesto("ACEITE", medicines);
        std::cout << "\nTotal encontrados: " << oil.size() << std::endl;
        for (unsigned int i = 0; i < oil.size(); ++i){
            PaMedicamento *medicinePointer = oil[i];
            /**
             * Con punteros para usar el metodo usamos -> o (*ptr). para acceder a un metodo de un objeto de manera indirecta
             * ya que por asi decirlo "seguiremos la direccion" y accederemos al objeto apuntado
             */
            std::cout << " Medicamento: ( IdNum=" << (*medicinePointer).getIdNum() << " IdAlpha="
                      << medicinePointer->getIdAlpha() << " Nombre=" << medicinePointer->getName() << std::endl;
        }
    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    return 0;
}
