//
// Created by jmart on 08/11/2025.
//
#include "../include/PaMedicamento.h"

#ifndef STOCK_H
#define STOCK_H

class Stock{
    int m_id_PaMed;
    int m_num_stock;
    PaMedicamento* m_number;

public:
    /**
     * @brief Constructor por defecto
     * @post Inicializa los atributos a valores por defecto
     */
    Stock() = default;
    /**
     * @brief Constructor con parametros
     * @param idPaMed Identificador numerico del medicamento
     * @param unidades Numero de unidades en stock
     * @param pa Puntero al medicamento
     */
    Stock(int idPaMed, int unidades, PaMedicamento* pa);
    /**
     * @brief Destructor
     * @post Destructor por defecto
     */
    ~Stock() = default;

    /**
     * @brief Decrementa el stock en n unidades
     * @param n Numero de unidades a decrementar
     * @return Devuelve true si se ha podido decrementar el stock, false en caso contrario
     */
    bool decrementa(int n);
    /**
     * @brief Incrementa el stock en n unidades
     * @param n Numero de unidades a incrementar
     * @post Incrementa el stock en n unidades
     */
    void incrementa(int n);

    /**
     * @brief Operador menor que
     * @param rhs Objeto Stock con el que se va a comparar
     * @return Devuelve true si el objeto que llama al operador es menor que el objeto pasado por parametro, false en caso contrario
     */
    bool operator<(const Stock &rhs) const;

    /**
     * @brief Setters
     * @param n Nuevo valor para el atributo
     * @post Actualiza el valor del atributo
     */
    void setIdPaMed(int n);
    /**
     * @brief Setter del numero de stock
     * @param n Nuevo numero de stock
     * @post Actualiza el numero de stock
     */
    void setNumStock(int n);
    /**
     * @brief Setter del puntero al medicamento
     * @param pa Puntero al medicamento
     * @post Actualiza el puntero al medicamento
     */
    void setNumber(PaMedicamento* pa);

    /**
     * @brief Getters
     * @return Devuelve el valor del atributo
     */
    int getIdPaMed() const;
    /**
     * @brief Getter del numero de stock
     * @return Devuelve el numero de stock
     */
    int getNumStock() const;
    /**
     * @brief Getter del puntero al medicamento
     * @return Devuelve el puntero al medicamento
     */
    PaMedicamento* getNumber() const;
};

#endif //STOCK_H
