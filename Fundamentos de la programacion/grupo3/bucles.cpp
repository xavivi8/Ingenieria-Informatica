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

int main(){
  int dia, mes, anyo;

  dia = getDay();
  mes = getMounth();
  anyo = getYear();

  cout << anyo;
  if (anyo < 0) {

  }

  return 0;
}
