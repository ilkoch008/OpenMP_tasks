cmake_minimum_required(VERSION 3.17)
project(task6 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp ")

add_executable(task6 main.c)