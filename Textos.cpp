//
// Created by Edu on 10/27/2019.
//

#include "Textos.h"
#include<SFML/Graphics.hpp>

using namespace sf;

Textos::Textos(String newMessage, Font *Font, int newSize, int x, int y) {

    txt->setFillColor(Color::Red);
    this->message = newMessage;
    txt->setString( message);
    this->font = Font;
    txt->setFont(*font);
    this->size = newSize;
    txt->setCharacterSize(size);
    this->posX = x;
    this->posY = y;
    txt->setPosition(posX, posY);
}

void Textos::setMessage(String newMessage) {
    this->message = newMessage;
    txt->setString( message);
}

void Textos::setFont(Font *Font) {
    this->font = Font;
    txt->setFont(*font);
}

void Textos::setSize(int newSize) {
    this->size = newSize;
    txt->setCharacterSize(size);
}

void Textos::setPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
    txt->setPosition((float) posX, (float) posY);
}

void Textos::draw(RenderWindow *w) {
    w->draw(*txt);
}

Textos::~Textos() {
    delete txt;
}




// txt->setOrigin(txtGameOver->getGlobalBounds().width / 2, txtGameOver->getGlobalBounds().height / 2);

















/*
//Font Assignment.
fuenteRetro->loadFromFile("fuentes/Retro.ttf");

//Text Configuration.
txtVidas->setFont(*fuenteRetro);
txtVidas->setString("LIFES");
txtVidas->setPosition(0,0);
txtVidas->setFillColor(Color::Red);
txtVidas->setCharacterSize(20);

numVidas->setFont(*fuenteRetro);
numVidas->setPosition(50,0);
numVidas->setFillColor(Color::Red);
numVidas->setCharacterSize(20);



txtTryAgain->setString("Press space to try again");
txtTryAgain->setFont(*fuenteRetro);
txtTryAgain->setFillColor(Color::Red);
txtTryAgain->setCharacterSize(30);
txtTryAgain->setPosition(desktopX/2 - 3,desktopY/2 - 30);
txtTryAgain->setOrigin(txtTryAgain->getGlobalBounds().width/2, txtTryAgain->getGlobalBounds().height/2);

txtQuit->setString("Press esc to quit");
txtQuit->setFont(*fuenteRetro);
txtQuit->setFillColor(Color::Red);
txtQuit->setCharacterSize(30);
txtQuit->setPosition(desktopX/2 + 40 ,desktopY/2 + 30);
txtQuit->setOrigin(txtTryAgain->getGlobalBounds().width/2, txtTryAgain->getGlobalBounds().height/2);
 */
