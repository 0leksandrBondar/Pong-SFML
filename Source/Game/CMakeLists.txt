cmake_minimum_required(VERSION 3.14)

add_executable(Pong main.cpp)

target_link_libraries(
        Pong
        SFML
        App
)

add_custom_command(TARGET Pong PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/Resource
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/Resource
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resource
        ${CMAKE_CURRENT_BINARY_DIR}/Resource)

add_custom_target(
        Copy-Assets
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/Resource
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/Resource
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resource
        ${CMAKE_CURRENT_BINARY_DIR}/Resource
)

add_custom_command(TARGET Pong PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/Libs/SFML/bin"
        $<TARGET_FILE_DIR:Pong>)