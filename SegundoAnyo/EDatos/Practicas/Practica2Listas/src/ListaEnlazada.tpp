//
// Created by jmart on 08/10/2025.
//
#include "../include/ListaEnlazada.h"

/**
 * 
 * Nodo
 * 
 */

template<class L>
template<class N>
ListaEnlazada<L>::Nodo<N>::Nodo(const N &aDato, Nodo *asig){
    m_dato = aDato;
    sig = asig;
}

/**
 * 
 * Iterador
 * 
 */

template<class L>
template<class I>
ListaEnlazada<L>::Iterador<I>::Iterador(Nodo<L> *aNodo){
    nodo = aNodo;
}

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