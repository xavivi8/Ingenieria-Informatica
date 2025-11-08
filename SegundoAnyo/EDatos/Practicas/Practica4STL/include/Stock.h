//
// Created by jmart on 08/11/2025.
//

#ifndef STOCK_H
#define STOCK_H

class Stock{
    int m_id_PaMed;
    int m_num_stock;

public:
    Stock() = default;
    Stock(int idPaMed, int unidades): m_id_PaMed(idPaMed), m_num_stock(unidades){};

    void decrementa(int n);
    void incrementa(int n);

    void setNumStock(int n);

    int getIdPaMed() const;
    int getNumStock() const;
};

#endif //STOCK_H
