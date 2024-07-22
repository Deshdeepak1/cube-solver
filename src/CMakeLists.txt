cmake_minimum_required(VERSION 3.29)
project(CubeSolver
    VERSION 0.1
    DESCRIPTION "Rubik's Cube Solver"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_definitions(
PROJECT_VERSION="${PROJECT_VERSION}"
PROJECT_NAME="${PROJECT_NAME}"
)

include_directories(model)

add_executable(CubeSolver main.cpp
    model/Cube.cpp
)

