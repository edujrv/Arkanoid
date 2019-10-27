
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

    selectedItemIndex=0;
}

void Menu::draw(RenderWindow &w) {
    int i=0;

    for(i=0; i < 2; i++){
        w.draw(textm[i]);

    }

}

void Menu::moveUp() {

    if(selectedItemIndex-1 >= 0){
        textm[selectedItemIndex].setFillColor(Color::White);
        textm[selectedItemIndex].setCharacterSize(40);
        selectedItemIndex--;
        textm[selectedItemIndex].setFillColor(Color::Red);
        textm[selectedItemIndex].setCharacterSize(60);
    }

}

void Menu::moveDown() {
    if(selectedItemIndex+1 <2){
        textm[selectedItemIndex].setFillColor(Color::White);
        textm[selectedItemIndex].setCharacterSize(40);
        selectedItemIndex++;
        textm[selectedItemIndex].setFillColor(Color::Red);
        textm[selectedItemIndex].setCharacterSize(60);
    }
}

int Menu::getSelectedItemIndex() {
    return selectedItemIndex;
}

Menu::~Menu() = default;
