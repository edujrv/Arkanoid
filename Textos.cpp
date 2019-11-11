

#include "Textos.h"


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


void Textos::enterName(std::string letra) {
    std::cout<<"letra:"<<letra<<std::endl;
    txt->setString(letra);

}

void Textos::draw(RenderWindow *w) {
    w->draw(*txt);
}

Textos::~Textos() {
    delete txt;
}






















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
