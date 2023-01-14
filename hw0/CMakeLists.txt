cmake_minimum_required (VERSION 3.10)
project (Transformation)

# Use our custom Eigen
include_directories(../deps)

add_executable (Transformation main.cpp)
