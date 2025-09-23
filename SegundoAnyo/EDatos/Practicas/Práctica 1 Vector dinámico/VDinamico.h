//
// Created by jmart on 23/09/2025.
//

#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <algorithm>
#include <cmath>
#include <climits>


template<class T>
class VDinamico {
private:
    //Se ocupa de redondear a la potencia de 2
    void roundToPowerOf2(unsigned long int &t);
    //Se ocupa de coger memoria
    void allocateMemory();
    //Se ocupa de liberar memoria
    void freeMemory();

    unsigned long int tamaf,tamal;
    T *v;

public:
    VDinamico();
    VDinamico(unsigned long int tama);
    VDinamico(const VDnamico<T> &orig);
    VDinamico(const VDinamico<T>& origen, unsigned long int inicio, unsigned long int num);
    ~VDinamico();

    VDinamico<T> &operator=(const VDinamico<T> &arr);
    T &operator[](unsigned long int pos);
    void insert (const T &data, unsigned long int pos=UINT_MAX);
    T remove (unsigned long int pos=UINT_MAX);
    unsigned long int tama();

    unsigned long int binarySearch(const T &data);

    void sort();

}

template<class T>
void VDinamico<T>::roundToPowerOf2(unsigned long int &t) {

};

template<class T>
void VDinamico<T>::VDinamico(){
    tamaf = 1;
    tamal = 0;
    // Inicializo el victor con tamanyo fisico 1 y vacio
    v = new T[tamaf];
};

#endif //VDINAMICO_H
