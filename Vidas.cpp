
#include "Vidas.h"


//using namespace sf;

Vidas::Vidas( RenderWindow* w, int num) {


        tVidaEmpty.loadFromFile("imagenes/vidaPerdida.png");
        sVidaEmpty.setTexture(tVidaEmpty);
        sVidaEmpty.setScale(0.25 , 0.25);
        sVidaEmpty.setPosition(Vector2f(0 + (w->getSize().x/40),100 + (w->getSize().y/8 * num)));


        tVidaFull.loadFromFile("imagenes/vida.png");
        sVidaFull.setTexture(tVidaFull);
        sVidaFull.setScale(0.25 , 0.25);
        sVidaFull.setPosition(Vector2f(0 + (w->getSize().x/40),100 + w->getSize().y/8 * num));



}



void Vidas::draw(RenderWindow *w, int indicador) {


    if(indicador==0){
        w->draw(sVidaEmpty);
    }
        if(indicador==1){
            w->draw(sVidaFull);
        }

}

Vidas::~Vidas()=default;