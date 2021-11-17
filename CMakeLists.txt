cmake_minimum_required(VERSION 3.20)
project(LINFO1252_projet C)

set(CMAKE_C_STANDARD 99)

add_executable(
        LINFO1252_projet
        philosophers/src/main.c
        philosophers/headers/main.h
        producers_consumers/src/prod_cons.c producers_consumers/headers/prod_cons.h)
