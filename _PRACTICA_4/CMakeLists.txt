cmake_minimum_required(VERSION 3.16)

project(_PRACTICA_4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(_PRACTICA_4 main.cpp
    Enrutador.h Enrutador.cpp
    Red.h Red.cpp)

include(GNUInstallDirs)
install(TARGETS _PRACTICA_4
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
