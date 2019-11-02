//
// Created by edu on 1/11/19.
//

#include "Ladrillo.h"

Ladrillo::Ladrillo(float posX, float posY, int idLadrilloX, int idLadrilloY) {

    tLadri.loadFromFile("imagenes/Brick1.png");
    sLadri.setTexture(tLadri);
    sLadri.setScale(0.75,0.75);
    xLong = (float) (tLadri.getSize().x * 0.75) + 1;
    yLong = (float) (tLadri.getSize().y * 0.75);

    this->posX = posX + (xLong * (float) idLadrilloX);
    this->posY = posY + (yLong * (float) idLadrilloY);
    sLadri.setPosition(this->posX,this->posY);
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

float Ladrillo::getXLong() {
    return yLong;
}

Ladrillo::Ladrillo() = default;

Ladrillo::~Ladrillo() = default;
