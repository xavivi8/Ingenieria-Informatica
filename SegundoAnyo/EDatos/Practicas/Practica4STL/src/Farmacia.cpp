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

int Farmacia::buscaMedicamID(int id_num){
    std::set<Stock>::const_iterator it =m_order.find( Stock(id_num, 0, nullptr) );
    if (it == m_order.end()) return -1;
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
    for (std::set<Stock>::const_iterator it = m_order.cbegin(); it != m_order.cbegin(); ++it) {
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
    if (n <= 0) {
        throw std::invalid_argument("La cantidad debe ser > 0");
    }

    Stock clave(pa->getIdNum(), 0, nullptr);
    std::set<Stock>::const_iterator it = m_order.find(clave);

    if (it == m_order.cend()) {
       m_order.insert(Stock(pa->getIdNum(), n, pa));
    } else {
        int unidades = it->getNumStock();
        PaMedicamento* ref = it->getNumber();
        m_order.erase(it);
        // Conserva el puntero existente si lo había; si era null, usa 'pa'
        m_order.insert(Stock(pa->getIdNum(), unidades + n, ref ? ref : pa));
    }
}

PaMedicamento* Farmacia::comprarMedicamento(int id_num, int n){
    if (n <= 0) {
        throw std::invalid_argument("La cantidad a comprar debe ser > 0");
    }

    std::set<Stock>::const_iterator it = m_order.find(Stock(id_num, 0, nullptr));

    int disponible = (it == m_order.cend()) ? 0 : it->getNumStock();
    if (disponible < n) {
        // Necesitamos reponer la diferencia
        int falta = n - disponible;
        if (!m_linkMedi) {
            throw std::logic_error("Farmacia sin enlace a MediExpress: no se puede reponer stock.");
        }

        pedidoMedicam(id_num, falta);

        it = m_order.find(Stock(id_num, 0, nullptr));
        if (it == m_order.cend() || it->getNumStock() < n) {
            throw std::runtime_error("Stock insuficiente tras solicitar reposición.");
        }
    }

    Stock actualizado = *it;
    PaMedicamento* pa = actualizado.getNumber();
    int restante = actualizado.getNumStock() - n;

    m_order.erase(it);
    if (restante > 0) {
        actualizado.setNumStock(restante);
        m_order.insert(actualizado);
    }

    if (!pa && m_linkMedi) {
        pa = m_linkMedi->buscarCompuesto(id_num);
    }

    return pa;
}

bool Farmacia::deleteStock(int idNum){
    std::set<Stock>::const_iterator it = m_order.find( Stock(idNum, 0, nullptr) );
    if (it == m_order.cend()) return false;
    m_order.erase(it);
    return true;
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