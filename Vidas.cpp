
#include "Vidas.h"
//#include <SFML/Graphics.hpp>

//using namespace sf;

Vidas::Vidas(int idVida) {

    tVida.loadFromFile("imagenes/vida.png");
    sVida.setTexture(tVida);
    sVida.setScale(0.13 , 0.13);
    posY = posY + (float)(tVida.getSize().y * idVida);
    sVida.setPosition(posX , posY);
    estado = true;

}

void Vidas::setEstado(bool nuevoEstado) {
    this->estado = nuevoEstado;
}

void Vidas::draw(RenderWindow *w) {
    if(estado){
        tVida.loadFromFile("imagenes/vida.png");
    }else{
        tVida.loadFromFile("imagenes/vidaPerdida.png");
    }
    w->draw(sVida);
}
