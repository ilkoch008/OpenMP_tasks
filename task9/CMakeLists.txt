cmake_minimum_required(VERSION 3.17)
project(task9 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

add_executable(task9  bugged6.c )

# main.c bugged1.c bugged2.c bugged3.c bugged4.c bugged5.c bugged6.c
