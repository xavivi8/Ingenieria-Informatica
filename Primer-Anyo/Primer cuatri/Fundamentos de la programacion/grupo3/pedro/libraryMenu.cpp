//
// Created by jmart on 02/12/2024.
//

#include "libraryMenu.h"
#include <string>

int main() {
  std::string input;

  std::vector<std::string> enunciados = {"sumar", "restar", "multiplicar", "Salir"};
  std::vector<std::string> opcionesStr = {"1", "2", "3", "0"};

  menu(
    enunciados
    ,opcionesStr//{"1","2","3","4"}
    ,"0"
    );

/*
  std::cout << "Seleccione una opción: ";
  std::getline(std::cin, input);

    if (input == opcionesStr.back()) {
    std::cout << "Has seleccionado la última opción";
  } else {
    std::cout << "No es última opción";
  }
  */
}
