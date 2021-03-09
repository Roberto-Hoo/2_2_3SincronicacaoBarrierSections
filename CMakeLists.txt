cmake_minimum_required(VERSION 3.17)
project(2_2_3SincronicacaoBarrierSections)

add_executable(2_2_3SincronicacaoBarrierSections SincronicacaoBarrierSections.cpp)

# Acesso ao OpenMP
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")
set (SOURCE_FILES SincronicacaoBarrierSections.cpp)