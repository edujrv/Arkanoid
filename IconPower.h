
#ifndef ARKANOID_ICONPOWER_H
#define ARKANOID_ICONPOWER_H
#include <SFML/Graphics.hpp>


using namespace sf;


class IconPower {
private:
    Texture tIconPower;
    Sprite sIconPower;
public:
    IconPower(RenderWindow* w);
    void draw(RenderWindow *w);
    ~IconPower();

};


#endif //ARKANOID_ICONPOWER_H
