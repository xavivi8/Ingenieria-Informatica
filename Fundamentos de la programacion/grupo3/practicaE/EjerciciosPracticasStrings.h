//
// Created by jmart on 28/10/2024.
//
#include <iostream>
#include <string>
#include <cstdio>

#include "functions.h"

using namespace std;
#ifndef EJERCICIOSVECTORES_H
#define EJERCICIOSSTRINGS_H

int ejer1(){
    string cadena_a_analizar = "";
    int cont_a = 0, cont_e = 0, cont_i = 0, cont_o = 0, cont_u = 0;

    cadena_a_analizar = getString("Inserte una cadena para sacar la cantidad de vocales de cada tipo: ");

    for(int i=0; i<=cadena_a_analizar.length();i++){
        if('a' == cadena_a_analizar[i] || 'A' == cadena_a_analizar[i]){
            cont_a++;
        }
        if('e' == cadena_a_analizar[i] || 'E' == cadena_a_analizar[i]){
            cont_e++;
        }
        if('i' == cadena_a_analizar[i] || 'I' == cadena_a_analizar[i]){
            cont_i++;
        }
        if('o' == cadena_a_analizar[i] || 'O' == cadena_a_analizar[i]){
            cont_o++;
        }
        if('u' == cadena_a_analizar[i] || 'U' == cadena_a_analizar[i]){
            cont_u++;
        }
    }

    cout << "Hay esta cantidad de vocales: \nA: " << cont_a
        << "\nE: " << cont_e
        << "\nI: " << cont_i
        << "\nO: " << cont_o
        << "\nU: " << cont_u << endl;

    return 0;
}
int ejer2(){
    cin.ignore();
    int primera_cadena=0;
    string cadena ="", cadena_max, cadena_min;
    do{
        cout << "Inserte una cadena: " << endl;
        getline(cin,cadena);
        //cadena=getString("Inserte una cadena: ");

        if(primera_cadena==0){
            cadena_max=cadena;
            cadena_min=cadena;
            primera_cadena++;
        }

        if(cadena!="FIN"){
            if(cadena > cadena_max){
            cadena_max=cadena;
            }
            if(cadena < cadena_min){
                cadena_min=cadena;
            }
        }

    }while(cadena!="FIN");

    cout << "Cadena lexicografica mayor: " << cadena_max
        <<"\nCadena lexicografica menor: " << cadena_min << endl;
    return 0;
}

int ejer3(){
    cin.ignore();
    int primera_cadena=0;
    string cadena ="", cadena_max, cadena_min;
    do{
        cout << "Inserte una cadena: " << endl;
        getline(cin,cadena);

        if(primera_cadena==0){
            cadena_max=cadena;
            cadena_min=cadena;
            primera_cadena++;
        }

        if(cadena!="FIN"){
            if(cadena.length()>=cadena_max.length()){
            cadena_max=cadena;
            }
            if(cadena.length()<=cadena_min.length()){
                cadena_min=cadena;
            }
        }

    }while(cadena!="FIN");

    cout << "Cadena maxima: " << cadena_max
        <<"\nCadena minima: " << cadena_min << endl;
    return 0;
}

#endif