cmake_minimum_required(VERSION 3.17)
project(NagyHazi C)

set(CMAKE_C_STANDARD 99)

add_executable(NagyHazi main.c datumkezeles.c datumkezeles.h jaratkezeles.c jaratkezeles.h menu.c menu.h fajlkezeles.c fajlkezeles.h validacio.c validacio.h)