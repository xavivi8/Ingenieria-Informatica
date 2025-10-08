//
// Created by jmart on 08/10/2025.
//

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

template<class T>
class ListaEnlazada {

    //declaracion del Nodo local
    template<class X>
    class Nodo {

    public:
        X dato;
        Nodo *sig;
        Nodo(const X &aDato, Nodo *aSig = 0):
                dato(aDato), sig(aSig) {}
        ~Nodo() {}
    };

    Nodo<T> *cabecera, *cola;
    unsigned tama;

public:

    //declaracion del iterador
    template <class U>
    class Iterador {
        Nodo<T> *nodo;
    public:
        friend class ListaEnlazada<T>;

        Iterador(Nodo<T> *aNodo=0) : nodo(aNodo) {}

        bool fin() { return nodo == 0; }

        void siguiente() {
            nodo = nodo->sig;
        }
        // Nodo<T> *vernodo() { return nodo; }
        T &dato() { return nodo->dato; }
        ~Iterador() {}
    };

    ListaEnlazada() : cabecera(0), cola(0), tama(0) {}
    ~ListaEnlazada();
    ListaEnlazada(const ListaEnlazada<T> &l);
    ListaEnlazada &operator=(const ListaEnlazada<T> &l);
    Iterador iterador() const;
    void insertarInicio(const T &dato);
    void insertarFin(const T &dato);
    void insertaDelante(Iterador &p, const T &dato);
    void insertaDetras( Iterador &p, const T &dato);
    void borrarInicio();
    void borrarFinal();
    void borra(Iterador &i);
    int tam(){ return tama;}
    void destruyeLista();  //puede/debe ir en private

    ListaEnlazada<T>& concatena(const ListaEnlazada<T> &l);
    ListaEnlazada<T> operator+(const ListaEnlazada<T> &l);

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

#endif //LISTAENLAZADA_H
