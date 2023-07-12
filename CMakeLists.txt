cmake_minimum_required(VERSION 3.16)
project("VolnaApp")

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE INCLUDE src/*.hpp)

add_executable(VolnaApp "${SOURCES}" "${INCLUDE}")