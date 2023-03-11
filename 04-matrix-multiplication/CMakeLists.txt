cmake_minimum_required(VERSION 3.25.2)

project(matmul VERSION 0.1.0 LANGUAGES CXX)

add_executable(matmul main.cpp)
target_link_libraries(matmul PRIVATE OpenCL)
target_include_directories(matmul PRIVATE "/usr/include")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/matmul.cl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/matrices" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_test(NAME matmul_test COMMAND ./04-matrix-multiplication/matmul ./build/04-matrix-multiplication/matmul.cl ./build/04-matrix-multiplication/matrices/a.matrix
./build/04-matrix-multiplication/matrices/b.matrix
)
