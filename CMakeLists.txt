#-------------------------------------#
#   Ray-Tracer Build Configuration    #
#                                     #
#   See README.md for instructions    #
#-------------------------------------#
cmake_minimum_required(VERSION 3.10)

project(
  Ray-Tracer
  VERSION 2.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(EXE_NAME rtrender)
list(APPEND SRC_FILES src/main.cpp src/vec3.cpp src/geometry/sphere.cpp
    src/geometry/geometric_list.cpp)

add_executable(${EXE_NAME} ${SRC_FILES})

target_include_directories(${EXE_NAME} PUBLIC external)
