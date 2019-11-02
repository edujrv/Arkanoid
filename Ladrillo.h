

#ifndef ARKANOID_LADRILLO_H
#define ARKANOID_LADRILLO_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Ladrillo {
private:
    float posX;
    float posY;
    Texture tLadri;
    Sprite sLadri;
    float xLong;
    float yLong;

public:
    explicit Ladrillo(float posX, float posY, int idLadrilloX, int idLadrilloY);
    Ladrillo();
    void draw(RenderWindow *w);
    float  getX();
    float getY();
    float  getXLong();
    float  getYLong();
    ~Ladrillo();
};


#endif //ARKANOID_LADRILLO_H
