
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
    bool direccion;
    Sprite sBall;
    float radioBall;


    //Public Variables.
public:
    bool isDrew = false;
    Ball(float xBall, float yBall, Texture *texturaBall);
    ~Ball();
    float getRadio(Texture *texturaBall);
    void draw(RenderWindow *w);
    void move();
    void moveBallWithPlayerbar(float  longBar, float  highBar, float xBar, float yBar);


};//End Ball Class.


#endif //ARKANOID_BALL_H
