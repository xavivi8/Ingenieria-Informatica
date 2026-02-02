//
// Created by jmart on 18/10/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <string_view>
#include <vector>

namespace utils{

     /**
     * @brief Convierte un carácter a minúscula de forma segura.
     * @param c Carácter de entrada (debe ser convertible a unsigned char).
     * @return El mismo carácter en minúscula (si procede).
     * @post Usa std::tolower pero recibiendo 'unsigned char' para evitar comportamiento indefinido.
     */
    char toLow(unsigned char c);

    /**
     * @brief Convierte una cadena a minúsculas "in-place".
     * @param s Cadena a normalizar (se modificará).
     * @post Todas las letras ASCII de 's' quedan en minúscula.
     * @warning No realiza normalización Unicode (solo transformación byte a byte).
     */
    void toLowerInPlace(std::string &s);

    /**
     * @brief Devuelve una COPIA de la cadena en minúsculas.
     * @param s Cadena de entrada (se pasa por valor para copiar).
     * @return Nueva cadena idéntica a 's' pero con letras en minúscula.
     * @post No modifica el argumento del llamante, trabaja sobre la copia.
     */
    std::string lowerCopy(std::string s);

    /**
     * @brief Comprueba si 'haystack' contiene 'needle' sin distinguir mayúsculas/minúsculas.
     * @param haystack Cadena "pajar" donde buscar.
     * @param needle   Cadena "aguja" a localizar como subcadena.
     * @return true si 'needle' aparece en 'haystack' (case-insensitive); false en caso contrario.
     * @post La búsqueda se hace convirtiendo copias a minúsculas y usando std::string::find.
     * @note Política con needle vacío: devuelve true (toda cadena contiene la subcadena vacía).
     */
    bool iContains(const std::string &haystack,const std::string &needle);

    /**
     * @brief Limpia un token eliminando caracteres no alfanuméricos y convirtiendo a minúsculas.
     * @param t Token de entrada.
     * @return Nueva cadena con solo caracteres alfanuméricos en minúscula.
     * @post Se eliminan todos los caracteres que no sean letras o dígitos (según std::isalnum).
     * @note No realiza normalización Unicode (tildes/ñ se procesan byte a byte).
     */
    std::string cleanToken(const std::string &t);

    /**
     * @brief Divide un texto en tokens limpios separados por espacios.
     * @param text Texto de entrada.
     * @return Vector de cadenas con los tokens limpios.
     * @post Cada token se limpia usando cleanToken() y se descartan tokens vacíos.
     * @note La división se realiza por espacios usando un flujo (std::istringstream).
     */
    std::vector<std::string> splitTerms(const std::string &text);
}

#endif //UTILS_H
