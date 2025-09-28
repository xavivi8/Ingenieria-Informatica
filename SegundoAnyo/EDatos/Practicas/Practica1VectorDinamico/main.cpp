#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "VDinamico.h"
#include "PaMedicamento.h"
//Preguntar si se pueden usar "#include <vector>"

VDinamico<PaMedicamento> loadMedicinesFromCsv(const std::string &csvPath){

    std::ifstream is;
    std::stringstream columns;
    std::string row;
    int count=0;
    std::string idNum = "";
    std::string idAlpha = "";
    std::string name = "";

    VDinamico<PaMedicamento> aux;

    is.open(csvPath); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, row ) ) {

            //¿Se ha leído una nueva fila?
            if (row!="") {

                columns.str(row);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columns, idNum, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columns, idAlpha,';');
                getline(columns, name,';');


                row="";
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

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    
    return aux;
};

void showFirst50(VDinamico<PaMedicamento> &medicines){
    unsigned int limit = 100;

    if(limit > medicines.size()){
        limit = medicines.size();
        std::cout << "Primeros "<< limit << " elementos: " << std::endl;
    } else {
        std::cout << "Primeros 50 elementos: " << std::endl;
    }

    for(unsigned int i = 0; i < limit; ++i){
        std::cout << "Medicamento: Id Num: " << medicines[i].getIdNum() << " - Id Alpha: " << medicines[i].getIdAlpha() 
        << " - Nombre: " << medicines[i].getName() << std::endl;
    }
};

void searchGroupOfMedicinesByIds(VDinamico<PaMedicamento> &medicines, VDinamico<int> &ids){
    for(unsigned int i = 0; i < ids.size(); ++i){
        int id = ids[i];
        PaMedicamento medicineAux(id,"","");

        unsigned int pos = medicines.binarySearch(medicineAux);

        if(pos != UINT_MAX){
             std::cout << "Posicion en el vector: " << pos << "\n"
                  << " Medicamento: ( IdNum=" << medicines[pos].getIdNum()
                  << " IdAlpha=" << medicines[pos].getIdAlpha()
                  << " Nombre=" << medicines[pos].getName()
                  << ")" << std::endl;
        } else {
            std::cout << "No se encontro medicamento cuyo id es: " << id << std::endl;
        }
    }
};

int main(int argc, const char * argv[]) {
    VDinamico<PaMedicamento> medicines = loadMedicinesFromCsv("../pa_medicamentos.csv");

    for (unsigned int i = 0; i < medicines.size(); i++) {
        std::cout << i+1 << " Medicamento: ( IdNum=" << medicines[i].getIdNum()
                  << " IdAlpha=" << medicines[i].getIdAlpha()
                  << " Nombre=" << medicines[i].getName()
                  << ")" << std::endl;
    }

    showFirst50(medicines);

    medicines.sort();

    showFirst50(medicines);

    std::cout << "Buscar los ids" << std::endl;
    VDinamico<int> ids;
    ids.insert(350);
    ids.insert(409);
    ids.insert(820);
    ids.insert(9009);
    ids.insert(12370);
    searchGroupOfMedicinesByIds(medicines, ids);

    return 0;
}

