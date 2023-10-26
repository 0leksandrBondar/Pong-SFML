cmake_minimum_required(VERSION 3.14)

set(SOURCES Player.cpp)

add_library(Players ${SOURCES})

target_link_libraries(
        Players
        SFML
        GameController
)

target_include_directories(Players PUBLIC ./)