cmake_minimum_required(VERSION 3.26)
project(Projeto_AED)

set(CMAKE_CXX_STANDARD 14)

include_directories(Files/Header)

add_executable(Projeto_AED
        Files/Header/Airlines.h
        Files/Header/Airports.h
        Files/Header/Display.h
        Files/Header/Flights.h
        Files/Header/Reader.h
        Files/Header/Menu.h
        Files/Source/Airlines.cpp
        Files/Source/Airports.cpp
        Files/Source/Display.cpp
        Files/Source/Flights.cpp
        Files/Source/Reader.cpp
        Files/Source/Menu.cpp
        main.cpp
)
