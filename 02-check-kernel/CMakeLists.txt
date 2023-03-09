cmake_minimum_required(VERSION 3.25.2)

project(hello-world VERSION 0.1.0 LANGUAGES CXX)

add_executable(check-kernel-cl main.cpp)
target_link_libraries(check-kernel-cl PRIVATE OpenCL)
target_include_directories(check-kernel-cl PRIVATE "/usr/include")
