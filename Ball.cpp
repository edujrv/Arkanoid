#include "Ball.h"
#include <math.h>
#include "iostream"

//Builder.
Ball::Ball(float xBall, float yBall, Texture *texturaBall) {

    sBall.setTexture(*texturaBall);   //Sprite Loading.
    sBall.setScale(0.7, 0.7);  //Object Size. 0.7
    tBall = *texturaBall;


    //Initial Variables.
    this->xBall = xBall;
    this->yBall = yBall;
     velBall = 5;
     velBallX = 2;
     velBallY = sqrt(velBall * velBall - velBallX * velBallX);

    radioBall = 0;
    isDrew = false; // QUIERO CAMBIAR ESTE NOMBRE POR isPlaying o isAlive PERO NO ME DEJA EL CLION ASI QUE BUENO. ESTA VARIABLE QUIERE DECIR QUE SI LA PELOTA ESTA REBOTANDO POR LA PANTALLA O ESTA PEGADA A LA RAQUETA O MUERTA.

}//End Builder.


// moveBallWithPlayerbar
void Ball::moveBallWithPlayerbar(float longBar, float highBar, float xBar, float yBar) {

    float scale;
    scale = (float) (longBar * 0.2);
    xBall = xBar + (scale / 2) - ((Ball::getRadio(&tBall) * 0.7) / 2);
    yBall = yBar - highBar;

}//End moveBallWithPlayerbar.


//Dibujar.
void Ball::draw(RenderWindow *w) {

    sBall.setPosition(xBall, yBall);     //Spray Position.
    w->draw(sBall);       //Drawing.

}//End Dibujar.


// Calculo  de delta X
float Ball::deltaX(float xBall, float longbar, float xBar, float ballSize) {
    float deltaX;
    if ((xBall >= (xBar + (longbar*0.2) / 2) - (ballSize / 4)) && (xBall <= (xBar + (longbar*0.2) / 2) + (ballSize / 4))) {
        deltaX = 0;
    } else {
        if(xBall < (xBar + (longbar*0.2)/2) - (ballSize / 4)) {
            deltaX = (xBar + (longbar*0.2) / 2) - (xBall + ballSize / 2) - (ballSize / 4);
        } else if(xBall > (xBar + (longbar*0.2)/2) - (ballSize / 4)){
            deltaX = (xBar + (longbar*0.2) / 2) - (xBall + ballSize / 2) + (ballSize / 4);
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


void Ball::move(float longBar, float highBar, float xBar, float yBar, float desktopY, float desktopX, float ballSize,
                int *vidas, char *resetPosition) {

    if (isDrew) {

        yBall -= velBallY;
        sBall.setPosition(xBall, yBall);

        // DEFAULT CONDITION
        if (yBall <= 0) {
            velBallY *= -1;
        }

        //CONDICION DEFAULT
        if (yBall + ballSize >= yBar ) {
            if ((xBall+ballSize) >= (xBar) && xBall <= (xBar + (longBar * 0.2)) && (yBall <= yBar + highBar)) {
                velBallY *= -1;
                velBallX = deltaX(xBall, longBar, xBar, ballSize);
                yBall = (yBar-1)-ballSize;
            } else {
                if (yBall >= desktopY) {
                    isDrew = false;
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
        if ((xBall <= 0) || (xBall >= (desktopX - ballSize))) {
            velBallX *= -1;
        }
    }

}


//Destroyer.
Ball::~Ball() = default;
//End Destroyer.
