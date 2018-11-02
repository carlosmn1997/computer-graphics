cmake_minimum_required(VERSION 3.12)
project(computer_graphics)

set(CMAKE_CXX_STANDARD 14)

add_executable(computer_graphics main.cpp Vec.cpp Vec.h ReferenceSystem.h Planet.h Test.h DistanceCalculator.h Matrix.h exception.h imaging/imaging.cpp render/render.cpp)

add_executable(geometry_test tests/geometry_test.cpp Vec.cpp Vec.h ReferenceSystem.h Planet.h Test.h DistanceCalculator.h Matrix.h)

add_executable(imaging imaging/imaging.cpp imaging/Image.h imaging/RGB.h)

add_executable(imaging_test imaging/tests/image_test.cpp imaging/Image.h imaging/RGB.h)
