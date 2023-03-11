cmake_minimum_required(VERSION 3.25.2)

project(02-check-kernel VERSION 0.1.0 LANGUAGES CXX)

add_executable(check-kernel-cl main.cpp)
target_link_libraries(check-kernel-cl PRIVATE OpenCL)
target_include_directories(check-kernel-cl PRIVATE "/usr/include")

add_test(
    NAME check-kernel-test
    COMMAND check-kernel-cl
)

enable_testing()
