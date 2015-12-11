cmake_minimum_required(VERSION 2.8.11)
project(Raytracer)

include_directories(include)

file(GLOB_RECURSE srcFiles src/**.cpp)

add_executable(Raytracer ${srcFiles})
target_link_libraries(Raytracer pthread X11)