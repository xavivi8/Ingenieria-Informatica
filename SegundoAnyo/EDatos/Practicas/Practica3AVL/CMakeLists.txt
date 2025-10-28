cmake_minimum_required(VERSION 3.29)
project(Practica3AVL)

set(CMAKE_CXX_STANDARD 14)

# Directorio de headers
include_directories(include)

# Archivos fuente
add_executable(Practica3AVL
        src/main.cpp
        src/MediExpress.cpp
        src/PaMedicamento.cpp
        src/Laboratorio.cpp
        src/utils.cpp
        src/Farmacia.cpp
)