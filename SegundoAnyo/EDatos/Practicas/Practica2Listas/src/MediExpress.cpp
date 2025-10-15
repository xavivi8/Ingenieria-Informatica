//
// Created by jmart on 08/10/2025.
//
#include "../include/MediExpress.h"
#include <fstream>
#include <sstream>

/**
 * Metodos privados
 */

VDinamico<PaMedicamento> MediExpress::loadMedicinesFromCsv(const std::string &csvPath){

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

                PaMedicamento med(std::stoi(idNum), idAlpha, name);
                aux.insert(med);
            }
        }

        is.close();

    } else {
        
    }

    return aux;
};

ListaEnlazada<Laboratorio> MediExpress::loadLabFromCsv(const std::string &csvPath){
    std::ifstream is;
    std::stringstream columns;
    std::string row;

    std::string idStr = "";
    std::string nombre = "";
    std::string direccion = "";
    std::string cod_postal = "";
    std::string localidad = "";

    ListaEnlazada<Laboratorio> aux;

    is.open(csvPath);
    if (is.good()) {

        while (getline(is, row)) {
            if (row != "") {

                columns.str(row);

                getline(columns, idStr, ';');
                getline(columns, nombre, ';');
                getline(columns, direccion, ';');
                getline(columns, cod_postal, ';');
                getline(columns, localidad, '\r');

                row = "";
                columns.clear();

                // crear y añadir el laboratorio
                Laboratorio lab(std::stoi(idStr), nombre, direccion, cod_postal, localidad);
                aux.insertAtEnd(lab);
            }
        }

        is.close();

    } else {
    }

    return aux;
};


/**
 * Constructores
 */

MediExpress::MediExpress() = default;

MediExpress::MediExpress(const std::string &csvPathVD, const std::string &csvPathLE){
    m_med = loadMedicinesFromCsv(csvPathVD);
    m_lab = loadLabFromCsv(csvPathLE);
}

/**
 * Metodos
 */

void MediExpress::suministrarMed(const PaMedicamento& med, const Laboratorio& lab){
    bool labExists = false;
    for (auto it = m_lab.iterator(); !it.isEnd(); it.next()) {
        if (it.data().getId() == lab.getId()) {
            labExists = true;
            break;
        }
    }

    if (labExists) {
        
    }
}

