cmake_minimum_required(VERSION 3.14)

set(SOURCES
        App.h
        App.cpp)

add_library(App ${SOURCES})

target_link_libraries(
        App
        SFML
        GameController
)

target_include_directories(App PUBLIC ./)