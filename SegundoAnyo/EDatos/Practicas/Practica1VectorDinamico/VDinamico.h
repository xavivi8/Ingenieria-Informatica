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
    void roundToPowerOf2(unsigned int &t);
    //Se ocupa de coger memoria
    void allocateMemory();
    //Se ocupa de liberar memoria
    void freeMemory();

    unsigned int tamaf,tamal;
    T *v;

public:
    VDinamico();
    VDinamico(unsigned int tama);
    VDinamico(const VDinamico<T> &orig);
    VDinamico(const VDinamico<T>& origen, unsigned int inicio, unsigned int num);
    ~VDinamico();

    VDinamico<T> &operator=(const VDinamico<T> &arr);
    T &operator[](unsigned int pos);

    void insert (const T &data, unsigned int pos=UINT_MAX);
    T remove (unsigned int pos=UINT_MAX);
    unsigned int size();
    void sort();
    unsigned int binarySearch(const T &data);
};

/*
* Metodos privados
* */
template<class T>
void VDinamico<T>::roundToPowerOf2(unsigned int &t) {
    if (t == 0) { 
        t = 1; 
        return; 
    }
    
    /*
        Comparo en binario que no coincidan los 1
        2 = 0010
        2-1=0001
        0010 y 0001 no comparten unos en cada bit
    */
    if ((t & (t - 1)) == 0) {
        return;
    }

    unsigned int p = 1;
    while(p < t) {
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

    for(unsigned int i = 0; i < tamal; ++i){
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
    if (tamal <= (tamaf / 3) && tamaf > 1) {
        unsigned int newTamaf = tamaf / 2;
        T* aux = new T[newTamaf];

        for (unsigned int i = 0; i < tamal; i++) {
            aux[i] = v[i];
        }

        delete[] v;

        v = aux;
        tamaf = newTamaf;
    }
}

/*
* Constructores
* */
//Importante los constructores no se le ponen void
template<class T>
VDinamico<T>::VDinamico(){
    tamaf = 1;
    tamal = 0;
    // Inicializo el victor con tamanyo fisico 1 y vacio
    v = new T[tamaf];
};

template<class T>
VDinamico<T>::VDinamico(unsigned int tama){
    tamaf = tama;
    tamal = tama;
    //Redondeo a potencia de 2
    roundToPowerOf2(tamaf);
    v = new T[tamaf];
};

//Constructor copia
template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig) {
    tamaf = orig.tamaf;
    tamal = orig.tamal;

    v = new T[tamaf];

    for (unsigned int i = 0; i < tamal; i++) {
        v[i] = orig.v[i];
    }
};

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen, unsigned int inicio, unsigned int num) {
    if (inicio >= origen.tamal) { //Compruebo que el inicio este en el vector origen
        throw std::out_of_range("Indice de inicio fuera de rango");
    } else if (inicio + num > origen.tamal) { //Compruebo que el rango que voy a copiar no exceda el tamanyo del vector origen
        throw std::out_of_range("El rango excede el tamaño del vector origen");
    } else {
        tamal = num;
        tamaf = num;
        roundToPowerOf2(tamaf);
        v = new T[tamaf];
        for (unsigned int i = 0; i < num; i++) {
            v[i] = origen.v[inicio + i];
        }
    }
};

//Constructor destructor
template<class T>
VDinamico<T>::~VDinamico() {
    if(v) {
        delete[] v; //libero memoria
        /**
         * Importante:
         * Hago que v ya no apunte a una direccion de memoria que ya no eciste
         */
        v = nullptr; 
        tamaf = 0;
        tamal = 0;
    }
};

/**
 * Operadores
 */
template<class T>
VDinamico<T> &VDinamico<T>::operator=(const VDinamico<T> &arr) {
    /**
     * compruebo que sean distintos los vectores dinamicos
     * this es un puntero que apunta al objeto que esta a la izquierda del =, es decir al objeto que llama al operador =
     */
    if (this != &arr) {
        delete[] v;
        tamaf = arr.tamaf;
        tamal = arr.tamal;
        roundToPowerOf2(tamaf);
        v = new T[tamaf];
        for (unsigned int i = 0; i < tamal; ++i) {
            v[i] = arr.v[i];
        }
    }
    /**
     * Importante:
     * *this es el propio objeto al que apunta el puntero this
     * cuando hago el return *this estoy devolviendo el propio objeto, lo estoy devolviendo por referencia
     */
    return *this;
};

template<class T>
T &VDinamico<T>::operator[](unsigned int pos) {
    if(pos>=tamal){
        throw std::out_of_range("Posicion fuera de rango");
    }
    return v[pos];
};

/**
 * Metodos clasicos de listas dinamicas
 */
template<class T>
void VDinamico<T>::insert(const T &data, unsigned int pos) {
    if (pos == UINT_MAX) {
        pos = tamal;
    } else if (pos > tamal) {
        throw std::out_of_range("Posicion fuera de rango");
    }
    if((tamal+1) == tamaf) {
        allocateMemory();
    }

    for(unsigned int i = tamal; i > pos; --i) {
        v[i] = v[i-1];
    }

    v[pos] = data;
    tamal++;
};

template<class T>
T VDinamico<T>::remove(unsigned int pos){
    if (tamal == 0) {
        throw std::out_of_range("Vector vacio");
    }

    if (pos == UINT_MAX) {
        pos = tamal - 1;
    } else if (pos >= tamal) {
        throw std::out_of_range("Posicion fuera de rango");
    }


    T aux = v[pos];

    for(unsigned int i = pos; (i+1) < tamal; ++i) {
        v[i] = v[i+1];
    }

    tamal--;

    if(tamal <= (tamaf/3)) {
        freeMemory();
    }

    return aux;
};

template<class T>
unsigned int VDinamico<T>::size(){
    return tamal;
};

template<class T>
void VDinamico<T>::sort() {
    
};

#endif //VDINAMICO_H
