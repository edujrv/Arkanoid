cmake_minimum_required(VERSION 3.14)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML REQUIRED COMPONENTS system graphics window audio)
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(mySFML main.cpp Playerbar.cpp Playerbar.h Ball.cpp Ball.h)

target_link_libraries(mySFML sfml-graphics sfml-window sfml-system sfml-audio)

file(GLOB IMAGENES "imagenes/*")
file(COPY ${IMAGENES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/imagenes)