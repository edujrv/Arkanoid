//
// Created by fbara_ on 10/27/2019.
//

#ifndef ARKANOID_MENU_H
#define ARKANOID_MENU_H


#include <SFML/Graphics.hpp>
using namespace sf;

class Menu {
private:
    int selecteditemindex;
    Font fontm;
    Text textm[2];
public:
    Menu(float width, float hight);
    ~Menu();

    void draw(RenderWindow &w);
    void moveup();
    void movedown();
    int getselecteditemindex();

};



#endif //ARKANOID_MENU_H
