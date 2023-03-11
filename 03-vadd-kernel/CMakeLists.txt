cmake_minimum_required(VERSION 3.25.2)

project(03-check-kernel VERSION 0.1.0 LANGUAGES CXX)

add_executable(check-kernel-vadd main.cpp)
target_link_libraries(check-kernel-vadd PRIVATE OpenCL)
target_include_directories(check-kernel-vadd PRIVATE "/usr/include")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/vadd.cl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_test(
    NAME vadd-test
    COMMAND check-kernel-vadd "vadd.cl"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)
enable_testing()
