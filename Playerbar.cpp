#include "Playerbar.h"


//Builder.
Playerbar::Playerbar(RenderWindow* w, Texture *texturaPlayerbar, float playerbarSize) {
    //Sprite Loading.
    sPlayerbar.setTexture(*texturaPlayerbar);
    //Object Size.
    sPlayerbar.setScale(0.2,0.5);

    //Initial Variables.
    float xPlayerbar=(float) (w->getSize().x / 2) - (playerbarSize / 2);
    float yPlayerbar=(float) w->getSize().y - 100;
    this->xPlayerbar = xPlayerbar;
    this->yPlayerbar = yPlayerbar;
    this->tPlayerbar=*texturaPlayerbar;
    this->longPlayerbar=getLongX(texturaPlayerbar);
    this->highPLayerbar=getLongY(texturaPlayerbar);
    this->playerbarSize=playerbarSize;
    velPlayerbar = 10;
    longPlayerbar = 0;
    direccion = ' ';
                                                                                    }//End Builder.


//Mover.
float Playerbar::mover(char direccion) {
    //Actions for d and i.
    this->direccion = direccion;
    if (direccion == 'd'){
        xPlayerbar += velPlayerbar;
                        }else if (direccion == 'i') {
        xPlayerbar -= velPlayerbar;
    }//End ElseIf.

    //Returns new playerbar position.
    return xPlayerbar;
                        }//End Mover.


//Dibujar.
void Playerbar::dibujar(RenderWindow *w) {
    //Spray Position.
    sPlayerbar.setPosition(xPlayerbar, yPlayerbar);
    //Drawing.
    w->draw(sPlayerbar);

                                        }//End Dibujar.


//getLongX.
float Playerbar::getLongX(Texture *texturaPlayer) {
    longPlayerbar = texturaPlayer->getSize().x;
    return longPlayerbar;
                                                 }

float Playerbar::getLongY(Texture *texturaPlayerbar) {
    highPLayerbar = texturaPlayerbar->getSize().y;
    return highPLayerbar;
}
//End getLongX.

//Centrar.
void Playerbar::centrar(RenderWindow* w, Playerbar playerbar) {
    xPlayerbar= (w->getSize().x / 2) - (playerbarSize / 2);
}
//End Centrar.

//Destroyer.
Playerbar::~Playerbar() = default;
//End Destroyer.
