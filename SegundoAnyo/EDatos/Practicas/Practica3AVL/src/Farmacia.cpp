//
// Created by jmart on 27/10/2025.
//
#include "../include/Farmacia.h"
#include "../include/MediExpress.h"

#include <stdexcept>

/**
 * Constructor
 */


Farmacia::Farmacia(const std::string &cif, const std::string &province, const std::string &city, const std::string &name, const std::string &address, const std::string &postalCode){
    m_cif = cif;
    m_province = province;
    m_city = city;
    m_name = name;
    m_address = address;
    m_postalCode = postalCode;
};

/**
 * Operadores
 */


bool Farmacia::operator<(const Farmacia &farma) const{
    return m_cif < farma.m_cif;
};

/**
 * Metodos del uml
 */


void Farmacia::pedidoMedicam(unsigned int idNum){
    if(!m_linkMedi){
        throw std::logic_error("Farmacia sin enlace a MediExpress");
    }
};