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



target_include_directories(CubeSolver PRIVATE
    model
    pattern_databases
)

target_link_options(CubeSolver PRIVATE -static)

add_custom_command(TARGET CubeSolver POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCE_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/databases
)

install(TARGETS CubeSolver
    DESTINATION bin
)


