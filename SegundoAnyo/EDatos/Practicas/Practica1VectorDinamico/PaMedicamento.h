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

#endif //PAMEDICAMENTO_H
