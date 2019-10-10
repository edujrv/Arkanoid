
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
    bool isDrew = false;

    //Public Variables.
public:
    Ball(float xBall, float yBall, Texture *texturaBall);
    ~Ball();
    float getLongX(Texture *texturaBall);
    void dibujar(RenderWindow *w);
    void drawBall(RenderWindow *w);
    float moverBall(char direccion, float);


};//End Ball Class.


#endif //ARKANOID_BALL_H
