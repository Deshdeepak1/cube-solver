cmake_minimum_required(VERSION 3.10)

set(VERSION_MAJOR 2)
set(VERSION_MINOR 1)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR})

project(CubeSolver
    VERSION ${VERSION}
    DESCRIPTION "Rubik's Cube Solver"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS program_options)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/arthursonzogni/ftxui.git
  # GIT_TAG        v5.0.0
  GIT_TAG     main
  GIT_PROGRESS   TRUE
  GIT_SHALLOW    TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(ftxui)
# ------------------------------------------------------------------------------


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(DATABASES "../share/CubeSolver/databases")
else()
    set(DATABASES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/databases")
endif()

add_compile_definitions(
    PROJECT_VERSION="${PROJECT_VERSION}"
    PROJECT_NAME="${PROJECT_NAME}"
    DATABASES="${DATABASES}"
)

set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources/databases")


add_subdirectory(src)

install(DIRECTORY ${RESOURCE_DIR}/
    DESTINATION share/CubeSolver/databases
)


set(CPACK_GENERATOR "TGZ;ZIP;DEB")
set(CPACK_PACKAGE_NAME "CubeSolver")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VENDOR "Deshdeepak")
set(CPACK_PACKAGE_CONTACT "rkdeshdeepak1@gmail.com")
set(CPACK_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/package")

include(CPack)
