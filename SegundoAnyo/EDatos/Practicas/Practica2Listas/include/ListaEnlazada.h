//
// Created by jmart on 08/10/2025.
//

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

template<class T>
class ListaEnlazada {

    //declaracion deT Nodo local
    class Nodo {

    public:
        T m_dato;
        Nodo *sig;
        Nodo(const T &aDato, Nodo *aSig = 0): dato(valor), sig(siguiente) {};
        ~Nodo() {};
    };

    Nodo  *cabecera, *cola;
    unsigned m_tama;

public:

    //declaracion deT iterador
    class Iterador {
        Nodo  *nodo;
    public:
        friend class ListaEnlazada<T> ;

        Iterador(Nodo  *aNodo=0);
        bool fin() const;
        void siguiente();
        T &dato() const;
        ~Iterador();
    };

    ListaEnlazada();
    ListaEnlazada(const ListaEnlazada<T>  &aux);
    ~ListaEnlazada();
    ListaEnlazada &operator=(const ListaEnlazada<T>  &aux);
    ListaEnlazada<T>  operator+(const ListaEnlazada<T>  &aux);
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

    ListaEnlazada<T> & concatena(const ListaEnlazada<T>  &l);

    T &inicio(){ 
        if (!cabecera) 
            throw std::invalid_argument("No existe ese elemento");
        return cabecera->dato;
    };
    T &fin(){
        if (!cola) 
            throw std::invalid_argument("No existe ese elemento");
        return cola->dato;
    };
};

#include "../src/ListaEnlazada.tpp"
#endif //LISTAENLAZADA_H
