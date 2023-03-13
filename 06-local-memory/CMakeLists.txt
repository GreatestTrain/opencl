cmake_minimum_required(VERSION 3.25.2)

project(05-private-memory VERSION 0.1.0 LANGUAGES CXX)

add_executable(kernel-1 main.cpp)
target_link_libraries(kernel-1 PRIVATE OpenCL)
target_include_directories(kernel-1 PRIVATE "/usr/include")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/matmul.cl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/matmul_row_private_local.cl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/matrices" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_test(
    NAME matmul-test
    COMMAND kernel-1 "matmul.cl" "matrices/a.matrix" "matrices/b.matrix"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

add_test(
    NAME matmul-row-test
    COMMAND kernel-1 "matmul_row_private_local.cl" "matrices/a.matrix" "matrices/b.matrix"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

enable_testing()
