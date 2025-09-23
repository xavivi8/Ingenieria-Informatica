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

};

template<class T>
void VDinamico<T>::roundToPowerOf2(unsigned long int &t) {
    /*
        Comparo en binario que no coincidan los 1
        2 = 0010
        2-1=0001
        0010 y 0001 no comparten unos en cada bit
    */
    if ((t & (t - 1)) == 0) {
        return;
    }

    unsigned long int p;
    while(t<p) {
        //Desplazo a la izquierda un bit y guardo
        p<<=1;
    }
    t = p;
};

template<class T>
void VDinamico<T>::allocateMemory(){
    //Aumento la memoria a la potencia de 2
    tamaf *= 2;
    roundToPowerOf2(tamaf);

    //Creo un vector auxiliar
    T* aux = new T[tamaf];

    for(unsigned long int i = 0; i < tamal; ++i){
        aux[i] = v[i];
    }

    //Libero la memoria antigua
    delete[] v;

    //v que no apunta a nada hago que apunte a la dirección de memoria de aux
    v = aux;
};

/*
* Funciona igual que al aumentar la memoria pero ahora se liberara si el tamanyo logico (los elementos que tengo)
* es un tercio o menos que el tamanyo fisico (la capacidad total del vector)
* */
template<class T>
void VDinamico<T>::freeMemory() {
    if (tamal <= (tamaf / 3)) {
        unsigned long int newTamaf = tamaf / 2;
        T* aux = new T[newTamaf];

        for (unsigned long int i = 0; i < tamal; i++) {
            aux[i] = v[i];
        }

        delete[] v;

        v = aux;
        tamaf = newTamaf;
    }
}


template<class T>
void VDinamico<T>::VDinamico(){
    tamaf = 1;
    tamal = 0;
    // Inicializo el victor con tamanyo fisico 1 y vacio
    v = new T[tamaf];
};

template<class T>
void VDinamico<T>::VDinamico(unsigned long int tama){
    tamaf = tama;
    tamal = tama;
    //Redondeo a potencia de 2
    roundToPowerOf2(tamaf);
    v = new T[tamaf];
};

//Constructor copia
template<class T>
void VDinamico<T>::VDinamico(){

};

#endif //VDINAMICO_H
