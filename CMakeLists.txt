cmake_minimum_required(VERSION 3.14)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 14)

include_directories( "D:\\Program Files (x86)\\JetBrians\\CLion 2019.2\\mingw32\\include")

add_executable(mySFML main.cpp Playerbar.cpp Playerbar.h Ball.cpp Ball.h)

target_link_libraries(mySFML sfml-graphics sfml-window sfml-system)