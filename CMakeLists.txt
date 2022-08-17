cmake_minimum_required(VERSION 3.19)
project(abacus)
set(CMAKE_CXX_STANDARD 11)
add_executable(abacus addition.cpp subtraction.cpp base.h addition.h base.cpp subtraction.h main.cpp radication.cpp radication.h multiplication.cpp multiplication.h division.cpp division.h)

add_executable(Generate base.h base.cpp subtraction.cpp subtraction.h addition.cpp addition.h GenerateTestFile.cpp)