cmake_minimum_required(VERSION 3.14)

set(SOURCES
        GameController.h
        GameController.cpp
        Ball.cpp
        Ball.h)

add_library(GameController ${SOURCES})

target_link_libraries(
        GameController
        SFML
        Players
)

target_include_directories(GameController PUBLIC ./)