cmake_minimum_required(VERSION 3.25.2)

project(hello-world VERSION 0.1.0 LANGUAGES CXX)

add_executable(check-kernel-vadd main.cpp)
target_link_libraries(check-kernel-vadd PRIVATE OpenCL)
target_include_directories(check-kernel-vadd PRIVATE "/usr/include")
