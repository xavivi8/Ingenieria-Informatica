//
// Created by jmart on 16/12/2024.
//
#include <iostream>
#include <cctype>
#include "mis_datos.h"


#ifndef FUNCTIONS_H
#define FUNCTIONS_H
bool condicion1(char a){
    bool condition = false;
    if (toupper(a)=='A' ||toupper(a)=='B' ||toupper(a)=='C' ||toupper(a)=='D' ||toupper(a)=='E'){
        condition = true;
    }
    return condition;
}
int setRow(){
    char row = 'j';
    do{
        std::cout << "Inserte la columnas de A a E" << std::endl;
        cin >> row;  
    }while(!condicion1(row));

    return toupper(row);
}

char setColumn(){
    int column = 0;
    do{
        std::cout << "Inserte la fila, del 0 al 4" << std::endl;
        cin >> column;
        if(column!=0 || column!=1 || column!=2 || column!=3 || column!=4){
            std::cout << "Error al insertar datos, debe de ser un numero del 0 al 4, pruebe de nuevo" << std::endl;
        }

    }while(column!=0 || column!=1 || column!=2 || column!=3 || column!=4);
    return column;
}

void insertarDatos(Coordenadas v[]){
    int column = -1;
    char row = 'd';
    for(int i=0;i<MAX_DATOS;++i){
        row = setRow();
        column = setColumn();
        v[i] = {row, column};
    };
}

#endif //FUNCTIONS_H
