cmake_minimum_required(VERSION 2.8.11)
project(Raytracer)

include_directories(include src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

file(GLOB_RECURSE srcFiles src/**.cpp)

add_executable(Raytracer ${srcFiles})
target_link_libraries(Raytracer pthread X11)
