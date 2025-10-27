//
// Created by jmart on 27/10/2025.
//
#include "../include/Avl.h"

/**
 * Metodos privados
 */

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
