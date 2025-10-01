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
    unsigned int tamaf;
    unsigned int tamal;
    T *v;

    //Se ocupa de redondear a la potencia de 2
    void roundToPowerOf2(unsigned int &t);
    //Se ocupa de coger memoria
    void allocateMemory();
    //Se ocupa de liberar memoria
    void freeMemory();

public:
    VDinamico();
    VDinamico(unsigned int tamalog, T &dato);
    VDinamico(const VDinamico<T> &orig);
    VDinamico(const VDinamico<T>& origen, unsigned int inicio, unsigned int num);
    ~VDinamico();

    VDinamico<T> &operator=(const VDinamico<T> &arr);
    T &operator[](unsigned int index);

    void insert (const T &data, unsigned int pos=UINT_MAX);
    T remove (unsigned int index=UINT_MAX);
    unsigned int size();
    void sort();
    unsigned int binarySearch(const T &data);
};

/*
* Metodos privados
* */
/**
 * @brief redondea un numero a la potencia de 2 mas cercana
 * @param t Numero que se va a redondear a la potencia de 2
 * @post Redondea el numero t a la potencia de 2 mas cercana
 */
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

/**
 * @brief Aumenta la memoria del vector dinamico
 * @post Aumenta la memoria del vector dinamico al doble
 */
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
/**
 * @brief Reduce la memoria del vector dinamico
 * @post Reduce la memoria del vector dinamico si el tamanyo logico es un tercio o menos que el tamanyo fisico
 */
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
/**
 * @brief Constructor por defecto
 * @post Constructor por defecto que inicializa el vector con tamanyo fisico 1 y tamanyo logico vacio 
 */
template<class T>
VDinamico<T>::VDinamico(){
    tamaf = 1;
    tamal = 0;
    // Inicializo el victor con tamanyo fisico 1 y vacio
    v = new T[tamaf];
};

/**
 * @brief Constructor con parametros
 * @param tama Tamanyo logico inicial del vector
 * @param dato Dato con el que se inicializan las posiciones del vector
 * @post Constructor con parametros que inicializa el vector con tamanyo logico tama y con los elementos iguales a dato
 */
template<class T>
VDinamico<T>::VDinamico(unsigned int tama, T &dato){
    tamaf = tama;
    tamal = tama;
    //Redondeo a potencia de 2
    roundToPowerOf2(tamaf);
    v = new T[tamaf];

    for(unsigned int i = 0; i < tamal; ++i){
        v[i] = dato;
    }
};

//Constructor copia
/**
 * @brief Constructor copia
 * @param orig Vector dinamico que se va a copiar
 * @post Copia el vector dinamico orig en el vector que llama al constructor
 */
template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig) {
    tamaf = orig.tamaf;
    tamal = orig.tamal;

    v = new T[tamaf];

    for (unsigned int i = 0; i < tamal; i++) {
        v[i] = orig.v[i];
    }
};

/**
 * @brief Constructor copia de un rango de elementos
 * @throws std::out_of_range si el indice de inicio es mayor o igual que el tamanyo logico del vector origen
 * @throws std::out_of_range si el rango que se va a copiar excede el tamanyo logico del vector origen
 * @param origen Vector dinamico del que se va a copiar
 * @param inicio Indice del vector origen desde el que se va a empezar a copiar
 * @param num Numero de elementos que se van a copiar desde el vector origen
 * @post Constructor copia de un rango de elementos
 */
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
/**
 * @brief Destructor
 * @post Destructor del vector dinamico
 */
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
/**
 * @brief operador igual
 * @param arr Vector dinamico que se va a copiar
 * @return Devuelve una referencia al propio objeto
 * @post Sobrecarga del operador de asignacion
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

/**
 * @brief Acceso a los elementos del vector dinamico
 * @throws std::out_of_range si el indice es mayor o igual que el tamanyo logico
 * @param index Indice del vector dinamico
 * @return Devuelve una referencia al elemento en la posicion index
 * @post Sobrecarga del operador de acceso []
 */
template<class T>
T &VDinamico<T>::operator[](unsigned int index) {
    if(index>=tamal){
        throw std::out_of_range("Posicion fuera de rango");
    }
    return v[index];
};

/**
 * Metodos clasicos de listas dinamicas
 */
/**
 * @brief Inserta un elemento en el vector dinamico
 * @throws std::out_of_range si el indice es mayor que el tamanyo logico
 * @param data Dato que se va a insertar
 * @param index Indice en el que se va a insertar el dato, si no se especifica se inserta al final
 * @post Inserta un elemento en la posicion index, si no se especifica se inserta al final
 */
template<class T>
void VDinamico<T>::insert(const T &data, unsigned int index) {
    if (index == UINT_MAX) {
        index = tamal;
    } else if (index > tamal) {
        throw std::out_of_range("Posicion fuera de rango");
    }
    if(tamal == tamaf) {
        allocateMemory();
    }

    for( int i = tamal; i > index; --i) {
        v[i] = v[i-1];
    }

    v[index] = data;
    tamal++;
};

/**
 * @brief Elimina un elemento del vector dinamico
 * @throws std::out_of_range si el vector esta vacio o el indice es mayor que el tamanyo logico o esta vacio
 * @param index Indice del elemento que se va a eliminar, si no se especifica se elimina el ultimo
 * @return Devuelve el elemento eliminado
 * @post Elimina el elemento en la posicion index, si no se especifica se elimina el ultimo
 */
template<class T>
T VDinamico<T>::remove(unsigned int index){

    if(tamal <= (tamaf/3)) {
        freeMemory();
    }

    if (tamal == 0) {
        throw std::out_of_range("Vector vacio");
    }

    if (index == UINT_MAX) {
        index = tamal - 1;
    } else if (index >= tamal) {
        throw std::out_of_range("Posicion fuera de rango");
    }


    T aux = v[index];

    for(unsigned int i = index; (i+1) < tamal; ++i) {
        v[i] = v[i+1];
    }

    tamal--;

    return aux;
};

/**
 * @brief como un getter
 * @return Devuelve el tamanyo logico del vector
 * @post Devuelve el tamanyo logico del vector
 */
template<class T>
unsigned int VDinamico<T>::size(){
    return tamal;
};

/**
 * @brief tipica funcion de ordenacion
 * @post Ordena el vector dinamico
 */
template<class T>
void VDinamico<T>::sort() {
    if (tamal > 1) {
        std::sort(v, v + tamal);
    }
};

/**
 * @brief Busca un elemento en el vector dinamico mediante busqueda dicotomica
 * @pre El vector debe estar ordenado
 * @param data Dato que se va a buscar
 * @return Devuelve el indice del elemento buscado, si no se encuentra devuelve -1
 * @post Busca un elemento en el vector dinamico mediante busqueda binaria
 */
template<class T>
unsigned int VDinamico<T>::binarySearch(const T &data){
    int low = 0;
    int high = tamal - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if(v[mid] == data){
            return mid;
        } else if(v[mid] < data) {
            low = mid + 1;
        } else {
            high = mid -1;
        }
    }

    return -1;
};

#endif //VDINAMICO_H
