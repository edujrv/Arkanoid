
#ifndef ARKANOID_TEXTOS_H
#define ARKANOID_TEXTOS_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Textos {
private:
    //Font Print on Windows Declaration.
    Font * font = new Font();
    String message;
    int size = 0;
    int  posX;
    int posY;


    Text *txt = new Text();


public:
    Textos(String newMessage, Font *Font, int newSize, int x, int y);
    void setMessage(String message);
    void setFont(Font *font);
    void setSize(int size);
    void setPosition(int x, int y);
    void draw(RenderWindow *w);
    ~Textos();
};


#endif //ARKANOID_TEXTOS_H
