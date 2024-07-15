cmake_minimum_required(VERSION 3.5.0)
project(data-structures VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()
add_executable(data-structures main.cpp)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(external/googletest)
