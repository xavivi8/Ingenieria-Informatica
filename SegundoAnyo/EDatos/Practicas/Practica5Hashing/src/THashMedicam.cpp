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

