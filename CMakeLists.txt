cmake_minimum_required(VERSION 3.8)
project(Data_Structures)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Deneme/main.cpp
        Deneme/Monster.cpp
        Deneme/Monster.h "Phone Book/main.cpp")

add_executable(Data_Structures ${SOURCE_FILES})