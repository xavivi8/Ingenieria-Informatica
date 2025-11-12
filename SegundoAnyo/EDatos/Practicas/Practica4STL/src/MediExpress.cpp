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
    if (m_med.empty()) return;

    // 1) Reparto: 2 medicamentos por laboratorio en orden de lista
    auto medIt = m_med.begin();
    for (auto labIt = m_lab.begin(); labIt != m_lab.end() && medIt != m_med.end(); ++labIt) {
        for (int k = 0; k < 2 && medIt != m_med.end(); ++k, ++medIt) {
            medIt->second.setServidoPor(&(*labIt));
        }
    }
    if (medIt == m_med.end()) return;

    // 2) Resto: uno a cada primer laboratorio cuya ciudad contenga "Madrid"
    auto labsMadrid = buscarLabCiudad("Madrid"); // usa utils::iContains
    for (Laboratorio* lm : labsMadrid) {
        if (medIt == m_med.end()) break;
        medIt->second.setServidoPor(lm);
        ++medIt;
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
}

MediExpress::~MediExpress() = default;

/**
 * Metodos
 */

void MediExpress::suministrarMed(const PaMedicamento &med, const Laboratorio &lab) {
    Laboratorio* labReal = buscarLab(lab.getLabName());
    if (!labReal) return;

    auto itMed = m_med.find(med.getIdNum());
    if (itMed != m_med.end()) {
        itMed->second.setServidoPor(labReal);
    }
}

Laboratorio* MediExpress::buscarLab(const std::string &labName) {
    for (auto it = m_lab.begin(); it != m_lab.end(); ++it) {
        if (it->getLabName() == labName) return &(*it);
    }
    return nullptr;
}

std::vector<Laboratorio*> MediExpress::buscarLabCiudad(const std::string &cityName) const {
    std::vector<Laboratorio*> aux;
    for (auto it = m_lab.cbegin(); it != m_lab.cend(); ++it) {
        if (utils::iContains(it->getCity(), cityName)) {
            // la función es const, pero la firma pide puntero no-const asi que hay que solucionarlo
            aux.push_back(const_cast<Laboratorio*>(&(*it)));
        }
    }
    return aux;
}
std::vector<PaMedicamento*> MediExpress::buscarCompuesto(const std::string &compoundName) const {
    std::vector<PaMedicamento*> aux;
    for (auto it = m_med.cbegin(); it != m_med.cend(); ++it) {
        if (utils::iContains(it->second.getName(), compoundName)) {
            aux.push_back(const_cast<PaMedicamento*>(&it->second));
        }
    }
    return aux;
}

std::vector<PaMedicamento*> MediExpress::getMedicamSinLab() const {
    std::vector<PaMedicamento*> aux;
    for (auto it = m_med.cbegin(); it != m_med.cend(); ++it) {
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
    auto it = m_med.find(id_num);
    return (it == m_med.end()) ? nullptr : &it->second;
}

Farmacia* MediExpress::buscarFarmacia(const std::string &cif) {
    const std::string clave = utils::lowerCopy(cif);
    for (auto it = m_farma.begin(); it != m_farma.end(); ++it) {
        if (utils::lowerCopy(it->getCif()) == clave) return &(*it);
    }
    return nullptr;
}

std::vector<Laboratorio*> MediExpress::buscarLabs(const std::string &nombrePA) const {
    std::vector<Laboratorio*> resultado;
    std::unordered_set<Laboratorio*> visto;

    for (auto it = m_med.cbegin(); it != m_med.cend(); ++it) {
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
    for (auto it = m_farma.cbegin(); it != m_farma.cend(); ++it) {
        if (utils::iContains(it->getProvince(), provincia)) {
            v.push_back(const_cast<Farmacia*>(&(*it)));
        }
    }
    return v;
}

bool MediExpress::eliminarMedicamento(int id_num) {
    return m_med.erase(id_num) > 0;
}