cmake_minimum_required(VERSION 3.14)

project(Pong VERSION 0.1 LANGUAGES CXX)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ${CMAKE_SOURCE_DIR}/Libs/SFML/lib/cmake/SFML)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Source)
