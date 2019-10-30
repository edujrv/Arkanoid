
#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H

#include <SFML/Graphics.hpp>
#include "Stack.h"
using namespace sf;


//Class Ball Statement.
class Ball {
    //Private Variables.
private:
    float velBall;
    float velBallX;
    float velBallY;
    float xBall;
    float yBall;
    Sprite sBall;
    float radioBall;
    Texture tBall;

    //Public Variables.
public:
    bool isDrew = false;
    Ball(float xBall, float yBall, Texture *texturaBall);
    ~Ball();
    float getRadio(Texture *texturaBall);
    float deltaX(float xBall, float longbar, float xBar, float ballSize);
    void draw(RenderWindow *w);
    void move(float  longBar, float  highBar, float xBar, float yBar, float desktopY, float desktopX, float ballSize, int *vidas, char *resetPosition,char* perdidaVida, char* colisiono);
    void moveBallWithPlayerbar(float  longBar, float  highBar, float xBar, float yBar);


};//End Ball Class.


#endif //ARKANOID_BALL_H
