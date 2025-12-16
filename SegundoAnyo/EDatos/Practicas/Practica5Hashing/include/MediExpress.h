//
// Created by jmart on 08/10/2025.
//

#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H
#include "./PaMedicamento.h"
#include "./Laboratorio.h"
#include "./Farmacia.h"
#include "./THashMedicam.h"

#include <set>
#include <vector>
#include <list>
#include <map>
#include <string>

class MediExpress{
    private:
        THashMedicam m_idMedication;
        std::multimap<std::string, PaMedicamento*> m_nameMed;
        std::vector<Farmacia> m_far;
        std::list<Laboratorio> m_labs;
        
        // tiempos de la última prueba de rendimiento
        double m_hashTime{0.0};
        double m_listTime{0.0};

        /**
         * @brief Carga los medicamentos desde un archivo CSV
         * @param csvPath Ruta del archivo CSV
         * @return Devuelve un mapa con los medicamentos cargados
         */
        std::vector<PaMedicamento> loadMedicinesFromCsv(const std::string &csvPath);
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
                    const std::string &csvPathAVL,
                    double lambda,
                    TipoHash tipoHash);
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
         * @brief Obtiene los medicamentos que no tienen laboratorio asignado
         * @return Devuelve un vector con punteros a los medicamentos sin laboratorio asignado
         */
        std::vector<PaMedicamento*> getMedicamSinLab() const;

        //metodos pract3
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

        //metodos pract5
        /**
         * @brief Busca medicamentos por su nombre compuesto
         * @param nombrePA Nombre compuesto del medicamento
         * @return Devuelve un vector con punteros a los medicamentos que coinciden con el nombre dado
         */
        std::vector<PaMedicamento*> buscarCompuesto(const std::string &nombrePA) const;
        /**
         * @brief Busca un medicamento por su identificador numerico
         * @param id_num Identificador numerico del medicamento
         * @return Devuelve un puntero al medicamento si se encuentra, nullptr en caso contrario
         */
        PaMedicamento* buscarCompuesto(int id_num);
        /**
         * @brief Muestra el estado de la tabla hash
         */
        void mostrarEstadoTabla();
        /**
         * @brief Realiza una prueba de rendimiento comparando la búsqueda en la tabla hash y en una lista
         */
        void pruebaRendimiento(); 
        
        //getters
        //metricas de la tabla hash
        /**
         * @brief Devuelve el número de colisiones máximas ocurridas durante las inserciones
         * @return Devuelve el número de colisiones máximas ocurridas durante las inserciones
         */
        unsigned int getMaxColisiones() const;
        /**
         * @brief Devuelve el número de inserciones que han tenido más de 10 colisiones
         * @return Devuelve el número de inserciones que han tenido más de 10 colisiones
         */
        unsigned int getNumMax10() const;
        /**
         * @brief Devuelve el promedio de colisiones por inserción
         * @return Devuelve el promedio de colisiones por inserción
         */
        float getPromedioColisiones() const;
        /**
         * @brief Devuelve el factor de carga de la tabla hash
         * @return Devuelve el factor de carga de la tabla hash
         */
        float getFactorCarga() const;
        /**
         * @brief Devuelve el tamaño de la tabla hash
         * @return Devuelve el tamaño de la tabla hash
         */
        unsigned int getTamTabla() const;
        /**
         * @brief Devuelve el número de elementos almacenados en la tabla hash
         * @return Devuelve el número de elementos almacenados en la tabla hash
         */
        unsigned int getNumElementos() const;

        //tiempos de la última prueba de rendimiento (en ms)
        /**
         * @brief Devuelve el tiempo de búsqueda en la tabla hash
         * @return Devuelve el tiempo de búsqueda en la tabla hash
         */
        double getTiempoHash() const;
        /**
         * @brief Devuelve el tiempo de búsqueda en la lista
         * @return Devuelve el tiempo de búsqueda en la lista
         */
        double getTiempoLista() const;

};

#endif //MEDIEXPRESS_H
