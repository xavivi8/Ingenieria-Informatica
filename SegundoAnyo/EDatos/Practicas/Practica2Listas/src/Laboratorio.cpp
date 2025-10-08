//
// Created by jmart on 08/10/2025.
//
#include "../include/Laboratorio.h"

/**
 * Constructores
 */
Laboratorio::Laboratorio(){
    m_id = 0;
    m_nombre_lab = "";
    m_direccion = "";
    m_cod_postal = "";
    m_localidad = "";
};

Laboratorio::Laboratorio(int id, const std::string &nombre_lab, const std::string &direccion, const std::string &cod_postal, const std::string &localidad) {
    m_id = id;
    m_nombre_lab = nombre_lab;
    m_direccion = direccion;
    m_cod_postal = cod_postal;
    m_localidad = localidad;
}

/**
 * Getters
 */
int Laboratorio::getId() const {
    return m_id;
}

std::string Laboratorio::getNombreLab() const {
    return m_nombre_lab;
}

std::string Laboratorio::getDireccion() const {
    return m_direccion;
}

std::string Laboratorio::getCodPostal() const {
    return m_cod_postal;
}

std::string Laboratorio::getLocalidad() const {
    return m_localidad;
}

/**
 * Setters
 */
void Laboratorio::setId(int id) {
    m_id = id;
}

void Laboratorio::setNombreLab(const std::string &nombre_lab) {
    m_nombre_lab = nombre_lab;
}

void Laboratorio::setDireccion(const std::string &direccion) {
    m_direccion = direccion;
}

void Laboratorio::setCodPostal(const std::string &cod_postal) {
    m_cod_postal = cod_postal;
}

void Laboratorio::setLocalidad(const std::string &localidad) {
    m_localidad = localidad;
}