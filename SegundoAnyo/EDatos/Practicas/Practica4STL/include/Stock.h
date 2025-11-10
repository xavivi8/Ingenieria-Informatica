//
// Created by jmart on 08/11/2025.
//
#include "../include/PaMedicamento.h"

#ifndef STOCK_H
#define STOCK_H

class Stock{
    int m_id_PaMed;
    int m_num_stock;
    PaMedicamento* m_idNum;

public:
    Stock() = default;
    Stock(int idPaMed, int unidades, PaMedicamento* pa);
    virtual ~Stock();

    bool decrementa(int n);
    void incrementa(int n);

    bool operator<(const Stock &rhs) const;

    void setIdPaMed(int n);
    void setNumStock(int n);
    void setIdNum(PaMedicamento* pa);

    int getIdPaMed() const;
    int getNumStock() const;
    PaMedicamento* getIdNum() const;
};

#endif //STOCK_H
