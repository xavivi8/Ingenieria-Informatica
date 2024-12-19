//
// Created by jmart on 19/12/2024.
//
#include "Tablero.h"

int main() {
    Tablero jugador1;

    // Colocar barcos
    jugador1.colocarBarco(0, 0, 4, 'H'); // Barco horizontal de longitud 4
    jugador1.colocarBarco(2, 3, 3, 'V'); // Barco vertical de longitud 3
    jugador1.colocarBarco(7, 5, 2, 'V');
    // Mostrar el tablero inicial
    jugador1.mostrar(false);
    cout << "Tablero del jugador 1:" << endl;
    jugador1.mostrar(true); // Ocultar los barcos

    // Simular disparos
    jugador1.disparar(0, 0); // Impacto
    jugador1.disparar(1, 1); // Agua
    jugador1.disparar(2, 3); // Impacto

    // Mostrar el tablero después de los disparos
    cout << "Tablero despues de los disparos:" << endl;
    jugador1.mostrar(true); // Mostrar con barcos ocultos

    // Verificar si quedan barcos
    if (!jugador1.quedanBarcos()) {
        cout << "¡Todos los barcos han sido hundidos!" << endl;
    }

    return 0;
}

