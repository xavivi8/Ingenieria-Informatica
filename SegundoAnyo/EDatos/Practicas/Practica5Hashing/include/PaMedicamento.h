//
// Created by jmart on 25/09/2025.
//

#ifndef PAMEDICAMENTO_H
#define PAMEDICAMENTO_H

#include <string>

class Laboratorio;
class PaMedicamento{
private:
    int m_id_num;
    std::string m_id_alpha;
    std::string m_name;
    Laboratorio *m_servidoPor{nullptr};

public:
    /**
     * @brief Constructor por defecto
     * @post Constructor por defecto que inicializa los atributos a valores por defecto
     */
    PaMedicamento();
    /**
     * @brief Constructor con parametros
     * @param idNum Identificador numerico del medicamento
     * @param idAlpha Identificador alfanumerico del medicamento
     * @param name Nombre del medicamento
     * @post Constructor con parametros que inicializa los atributos con los valores pasados por parametro
     */
    PaMedicamento(int id_num, std::string id_alpha, std::string name);
    /**
     * @brief Destructor
     * @post Destructor que libera la memoria ocupada por los atributos
     */
    ~PaMedicamento();

    /**
     * @brief operador igual igual
     * @param object Objeto PaMedicamento con el que se va a comparar
     * @return Devuelve true si los objetos son iguales, false en caso contrario
     */
    bool operator==(const PaMedicamento &object) const;
    /**
     * @brief operador menor que
     * @param object Objeto PaMedicamento con el que se va a comparar
     * @return Devuelve true si el objeto que llama al operador es menor que el objeto pasado por parametro, false en caso contrario
     */
    bool operator<(const PaMedicamento &object) const;
    
    //Getters
    /**
     * @brief Getter del identificador numerico
     * @return Devuelve el identificador numerico del medicamento
     */
    int getIdNum() const;
    /**
     * @brief Getter del identificador alfanumerico
     * @return Devuelve el identificador alfanumerico del medicamento
     */
    std::string getIdAlpha() const;
    /**
     * @brief Getter del nombre del medicamento
     * @return Devuelve el nombre del medicamento
     */
    std::string getName() const;
    /**
     * @brief Getter del laboratorio que sirve el medicamento
     * @return Devuelve un puntero al laboratorio que sirve el medicamento
     */
    Laboratorio *getServidoPor() const;

    //Setters
    /**
     * @brief Setter del identificador numerico
     * @param num Nuevo identificador numerico del medicamento
     * @post Actualiza el identificador numerico del medicamento
     */
    void setIdNum(int id_num);
    /**
     * @brief Setter del identificador alfanumerico
     * @param alphanumeric Nuevo identificador alfanumerico del medicamento
     * @post Actualiza el identificador alfanumerico del medicamento
     */
    void setIdAlpha(std::string id_alpha);
    /**
     * @brief Setter del nombre del medicamento
     * @param name Nuevo nombre del medicamento
     * @post Actualiza el nombre del medicamento
     */
    void setName(std::string name);
    /**
     * @brief Setter del laboratorio que sirve el medicamento
     * @param lab Puntero al laboratorio
     * @post Actualiza el puntero al laboratorio que sirve el medicamento
     */
    void setServidoPor(Laboratorio *lab);
};

#endif //PAMEDICAMENTO_H
