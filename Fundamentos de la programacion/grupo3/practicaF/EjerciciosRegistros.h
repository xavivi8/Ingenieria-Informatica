//
// Created by jmart on 31/10/2024.
//
#include <iostream>

#include "functions.h"

using namespace std;
#ifndef EJERCICIOSREGISTROS_H
#define EJERCICIOSREGISTROS_H

struct TIEMPO {
    int hora;
    int minuto;
    int segunto;
};

TIEMPO etapas[4] = {{10,20,45},{2,3,4},{4,45,33},{5,55,21}};

int ejer1(){
    int h=0, m=0, s=0;

    for(int i=0; i<=4;i++){
        h += etapas[i].hora;
        m += etapas[i].minuto;
        s += etapas[i].segunto;
    };

    m += s / 60;
    s %= 60;
    h += m / 60;
    m %= 60;
    cout << "Tiempo total: " << h << " horas, " << m << " minutos, " << s << " segundos." << endl;
    return 0;
}

struct PERSONA {
    string nombre;
    bool alergia;
};

const int CANT_PERSON = 4;
PERSONA personas[CANT_PERSON]={{"Javi",true},{"Pedro",false},{"Marco",false},{"Maria Jose",false}};

int ejer2(){
    int pos_aler=0, pos_sin_aler=0;
    string pers_aler="", per_sin_aler="";
    PERSONA persona_sin_aler[CANT_PERSON];
    PERSONA persona_con_aler[CANT_PERSON];
    for(int i=0;i<=CANT_PERSON;i++){
        if(personas[i].alergia){
            persona_con_aler[pos_aler]=personas[i];
            pers_aler+=("\n"+personas[i].nombre);
            pos_aler++;
        } else {
            persona_sin_aler[pos_sin_aler]=personas[i];
            per_sin_aler+=("\n"+personas[i].nombre);
            pos_sin_aler++;
        }
    };
    cout << "Personas con alergia: " << pers_aler 
        << "\nPersonas sin alergia: "<< per_sin_aler<<endl;
    return 0;
}

#endif