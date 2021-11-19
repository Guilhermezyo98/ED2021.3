cmake_minimum_required(VERSION 3.10)
project(ED2021)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(ED2021
        "src/main.cpp"
        "src/Timer.cpp"
        "src/Timer.h" "src/Leitura.h" "src/Leitura.cpp"  "src/Parametros_constantes.h"  "src/Leitura_Legacy.cpp")