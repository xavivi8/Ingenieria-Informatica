//
// Created by jmart on 08/10/2025.
//
#include "../include/MediExpress.h"
#include "../include/Farmacia.h"
#include "../include/utils.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <unordered_set>

/**
 * Metodos privados
 */

std::map<int, PaMedicamento> MediExpress::loadMedicinesFromCsv(const std::string &csvPath) {
    std::map<int, PaMedicamento> aux;

    std::ifstream is(csvPath, std::ios::binary);
    if (!is.is_open()) {
        std::cerr << "[ERROR] No puedo abrir: " << csvPath << "\n";
        return aux;
    }

    std::string row;
    while (std::getline(is, row)) {
        if (row.empty()) continue;

        std::stringstream columns(row);
        std::string idNum, idAlpha, name;

        std::getline(columns, idNum,   ';');
        std::getline(columns, idAlpha, ';');
        std::getline(columns, name,    ';'); // el último ; es opcional

        if (idNum.empty()) continue;

        PaMedicamento med(std::stoi(idNum), idAlpha, name);
        aux.emplace(med.getIdNum(), std::move(med));
    }
    return aux;
}

std::list<Laboratorio> MediExpress::loadLabFromCsv(const std::string &csvPath) {
    std::list<Laboratorio> aux;

    std::ifstream is(csvPath, std::ios::binary);
    if (!is.is_open()) {
        std::cerr << "[ERROR] No puedo abrir: " << csvPath << "\n";
        return aux;
    }

    std::string row;
    while (std::getline(is, row)) {
        if (row.empty()) continue;

        std::stringstream columns(row);
        std::string idStr, nombre, direccion, cod_postal, localidad;

        std::getline(columns, idStr,      ';');
        std::getline(columns, nombre,     ';');
        std::getline(columns, direccion,  ';');
        std::getline(columns, cod_postal, ';');
        std::getline(columns, localidad);

        if (idStr.empty()) continue;

        aux.emplace_back(std::stoi(idStr), nombre, direccion, cod_postal, localidad);
    }
    return aux;
}

std::vector<Farmacia> MediExpress::loadFarmacieFromCsv(const std::string &csvPath) {
    std::vector<Farmacia> aux;

    std::ifstream is(csvPath, std::ios::binary);
    if (!is.is_open()) {
        std::cerr << "[ERROR] No puedo abrir: " << csvPath << "\n";
        return aux;
    }

    std::string row;
    while (std::getline(is, row)) {
        if (row.empty()) continue;

        std::stringstream columns(row);
        std::string cif, province, city, name, address, postalCode;

        std::getline(columns, cif,        ';');
        std::getline(columns, province,   ';');
        std::getline(columns, city,       ';');
        std::getline(columns, name,       ';');
        std::getline(columns, address,    ';');
        std::getline(columns, postalCode);

        if (cif.empty()) continue;

        aux.emplace_back(cif, province, city, name, address, postalCode, this);
    }
    return aux;
}

void MediExpress::autoLinkMedications() {
    // 1) Obtener lista de medicamentos sin duplicados desde nombMedication
    std::vector<PaMedicamento*> meds;
    meds.reserve(nombMedication.size());
    std::unordered_set<PaMedicamento*> visto;

    for (std::multimap<std::string, PaMedicamento*>::iterator it = nombMedication.begin();
         it != nombMedication.end(); ++it) {
        PaMedicamento* p = it->second;
        if (p && !visto.count(p)) {
            visto.insert(p);
            meds.push_back(p);
        }
    }

    if (meds.empty()) return;

    // 2) Reparto: 2 medicamentos por laboratorio en orden de lista
    std::size_t idxMed = 0;
    for (std::list<Laboratorio>::iterator labIt = m_lab.begin();
         labIt != m_lab.end() && idxMed < meds.size();
         ++labIt) {

        for (int k = 0; k < 2 && idxMed < meds.size(); ++k, ++idxMed) {
            meds[idxMed]->setServidoPor(&(*labIt));
        }
    }

    if (idxMed >= meds.size()) return;

    // 3) Resto: uno a cada laboratorio cuya ciudad contenga "Madrid"
    std::vector<Laboratorio*> labsMadrid = buscarLabCiudad("Madrid");
    for (Laboratorio* lm : labsMadrid) {
        if (idxMed >= meds.size()) break;
        meds[idxMed]->setServidoPor(lm);
        ++idxMed;
    }
}

void MediExpress::autoLinkFarmaciasStock() {
    if (m_med.empty() || m_farma.empty()) {
        return;
    }

    const int STOCK_INICIAL = 10;
    const int MEDICAMENTOS_POR_F = 100;

    std::vector<int> ids;
    ids.reserve(m_med.size());
    for (std::map<int, PaMedicamento>::const_iterator it = m_med.cbegin();
         it != m_med.cend();
         ++it) {
        ids.push_back(it->first);
    }

    if (ids.empty()) {
        return;
    }

    const std::size_t total = ids.size();
    std::size_t index = 0;

    for (std::vector<Farmacia>::iterator itFar = m_farma.begin();
         itFar != m_farma.end();
         ++itFar) {

        for (int k = 0; k < MEDICAMENTOS_POR_F; ++k) {
            int idMed = ids[index];

            suministrarFarmacia(*itFar, idMed, STOCK_INICIAL);

            ++index;
            if (index >= total) {
                index = 0;
            }
        }
    }
}


/**
 * Constructores
 */

MediExpress::MediExpress() = default;

MediExpress::MediExpress(const std::string &csvPathVD,
                         const std::string &csvPathLE,
                         const std::string &csvPathAVL) {
    m_med   = loadMedicinesFromCsv(csvPathVD);
    m_lab   = loadLabFromCsv(csvPathLE);
    m_farma = loadFarmacieFromCsv(csvPathAVL);
    autoLinkMedications();
    autoLinkFarmaciasStock();
}

MediExpress::~MediExpress() = default;

/**
 * Metodos
 */

void MediExpress::suministrarMed(const PaMedicamento &med, const Laboratorio &lab) {
    Laboratorio* labReal = buscarLab(lab.getLabName());
    if (!labReal) return;

    std::map<int, PaMedicamento>::iterator itMed = m_med.find(med.getIdNum());
    if (itMed != m_med.end()) {
        itMed->second.setServidoPor(labReal);
    }
}

Laboratorio* MediExpress::buscarLab(const std::string &labName) {
    for (std::list<Laboratorio>::iterator it = m_lab.begin(); it != m_lab.end(); ++it) {
        if (it->getLabName() == labName) return &(*it);
    }
    return nullptr;
}

std::vector<Laboratorio*> MediExpress::buscarLabCiudad(const std::string &cityName) const {
    std::vector<Laboratorio*> aux;
    for (std::list<Laboratorio>::const_iterator it = m_lab.cbegin(); it != m_lab.cend(); ++it) {
        if (utils::iContains(it->getCity(), cityName)) {
            // la función es const, pero la firma pide puntero no-const asi que hay que solucionarlo
            aux.push_back(const_cast<Laboratorio*>(&(*it)));
        }
    }
    return aux;
}
std::vector<PaMedicamento*> MediExpress::buscarCompuesto(const std::string &compoundName) const {
    std::vector<PaMedicamento*> aux;
    for (std::map<int, PaMedicamento>::const_iterator it = m_med.cbegin(); it != m_med.cend(); ++it) {
        if (utils::iContains(it->second.getName(), compoundName)) {
            aux.push_back(const_cast<PaMedicamento*>(&it->second));
        }
    }
    return aux;
}

std::vector<PaMedicamento*> MediExpress::getMedicamSinLab() const {
    std::vector<PaMedicamento*> aux;
    for (std::map<int, PaMedicamento>::const_iterator it = m_med.cbegin(); it != m_med.cend(); ++it) {
        if (it->second.getServidoPor() == nullptr) {
            aux.push_back(const_cast<PaMedicamento*>(&it->second));
        }
    }
    return aux;
}

/**
 * Metodos pract 3
 */


PaMedicamento* MediExpress::buscarCompuesto(int id_num) {
    std::map<int, PaMedicamento>::iterator it = m_med.find(id_num);
    return (it == m_med.end()) ? nullptr : &it->second;
}

Farmacia* MediExpress::buscarFarmacia(const std::string &cif) {
    const std::string clave = utils::lowerCopy(cif);
    for (std::vector<Farmacia>::iterator it = m_farma.begin(); it != m_farma.end(); ++it) {
        if (utils::lowerCopy(it->getCif()) == clave) return &(*it);
    }
    return nullptr;
}

std::vector<Laboratorio*> MediExpress::buscarLabs(const std::string &nombrePA) const {
    std::vector<Laboratorio*> resultado;
    std::unordered_set<Laboratorio*> visto;

    for (std::map<int, PaMedicamento>::const_iterator it = m_med.cbegin(); it != m_med.cend(); ++it) {
        const PaMedicamento &med = it->second;
        if (!utils::iContains(med.getName(), nombrePA)) continue;

        Laboratorio* lab = med.getServidoPor();
        if (lab && !visto.count(lab)) {
            resultado.push_back(lab);
            visto.insert(lab);
        }
    }
    return resultado;
}

/**
 * Metodos pract 4
 */

void MediExpress::suministrarFarmacia(Farmacia &f, int id_num, int n) {
    PaMedicamento* med = buscarCompuesto(id_num);
    if (!med) throw std::logic_error("Medicamento no encontrado");
    f.nuevoStock(med, n);
}

std::vector<Farmacia*> MediExpress::buscarFarmacias(const std::string &provincia) const {
    std::vector<Farmacia*> v;
    for (std::vector<Farmacia>::const_iterator it = m_farma.cbegin(); it != m_farma.cend(); ++it) {
        if (utils::iContains(it->getProvince(), provincia)) {
            v.push_back(const_cast<Farmacia*>(&(*it)));
        }
    }
    return v;
}

bool MediExpress::eliminarMedicamento(int id_num) {
    std::map<int, PaMedicamento>::iterator itMed = m_med.find(id_num);
    if (itMed == m_med.end()) return false;

    for (std::vector<Farmacia>::iterator it = m_farma.begin(); it != m_farma.end(); ++it) {
        it->eliminarStock(id_num);
    }

    m_med.erase(itMed);

    return true;
}