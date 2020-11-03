cmake_minimum_required(VERSION 3.17)
project(task8 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp -Ofast")

add_executable(task8 main.c all.h)