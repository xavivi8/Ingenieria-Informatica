//
// Created by jmart on 19/12/2024.
//

#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
using namespace std;

class Tablero {
private:
    static const int TAMANO = 10;
    char grid[TAMANO][TAMANO];

public:
    Tablero();
    void mostrar(bool ocultarBarcos = false);
    bool colocarBarco(int x, int y, int longitud, char direccion);
    bool disparar(int x, int y);
    bool quedanBarcos();
};

#endif //TABLERO_H
