cmake_minimum_required(VERSION 3.20)
project(prog1)

set(CMAKE_CXX_STANDARD 11)

add_executable(prog1 main.cpp Queue.h List.h CircularArray.h)
