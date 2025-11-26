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
    class Entrada {
     public:
        unsigned long m_key;
        Estado m_state;  //0(libre), 1(ocupada), 2(disponible)
        PaMedicamento m_data;
        Entrada(): m_state(LIBRE), m_key(0), m_data() {}
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

    bool isPrime(unsigned n);
    int previousPrime(unsigned number);
    int nextPrime(unsigned number);

    //  la función de dispersión es cuadratica
    unsigned hash(unsigned long clave, int i);
    
    //  la funcion de dispersion es doble
    unsigned hash2(unsigned clave, int i);

    //  la funcion de dispersion es doble
    unsigned hash3(unsigned clave, int i);
    
public:
    THashMedicam();
    THashMedicam(unsigned long maxElementos, double lamda=0.7, TipoHash t = HASH1);
    THashMedicam(const THashMedicam &orig);
    ~THashMedicam();

    THashMedicam& operator=(const THashMedicam &orig);

    bool insertar(unsigned long clave, PaMedicamento &dato);
    bool borrar(unsigned long clave);
    PaMedicamento* buscar(unsigned long clave);
    unsigned int numElementos() const;

    unsigned int getTableSize() const;
    unsigned long getMaxCollisions() const;
    unsigned int getNumOver10Collisions() const;
    float getAverageCollisions() const;
    float getLoadFactor() const;

    TipoHash getHashType() const;
};

#endif //THASHMEDICAM_H
