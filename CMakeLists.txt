cmake_minimum_required(VERSION 3.20)
project(ED2021)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ED2021
        main.cpp
        Timer.cpp
        Timer.h "Leitura.h" "cabecalhos_basicos.h" "Parametros_constantes.h" "Leitura.cpp")
