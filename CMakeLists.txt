cmake_minimum_required(VERSION 4.4)
project(asciize LANGUAGES CXX)

set(SOURCES
    src/main.cpp
    src/get_luminance.cpp
    src/render.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)
