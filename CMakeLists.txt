cmake_minimum_required(VERSION 3.29)
project(OOP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OOP
    Client.cpp
    Client.h
        Camera.h
        Camera.cpp
        Angajat.cpp
        Angajat.h
        Client.cpp
        Client.cpp
        main.cpp
        Persoana.cpp
        Persoana.h
        TipCamera.cpp
        TipCamera.h
        Rezervare.cpp
        Rezervare.h
        Hotel.cpp
        Hotel.h
        IAfisabil.h)
