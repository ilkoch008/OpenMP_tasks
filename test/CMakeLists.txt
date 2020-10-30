cmake_minimum_required(VERSION 3.17)
project(test C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp ")

add_executable(test main.c)