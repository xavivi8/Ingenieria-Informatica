//
// Created by jmart on 08/11/2025.
//
#include "../include/Stock.h"

/*
Constructor
*/


Stock::Stock(int idPaMed, int unidades, PaMedicamento* pa){
    m_id_PaMed = idPaMed;
    m_num_stock = unidades;
    m_number = pa;
};

/*
Metodos
*/

bool Stock::decrementa(int n){
    if (n <= 0 || m_num_stock < n) return false;
    m_num_stock -= n;
    return true;
}

void Stock::incrementa(int n){
    if (n > 0) {
        m_num_stock += n;
    }
};

/*
Operator
*/

bool Stock::operator<(const Stock &rhs) const{
    return (m_id_PaMed < rhs.getIdPaMed());
};

/*
Getters
*/

int Stock::getIdPaMed() const{
    return m_id_PaMed;
};

int Stock::getNumStock() const{
    return m_num_stock;
};

PaMedicamento* Stock::getNumber() const{
    return m_number;
};


/*
Setters
*/

void Stock::setIdPaMed(int n){
    m_id_PaMed = n;
};

void Stock::setNumStock(int n){
    m_num_stock = n;
}

void Stock::setNumber(PaMedicamento* pa){
    m_number = pa;
}