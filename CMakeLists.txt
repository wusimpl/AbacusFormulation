cmake_minimum_required(VERSION 3.19)
project(abacus)

set(CMAKE_CXX_STANDARD 11)

add_executable(abacus addition.cpp subtraction.cpp base.h addition.h base.cpp subtraction.h main.cpp)