//
// Created by jmart on 08/10/2025.
//
#include "../include/ListaEnlazada.h"

/**
 * 
 * Iterador
 * 
 */

template<class T>
ListaEnlazada<T>::Iterador::Iterador(Nodo *aNodo){
    nodo = aNodo;
};

template<class T>
bool ListaEnlazada<T>::Iterador::fin() const {
    return nodo == nullptr;
};

template<class T>
void ListaEnlazada<T>::Iterador::siguiente(){
    if(nodo != nullptr){
        nodo = nodo->sig;
    }
};

template<class T>
T &ListaEnlazada<T>::Iterador::dato() const{
    if(nodo == nullptr){
        throw std::out_of_range("Iterador fuera de rango");
    }
    return nodo->m_dato;
};

template<class T>
ListaEnlazada<T>::Iterador::~Iterador() = default;

/**
 * 
 * ListaEnlazada
 * 
 */

/**
 * Constructor
 */
template<class L>
ListaEnlazada<L>::ListaEnlazada(){
    cabecera = 0;
    cola = 0;
    m_tama = 0;
};

template<class L>
ListaEnlazada<L>::ListaEnlazada(const ListaEnlazada<L> &aux){
    Nodo<L> *i = aux.cabecera;
    cabecera = 0;
    cola = 0;
    m_tama = aux.m_tama;

    while(i){
        Nodo<L> *newNodo;
        newNodo = new Nodo<N>(i->dato, 0);

        if(cola != 0){
            cola->sig = newNodo;
        }

        if(cabecera == 0){
            cabecera = newNodo;
        }

        cola = newNodo;

        i = i->sig;
    }
};

/**
 * Operadores
 */

template<class L>
ListaEnlazada<L> &ListaEnlazada<L>::operator=(const ListaEnlazada<L> &aux){
    if(this != aux){

    }
};