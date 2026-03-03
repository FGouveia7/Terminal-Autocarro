cmake_minimum_required(VERSION 3.30)
project(AutocarrosV2)

set(CMAKE_CXX_STANDARD 20)

add_executable(AutocarrosV2 1main.cpp
        2estruturas.h
        3nomes.cpp
        3nomes.h
        4passageiro.cpp
        4passageiro.h
        5autocarros.cpp
        5autocarros.h
        6matricula.cpp
        6matricula.h
        7arvorebinaria.cpp
        7arvorebinaria.h
        8paragem.cpp
        8paragem.h
        9menus.cpp
        9menus.h
        10imprimir.cpp
        10imprimir.h
)
