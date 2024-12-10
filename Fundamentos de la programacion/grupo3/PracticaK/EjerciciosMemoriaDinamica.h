//
// Created by jmart on 03/12/2024.
//
#include <iostream>

#ifndef EJERCICIOSMEMORIADINAMICA_H
#define EJERCICIOSMEMORIADINAMICA_H

const int TAMMAX=50;
struct Persona {
  string nombre;
  int edad;
  string localidad;
};

Persona* buscar_por_localidad(Persona vector[], int tam, string localidad,int& tamResultado) {
  // Contar cuántos resultados hay
  tamResultado = 0;
  for (int i = 0; i < tam; ++i) {
      if (vector[i].localidad == localidad) {
          tamResultado++;
      }
  }

  // Crear un arreglo dinámico del tamaño exacto
  Persona* resultado = new Persona[tamResultado];
  int index = 0;

  // Llenar el arreglo con las coincidencias
  for (int i = 0; i < tam; ++i) {
      if (vector[i].localidad == localidad) {
          resultado[index] = vector[i];
          index++;
      }
  }

  return resultado;
}

int ejer3(){
  Persona personas[TAMMAX] = {
    {"a",5,"Benalmadena"},
    {"b",35,"e"},
    {"c",55,"Benalmadena"},
    {"d",25,"g"},
    {"f",15,"Benalmadena"},
  };
  int tamResultado;
  Persona *resultado = buscar_por_localidad(personas,TAMMAX,"Benalmadena",tamResultado);

  for(int i=0; i<tamResultado;++i){
    cout << "Nombre: " << resultado[i].nombre << " - Edad: " << resultado[i].edad << " - Localidad: " << resultado[i].localidad << endl;
  }

  return 0;
}


void hacer_vector(const int tam, std::string *&v){
  v=new std::string[tam];
  v[0]="rojo";
  v[1]="azul";
  v[2]="verde";
  v[3]="rosa";
  v[4]="morado";
}
std::string* hacer_vector(const int tam) {
    return new std::string[tam];
}

void mostrar_vector(const std::string* v, const int tam) {
  for(int i=0; i<tam; ++i) {
    std::cout<<v[i]<<std::endl;
  }
}

void direccion_nuevo_vector( int tam1, std::string v1[], const int tam2, std::string *&v2) {
  v2=new std::string[tam2];
  if(tam1>=tam2) {
    for(int i=0; i<tam2; ++i) {
    v2[i]=v1[i];
    }
  }
  if(tam1<tam2) {
    for(int i=0; i<tam1; ++i) {
      v2[i]=v1[i];
    }
    for(int i=tam1; i<tam2; ++i) {
      v2[i]="";
    }
  }
  delete[] v1;
}

void copia_vector(std::string v1[], int tam1, std::string v2[], int *tam2) {
  *tam2=tam1;
  for(int i=0; i<tam1; ++i) {
    v2[i]=v1[i];
  }
}

int ejer4(){
  int tam1=5,tam=5;
  std::string* vector = hacer_vector(tam);
  //std::string *vector=nullptr;
  std::string *vector2=nullptr;

  //hacer_vector(tam1,vector);

  //mostrar_vector(vector, tam1);

  //direccion_nuevo_vector(tam1,vector,3,vector2);
  std::cout<<"La direccion de memoria del primer valor del vector 2 es "<<std::endl;

  return 0;
}

#endif //EJERCICIOSMEMORIADINAMICA_H
