
#include "Ladrillo.h"     

Ladrillo::Ladrillo(float posX, float posY, int idLadrilloX, int idLadrilloY, int idLadri, String pic) {

    tLadri.loadFromFile(pic);
    sLadri.setTexture(tLadri);
    sLadri.setScale(0.75,0.75);

    xLong = (float) (tLadri.getSize().x * 0.75);
    yLong = (float) (tLadri.getSize().y * 0.75);

    this->posX = posX + (xLong * (float) idLadrilloX);
    this->posY = posY + (yLong * (float) idLadrilloY);
    sLadri.setPosition(this->posX,this->posY);
    this->idLadri = idLadri;
}

void Ladrillo::draw(RenderWindow *w) {
    w->draw(sLadri);
}

float Ladrillo::getX() {
    return posX;
}

float Ladrillo::getY() {
    return posY;
}

float Ladrillo::getXLong() {
    return xLong;
}

float Ladrillo::getYLong() {
    return yLong;
}

int Ladrillo::getId() {
    return idLadri;
}

Ladrillo::Ladrillo() = default;

Ladrillo::~Ladrillo() = default;
