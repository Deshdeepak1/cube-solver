cmake_minimum_required(VERSION 3.29)
project(CubeSolver
    VERSION 0.6
    DESCRIPTION "Rubik's Cube Solver"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_definitions(
PROJECT_VERSION="${PROJECT_VERSION}"
PROJECT_NAME="${PROJECT_NAME}"
)



add_executable(CubeSolver main.cpp
    model/Cube.cpp
    model/Cube1dArray.cpp
    model/Cube3dArray.cpp
    model/CubeBitboard.cpp
    pattern_databases/math.cpp
    pattern_databases/NibbleArray.cpp
    pattern_databases/PatternDatabase.cpp
    pattern_databases/CornerPatternDatabase.cpp
    pattern_databases/CornerDBMaker.cpp
)
target_include_directories(CubeSolver PRIVATE model)
target_link_libraries(CubeSolver PUBLIC "-static")
