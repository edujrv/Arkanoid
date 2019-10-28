
#ifndef ARKANOID_MENU_H
#define ARKANOID_MENU_H

#include "Textos.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Menu {
private:
    int selectedItemIndex;
    Font fontm;
    Text textm[2];
public:
    Menu(float width, float hight);
    ~Menu();

    void draw(RenderWindow &w);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex();

};



#endif //ARKANOID_MENU_H
