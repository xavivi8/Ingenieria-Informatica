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
    //Se ocupa de coger memoria
    void allocateMemory();
    //Se ocupa de liberar memoria
    void freeMemory();
    //Se ocupa de redondear a la potencia de 2
    void roundToPowerOf2(unsigned long int &t);

    unsigned long int tamal,tamaf;
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

};

#endif //VDINAMICO_H
