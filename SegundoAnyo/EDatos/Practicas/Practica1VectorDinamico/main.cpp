#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "VDinamico.h"
#include "PaMedicamento.h"

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

int main(int argc, const char * argv[]) {
    VDinamico<PaMedicamento> medicines = loadMedicinesFromCsv("../pa_medicamentos.csv");

    std::cout << "\nTotal medicines loaded: " << medicines.size() << std::endl;

    // Example: iterate all medicines
    for (unsigned int i = 0; i < medicines.size(); i++) {
        std::cout << i+1 << " Medicine: ( Id_number=" << medicines[i].getIdNum()
                  << " Id_alpha=" << medicines[i].getIdAlpha()
                  << " Name=" << medicines[i].getName()
                  << ")" << std::endl;
    }

    return 0;
}

