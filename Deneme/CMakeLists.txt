cmake_minimum_required(VERSION 3.8)
project(Deneme)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Monster.cpp Monster.h)
add_executable(Deneme ${SOURCE_FILES})