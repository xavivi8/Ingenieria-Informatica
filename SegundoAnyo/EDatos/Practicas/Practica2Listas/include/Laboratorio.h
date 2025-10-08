//
// Created by jmart on 08/10/2025.
//

#ifndef LABORATORIO_H
#define LABORATORIO_H

#include <string>

class Laboratorio{
private:
    unsigned m_id;
    std::string m_nombre_lab;
    std::string m_direccion;
    std::string m_cod_postal;
    std::string m_localidad;

public:
    // Constructores
    Laboratorio();
    Laboratorio(int id,
                const std::string &nombre_lab,
                const std::string &direccion,
                const std::string &cod_postal,
                const std::string &localidad);

    // Destructor
    ~Laboratorio() = default;  // no hay recursos dinámicos, por ende se puede usar el default

    // Getters
    int getId() const;
    std::string getNombreLab() const;
    std::string getDireccion() const;
    std::string getCodPostal() const;
    std::string getLocalidad() const;

    // Setters
    void setId(int id);
    void setNombreLab(const std::string &nombre_lab);
    void setDireccion(const std::string &direccion);
    void setCodPostal(const std::string &cod_postal);
    void setLocalidad(const std::string &localidad);
};

#endif // LABORATORIO_H
