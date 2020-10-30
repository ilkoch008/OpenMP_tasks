cmake_minimum_required(VERSION 3.17)
project(task7 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp ")

set(SOURCE_FILES main.c)

add_executable(task7 ${SOURCE_FILES})

target_link_libraries(task7 mingw32 SDL2main SDL2)
