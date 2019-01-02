cmake_minimum_required(VERSION 3.12)
project(computer_graphics)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(computer_graphics main.cpp Vec.cpp Vec.h ReferenceSystem.h Planet.h Test.h DistanceCalculator.h Matrix.h exception.h imaging/imaging.cpp render/Plane.h render/tests/render_test.cpp render/Render.h render/RandomNumber.h render/Square.h)

add_executable(geometry_test tests/geometry_test.cpp Vec.cpp Vec.h ReferenceSystem.h Planet.h Test.h DistanceCalculator.h Matrix.h)

add_executable(imaging imaging/imaging.cpp imaging/Image.h imaging/RGB.h)

add_executable(imaging_test imaging/tests/image_test.cpp imaging/Image.h imaging/RGB.h)

add_executable(render_test render/tests/render_test.cpp render/Plane.h render/Sphere.h Vec.cpp Vec.h ReferenceSystem.h exception.h render/Render.h render/Light.h render/Object.h render/RandomNumber.h)