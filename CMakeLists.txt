cmake_minimum_required(VERSION 3.14)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML REQUIRED COMPONENTS system graphics window audio)
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(mySFML main.cpp Playerbar.cpp Playerbar.h Ball.cpp Ball.h Menu.cpp Menu.h Textos.cpp Textos.h Vidas.cpp
        Vidas.h Nodo.h Stack.h Ladrillo.cpp Ladrillo.h LinkedList.h Queue.h IconPower.cpp IconPower.h)

target_link_libraries(mySFML sfml-graphics sfml-window sfml-system sfml-audio)

file(GLOB IMAGENES "imagenes/*")
file(COPY ${IMAGENES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/imagenes)

file(GLOB AUDIOS "audios/*")
file(COPY ${AUDIOS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/audios)

file(GLOB FUENTES "fuentes/*")
file(COPY ${FUENTES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fuentes)

file(GLOB TEXTOS "textos/*")
file(COPY ${TEXTOS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/textos)