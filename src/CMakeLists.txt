cmake_minimum_required(VERSION 4.0 FATAL_ERROR)

project(catngrep VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/release")
add_executable(cat cat.cpp cat.hpp)
add_executable(grep grep.cpp grep.hpp)