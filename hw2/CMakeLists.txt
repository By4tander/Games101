cmake_minimum_required(VERSION 3.10)
if (WIN32)
    include("E:/Git_Repos/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif ()
project(Rasterizer)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories(../deps)
include_directories(OpenCV_INCLUDE_DIRS)

add_executable(Rasterizer main.cpp rasterizer.hpp rasterizer.cpp global.hpp Triangle.hpp Triangle.cpp)
target_link_libraries(Rasterizer ${OpenCV_LIBRARIES})
