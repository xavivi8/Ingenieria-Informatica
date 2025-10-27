//
// Created by jmart on 27/10/2025.
//

#ifndef AVL_H
#define AVL_H

#include "../include/VDinamico.h"

template <class T>
class Avl {

    //Declaración del nodo local
    class Node {
    public:
        Node *m_left;
        Node *m_right;
        char m_bal; // -1, 0 , 1 para un árbol avl
        T m_data;

        Node(const T &element): m_left(0), m_right(0), m_bal(0), m_data(ele){}
        Node(const Node &orig): m_left(orig.m_left), m_right(orig.m_right), m_bal(orig.m_bal), m_data(orig.dato){}
    };

    Node *m_root;
    unsigned int m_size;

    void inorder(Node p, int level, Vdinamico<T> &v);
    
    Node *findKey ( const T &data, Node *p);
    int insertNode(Node* &c, const T &data);
    
    void destroyTree(Node* &p);
    
    void rotDer(Node* &p);
    void rotIzq(Node* &p);
    
    Node* copyAvl(Node *p);

    unsigned int countElements(Node* p);

    unsigned hightHelper(Node* p);

public:
               
    Avl() : m_root(0), m_size(0) {}
    Avl(const Avl<T>& orig);

    Avl<T>& operator=(const Avl<T>& orig);

    T* buscaRec (const T &dato);
    T* buscaIt(const T &dato);
    bool inserta(const T &dato);
  
    unsigned int numElementos();
    unsigned int altura();

    unsigned int getSize(){ return m_size;};

    VDinamico<T*> recorreInorden() {
        VDinamico<T*> v;
        inorden(m_root,0,v);
        return v;
    };

    ~Avl(){
        destroyTree(m_root);
    };
};

#include "../src/Avl.tpp"
#endif //AVL_H
