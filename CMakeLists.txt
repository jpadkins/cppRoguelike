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

# SFML 2.x
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

# Boost
set(BOOST_USE_STATIC_LIBS OFF)
set(BOOST_USE_MULTITHREADED ON)
set(BOOST_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS system filesystem REQUIRED)

# Define executable
add_executable(roguelike ${SOURCES})

# Link libraries
target_link_libraries(roguelike m)
target_link_libraries(roguelike dl)
target_link_libraries(roguelike ${SFML_LIBRARIES})
target_link_libraries(roguelike
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY})
