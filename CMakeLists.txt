cmake_minimum_required(VERSION 3.14)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 14)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS system graphics window audio)

add_executable(mySFML main.cpp Playerbar.cpp Playerbar.h Ball.cpp Ball.h)

target_link_libraries(mySFML sfml-graphics sfml-audio sfml-window sfml-system -static)

file(GLOB IMAGENES "imagenes/*")
file(COPY ${IMAGENES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/imagenes)