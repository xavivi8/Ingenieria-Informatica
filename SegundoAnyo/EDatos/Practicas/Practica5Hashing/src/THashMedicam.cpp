//
// Created by jmart on 21/11/2025.
//
#include "../include/THashMedicam.h"
#include <cmath>

/**
 * Metodos privados 
 */

bool THashMedicam::esprimo(unsigned n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    unsigned limite = static_cast<unsigned>(std::sqrt(static_cast<double>(n)));
    for (unsigned i = 3; i <= limite; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int THashMedicam::primo_mayor(unsigned numero) {
    if (numero < 2) numero = 2;
    while (!esprimo(numero)) {
        ++numero;
    }
    return static_cast<int>(numero);
}

int THashMedicam::primo_menor(unsigned numero) {
    if (numero <= 3) return 2;
    unsigned candidato = numero - 1;
    while (candidato >= 2 && !esprimo(candidato)) {
        --candidato;
    }
    if (candidato < 2) candidato = 2;
    return static_cast<int>(candidato);
}

// Sondeo cuadrático: h_i(k) = (k % tamaf + i*i) % tamaf
unsigned THashMedicam::hash(unsigned long clave, int i) {
    unsigned long base = clave % tamaf;
    unsigned long inc  = static_cast<unsigned long>(i) * static_cast<unsigned long>(i);
    return static_cast<unsigned>((base + inc) % tamaf);
}

// Doble dispersión clásica: h_i(k) = (h1 + i*h2) % tamaf
// h2(k) = primoMenor - (k % primoMenor)
unsigned THashMedicam::hash2(unsigned clave, int i) {
    unsigned h1 = static_cast<unsigned>(clave % tamaf);
    unsigned paso = static_cast<unsigned>(primoMenor - (clave % primoMenor));
    return static_cast<unsigned>((h1 + static_cast<unsigned long>(i) * paso) % tamaf);
}

// Variante alternativa de doble dispersión
unsigned THashMedicam::hash3(unsigned clave, int i) {
    unsigned h1 = static_cast<unsigned>(clave % tamaf);
    unsigned paso = static_cast<unsigned>((clave % primoMenor) + 1); // evita paso 0
    return static_cast<unsigned>((h1 + static_cast<unsigned long>(i) * paso) % tamaf);
}

/**
 * Metodos publicos
 */

THashMedicam::THashMedicam(unsigned long maxElementos, double lamda, TipoHash t)
    : tamaf(0),
      tamal(0),
      maxCol(0),
      max10(0),
      sumaColisiones(0),
      primoMenor(0),
      tipo(t) {

    if (lamda <= 0.0 || lamda >= 1.0) {
        lamda = 0.7;  // valor por defecto razonable
    }

    // tamaño mínimo necesario para garantizar el factor de carga
    double tamNecesario = std::ceil(maxElementos / lamda);

    tamaf = static_cast<unsigned long>(primo_mayor(static_cast<unsigned>(tamNecesario)));

    primoMenor = static_cast<unsigned long>(primo_menor(static_cast<unsigned>(tamaf)));

    tabla.resize(static_cast<std::size_t>(tamaf));
}

THashMedicam::THashMedicam(const THashMedicam &orig)
    : tamaf(orig.tamaf),
      tamal(orig.tamal),
      maxCol(orig.maxCol),
      max10(orig.max10),
      sumaColisiones(orig.sumaColisiones),
      primoMenor(orig.primoMenor),
      tabla(orig.tabla) {}

THashMedicam::~THashMedicam() = default;

/**
 * Operadores
 */

THashMedicam& THashMedicam::operator=(const THashMedicam &orig) {
    if (this != &orig) {
        tamaf = orig.tamaf;
        tamal = orig.tamal;
        maxCol = orig.maxCol;
        max10 = orig.max10;
        sumaColisiones = orig.sumaColisiones;
        primoMenor = orig.primoMenor;
        tabla = orig.tabla;
        tipo = orig.tipo;
    }
    return *this;
}

/**
 * Metodos
 */
bool THashMedicam::insertar(unsigned long clave, PaMedicamento &dato) {
    if (tamal >= tamaf) {
        return false;
    }

    int colisiones = 0;
    int primeraDisponible = -1;

    for (int i = 0; i < static_cast<int>(tamaf); ++i) {

        unsigned idx;
        switch (tipo) {
            case HASH1: idx = hash(clave, i);  break;
            case HASH2: idx = hash2(clave, i); break;
            case HASH3: idx = hash3(clave, i); break;
            default:    idx = hash(clave, i);  break;
        }

        Entrada &e = tabla[idx];

        if (e.marca == OCUPADA) {
            if (e.clave == clave) {
                return false;
            }
            ++colisiones;
            continue;
        }

        if (e.marca == DISPONIBLE) {
            if (primeraDisponible == -1) {
                primeraDisponible = static_cast<int>(idx);
            }
            ++colisiones;
            continue;
        }

        // e.marca == LIBRE -> insertamos
        unsigned posFinal = (primeraDisponible != -1) ? static_cast<unsigned>(primeraDisponible) : idx;

        tabla[posFinal].clave = clave;
        tabla[posFinal].dato  = dato;
        tabla[posFinal].marca = OCUPADA;

        ++tamal;

        if (colisiones > static_cast<int>(maxCol)) {
            maxCol = static_cast<unsigned long>(colisiones);
        }
        sumaColisiones += static_cast<unsigned long>(colisiones);

        if (colisiones > 10) {
            ++max10;
        }

        return true;
    }

    return false;
}

PaMedicamento *THashMedicam::buscar(unsigned long clave) {
    for (int i = 0; i < static_cast<int>(tamaf); ++i) {

        unsigned idx;
        switch (tipo) {
            case HASH1: idx = hash(clave, i);  break;
            case HASH2: idx = hash2(clave, i); break;
            case HASH3: idx = hash3(clave, i); break;
            default:    idx = hash(clave, i);  break;
        }

        Entrada &e = tabla[idx];

        if (e.marca == LIBRE) {
            return nullptr;
        }

        if (e.marca == OCUPADA && e.clave == clave) {
            return &e.dato;
        }
    }
    return nullptr;
}

bool THashMedicam::borrar(unsigned long clave) {
    for (int i = 0; i < static_cast<int>(tamaf); ++i) {

        unsigned idx;
        switch (tipo) {
            case HASH1: idx = hash(clave, i);  break;
            case HASH2: idx = hash2(clave, i); break;
            case HASH3: idx = hash3(clave, i); break;
            default:    idx = hash(clave, i);  break;
        }

        Entrada &e = tabla[idx];

        if (e.marca == LIBRE) {
            return false;
        }

        if (e.marca == OCUPADA && e.clave == clave) {
            e.marca = DISPONIBLE;
            --tamal;
            return true;
        }
    }
    return false;
}


/**
 * Getters
 */

unsigned int THashMedicam::numElementos() const{
    return static_cast<unsigned int>(tamal);
}

unsigned int THashMedicam::tamTabla() const{
    return static_cast<unsigned int>(tamaf);
}

unsigned long THashMedicam::maxColisiones() const {
    return maxCol;
}

unsigned int THashMedicam::numMax10() const{
    return static_cast<unsigned int>(max10);
}

float THashMedicam::promedioColisiones() const {
    if (tamal == 0) return 0.0f;
    return static_cast<float>(sumaColisiones) /
           static_cast<float>(tamal);
}

float THashMedicam::factorCarga() const{
    if (tamaf == 0) return 0.0f;
    return static_cast<float>(tamal) /
           static_cast<float>(tamaf);
}

TipoHash THashMedicam::getTipo() const {
    return tipo;
}