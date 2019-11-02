#include "Ball.h"
#include <math.h>
#include "iostream"

//Builder.
Ball::Ball(Playerbar playerbar, Texture *texturaBall, float ballSize) {

    sBall.setTexture(*texturaBall);   //Sprite Loading.
    sBall.setScale(0.7, 0.7);  //Object Size. 0.7
    tBall = *texturaBall;

    float xBall = playerbar.xPlayerbar + (playerbar.getLongX(&playerbar.tPlayerbar) / 2) - (ballSize / 2);
    float yBall = playerbar.yPlayerbar - playerbar.getLongY(&playerbar.tPlayerbar);
    //Initial Variables.
    this->xBall = xBall;
    this->yBall = yBall;
    this->ballSize=ballSize;
     velBall = 5;
     velBallX = 2;
     velBallY = sqrt(velBall * velBall - velBallX * velBallX);

    radioBall = 0;
    isDrew = false; // QUIERO CAMBIAR ESTE NOMBRE POR isPlaying o isAlive PERO NO ME DEJA EL CLION ASI QUE BUENO. ESTA VARIABLE QUIERE DECIR QUE SI LA PELOTA ESTA REBOTANDO POR LA PANTALLA O ESTA PEGADA A LA RAQUETA O MUERTA.

}//End Builder.


// moveBallWithPlayerbar
void Ball::moveBallWithPlayerbar(Playerbar playerbar) {

    float scale;
    scale = (float) (playerbar.getLongX(&playerbar.tPlayerbar) * 0.2);
    xBall = playerbar.xPlayerbar + (scale / 2) - ((Ball::getRadio(&tBall) * 0.7) / 2);
    yBall = playerbar.yPlayerbar - playerbar.getLongY(&playerbar.tPlayerbar);

}//End moveBallWithPlayerbar.


//Dibujar.
void Ball::draw(RenderWindow *w) {

    sBall.setPosition(xBall, yBall);     //Spray Position.
    w->draw(sBall);       //Drawing.

}//End Dibujar.


// Calculo  de delta X
float Ball::deltaX(Ball ball, Playerbar playerbar) {
    float deltaX;
    if ((xBall >= (playerbar.xPlayerbar + (playerbar.getLongX(&playerbar.tPlayerbar)*0.2) / 2) - (ballSize / 4)) && (xBall <= (playerbar.xPlayerbar + (playerbar.getLongX(&playerbar.tPlayerbar)*0.2) / 2) + (ballSize / 4))) {
        deltaX = 0;
    } else {
        if(xBall < (playerbar.xPlayerbar + (playerbar.getLongX(&playerbar.tPlayerbar)*0.2)/2) - (ballSize / 4)) {
            deltaX = (playerbar.xPlayerbar + (playerbar.getLongX(&playerbar.tPlayerbar)*0.2) / 2) - (xBall + ballSize / 2) - (ballSize / 4);
        } else if(xBall > (playerbar.xPlayerbar + (playerbar.getLongX(&playerbar.tPlayerbar)*0.2)/2) - (ballSize / 4)){
            deltaX = (playerbar.xPlayerbar + (playerbar.getLongX(&playerbar.tPlayerbar)*0.2) / 2) - (xBall + ballSize / 2) + (ballSize / 4);
        }
    }
    std::cout << "deltaX = "<< deltaX << std::endl;
    if(deltaX < 0){
        return (deltaX/7)+2;
    }
    if(deltaX > 0){
        return (deltaX/7)-2;
    }
    return deltaX/7;
}

//getRadio.     //En realidad aqui estamos obteniendo el diametro podriamos cambiar los nombres de variables es confuso.
float Ball::getRadio(Texture *texturaBall) {
    radioBall = texturaBall->getSize().x;
    return radioBall;
}
//End getRadio.


void Ball::move(Playerbar playerbar,Ball ball,RenderWindow *w,int *vidas, char *resetPosition,char* perdidaVida, char* colisiono) {



    if (isDrew) {

        yBall -= velBallY;
        sBall.setPosition(xBall, yBall);

        // DEFAULT CONDITION
        if (yBall <= 0) {
            velBallY *= -1;
            *colisiono='V';
        }

        //CONDICION DEFAULT
        if (yBall + ballSize >= playerbar.yPlayerbar) {
            if ((xBall+ballSize) >= (playerbar.xPlayerbar) && xBall <= (playerbar.xPlayerbar + (playerbar.getLongX(&playerbar.tPlayerbar) * 0.2)) && (yBall <= playerbar.yPlayerbar + playerbar.getLongY(&playerbar.tPlayerbar))) {
                velBallY *= -1;
                velBallX = deltaX(ball,playerbar);
                yBall = (playerbar.yPlayerbar-1)-ballSize;
                *colisiono='V';
            } else {
                if (yBall >= w->getSize().y) {
                    isDrew = false;
                    *perdidaVida='V';
                    (*vidas)--;
                    *resetPosition = 'V';
                    velBallY = abs(velBallY);
                }

            }

        }

        /*
                * INSERTAR CONDICION DE COLISIONES EJE Y
                **/


        xBall -= velBallX;
        // sBall.setPosition(xBall, yBall);
        if ((xBall <= 140) || (xBall >= (w->getSize().x - ballSize - 130))) {
            velBallX *= -1;
            *colisiono='V';
        }
    }

}

bool Ball::colisionoLadrillo(Ladrillo ladri) {
    if (xBall >= (float)(ladri.getX() && xBall < (ladri.getX() + ladri.getXLong())) && (yBall >= ladri.getY() && yBall < (ladri.getY() + ladri.getYLong()))){

    }
    return false;
}


//Destroyer.
Ball::~Ball() = default;
//End Destroyer.
