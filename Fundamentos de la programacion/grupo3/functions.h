//
// Created by jmart on 23/09/2024.
//
#include <iostream>
#include <string>

using namespace std;

int getInt(string message){
  int inter;

  cout << message << endl;
  cin >> inter;

  return 0;
}

double getDouble(string message){
  double doub;

  cout << message << endl;
  cin >> doub;

  return doub;
}

std::string getString(string message){
  string text;

  cout << message << endl;
  cin >> text;

  return text;
}