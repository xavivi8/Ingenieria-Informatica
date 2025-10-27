//
// Created by jmart on 27/10/2025.
//
#include "../include/Avl.h"

/**
 * Metodos privados
 */

template<class T>
void Avl<T>::rotDer(Node *&p){
    //raiz actual (a)
    Node* q = p;
    //hijo del actual (b)
    Node* l = q->m_left;

    //rotacion
    p = l;
    q->m_left = l->m_right;
    l->m_right= q;

    //actualizo
    q->m_bal--
    if(l->m_bal<0) q->m_bal -= l->m_bal;

    l->m_bal--
    if (q->m_bal > 0) l->m_bal += q->m_bal;
};

template<class T>
void Avl<T>::rotIzq(Node *&p){
    //raiz actual (a)
    Node* q = p;
    //hijo del actual (b)
    Node* r = q->m_right;

    //rotacion
    p = r;
    q->m_right = r->m_left;
    r->m_left= q;

    //actualizo
    q->m_bal++;
    if(r->m_bal<0) q->m_bal += -r->m_bal;

    r->m_bal++;
    if (q->m_bal > 0) r->m_bal += q->m_bal;
};

template<class T>
int Avl<T>::insertNode(Node *&c, const T &data){
    if(!c){
        c = new Node(data);
        ++m_size;
        return 1;
    }

    unsigned int deltaH = 0;

    if(data < c->m_data){
        if(insertNode(c->m_left, data)){
            c->m_bal++;
            if(c->m_bal==1){
                deltaH=1;
            } else if(c->m_bal == 2){ //si pasa esto es que hay un desvalance por la izq
                if(c->m_left->m_bal < 0){
                    rotIzq(c->m_left);
                } else {
                    rotDer(c);
                }
                deltaH = 0;
            }
        }
    } else if(c->m_data < data){
        if(insertNode(c->m_right, data)){
            c->m_bal--;
            if(c->m_bal == -1){
                deltaH = 1;
            } else if(c->m_bal==-2){ //si pasa esto es que hay un desvalance por la der
                if(c->m_right->m_bal > 0){
                    rotDer(c->m_right);
                } else {
                    rotIzq(c);
                }
                deltaH = 0;
            }
        }
    } else {
        deltaH = 0;
    }
    return deltaH;
};

template<class T>
typename Avl<T>::Node* Avl<T>::copyAvl(Node* p) {
    if(!p) return nullptr;
    Node *n = new Node(p->m_data);
    n->m_bal = p->m_bal;
    n->m_left = copyAvl(p->m_left);
    n->m_right = copyAvl(p->m_right);
    return n;
};

template<class T>
void Avl<T>::destroyTree(Node*& p) {
    if(p){
        destroyTree(p->m_left);
        destroyTree(p->m_right);
        delete p;
        p = nullptr;
    }
}

/**
 * Metodos publicos
 */

template<class T>
bool Avl<T>::inserta(const T &dato){
    unsigned before = m_size;
    insertNode(m_root, dato);
    return m_size != before;
};