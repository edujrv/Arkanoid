cmake_minimum_required(VERSION 3.14)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 14)

include_directories( "C:\\Users\\Camilo\\Downloads\\INFO\\mingw64\\include")

add_executable(mySFML main.cpp Playerbar.cpp Playerbar.h Ball.cpp Ball.h)

target_link_libraries(mySFML sfml-graphics sfml-window sfml-system)