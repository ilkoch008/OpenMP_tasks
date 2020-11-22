cmake_minimum_required(VERSION 3.17)
project(lab_MPI C)

set(CMAKE_C_STANDARD 11)

find_package(MPI)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(lab_MPI 2d.c)

target_link_libraries(lab_MPI ${MPI_C_LIBRARIES})