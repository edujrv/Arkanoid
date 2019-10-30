
#include "Vidas.h"
//#include <SFML/Graphics.hpp>

//using namespace sf;

Vidas::Vidas( float width, float hight, int num) {


        tVidaEmpty.loadFromFile("imagenes/vidaPerdida.png");
        sVidaEmpty.setTexture(tVidaEmpty);
        sVidaEmpty.setScale(0.13 , 0.13);
        sVidaEmpty.setPosition(Vector2f(0 + (width/30),100 + hight/8 * num));




        tVidaFull.loadFromFile("imagenes/vida.png");
        sVidaFull.setTexture(tVidaFull);
        sVidaFull.setScale(0.13 , 0.13);
        sVidaFull.setPosition(Vector2f(0 + (width/30),100 + hight/8 * num));



}

void Vidas::cambioIndicator(int indicador){
  indicator=indicador;
}

void Vidas::draw(RenderWindow *w, int indicador) {


    if(indicador==0){
        w->draw(sVidaEmpty);
    }
        if(indicador==1){
            w->draw(sVidaFull);
        }

}
