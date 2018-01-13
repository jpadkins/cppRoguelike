cmake_minimum_required(VERSION 2.6)
project(roguelike)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -Wconversion -pedantic -O2 -g")

# Source files
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR})
file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/*.cpp
        ${PROJECT_SOURCE_DIR}/*.hpp)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# SFML 2.x
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

# Lua
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# Define executable
add_executable(roguelike ${SOURCES})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Link libraries
target_link_libraries(roguelike m)
target_link_libraries(roguelike dl)
target_link_libraries(roguelike ${SFML_LIBRARIES})
target_link_libraries(roguelike ${LUA_LIBRARIES})
