cmake_minimum_required(VERSION 3.10)

# Project name
project(RayTracer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
add_executable(raytracer
    main.cpp
    Vect.cpp
    Ray.cpp
    Sphere.cpp
    Rectangle.cpp
    Triangle.cpp
    dotobj.cpp
    Camera.cpp
)

# Include directories
target_include_directories(raytracer PRIVATE ${CMAKE_SOURCE_DIR})
