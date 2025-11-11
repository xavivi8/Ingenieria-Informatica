//
// Created by jmart on 27/10/2025.
//

#ifndef FARMACIA_H
#define FARMACIA_H

#include "../include/PaMedicamento.h"
#include "../include/Avl.h"
#include <string>

class MediExpress;
class Farmacia{
    std::string m_cif;
    std::string m_province;
    std::string m_city;
    std::string m_name;
    std::string m_address;
    std::string m_postalCode;

    MediExpress* m_linkMedi{nullptr};
    Avl<PaMedicamento*> m_dispense;

    public:
    Farmacia() = default;
    Farmacia(const std::string &cif,
             const std::string &province,
             const std::string &city,
             const std::string &name,
             const std::string &address,
             const std::string &postalCode,
             MediExpress* med);
    ~Farmacia() = default;

    bool operator<(const Farmacia &farma) const;
    friend std::ostream& operator<<(std::ostream& os, const Farmacia& f);

    void pedidoMedicam(int idNum);
    PaMedicamento* buscaMedicam(int id_num);
    void dispensaMedicam(const PaMedicamento &pa);

    void setLinkMedi(MediExpress *medi);
    MediExpress* getLinkMedi() const;
};

#endif //FARMACIA_H
