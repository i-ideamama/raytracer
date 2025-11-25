cmake_minimum_required(VERSION 3.10)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(raytracer 
    src/main.cpp
)

target_include_directories(raytracer PRIVATE
    src/materials
    src/objects
    src/utils
    src/world
)

target_link_libraries(raytracer PUBLIC OpenMP::OpenMP_CXX)


