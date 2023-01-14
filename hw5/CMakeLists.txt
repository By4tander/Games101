cmake_minimum_required(VERSION 3.10)
if (WIN32)
    include("E:/Git_Repos/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif ()
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

include_directories(../deps)
include_directories(OpenCV_INCLUDE_DIRS)

add_executable(RayTracing main.cpp Object.hpp Vector.hpp Sphere.hpp global.hpp Triangle.hpp Scene.cpp Scene.hpp Light.hpp Renderer.cpp)