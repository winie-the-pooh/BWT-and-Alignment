cmake_minimum_required(VERSION 3.15)
project(WFA_alignment)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Release")

include_directories(WFA)
add_subdirectory(WFA)

add_executable(WFA_alignment main.cpp)
target_link_libraries(WFA_alignment wfa)

add_executable(Test tester.cpp)
target_link_libraries(Test wfa)