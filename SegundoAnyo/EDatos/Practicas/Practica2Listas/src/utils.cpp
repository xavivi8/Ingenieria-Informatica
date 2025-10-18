//
// Created by jmart on 18/10/2025.
//
#include "../include/utils.h"
#include <algorithm>
#include <cctype>

namespace utils {

    char toLow(unsigned char c){
        return static_cast<char>(std::tolower(c));
    }
}
