cmake_minimum_required(VERSION 3.14)

set(SOURCES
        MainWindow.h
        MainWindow.cpp)

add_library(Window ${SOURCES})

target_link_libraries(
        Window
        SFML
        GameController
)

target_include_directories(Window PUBLIC ./)