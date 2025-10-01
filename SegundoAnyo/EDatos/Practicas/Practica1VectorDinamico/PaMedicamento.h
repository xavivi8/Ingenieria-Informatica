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
    PaMedicamento(int id_num, std::string id_alpha, std::string name);
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
    void setName(std::string name);
};

/**
 * Constructores
 */
/**
 * @brief Constructor por defecto
 * @post Constructor por defecto que inicializa los atributos a valores por defecto
 */
PaMedicamento::PaMedicamento(){
    id_num = 0;
    id_alpha = "";
    nombre = "";
};

/**
 * @brief Constructor con parametros
 * @param idNum Identificador numerico del medicamento
 * @param idAlpha Identificador alfanumerico del medicamento
 * @param name Nombre del medicamento
 * @post Constructor con parametros que inicializa los atributos con los valores pasados por parametro
 */
PaMedicamento::PaMedicamento(int idNum, std::string idAlpha, std::string name){
    id_num = idNum;
    id_alpha = idAlpha;
    nombre = name;
};

/**
 * @brief Destructor
 * @post Destructor que libera la memoria ocupada por los atributos
 */
PaMedicamento::~PaMedicamento(){
    id_num = 0;
    id_alpha.clear();
    nombre.clear();
};

/**
 * Operadores
 */
/**
 * @brief operador igual igual
 * @param object Objeto PaMedicamento con el que se va a comparar
 * @return Devuelve true si los objetos son iguales, false en caso contrario
 */
bool PaMedicamento::operator==(const PaMedicamento &object) const {
    bool equal = false;

    if(id_num == object.id_num){
        equal = true;
    }

    return equal;
}

/**
 * @brief operador menor que
 * @param object Objeto PaMedicamento con el que se va a comparar
 * @return Devuelve true si el objeto que llama al operador es menor que el objeto pasado por parametro, false en caso contrario
 */
bool PaMedicamento::operator<(const PaMedicamento &object) const{
    return (id_num < object.id_num);
};

/**
 * Getters
 */
/**
 * @brief Getter del identificador numerico
 * @return Devuelve el identificador numerico del medicamento
 */
int PaMedicamento::getIdNum() const{
    return id_num;
};

/**
 * @brief Getter del identificador alfanumerico
 * @return Devuelve el identificador alfanumerico del medicamento
 */
std::string PaMedicamento::getIdAlpha() const{
    return id_alpha;
};

/**
 * @brief Getter del nombre del medicamento
 * @return Devuelve el nombre del medicamento
 */
std::string PaMedicamento::getName() const{
    return nombre;
};

/**
 * Setters
 */
/**
 * @brief Setter del identificador numerico
 * @param num Nuevo identificador numerico del medicamento
 * @post Actualiza el identificador numerico del medicamento
 */
void PaMedicamento::setIdNum(int num){
    id_num = num;
};

/**
 * @brief Setter del identificador alfanumerico
 * @param alphanumeric Nuevo identificador alfanumerico del medicamento
 * @post Actualiza el identificador alfanumerico del medicamento
 */
void PaMedicamento::setIdAlpha(std::string alphanumeric){
    id_alpha = alphanumeric;
};

/**
 * @brief Setter del nombre del medicamento
 * @param name Nuevo nombre del medicamento
 * @post Actualiza el nombre del medicamento
 */
void PaMedicamento::setName(std::string name){
    nombre = name;
};

#endif //PAMEDICAMENTO_H
