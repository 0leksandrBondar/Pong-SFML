cmake_minimum_required(VERSION 3.14)

add_executable(Pong main.cpp)

target_link_libraries(
        Pong
        SFML
)