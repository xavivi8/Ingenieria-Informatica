//
// Created by jmart on 08/10/2025.
//
#include "../include/VDinamico.h"
#include "../include/ListaEnlazada.h"
#include "../include/PaMedicamento.h"
#include "../include/Laboratorio.h"

#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H

class Farmacia;
class MediExpress{
    private:
        VDinamico<PaMedicamento> m_med;
        ListaEnlazada<Laboratorio> m_lab;

        VDinamico<PaMedicamento> loadMedicinesFromCsv(const std::string &csvPath);
        ListaEnlazada<Laboratorio> loadLabFromCsv(const std::string &csvPath);
        void autoLinkMedications();

    public:
        MediExpress();
        MediExpress(const std::string &csvPathVD,const std::string &csvPathLE);
        ~MediExpress();

        void suministrarMed(PaMedicamento &med, Laboratorio &lab);
        Laboratorio* buscarLab(const std::string &labName);
        ListaEnlazada<Laboratorio*> buscarLabCiudad(const std::string &cityName) const;
        VDinamico<PaMedicamento*> buscarCompuesto(const std::string &compoundName) const;
        VDinamico<PaMedicamento*> getMedicamSinLab() const;

        //metodos pract3
        PaMedicamento* buscarCompuesto(int id_num);
        void suministrarFarmacia(Farmacia &f, unsigned int id_num);
        Farmacia* buscarFarmacia(const std::string &cif) const;
        VDinamico<Laboratorio*> buscarLabs(const std::string &nombrePA) const;
};

#endif //MEDIEXPRESS_H
