
#include "IconPower.h"

IconPower::IconPower(RenderWindow* w){
    tIconPower.loadFromFile("imagenes/IconPower.png");
    sIconPower.setTexture(tIconPower);
    sIconPower.setScale(0.15 , 0.15);
    sIconPower.setPosition(Vector2f(0 + (w->getSize().x/40),100 + (w->getSize().y/8 * 4)));

}
void IconPower::draw(RenderWindow *w) {
    w->draw(sIconPower);
}

IconPower::~IconPower()=default;