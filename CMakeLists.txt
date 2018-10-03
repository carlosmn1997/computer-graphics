cmake_minimum_required(VERSION 3.12)
project(computer_graphics)

set(CMAKE_CXX_STANDARD 14)

add_executable(computer_graphics main.cpp Vec.cpp Vec.h ReferenceSystem.h Planet.h Test.h DistanceCalculator.h)