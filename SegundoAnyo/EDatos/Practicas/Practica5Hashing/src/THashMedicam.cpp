//
// Created by jmart on 21/11/2025.
//
#include "../include/THashMedicam.h"
#include <cmath>

/**
 * Metodos privados 
 */

bool THashMedicam::isPrime(unsigned n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    unsigned limit = static_cast<unsigned>(std::sqrt(static_cast<double>(n)));
    for (unsigned i = 3; i <= limit; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int THashMedicam::nextPrime(unsigned number) {
    if (number < 2) number = 2;
    while (!isPrime(number)) {
        ++number;
    }
    return static_cast<int>(number);
}

int THashMedicam::previousPrime(unsigned number) {
    if (number <= 3) return 2;
    unsigned candidate = number - 1;
    while (candidate >= 2 && !isPrime(candidate)) {
        --candidate;
    }
    if (candidate < 2) candidate = 2;
    return static_cast<int>(candidate);
}

// Sondeo cuadrático: h_i(k) = (k % m_tableSize + i*i) % m_tableSize
unsigned THashMedicam::hash(unsigned long clave, int i) {
    unsigned long base = clave % m_tableSize;
    unsigned long inc  = static_cast<unsigned long>(i) * static_cast<unsigned long>(i);
    return static_cast<unsigned>((base + inc) % m_tableSize);
}

// Doble dispersión clásica: h_i(k) = (h1 + i*h2) % m_tableSize
// h2(k) = primoMenor - (k % primoMenor)
unsigned THashMedicam::hash2(unsigned clave, int i) {
    unsigned h1 = static_cast<unsigned>(clave % m_tableSize);
    unsigned step = static_cast<unsigned>(m_smallerPrime - (clave % m_smallerPrime));
    return static_cast<unsigned>((h1 + static_cast<unsigned long>(i) * step) % m_tableSize);
}

// Variante alternativa de doble dispersión
unsigned THashMedicam::hash3(unsigned clave, int i) {
    unsigned h1 = static_cast<unsigned>(clave % m_tableSize);
    unsigned step = static_cast<unsigned>((clave % m_smallerPrime) + 1); // evita paso 0
    return static_cast<unsigned>((h1 + static_cast<unsigned long>(i) * step) % m_tableSize);
}

/**
 * Metodos publicos
 */

THashMedicam::THashMedicam(unsigned long maxElementos, double lamda, TipoHash t)
    : m_tableSize(0),
      m_numElements(0),
      m_maxCollisions(0),
      m_over10Collisions(0),
      m_collisionsSum(0),
      m_smallerPrime(0),
      m_table(),
      m_hashType(t) {

    if (lamda <= 0.0 || lamda >= 1.0) {
        lamda = 0.7;  // valor por defecto razonable
    }

    // tamaño mínimo necesario para garantizar el factor de carga
    double tamNecesario = std::ceil(maxElementos / lamda);

    m_tableSize = static_cast<unsigned long>(nextPrime(static_cast<unsigned>(tamNecesario)));

    m_smallerPrime = static_cast<unsigned long>(previousPrime(static_cast<unsigned>(m_tableSize)));

    m_table.resize(static_cast<std::size_t>(m_tableSize));
}

THashMedicam::THashMedicam(const THashMedicam &orig)
    : m_tableSize(orig.m_tableSize),
      m_numElements(orig.m_numElements),
      m_maxCollisions(orig.m_maxCollisions),
      m_over10Collisions(orig.m_over10Collisions),
      m_collisionsSum(orig.m_collisionsSum),
      m_smallerPrime(orig.m_smallerPrime),
      m_table(orig.m_table),
      m_hashType(orig.m_hashType) {}

THashMedicam::~THashMedicam() = default;

/**
 * Operadores
 */

THashMedicam& THashMedicam::operator=(const THashMedicam &orig) {
    if (this != &orig) {
        m_tableSize = orig.m_tableSize;
        m_numElements = orig.m_numElements;
        m_maxCollisions = orig.m_maxCollisions;
        m_over10Collisions = orig.m_over10Collisions;
        m_collisionsSum = orig.m_collisionsSum;
        m_smallerPrime = orig.m_smallerPrime;
        m_table = orig.m_table;
        m_hashType = orig.m_hashType;
    }
    return *this;
}

/**
 * Metodos
 */
bool THashMedicam::insertar(unsigned long clave, PaMedicamento &dato) {
    if (m_numElements >= m_tableSize) {
        return false;
    }

    int collisions = 0;
    int firstAvailable = -1;

    for (int i = 0; i < static_cast<int>(m_tableSize); ++i) {

        unsigned idx;
        switch (m_hashType) {
            case HASH1: idx = hash(clave, i);  break;
            case HASH2: idx = hash2(clave, i); break;
            case HASH3: idx = hash3(clave, i); break;
            default: idx = hash(clave, i);  break;
        }

        Entrada &entry = m_table[idx];

        if (entry.m_state  == OCUPADA) {
            if (entry.m_key  == clave) {
                return false;
            }
            ++collisions;
            continue;
        }

        if (entry.m_state  == DISPONIBLE) {
            if (firstAvailable == -1) {
                firstAvailable = static_cast<int>(idx);
            }
            ++collisions;
            continue;
        }

        // entry.m_state  == LIBRE -> insertamos
        unsigned finalPos  = (firstAvailable != -1) ? static_cast<unsigned>(firstAvailable) : idx;

        m_table[finalPos ].m_key = clave;
        m_table[finalPos ].m_data = dato;
        m_table[finalPos ].m_state = OCUPADA;

        ++m_numElements;

        if (collisions > static_cast<int>(m_maxCollisions)) {
            m_maxCollisions = static_cast<unsigned long>(collisions);
        }
        m_collisionsSum += static_cast<unsigned long>(collisions);

        if (collisions > 10) {
            ++m_over10Collisions;
        }

        return true;
    }

    return false;
}

PaMedicamento *THashMedicam::buscar(unsigned long clave) {
    for (int i = 0; i < static_cast<int>(m_tableSize); ++i) {

        unsigned idx;
        switch (m_hashType) {
            case HASH1: idx = hash(clave, i);  break;
            case HASH2: idx = hash2(clave, i); break;
            case HASH3: idx = hash3(clave, i); break;
            default: idx = hash(clave, i);  break;
        }

        Entrada &entry = m_table[idx];

        if (entry.m_state  == LIBRE) {
            return nullptr;
        }

        if (entry.m_state  == OCUPADA && entry.m_key  == clave) {
            return &entry.m_data  ;
        }
    }
    return nullptr;
}

bool THashMedicam::borrar(unsigned long clave) {
    for (int i = 0; i < static_cast<int>(m_tableSize); ++i) {

        unsigned idx;
        switch (m_hashType) {
            case HASH1: idx = hash(clave, i);  break;
            case HASH2: idx = hash2(clave, i); break;
            case HASH3: idx = hash3(clave, i); break;
            default:    idx = hash(clave, i);  break;
        }

        Entrada &entry = m_table[idx];

        if (entry.m_state  == LIBRE) {
            return false;
        }

        if (entry.m_state  == OCUPADA && entry.m_key  == clave) {
            entry.m_state  = DISPONIBLE;
            --m_numElements;
            return true;
        }
    }
    return false;
}


/**
 * Getters
 */

unsigned int THashMedicam::numElementos() const{
    return static_cast<unsigned int>(m_numElements);
}

unsigned int THashMedicam::getTableSize() const{
    return static_cast<unsigned int>(m_tableSize);
}

unsigned long THashMedicam::getMaxCollisions() const {
    return m_maxCollisions;
}

unsigned int THashMedicam::getNumOver10Collisions() const{
    return static_cast<unsigned int>(m_over10Collisions);
}

float THashMedicam::getAverageCollisions() const {
    if (m_numElements == 0) return 0.0f;
    return static_cast<float>(m_collisionsSum) /
           static_cast<float>(m_numElements);
}

float THashMedicam::getLoadFactor() const{
    if (m_tableSize == 0) return 0.0f;
    return static_cast<float>(m_numElements) /
           static_cast<float>(m_tableSize);
}

TipoHash THashMedicam::getHashType() const {
    return m_hashType;
}