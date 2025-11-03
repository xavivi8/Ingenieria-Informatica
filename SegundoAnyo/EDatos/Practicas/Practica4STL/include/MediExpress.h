//
// Created by jmart on 08/10/2025.
//
#include "../include/VDinamico.h"
#include "../include/ListaEnlazada.h"
#include "../include/PaMedicamento.h"
#include "../include/Laboratorio.h"
#include "../include/Avl.h"
#include "../include/Farmacia.h"

#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H

class MediExpress{
    private:
        VDinamico<PaMedicamento> m_med;
        ListaEnlazada<Laboratorio> m_lab;
        Avl<Farmacia> m_farma;

        VDinamico<PaMedicamento> loadMedicinesFromCsv(const std::string &csvPath);
        ListaEnlazada<Laboratorio> loadLabFromCsv(const std::string &csvPath);
        Avl<Farmacia> loadFarmacieFromCsv(const std::string &csvPath);
        void autoLinkMedications();

    public:
        MediExpress();
        MediExpress(const std::string &csvPathVD,const std::string &csvPathLE,const std::string &csvPathAVL);
        ~MediExpress();

        void suministrarMed(PaMedicamento &med, Laboratorio &lab);
        Laboratorio* buscarLab(const std::string &labName);
        ListaEnlazada<Laboratorio*> buscarLabCiudad(const std::string &cityName) const;
        VDinamico<PaMedicamento*> buscarCompuesto(const std::string &compoundName) const;
        VDinamico<PaMedicamento*> getMedicamSinLab() const;

        //metodos pract3
        PaMedicamento* buscarCompuesto(int id_num);
        void suministrarFarmacia(Farmacia *f, int idNum);
        Farmacia* buscarFarmacia(const std::string &cif);
        VDinamico<Laboratorio*> buscarLabs(const std::string &nombrePA) const;
};

#endif //MEDIEXPRESS_H
