cmake_minimum_required(VERSION 3.25.2)

project(opencl-tasks VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

include_directories(BEFORE PUBLIC src/include)

add_subdirectory(00-hello-world)
add_subdirectory(01-check-opencl)
add_subdirectory(02-check-kernel)
add_subdirectory(03-vadd-kernel)

