# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8)

# Project's name
project(CruiseControl)


# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${./cmake/bin)
set(EXECUTABLE_OUTPUT_PATH ${./cmake/output})
set(LIBRARY_OUTPUT_PATH ${./cmake/lib})

# The following folder will be included
include_directories("${./node1/header}")
include_directories("${./node2/header}")