//
// Created by jmart on 23/09/2024.
//
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>

using namespace std;

int getInt(string message){
  int inter;

  cout << message << endl;
  cin >> inter;

  return inter;
}

bool getBool(string message){
  bool boleano = false;
  string respuesta="";
  cout << message << endl;
  cin >> respuesta;

  if(respuesta=="si"){
    boleano = true;
  }

  return boleano;
}

double getDouble(string message){
  double doub;

  cout << message << endl;
  cin >> doub;

  return doub;
}

float getFloat(string message){
  float floa;

  cout << message << endl;
  cin >> floa;

  return floa;
}

char getChar(string message){
  char caracter;

  cout << message << endl;
  cin >> caracter;

  return caracter;
}

std::string getString(string message){
  string text;

  cout << message << endl;
  cin >> text;

  return text;
}

bool isVocal(char caracte){
  if(caracte=='a' || caracte=='e' || caracte=='i' || caracte=='o' || caracte=='u' || caracte=='A' || caracte=='E'
      || caracte=='I' || caracte=='O' || caracte=='U' ){
    return true;
      } else {
        return false;
      }
}

#endif