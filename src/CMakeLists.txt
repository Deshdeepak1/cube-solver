add_executable(CubeSolver main.cpp
    ui/cli.cpp
    ui/tui.cpp
    model/Cube.cpp
    model/Cube1DArray.cpp
    model/Cube3DArray.cpp
    model/CubeBitboard.cpp
    model/CubeFactory.cpp
    pattern_databases/math.cpp
    pattern_databases/NibbleArray.cpp
    pattern_databases/PatternDatabase.cpp
    pattern_databases/CornerPatternDatabase.cpp
    pattern_databases/CornerDBMaker.cpp
)



target_include_directories(CubeSolver PRIVATE
    model
    pattern_databases
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(CubeSolver PRIVATE
    ${Boost_LIBRARIES}
    ftxui::screen
    ftxui::dom
    ftxui::component
)

target_link_options(CubeSolver PRIVATE -static)

add_custom_command(TARGET CubeSolver POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCE_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/databases
)

install(TARGETS CubeSolver
    DESTINATION bin
)


