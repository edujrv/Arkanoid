
#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H

#include <SFML/Graphics.hpp>
#include "Stack.h"
#include "Playerbar.h"
#include "Ladrillo.h"

using namespace sf;


//Class Ball Statement.
class Ball {
    //Private Variables.
private:
    float ballSize;
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
    bool isPlaying = false;
    Ball(Playerbar playerbar, Texture *texturaBall, float ballSize);
    ~Ball();
    float getRadio(Texture *texturaBall);
    float deltaX(Ball ball, Playerbar playerbar);
    void draw(RenderWindow *w);
    void move(Playerbar playerbar,Ball ball,RenderWindow *w,int *vidas, char *resetPosition,char* perdidaVida, char* colisiono);
    void moveBallWithPlayerbar(Playerbar playerbar);
    bool colisionoLadrillo(Ladrillo ladri);

};//End Ball Class.


#endif //ARKANOID_BALL_H
