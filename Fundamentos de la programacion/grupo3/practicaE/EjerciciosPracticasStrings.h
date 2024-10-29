//
// Created by jmart on 28/10/2024.
//
#include <iostream>
#include <cstdio>

#include "functions.h"

using namespace std;
#ifndef EJERCICIOSVECTORES_H
#define EJERCICIOSSTRINGS_H

int ejer1(){
    string cadena_a_analizar = "";
    int cant_a = 0, cant_e = 0, cant_i = 0, cant_o = 0, cant_u = 0;

    cadena_a_analizar = getString("Inserte una cadena para sacar la cantidad de vocales de cada tipo: ");

    for(int i=0; i<=cadena_a_analizar.length();i++){
        if('a' == cadena_a_analizar[i] || 'A' == cadena_a_analizar[i]){
            cant_a++;
        }
        if('e' == cadena_a_analizar[i] || 'E' == cadena_a_analizar[i]){
            cant_e++;
        }
        if('i' == cadena_a_analizar[i] || 'I' == cadena_a_analizar[i]){
            cant_i++;
        }
        if('o' == cadena_a_analizar[i] || 'O' == cadena_a_analizar[i]){
            cant_o++;
        }
        if('u' == cadena_a_analizar[i] || 'U' == cadena_a_analizar[i]){
            cant_u++;
        }
    }

    cout << "Hay esta cantidad de vocales: \nA: " << cant_a
        << "\nE: " << cant_e
        << "\nI: " << cant_i
        << "\nO: " << cant_o
        << "\nU: " << cant_u << endl;

    return 0;
}

#endif