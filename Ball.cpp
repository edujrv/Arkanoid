#include "Ball.h"
#include <cmath>
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
    this->ballSize = ballSize;
     velBall = 7;
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


// Calculo  de delta X para la playerbar
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

void Ball::changeIsDrew(){
    isDrew = false;
}



void Ball::move(Playerbar playerbar, Ball ball, RenderWindow *w, int *vidas, char *resetPosition, char* perdidaVida, char* colisiono, LinkedList <Ladrillo*> &ladrillos, bool *verifColisionPowerup) {
int i = 0;
Ladrillo *aBorrar = nullptr;

    if (isDrew) {

        yBall -= velBallY;
        sBall.setPosition(xBall, yBall);

        // DEFAULT CONDITION
        if (yBall <= 0) {
            yBall += 10;
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

        // // // // // // // // // // // //
        //     COLISION DE LADRILLOS     //
        // // // // // // // // // // // //
        for (ladrillos.begin(); !ladrillos.ended() ; ladrillos.next()) {

            if ((ladrillos.get()->getY() + ladrillos.get()->getYLong() )>= yBall && (yBall + (ballSize * 0.7)) >= ladrillos.get()->getY() ){          // SI LA PELOTA CHOCA AL LADRILLO
                if ((xBall + (ballSize * 0.7) )>= ladrillos.get()->getX() && xBall <= (ladrillos.get()->getX() + ladrillos.get()->getXLong())){       //

                    //SI LA PELOTA CHOCA AL LADRILLO POR ABAJO
                    if ((yBall) >= (ladrillos.get()->getY() + (ladrillos.get()->getYLong() / 2))){
                        yBall += 5;
                        velBallY = -velBall;
                        *colisiono='V';
                    }

                    //SI LA PELOTA CHOCA AL LADRILLO POR IZQUIERDA
                   else if ((xBall + (ballSize * 0.7)) <= (ladrillos.get()->getX() + (ballSize ))){
                      //  ladrillos.remove(ladrillos.get()->getId());
                        xBall -= 10;
                        velBallX = velBall;
                        *colisiono='V';
                    }

                    //SI LA PELOTA CHOOCA AL LADRILLO POR ARRIBA
                   else if ((yBall + (ballSize * 0.7)) <= (ladrillos.get()->getY() + (ladrillos.get()->getYLong() / 2))){
                      // ladrillos.remove(ladrillos.get()->getId());
                        yBall -= 10;
                        velBallY = velBall;
                        *colisiono='V';
                    }

                    //SI LA PELOTA CHOCA AL LADRILLO POR DERECHA
                  else if (xBall >= ((ladrillos.get()->getX() + ladrillos.get()->getXLong()) - ((ballSize * 0.7) / 2)) ) {
                        yBall += 10;
                        velBallY = -velBall;
                        *colisiono='V';
                    }
                    i = ladrillos.get()->getId();

                  std::cout<<"id del ladrillo "<< i <<std::endl;
                    aBorrar = ladrillos.get();
                    *verifColisionPowerup = true;
                }
            }


        }
        if(aBorrar != nullptr){ // si tengo que borrar ese ladrillo lo saco de la lista
            ladrillos.remove(aBorrar);
            delete aBorrar; // Como había echo un new, hago un delete.
        }
        xBall -= velBallX;
        if ((xBall <= 130)) {
            velBallX *= -1;
            xBall = 131;
            *colisiono='V';
        } else if ((xBall >= (w->getSize().x - ballSize - 130))){
            velBallX *= -1;
            xBall = (w->getSize().x - ballSize - 130) - 1;
            *colisiono='V';
        }
    }

}


//Destroyer.
Ball::~Ball() = default;
//End Destroyer.


