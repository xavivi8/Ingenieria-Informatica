//
// Created by jmart on 27/10/2025.
//
#include "../include/Farmacia.h"
#include "../include/MediExpress.h"

#include <stdexcept>

/**
 * Constructor
 */


Farmacia::Farmacia(const std::string &cif, const std::string &province, const std::string &city, const std::string &name, const std::string &address, const std::string &postalCode, MediExpress* med){
    m_cif = cif;
    m_province = province;
    m_city = city;
    m_name = name;
    m_address = address;
    m_postalCode = postalCode;
    m_linkMedi = med;
};

/**
 * Operadores
 */


bool Farmacia::operator<(const Farmacia &farma) const{
    return m_cif < farma.m_cif;
};

std::ostream& operator<<(std::ostream& os, const Farmacia& f) {
    os << f.m_cif << " | " << f.m_name << " | " << f.m_city
       << " (" << f.m_province << ") | " << f.m_postalCode
       << " | " << f.m_address;
    return os;
}

/**
 * Metodos del uml
 */


void Farmacia::pedidoMedicam(int idNum){
    if(!m_linkMedi){
        throw std::logic_error("Farmacia sin enlace a MediExpress");
    }
    m_linkMedi->suministrarFarmacia(this, idNum);
};


PaMedicamento* Farmacia::buscaMedicam(int idNum){
    PaMedicamento aux(idNum, "", "");
    PaMedicamento* key = &aux;

    PaMedicamento** found = m_dispense.buscaIt(key);
    if (!found) return nullptr;

    return *found;
}



void Farmacia::dispensaMedicam(PaMedicamento &pa){
    if(!m_dispense.inserta(&pa)){
        throw std::runtime_error("El medicamento ya se encuentra");
    }
};

/**
 * Getters
 */


MediExpress* Farmacia::getLinkMedi() const{
    return m_linkMedi;
};

/**
 * Setters
 */


void Farmacia::setLinkMedi(MediExpress *medi){
    m_linkMedi = medi;
};