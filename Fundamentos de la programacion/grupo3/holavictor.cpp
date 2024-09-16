//
// Created by admin on 16/09/2024.
//
/*
 * autor: Francisco Javier Martin-Lunas Escobar
 * fecha: 16/09/2024
 * objetivo: probar c++
 * */

#include <iostream>
using namespace std;

int main() {
    string name = "Victor";
    int edad;
    cout << "Hello " << name << "\n";
    cout << "Hola " << name << " dame tu edad por favor: " << endl;
    cin >> edad;
    if (edad >= 35) {
        cout << "Estas mayor ehh... ya con tus " << edad;
    } else {
        cout << "Te mantienes joven de momento" << endl;
    }
    return 0;
}