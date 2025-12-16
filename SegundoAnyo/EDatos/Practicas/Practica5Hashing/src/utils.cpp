//
// Created by jmart on 18/10/2025.
//
#include "../include/utils.h"
#include <algorithm>
#include <cctype>
#include <sstream>

namespace utils {

    char toLow(unsigned char c){
        return static_cast<char>(std::tolower(c));
    }

    void toLowerInPlace(std::string &s){
        std::transform(s.begin(),s.end(),s.begin(),[](unsigned char c){return toLow(c);});
    }

    std::string lowerCopy(std::string s){
        toLowerInPlace(s);
        return s;
    }

    bool iContains(const std::string &h,const std::string &n) {
        bool val = true;
        if(!n.empty()){
            std::string haystack = h;
            std::string needle = n;
            toLowerInPlace(haystack);
            toLowerInPlace(needle);
            val = haystack.find(needle) != std::string::npos;
        }
        return val;
    }

    std::string cleanToken(std::string_view t) {
        std::string out;
        out.reserve(t.size());
        for (std::string::size_type i = 0; i < t.size(); ++i) {
            unsigned char c = static_cast<unsigned char>(t[i]);
            if (std::isalnum(c)) {
                out.push_back(static_cast<char>(std::tolower(c)));
            }
        }
        return out;
    }

    std::vector<std::string> splitTerms(std::string_view text) {
        std::vector<std::string> terms;

        // Pasamos a std::string para usar istringstream cómodamente
        std::string s(text);
        std::istringstream iss(s);

        std::string tok;
        while (iss >> tok) {
            std::string cleaned = cleanToken(tok);
            if (!cleaned.empty()) terms.push_back(cleaned);
        }
        return terms;
    }

}
