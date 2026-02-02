//
// Created by jmart on 08/10/2025.
//

#ifndef LABORATORIO_H
#define LABORATORIO_H

#include <string>
#include <ostream>

class Laboratorio{
private:
    unsigned int m_id;
    std::string m_lab_name;
    std::string m_address;
    std::string m_postal_code;
    std::string m_city;

public:
    /**
     * @brief Constructor por defecto
     */
    Laboratorio();
    /**
     * @brief Constructor parametrizado
     * @param id Identificador del laboratorio
     * @param nombre_lab Nombre del laboratorio
     * @param direccion Dirección del laboratorio
     * @param cod_postal Código postal del laboratorio
     * @param localidad Localidad del laboratorio
     */
    Laboratorio(int id,
                const std::string &nombre_lab,
                const std::string &direccion,
                const std::string &cod_postal,
                const std::string &localidad);

    /**
     * @brief Destructor
     */
    ~Laboratorio() = default;  // no hay recursos dinámicos, por ende se puede usar el default

    /**
     * @brief Operador de igualdad
     * @param lab Laboratorio a comparar
     * @return Devuelve true si los laboratorios son iguales, false en caso contrario
     */
    bool operator==(const Laboratorio &lab) const;
    /**
     * @brief Operador de salida
     * @param os Flujo de salida
     * @param l Laboratorio a mostrar
     * @return Devuelve el flujo de salida
     */
    friend std::ostream& operator<<(std::ostream& os, const Laboratorio& l);

    // Getters
    /**
     * @brief Devuelve el identificador del laboratorio
     * @return Devuelve el identificador del laboratorio
     */
    int getId() const;
    /**
     * @brief Devuelve el nombre del laboratorio
     * @return Devuelve el nombre del laboratorio
     */
    std::string getLabName() const;
    /**
     * @brief Devuelve la dirección del laboratorio
     * @return Devuelve la dirección del laboratorio
     */
    std::string getAddress() const;
    /**
     * @brief Devuelve el código postal del laboratorio
     * @return Devuelve el código postal del laboratorio
     */
    std::string getPostalCode() const;
    /**
     * @brief Devuelve la localidad del laboratorio
     * @return Devuelve la localidad del laboratorio
     */
    std::string getCity() const;

    // Setters
    /**
     * @brief Establece el identificador del laboratorio
     * @param id Identificador del laboratorio
     */
    void setId(int id);
    /**
     * @brief Establece el nombre del laboratorio
     * @param nombre_lab Nombre del laboratorio
     */
    void setLabName(const std::string &nombre_lab);
    /**
     * @brief Establece la dirección del laboratorio
     * @param direccion Dirección del laboratorio
     */
    void setAddress(const std::string &direccion);
    /**
     * @brief Establece el código postal del laboratorio
     * @param cod_postal Código postal del laboratorio
     */
    void setPostalCode(const std::string &cod_postal);
    /**
     * @brief Establece la localidad del laboratorio
     * @param localidad Localidad del laboratorio
     */
    void setCity(const std::string &localidad);
};

#endif // LABORATORIO_H
