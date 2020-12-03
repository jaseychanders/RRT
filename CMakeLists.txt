cmake_minimum_required(VERSION 3.17)
project(RRT)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RRT
        README.md main.cpp RRT.cpp RRT.h RandomGenerator.cpp RandomGenerator.h)


