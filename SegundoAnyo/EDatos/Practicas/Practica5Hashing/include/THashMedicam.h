//
// Created by jmart on 21/11/2025.
//

#ifndef THASHMEDICAM_H
#define THASHMEDICAM_H

#include <vector>
#include "../include/PaMedicamento.h"

enum Estado{LIBRE,OCUPADA,DISPONIBLE};

class THashMedicam {
private:    
    class Entrada {
     public:
        unsigned long clave;
        Estado marca;  //0(libre), 1(ocupada), 2(disponible)
        PaMedicamento dato;
        Entrada(): marca(LIBRE), clave(0), dato() {}
        ~Entrada(){};
    };

    unsigned long tamaf;
    unsigned long tamal; 
    unsigned long maxCol;
    unsigned long max10;
    unsigned long sumaColisiones;
    unsigned long primoMenor;

    std::vector<Entrada> tabla;

    bool esprimo(unsigned n);
    int primo_menor(unsigned numero);
    int primo_mayor(unsigned numero);

    //  la función de dispersión es cuadratica
    unsigned hash(unsigned long clave, int i);
    
    //  la funcion de dispersion es doble
    unsigned hash2(unsigned clave, int i);

    //  la funcion de dispersion es doble
    unsigned hash3(unsigned clave, int i);
    
public:
    THashMedicam();
    THashMedicam(unsigned long maxElementos, double lamda=0.7);
    THashMedicam(const THashMedicam &orig);
    ~THashMedicam();

    THashMedicam& operator=(const THashMedicam &orig);

    bool insertar(unsigned long clave, PaMedicamento &dato);
    bool borrar(unsigned long clave);
    PaMedicamento* buscar(unsigned long clave);
    
    unsigned int numElementos() const;
    unsigned int tamTabla() const;
    unsigned long maxColisiones() const;
    unsigned int numMax10() const;
    float promedioColisiones() const;
    float factorCarga() const;
};

#endif //THASHMEDICAM_H
