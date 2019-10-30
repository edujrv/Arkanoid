
#ifndef ARKANOID_VIDAS_H
#define ARKANOID_VIDAS_H

#include <SFML/Graphics.hpp>


using namespace sf;

class Vidas {
private:
    Texture tVidaFull;
    Texture tVidaEmpty;
    Sprite sVidaFull;
    Sprite sVidaEmpty;
    int indicator;


public:
     explicit Vidas( float width, float hight, int num);
     void cambioIndicator(int indicador);
     void draw(RenderWindow *w, int indicador);
};


#endif //ARKANOID_VIDAS_H




