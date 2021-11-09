cmake_minimum_required(VERSION 3.10)
project(ED2021)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ED2021
        "src/main.cpp"
        "src/Timer.cpp"
        "src/Timer.h" "src/Leitura.h" "src/Leitura.cpp" "src/cabecalhos_basicos.h" "src/Parametros_constantes.h" )
