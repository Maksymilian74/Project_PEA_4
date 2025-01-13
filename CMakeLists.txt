cmake_minimum_required(VERSION 3.27)
project(Projekt_PEA_4)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekt_PEA_4
        Algorithms/Algorithms.cpp
        Algorithms/Algorithms.h
        Main/Main.cpp
        Main/Menu.cpp
        Main/Menu.h
        Structures/Matrix.cpp
        Structures/Matrix.h
        Utils/ReadFile.h
        Utils/ReadFile.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static")
