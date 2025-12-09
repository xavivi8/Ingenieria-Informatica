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
#include <chrono>

/**
 * Metodos privados
 */

std::vector<PaMedicamento> MediExpress::loadMedicinesFromCsv(const std::string &csvPath) {
    std::vector<PaMedicamento> medicines;

    std::ifstream is(csvPath, std::ios::binary);
    if (!is.is_open()) {
        std::cerr << "[ERROR] No puedo abrir: " << csvPath << "\n";
        return medicines;
    }

    std::string row;
    while (std::getline(is, row)) {
        if (row.empty()) {
            continue;
        }

        std::stringstream columns(row);
        std::string idNum;
        std::string idAlpha;
        std::string name;

        std::getline(columns, idNum,   ';');
        std::getline(columns, idAlpha, ';');
        std::getline(columns, name,    ';');  // el último ; es opcional

        if (idNum.empty()) {
            continue;
        }

        int numericId = std::stoi(idNum);
        medicines.emplace_back(numericId, idAlpha, name);
    }

    return medicines;
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
    meds.reserve(m_nameMed.size());
    std::unordered_set<PaMedicamento*> visto;

    for (std::multimap<std::string, PaMedicamento*>::iterator it = m_nameMed.begin(); it != m_nameMed.end(); ++it) {
        PaMedicamento* p = it->second;
        if (p && !visto.count(p)) {
            visto.insert(p);
            meds.push_back(p);
        }
    }

    if (meds.empty()) return;

    // 2) Reparto: 2 medicamentos por laboratorio en orden de lista
    std::size_t idxMed = 0;
    for (std::list<Laboratorio>::iterator labIt = m_labs.begin(); labIt != m_labs.end() && idxMed < meds.size(); ++labIt) {

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
    std::vector<int> ids;
    ids.reserve(m_nameMed.size());
    std::unordered_set<PaMedicamento*> visto;

    for (std::multimap<std::string, PaMedicamento*>::iterator it = m_nameMed.begin();
         it != m_nameMed.end(); ++it) {
        PaMedicamento* p = it->second;
        if (p && !visto.count(p)) {
            visto.insert(p);
            ids.push_back(p->getIdNum());
        }
    }

    if (ids.empty() || m_far.empty()) {
        return;
    }

    const int STOCK_INICIAL      = 10;
    const int MEDICAMENTOS_POR_F = 100;

    const std::size_t total = ids.size();
    std::size_t index = 0;

    for (std::size_t i = 0; i < m_far.size(); ++i) {
        Farmacia &f = m_far[i];

        for (int k = 0; k < MEDICAMENTOS_POR_F; ++k) {
            int idMed = ids[index];

            suministrarFarmacia(f, idMed, STOCK_INICIAL);

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

MediExpress::MediExpress() : m_idMedication(1) {}

MediExpress::MediExpress(const std::string &csvPathVD, const std::string &csvPathLE, const std::string &csvPathAVL,double lambda, TipoHash tipoHash) : m_idMedication(1) {
    std::vector<PaMedicamento> auxMed = loadMedicinesFromCsv(csvPathVD);

    THashMedicam tmp(static_cast<unsigned long>(auxMed.size()), lambda, tipoHash);

    for (std::size_t i = 0; i < auxMed.size(); ++i) {
        PaMedicamento &med = auxMed[i];
        unsigned long key = static_cast<unsigned long>(med.getIdNum());
        tmp.insertar(key, med);
    }
    m_idMedication = tmp;

    m_labs = loadLabFromCsv(csvPathLE);

    std::vector<Farmacia> auxFarma = loadFarmacieFromCsv(csvPathAVL);
    m_far = auxFarma;

    for (std::size_t i = 0; i < auxMed.size(); ++i) {
        int id = auxMed[i].getIdNum();
        PaMedicamento* p = m_idMedication.buscar(static_cast<unsigned long>(id));
        if (!p) continue;
        std::string clave = utils::lowerCopy(p->getName());
        m_nameMed.insert(std::make_pair(clave, p));
    }

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

    PaMedicamento* encontrado = m_idMedication.buscar(med.getIdNum());
    if (encontrado) {
        encontrado->setServidoPor(labReal);
    }
}

Laboratorio* MediExpress::buscarLab(const std::string &labName) {
    for (std::list<Laboratorio>::iterator it = m_labs.begin(); it != m_labs.end(); ++it) {
        if (it->getLabName() == labName) return &(*it);
    }
    return nullptr;
}

std::vector<Laboratorio*> MediExpress::buscarLabCiudad(const std::string &cityName) const {
    std::vector<Laboratorio*> aux;
    for (std::list<Laboratorio>::const_iterator it = m_labs.cbegin(); it != m_labs.cend(); ++it) {
        if (utils::iContains(it->getCity(), cityName)) {
            // la función es const, pero la firma pide puntero no-const asi que hay que solucionarlo
            aux.push_back(const_cast<Laboratorio*>(&(*it)));
        }
    }
    return aux;
}

std::vector<PaMedicamento*> MediExpress::buscarCompuesto(const std::string &compoundName) const {
    std::vector<PaMedicamento*> aux;
    std::unordered_set<PaMedicamento*> visto;
//find () y hacer un set interset
    for (std::multimap<std::string, PaMedicamento*>::const_iterator it = m_nameMed.cbegin(); it != m_nameMed.cend(); ++it) {
        PaMedicamento* med = it->second;
        if (!med) continue;
        if (visto.count(med)) continue; // evitar duplicados

        if (utils::iContains(med->getName(), compoundName)) {
            aux.push_back(med);
            visto.insert(med);
        }
    }
    return aux;
}

std::vector<PaMedicamento*> MediExpress::getMedicamSinLab() const {
    std::vector<PaMedicamento*> aux;
    std::unordered_set<PaMedicamento*> visto;

    for (std::multimap<std::string, PaMedicamento*>::const_iterator it = m_nameMed.cbegin(); it != m_nameMed.cend(); ++it) {
        PaMedicamento* med = it->second;
        if (!med) continue;
        if (visto.count(med)) continue;

        if (med->getServidoPor() == nullptr) {
            aux.push_back(med);
        }
        visto.insert(med);
    }
    return aux;
}

/**
 * Metodos pract 3
 */


PaMedicamento* MediExpress::buscarCompuesto(int id_num) {
    return m_idMedication.buscar(static_cast<unsigned long>(id_num));
}

Farmacia* MediExpress::buscarFarmacia(const std::string &cif) {
    const std::string clave = utils::lowerCopy(cif);

    for (std::size_t i = 0; i < m_far.size(); ++i) {
        const std::string cifFarma = utils::lowerCopy(m_far[i].getCif());
        if (cifFarma == clave) {
            return &m_far[i];
        }
    }

    return nullptr;
}


std::vector<Laboratorio*> MediExpress::buscarLabs(const std::string &nombrePA) const {
    std::vector<Laboratorio*> resultado;
    std::unordered_set<Laboratorio*> visto;

    std::vector<PaMedicamento*> meds = buscarCompuesto(nombrePA);
     for (std::size_t i = 0; i < meds.size(); ++i) {
        PaMedicamento* med = meds[i];
        if (!med) {
            continue;
        }

        Laboratorio* lab = med->getServidoPor();
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

    for (std::size_t i = 0; i < m_far.size(); ++i) {
        const std::string &provFarma = m_far[i].getProvince();
        if (utils::iContains(provFarma, provincia)) {
            v.push_back(const_cast<Farmacia*>(&m_far[i]));
        }
    }

    return v;
}


bool MediExpress::eliminarMedicamento(int id_num) {
    PaMedicamento* med = m_idMedication.buscar(id_num);
    if (!med) return false;

    for (std::size_t i = 0; i < m_far.size(); ++i) {
        m_far[i].eliminarStock(id_num);
    }

    m_idMedication.borrar(id_num);

    for (std::multimap<std::string, PaMedicamento*>::iterator it = m_nameMed.begin();
         it != m_nameMed.end(); ) {
        if (it->second == med) {
            it = m_nameMed.erase(it);
        } else {
            ++it;
        }
    }

    return true;
}

void MediExpress::mostrarEstadoTabla() {
    std::cout << "================ ESTADO INTERNO DE LA TABLA HASH ================\n";

    unsigned int tam = m_idMedication.getTableSize();
    unsigned int nElems = m_idMedication.numElementos();
    float lambda = m_idMedication.getLoadFactor();
    unsigned long maxCol = m_idMedication.getMaxCollisions();
    unsigned int num10 = m_idMedication.getNumOver10Collisions();
    float promCol = m_idMedication.getAverageCollisions();

    std::cout << "  Tamanyo de la tabla        : " << tam << "\n";
    std::cout << "  N de elementos almacenados: " << nElems << "\n";
    std::cout << "  Factor de carga (lambda)  : " << lambda << "\n";
    std::cout << "  Max. colisiones insercion : " << maxCol << "\n";
    std::cout << "  N inserciones > 10 col.  : " << num10 << "\n";
    std::cout << "  Promedio de colisiones    : " << promCol << "\n";
    std::cout << "=================================================================\n";
}

void MediExpress::pruebaRendimiento() {
    // 1) Construimos un vector de IDs y una lista de PaMedicamento
    std::vector<int> ids;
    std::list<PaMedicamento> lista;
    std::unordered_set<PaMedicamento*> visto;

    for (std::multimap<std::string, PaMedicamento*>::const_iterator it = m_nameMed.cbegin(); it != m_nameMed.cend(); ++it) {

        PaMedicamento* med = it->second;
        if (!med) continue;
        if (visto.count(med)) continue;

        visto.insert(med);
        ids.push_back(med->getIdNum());
        lista.push_back(*med);
    }

    if (ids.empty()) {
        m_hashTime  = 0.0;
        m_listTime = 0.0;
        return;
    }

    // 2) Búsqueda masiva en la tabla hash
    std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();

    for (std::size_t i = 0; i < ids.size(); ++i) {
        int id = ids[i];
        PaMedicamento* p = buscarCompuesto(id);
        (void)p;
    }

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> durHash = t1 - t0;

    // 3) Búsqueda masiva en std::list<PaMedicamento>
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    for (std::size_t i = 0; i < ids.size(); ++i) {
        int id = ids[i];
        bool found = false;

        for (std::list<PaMedicamento>::const_iterator it = lista.cbegin();
             it != lista.cend(); ++it) {
            if (it->getIdNum() == id) {
                found = true;
                break;
            }
        }

        (void)found;
    }

    std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> durList = t3 - t2;

    // 4) Guardamos los tiempos para que el main los lea
    m_hashTime  = durHash.count();
    m_listTime = durList.count();
}

/**
 * Getters
 */

unsigned int MediExpress::getMaxColisiones() const {
    return static_cast<unsigned int>(m_idMedication.getMaxCollisions());
}

unsigned int MediExpress::getNumMax10() const { 
    return m_idMedication.getNumOver10Collisions();
}
float MediExpress::getPromedioColisiones() const { 
    return m_idMedication.getAverageCollisions(); 
}
float MediExpress::getFactorCarga() const { 
    return m_idMedication.getLoadFactor(); 
}
unsigned int MediExpress::getTamTabla() const { 
    return m_idMedication.getTableSize(); 
}
unsigned int MediExpress::getNumElementos() const { 
    return m_idMedication.numElementos(); 
}

double MediExpress::getTiempoHash() const { 
    return m_hashTime; 
}
double MediExpress::getTiempoLista() const { 
    return m_listTime; 
}
