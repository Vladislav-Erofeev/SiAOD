cmake_minimum_required(VERSION 3.23)
project(SiAOD)

set(CMAKE_CXX_STANDARD 14)

add_executable(SiAOD main.cpp prac6/prac6_1.h prac6/prac6_2.h "prac4/Tree.h" "prac4/prac4.cpp" "prac4/prac4.h")
