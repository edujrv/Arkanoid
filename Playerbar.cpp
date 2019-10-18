
#include "Playerbar.h"


//Builder.
Playerbar::Playerbar(float xPlayerbar, float yPlayerbar, Texture *texturaPlayerbar) {
    //Sprite Loading.
    sPlayerbar.setTexture(*texturaPlayerbar);
    //Object Size.
    sPlayerbar.setScale(0.2,0.5);

    //Initial Variables.
    this->xPlayerbar = xPlayerbar;
    this->yPlayerbar = yPlayerbar;
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
void Playerbar::centrar(float desktopX, float playerbarSize) {
    xPlayerbar= (desktopX / 2) - (playerbarSize / 2);
}
//End Centrar.

//Destroyer.
Playerbar::~Playerbar() = default;
//End Destroyer.
