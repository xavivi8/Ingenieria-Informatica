//
// Created by jmart on 21/11/2025.
//

#ifndef THASHMEDICAM_H
#define THASHMEDICAM_H

#include <vector>
#include "../include/PaMedicamento.h"

enum Estado{LIBRE,OCUPADA,DISPONIBLE};
enum TipoHash { HASH1 = 1, HASH2 = 2, HASH3 = 3 };

class THashMedicam {
private:    
    /**
     * @brief Clase interna que representa una entrada en la tabla hash
     */
    class Entrada {
     public:
        unsigned long m_key;
        Estado m_state;  //0(libre), 1(ocupada), 2(disponible)
        PaMedicamento m_data;
        /**
         * @brief Constructor por defecto
         */
        Entrada(): m_state(LIBRE), m_key(0), m_data() {}
        /**
         * @brief Destructor
         */
        ~Entrada(){};
    };

    unsigned long m_tableSize;
    unsigned long m_numElements; 
    unsigned long m_maxCollisions;
    unsigned long m_over10Collisions;
    unsigned long m_collisionsSum;
    unsigned long m_smallerPrime;

    std::vector<Entrada> m_table;
    TipoHash m_hashType;

    /**
     * @brief Comprueba si un número es primo
     * @param n Número a comprobar
     * @return Devuelve true si el número es primo, false en caso contrario
     */
    bool isPrime(unsigned n);
    /**
     * @brief Devuelve el primo menor o igual a un número dado
     * @param number Número dado
     * @return Devuelve el primo menor o igual a number
     */
    int previousPrime(unsigned number);
    /**
     * @brief Devuelve el primo mayor o igual a un número dado
     * @param number Número dado
     * @return Devuelve el primo mayor o igual a number
     */
    int nextPrime(unsigned number);

    /**
     * @brief Función de dispersión con sondeo cuadrático
     * @param clave Clave a dispersar
     * @param i Número de colisiones ocurridas
     * @return Devuelve el índice de la tabla hash
     */
    unsigned hash(unsigned long clave, int i);
    
    /**
     * @brief Función de dispersión con doble hashing clásico
     * @param clave Clave a dispersar
     * @param i Número de colisiones ocurridas
     * @return Devuelve el índice de la tabla hash
     */
    unsigned hash2(unsigned clave, int i);

    /**
     * @brief Función de dispersión con variante de doble hashing
     * @param clave Clave a dispersar
     * @param i Número de colisiones ocurridas
     * @return Devuelve el índice de la tabla hash
     */
    unsigned hash3(unsigned clave, int i);
    
public:
    /**
     * @brief Constructor por defecto
     */
    THashMedicam();
    /**
     * @brief Constructor parametrizado
     * @param maxElementos Número máximo de elementos a almacenar
     * @param lamda Factor de carga deseado
     * @param t Tipo de función de dispersión
     */
    THashMedicam(unsigned long maxElementos, double lamda=0.7, TipoHash t = HASH1);
    /**
     * @brief Constructor de copia
     * @param orig Objeto a copiar
     */
    THashMedicam(const THashMedicam &orig);
    /**
     * @brief Destructor
     */
    ~THashMedicam();

    /**
     * @brief Operador de asignación
     * @param orig Objeto a copiar
     * @return Devuelve una referencia al objeto actual
     */
    THashMedicam& operator=(const THashMedicam &orig);

    /**
     * @brief Inserta un elemento en la tabla hash
     * @param clave Clave del elemento a insertar
     * @param dato Dato del elemento a insertar
     * @return Devuelve true si se ha insertado correctamente, false en caso contrario
     */
    bool insertar(unsigned long clave, PaMedicamento &dato);
    /**
     * @brief Elimina un elemento de la tabla hash
     * @param clave Clave del elemento a eliminar
     * @return Devuelve true si se ha eliminado correctamente, false en caso contrario
     */
    bool borrar(unsigned long clave);
    /**
     * @brief Busca un elemento en la tabla hash
     * @param clave Clave del elemento a buscar
     * @return Devuelve un puntero al elemento si se encuentra, nullptr en caso contrario
     */
    PaMedicamento* buscar(unsigned long clave);
    /**
     * @brief Devuelve el número de elementos almacenados en la tabla hash
     * @return Devuelve el número de elementos almacenados en la tabla hash
     */
    unsigned int numElementos() const;

    /**
     * @brief Devuelve el tamaño de la tabla hash
     * @return Devuelve el tamaño de la tabla hash
     */
    unsigned int getTableSize() const;
    /**
     * @brief Devuelve el tipo de función de dispersión utilizada
     * @return Devuelve el tipo de función de dispersión utilizada
     */
    unsigned long getMaxCollisions() const;
    /**
     * @brief Devuelve el número de inserciones con más de 10 colisiones
     * @return Devuelve el número de inserciones con más de 10 colisiones
     */
    unsigned int getNumOver10Collisions() const;
    /**
     * @brief Devuelve el promedio de colisiones por inserción
     * @return Devuelve el promedio de colisiones por inserción
     */
    float getAverageCollisions() const;
    /**
     * @brief Devuelve el factor de carga actual de la tabla hash
     * @return Devuelve el factor de carga actual de la tabla hash
     */
    float getLoadFactor() const;

    /**
     * @brief Devuelve el tipo de función de dispersión utilizada
     * @return Devuelve el tipo de función de dispersión utilizada
     */
    TipoHash getHashType() const;
};

#endif //THASHMEDICAM_H
