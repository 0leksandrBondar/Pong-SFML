cmake_minimum_required(VERSION 3.14)

set(SOURCES
        GameResultScreen.cpp
        GameResultScreen.h)

add_library(Widgets ${SOURCES})

target_link_libraries(
        Widgets
        SFML
        GameController
)

target_include_directories(Widgets PUBLIC ./)