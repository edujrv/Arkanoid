
#ifndef ARKANOID_VIDAS_H
#define ARKANOID_VIDAS_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Vidas {
private:
    Texture tVida;
    Sprite sVida;
    bool estado = true; // true vivo - false muerto.
    float posX = 15;
    float posY = 15;
    int idVida = 0;

public:
     explicit Vidas(int idVida);
     void setEstado(bool nuevoEstado);
     void draw(RenderWindow *w);
};


#endif //ARKANOID_VIDAS_H



/*
 * set estado
 * constructor = new vida
 * dibujar
 * /
**/

