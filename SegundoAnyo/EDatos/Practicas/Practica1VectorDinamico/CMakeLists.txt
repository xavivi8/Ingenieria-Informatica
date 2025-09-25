cmake_minimum_required(VERSION 3.29)
project(Practica1VectorDinamico)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Practica1VectorDinamico
        main.cpp
        VDinamico.h
        PaMedicamento.h)