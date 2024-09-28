//
// Created by jmart on 23/09/2024.
//
#include <iostream>
#include "functions.h"

using namespace std;

int ejer1(){
  double num1, num2;

  num1 = getInt("De un primer numero");
  num2 = getInt("De un segundo numero");

  cout << "Suma " + to_string(num1+num2)
              + "\n Resta: " + to_string(num1-num2)
              + "\n Producto: " + to_string(num1*num2)
              + "\n Division: " + to_string(num1/num2)
       << endl;

  return 0;
}

int ejer2(){
  double precio;

  precio = getInt("Inserte el precio de un producto sin iva.");

  double iva = precio * 0.21;
  double precioConIva = precio + iva;

  cout << "" + to_string(precio +(precio*0.21)) << endl;
  cout << precioConIva;

  return 0;
}

int ejer3(){
  int edad;
  float altura;
  char grupoTeoria;

  edad = getInt("Inserte la edad");
  altura = getFloat("Inserte la altura");
  grupoTeoria = getChar("Inserte el grupo de teoria");

  cout << "Ha indicado que su edad es " << edad << " anyos. "
                                                   "\n Ha indicado que su altura es " << altura << " m. "
                                                   "\n Ha indicado que su grupo de teoria es " << grupoTeoria << "." << endl;

  return 0;
}

int ejer4(){
  int nota_practicas, nota_teoria, nota_participacion;

  nota_practicas = getInt("Nota de practicas");
  nota_teoria = getInt("Nota de teoria; ");
  nota_participacion = getInt("Nota de participacion: ");

  cout << "Nota media: " << to_string((nota_practicas * 0.3)+(nota_teoria*0.6)+(nota_participacion*0.1)) << endl;

  return 0;
}

int ejer5() {
  bool preguntar_notas = true;
  float nota;
  float sumatoria_de_notas = 0;
  int contador_de_notas = 0;

  cout << "Introduce las notas de los alumnos (introduce -1 o menos para terminar): " << endl;

  while (preguntar_notas) {

    cout << "Inserte una nota: " << endl;
    cin >> nota;

    if (nota <= -1) {
      preguntar_notas = false;
    }

    if (nota >= 0) {
      sumatoria_de_notas += nota;
      contador_de_notas++;
    }
  }

  if(contador_de_notas == 0) {
    cout << "No se introdujeron notas válidas." << endl;
  } else {
    cout << "Nota media: " << to_string(sumatoria_de_notas/contador_de_notas) << endl;
  }

  return 0;
}