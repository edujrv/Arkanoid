
#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H

#include <SFML/Graphics.hpp>
#include "Stack.h"
#include "Playerbar.h"
#include "Ladrillo.h"
#include "LinkedList.h"
#include <fstream>
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
    bool isDrew;
    bool isPlaying = false;
    Ball(Playerbar playerbar, Texture *texturaBall, float ballSize);
    ~Ball();
    float getRadio(Texture *texturaBall);
    float deltaX(Ball ball, Playerbar playerbar);
    void draw(RenderWindow *w);
    void move(Playerbar playerbar,Ball ball,RenderWindow *w,int *vidas, char *resetPosition,char* perdidaVida, char* colisiono,  LinkedList <Ladrillo*> &ladrillos);
    void moveBallWithPlayerbar(Playerbar playerbar);

    float deltaLadris(Ball ball,Ladrillo &ladrillos);

};//End Ball Class.


#endif //ARKANOID_BALL_H
