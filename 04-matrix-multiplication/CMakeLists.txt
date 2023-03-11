cmake_minimum_required(VERSION 3.25.2)

project(matmul VERSION 0.1.0 LANGUAGES CXX)

add_executable(matmul main.cpp)
target_link_libraries(matmul PRIVATE OpenCL)
target_include_directories(matmul PRIVATE "/usr/include")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/vadd.cl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
