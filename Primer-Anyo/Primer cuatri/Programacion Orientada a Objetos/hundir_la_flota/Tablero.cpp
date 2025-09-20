//
// Created by jmart on 19/12/2024.
//
#include "Tablero.h"

// Constructor
Tablero::Tablero() {
    for (int i = 0; i < TAMANO; ++i) {
        for (int j = 0; j < TAMANO; ++j) {
            grid[i][j] = '~';
        }
    }
}

// Mostrar el tablero
void Tablero::mostrar(bool ocultarBarcos) {
    cout << "  ";
    for (int i = 0; i < TAMANO; ++i) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < TAMANO; ++i) {
        cout << i << " ";
        for (int j = 0; j < TAMANO; ++j) {
            if (ocultarBarcos && grid[i][j] == 'B') {
                cout << "~ ";
            } else {
                cout << grid[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Colocar barco
bool Tablero::colocarBarco(int x, int y, int longitud, char direccion) {
    if (direccion == 'H') {
        if (y + longitud > TAMANO) return false;
        for (int i = 0; i < longitud; ++i) {
            if (grid[x][y + i] != '~') return false;
        }
        for (int i = 0; i < longitud; ++i) {
            grid[x][y + i] = 'B';
        }
    } else if (direccion == 'V') {
        if (x + longitud > TAMANO) return false;
        for (int i = 0; i < longitud; ++i) {
            if (grid[x + i][y] != '~') return false;
        }
        for (int i = 0; i < longitud; ++i) {
            grid[x + i][y] = 'B';
        }
    } else {
        return false;
    }
    return true;
}

// Disparar
bool Tablero::disparar(int x, int y) {
    if (grid[x][y] == 'B') {
        grid[x][y] = 'X';
        cout << "¡Impacto!" << endl;
        return true;
    } else if (grid[x][y] == '~') {
        grid[x][y] = '*';
        cout << "¡Agua!" << endl;
        return false;
    } else {
        cout << "Ya disparaste aqui." << endl;
        return false;
    }
}

// Quedan barcos
bool Tablero::quedanBarcos() {
    for (int i = 0; i < TAMANO; ++i) {
        for (int j = 0; j < TAMANO; ++j) {
            if (grid[i][j] == 'B') {
                return true;
            }
        }
    }
    return false;
}
