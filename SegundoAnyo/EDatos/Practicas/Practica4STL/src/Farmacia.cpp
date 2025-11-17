//
// Created by jmart on 27/10/2025.
//
#include "../include/Farmacia.h"
#include "../include/MediExpress.h"
#include "../include/utils.h"

#include <stdexcept>

/*
Metodos privados
*/

void Farmacia::pedidoMedicam(int idNum, int n){
    if(!m_linkMedi){
        throw std::logic_error("Farmacia sin enlace a MediExpress");
    }
    if(n <= 0){
        throw std::invalid_argument("Cantidad solicitada debe ser > 0");
    }
    m_linkMedi->suministrarFarmacia(*this, idNum, n);
};

int Farmacia::buscaMedicamID(int id_num) const{
    std::set<Stock>::const_iterator it =m_order.find( Stock(id_num, 0, nullptr) );
    if (it == m_order.end()) return 0;
    return it->getNumStock();
};

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

std::vector<PaMedicamento*> Farmacia::buscaMedicamNombre(const std::string &nombre){
    std::vector<PaMedicamento*> resultados;
    if (nombre.empty()) return resultados;

    resultados.reserve(m_order.size());
    for (std::set<Stock>::const_iterator it = m_order.cbegin(); it != m_order.cend(); ++it) {
        PaMedicamento* pa = it->getNumber();
        if (!pa) continue;

        if (utils::iContains(pa->getName(), nombre)) {
            resultados.push_back(pa);
        }
    }
    return resultados;
}

void Farmacia::nuevoStock(PaMedicamento* pa, int n){
    if (!pa) {
        throw std::invalid_argument("PaMedicamento nulo");
    }
    if (n < 0) {
        throw std::invalid_argument("La cantidad debe ser > 0");
    }

    std::set<Stock>::const_iterator it = m_order.find(Stock(pa->getIdNum(), 0, nullptr));

    if (it == m_order.cend()) {
        m_order.insert(Stock(pa->getIdNum(), n, pa));
    } else {
        Stock actualizado = *it;
        m_order.erase(it);
        actualizado.incrementa(n);
        if (!actualizado.getNumber()) {
            actualizado.setNumber(pa);
        }
        m_order.insert(actualizado);
    }
}



int Farmacia::comprarMedicam(int id_num, int n, PaMedicamento* &result) {
    if (n <= 0) {
        throw std::invalid_argument("La cantidad a comprar debe ser > 0");
    }

    result = nullptr;

    int disponible = buscaMedicamID(id_num);

    if (disponible < n) {
        return 0;  // sin venta
    }

    std::set<Stock>::const_iterator it = m_order.find(Stock(id_num, 0, nullptr));
    if (it == m_order.cend()) {
        return 0;
    }

    Stock actualizado = *it;

    result = actualizado.getNumber();
    if (!result && m_linkMedi) {
        result = m_linkMedi->buscarCompuesto(id_num);
    }

    int restante = actualizado.getNumStock() - n;

    m_order.erase(it);
    actualizado.setNumStock(restante);
    if (restante > 0) {
        m_order.insert(actualizado);
    }

    return n;
}


bool Farmacia::eliminarStock(int idNum){
    std::set<Stock>::const_iterator it = m_order.find( Stock(idNum, 0, nullptr) );
    if (it == m_order.cend()) return false;
    m_order.erase(it);
    return true;
}

int Farmacia::getStock(int id_num) const {
    return buscaMedicamID(id_num);
}


/**
 * Getters
 */

std::string Farmacia::getCif() const{
    return m_cif;
}

std::string Farmacia::getProvince() const{
    return m_province;
}

std::string Farmacia::getCity() const{
    return m_city;
}

std::string Farmacia::getName() const{
    return m_name;
}

std::string Farmacia::getAddress() const{
    return m_address;
}

std::string Farmacia::getPostalCode() const{
    return m_postalCode;
}

MediExpress* Farmacia::getLinkMedi() const{
    return m_linkMedi;
};

/**
 * Setters
 */

void Farmacia::setCif(const std::string &cif){
    m_cif = cif;
}

void Farmacia::setProvince(const std::string &province){
    m_province = province;
}

void Farmacia::setCity(const std::string &city){
    m_city = city;
}

void Farmacia::setName(const std::string &name){
    m_name = name;
}

void Farmacia::setAddress(const std::string &address){
    m_address = address;
}

void Farmacia::setPostalCode(const std::string &postalCode){
    m_postalCode = postalCode;
}

void Farmacia::setLinkMedi(MediExpress *medi){
    m_linkMedi = medi;
};