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


/*
Getters
*/

int Stock::getIdPaMed() const{
    return m_id_PaMed;
};

int Stock::getNumStock() const{
    return m_num_stock;
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