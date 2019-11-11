
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



public:
     explicit Vidas( RenderWindow* w, int num);
     void draw(RenderWindow *w, int indicador);
    ~Vidas();
};


#endif //ARKANOID_VIDAS_H




