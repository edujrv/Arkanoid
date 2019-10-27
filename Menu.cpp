
#include "Menu.h"

Menu::Menu(float width, float hight) {

    if(!fontm.loadFromFile("fuentes/Retro.ttf")){
    }

    textm[0].setFont(fontm);
    textm[0].setFillColor(Color::Red);
    textm[0].setString("INICIAR");
    textm[0].setCharacterSize(60);
    textm[0].setPosition(Vector2f(width-(width/6), hight/3 * 1));

    textm[1].setFont(fontm);
    textm[1].setFillColor(Color::White);
    textm[1].setString("SALIR");
    textm[1].setCharacterSize(40);
    textm[1].setPosition(Vector2f(width-(width/6), hight/3 * 2));

    selecteditemindex=0;
}

void Menu::draw(RenderWindow &w) {
    int i=0;

    for(i=0; i < 2; i++){
        w.draw(textm[i]);

    }

}

void Menu::moveup() {

    if(selecteditemindex-1 >= 0){
        textm[selecteditemindex].setFillColor(Color::White);
        textm[selecteditemindex].setCharacterSize(40);
        selecteditemindex--;
        textm[selecteditemindex].setFillColor(Color::Red);
        textm[selecteditemindex].setCharacterSize(60);
    }

}

void Menu::movedown() {
    if(selecteditemindex+1 <2){
        textm[selecteditemindex].setFillColor(Color::White);
        textm[selecteditemindex].setCharacterSize(40);
        selecteditemindex++;
        textm[selecteditemindex].setFillColor(Color::Red);
        textm[selecteditemindex].setCharacterSize(60);
    }
}

int Menu::getselecteditemindex() {
    return selecteditemindex;
}

Menu::~Menu() = default;
