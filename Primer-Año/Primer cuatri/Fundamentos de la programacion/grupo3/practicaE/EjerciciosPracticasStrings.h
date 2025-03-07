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

int ejer4(){
    cin.ignore();
    bool nombre_encontrado=false;
    string cadena = "";
    string nombres[]={"Javi","Marco","Pedro"};
    int tamano = sizeof(nombres) / sizeof(nombres[0]);

    cout << "Inserte un nombre: " << endl;
    getline(cin,cadena);

    for(int i=0;i<=tamano;i++){
        if(cadena==nombres[i]){
            nombre_encontrado=true;
        }
    }

    if(nombre_encontrado){
        cout << "Se ha encontrado el nombre " << cadena << " en el vector" << endl;
    } else {
        cout << "No se ha encontrado el nombre " << cadena << " en el vector" << endl;
    }

    return 0;
}

int ejer5(){
    cin.ignore();
    bool palindromo = true;
    string cadena1="";
    int pos_ini=0, pos_fin=0;
    cout << "Inserte una cadena: " << endl;
    getline(cin,cadena1);
    pos_fin = (cadena1.length()-1);
    while(palindromo && pos_ini<=cadena1.length()){
        if(cadena1[pos_ini]!=cadena1[pos_fin]){
            palindromo=false;
        }
        pos_ini--;
        pos_fin++;
    }
    if(palindromo){
        cout << "Es un palindromo" << endl;
    } else {
        cout << "No es un palindromo" << endl;
    }
    return 0;
}

int ejer7(){
    string cadena="", palabra="";
    string palabras[100];
    int pos_palabras = 0;
    cout << "Inserte una primera cadena: " << endl;
    getline(cin,cadena);
    cadena+=' ';
    for(int i=0;i<=cadena.length();i++){
        if(cadena[i]!=' '){
            palabra+=cadena[i];
        } else if(cadena[i]==' ' && palabra != ""){
            palabras[pos_palabras] = palabra;
            pos_palabras++;
            palabra = "";
        }
    }
    cout << "Cantidad de palabras: " << pos_palabras << endl;
    return 0;
}

#endif