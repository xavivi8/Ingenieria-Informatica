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
ListaEnlazada<T>::Iterator::Iterator(Node *aNode){
    m_node = aNode;
};

template<class T>
bool ListaEnlazada<T>::Iterator::isEnd() const {
    return m_node == nullptr;
};

template<class T>
void ListaEnlazada<T>::Iterator::next(){
    if(m_node != nullptr){
        m_node = m_node->next;
    }
};

template<class T>
T &ListaEnlazada<T>::Iterator::data() const{
    if(m_node == nullptr){
        throw std::out_of_range("Iterador fuera de rango");
    }
    return m_nodo->m_data;
};

template<class T>
ListaEnlazada<T>::Iterator::~Iterator() = default;

/**
 * 
 * ListaEnlazada
 * 
 */
/**
 * Metodos privados
 */

template<class T>
void ListaEnlazada<T>::clear(){
    Node *current = m_head;
    Node *nextNode;

    while(current != nullptr){
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
};

/**
 * Constructor
 */

template<class T>
ListaEnlazada<T>::ListaEnlazada(){
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
};

template<class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T> &aux){
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;

    Node *current = aux.m_head;
    while(current != nullptr){
        insertAtEnd(current->m_dato);
        current = current->next;
    }
};

template<class T>
ListaEnlazada<T>::~ListaEnlazada(){
    clear();
}

/**
 * Operadores
 */

template<class T>
ListaEnlazada<T> &ListaEnlazada<T>::operator=(const ListaEnlazada<T> &aux) {
    if (this == &aux) {
        return *this;
    }

    clear();

    Node *current = aux.m_head;
    while(current != nullptr){
        insertAtEnd(current->m_data);
        current = current->next;
    }

    return *this;
};

template<class T>
ListaEnlazada<T> ListaEnlazada<T>::operator+(const ListaEnlazada<T> &aux){
    ListaEnlazada<T> result;

    Node *current = m_head;
    while(current != nullptr){
        result.insertAtEnd(current->m_data);
        current = current->next;
    }

    current = aux.m_head;
    while(current != nullptr){
        result.insertAtEnd(current->m_data);
        current = current->next;
    }

    return result;
}

/**
 * Iterador
 */

template<class T>
ListaEnlazada<T>::Iterator ListaEnlazada<T>::iterator() const{
    return Iterator(m_head);
};