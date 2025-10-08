//
// Created by jmart on 08/10/2025.
//

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

template<class L>
class ListaEnlazada {

    //declaracion del Nodo local
    template<class N>
    class Nodo {

    public:
        N m_dato;
        Nodo *sig;
        Nodo(const N &aDato, Nodo *aSig = 0)
        ~Nodo() {}
    };

    Nodo<L> *cabecera, *cola;
    unsigned m_tama;

public:

    //declaracion del iterador
    template <class I>
    class Iterador {
        Nodo<L> *nodo;
    public:
        friend class ListaEnlazada<L>;

        Iterador(Nodo<L> *aNodo=0)

        bool fin() { return nodo == 0; }

        void siguiente() {
            nodo = nodo->sig;
        }
        // Nodo<T> *vernodo() { return nodo; }
        T &dato() { return nodo->dato; }
        ~Iterador() {}
    };

    ListaEnlazada();
    ListaEnlazada(const ListaEnlazada<L> &aux);
    ~ListaEnlazada();
    ListaEnlazada &operator=(const ListaEnlazada<L> &aux);
    ListaEnlazada<L> operator+(const ListaEnlazada<L> &aux);
    Iterador iterador() const;
    void insertarInicio(const T &dato);
    void insertarFin(const T &dato);
    void insertaDelante(Iterador &p, const T &dato);
    void insertaDetras( Iterador &p, const T &dato);
    void borrarInicio();
    void borrarFinal();
    void borra(Iterador &i);
    int tam(){ return m_tama;}
    void destruyeLista();  //puede/debe ir en private

    ListaEnlazada<L>& concatena(const ListaEnlazada<L> &l);

    L &inicio(){ 
        if (!cabecera) 
            throw std::invalid_argument("No existe ese elemento");
        return cabecera->dato;
    };
    L &fin(){
        if (!cola) 
            throw std::invalid_argument("No existe ese elemento");
        return cola->dato;
    };
};

#include "../src/ListaEnlazada.tpp"
#endif //LISTAENLAZADA_H
