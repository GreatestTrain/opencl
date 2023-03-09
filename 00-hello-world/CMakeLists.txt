cmake_minimum_required(VERSION 3.25.2)

project(hello-world VERSION 0.1.0 LANGUAGES CXX)

add_executable(hello-world-cl main.cpp)
target_link_libraries(hello-world-cl PRIVATE OpenCL)
target_include_directories(hello-world-cl PRIVATE "/usr/include")