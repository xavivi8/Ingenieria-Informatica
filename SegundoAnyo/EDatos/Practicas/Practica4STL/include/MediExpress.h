//
// Created by jmart on 08/10/2025.
//
#include "../include/VDinamico.h"
#include "../include/ListaEnlazada.h"
#include "../include/PaMedicamento.h"
#include "../include/Laboratorio.h"
#include "../include/Avl.h"
#include "../include/Farmacia.h"

#include <set>
#include <vector>
#include <list>
#include <map>

#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H

class MediExpress{
    private:
        std::map<int, PaMedicamento> m_med;
        std::list<Laboratorio> m_lab;
        std::vector<Farmacia> m_farma;

        std::map<int, PaMedicamento> loadMedicinesFromCsv(const std::string &csvPath);
        std::list<Laboratorio> loadLabFromCsv(const std::string &csvPath);
        std::vector<Farmacia> loadFarmacieFromCsv(const std::string &csvPath);
        void autoLinkMedications();

    public:
        MediExpress();
        MediExpress(const std::string &csvPathVD,
                    const std::string &csvPathLE,
                    const std::string &csvPathAVL);
        ~MediExpress();

        void suministrarMed(PaMedicamento &med, Laboratorio &lab);
        Laboratorio* buscarLab(const std::string &labName);
        std::vector<Laboratorio*> buscarLabCiudad(const std::string &cityName) const;
        std::vector<PaMedicamento*> buscarCompuesto(const std::string &compoundName) const;
        std::vector<PaMedicamento*> getMedicamSinLab() const;

        //metodos pract3
        PaMedicamento* buscarCompuesto(int id_num);
        Farmacia* buscarFarmacia(const std::string &cif);
        std::vector<Laboratorio*> buscarLabs(const std::string &nombrePA) const;

        //metodos pract4
        void suministrarFarmacia(Farmacia &f, int id_num, int n);
        std::vector<Farmacia*> buscarFarmacias(const std::string &provincia) const;
        bool eliminarMedicamento(int id_num);
};

#endif //MEDIEXPRESS_H
