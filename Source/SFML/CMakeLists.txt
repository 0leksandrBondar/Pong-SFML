cmake_minimum_required(VERSION 3.14)

find_package(SFML COMPONENTS audio system window graphics network REQUIRED)

add_library(SFML INTERFACE)

target_link_libraries(SFML INTERFACE
        sfml-system
        sfml-window
        sfml-graphics
        sfml-network
        sfml-audio
)