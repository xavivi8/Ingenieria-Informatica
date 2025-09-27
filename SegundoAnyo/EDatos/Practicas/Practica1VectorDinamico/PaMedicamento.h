//
// Created by jmart on 25/09/2025.
//

#ifndef PAMEDICAMENTO_H
#define PAMEDICAMENTO_H

#include <string>

class PaMedicamento{
private:
    int id_num;
    std::string id_alpha;
    std::string nombre;

public:
    PaMedicamento();
    PaMedicamento(int id_num, std::string id_alpha, std::string nombre);
    /**
     * Prefuntar si se podria usar "~PaMedicamento() = default;" para que el contructor lo haga automaticamente
     * porque como no hay nada dinamico nos podriamos ahorar el hacerlo manual
     */
    ~PaMedicamento();

    //Operators
    //Al poner al final el const se promete que esa funcion no modificara atributos
    bool operator==(const PaMedicamento &object) const;
    bool operator<(const PaMedicamento &object) const;
    
    //Getters
    int getIdNum() const;
    std::string getIdAlpha() const;
    std::string getName() const;

    //Setters
    void setIdNum(int id_num);
    void setIdAlpha(std::string id_alpha);
    void setName(std::string nombre);
};

/**
 * Constructores
 */
PaMedicamento::PaMedicamento(){
    id_num = 0;
    id_alpha = "";
    nombre = "";
};

PaMedicamento::PaMedicamento(int idNum, std::string idAlpha, std::string name){
    id_num = idNum;
    id_alpha = idAlpha;
    nombre = name;
};

PaMedicamento::~PaMedicamento(){
    id_num = 0;
    id_alpha.clear();
    nombre.clear();
};

/**
 * Operadores
 */
bool PaMedicamento::operator==(const PaMedicamento &object) const {
    bool equal = false;

    if(id_num == object.id_num && id_alpha == object.id_alpha && nombre == object.nombre){
        equal = true;
    }

    return equal;
}

bool PaMedicamento::operator<(const PaMedicamento &object) const{
    return (id_num < object.id_num);
};

/**
 * Getters
 */
int PaMedicamento::getIdNum() const{
    return id_num;
};

std::string PaMedicamento::getIdAlpha() const{
    return id_alpha;
};

std::string PaMedicamento::getName() const{
    return nombre;
};

#endif //PAMEDICAMENTO_H
