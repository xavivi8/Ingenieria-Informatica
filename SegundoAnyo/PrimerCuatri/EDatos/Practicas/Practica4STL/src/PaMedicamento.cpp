//
// Created by jmart on 08/10/2025.
//
#include "../include/PaMedicamento.h"
#include "../include/Laboratorio.h"

/**
 * Constructores
 */
PaMedicamento::PaMedicamento(){
    m_id_num = 0;
    m_id_alpha = "";
    m_name = "";
};

PaMedicamento::PaMedicamento(int idNum, std::string idAlpha, std::string name){
    m_id_num = idNum;
    m_id_alpha = idAlpha;
    m_name = name;
};

PaMedicamento::~PaMedicamento(){
    m_id_num = 0;
    m_id_alpha.clear();
    m_name.clear();
    m_servidoPor = nullptr;
};

/**
 * Operadores
 */
bool PaMedicamento::operator==(const PaMedicamento &object) const {
    bool equal = false;

    if(m_id_num == object.m_id_num){
        equal = true;
    }

    return equal;
}

bool PaMedicamento::operator<(const PaMedicamento &object) const{
    return (m_id_num < object.m_id_num);
};

/**
 * Getters
 */
int PaMedicamento::getIdNum() const{
    return m_id_num;
};

std::string PaMedicamento::getIdAlpha() const{
    return m_id_alpha;
};

std::string PaMedicamento::getName() const{
    return m_name;
};

Laboratorio *PaMedicamento::getServidoPor() const{
    return m_servidoPor;
}

/**
 * Setters
 */
void PaMedicamento::setIdNum(int num){
    m_id_num = num;
};

void PaMedicamento::setIdAlpha(std::string alphanumeric){
    m_id_alpha = alphanumeric;
};

void PaMedicamento::setName(std::string name){
    m_name = name;
};

void PaMedicamento::setServidoPor(Laboratorio *lab){
    m_servidoPor = lab;
}
