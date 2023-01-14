cmake_minimum_required(VERSION 3.10)
if (WIN32)
    include("E:/Git_Repos/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif ()
project(BezierCurve)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 14)

include_directories(../deps)
include_directories(OpenCV_INCLUDE_DIRS)

add_executable(BezierCurve main.cpp)

target_link_libraries(BezierCurve ${OpenCV_LIBRARIES})
