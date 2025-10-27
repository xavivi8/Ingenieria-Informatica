//
// Created by jmart on 27/10/2025.
//

#ifndef FARMACIA_H
#define FARMACIA_H

#include "../include/PaMedicamento.h"
#include "../include/Avl.h"
#include <string>

class MediExpress;
class Farmacia{
    std::string m_cif;
    std::string m_provincia;
    std::string m_localidad;
    std::string m_nombre;
    std::string m_direccion;
    std::string m_codpostal;
    Avl<PaMedicamento> dispense;

    public:
    Farmacia();
    Farmacia(const std::string &cif,
             const std::string &provincia,
             const std::string &localidad,
             const std::string &nombre,
             const std::string &direccion,
             const std::string &codPostal);
    ~Farmacia();

    bool operator<(const Farmacia &farma) const;

    void pedidoMedicam(unsigned int id_num);
    PaMedicamento* buscaMedicam(unsigned int id_num);
    void dispensaMedicam(PaMedicamento pa);
};

#endif //FARMACIA_H
