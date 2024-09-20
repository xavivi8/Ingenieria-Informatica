//
// Created by jmart on 20/09/2024.
//
#include <iostream>
#include "strings.h"
using namespace std;

int getDay() {
    int day = 1;

    cout << introduce_esp + day_esp << endl;
    cin >> day;

    if (day <= 0) {
        cout << "No puede ser el dia menor o igual a 0" << endl;
        day = getDay();
    }

    return day;
}

int getMounth() {
    int mounth = 1;

    cout << introduce_esp + mounth_esp << endl;
    cin >> mounth;

    if (mounth <= 0 || mounth > 12) {
        cout << "No puede ser el mes menor o igual a 0 y tampoco mayor que 12" << endl;
        mounth = getMounth();
    }

    return mounth;
}

int getYear() {
    int year = 1;

    cout << introduce_esp + year_esp << endl;
    cin >> year;

    if (year < 0) {
        cout << "No puede ser el anyo menor o igual a 0 " << endl;
        year = getYear();
    }

    return year;
}

bool esBisiesto(int anyo) {
    // divisible entre 5 y no divisible entre 100 a menos que también sea divisible por 400
    if ((anyo % 4 == 0 && anyo % 100 != 0) || (anyo % 400 == 0)) {
        return true;
    }
    return false;
}

bool esFechaValida(int dia, int mes, int anyo) {

    switch (mes) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if (dia > 31) return false;  // Meses con 31 días
        break;
    case 4: case 6: case 9: case 11:
        if (dia > 30) return false;  // Meses con 30 días
        break;
    case 2:
        if (esBisiesto(anyo)) {
            if (dia > 29) return false;  // Febrero en año bisiesto
        } else {
            if (dia > 28) return false;  // Febrero en año no bisiesto
        }
        break;
    default:
        return false;
    }
    return true;
}

int main() {
    int dia, mes, anyo;

    dia = getDay();
    mes = getMounth();
    anyo = getYear();
    
    if (esFechaValida(dia, mes, anyo)) {
        cout << "La fecha " << dia << "/" << mes << "/" << anyo << " es valida." << endl;
    } else {
        cout << "La fecha " << dia << "/" << mes << "/" << anyo << " no es valida." << endl;
    }

    return 0;
}
