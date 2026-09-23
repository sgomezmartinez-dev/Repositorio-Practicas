cmake_minimum_required(VERSION 3.16)

project(_PRACTICA3_ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(_PRACTICA3_ main.cpp
    ejercicio_rle.h ejercicio_rle.cpp
    ejercicio_lz78.h ejercicio_lz78.cpp
    encriptacion_desencriptacion.h encriptacion_desencriptacion.cpp)

include(GNUInstallDirs)
install(TARGETS _PRACTICA3_
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
