cmake_minimum_required(VERSION 3.25.2)

project(05-private-memory VERSION 0.1.0 LANGUAGES CXX)

add_executable(kernel main.cpp)
target_link_libraries(kernel PRIVATE OpenCL)
target_include_directories(kernel PRIVATE "/usr/include")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/matmul.cl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/matmul_row.cl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/matmul_row_private.cl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/matrices" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_test(
    NAME matmul-test
    COMMAND kernel "matmul.cl" "matrices/a.matrix" "matrices/b.matrix"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

add_test(
    NAME matmul-row-test
    COMMAND kernel "matmul.cl" "matrices/a.matrix" "matrices/b.matrix"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

add_test(
    NAME matmul-row-private-test
    COMMAND kernel "matmul.cl" "matrices/a.matrix" "matrices/b.matrix"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

enable_testing()
