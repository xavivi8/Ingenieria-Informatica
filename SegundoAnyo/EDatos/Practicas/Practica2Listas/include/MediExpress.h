//
// Created by jmart on 08/10/2025.
//
#include "../include/VDinamico.h"
#include "../include/ListaEnlazada.h"
#include "../include/PaMedicamento.h"
#include "../include/Laboratorio.h"

#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H

class MediExpress{
    public:
    void suministarMed(PaMedicamento paMed, Laboratorio lab);
    void findLab() const;
    void findLabCity() const;
    void findCompuesto() const;
 
};

#endif //MEDIEXPRESS_H
