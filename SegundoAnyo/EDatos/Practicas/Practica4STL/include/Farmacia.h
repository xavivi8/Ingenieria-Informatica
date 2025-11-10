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
    std::set<Stock> order;

    void pedidoMedicam(int idNum, int n);
    int buscaMedicamID(int id_num);


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

    PaMedicamento* buscaMedicam(int id_num);
    std::vector<PaMedicamento*> buscaMedicamNombre(const std::string &nombre);
    void nuevoStock(PaMedicamento* pa, int n);
    
    PaMedicamento* comprarMedicamento(int id_num, int n);

    
    

    bool deleteStock(int idNum);

    //Getters
    std::string& getCif() const;
    std::string& getProvince() const;
    std::string& getCity() const;
    std::string& getName() const;
    std::string& getAddress() const;
    std::string& getPostalCode() const;
    MediExpress* getLinkMedi() const;

    //Setters
    void setCif(const std::string &cif);
    void setProvince(const std::string &province);
    void setCity(const std::string &city);
    void setName(const std::string &name);
    void setAddress(const std::string &address);
    void setPostalCode(const std::string &postalCode);
    void setLinkMedi(MediExpress *medi);

};

#endif //FARMACIA_H
