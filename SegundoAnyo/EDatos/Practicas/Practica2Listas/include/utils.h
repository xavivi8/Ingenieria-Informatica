//
// Created by jmart on 18/10/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <string_view>

namespace utils{

    char toLow(unsigned char c);

    void toLowerInPlace(std::string &s);

    std::string lowerCopy(std::string s);

    bool iContains(const std::string &haystack,const std::string &needle);

}

#endif //UTILS_H
