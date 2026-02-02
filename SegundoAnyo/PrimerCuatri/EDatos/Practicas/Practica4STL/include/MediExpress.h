//
// Created by jmart on 08/10/2025.
//

#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H
#include "../include/PaMedicamento.h"
#include "../include/Laboratorio.h"
#include "../include/Farmacia.h"

#include <set>
#include <vector>
#include <list>
#include <map>

class MediExpress{
    private:
        std::map<int, PaMedicamento> m_med;
        std::list<Laboratorio> m_lab;
        std::vector<Farmacia> m_farma;

        /**
         * @brief Carga los medicamentos desde un archivo CSV
         * @param csvPath Ruta del archivo CSV
         * @return Devuelve un mapa con los medicamentos cargados
         */
        std::map<int, PaMedicamento> loadMedicinesFromCsv(const std::string &csvPath);
        /**
         * @brief Carga los laboratorios desde un archivo CSV
         * @param csvPath Ruta del archivo CSV
         * @return Devuelve una lista con los laboratorios cargados
         */
        std::list<Laboratorio> loadLabFromCsv(const std::string &csvPath);
        /**
         * @brief Carga las farmacias desde un archivo CSV
         * @param csvPath Ruta del archivo CSV
         * @return Devuelve un vector con las farmacias cargadas
         */
        std::vector<Farmacia> loadFarmacieFromCsv(const std::string &csvPath);
        /**
         * @brief Enlaza automaticamente los medicamentos con sus laboratorios
         */
        void autoLinkMedications();
        /**
         * @brief Enlaza automaticamente las farmacias con sus stocks
         */
        void autoLinkFarmaciasStock();

    public:
        /**
         * @brief Constructor por defecto
         * @post Inicializa los atributos a valores por defecto
         */
        MediExpress();
        /**
         * @brief Constructor con parametros
         * @param csvPathVD Ruta del archivo CSV de medicamentos
         * @param csvPathLE Ruta del archivo CSV de laboratorios
         * @param csvPathAVL Ruta del archivo CSV de farmacias
         * @post Inicializa los atributos con los valores pasados por parametro
         */
        MediExpress(const std::string &csvPathVD,
                    const std::string &csvPathLE,
                    const std::string &csvPathAVL);
        /**
         * @brief Destructor
         * @post Destructor por defecto
         */
        ~MediExpress();

        /**
         * @brief Suministra un medicamento a un laboratorio
         * @param med Medicamento a suministrar
         * @param lab Laboratorio al que se le suministra el medicamento
         * @post Suministra el medicamento al laboratorio
         */
        void suministrarMed(const PaMedicamento &med, const Laboratorio &lab);
        /**
         * @brief Suministra un medicamento a una farmacia
         * @param med Medicamento a suministrar
         * @param farma Farmacia a la que se le suministra el medicamento
         * @post Suministra el medicamento a la farmacia
         */
        Laboratorio* buscarLab(const std::string &labName);
        /**
         * @brief Busca laboratorios en una ciudad
         * @param cityName Nombre de la ciudad
         * @return Devuelve un vector con punteros a los laboratorios que se encuentran en la ciudad dada
         */
        std::vector<Laboratorio*> buscarLabCiudad(const std::string &cityName) const;
        /**
         * @brief Busca medicamentos que contengan un compuesto activo
         * @param compoundName Nombre del compuesto activo
         * @return Devuelve un vector con punteros a los medicamentos que contienen el compuesto activo dado
         */
        std::vector<PaMedicamento*> buscarCompuesto(const std::string &compoundName) const;
        /**
         * @brief Obtiene los medicamentos que no tienen laboratorio asignado
         * @return Devuelve un vector con punteros a los medicamentos sin laboratorio asignado
         */
        std::vector<PaMedicamento*> getMedicamSinLab() const;

        //metodos pract3
        /**
         * @brief Busca un medicamento por su identificador numerico
         * @param id_num Identificador numerico del medicamento
         * @return Devuelve un puntero al medicamento si se encuentra, nullptr en caso contrario
         */
        PaMedicamento* buscarCompuesto(int id_num);
        /**
         * @brief Busca una farmacia por su CIF
         * @param cif CIF de la farmacia
         * @return Devuelve un puntero a la farmacia si se encuentra, nullptr en caso contrario
         */
        Farmacia* buscarFarmacia(const std::string &cif);
        /**
         * @brief Busca laboratorios que suministren un medicamento por su nombre
         * @param nombrePA Nombre del medicamento
         * @return Devuelve un vector con punteros a los laboratorios que suministran el medicamento dado
         */
        std::vector<Laboratorio*> buscarLabs(const std::string &nombrePA) const;

        //metodos pract4
        /**
         * @brief Suministra un medicamento a una farmacia
         * @param f Farmacia a la que se le suministra el medicamento
         * @param id_num Identificador numerico del medicamento
         * @param n Numero de unidades a suministrar
         * @post Suministra el medicamento a la farmacia
         */
        void suministrarFarmacia(Farmacia &f, int id_num, int n);
        /**
         * @brief Busca farmacias en una provincia
         * @param provincia Nombre de la provincia
         * @return Devuelve un vector con punteros a las farmacias que se encuentran en la provincia dada
         */
        std::vector<Farmacia*> buscarFarmacias(const std::string &provincia) const;
        /**
         * @brief Elimina un medicamento del sistema
         * @param id_num Identificador numerico del medicamento
         * @return Devuelve true si se ha podido eliminar el medicamento, false en caso contrario
         */
        bool eliminarMedicamento(int id_num);
};

#endif //MEDIEXPRESS_H
