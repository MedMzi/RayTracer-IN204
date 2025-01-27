cmake_minimum_required(VERSION 3.10)

# Project name
project(RayTracer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find TinyXML2 package
set(TINYXML2_INCLUDE_DIR /usr/include)
set(TINYXML2_LIBRARY /usr/lib/x86_64-linux-gnu/libtinyxml2.so) 

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
    Material.cpp
    loadScene.cpp
)

# Include directories
target_include_directories(raytracer PRIVATE ${TINYXML2_INCLUDE_DIR})
target_include_directories(raytracer PRIVATE ${CMAKE_SOURCE_DIR})

# Link TinyXML2 library
target_link_libraries(raytracer PRIVATE ${TINYXML2_LIBRARY})
