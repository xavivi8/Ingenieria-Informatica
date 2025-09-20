//
// Created by jmart on 02/12/2024.
//

#ifndef LIBRARYMENU_H
#define LIBRARYMENU_H

#include <iostream>
#include <list>
#include <string>
#include <vector>

template <typename T>
void menu(
    const std::vector<std::string>& statement
    ,const std::vector<T>& options
    ,const std::string exitOpt
) {
  if (statement.size() != options.size()) {
    std::cerr << "Error: ¡¡¡Care about size of statements and options!!! Must be the same." << std::endl;
    return;
  }

  int currentOpt;

  do {
    std::cout << "Menu:" << std::endl;
    for (size_t i = 0; i < options.size(); ++i) {
      std::cout << options[i] << ": " << statement[i] << std::endl;
    }

    std::cout << "Select an option: ";
    std::cin >> currentOpt;

    if (currentOpt < 1 || currentOpt > static_cast<int>(options.size())) {
      std::cout << "Invalid option. Please select a number between 1 and " << options.size() << "." << std::endl;
    } else {
      std::cout << "Selected: " << options[currentOpt - 1] << " - " << statement[currentOpt - 1] << std::endl;
    }

    // TODO corregir que elijas tú q número es salir
  } while (options[currentOpt - 1] != exitOpt);
}

//void menu();


#endif //LIBRARYMENU_H
