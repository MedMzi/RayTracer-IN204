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
    World.cpp
    RayIntersect.cpp
)

# Include directories
target_include_directories(raytracer PRIVATE ${CMAKE_SOURCE_DIR})

# Find and link tinyxml2 using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(TINYXML2 REQUIRED tinyxml2)

include_directories(${TINYXML2_INCLUDE_DIRS})
link_directories(${TINYXML2_LIBRARY_DIRS})

target_link_libraries(raytracer PRIVATE ${TINYXML2_LIBRARIES})