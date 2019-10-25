
#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H

#include <SFML/Graphics.hpp>
using namespace sf;


//Class Ball Statement.
class Ball {
    //Private Variables.
private:
    float velBall;
    float xBall;
    float yBall;
    bool direccionY; // True = Up . False = Down
    bool direccionX; // True = Right . False = Left
    Sprite sBall;
    float radioBall;
    Texture tBall;

    //Public Variables.
public:
    bool isDrew = false;
    Ball(float xBall, float yBall, Texture *texturaBall);
    ~Ball();
    float getRadio(Texture *texturaBall);
    void draw(RenderWindow *w);
    void move(float  longBar, float  highBar, float xBar, float yBar, float desktopY, float desktopX, float ballSize, int *vidas, char *resetPosition);
    void moveBallWithPlayerbar(float  longBar, float  highBar, float xBar, float yBar);


};//End Ball Class.


#endif //ARKANOID_BALL_H
