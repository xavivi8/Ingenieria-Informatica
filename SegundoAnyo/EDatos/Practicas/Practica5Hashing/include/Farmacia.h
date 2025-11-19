//
// Created by jmart on 27/10/2025.
//

#ifndef FARMACIA_H
#define FARMACIA_H

#include "../include/PaMedicamento.h"
#include "../include/Stock.h"
#include <string>
#include <set>
#include <vector>


class MediExpress;
class Farmacia{
    std::string m_cif;
    std::string m_province;
    std::string m_city;
    std::string m_name;
    std::string m_address;
    std::string m_postalCode;

    MediExpress* m_linkMedi{nullptr};
    std::set<Stock> m_order;

    /**
     * @brief Realiza un pedido de n unidades del medicamento con id idNum
     * @param idNum Identificador numerico del medicamento
     * @param n Numero de unidades a pedir
     * @post Realiza un pedido de n unidades del medicamento con id idNum
     */
    void pedidoMedicam(int idNum, int n);
    /**
     * @brief Busca un medicamento en el stock de la farmacia por su identificador numerico
     * @param id_num Identificador numerico del medicamento
     * @return Devuelve el numero de unidades en stock del medicamento, o -1 si no se encuentra
     */
    int buscaMedicamID(int id_num) const;


    public:
    /**
     * @brief Constructor por defecto
     * @post Inicializa los atributos a valores por defecto
     */
    Farmacia() = default;
    /**
     * @brief Constructor con parametros
     * @param cif CIF de la farmacia
     * @param province Provincia donde se encuentra la farmacia
     * @param city Ciudad donde se encuentra la farmacia
     * @param name Nombre de la farmacia
     * @param address Direccion de la farmacia
     * @param postalCode Codigo postal de la farmacia
     * @param med Puntero a la instancia de MediExpress
     * @post Inicializa los atributos con los valores pasados por parametro
     */
    Farmacia(const std::string &cif,
             const std::string &province,
             const std::string &city,
             const std::string &name,
             const std::string &address,
             const std::string &postalCode,
             MediExpress* med);
    /**
     * @brief Destructor
     * @post Destructor por defecto
     */
    ~Farmacia() = default;

    /**
     * @brief Operador menor que
     * @param farma Objeto Farmacia con el que se va a comparar
     * @return Devuelve true si el objeto que llama al operador es menor que el objeto pasado por parametro, false en caso contrario
     */
    bool operator<(const Farmacia &farma) const;
    /**
     * @brief Operador de salida
     * @param os Stream de salida
     * @param f Objeto Farmacia que se va a imprimir
     * @return Devuelve el stream de salida
     */
    friend std::ostream& operator<<(std::ostream& os, const Farmacia& f);

    /**
     * @brief Busca medicamentos en el stock de la farmacia por su nombre
     * @param nombre Nombre del medicamento
     * @return Devuelve un vector con punteros a los medicamentos que coinciden con el nombre dado
     */
    std::vector<PaMedicamento*> buscaMedicamNombre(const std::string &nombre);
    /**
     * @brief Añade un nuevo stock de un medicamento a la farmacia
     * @param pa Puntero al medicamento
     */
    void nuevoStock(PaMedicamento* pa, int n);
    /**
     * @brief Compra n unidades del medicamento con id id_num
     * @param id_num Identificador numerico del medicamento
     * @param n Numero de unidades a comprar
     * @param result Puntero al medicamento comprado
     * @return Devuelve el numero de unidades compradas, o -1 si no se ha podido comprar
     */
    int comprarMedicam(int id_num, int n, PaMedicamento* &result);
    /**
     * @brief Elimina el stock del medicamento con id idNum
     * @param idNum Identificador numerico del medicamento
     * @return Devuelve true si se ha podido eliminar el stock, false en caso contrario
     */
    bool eliminarStock(int idNum);
    /**
     * @brief Obtiene el stock del medicamento con id id_num
     * @param id_num Identificador numerico del medicamento
     * @return Devuelve el numero de unidades en stock del medicamento, o -1 si no se encuentra
     */
    int getStock(int id_num) const;

    //Getters
    /**
     * @brief Getters
     * @return Devuelve el valor del atributo
     */
    std::string getCif() const;
    /**
     * @brief Getter de la provincia
     * @return Devuelve la provincia donde se encuentra la farmacia
     */
    std::string getProvince() const;
    /**
     * @brief Getter de la ciudad
     * @return Devuelve la ciudad donde se encuentra la farmacia
     */
    std::string getCity() const;
    /**
     * @brief Getter del nombre
     * @return Devuelve el nombre de la farmacia
     */
    std::string getName() const;
    /**
     * @brief Getter de la direccion
     * @return Devuelve la direccion de la farmacia
     */
    std::string getAddress() const;
    /**
     * @brief Getter del codigo postal
     * @return Devuelve el codigo postal de la farmacia
     */
    std::string getPostalCode() const;
    /**
     * @brief Getter del puntero a MediExpress
     * @return Devuelve un puntero a la instancia de MediExpress
     */
    MediExpress* getLinkMedi() const;

    //Setters
    /**
     * @brief Setters
     * @param valor Nuevo valor para el atributo
     * @post Actualiza el valor del atributo
     */
    void setCif(const std::string &cif);
    /**
     * @brief Setter de la provincia
     * @param province Nueva provincia donde se encuentra la farmacia
     * @post Actualiza la provincia donde se encuentra la farmacia
     */
    void setProvince(const std::string &province);
    /**
     * @brief Setter de la ciudad
     * @param city Nueva ciudad donde se encuentra la farmacia
     * @post Actualiza la ciudad donde se encuentra la farmacia
     */
    void setCity(const std::string &city);
    /**
     * @brief Setter del nombre
     * @param name Nuevo nombre de la farmacia
     * @post Actualiza el nombre de la farmacia
     */
    void setName(const std::string &name);
    /**
     * @brief Setter de la direccion
     * @param address Nueva direccion de la farmacia
     * @post Actualiza la direccion de la farmacia
     */
    void setAddress(const std::string &address);
    /**
     * @brief Setter del codigo postal
     * @param postalCode Nuevo codigo postal de la farmacia
     * @post Actualiza el codigo postal de la farmacia
     */
    void setPostalCode(const std::string &postalCode);
    /**
     * @brief Setter del puntero a MediExpress
     * @param medi Puntero a la instancia de MediExpress
     * @post Actualiza el puntero a la instancia de MediExpress
     */
    void setLinkMedi(MediExpress *medi);

};

#endif //FARMACIA_H
