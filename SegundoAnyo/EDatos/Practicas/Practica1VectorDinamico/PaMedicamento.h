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
    bool &operator==(const PaMedicamento &object);
    bool &operator<(const PaMedicamento &object);
    
    //Getters
    //Al poner al final el const se promete que esa funcion no modificara atributos
    int getIdNum() const;
    std::string getIdAlpha() const;
    std::string getNombre() const;

    //Setters
    void setIdNum(int id_num);
    void setIdAlpha(std::string id_alpha);
    void setNombre(std::string nombre);
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

#endif //PAMEDICAMENTO_H
